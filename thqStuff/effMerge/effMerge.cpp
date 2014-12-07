/*** effMerge.cpp
- Take the 2D efficiencies in all processes and bins (of 2012Bravo files) and combine in a single file
- ROOT macro
- "AAAAAAAAAAAAAaaaaaaaaaaaaAAAAAAAAAAAAAAAA..."
- Afiq A. Anuar
***/

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

void effMerge() {

 string inDir, outDir;

 // input and output directory (updates itself with conf above)
 inDir = "/home/ieeya/Downloads/tHq/Part2_BTagEff/root_files/2012Bravo_eff/hists";
 //outDir = "/home/ieeya/Downloads/Part2_BTagEff/root_files/2012Bravo_eff/";
 outDir = "/home/ieeya/Downloads/";

 // Inclusive-4 files
 TFile *f_tHq_nc_in4 = new TFile((inDir + "_in4/tHq-nc.root").c_str());
 TFile *f_tHq_sm_in4 = new TFile((inDir + "_in4/tHq-sm.root").c_str());
 TFile *f_ttH_in4 = new TFile((inDir + "_in4/ttH.root").c_str());
 TFile *f_ttbar_semilep_in4 = new TFile((inDir + "_in4/ttbar-semilep.root").c_str());
 TFile *f_ttbar_dilep_in4 = new TFile((inDir + "_in4/ttbar-dilep.root").c_str());
 TFile *f_ttbar_inc_in4 = new TFile((inDir + "_in4/ttbar-inc.root").c_str());
 TFile *f_t_schan_in4 = new TFile((inDir + "_in4/t-schan.root").c_str());
 TFile *f_t_tchan_in4 = new TFile((inDir + "_in4/t-tchan.root").c_str());
 TFile *f_t_tWchan_in4 = new TFile((inDir + "_in4/t-tWchan.root").c_str());
 TFile *f_Wjets_in4 = new TFile((inDir + "_in4/Wjets.root").c_str());

 // Exclusive-4 files
 TFile *f_tHq_nc_ex4 = new TFile((inDir + "_ex4/tHq-nc.root").c_str());
 TFile *f_tHq_sm_ex4 = new TFile((inDir + "_ex4/tHq-sm.root").c_str());
 TFile *f_ttH_ex4 = new TFile((inDir + "_ex4/ttH.root").c_str());
 TFile *f_ttbar_semilep_ex4 = new TFile((inDir + "_ex4/ttbar-semilep.root").c_str());
 TFile *f_ttbar_dilep_ex4 = new TFile((inDir + "_ex4/ttbar-dilep.root").c_str());
 TFile *f_ttbar_inc_ex4 = new TFile((inDir + "_ex4/ttbar-inc.root").c_str());
 TFile *f_t_schan_ex4 = new TFile((inDir + "_ex4/t-schan.root").c_str());
 TFile *f_t_tchan_ex4 = new TFile((inDir + "_ex4/t-tchan.root").c_str());
 TFile *f_t_tWchan_ex4 = new TFile((inDir + "_ex4/t-tWchan.root").c_str());
 TFile *f_Wjets_ex4 = new TFile((inDir + "_ex4/Wjets.root").c_str());

 // Exclusive-5 files
 TFile *f_tHq_nc_ex5 = new TFile((inDir + "_ex5/tHq-nc.root").c_str());
 TFile *f_tHq_sm_ex5 = new TFile((inDir + "_ex5/tHq-sm.root").c_str());
 TFile *f_ttH_ex5 = new TFile((inDir + "_ex5/ttH.root").c_str());
 TFile *f_ttbar_semilep_ex5 = new TFile((inDir + "_ex5/ttbar-semilep.root").c_str());
 TFile *f_ttbar_dilep_ex5 = new TFile((inDir + "_ex5/ttbar-dilep.root").c_str());
 TFile *f_ttbar_inc_ex5 = new TFile((inDir + "_ex5/ttbar-inc.root").c_str());
 TFile *f_t_schan_ex5 = new TFile((inDir + "_ex5/t-schan.root").c_str());
 TFile *f_t_tchan_ex5 = new TFile((inDir + "_ex5/t-tchan.root").c_str());
 TFile *f_t_tWchan_ex5 = new TFile((inDir + "_ex5/t-tWchan.root").c_str());
 TFile *f_Wjets_ex5 = new TFile((inDir + "_ex5/Wjets.root").c_str());

 // Exclusive-6 files
 TFile *f_tHq_nc_ex6 = new TFile((inDir + "_ex6/tHq-nc.root").c_str());
 TFile *f_tHq_sm_ex6 = new TFile((inDir + "_ex6/tHq-sm.root").c_str());
 TFile *f_ttH_ex6 = new TFile((inDir + "_ex6/ttH.root").c_str());
 TFile *f_ttbar_semilep_ex6 = new TFile((inDir + "_ex6/ttbar-semilep.root").c_str());
 TFile *f_ttbar_dilep_ex6 = new TFile((inDir + "_ex6/ttbar-dilep.root").c_str());
 TFile *f_ttbar_inc_ex6 = new TFile((inDir + "_ex6/ttbar-inc.root").c_str());
 TFile *f_t_schan_ex6 = new TFile((inDir + "_ex6/t-schan.root").c_str());
 TFile *f_t_tchan_ex6 = new TFile((inDir + "_ex6/t-tchan.root").c_str());
 TFile *f_t_tWchan_ex6 = new TFile((inDir + "_ex6/t-tWchan.root").c_str());
 TFile *f_Wjets_ex6 = new TFile((inDir + "_ex6/Wjets.root").c_str());

 // Output file
 TFile *f_out = new TFile((outDir + "2012Bravo_eff.root").c_str(), "recreate");

 // Get the historams (AAAAaaaaa...)
 // in4
 TH2D *in4_tHq_nc_b_T = dynamic_cast<TH2D *>(f_tHq_nc_in4->Get("PtEta_Eff_b_T"));
 TH2D *in4_tHq_nc_c_T = dynamic_cast<TH2D *>(f_tHq_nc_in4->Get("PtEta_Eff_c_T"));
 TH2D *in4_tHq_nc_uds_T = dynamic_cast<TH2D *>(f_tHq_nc_in4->Get("PtEta_Eff_uds_T"));
 TH2D *in4_tHq_nc_g_T = dynamic_cast<TH2D *>(f_tHq_nc_in4->Get("PtEta_Eff_g_T"));

 TH2D *in4_tHq_sm_b_T = dynamic_cast<TH2D *>(f_tHq_sm_in4->Get("PtEta_Eff_b_T"));
 TH2D *in4_tHq_sm_c_T = dynamic_cast<TH2D *>(f_tHq_sm_in4->Get("PtEta_Eff_c_T"));
 TH2D *in4_tHq_sm_uds_T = dynamic_cast<TH2D *>(f_tHq_sm_in4->Get("PtEta_Eff_uds_T"));
 TH2D *in4_tHq_sm_g_T = dynamic_cast<TH2D *>(f_tHq_sm_in4->Get("PtEta_Eff_g_T"));

 TH2D *in4_ttH_b_T = dynamic_cast<TH2D *>(f_ttH_in4->Get("PtEta_Eff_b_T"));
 TH2D *in4_ttH_c_T = dynamic_cast<TH2D *>(f_ttH_in4->Get("PtEta_Eff_c_T"));
 TH2D *in4_ttH_uds_T = dynamic_cast<TH2D *>(f_ttH_in4->Get("PtEta_Eff_uds_T"));
 TH2D *in4_ttH_g_T = dynamic_cast<TH2D *>(f_ttH_in4->Get("PtEta_Eff_g_T"));

 TH2D *in4_ttbar_semilep_b_T = dynamic_cast<TH2D *>(f_ttbar_semilep_in4->Get("PtEta_Eff_b_T"));
 TH2D *in4_ttbar_semilep_c_T = dynamic_cast<TH2D *>(f_ttbar_semilep_in4->Get("PtEta_Eff_c_T"));
 TH2D *in4_ttbar_semilep_uds_T = dynamic_cast<TH2D *>(f_ttbar_semilep_in4->Get("PtEta_Eff_uds_T"));
 TH2D *in4_ttbar_semilep_g_T = dynamic_cast<TH2D *>(f_ttbar_semilep_in4->Get("PtEta_Eff_g_T"));

 TH2D *in4_ttbar_dilep_b_T = dynamic_cast<TH2D *>(f_ttbar_dilep_in4->Get("PtEta_Eff_b_T"));
 TH2D *in4_ttbar_dilep_c_T = dynamic_cast<TH2D *>(f_ttbar_dilep_in4->Get("PtEta_Eff_c_T"));
 TH2D *in4_ttbar_dilep_uds_T = dynamic_cast<TH2D *>(f_ttbar_dilep_in4->Get("PtEta_Eff_uds_T"));
 TH2D *in4_ttbar_dilep_g_T = dynamic_cast<TH2D *>(f_ttbar_dilep_in4->Get("PtEta_Eff_g_T"));

 TH2D *in4_ttbar_inc_b_T = dynamic_cast<TH2D *>(f_ttbar_inc_in4->Get("PtEta_Eff_b_T"));
 TH2D *in4_ttbar_inc_c_T = dynamic_cast<TH2D *>(f_ttbar_inc_in4->Get("PtEta_Eff_c_T"));
 TH2D *in4_ttbar_inc_uds_T = dynamic_cast<TH2D *>(f_ttbar_inc_in4->Get("PtEta_Eff_uds_T"));
 TH2D *in4_ttbar_inc_g_T = dynamic_cast<TH2D *>(f_ttbar_inc_in4->Get("PtEta_Eff_g_T"));

 TH2D *in4_t_schan_b_T = dynamic_cast<TH2D *>(f_t_schan_in4->Get("PtEta_Eff_b_T"));
 TH2D *in4_t_schan_c_T = dynamic_cast<TH2D *>(f_t_schan_in4->Get("PtEta_Eff_c_T"));
 TH2D *in4_t_schan_uds_T = dynamic_cast<TH2D *>(f_t_schan_in4->Get("PtEta_Eff_uds_T"));
 TH2D *in4_t_schan_g_T = dynamic_cast<TH2D *>(f_t_schan_in4->Get("PtEta_Eff_g_T"));

 TH2D *in4_t_tchan_b_T = dynamic_cast<TH2D *>(f_t_tchan_in4->Get("PtEta_Eff_b_T"));
 TH2D *in4_t_tchan_c_T = dynamic_cast<TH2D *>(f_t_tchan_in4->Get("PtEta_Eff_c_T"));
 TH2D *in4_t_tchan_uds_T = dynamic_cast<TH2D *>(f_t_tchan_in4->Get("PtEta_Eff_uds_T"));
 TH2D *in4_t_tchan_g_T = dynamic_cast<TH2D *>(f_t_tchan_in4->Get("PtEta_Eff_g_T"));

 TH2D *in4_t_tWchan_b_T = dynamic_cast<TH2D *>(f_t_tWchan_in4->Get("PtEta_Eff_b_T"));
 TH2D *in4_t_tWchan_c_T = dynamic_cast<TH2D *>(f_t_tWchan_in4->Get("PtEta_Eff_c_T"));
 TH2D *in4_t_tWchan_uds_T = dynamic_cast<TH2D *>(f_t_tWchan_in4->Get("PtEta_Eff_uds_T"));
 TH2D *in4_t_tWchan_g_T = dynamic_cast<TH2D *>(f_t_tWchan_in4->Get("PtEta_Eff_g_T"));

 TH2D *in4_Wjets_b_T = dynamic_cast<TH2D *>(f_Wjets_in4->Get("PtEta_Eff_b_T"));
 TH2D *in4_Wjets_c_T = dynamic_cast<TH2D *>(f_Wjets_in4->Get("PtEta_Eff_c_T"));
 TH2D *in4_Wjets_uds_T = dynamic_cast<TH2D *>(f_Wjets_in4->Get("PtEta_Eff_uds_T"));
 TH2D *in4_Wjets_g_T = dynamic_cast<TH2D *>(f_Wjets_in4->Get("PtEta_Eff_g_T"));

 // ex4
 TH2D *ex4_tHq_nc_b_T = dynamic_cast<TH2D *>(f_tHq_nc_ex4->Get("PtEta_Eff_b_T"));
 TH2D *ex4_tHq_nc_c_T = dynamic_cast<TH2D *>(f_tHq_nc_ex4->Get("PtEta_Eff_c_T"));
 TH2D *ex4_tHq_nc_uds_T = dynamic_cast<TH2D *>(f_tHq_nc_ex4->Get("PtEta_Eff_uds_T"));
 TH2D *ex4_tHq_nc_g_T = dynamic_cast<TH2D *>(f_tHq_nc_ex4->Get("PtEta_Eff_g_T"));

 TH2D *ex4_tHq_sm_b_T = dynamic_cast<TH2D *>(f_tHq_sm_ex4->Get("PtEta_Eff_b_T"));
 TH2D *ex4_tHq_sm_c_T = dynamic_cast<TH2D *>(f_tHq_sm_ex4->Get("PtEta_Eff_c_T"));
 TH2D *ex4_tHq_sm_uds_T = dynamic_cast<TH2D *>(f_tHq_sm_ex4->Get("PtEta_Eff_uds_T"));
 TH2D *ex4_tHq_sm_g_T = dynamic_cast<TH2D *>(f_tHq_sm_ex4->Get("PtEta_Eff_g_T"));

 TH2D *ex4_ttH_b_T = dynamic_cast<TH2D *>(f_ttH_ex4->Get("PtEta_Eff_b_T"));
 TH2D *ex4_ttH_c_T = dynamic_cast<TH2D *>(f_ttH_ex4->Get("PtEta_Eff_c_T"));
 TH2D *ex4_ttH_uds_T = dynamic_cast<TH2D *>(f_ttH_ex4->Get("PtEta_Eff_uds_T"));
 TH2D *ex4_ttH_g_T = dynamic_cast<TH2D *>(f_ttH_ex4->Get("PtEta_Eff_g_T"));

 TH2D *ex4_ttbar_semilep_b_T = dynamic_cast<TH2D *>(f_ttbar_semilep_ex4->Get("PtEta_Eff_b_T"));
 TH2D *ex4_ttbar_semilep_c_T = dynamic_cast<TH2D *>(f_ttbar_semilep_ex4->Get("PtEta_Eff_c_T"));
 TH2D *ex4_ttbar_semilep_uds_T = dynamic_cast<TH2D *>(f_ttbar_semilep_ex4->Get("PtEta_Eff_uds_T"));
 TH2D *ex4_ttbar_semilep_g_T = dynamic_cast<TH2D *>(f_ttbar_semilep_ex4->Get("PtEta_Eff_g_T"));

 TH2D *ex4_ttbar_dilep_b_T = dynamic_cast<TH2D *>(f_ttbar_dilep_ex4->Get("PtEta_Eff_b_T"));
 TH2D *ex4_ttbar_dilep_c_T = dynamic_cast<TH2D *>(f_ttbar_dilep_ex4->Get("PtEta_Eff_c_T"));
 TH2D *ex4_ttbar_dilep_uds_T = dynamic_cast<TH2D *>(f_ttbar_dilep_ex4->Get("PtEta_Eff_uds_T"));
 TH2D *ex4_ttbar_dilep_g_T = dynamic_cast<TH2D *>(f_ttbar_dilep_ex4->Get("PtEta_Eff_g_T"));

 TH2D *ex4_ttbar_inc_b_T = dynamic_cast<TH2D *>(f_ttbar_inc_ex4->Get("PtEta_Eff_b_T"));
 TH2D *ex4_ttbar_inc_c_T = dynamic_cast<TH2D *>(f_ttbar_inc_ex4->Get("PtEta_Eff_c_T"));
 TH2D *ex4_ttbar_inc_uds_T = dynamic_cast<TH2D *>(f_ttbar_inc_ex4->Get("PtEta_Eff_uds_T"));
 TH2D *ex4_ttbar_inc_g_T = dynamic_cast<TH2D *>(f_ttbar_inc_ex4->Get("PtEta_Eff_g_T"));

 TH2D *ex4_t_schan_b_T = dynamic_cast<TH2D *>(f_t_schan_ex4->Get("PtEta_Eff_b_T"));
 TH2D *ex4_t_schan_c_T = dynamic_cast<TH2D *>(f_t_schan_ex4->Get("PtEta_Eff_c_T"));
 TH2D *ex4_t_schan_uds_T = dynamic_cast<TH2D *>(f_t_schan_ex4->Get("PtEta_Eff_uds_T"));
 TH2D *ex4_t_schan_g_T = dynamic_cast<TH2D *>(f_t_schan_ex4->Get("PtEta_Eff_g_T"));

 TH2D *ex4_t_tchan_b_T = dynamic_cast<TH2D *>(f_t_tchan_ex4->Get("PtEta_Eff_b_T"));
 TH2D *ex4_t_tchan_c_T = dynamic_cast<TH2D *>(f_t_tchan_ex4->Get("PtEta_Eff_c_T"));
 TH2D *ex4_t_tchan_uds_T = dynamic_cast<TH2D *>(f_t_tchan_ex4->Get("PtEta_Eff_uds_T"));
 TH2D *ex4_t_tchan_g_T = dynamic_cast<TH2D *>(f_t_tchan_ex4->Get("PtEta_Eff_g_T"));

 TH2D *ex4_t_tWchan_b_T = dynamic_cast<TH2D *>(f_t_tWchan_ex4->Get("PtEta_Eff_b_T"));
 TH2D *ex4_t_tWchan_c_T = dynamic_cast<TH2D *>(f_t_tWchan_ex4->Get("PtEta_Eff_c_T"));
 TH2D *ex4_t_tWchan_uds_T = dynamic_cast<TH2D *>(f_t_tWchan_ex4->Get("PtEta_Eff_uds_T"));
 TH2D *ex4_t_tWchan_g_T = dynamic_cast<TH2D *>(f_t_tWchan_ex4->Get("PtEta_Eff_g_T"));

 TH2D *ex4_Wjets_b_T = dynamic_cast<TH2D *>(f_Wjets_ex4->Get("PtEta_Eff_b_T"));
 TH2D *ex4_Wjets_c_T = dynamic_cast<TH2D *>(f_Wjets_ex4->Get("PtEta_Eff_c_T"));
 TH2D *ex4_Wjets_uds_T = dynamic_cast<TH2D *>(f_Wjets_ex4->Get("PtEta_Eff_uds_T"));
 TH2D *ex4_Wjets_g_T = dynamic_cast<TH2D *>(f_Wjets_ex4->Get("PtEta_Eff_g_T"));

 // ex5
 TH2D *ex5_tHq_nc_b_T = dynamic_cast<TH2D *>(f_tHq_nc_ex5->Get("PtEta_Eff_b_T"));
 TH2D *ex5_tHq_nc_c_T = dynamic_cast<TH2D *>(f_tHq_nc_ex5->Get("PtEta_Eff_c_T"));
 TH2D *ex5_tHq_nc_uds_T = dynamic_cast<TH2D *>(f_tHq_nc_ex5->Get("PtEta_Eff_uds_T"));
 TH2D *ex5_tHq_nc_g_T = dynamic_cast<TH2D *>(f_tHq_nc_ex5->Get("PtEta_Eff_g_T"));

 TH2D *ex5_tHq_sm_b_T = dynamic_cast<TH2D *>(f_tHq_sm_ex5->Get("PtEta_Eff_b_T"));
 TH2D *ex5_tHq_sm_c_T = dynamic_cast<TH2D *>(f_tHq_sm_ex5->Get("PtEta_Eff_c_T"));
 TH2D *ex5_tHq_sm_uds_T = dynamic_cast<TH2D *>(f_tHq_sm_ex5->Get("PtEta_Eff_uds_T"));
 TH2D *ex5_tHq_sm_g_T = dynamic_cast<TH2D *>(f_tHq_sm_ex5->Get("PtEta_Eff_g_T"));

 TH2D *ex5_ttH_b_T = dynamic_cast<TH2D *>(f_ttH_ex5->Get("PtEta_Eff_b_T"));
 TH2D *ex5_ttH_c_T = dynamic_cast<TH2D *>(f_ttH_ex5->Get("PtEta_Eff_c_T"));
 TH2D *ex5_ttH_uds_T = dynamic_cast<TH2D *>(f_ttH_ex5->Get("PtEta_Eff_uds_T"));
 TH2D *ex5_ttH_g_T = dynamic_cast<TH2D *>(f_ttH_ex5->Get("PtEta_Eff_g_T"));

 TH2D *ex5_ttbar_semilep_b_T = dynamic_cast<TH2D *>(f_ttbar_semilep_ex5->Get("PtEta_Eff_b_T"));
 TH2D *ex5_ttbar_semilep_c_T = dynamic_cast<TH2D *>(f_ttbar_semilep_ex5->Get("PtEta_Eff_c_T"));
 TH2D *ex5_ttbar_semilep_uds_T = dynamic_cast<TH2D *>(f_ttbar_semilep_ex5->Get("PtEta_Eff_uds_T"));
 TH2D *ex5_ttbar_semilep_g_T = dynamic_cast<TH2D *>(f_ttbar_semilep_ex5->Get("PtEta_Eff_g_T"));

 TH2D *ex5_ttbar_dilep_b_T = dynamic_cast<TH2D *>(f_ttbar_dilep_ex5->Get("PtEta_Eff_b_T"));
 TH2D *ex5_ttbar_dilep_c_T = dynamic_cast<TH2D *>(f_ttbar_dilep_ex5->Get("PtEta_Eff_c_T"));
 TH2D *ex5_ttbar_dilep_uds_T = dynamic_cast<TH2D *>(f_ttbar_dilep_ex5->Get("PtEta_Eff_uds_T"));
 TH2D *ex5_ttbar_dilep_g_T = dynamic_cast<TH2D *>(f_ttbar_dilep_ex5->Get("PtEta_Eff_g_T"));

 TH2D *ex5_ttbar_inc_b_T = dynamic_cast<TH2D *>(f_ttbar_inc_ex5->Get("PtEta_Eff_b_T"));
 TH2D *ex5_ttbar_inc_c_T = dynamic_cast<TH2D *>(f_ttbar_inc_ex5->Get("PtEta_Eff_c_T"));
 TH2D *ex5_ttbar_inc_uds_T = dynamic_cast<TH2D *>(f_ttbar_inc_ex5->Get("PtEta_Eff_uds_T"));
 TH2D *ex5_ttbar_inc_g_T = dynamic_cast<TH2D *>(f_ttbar_inc_ex5->Get("PtEta_Eff_g_T"));

 TH2D *ex5_t_schan_b_T = dynamic_cast<TH2D *>(f_t_schan_ex5->Get("PtEta_Eff_b_T"));
 TH2D *ex5_t_schan_c_T = dynamic_cast<TH2D *>(f_t_schan_ex5->Get("PtEta_Eff_c_T"));
 TH2D *ex5_t_schan_uds_T = dynamic_cast<TH2D *>(f_t_schan_ex5->Get("PtEta_Eff_uds_T"));
 TH2D *ex5_t_schan_g_T = dynamic_cast<TH2D *>(f_t_schan_ex5->Get("PtEta_Eff_g_T"));

 TH2D *ex5_t_tchan_b_T = dynamic_cast<TH2D *>(f_t_tchan_ex5->Get("PtEta_Eff_b_T"));
 TH2D *ex5_t_tchan_c_T = dynamic_cast<TH2D *>(f_t_tchan_ex5->Get("PtEta_Eff_c_T"));
 TH2D *ex5_t_tchan_uds_T = dynamic_cast<TH2D *>(f_t_tchan_ex5->Get("PtEta_Eff_uds_T"));
 TH2D *ex5_t_tchan_g_T = dynamic_cast<TH2D *>(f_t_tchan_ex5->Get("PtEta_Eff_g_T"));

 TH2D *ex5_t_tWchan_b_T = dynamic_cast<TH2D *>(f_t_tWchan_ex5->Get("PtEta_Eff_b_T"));
 TH2D *ex5_t_tWchan_c_T = dynamic_cast<TH2D *>(f_t_tWchan_ex5->Get("PtEta_Eff_c_T"));
 TH2D *ex5_t_tWchan_uds_T = dynamic_cast<TH2D *>(f_t_tWchan_ex5->Get("PtEta_Eff_uds_T"));
 TH2D *ex5_t_tWchan_g_T = dynamic_cast<TH2D *>(f_t_tWchan_ex5->Get("PtEta_Eff_g_T"));

 TH2D *ex5_Wjets_b_T = dynamic_cast<TH2D *>(f_Wjets_ex5->Get("PtEta_Eff_b_T"));
 TH2D *ex5_Wjets_c_T = dynamic_cast<TH2D *>(f_Wjets_ex5->Get("PtEta_Eff_c_T"));
 TH2D *ex5_Wjets_uds_T = dynamic_cast<TH2D *>(f_Wjets_ex5->Get("PtEta_Eff_uds_T"));
 TH2D *ex5_Wjets_g_T = dynamic_cast<TH2D *>(f_Wjets_ex5->Get("PtEta_Eff_g_T"));

 // ex6
 TH2D *ex6_tHq_nc_b_T = dynamic_cast<TH2D *>(f_tHq_nc_ex6->Get("PtEta_Eff_b_T"));
 TH2D *ex6_tHq_nc_c_T = dynamic_cast<TH2D *>(f_tHq_nc_ex6->Get("PtEta_Eff_c_T"));
 TH2D *ex6_tHq_nc_uds_T = dynamic_cast<TH2D *>(f_tHq_nc_ex6->Get("PtEta_Eff_uds_T"));
 TH2D *ex6_tHq_nc_g_T = dynamic_cast<TH2D *>(f_tHq_nc_ex6->Get("PtEta_Eff_g_T"));

 TH2D *ex6_tHq_sm_b_T = dynamic_cast<TH2D *>(f_tHq_sm_ex6->Get("PtEta_Eff_b_T"));
 TH2D *ex6_tHq_sm_c_T = dynamic_cast<TH2D *>(f_tHq_sm_ex6->Get("PtEta_Eff_c_T"));
 TH2D *ex6_tHq_sm_uds_T = dynamic_cast<TH2D *>(f_tHq_sm_ex6->Get("PtEta_Eff_uds_T"));
 TH2D *ex6_tHq_sm_g_T = dynamic_cast<TH2D *>(f_tHq_sm_ex6->Get("PtEta_Eff_g_T"));

 TH2D *ex6_ttH_b_T = dynamic_cast<TH2D *>(f_ttH_ex6->Get("PtEta_Eff_b_T"));
 TH2D *ex6_ttH_c_T = dynamic_cast<TH2D *>(f_ttH_ex6->Get("PtEta_Eff_c_T"));
 TH2D *ex6_ttH_uds_T = dynamic_cast<TH2D *>(f_ttH_ex6->Get("PtEta_Eff_uds_T"));
 TH2D *ex6_ttH_g_T = dynamic_cast<TH2D *>(f_ttH_ex6->Get("PtEta_Eff_g_T"));

 TH2D *ex6_ttbar_semilep_b_T = dynamic_cast<TH2D *>(f_ttbar_semilep_ex6->Get("PtEta_Eff_b_T"));
 TH2D *ex6_ttbar_semilep_c_T = dynamic_cast<TH2D *>(f_ttbar_semilep_ex6->Get("PtEta_Eff_c_T"));
 TH2D *ex6_ttbar_semilep_uds_T = dynamic_cast<TH2D *>(f_ttbar_semilep_ex6->Get("PtEta_Eff_uds_T"));
 TH2D *ex6_ttbar_semilep_g_T = dynamic_cast<TH2D *>(f_ttbar_semilep_ex6->Get("PtEta_Eff_g_T"));

 TH2D *ex6_ttbar_dilep_b_T = dynamic_cast<TH2D *>(f_ttbar_dilep_ex6->Get("PtEta_Eff_b_T"));
 TH2D *ex6_ttbar_dilep_c_T = dynamic_cast<TH2D *>(f_ttbar_dilep_ex6->Get("PtEta_Eff_c_T"));
 TH2D *ex6_ttbar_dilep_uds_T = dynamic_cast<TH2D *>(f_ttbar_dilep_ex6->Get("PtEta_Eff_uds_T"));
 TH2D *ex6_ttbar_dilep_g_T = dynamic_cast<TH2D *>(f_ttbar_dilep_ex6->Get("PtEta_Eff_g_T"));

 TH2D *ex6_ttbar_inc_b_T = dynamic_cast<TH2D *>(f_ttbar_inc_ex6->Get("PtEta_Eff_b_T"));
 TH2D *ex6_ttbar_inc_c_T = dynamic_cast<TH2D *>(f_ttbar_inc_ex6->Get("PtEta_Eff_c_T"));
 TH2D *ex6_ttbar_inc_uds_T = dynamic_cast<TH2D *>(f_ttbar_inc_ex6->Get("PtEta_Eff_uds_T"));
 TH2D *ex6_ttbar_inc_g_T = dynamic_cast<TH2D *>(f_ttbar_inc_ex6->Get("PtEta_Eff_g_T"));

 TH2D *ex6_t_schan_b_T = dynamic_cast<TH2D *>(f_t_schan_ex6->Get("PtEta_Eff_b_T"));
 TH2D *ex6_t_schan_c_T = dynamic_cast<TH2D *>(f_t_schan_ex6->Get("PtEta_Eff_c_T"));
 TH2D *ex6_t_schan_uds_T = dynamic_cast<TH2D *>(f_t_schan_ex6->Get("PtEta_Eff_uds_T"));
 TH2D *ex6_t_schan_g_T = dynamic_cast<TH2D *>(f_t_schan_ex6->Get("PtEta_Eff_g_T"));

 TH2D *ex6_t_tchan_b_T = dynamic_cast<TH2D *>(f_t_tchan_ex6->Get("PtEta_Eff_b_T"));
 TH2D *ex6_t_tchan_c_T = dynamic_cast<TH2D *>(f_t_tchan_ex6->Get("PtEta_Eff_c_T"));
 TH2D *ex6_t_tchan_uds_T = dynamic_cast<TH2D *>(f_t_tchan_ex6->Get("PtEta_Eff_uds_T"));
 TH2D *ex6_t_tchan_g_T = dynamic_cast<TH2D *>(f_t_tchan_ex6->Get("PtEta_Eff_g_T"));

 TH2D *ex6_t_tWchan_b_T = dynamic_cast<TH2D *>(f_t_tWchan_ex6->Get("PtEta_Eff_b_T"));
 TH2D *ex6_t_tWchan_c_T = dynamic_cast<TH2D *>(f_t_tWchan_ex6->Get("PtEta_Eff_c_T"));
 TH2D *ex6_t_tWchan_uds_T = dynamic_cast<TH2D *>(f_t_tWchan_ex6->Get("PtEta_Eff_uds_T"));
 TH2D *ex6_t_tWchan_g_T = dynamic_cast<TH2D *>(f_t_tWchan_ex6->Get("PtEta_Eff_g_T"));

 TH2D *ex6_Wjets_b_T = dynamic_cast<TH2D *>(f_Wjets_ex6->Get("PtEta_Eff_b_T"));
 TH2D *ex6_Wjets_c_T = dynamic_cast<TH2D *>(f_Wjets_ex6->Get("PtEta_Eff_c_T"));
 TH2D *ex6_Wjets_uds_T = dynamic_cast<TH2D *>(f_Wjets_ex6->Get("PtEta_Eff_uds_T"));
 TH2D *ex6_Wjets_g_T = dynamic_cast<TH2D *>(f_Wjets_ex6->Get("PtEta_Eff_g_T"));

 // Set the proper name and title for the histograms
 // in4
 in4_tHq_nc_b_T->SetNameTitle("tHq-nc_b_T", "tHq-nc b CSVT Efficiency");
 in4_tHq_nc_c_T->SetNameTitle("tHq-nc_c_T", "tHq-nc c CSVT Efficiency");
 in4_tHq_nc_uds_T->SetNameTitle("tHq-nc_uds_T", "tHq-nc uds CSVT Efficiency");
 in4_tHq_nc_g_T->SetNameTitle("tHq-nc_g_T", "tHq-nc g CSVT Efficiency");

 in4_tHq_sm_b_T->SetNameTitle("tHq-sm_b_T", "tHq-sm b CSVT Efficiency");
 in4_tHq_sm_c_T->SetNameTitle("tHq-sm_c_T", "tHq-sm c CSVT Efficiency");
 in4_tHq_sm_uds_T->SetNameTitle("tHq-sm_uds_T", "tHq-sm uds CSVT Efficiency");
 in4_tHq_sm_g_T->SetNameTitle("tHq-sm_g_T", "tHq-sm g CSVT Efficiency");

 in4_ttH_b_T->SetNameTitle("ttH_b_T", "ttH b CSVT Efficiency");
 in4_ttH_c_T->SetNameTitle("ttH_c_T", "ttH c CSVT Efficiency");
 in4_ttH_uds_T->SetNameTitle("ttH_uds_T", "ttH uds CSVT Efficiency");
 in4_ttH_g_T->SetNameTitle("ttH_g_T", "ttH g CSVT Efficiency");

 in4_ttbar_semilep_b_T->SetNameTitle("ttbar-semilep_b_T", "ttbar-semilep b CSVT Efficiency");
 in4_ttbar_semilep_c_T->SetNameTitle("ttbar-semilep_c_T", "ttbar-semilep c CSVT Efficiency");
 in4_ttbar_semilep_uds_T->SetNameTitle("ttbar-semilep_uds_T", "ttbar-semilep uds CSVT Efficiency");
 in4_ttbar_semilep_g_T->SetNameTitle("ttbar-semilep_g_T", "ttbar-semilep g CSVT Efficiency");

 in4_ttbar_dilep_b_T->SetNameTitle("ttbar-dilep_b_T", "ttbar-dilep b CSVT Efficiency");
 in4_ttbar_dilep_c_T->SetNameTitle("ttbar-dilep_c_T", "ttbar-dilep c CSVT Efficiency");
 in4_ttbar_dilep_uds_T->SetNameTitle("ttbar-dilep_uds_T", "ttbar-dilep uds CSVT Efficiency");
 in4_ttbar_dilep_g_T->SetNameTitle("ttbar-dilep_g_T", "ttbar-dilep g CSVT Efficiency");

 in4_ttbar_inc_b_T->SetNameTitle("ttbar-inc_b_T", "ttbar-inc b CSVT Efficiency");
 in4_ttbar_inc_c_T->SetNameTitle("ttbar-inc_c_T", "ttbar-inc c CSVT Efficiency");
 in4_ttbar_inc_uds_T->SetNameTitle("ttbar-inc_uds_T", "ttbar-inc uds CSVT Efficiency");
 in4_ttbar_inc_g_T->SetNameTitle("ttbar-inc_g_T", "ttbar-inc g CSVT Efficiency");

 in4_t_schan_b_T->SetNameTitle("t-schan_b_T", "t-schan b CSVT Efficiency");
 in4_t_schan_c_T->SetNameTitle("t-schan_c_T", "t-schan c CSVT Efficiency");
 in4_t_schan_uds_T->SetNameTitle("t-schan_uds_T", "t-schan uds CSVT Efficiency");
 in4_t_schan_g_T->SetNameTitle("t-schan_g_T", "t-schan g CSVT Efficiency");

 in4_t_tchan_b_T->SetNameTitle("t-tchan_b_T", "t-tchan b CSVT Efficiency");
 in4_t_tchan_c_T->SetNameTitle("t-tchan_c_T", "t-tchan c CSVT Efficiency");
 in4_t_tchan_uds_T->SetNameTitle("t-tchan_uds_T", "t-tchan uds CSVT Efficiency");
 in4_t_tchan_g_T->SetNameTitle("t-tchan_g_T", "t-tchan g CSVT Efficiency");

 in4_t_tWchan_b_T->SetNameTitle("t-tWchan_b_T", "t-tWchan b CSVT Efficiency");
 in4_t_tWchan_c_T->SetNameTitle("t-tWchan_c_T", "t-tWchan c CSVT Efficiency"); 
 in4_t_tWchan_uds_T->SetNameTitle("t-tWchan_uds_T", "t-tWchan uds CSVT Efficiency");
 in4_t_tWchan_g_T->SetNameTitle("t-tWchan_g_T", "t-tWchan g CSVT Efficiency");

 in4_Wjets_b_T->SetNameTitle("Wjets_b_T", "Wjets b CSVT Efficiency");
 in4_Wjets_c_T->SetNameTitle("Wjets_c_T", "Wjets c CSVT Efficiency");
 in4_Wjets_uds_T->SetNameTitle("Wjets_uds_T", "Wjets uds CSVT Efficiency");
 in4_Wjets_g_T->SetNameTitle("Wjets_g_T", "Wjets g CSVT Efficiency");

 // ex4
 ex4_tHq_nc_b_T->SetNameTitle("tHq-nc_b_T", "tHq-nc b CSVT Efficiency");
 ex4_tHq_nc_c_T->SetNameTitle("tHq-nc_c_T", "tHq-nc c CSVT Efficiency");
 ex4_tHq_nc_uds_T->SetNameTitle("tHq-nc_uds_T", "tHq-nc uds CSVT Efficiency");
 ex4_tHq_nc_g_T->SetNameTitle("tHq-nc_g_T", "tHq-nc g CSVT Efficiency");

 ex4_tHq_sm_b_T->SetNameTitle("tHq-sm_b_T", "tHq-sm b CSVT Efficiency");
 ex4_tHq_sm_c_T->SetNameTitle("tHq-sm_c_T", "tHq-sm c CSVT Efficiency");
 ex4_tHq_sm_uds_T->SetNameTitle("tHq-sm_uds_T", "tHq-sm uds CSVT Efficiency");
 ex4_tHq_sm_g_T->SetNameTitle("tHq-sm_g_T", "tHq-sm g CSVT Efficiency");

 ex4_ttH_b_T->SetNameTitle("ttH_b_T", "ttH b CSVT Efficiency");
 ex4_ttH_c_T->SetNameTitle("ttH_c_T", "ttH c CSVT Efficiency");
 ex4_ttH_uds_T->SetNameTitle("ttH_uds_T", "ttH uds CSVT Efficiency");
 ex4_ttH_g_T->SetNameTitle("ttH_g_T", "ttH g CSVT Efficiency");

 ex4_ttbar_semilep_b_T->SetNameTitle("ttbar-semilep_b_T", "ttbar-semilep b CSVT Efficiency");
 ex4_ttbar_semilep_c_T->SetNameTitle("ttbar-semilep_c_T", "ttbar-semilep c CSVT Efficiency");
 ex4_ttbar_semilep_uds_T->SetNameTitle("ttbar-semilep_uds_T", "ttbar-semilep uds CSVT Efficiency");
 ex4_ttbar_semilep_g_T->SetNameTitle("ttbar-semilep_g_T", "ttbar-semilep g CSVT Efficiency");

 ex4_ttbar_dilep_b_T->SetNameTitle("ttbar-dilep_b_T", "ttbar-dilep b CSVT Efficiency");
 ex4_ttbar_dilep_c_T->SetNameTitle("ttbar-dilep_c_T", "ttbar-dilep c CSVT Efficiency");
 ex4_ttbar_dilep_uds_T->SetNameTitle("ttbar-dilep_uds_T", "ttbar-dilep uds CSVT Efficiency");
 ex4_ttbar_dilep_g_T->SetNameTitle("ttbar-dilep_g_T", "ttbar-dilep g CSVT Efficiency");

 ex4_ttbar_inc_b_T->SetNameTitle("ttbar-inc_b_T", "ttbar-inc b CSVT Efficiency");
 ex4_ttbar_inc_c_T->SetNameTitle("ttbar-inc_c_T", "ttbar-inc c CSVT Efficiency");
 ex4_ttbar_inc_uds_T->SetNameTitle("ttbar-inc_uds_T", "ttbar-inc uds CSVT Efficiency");
 ex4_ttbar_inc_g_T->SetNameTitle("ttbar-inc_g_T", "ttbar-inc g CSVT Efficiency");

 ex4_t_schan_b_T->SetNameTitle("t-schan_b_T", "t-schan b CSVT Efficiency");
 ex4_t_schan_c_T->SetNameTitle("t-schan_c_T", "t-schan c CSVT Efficiency");
 ex4_t_schan_uds_T->SetNameTitle("t-schan_uds_T", "t-schan uds CSVT Efficiency");
 ex4_t_schan_g_T->SetNameTitle("t-schan_g_T", "t-schan g CSVT Efficiency");

 ex4_t_tchan_b_T->SetNameTitle("t-tchan_b_T", "t-tchan b CSVT Efficiency");
 ex4_t_tchan_c_T->SetNameTitle("t-tchan_c_T", "t-tchan c CSVT Efficiency");
 ex4_t_tchan_uds_T->SetNameTitle("t-tchan_uds_T", "t-tchan uds CSVT Efficiency");
 ex4_t_tchan_g_T->SetNameTitle("t-tchan_g_T", "t-tchan g CSVT Efficiency");

 ex4_t_tWchan_b_T->SetNameTitle("t-tWchan_b_T", "t-tWchan b CSVT Efficiency");
 ex4_t_tWchan_c_T->SetNameTitle("t-tWchan_c_T", "t-tWchan c CSVT Efficiency"); 
 ex4_t_tWchan_uds_T->SetNameTitle("t-tWchan_uds_T", "t-tWchan uds CSVT Efficiency");
 ex4_t_tWchan_g_T->SetNameTitle("t-tWchan_g_T", "t-tWchan g CSVT Efficiency");

 ex4_Wjets_b_T->SetNameTitle("Wjets_b_T", "Wjets b CSVT Efficiency");
 ex4_Wjets_c_T->SetNameTitle("Wjets_c_T", "Wjets c CSVT Efficiency");
 ex4_Wjets_uds_T->SetNameTitle("Wjets_uds_T", "Wjets uds CSVT Efficiency");
 ex4_Wjets_g_T->SetNameTitle("Wjets_g_T", "Wjets g CSVT Efficiency");

 // ex5
 ex5_tHq_nc_b_T->SetNameTitle("tHq-nc_b_T", "tHq-nc b CSVT Efficiency");
 ex5_tHq_nc_c_T->SetNameTitle("tHq-nc_c_T", "tHq-nc c CSVT Efficiency");
 ex5_tHq_nc_uds_T->SetNameTitle("tHq-nc_uds_T", "tHq-nc uds CSVT Efficiency");
 ex5_tHq_nc_g_T->SetNameTitle("tHq-nc_g_T", "tHq-nc g CSVT Efficiency");

 ex5_tHq_sm_b_T->SetNameTitle("tHq-sm_b_T", "tHq-sm b CSVT Efficiency");
 ex5_tHq_sm_c_T->SetNameTitle("tHq-sm_c_T", "tHq-sm c CSVT Efficiency");
 ex5_tHq_sm_uds_T->SetNameTitle("tHq-sm_uds_T", "tHq-sm uds CSVT Efficiency");
 ex5_tHq_sm_g_T->SetNameTitle("tHq-sm_g_T", "tHq-sm g CSVT Efficiency");

 ex5_ttH_b_T->SetNameTitle("ttH_b_T", "ttH b CSVT Efficiency");
 ex5_ttH_c_T->SetNameTitle("ttH_c_T", "ttH c CSVT Efficiency");
 ex5_ttH_uds_T->SetNameTitle("ttH_uds_T", "ttH uds CSVT Efficiency");
 ex5_ttH_g_T->SetNameTitle("ttH_g_T", "ttH g CSVT Efficiency");

 ex5_ttbar_semilep_b_T->SetNameTitle("ttbar-semilep_b_T", "ttbar-semilep b CSVT Efficiency");
 ex5_ttbar_semilep_c_T->SetNameTitle("ttbar-semilep_c_T", "ttbar-semilep c CSVT Efficiency");
 ex5_ttbar_semilep_uds_T->SetNameTitle("ttbar-semilep_uds_T", "ttbar-semilep uds CSVT Efficiency");
 ex5_ttbar_semilep_g_T->SetNameTitle("ttbar-semilep_g_T", "ttbar-semilep g CSVT Efficiency");

 ex5_ttbar_dilep_b_T->SetNameTitle("ttbar-dilep_b_T", "ttbar-dilep b CSVT Efficiency");
 ex5_ttbar_dilep_c_T->SetNameTitle("ttbar-dilep_c_T", "ttbar-dilep c CSVT Efficiency");
 ex5_ttbar_dilep_uds_T->SetNameTitle("ttbar-dilep_uds_T", "ttbar-dilep uds CSVT Efficiency");
 ex5_ttbar_dilep_g_T->SetNameTitle("ttbar-dilep_g_T", "ttbar-dilep g CSVT Efficiency");

 ex5_ttbar_inc_b_T->SetNameTitle("ttbar-inc_b_T", "ttbar-inc b CSVT Efficiency");
 ex5_ttbar_inc_c_T->SetNameTitle("ttbar-inc_c_T", "ttbar-inc c CSVT Efficiency");
 ex5_ttbar_inc_uds_T->SetNameTitle("ttbar-inc_uds_T", "ttbar-inc uds CSVT Efficiency");
 ex5_ttbar_inc_g_T->SetNameTitle("ttbar-inc_g_T", "ttbar-inc g CSVT Efficiency");

 ex5_t_schan_b_T->SetNameTitle("t-schan_b_T", "t-schan b CSVT Efficiency");
 ex5_t_schan_c_T->SetNameTitle("t-schan_c_T", "t-schan c CSVT Efficiency");
 ex5_t_schan_uds_T->SetNameTitle("t-schan_uds_T", "t-schan uds CSVT Efficiency");
 ex5_t_schan_g_T->SetNameTitle("t-schan_g_T", "t-schan g CSVT Efficiency");

 ex5_t_tchan_b_T->SetNameTitle("t-tchan_b_T", "t-tchan b CSVT Efficiency");
 ex5_t_tchan_c_T->SetNameTitle("t-tchan_c_T", "t-tchan c CSVT Efficiency");
 ex5_t_tchan_uds_T->SetNameTitle("t-tchan_uds_T", "t-tchan uds CSVT Efficiency");
 ex5_t_tchan_g_T->SetNameTitle("t-tchan_g_T", "t-tchan g CSVT Efficiency");

 ex5_t_tWchan_b_T->SetNameTitle("t-tWchan_b_T", "t-tWchan b CSVT Efficiency");
 ex5_t_tWchan_c_T->SetNameTitle("t-tWchan_c_T", "t-tWchan c CSVT Efficiency"); 
 ex5_t_tWchan_uds_T->SetNameTitle("t-tWchan_uds_T", "t-tWchan uds CSVT Efficiency");
 ex5_t_tWchan_g_T->SetNameTitle("t-tWchan_g_T", "t-tWchan g CSVT Efficiency");

 ex5_Wjets_b_T->SetNameTitle("Wjets_b_T", "Wjets b CSVT Efficiency");
 ex5_Wjets_c_T->SetNameTitle("Wjets_c_T", "Wjets c CSVT Efficiency");
 ex5_Wjets_uds_T->SetNameTitle("Wjets_uds_T", "Wjets uds CSVT Efficiency");
 ex5_Wjets_g_T->SetNameTitle("Wjets_g_T", "Wjets g CSVT Efficiency");

 ex6_tHq_nc_b_T->SetNameTitle("tHq-nc_b_T", "tHq-nc b CSVT Efficiency");
 ex6_tHq_nc_c_T->SetNameTitle("tHq-nc_c_T", "tHq-nc c CSVT Efficiency");
 ex6_tHq_nc_uds_T->SetNameTitle("tHq-nc_uds_T", "tHq-nc uds CSVT Efficiency");
 ex6_tHq_nc_g_T->SetNameTitle("tHq-nc_g_T", "tHq-nc g CSVT Efficiency");

 ex6_tHq_sm_b_T->SetNameTitle("tHq-sm_b_T", "tHq-sm b CSVT Efficiency");
 ex6_tHq_sm_c_T->SetNameTitle("tHq-sm_c_T", "tHq-sm c CSVT Efficiency");
 ex6_tHq_sm_uds_T->SetNameTitle("tHq-sm_uds_T", "tHq-sm uds CSVT Efficiency");
 ex6_tHq_sm_g_T->SetNameTitle("tHq-sm_g_T", "tHq-sm g CSVT Efficiency");

 ex6_ttH_b_T->SetNameTitle("ttH_b_T", "ttH b CSVT Efficiency");
 ex6_ttH_c_T->SetNameTitle("ttH_c_T", "ttH c CSVT Efficiency");
 ex6_ttH_uds_T->SetNameTitle("ttH_uds_T", "ttH uds CSVT Efficiency");
 ex6_ttH_g_T->SetNameTitle("ttH_g_T", "ttH g CSVT Efficiency");

 ex6_ttbar_semilep_b_T->SetNameTitle("ttbar-semilep_b_T", "ttbar-semilep b CSVT Efficiency");
 ex6_ttbar_semilep_c_T->SetNameTitle("ttbar-semilep_c_T", "ttbar-semilep c CSVT Efficiency");
 ex6_ttbar_semilep_uds_T->SetNameTitle("ttbar-semilep_uds_T", "ttbar-semilep uds CSVT Efficiency");
 ex6_ttbar_semilep_g_T->SetNameTitle("ttbar-semilep_g_T", "ttbar-semilep g CSVT Efficiency");

 ex6_ttbar_dilep_b_T->SetNameTitle("ttbar-dilep_b_T", "ttbar-dilep b CSVT Efficiency");
 ex6_ttbar_dilep_c_T->SetNameTitle("ttbar-dilep_c_T", "ttbar-dilep c CSVT Efficiency");
 ex6_ttbar_dilep_uds_T->SetNameTitle("ttbar-dilep_uds_T", "ttbar-dilep uds CSVT Efficiency");
 ex6_ttbar_dilep_g_T->SetNameTitle("ttbar-dilep_g_T", "ttbar-dilep g CSVT Efficiency");

 ex6_ttbar_inc_b_T->SetNameTitle("ttbar-inc_b_T", "ttbar-inc b CSVT Efficiency");
 ex6_ttbar_inc_c_T->SetNameTitle("ttbar-inc_c_T", "ttbar-inc c CSVT Efficiency");
 ex6_ttbar_inc_uds_T->SetNameTitle("ttbar-inc_uds_T", "ttbar-inc uds CSVT Efficiency");
 ex6_ttbar_inc_g_T->SetNameTitle("ttbar-inc_g_T", "ttbar-inc g CSVT Efficiency");

 ex6_t_schan_b_T->SetNameTitle("t-schan_b_T", "t-schan b CSVT Efficiency");
 ex6_t_schan_c_T->SetNameTitle("t-schan_c_T", "t-schan c CSVT Efficiency");
 ex6_t_schan_uds_T->SetNameTitle("t-schan_uds_T", "t-schan uds CSVT Efficiency");
 ex6_t_schan_g_T->SetNameTitle("t-schan_g_T", "t-schan g CSVT Efficiency");

 ex6_t_tchan_b_T->SetNameTitle("t-tchan_b_T", "t-tchan b CSVT Efficiency");
 ex6_t_tchan_c_T->SetNameTitle("t-tchan_c_T", "t-tchan c CSVT Efficiency");
 ex6_t_tchan_uds_T->SetNameTitle("t-tchan_uds_T", "t-tchan uds CSVT Efficiency");
 ex6_t_tchan_g_T->SetNameTitle("t-tchan_g_T", "t-tchan g CSVT Efficiency");

 ex6_t_tWchan_b_T->SetNameTitle("t-tWchan_b_T", "t-tWchan b CSVT Efficiency");
 ex6_t_tWchan_c_T->SetNameTitle("t-tWchan_c_T", "t-tWchan c CSVT Efficiency"); 
 ex6_t_tWchan_uds_T->SetNameTitle("t-tWchan_uds_T", "t-tWchan uds CSVT Efficiency");
 ex6_t_tWchan_g_T->SetNameTitle("t-tWchan_g_T", "t-tWchan g CSVT Efficiency");

 ex6_Wjets_b_T->SetNameTitle("Wjets_b_T", "Wjets b CSVT Efficiency");
 ex6_Wjets_c_T->SetNameTitle("Wjets_c_T", "Wjets c CSVT Efficiency");
 ex6_Wjets_uds_T->SetNameTitle("Wjets_uds_T", "Wjets uds CSVT Efficiency");
 ex6_Wjets_g_T->SetNameTitle("Wjets_g_T", "Wjets g CSVT Efficiency");

 // Prepare the directories inside the output file
 f_out->mkdir("in4_jPt30");
 f_out->mkdir("ex4_jPt30");
 f_out->mkdir("ex5_jPt30");
 f_out->mkdir("ex6_jPt30");

 // Prepare the version number
 TObjString *ver = new TObjString("1.0");
 ver->Write("formatVersion");

 // Dump the histograms in the right folder
 // in4
 f_out->cd("in4_jPt30");
 
 in4_tHq_nc_b_T->Write();
 in4_tHq_nc_c_T->Write();
 in4_tHq_nc_uds_T->Write();
 in4_tHq_nc_g_T->Write();

 in4_tHq_sm_b_T->Write();
 in4_tHq_sm_c_T->Write();
 in4_tHq_sm_uds_T->Write();
 in4_tHq_sm_g_T->Write();

 in4_ttH_b_T->Write();
 in4_ttH_c_T->Write();
 in4_ttH_uds_T->Write();
 in4_ttH_g_T->Write();

 in4_ttbar_semilep_b_T->Write();
 in4_ttbar_semilep_c_T->Write();
 in4_ttbar_semilep_uds_T->Write();
 in4_ttbar_semilep_g_T->Write();

 in4_ttbar_dilep_b_T->Write();
 in4_ttbar_dilep_c_T->Write();
 in4_ttbar_dilep_uds_T->Write();
 in4_ttbar_dilep_g_T->Write();

 in4_ttbar_inc_b_T->Write();
 in4_ttbar_inc_c_T->Write();
 in4_ttbar_inc_uds_T->Write();
 in4_ttbar_inc_g_T->Write();

 in4_t_schan_b_T->Write();
 in4_t_schan_c_T->Write();
 in4_t_schan_uds_T->Write();
 in4_t_schan_g_T->Write();

 in4_t_tchan_b_T->Write();
 in4_t_tchan_c_T->Write();
 in4_t_tchan_uds_T->Write();
 in4_t_tchan_g_T->Write();

 in4_t_tWchan_b_T->Write();
 in4_t_tWchan_c_T->Write(); 
 in4_t_tWchan_uds_T->Write();
 in4_t_tWchan_g_T->Write();

 in4_Wjets_b_T->Write();
 in4_Wjets_c_T->Write();
 in4_Wjets_uds_T->Write();
 in4_Wjets_g_T->Write();

 // ex4
 f_out->cd("ex4_jPt30");
 
 ex4_tHq_nc_b_T->Write();
 ex4_tHq_nc_c_T->Write();
 ex4_tHq_nc_uds_T->Write();
 ex4_tHq_nc_g_T->Write();

 ex4_tHq_sm_b_T->Write();
 ex4_tHq_sm_c_T->Write();
 ex4_tHq_sm_uds_T->Write();
 ex4_tHq_sm_g_T->Write();

 ex4_ttH_b_T->Write();
 ex4_ttH_c_T->Write();
 ex4_ttH_uds_T->Write();
 ex4_ttH_g_T->Write();

 ex4_ttbar_semilep_b_T->Write();
 ex4_ttbar_semilep_c_T->Write();
 ex4_ttbar_semilep_uds_T->Write();
 ex4_ttbar_semilep_g_T->Write();

 ex4_ttbar_dilep_b_T->Write();
 ex4_ttbar_dilep_c_T->Write();
 ex4_ttbar_dilep_uds_T->Write();
 ex4_ttbar_dilep_g_T->Write();

 ex4_ttbar_inc_b_T->Write();
 ex4_ttbar_inc_c_T->Write();
 ex4_ttbar_inc_uds_T->Write();
 ex4_ttbar_inc_g_T->Write();

 ex4_t_schan_b_T->Write();
 ex4_t_schan_c_T->Write();
 ex4_t_schan_uds_T->Write();
 ex4_t_schan_g_T->Write();

 ex4_t_tchan_b_T->Write();
 ex4_t_tchan_c_T->Write();
 ex4_t_tchan_uds_T->Write();
 ex4_t_tchan_g_T->Write();

 ex4_t_tWchan_b_T->Write();
 ex4_t_tWchan_c_T->Write(); 
 ex4_t_tWchan_uds_T->Write();
 ex4_t_tWchan_g_T->Write();

 ex4_Wjets_b_T->Write();
 ex4_Wjets_c_T->Write();
 ex4_Wjets_uds_T->Write();
 ex4_Wjets_g_T->Write();

 // ex5
 f_out->cd("ex5_jPt30");
 
 ex5_tHq_nc_b_T->Write();
 ex5_tHq_nc_c_T->Write();
 ex5_tHq_nc_uds_T->Write();
 ex5_tHq_nc_g_T->Write();

 ex5_tHq_sm_b_T->Write();
 ex5_tHq_sm_c_T->Write();
 ex5_tHq_sm_uds_T->Write();
 ex5_tHq_sm_g_T->Write();

 ex5_ttH_b_T->Write();
 ex5_ttH_c_T->Write();
 ex5_ttH_uds_T->Write();
 ex5_ttH_g_T->Write();

 ex5_ttbar_semilep_b_T->Write();
 ex5_ttbar_semilep_c_T->Write();
 ex5_ttbar_semilep_uds_T->Write();
 ex5_ttbar_semilep_g_T->Write();

 ex5_ttbar_dilep_b_T->Write();
 ex5_ttbar_dilep_c_T->Write();
 ex5_ttbar_dilep_uds_T->Write();
 ex5_ttbar_dilep_g_T->Write();

 ex5_ttbar_inc_b_T->Write();
 ex5_ttbar_inc_c_T->Write();
 ex5_ttbar_inc_uds_T->Write();
 ex5_ttbar_inc_g_T->Write();

 ex5_t_schan_b_T->Write();
 ex5_t_schan_c_T->Write();
 ex5_t_schan_uds_T->Write();
 ex5_t_schan_g_T->Write();

 ex5_t_tchan_b_T->Write();
 ex5_t_tchan_c_T->Write();
 ex5_t_tchan_uds_T->Write();
 ex5_t_tchan_g_T->Write();

 ex5_t_tWchan_b_T->Write();
 ex5_t_tWchan_c_T->Write(); 
 ex5_t_tWchan_uds_T->Write();
 ex5_t_tWchan_g_T->Write();

 ex5_Wjets_b_T->Write();
 ex5_Wjets_c_T->Write();
 ex5_Wjets_uds_T->Write();
 ex5_Wjets_g_T->Write();

 // ex6
 f_out->cd("ex6_jPt30");
 
 ex6_tHq_nc_b_T->Write();
 ex6_tHq_nc_c_T->Write();
 ex6_tHq_nc_uds_T->Write();
 ex6_tHq_nc_g_T->Write();

 ex6_tHq_sm_b_T->Write();
 ex6_tHq_sm_c_T->Write();
 ex6_tHq_sm_uds_T->Write();
 ex6_tHq_sm_g_T->Write();

 ex6_ttH_b_T->Write();
 ex6_ttH_c_T->Write();
 ex6_ttH_uds_T->Write();
 ex6_ttH_g_T->Write();

 ex6_ttbar_semilep_b_T->Write();
 ex6_ttbar_semilep_c_T->Write();
 ex6_ttbar_semilep_uds_T->Write();
 ex6_ttbar_semilep_g_T->Write();

 ex6_ttbar_dilep_b_T->Write();
 ex6_ttbar_dilep_c_T->Write();
 ex6_ttbar_dilep_uds_T->Write();
 ex6_ttbar_dilep_g_T->Write();

 ex6_ttbar_inc_b_T->Write();
 ex6_ttbar_inc_c_T->Write();
 ex6_ttbar_inc_uds_T->Write();
 ex6_ttbar_inc_g_T->Write();

 ex6_t_schan_b_T->Write();
 ex6_t_schan_c_T->Write();
 ex6_t_schan_uds_T->Write();
 ex6_t_schan_g_T->Write();

 ex6_t_tchan_b_T->Write();
 ex6_t_tchan_c_T->Write();
 ex6_t_tchan_uds_T->Write();
 ex6_t_tchan_g_T->Write();

 ex6_t_tWchan_b_T->Write();
 ex6_t_tWchan_c_T->Write(); 
 ex6_t_tWchan_uds_T->Write();
 ex6_t_tWchan_g_T->Write();

 ex6_Wjets_b_T->Write();
 ex6_Wjets_c_T->Write();
 ex6_Wjets_uds_T->Write();
 ex6_Wjets_g_T->Write();

 f_out->Close();

}
