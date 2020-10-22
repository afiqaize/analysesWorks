/*******************************************************************************
 2HDMC - two-Higgs-doublet model calculator
 Demo program

 http://2hdmc.hepforge.org
*******************************************************************************/
#include "Constraints.h"
#include "DecayTable.h"
#include "SM.h"
#include "THDM.h"

#include "tclap/CmdLine.h"

constexpr double beyond_lhc = 5000.;
constexpr double wepsH = 0.0002;
constexpr double wepsA = 0.00001;
constexpr double meps = 0.05;
constexpr double teps = 0.00001;
constexpr double damper = 0.975;

/*/ this is overkill for this purpose
bool almost_equal(double x, double y, int ulp = 2)
{
  // the machine epsilon has to be scaled to the magnitude of the values used
  // and multiplied by the desired precision in ULPs (units in the last place)
  return std::abs(x - y) <= std::numeric_limits<double>::epsilon() * std::abs(x + y) * ulp
    // unless the result is subnormal
    or std::abs(x - y) < std::numeric_limits<double>::min();
}
*/

double distance_to_target(THDM &model, double mh, double mA, double tb, int idx, double muse, double wuse)
{
  if (!model.set_hMSSM(mh, mA, tb))
    return 9999.;

  DecayTable table(model);
  double weps = (idx == 3) ? wepsA : wepsH;
  double wtmp = table.get_gammatot_h(idx) / muse;

  double mdist = std::abs(model.get_hmass(idx) - muse) > 0.5 * meps ? 
    ((model.get_hmass(idx) - muse) * (model.get_hmass(idx) - muse) / (muse * muse)) : 0.;
  double wdist = std::abs(wtmp - wuse) > 0.5 * weps ? 
    ((wtmp - wuse) * (wtmp - wuse) / (wuse * wuse)) : 0.;

  return 1000. * (mdist + wdist);
}

