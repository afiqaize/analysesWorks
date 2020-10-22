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
#include <random>

constexpr double beyond_lhc = 1000000.;
constexpr double wepsH = 0.0002;
constexpr double wepsA = 0.00002;
constexpr double teps = 0.00001;
constexpr double damper = 0.975;
constexpr double mh = 125.;

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

double distance_to_target(SM &sm, THDM &model, double mA, double mH, double mC, double tb, double sba, double sqm12, 
                          int idx, double muse, double wuse)
{
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

  model.set_SM(sm);
  if (!model.set_param_phys(mh, mH, mA, mC, sba, /*lam6*/ 0., /*lam7*/ 0., sqm12, tb))
    return 9999.;

  model.set_yukawas_type(2);
  DecayTable table(model);
  const double wtmp = table.get_gammatot_h(idx) / muse;
  /*
  std::cout << std::defaultfloat << "inside "
            << ", width " << std::fixed << std::setprecision(6) << wtmp
            << ", distance2 " << std::fixed << std::setprecision(6) << 1000. * std::abs(wtmp - wuse)
            << ", mA " << std::defaultfloat << mA
            << ", mH " << std::defaultfloat << mH
            << ", mC " << std::defaultfloat << mC
            << ", tanb " << std::fixed << std::setprecision(6) << tb
            << ", sba " << std::fixed << std::setprecision(6) << sba
            << ", sqm12 " << std::fixed << std::setprecision(6) << sqm12 << "\n";
  */
  return 1000. * std::abs(wtmp - wuse);
}