int main(int argc, char **argv) {
  TCLAP::CmdLine cmdbase("A/H -> analysis, 2HDMC calculator", ' ', "0.01");
  TCLAP::ValueArg<double> cmdmA("", "mA", "mass of A", false, beyond_lhc, "", cmdbase);
  TCLAP::ValueArg<double> cmdwA("", "wA", "relative width of A", false, -1., "", cmdbase);
  TCLAP::ValueArg<double> cmdmH("", "mH", "mass of H", false, beyond_lhc, "", cmdbase);
  TCLAP::ValueArg<double> cmdwH("", "wH", "relative width of H", false, -1., "", cmdbase);
  TCLAP::ValueArg<double> cmdtb("", "tanb", "tan beta", false, 1., "", cmdbase);
  TCLAP::ValueArg<double> cmdrl("", "relax", "multiplier of epsilon window to report match in singlepoint", false, 10., "", cmdbase);
  TCLAP::SwitchArg cmdsp("", "singlepoint", "Calculate only for single point", cmdbase, false);
  TCLAP::SwitchArg cmdsc("", "skipcheck", "Skip unitarity, pertubativity and stability checks", cmdbase, false);
  cmdbase.parse( argc, argv );

  double mA = cmdmA.getValue();
  double wA = cmdwA.getValue();
  double mH = cmdmH.getValue();
  double wH = cmdwH.getValue();
  double tb = cmdtb.getValue();
  double rl = cmdrl.getValue();
  bool sp = cmdsp.getValue();
  bool sc = cmdsc.getValue();

  // remove invalid parameters
  // setup such that do either A or H, not both
  if (!(mA < beyond_lhc) and !(mH < beyond_lhc))
    return -1;
  if (!(wA > 0. and wA < 1.) and !(wH > 0. and wH < 1.))
    return -1;
  if (!(tb > 0.))
    return -1;

  // Create SM and set parameters
  SM sm;
  sm.set_qmass_pole(6, 172.5);
  sm.set_qmass_pole(5, 4.7);

  sm.set_lmass_pole(3, 1.777);

  // FIXME find the value the A/H model
  //sm.set_alpha(1. / 127.934);
  //sm.set_alpha0(1. / 137.0359997);

  sm.set_alpha_s(0.118);

  sm.set_MZ(91.188);
  sm.set_gamma_Z(2.441404);

  sm.set_MW(80.419);
  sm.set_gamma_W(2.0476);

  sm.set_GF(1.16639E-5);

  // Create 2HDM and set SM parameters
  THDM model;
  model.set_SM(sm);

  double mh = 125.;
  int idx = (wA > 0.) ? 3 : 2, wprev = 0, mprev = 0, iter = -1;
  const std::string puse = (idx == 3) ? "A" : "H";
  double tstep = 0.5, mstep = 5., muse = (idx == 3) ? mA : mH, wuse = (idx == 3) ? wA : wH, weps = (idx == 3) ? wepsA : wepsH;
  double dtmp = damper, mtmp = -1., wtmp = -1.;

  if (idx == 2 and !(mA < beyond_lhc))
    mA = 0.75 * mH;

  double min_distance = 9999., fstep = 9999.;
  std::array<double, 41> variation = {9999., 
                                      9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999.,
                                      9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999.,
                                      9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999.,
                                      9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999.,
                                      9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999.};
  while (std::abs(wtmp - wuse) > weps or std::abs(mtmp - muse) > meps) {
    variation[0] = distance_to_target(model, mh, mA, tb, idx, muse, wuse);

    if (!sp) {
      fstep = 1.;
      variation[1] = distance_to_target(model, mh, mA + (fstep * mstep), tb, idx, muse, wuse);
      variation[2] = distance_to_target(model, mh, mA - (fstep * mstep), tb, idx, muse, wuse);
      variation[3] = distance_to_target(model, mh, mA, tb + (fstep * tstep), idx, muse, wuse);
      variation[4] = distance_to_target(model, mh, mA, tb - (fstep * tstep), idx, muse, wuse);
      variation[5] = distance_to_target(model, mh, mA + (fstep * mstep), tb + (fstep * tstep), idx, muse, wuse);
      variation[6] = distance_to_target(model, mh, mA - (fstep * mstep), tb - (fstep * tstep), idx, muse, wuse);
      variation[7] = distance_to_target(model, mh, mA + (fstep * mstep), tb - (fstep * tstep), idx, muse, wuse);
      variation[8] = distance_to_target(model, mh, mA - (fstep * mstep), tb + (fstep * tstep), idx, muse, wuse);

      fstep = 10.;
      variation[9] = distance_to_target(model, mh, mA + (fstep * mstep), tb, idx, muse, wuse);
      variation[10] = distance_to_target(model, mh, mA - (fstep * mstep), tb, idx, muse, wuse);
      variation[11] = distance_to_target(model, mh, mA, tb + (fstep * tstep), idx, muse, wuse);
      variation[12] = distance_to_target(model, mh, mA, tb - (fstep * tstep), idx, muse, wuse);
      variation[13] = distance_to_target(model, mh, mA + (fstep * mstep), tb + (fstep * tstep), idx, muse, wuse);
      variation[14] = distance_to_target(model, mh, mA - (fstep * mstep), tb - (fstep * tstep), idx, muse, wuse);
      variation[15] = distance_to_target(model, mh, mA + (fstep * mstep), tb - (fstep * tstep), idx, muse, wuse);
      variation[16] = distance_to_target(model, mh, mA - (fstep * mstep), tb + (fstep * tstep), idx, muse, wuse);

      fstep = 2.;
      variation[17] = distance_to_target(model, mh, mA + (fstep * mstep), tb, idx, muse, wuse);
      variation[18] = distance_to_target(model, mh, mA - (fstep * mstep), tb, idx, muse, wuse);
      variation[19] = distance_to_target(model, mh, mA, tb + (fstep * tstep), idx, muse, wuse);
      variation[20] = distance_to_target(model, mh, mA, tb - (fstep * tstep), idx, muse, wuse);
      variation[21] = distance_to_target(model, mh, mA + (fstep * mstep), tb + (fstep * tstep), idx, muse, wuse);
      variation[22] = distance_to_target(model, mh, mA - (fstep * mstep), tb - (fstep * tstep), idx, muse, wuse);
      variation[23] = distance_to_target(model, mh, mA + (fstep * mstep), tb - (fstep * tstep), idx, muse, wuse);
      variation[24] = distance_to_target(model, mh, mA - (fstep * mstep), tb + (fstep * tstep), idx, muse, wuse);

      fstep = 0.5;
      variation[25] = distance_to_target(model, mh, mA + (fstep * mstep), tb, idx, muse, wuse);
      variation[26] = distance_to_target(model, mh, mA - (fstep * mstep), tb, idx, muse, wuse);
      variation[27] = distance_to_target(model, mh, mA, tb + (fstep * tstep), idx, muse, wuse);
      variation[28] = distance_to_target(model, mh, mA, tb - (fstep * tstep), idx, muse, wuse);
      variation[29] = distance_to_target(model, mh, mA + (fstep * mstep), tb + (fstep * tstep), idx, muse, wuse);
      variation[30] = distance_to_target(model, mh, mA - (fstep * mstep), tb - (fstep * tstep), idx, muse, wuse);
      variation[31] = distance_to_target(model, mh, mA + (fstep * mstep), tb - (fstep * tstep), idx, muse, wuse);
      variation[32] = distance_to_target(model, mh, mA - (fstep * mstep), tb + (fstep * tstep), idx, muse, wuse);

      fstep = 0.1;
      variation[33] = distance_to_target(model, mh, mA + (fstep * mstep), tb, idx, muse, wuse);
      variation[34] = distance_to_target(model, mh, mA - (fstep * mstep), tb, idx, muse, wuse);
      variation[35] = distance_to_target(model, mh, mA, tb + (fstep * tstep), idx, muse, wuse);
      variation[36] = distance_to_target(model, mh, mA, tb - (fstep * tstep), idx, muse, wuse);
      variation[37] = distance_to_target(model, mh, mA + (fstep * mstep), tb + (fstep * tstep), idx, muse, wuse);
      variation[38] = distance_to_target(model, mh, mA - (fstep * mstep), tb - (fstep * tstep), idx, muse, wuse);
      variation[39] = distance_to_target(model, mh, mA + (fstep * mstep), tb - (fstep * tstep), idx, muse, wuse);
      variation[40] = distance_to_target(model, mh, mA - (fstep * mstep), tb + (fstep * tstep), idx, muse, wuse);
    }

    auto mdist = std::min_element(std::begin(variation), std::end(variation));
    auto mpos = std::distance(std::begin(variation), mdist);
    if (*mdist < min_distance)
      min_distance = *mdist;

    if (mpos > 32) {
      fstep = 0.1;
      mpos -= 32;
    }
    else if (mpos > 24) {
      fstep = 0.5;
      mpos -= 24;
    }
    else if (mpos > 16) {
      fstep = 2.;
      mpos -= 16;
    }
    else if (mpos > 8) {
      fstep = 10.;
      mpos -= 8;
    }
    else 
      fstep = 1.;

    if (mpos == 0) {
      if (dtmp < 1e-6) {
        std::cerr << "No more improvement detected after " << iter << " iterations. Aborting!!" << std::endl;
        break;
      }

      mstep *= dtmp;
      tstep *= dtmp;
      dtmp *= dtmp;
    }
    else if (mpos == 1) {
      mA += (fstep * mstep);
    }
    else if (mpos == 2) {
      mA -= (fstep * mstep);
    }
    else if (mpos == 3) {
      tb += (fstep * tstep);
    }
    else if (mpos == 4) {
      tb -= (fstep * tstep);
    }
    else if (mpos == 5) {
      mA += (fstep * mstep);
      tb += (fstep * tstep);
    }
    else if (mpos == 6) {
      mA -= (fstep * mstep);
      tb -= (fstep * tstep);
    }
    else if (mpos == 7) {
      mA += (fstep * mstep);
      tb -= (fstep * tstep);
    }
    else if (mpos == 8) {
      mA -= (fstep * mstep);
      tb += (fstep * tstep);
    }

    model.set_hMSSM(mh, mA, tb);
    mtmp = model.get_hmass(idx);
    DecayTable table(model);
    wtmp = table.get_gammatot_h(idx) / muse;
    std::cout << std::defaultfloat << "iteration " << ++iter << ": " << puse << muse 
              << ", mass " << std::fixed << std::setprecision(6) << mtmp 
              << ", width " << std::fixed << std::setprecision(6) << wtmp
              << ", distance " << std::fixed << std::setprecision(6) << min_distance
              << ", tanb " << std::fixed << std::setprecision(6) << tb 
              << ", mA " << std::fixed << std::setprecision(6) << mA;
    if (sp) {
      if (rl > 1. and std::abs(wtmp - wuse) < weps and std::abs(mtmp - muse) < meps)
        std::cout << " [singlepoint] >>> within search epsilon!!! <<<\n";
      else if (std::abs(wtmp - wuse) < rl * weps and std::abs(mtmp - muse) < rl * meps)
        std::cout << std::defaultfloat << " [singlepoint] >>> within " << rl << " epsilon!!! <<<\n";
      else
        std::cout << "\n";
      break;
    }
    else 
      std::cout << "\n";
  }
  (void) wprev;
  (void) mprev;

  /*
  while (std::abs(wtmp - wuse) > weps or std::abs(model.get_hmass(idx) - muse) > meps) {
    if (!model.set_hMSSM(mh, mA, tb)) {
      std::cerr << "The specified parameters mh " << mh << " mA " << mA << " tanb " << tb << " are not valid. Aborting!" << std::endl;
      return -1;
    }

    DecayTable table(model);
    wtmp = table.get_gammatot_h(idx) / muse;

    std::cout << std::defaultfloat << "iteration " << ++iter << ": " << puse << muse 
              << ", mass " << std::fixed << std::setprecision(6) << model.get_hmass(idx) 
              << ", tanb " << std::fixed << std::setprecision(6) << tb 
              << ", width " << std::fixed << std::setprecision(6) << wtmp;

    if (sp) {
      std::cout << "   [singlepoint setting: mA " << cmdmA.getValue() << " wA " << cmdwA.getValue() << " mH " << cmdmH.getValue() <<  " wH " << cmdwH.getValue() << " tanb " << cmdtb.getValue() << "]";

      if (rl > 1. and std::abs(wtmp - wuse) < weps and std::abs(model.get_hmass(idx) - muse) < meps)
        std::cout << " >>> within search epsilon!!! <<<\n";
      else if (std::abs(wtmp - wuse) < rl * weps and std::abs(model.get_hmass(idx) - muse) < rl * meps)
        std::cout << std::defaultfloat << " >>> within " << rl << " epsilon!!! <<<\n";
      else
        std::cout << "\n";

      break;
    }
    else 
      std::cout << "\n";

    if (iter > 2000) {
      std::cout << "2000 iterations of the search performed without the masses/widths within desired epsilon. Aborting!" << std::endl;
      return -1;
    }

    if (std::abs(model.get_hmass(idx) - muse) > meps) {
      if (model.get_hmass(idx) > muse) {
        if (mprev == -1 and mstep > meps)
          mstep = damper * mstep;
        mprev = 1;

        mA = mA - mstep;
      }
      else if (model.get_hmass(idx) < muse) {
        if (mprev == 1 and mstep > meps)
          mstep = damper * mstep;
        mprev = -1;

        mA = mA + mstep;
      }

      continue;
    }

    if (std::abs(wtmp - wuse) > weps) {
      if (wtmp > wuse) {
        if (wprev == -1 and tstep > teps)
          tstep = damper * tstep;
        wprev = 1;

        tb = tb * (1. + tstep);

        if (idx == 2)
          mA = mA - mstep;
      }
      else if (wtmp < wuse) {
        if (wprev == 1 and tstep > teps)
          tstep = damper * tstep;
        wprev = -1;

        tb = tb * (1. - tstep);

        if (idx == 2)
          mA = mA + mstep;
      }
    }
  }
  */

  if (!sc) {
    std::cout << "\nChecking 2HDM model constaints:\n";
    Constraints constr(model);
    const bool stable = constr.check_stability();
    const bool unitary = constr.check_unitarity();
    const bool perturbative = constr.check_perturbativity();

    if (!(stable and unitary and perturbative)) {
      std::cout << "Parameter search results in a model that is either unstable, not unitary or not perturbative. Aborting!" << std::endl;
      return -1;
    }
    else
      std::cout << "Stability, unitarity and perturbativity constraints are all satisfied!\n\n";
  }
  else
      std::cout << ">>> FIXME <<< skipping stability, unitarity and perturbativity checks!!!\n\n";

  std::cout << "Printing model parameters:\n";
  model.print_param_phys();
  model.print_param_gen();
  model.print_param_hybrid();

  std::cout << "\nPrinting decays of all Higgses in this model\n";
  DecayTable table(model);
  table.print_decays(1);
  std::cout << "h mass: " << model.get_hmass(1) << " relative width " << table.get_gammatot_h(1) / model.get_hmass(1) << "\n";

  table.print_decays(3);
  std::cout << "A mass: " << model.get_hmass(3) << " relative width " << table.get_gammatot_h(3) / model.get_hmass(3) << "\n";

  table.print_decays(2);
  std::cout << "H mass: " << model.get_hmass(2) << " relative width " << table.get_gammatot_h(2) / model.get_hmass(2) << "\n";

  table.print_decays(4);
  std::cout << "H+ mass: " << model.get_hmass(4) << " relative width " << table.get_gammatot_h(4) / model.get_hmass(4) << "\n";

  //std::cout << sm.get_qmass_MSbar(4) << "\n";
  //std::cout << sm.get_qmass_MSbar(5) << "\n";
}