int main(int argc, char **argv) {
  TCLAP::CmdLine cmdbase("A/H -> analysis, 2HDMC calculator", ' ', "0.01");
  TCLAP::ValueArg<double> cmdmA("", "mA", "mass of A", false, beyond_lhc, "", cmdbase);
  TCLAP::ValueArg<double> cmdwA("", "wA", "relative width of A", false, -1., "", cmdbase);
  TCLAP::ValueArg<double> cmdmH("", "mH", "mass of H", false, beyond_lhc, "", cmdbase);
  TCLAP::ValueArg<double> cmdwH("", "wH", "relative width of H", false, -1., "", cmdbase);
  TCLAP::ValueArg<double> cmdmC("", "mC", "mass of H+", false, beyond_lhc, "", cmdbase);
  TCLAP::ValueArg<double> cmdtb("", "tanb", "tan beta", false, 1., "", cmdbase);
  TCLAP::ValueArg<double> cmdsba("", "sba", "sin(beta - alpha), should be near -1", false, -1., "", cmdbase);
  TCLAP::ValueArg<double> cmdsqm12("", "sqm12", "square of m12", false, beyond_lhc / 5., "", cmdbase);
  TCLAP::ValueArg<double> cmdrl("", "relax", "multiplier of epsilon window to report match in singlepoint", false, 10., "", cmdbase);
  TCLAP::SwitchArg cmdsp("", "singlepoint", "Calculate only for single point", cmdbase, false);
  TCLAP::SwitchArg cmdsc("", "skipcheck", "Skip unitarity, pertubativity and stability checks", cmdbase, false);
  TCLAP::SwitchArg cmdrand("", "random", "false: always use 2 and 5 as the grid search multipliers. default." 
                           "false: use random prime multipliers each iteration from 1 - 20.", cmdbase, false);
  cmdbase.parse( argc, argv );

  double mA = cmdmA.getValue();
  double wA = cmdwA.getValue();
  double mH = cmdmH.getValue();
  double wH = cmdwH.getValue();
  double mC = cmdmC.getValue();
  double tb = cmdtb.getValue();
  double sba = cmdsba.getValue();
  double sqm12 = cmdsqm12.getValue();
  double rl = cmdrl.getValue();
  bool sp = cmdsp.getValue();
  bool sc = cmdsc.getValue();
  bool randomff = cmdrand.getValue();

  // remove invalid parameters
  // setup such that do either A or H, not both
  if (!(mA < beyond_lhc) and !(mH < beyond_lhc))
    return -1;
  if (!(wA > 0. and wA < 1.) and !(wH > 0. and wH < 1.))
    return -1;
  if (!(sqm12 > 0.))
    return -1;
  if (!(tb > 0.))
    return -1;

  int idx = (wA > 0.) ? 3 : 2, iter = -1;
  const std::string puse = (idx == 3) ? "A" : "H";
  double tstep = 0.1, sstep = 0.000002, mstep = 5000.;
  double dtmp = damper, wtmp = -1.;

  const double muse = (idx == 3) ? mA : mH;
  const double wuse = (idx == 3) ? wA : wH;
  const double weps = (idx == 3) ? wepsA : wepsH;

  const std::array<double, 8> ffa = {2., 3., 5., 7., 11., 13., 17., 19.};
  std::array<double, 2> ffu = {ffa[0], ffa[1]};
  std::mt19937_64 rng(std::random_device{}());
  std::uniform_int_distribution<> uc(0, 7);
 
  double min_distance = 9999., ff = 9999.;
  // dofs tb, sba, sqm12
  std::array<double, 131> variation = {9999., 
                                       // x1 unn dnn nun ndn nnu nnd uun udn dun ddn unu und dnu dnd nuu nud ndu ndd uuu uud udu udd duu ddu dud ddd
                                       9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999.,
                                       9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999.,
                                       // x2 unn dnn nun ndn nnu nnd uun udn dun ddn unu und dnu dnd nuu nud ndu ndd uuu uud udu udd duu ddu dud ddd
                                       9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999.,
                                       9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999.,
                                       // x5 unn dnn nun ndn nnu nnd uun udn dun ddn unu und dnu dnd nuu nud ndu ndd uuu uud udu udd duu ddu dud ddd
                                       9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999.,
                                       9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999.,
                                       // /2 unn dnn nun ndn nnu nnd uun udn dun ddn unu und dnu dnd nuu nud ndu ndd uuu uud udu udd duu ddu dud ddd
                                       9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999.,
                                       9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999.,
                                       // /5 unn dnn nun ndn nnu nnd uun udn dun ddn unu und dnu dnd nuu nud ndu ndd uuu uud udu udd duu ddu dud ddd
                                       9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999.,
                                       9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999.};

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

  THDM model;
  model.set_SM(sm);

  while (std::abs(wtmp - wuse) > weps) {
    if (randomff) {
      int i1 = uc(rng), i2 = uc(rng);
      while (i2 == i1)
        i2 = uc(rng);

      ffu[0] = ffa[i1];
      ffu[1] = ffa[i2];
    }

    variation[0] = distance_to_target(sm, model, mA, mH, mC, tb, sba, sqm12, idx, muse, wuse);

    if (!sp) {
      ff = 1.;
      variation[1]   = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba,                sqm12,                idx, muse, wuse);
      variation[2]   = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba,                sqm12,                idx, muse, wuse);
      variation[3]   = distance_to_target(sm, model, mA, mH, mC, tb,                sba + (ff * sstep), sqm12,                idx, muse, wuse);
      variation[4]   = distance_to_target(sm, model, mA, mH, mC, tb,                sba - (ff * sstep), sqm12,                idx, muse, wuse);
      variation[5]   = distance_to_target(sm, model, mA, mH, mC, tb,                sba,                sqm12 + (ff * mstep), idx, muse, wuse);
      variation[6]   = distance_to_target(sm, model, mA, mH, mC, tb,                sba,                sqm12 - (ff * mstep), idx, muse, wuse);

      variation[7]   = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba + (ff * sstep), sqm12,                idx, muse, wuse);
      variation[8]   = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba - (ff * sstep), sqm12,                idx, muse, wuse);
      variation[9]   = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba + (ff * sstep), sqm12,                idx, muse, wuse);
      variation[10]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba - (ff * sstep), sqm12,                idx, muse, wuse);
      variation[11]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba,                sqm12 + (ff * mstep), idx, muse, wuse);
      variation[12]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba,                sqm12 - (ff * mstep), idx, muse, wuse);
      variation[13]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba,                sqm12 + (ff * mstep), idx, muse, wuse);
      variation[14]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba,                sqm12 - (ff * mstep), idx, muse, wuse);
      variation[15]  = distance_to_target(sm, model, mA, mH, mC, tb,                sba + (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[16]  = distance_to_target(sm, model, mA, mH, mC, tb,                sba + (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);
      variation[17]  = distance_to_target(sm, model, mA, mH, mC, tb,                sba - (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[18]  = distance_to_target(sm, model, mA, mH, mC, tb,                sba - (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);

      variation[19]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba + (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[20]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba + (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);
      variation[21]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba - (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[22]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba - (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);
      variation[23]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba + (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[24]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba - (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[25]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba + (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);
      variation[26]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba - (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);

      ff = ffu[0];
      variation[27]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba,                sqm12,                idx, muse, wuse);
      variation[28]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba,                sqm12,                idx, muse, wuse);
      variation[29]  = distance_to_target(sm, model, mA, mH, mC, tb,                sba + (ff * sstep), sqm12,                idx, muse, wuse);
      variation[30]  = distance_to_target(sm, model, mA, mH, mC, tb,                sba - (ff * sstep), sqm12,                idx, muse, wuse);
      variation[31]  = distance_to_target(sm, model, mA, mH, mC, tb,                sba,                sqm12 + (ff * mstep), idx, muse, wuse);
      variation[32]  = distance_to_target(sm, model, mA, mH, mC, tb,                sba,                sqm12 - (ff * mstep), idx, muse, wuse);

      variation[33]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba + (ff * sstep), sqm12,                idx, muse, wuse);
      variation[34]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba - (ff * sstep), sqm12,                idx, muse, wuse);
      variation[35]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba + (ff * sstep), sqm12,                idx, muse, wuse);
      variation[36]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba - (ff * sstep), sqm12,                idx, muse, wuse);
      variation[37]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba,                sqm12 + (ff * mstep), idx, muse, wuse);
      variation[38]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba,                sqm12 - (ff * mstep), idx, muse, wuse);
      variation[39]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba,                sqm12 + (ff * mstep), idx, muse, wuse);
      variation[40]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba,                sqm12 - (ff * mstep), idx, muse, wuse);
      variation[41]  = distance_to_target(sm, model, mA, mH, mC, tb,                sba + (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[42]  = distance_to_target(sm, model, mA, mH, mC, tb,                sba + (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);
      variation[43]  = distance_to_target(sm, model, mA, mH, mC, tb,                sba - (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[44]  = distance_to_target(sm, model, mA, mH, mC, tb,                sba - (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);

      variation[45]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba + (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[46]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba + (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);
      variation[47]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba - (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[48]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba - (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);
      variation[49]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba + (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[50]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba - (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[51]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba + (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);
      variation[52]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba - (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);

      ff = ffu[1];
      variation[53]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba,                sqm12,                idx, muse, wuse);
      variation[54]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba,                sqm12,                idx, muse, wuse);
      variation[55]  = distance_to_target(sm, model, mA, mH, mC, tb,                sba + (ff * sstep), sqm12,                idx, muse, wuse);
      variation[56]  = distance_to_target(sm, model, mA, mH, mC, tb,                sba - (ff * sstep), sqm12,                idx, muse, wuse);
      variation[57]  = distance_to_target(sm, model, mA, mH, mC, tb,                sba,                sqm12 + (ff * mstep), idx, muse, wuse);
      variation[58]  = distance_to_target(sm, model, mA, mH, mC, tb,                sba,                sqm12 - (ff * mstep), idx, muse, wuse);

      variation[59]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba + (ff * sstep), sqm12,                idx, muse, wuse);
      variation[60]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba - (ff * sstep), sqm12,                idx, muse, wuse);
      variation[61]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba + (ff * sstep), sqm12,                idx, muse, wuse);
      variation[62]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba - (ff * sstep), sqm12,                idx, muse, wuse);
      variation[63]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba,                sqm12 + (ff * mstep), idx, muse, wuse);
      variation[64]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba,                sqm12 - (ff * mstep), idx, muse, wuse);
      variation[65]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba,                sqm12 + (ff * mstep), idx, muse, wuse);
      variation[66]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba,                sqm12 - (ff * mstep), idx, muse, wuse);
      variation[67]  = distance_to_target(sm, model, mA, mH, mC, tb,                sba + (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[68]  = distance_to_target(sm, model, mA, mH, mC, tb,                sba + (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);
      variation[69]  = distance_to_target(sm, model, mA, mH, mC, tb,                sba - (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[70]  = distance_to_target(sm, model, mA, mH, mC, tb,                sba - (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);

      variation[71]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba + (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[72]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba + (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);
      variation[73]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba - (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[74]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba - (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);
      variation[75]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba + (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[76]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba - (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[77]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba + (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);
      variation[78]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba - (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);

      ff = 1. / ffu[0];
      variation[79]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba,                sqm12,                idx, muse, wuse);
      variation[80]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba,                sqm12,                idx, muse, wuse);
      variation[81]  = distance_to_target(sm, model, mA, mH, mC, tb,                sba + (ff * sstep), sqm12,                idx, muse, wuse);
      variation[82]  = distance_to_target(sm, model, mA, mH, mC, tb,                sba - (ff * sstep), sqm12,                idx, muse, wuse);
      variation[83]  = distance_to_target(sm, model, mA, mH, mC, tb,                sba,                sqm12 + (ff * mstep), idx, muse, wuse);
      variation[84]  = distance_to_target(sm, model, mA, mH, mC, tb,                sba,                sqm12 - (ff * mstep), idx, muse, wuse);

      variation[85]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba + (ff * sstep), sqm12,                idx, muse, wuse);
      variation[86]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba - (ff * sstep), sqm12,                idx, muse, wuse);
      variation[87]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba + (ff * sstep), sqm12,                idx, muse, wuse);
      variation[88]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba - (ff * sstep), sqm12,                idx, muse, wuse);
      variation[89]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba,                sqm12 + (ff * mstep), idx, muse, wuse);
      variation[90]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba,                sqm12 - (ff * mstep), idx, muse, wuse);
      variation[91]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba,                sqm12 + (ff * mstep), idx, muse, wuse);
      variation[92]  = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba,                sqm12 - (ff * mstep), idx, muse, wuse);
      variation[93]  = distance_to_target(sm, model, mA, mH, mC, tb,                sba + (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[94]  = distance_to_target(sm, model, mA, mH, mC, tb,                sba + (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);
      variation[95]  = distance_to_target(sm, model, mA, mH, mC, tb,                sba - (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[96]  = distance_to_target(sm, model, mA, mH, mC, tb,                sba - (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);

      variation[97]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba + (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[98]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba + (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);
      variation[99]  = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba - (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[100] = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba - (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);
      variation[101] = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba + (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[102] = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba - (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[103] = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba + (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);
      variation[104] = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba - (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);

      ff = 1. / ffu[1];
      variation[105] = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba,                sqm12,                idx, muse, wuse);
      variation[106] = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba,                sqm12,                idx, muse, wuse);
      variation[107] = distance_to_target(sm, model, mA, mH, mC, tb,                sba + (ff * sstep), sqm12,                idx, muse, wuse);
      variation[108] = distance_to_target(sm, model, mA, mH, mC, tb,                sba - (ff * sstep), sqm12,                idx, muse, wuse);
      variation[109] = distance_to_target(sm, model, mA, mH, mC, tb,                sba,                sqm12 + (ff * mstep), idx, muse, wuse);
      variation[110] = distance_to_target(sm, model, mA, mH, mC, tb,                sba,                sqm12 - (ff * mstep), idx, muse, wuse);

      variation[111] = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba + (ff * sstep), sqm12,                idx, muse, wuse);
      variation[112] = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba - (ff * sstep), sqm12,                idx, muse, wuse);
      variation[113] = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba + (ff * sstep), sqm12,                idx, muse, wuse);
      variation[114] = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba - (ff * sstep), sqm12,                idx, muse, wuse);
      variation[115] = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba,                sqm12 + (ff * mstep), idx, muse, wuse);
      variation[116] = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba,                sqm12 - (ff * mstep), idx, muse, wuse);
      variation[117] = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba,                sqm12 + (ff * mstep), idx, muse, wuse);
      variation[118] = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba,                sqm12 - (ff * mstep), idx, muse, wuse);
      variation[119] = distance_to_target(sm, model, mA, mH, mC, tb,                sba + (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[120] = distance_to_target(sm, model, mA, mH, mC, tb,                sba + (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);
      variation[121] = distance_to_target(sm, model, mA, mH, mC, tb,                sba - (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[122] = distance_to_target(sm, model, mA, mH, mC, tb,                sba - (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);

      variation[123] = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba + (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[124] = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba + (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);
      variation[125] = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba - (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[126] = distance_to_target(sm, model, mA, mH, mC, tb + (ff * tstep), sba - (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);
      variation[127] = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba + (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[128] = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba - (ff * sstep), sqm12 + (ff * mstep), idx, muse, wuse);
      variation[129] = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba + (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);
      variation[130] = distance_to_target(sm, model, mA, mH, mC, tb - (ff * tstep), sba - (ff * sstep), sqm12 - (ff * mstep), idx, muse, wuse);
    }

    auto mdist = std::min_element(std::begin(variation), std::end(variation));
    auto mpos = std::distance(std::begin(variation), mdist);
    if (*mdist < min_distance)
      min_distance = *mdist;

    if (mpos > 104) {
      ff = 1. / ffu[1];
      mpos -= 104;
    }
    else if (mpos > 78) {
      ff = 1. / ffu[0];
      mpos -= 78;
    }
    else if (mpos > 52) {
      ff = ffu[1];
      mpos -= 52;
    }
    else if (mpos > 26) {
      ff = ffu[0];
      mpos -= 26;
    }
    else 
      ff = 1.;

    if (mpos == 0) {
      if (dtmp < 1e-6) {
        std::cerr << "No more improvement detected after " << iter << " iterations. Aborting!!" << std::endl;
        break;
      }

      tstep *= dtmp;
      sstep *= dtmp;
      mstep *= dtmp;
      dtmp *= dtmp;
    }
    else if (mpos == 1)
      tb += (ff * tstep);
    else if (mpos == 2)
      tb -= (ff * tstep);
    else if (mpos == 3)
      sba += (ff * sstep);
    else if (mpos == 4)
      sba -= (ff * sstep);
    else if (mpos == 5)
      sqm12 += (ff * mstep);
    else if (mpos == 6)
      sqm12 -= (ff * mstep);
    else if (mpos == 7) {
      tb += (ff * tstep);
      sba += (ff * sstep);
    }
    else if (mpos == 8) {
      tb += (ff * tstep);
      sba -= (ff * sstep);
    }
    else if (mpos == 9) {
      tb -= (ff * tstep);
      sba += (ff * sstep);
    }
    else if (mpos == 10) {
      tb -= (ff * tstep);
      sba -= (ff * sstep);
    }
    else if (mpos == 11) {
      tb += (ff * tstep);
      sqm12 += (ff * mstep);
    }
    else if (mpos == 12) {
      tb += (ff * tstep);
      sqm12 -= (ff * mstep);
    }
    else if (mpos == 13) {
      tb -= (ff * tstep);
      sqm12 += (ff * mstep);
    }
    else if (mpos == 14) {
      tb -= (ff * tstep);
      sqm12 -= (ff * mstep);
    }
    else if (mpos == 15) {
      sba += (ff * sstep);
      sqm12 += (ff * mstep);
    }
    else if (mpos == 16) {
      sba += (ff * sstep);
      sqm12 -= (ff * mstep);
    }
    else if (mpos == 17) {
      sba -= (ff * sstep);
      sqm12 += (ff * mstep);
    }
    else if (mpos == 18) {
      sba -= (ff * sstep);
      sqm12 -= (ff * mstep);
    }
    else if (mpos == 19) {
      tb += (ff * tstep);
      sba += (ff * sstep);
      sqm12 += (ff * mstep);
    }
    else if (mpos == 20) {
      tb += (ff * tstep);
      sba += (ff * sstep);
      sqm12 -= (ff * mstep);
    }
    else if (mpos == 21) {
      tb += (ff * tstep);
      sba -= (ff * sstep);
      sqm12 += (ff * mstep);
    }
    else if (mpos == 22) {
      tb += (ff * tstep);
      sba -= (ff * sstep);
      sqm12 -= (ff * mstep);
    }
    else if (mpos == 23) {
      tb -= (ff * tstep);
      sba += (ff * sstep);
      sqm12 += (ff * mstep);
    }
    else if (mpos == 24) {
      tb -= (ff * tstep);
      sba -= (ff * sstep);
      sqm12 += (ff * mstep);
    }
    else if (mpos == 25) {
      tb -= (ff * tstep);
      sba += (ff * sstep);
      sqm12 -= (ff * mstep);
    }
    else if (mpos == 26) {
      tb -= (ff * tstep);
      sba -= (ff * sstep);
      sqm12 -= (ff * mstep);
    }

    model.set_param_phys(mh, mH, mA, mC, sba, /*lam6*/ 0., /*lam7*/ 0., sqm12, tb);
    model.set_yukawas_type(2);
    DecayTable table(model);
    wtmp = table.get_gammatot_h(idx) / muse;
    std::cout << std::defaultfloat << "iteration " << ++iter << ": " << puse << muse 
              << ", width " << std::fixed << std::setprecision(6) << wtmp
              << ", distance " << std::fixed << std::setprecision(6) << min_distance
              //<< ", distance2 " << std::fixed << std::setprecision(6) << 1000. * std::abs(wtmp - wuse)
              << ", mA " << std::defaultfloat << mA
              << ", mH " << std::defaultfloat << mH
              << ", mC " << std::defaultfloat << mC
              << ", tanb " << std::fixed << std::setprecision(6) << tb
              << ", sba " << std::fixed << std::setprecision(6) << sba
              << ", sqm12 " << std::fixed << std::setprecision(6) << sqm12;

    if (sp) {
      if (rl > 1. and std::abs(wtmp - wuse) < weps)
        std::cout << " [singlepoint] >>> within search epsilon!!! <<<\n";
      else if (std::abs(wtmp - wuse) < rl * weps)
        std::cout << std::defaultfloat << " [singlepoint] >>> within " << rl << " epsilon!!! <<<\n";
      else
        std::cout << "\n";
      break;
    }
    else 
      std::cout << "\n";
  }

  std::cout << "\nChecking 2HDM model constaints:\n";

  Constraints constr(model);
  const bool stable = constr.check_stability();
  const bool unitary = constr.check_unitarity();
  const bool perturbative = constr.check_perturbativity();

  if (!(stable and unitary and perturbative)) {
    if (!stable)
      std::cout << "Model is unstable.\n";
    if (!unitary)
      std::cout << "Model is not unitary.\n";
    if (!perturbative)
      std::cout << "Model is not perturbative.\n";

    if (!sc) {
      std::cout << "Aborting!" << std::endl;
      return -1;
    }
    else
      std::cout << ">>> Ignoring stability, unitarity and perturbativity checks!!!\n\n";
  }
  else
    std::cout << "Stability, unitarity and perturbativity constraints are all satisfied!\n\n";

  std::cout << "Printing model parameters:\n";
  model.print_param_phys();
  model.print_param_gen();
  model.print_param_hybrid();

  std::cout << "\nPrinting decays of all Higgses in this model\n";
  DecayTable table(model);
  table.print_decays(1);
  std::cout << "h mass: " << model.get_hmass(1) << " relative width " << table.get_gammatot_h(1) / model.get_hmass(1) << "\n";

  table.print_decays(idx);
  std::cout << puse << " mass: " << model.get_hmass(idx) << " relative width " << table.get_gammatot_h(idx) / model.get_hmass(idx) << "\n";

  /*
  table.print_decays(3);
  std::cout << "A mass: " << model.get_hmass(3) << " relative width " << table.get_gammatot_h(3) / model.get_hmass(3) << "\n";

  table.print_decays(2);
  std::cout << "H mass: " << model.get_hmass(2) << " relative width " << table.get_gammatot_h(2) / model.get_hmass(2) << "\n";

  table.print_decays(4);
  std::cout << "H+ mass: " << model.get_hmass(4) << " relative width " << table.get_gammatot_h(4) / model.get_hmass(4) << "\n";
  */
}
