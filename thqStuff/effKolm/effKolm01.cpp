/*** effKolm01.cpp (comProcess)
- Kolmogorov-Smirnov goodness of fit test on the eff hists (based on ttbar-semilep hists)
- Draw the hists for a visual comparison
- Afiq A. Anuar
***/

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

void effKolm01() {

 string binName, eraName, inDir, outDir;

 // the name of the bin/event conf used
 binName = "in4";

 // data comes from which campaign
 eraName = "2012Bravo";

 // input and output directory (updates itself with conf above)
 inDir = "/home/ieeya/Downloads/Part2_BTagEff/root_files/" + eraName + "_eff/hists_" + binName + "/";
 outDir = "/home/ieeya/Downloads/Part2_BTagEff/img/" + eraName + "_eff/comProcess/";

 // set up all the canvases and files
 TCanvas *c1 = new TCanvas("c1", "b pT", 200, 10, 1600, 900);
 TCanvas *c2 = new TCanvas("c2", "c pT", 200, 10, 1600, 900);
 TCanvas *c3 = new TCanvas("c3", "uds pT", 200, 10, 1600, 900);
 TCanvas *c4 = new TCanvas("c4", "g pT", 200, 10, 1600, 900);
 TCanvas *c5 = new TCanvas("c5", "b eta", 200, 10, 1600, 900);
 TCanvas *c6 = new TCanvas("c6", "c eta", 200, 10, 1600, 900);
 TCanvas *c7 = new TCanvas("c7", "uds eta", 200, 10, 1600, 900);
 TCanvas *c8 = new TCanvas("c8", "g eta", 200, 10, 1600, 900);

 TFile *f_tHq_nc = new TFile((inDir + "tHq-nc.root").c_str());
 TFile *f_tHq_sm = new TFile((inDir + "tHq-sm.root").c_str());
 TFile *f_ttH = new TFile((inDir + "ttH.root").c_str());
 TFile *f_ttbar_semilep = new TFile((inDir + "ttbar-semilep.root").c_str());
 TFile *f_ttbar_dilep = new TFile((inDir + "ttbar-dilep.root").c_str());
 TFile *f_ttbar_inc = new TFile((inDir + "ttbar-inc.root").c_str());
 TFile *f_t_schan = new TFile((inDir + "t-schan.root").c_str());
 TFile *f_t_tchan = new TFile((inDir + "t-tchan.root").c_str());
 TFile *f_t_tWchan = new TFile((inDir + "t-tWchan.root").c_str());
 TFile *f_Wjets = new TFile((inDir + "Wjets.root").c_str());

 // link up all the histograms
 // stacked hists
 THStack *Pt_Eff_b_T = new THStack("Pt_Eff_b_T", "Pt_Eff_b_T");
 THStack *Pt_Eff_c_T = new THStack("Pt_Eff_c_T", "Pt_Eff_c_T");
 THStack *Pt_Eff_uds_T = new THStack("Pt_Eff_uds_T", "Pt_Eff_uds_T");
 THStack *Pt_Eff_g_T = new THStack("Pt_Eff_g_T", "Pt_Eff_c_T");

 THStack *Eta_Eff_b_T = new THStack("Eta_Eff_b_T", "Eta_Eff_b_T");
 THStack *Eta_Eff_c_T = new THStack("Eta_Eff_c_T", "Eta_Eff_c_T");
 THStack *Eta_Eff_uds_T = new THStack("Eta_Eff_uds_T", "Eta_Eff_uds_T");
 THStack *Eta_Eff_g_T = new THStack("Eta_Eff_g_T", "Eta_Eff_g_T");

 // tHq-nc
 TH1D *tHq_nc_Pt_Eff_b_T = dynamic_cast<TH1D *>(f_tHq_nc->Get("Pt_Eff_b_T")); TH1D *tHq_nc_Eta_Eff_b_T = dynamic_cast<TH1D *>(f_tHq_nc->Get("Eta_Eff_b_T"));
 TH1D *tHq_nc_Pt_Eff_c_T = dynamic_cast<TH1D *>(f_tHq_nc->Get("Pt_Eff_c_T")); TH1D *tHq_nc_Eta_Eff_c_T = dynamic_cast<TH1D *>(f_tHq_nc->Get("Eta_Eff_c_T"));
 TH1D *tHq_nc_Pt_Eff_uds_T = dynamic_cast<TH1D *>(f_tHq_nc->Get("Pt_Eff_uds_T")); TH1D *tHq_nc_Eta_Eff_uds_T = dynamic_cast<TH1D *>(f_tHq_nc->Get("Eta_Eff_uds_T"));
 TH1D *tHq_nc_Pt_Eff_g_T = dynamic_cast<TH1D *>(f_tHq_nc->Get("Pt_Eff_g_T")); TH1D *tHq_nc_Eta_Eff_g_T = dynamic_cast<TH1D *>(f_tHq_nc->Get("Eta_Eff_g_T"));

 // tHq-sm
 TH1D *tHq_sm_Pt_Eff_b_T = dynamic_cast<TH1D *>(f_tHq_sm->Get("Pt_Eff_b_T")); TH1D *tHq_sm_Eta_Eff_b_T = dynamic_cast<TH1D *>(f_tHq_sm->Get("Eta_Eff_b_T"));
 TH1D *tHq_sm_Pt_Eff_c_T = dynamic_cast<TH1D *>(f_tHq_sm->Get("Pt_Eff_c_T")); TH1D *tHq_sm_Eta_Eff_c_T = dynamic_cast<TH1D *>(f_tHq_sm->Get("Eta_Eff_c_T"));
 TH1D *tHq_sm_Pt_Eff_uds_T = dynamic_cast<TH1D *>(f_tHq_sm->Get("Pt_Eff_uds_T")); TH1D *tHq_sm_Eta_Eff_uds_T = dynamic_cast<TH1D *>(f_tHq_sm->Get("Eta_Eff_uds_T"));
 TH1D *tHq_sm_Pt_Eff_g_T = dynamic_cast<TH1D *>(f_tHq_sm->Get("Pt_Eff_g_T")); TH1D *tHq_sm_Eta_Eff_g_T = dynamic_cast<TH1D *>(f_tHq_sm->Get("Eta_Eff_g_T"));

 // ttH
 TH1D *ttH_Pt_Eff_b_T = dynamic_cast<TH1D *>(f_ttH->Get("Pt_Eff_b_T")); TH1D *ttH_Eta_Eff_b_T = dynamic_cast<TH1D *>(f_ttH->Get("Eta_Eff_b_T"));
 TH1D *ttH_Pt_Eff_c_T = dynamic_cast<TH1D *>(f_ttH->Get("Pt_Eff_c_T")); TH1D *ttH_Eta_Eff_c_T = dynamic_cast<TH1D *>(f_ttH->Get("Eta_Eff_c_T"));
 TH1D *ttH_Pt_Eff_uds_T = dynamic_cast<TH1D *>(f_ttH->Get("Pt_Eff_uds_T")); TH1D *ttH_Eta_Eff_uds_T = dynamic_cast<TH1D *>(f_ttH->Get("Eta_Eff_uds_T"));
 TH1D *ttH_Pt_Eff_g_T = dynamic_cast<TH1D *>(f_ttH->Get("Pt_Eff_g_T")); TH1D *ttH_Eta_Eff_g_T = dynamic_cast<TH1D *>(f_ttH->Get("Eta_Eff_g_T"));

 // ttbar-semilep
 TH1D *ttbar_semilep_Pt_Eff_b_T = dynamic_cast<TH1D *>(f_ttbar_semilep->Get("Pt_Eff_b_T")); TH1D *ttbar_semilep_Eta_Eff_b_T = dynamic_cast<TH1D *>(f_ttbar_semilep->Get("Eta_Eff_b_T"));
 TH1D *ttbar_semilep_Pt_Eff_c_T = dynamic_cast<TH1D *>(f_ttbar_semilep->Get("Pt_Eff_c_T")); TH1D *ttbar_semilep_Eta_Eff_c_T = dynamic_cast<TH1D *>(f_ttbar_semilep->Get("Eta_Eff_c_T"));
 TH1D *ttbar_semilep_Pt_Eff_uds_T = dynamic_cast<TH1D *>(f_ttbar_semilep->Get("Pt_Eff_uds_T")); TH1D *ttbar_semilep_Eta_Eff_uds_T = dynamic_cast<TH1D *>(f_ttbar_semilep->Get("Eta_Eff_uds_T"));
 TH1D *ttbar_semilep_Pt_Eff_g_T = dynamic_cast<TH1D *>(f_ttbar_semilep->Get("Pt_Eff_g_T")); TH1D *ttbar_semilep_Eta_Eff_g_T = dynamic_cast<TH1D *>(f_ttbar_semilep->Get("Eta_Eff_g_T"));

 // ttbar-dilep
 TH1D *ttbar_dilep_Pt_Eff_b_T = dynamic_cast<TH1D *>(f_ttbar_dilep->Get("Pt_Eff_b_T")); TH1D *ttbar_dilep_Eta_Eff_b_T = dynamic_cast<TH1D *>(f_ttbar_dilep->Get("Eta_Eff_b_T"));
 TH1D *ttbar_dilep_Pt_Eff_c_T = dynamic_cast<TH1D *>(f_ttbar_dilep->Get("Pt_Eff_c_T")); TH1D *ttbar_dilep_Eta_Eff_c_T = dynamic_cast<TH1D *>(f_ttbar_dilep->Get("Eta_Eff_c_T"));
 TH1D *ttbar_dilep_Pt_Eff_uds_T = dynamic_cast<TH1D *>(f_ttbar_dilep->Get("Pt_Eff_uds_T")); TH1D *ttbar_dilep_Eta_Eff_uds_T = dynamic_cast<TH1D *>(f_ttbar_dilep->Get("Eta_Eff_uds_T"));
 TH1D *ttbar_dilep_Pt_Eff_g_T = dynamic_cast<TH1D *>(f_ttbar_dilep->Get("Pt_Eff_g_T")); TH1D *ttbar_dilep_Eta_Eff_g_T = dynamic_cast<TH1D *>(f_ttbar_dilep->Get("Eta_Eff_g_T"));

 // ttbar-inc
 TH1D *ttbar_inc_Pt_Eff_b_T = dynamic_cast<TH1D *>(f_ttbar_inc->Get("Pt_Eff_b_T")); TH1D *ttbar_inc_Eta_Eff_b_T = dynamic_cast<TH1D *>(f_ttbar_inc->Get("Eta_Eff_b_T"));
 TH1D *ttbar_inc_Pt_Eff_c_T = dynamic_cast<TH1D *>(f_ttbar_inc->Get("Pt_Eff_c_T")); TH1D *ttbar_inc_Eta_Eff_c_T = dynamic_cast<TH1D *>(f_ttbar_inc->Get("Eta_Eff_c_T"));
 TH1D *ttbar_inc_Pt_Eff_uds_T = dynamic_cast<TH1D *>(f_ttbar_inc->Get("Pt_Eff_uds_T")); TH1D *ttbar_inc_Eta_Eff_uds_T = dynamic_cast<TH1D *>(f_ttbar_inc->Get("Eta_Eff_uds_T"));
 TH1D *ttbar_inc_Pt_Eff_g_T = dynamic_cast<TH1D *>(f_ttbar_inc->Get("Pt_Eff_g_T")); TH1D *ttbar_inc_Eta_Eff_g_T = dynamic_cast<TH1D *>(f_ttbar_inc->Get("Eta_Eff_g_T"));

 // t-schan
 TH1D *t_schan_Pt_Eff_b_T = dynamic_cast<TH1D *>(f_t_schan->Get("Pt_Eff_b_T")); TH1D *t_schan_Eta_Eff_b_T = dynamic_cast<TH1D *>(f_t_schan->Get("Eta_Eff_b_T"));
 TH1D *t_schan_Pt_Eff_c_T = dynamic_cast<TH1D *>(f_t_schan->Get("Pt_Eff_c_T")); TH1D *t_schan_Eta_Eff_c_T = dynamic_cast<TH1D *>(f_t_schan->Get("Eta_Eff_c_T"));
 TH1D *t_schan_Pt_Eff_uds_T = dynamic_cast<TH1D *>(f_t_schan->Get("Pt_Eff_uds_T")); TH1D *t_schan_Eta_Eff_uds_T = dynamic_cast<TH1D *>(f_t_schan->Get("Eta_Eff_uds_T"));
 TH1D *t_schan_Pt_Eff_g_T = dynamic_cast<TH1D *>(f_t_schan->Get("Pt_Eff_g_T")); TH1D *t_schan_Eta_Eff_g_T = dynamic_cast<TH1D *>(f_t_schan->Get("Eta_Eff_g_T"));

 // t-tchan
 TH1D *t_tchan_Pt_Eff_b_T = dynamic_cast<TH1D *>(f_t_tchan->Get("Pt_Eff_b_T")); TH1D *t_tchan_Eta_Eff_b_T = dynamic_cast<TH1D *>(f_t_tchan->Get("Eta_Eff_b_T"));
 TH1D *t_tchan_Pt_Eff_c_T = dynamic_cast<TH1D *>(f_t_tchan->Get("Pt_Eff_c_T")); TH1D *t_tchan_Eta_Eff_c_T = dynamic_cast<TH1D *>(f_t_tchan->Get("Eta_Eff_c_T"));
 TH1D *t_tchan_Pt_Eff_uds_T = dynamic_cast<TH1D *>(f_t_tchan->Get("Pt_Eff_uds_T")); TH1D *t_tchan_Eta_Eff_uds_T = dynamic_cast<TH1D *>(f_t_tchan->Get("Eta_Eff_uds_T"));
 TH1D *t_tchan_Pt_Eff_g_T = dynamic_cast<TH1D *>(f_t_tchan->Get("Pt_Eff_g_T")); TH1D *t_tchan_Eta_Eff_g_T = dynamic_cast<TH1D *>(f_t_tchan->Get("Eta_Eff_g_T"));

 // t-tWchan
 TH1D *t_tWchan_Pt_Eff_b_T = dynamic_cast<TH1D *>(f_t_tWchan->Get("Pt_Eff_b_T")); TH1D *t_tWchan_Eta_Eff_b_T = dynamic_cast<TH1D *>(f_t_tWchan->Get("Eta_Eff_b_T"));
 TH1D *t_tWchan_Pt_Eff_c_T = dynamic_cast<TH1D *>(f_t_tWchan->Get("Pt_Eff_c_T")); TH1D *t_tWchan_Eta_Eff_c_T = dynamic_cast<TH1D *>(f_t_tWchan->Get("Eta_Eff_c_T"));
 TH1D *t_tWchan_Pt_Eff_uds_T = dynamic_cast<TH1D *>(f_t_tWchan->Get("Pt_Eff_uds_T")); TH1D *t_tWchan_Eta_Eff_uds_T = dynamic_cast<TH1D *>(f_t_tWchan->Get("Eta_Eff_uds_T"));
 TH1D *t_tWchan_Pt_Eff_g_T = dynamic_cast<TH1D *>(f_t_tWchan->Get("Pt_Eff_g_T")); TH1D *t_tWchan_Eta_Eff_g_T = dynamic_cast<TH1D *>(f_t_tWchan->Get("Eta_Eff_g_T"));

 // Wjets
 TH1D *Wjets_Pt_Eff_b_T = dynamic_cast<TH1D *>(f_Wjets->Get("Pt_Eff_b_T")); TH1D *Wjets_Eta_Eff_b_T = dynamic_cast<TH1D *>(f_Wjets->Get("Eta_Eff_b_T"));
 TH1D *Wjets_Pt_Eff_c_T = dynamic_cast<TH1D *>(f_Wjets->Get("Pt_Eff_c_T")); TH1D *Wjets_Eta_Eff_c_T = dynamic_cast<TH1D *>(f_Wjets->Get("Eta_Eff_c_T"));
 TH1D *Wjets_Pt_Eff_uds_T = dynamic_cast<TH1D *>(f_Wjets->Get("Pt_Eff_uds_T")); TH1D *Wjets_Eta_Eff_uds_T = dynamic_cast<TH1D *>(f_Wjets->Get("Eta_Eff_uds_T"));
 TH1D *Wjets_Pt_Eff_g_T = dynamic_cast<TH1D *>(f_Wjets->Get("Pt_Eff_g_T")); TH1D *Wjets_Eta_Eff_g_T = dynamic_cast<TH1D *>(f_Wjets->Get("Eta_Eff_g_T"));

 // styling (for 1D histos only)
 setTDRStyle();

 // stacks the histogram, one canvas for one flavor
 c1->cd();
 tHq_nc_Pt_Eff_b_T->SetMarkerStyle(1); tHq_nc_Pt_Eff_b_T->SetMarkerColor(1); tHq_nc_Pt_Eff_b_T->SetLineColor(1); Pt_Eff_b_T->Add(tHq_nc_Pt_Eff_b_T);
 tHq_sm_Pt_Eff_b_T->SetMarkerStyle(2); tHq_sm_Pt_Eff_b_T->SetMarkerColor(2); tHq_sm_Pt_Eff_b_T->SetLineColor(2); Pt_Eff_b_T->Add(tHq_sm_Pt_Eff_b_T);
 ttH_Pt_Eff_b_T->SetMarkerStyle(3); ttH_Pt_Eff_b_T->SetMarkerColor(3); ttH_Pt_Eff_b_T->SetLineColor(3); Pt_Eff_b_T->Add(ttH_Pt_Eff_b_T);
 ttbar_semilep_Pt_Eff_b_T->SetMarkerStyle(4); ttbar_semilep_Pt_Eff_b_T->SetMarkerColor(4); ttbar_semilep_Pt_Eff_b_T->SetLineColor(4); Pt_Eff_b_T->Add(ttbar_semilep_Pt_Eff_b_T);
 ttbar_dilep_Pt_Eff_b_T->SetMarkerStyle(5); ttbar_dilep_Pt_Eff_b_T->SetMarkerColor(5); ttbar_dilep_Pt_Eff_b_T->SetLineColor(5); Pt_Eff_b_T->Add(ttbar_dilep_Pt_Eff_b_T);
 ttbar_inc_Pt_Eff_b_T->SetMarkerStyle(6); ttbar_inc_Pt_Eff_b_T->SetMarkerColor(6); ttbar_inc_Pt_Eff_b_T->SetLineColor(6); Pt_Eff_b_T->Add(ttbar_inc_Pt_Eff_b_T);
 t_schan_Pt_Eff_b_T->SetMarkerStyle(7); t_schan_Pt_Eff_b_T->SetMarkerColor(7); t_schan_Pt_Eff_b_T->SetLineColor(7); Pt_Eff_b_T->Add(t_schan_Pt_Eff_b_T);
 t_tchan_Pt_Eff_b_T->SetMarkerStyle(23); t_tchan_Pt_Eff_b_T->SetMarkerColor(23); t_tchan_Pt_Eff_b_T->SetLineColor(23); Pt_Eff_b_T->Add(t_tchan_Pt_Eff_b_T);
 t_tWchan_Pt_Eff_b_T->SetMarkerStyle(28); t_tWchan_Pt_Eff_b_T->SetMarkerColor(28); t_tWchan_Pt_Eff_b_T->SetLineColor(28); Pt_Eff_b_T->Add(t_tWchan_Pt_Eff_b_T);
 Wjets_Pt_Eff_b_T->SetMarkerStyle(30); Wjets_Pt_Eff_b_T->SetMarkerColor(30); Wjets_Pt_Eff_b_T->SetLineColor(30); Pt_Eff_b_T->Add(Wjets_Pt_Eff_b_T);
 Pt_Eff_b_T->Draw("nostack");
 
 // legends
 TLegend *leg01 = new TLegend(.83, .75, .99, .99);
 leg01->SetHeader("Process");
 leg01->AddEntry(tHq_nc_Pt_Eff_b_T, "tHq-nc");
 leg01->AddEntry(tHq_sm_Pt_Eff_b_T, "tHq-sm");
 leg01->AddEntry(ttH_Pt_Eff_b_T, "ttH");
 leg01->AddEntry(ttbar_semilep_Pt_Eff_b_T, "ttbar-semilep");
 leg01->AddEntry(ttbar_dilep_Pt_Eff_b_T, "ttbar-dilep");
 leg01->AddEntry(ttbar_inc_Pt_Eff_b_T, "ttbar-inc");
 leg01->AddEntry(t_schan_Pt_Eff_b_T, "t-schan");
 leg01->AddEntry(t_tchan_Pt_Eff_b_T, "t-tchan");
 leg01->AddEntry(t_tWchan_Pt_Eff_b_T, "t-tWchan");
 leg01->AddEntry(Wjets_Pt_Eff_b_T, "Wjets");
 leg01->Draw();

 c1->SaveAs((outDir + "Pt_Eff_b_T.png").c_str());
 c1->SaveAs((outDir + "Pt_Eff_b_T.pdf").c_str());

 c2->cd();
 tHq_nc_Pt_Eff_c_T->SetMarkerStyle(1); tHq_nc_Pt_Eff_c_T->SetMarkerColor(1); tHq_nc_Pt_Eff_c_T->SetLineColor(1); Pt_Eff_c_T->Add(tHq_nc_Pt_Eff_c_T);
 tHq_sm_Pt_Eff_c_T->SetMarkerStyle(2); tHq_sm_Pt_Eff_c_T->SetMarkerColor(2); tHq_sm_Pt_Eff_c_T->SetLineColor(2); Pt_Eff_c_T->Add(tHq_sm_Pt_Eff_c_T);
 ttH_Pt_Eff_c_T->SetMarkerStyle(3); ttH_Pt_Eff_c_T->SetMarkerColor(3); ttH_Pt_Eff_c_T->SetLineColor(3); Pt_Eff_c_T->Add(ttH_Pt_Eff_c_T);
 ttbar_semilep_Pt_Eff_c_T->SetMarkerStyle(4); ttbar_semilep_Pt_Eff_c_T->SetMarkerColor(4); ttbar_semilep_Pt_Eff_c_T->SetLineColor(4); Pt_Eff_c_T->Add(ttbar_semilep_Pt_Eff_c_T);
 ttbar_dilep_Pt_Eff_c_T->SetMarkerStyle(5); ttbar_dilep_Pt_Eff_c_T->SetMarkerColor(5); ttbar_dilep_Pt_Eff_c_T->SetLineColor(5); Pt_Eff_c_T->Add(ttbar_dilep_Pt_Eff_c_T);
 ttbar_inc_Pt_Eff_c_T->SetMarkerStyle(6); ttbar_inc_Pt_Eff_c_T->SetMarkerColor(6); ttbar_inc_Pt_Eff_c_T->SetLineColor(6); Pt_Eff_c_T->Add(ttbar_inc_Pt_Eff_c_T);
 t_schan_Pt_Eff_c_T->SetMarkerStyle(7); t_schan_Pt_Eff_c_T->SetMarkerColor(7); t_schan_Pt_Eff_c_T->SetLineColor(7); Pt_Eff_c_T->Add(t_schan_Pt_Eff_c_T);
 t_tchan_Pt_Eff_c_T->SetMarkerStyle(23); t_tchan_Pt_Eff_c_T->SetMarkerColor(23); t_tchan_Pt_Eff_c_T->SetLineColor(23); Pt_Eff_c_T->Add(t_tchan_Pt_Eff_c_T);
 t_tWchan_Pt_Eff_c_T->SetMarkerStyle(28); t_tWchan_Pt_Eff_c_T->SetMarkerColor(28); t_tWchan_Pt_Eff_c_T->SetLineColor(28); Pt_Eff_c_T->Add(t_tWchan_Pt_Eff_c_T);
 Wjets_Pt_Eff_c_T->SetMarkerStyle(30); Wjets_Pt_Eff_c_T->SetMarkerColor(30); Wjets_Pt_Eff_c_T->SetLineColor(30); Pt_Eff_c_T->Add(Wjets_Pt_Eff_c_T);
 Pt_Eff_c_T->Draw("nostack");
 
 // legends
 TLegend *leg02 = new TLegend(.83, .75, .99, .99);
 leg02->SetHeader("Process");
 leg02->AddEntry(tHq_nc_Pt_Eff_c_T, "tHq-nc");
 leg02->AddEntry(tHq_sm_Pt_Eff_c_T, "tHq-sm");
 leg02->AddEntry(ttH_Pt_Eff_c_T, "ttH");
 leg02->AddEntry(ttbar_semilep_Pt_Eff_c_T, "ttbar-semilep");
 leg02->AddEntry(ttbar_dilep_Pt_Eff_c_T, "ttbar-dilep");
 leg02->AddEntry(ttbar_inc_Pt_Eff_c_T, "ttbar-inc");
 leg02->AddEntry(t_schan_Pt_Eff_c_T, "t-schan");
 leg02->AddEntry(t_tchan_Pt_Eff_c_T, "t-tchan");
 leg02->AddEntry(t_tWchan_Pt_Eff_c_T, "t-tWchan");
 leg02->AddEntry(Wjets_Pt_Eff_c_T, "Wjets");
 leg02->Draw();

 c2->SaveAs((outDir + "Pt_Eff_c_T.png").c_str());
 c2->SaveAs((outDir + "Pt_Eff_c_T.pdf").c_str());

 c3->cd();
 tHq_nc_Pt_Eff_uds_T->SetMarkerStyle(1); tHq_nc_Pt_Eff_uds_T->SetMarkerColor(1); tHq_nc_Pt_Eff_uds_T->SetLineColor(1); Pt_Eff_uds_T->Add(tHq_nc_Pt_Eff_uds_T);
 tHq_sm_Pt_Eff_uds_T->SetMarkerStyle(2); tHq_sm_Pt_Eff_uds_T->SetMarkerColor(2); tHq_sm_Pt_Eff_uds_T->SetLineColor(2); Pt_Eff_uds_T->Add(tHq_sm_Pt_Eff_uds_T);
 ttH_Pt_Eff_uds_T->SetMarkerStyle(3); ttH_Pt_Eff_uds_T->SetMarkerColor(3); ttH_Pt_Eff_uds_T->SetLineColor(3); Pt_Eff_uds_T->Add(ttH_Pt_Eff_uds_T);
 ttbar_semilep_Pt_Eff_uds_T->SetMarkerStyle(4); ttbar_semilep_Pt_Eff_uds_T->SetMarkerColor(4); ttbar_semilep_Pt_Eff_uds_T->SetLineColor(4); Pt_Eff_uds_T->Add(ttbar_semilep_Pt_Eff_uds_T);
 ttbar_dilep_Pt_Eff_uds_T->SetMarkerStyle(5); ttbar_dilep_Pt_Eff_uds_T->SetMarkerColor(5); ttbar_dilep_Pt_Eff_uds_T->SetLineColor(5); Pt_Eff_uds_T->Add(ttbar_dilep_Pt_Eff_uds_T);
 ttbar_inc_Pt_Eff_uds_T->SetMarkerStyle(6); ttbar_inc_Pt_Eff_uds_T->SetMarkerColor(6); ttbar_inc_Pt_Eff_uds_T->SetLineColor(6); Pt_Eff_uds_T->Add(ttbar_inc_Pt_Eff_uds_T);
 t_schan_Pt_Eff_uds_T->SetMarkerStyle(7); t_schan_Pt_Eff_uds_T->SetMarkerColor(7); t_schan_Pt_Eff_uds_T->SetLineColor(7); Pt_Eff_uds_T->Add(t_schan_Pt_Eff_uds_T);
 t_tchan_Pt_Eff_uds_T->SetMarkerStyle(23); t_tchan_Pt_Eff_uds_T->SetMarkerColor(23); t_tchan_Pt_Eff_uds_T->SetLineColor(23); Pt_Eff_uds_T->Add(t_tchan_Pt_Eff_uds_T);
 t_tWchan_Pt_Eff_uds_T->SetMarkerStyle(28); t_tWchan_Pt_Eff_uds_T->SetMarkerColor(28); t_tWchan_Pt_Eff_uds_T->SetLineColor(28); Pt_Eff_uds_T->Add(t_tWchan_Pt_Eff_uds_T);
 Wjets_Pt_Eff_uds_T->SetMarkerStyle(30); Wjets_Pt_Eff_uds_T->SetMarkerColor(30); Wjets_Pt_Eff_uds_T->SetLineColor(30); Pt_Eff_uds_T->Add(Wjets_Pt_Eff_uds_T);
 Pt_Eff_uds_T->Draw("nostack");
 
 // legends
 TLegend *leg03 = new TLegend(.83, .75, .99, .99);
 leg03->SetHeader("Process");
 leg03->AddEntry(tHq_nc_Pt_Eff_uds_T, "tHq-nc");
 leg03->AddEntry(tHq_sm_Pt_Eff_uds_T, "tHq-sm");
 leg03->AddEntry(ttH_Pt_Eff_uds_T, "ttH");
 leg03->AddEntry(ttbar_semilep_Pt_Eff_uds_T, "ttbar-semilep");
 leg03->AddEntry(ttbar_dilep_Pt_Eff_uds_T, "ttbar-dilep");
 leg03->AddEntry(ttbar_inc_Pt_Eff_uds_T, "ttbar-inc");
 leg03->AddEntry(t_schan_Pt_Eff_uds_T, "t-schan");
 leg03->AddEntry(t_tchan_Pt_Eff_uds_T, "t-tchan");
 leg03->AddEntry(t_tWchan_Pt_Eff_uds_T, "t-tWchan");
 leg03->AddEntry(Wjets_Pt_Eff_uds_T, "Wjets");
 leg03->Draw();

 c3->SaveAs((outDir + "Pt_Eff_uds_T.png").c_str());
 c3->SaveAs((outDir + "Pt_Eff_uds_T.pdf").c_str());

 c4->cd();
 tHq_nc_Pt_Eff_g_T->SetMarkerStyle(1); tHq_nc_Pt_Eff_g_T->SetMarkerColor(1); tHq_nc_Pt_Eff_g_T->SetLineColor(1); Pt_Eff_g_T->Add(tHq_nc_Pt_Eff_g_T);
 tHq_sm_Pt_Eff_g_T->SetMarkerStyle(2); tHq_sm_Pt_Eff_g_T->SetMarkerColor(2); tHq_sm_Pt_Eff_g_T->SetLineColor(2); Pt_Eff_g_T->Add(tHq_sm_Pt_Eff_g_T);
 ttH_Pt_Eff_g_T->SetMarkerStyle(3); ttH_Pt_Eff_g_T->SetMarkerColor(3); ttH_Pt_Eff_g_T->SetLineColor(3); Pt_Eff_g_T->Add(ttH_Pt_Eff_g_T);
 ttbar_semilep_Pt_Eff_g_T->SetMarkerStyle(4); ttbar_semilep_Pt_Eff_g_T->SetMarkerColor(4); ttbar_semilep_Pt_Eff_g_T->SetLineColor(4); Pt_Eff_g_T->Add(ttbar_semilep_Pt_Eff_g_T);
 ttbar_dilep_Pt_Eff_g_T->SetMarkerStyle(5); ttbar_dilep_Pt_Eff_g_T->SetMarkerColor(5); ttbar_dilep_Pt_Eff_g_T->SetLineColor(5); Pt_Eff_g_T->Add(ttbar_dilep_Pt_Eff_g_T);
 ttbar_inc_Pt_Eff_g_T->SetMarkerStyle(6); ttbar_inc_Pt_Eff_g_T->SetMarkerColor(6); ttbar_inc_Pt_Eff_g_T->SetLineColor(6); Pt_Eff_g_T->Add(ttbar_inc_Pt_Eff_g_T);
 t_schan_Pt_Eff_g_T->SetMarkerStyle(7); t_schan_Pt_Eff_g_T->SetMarkerColor(7); t_schan_Pt_Eff_g_T->SetLineColor(7); Pt_Eff_g_T->Add(t_schan_Pt_Eff_g_T);
 t_tchan_Pt_Eff_g_T->SetMarkerStyle(23); t_tchan_Pt_Eff_g_T->SetMarkerColor(23); t_tchan_Pt_Eff_g_T->SetLineColor(23); Pt_Eff_g_T->Add(t_tchan_Pt_Eff_g_T);
 t_tWchan_Pt_Eff_g_T->SetMarkerStyle(28); t_tWchan_Pt_Eff_g_T->SetMarkerColor(28); t_tWchan_Pt_Eff_g_T->SetLineColor(28); Pt_Eff_g_T->Add(t_tWchan_Pt_Eff_g_T);
 Wjets_Pt_Eff_g_T->SetMarkerStyle(30); Wjets_Pt_Eff_g_T->SetMarkerColor(30); Wjets_Pt_Eff_g_T->SetLineColor(30); Pt_Eff_g_T->Add(Wjets_Pt_Eff_g_T);
 Pt_Eff_g_T->Draw("nostack");
 
 // legends
 TLegend *leg04 = new TLegend(.83, .75, .99, .99);
 leg04->SetHeader("Process");
 leg04->AddEntry(tHq_nc_Pt_Eff_g_T, "tHq-nc");
 leg04->AddEntry(tHq_sm_Pt_Eff_g_T, "tHq-sm");
 leg04->AddEntry(ttH_Pt_Eff_g_T, "ttH");
 leg04->AddEntry(ttbar_semilep_Pt_Eff_g_T, "ttbar-semilep");
 leg04->AddEntry(ttbar_dilep_Pt_Eff_g_T, "ttbar-dilep");
 leg04->AddEntry(ttbar_inc_Pt_Eff_g_T, "ttbar-inc");
 leg04->AddEntry(t_schan_Pt_Eff_g_T, "t-schan");
 leg04->AddEntry(t_tchan_Pt_Eff_g_T, "t-tchan");
 leg04->AddEntry(t_tWchan_Pt_Eff_g_T, "t-tWchan");
 leg04->AddEntry(Wjets_Pt_Eff_g_T, "Wjets");
 leg04->Draw();

 c4->SaveAs((outDir + "Pt_Eff_g_T.png").c_str());
 c4->SaveAs((outDir + "Pt_Eff_g_T.pdf").c_str());

 c5->cd();
 tHq_nc_Eta_Eff_b_T->SetMarkerStyle(1); tHq_nc_Eta_Eff_b_T->SetMarkerColor(1); tHq_nc_Eta_Eff_b_T->SetLineColor(1); Eta_Eff_b_T->Add(tHq_nc_Eta_Eff_b_T);
 tHq_sm_Eta_Eff_b_T->SetMarkerStyle(2); tHq_sm_Eta_Eff_b_T->SetMarkerColor(2); tHq_sm_Eta_Eff_b_T->SetLineColor(2); Eta_Eff_b_T->Add(tHq_sm_Eta_Eff_b_T);
 ttH_Eta_Eff_b_T->SetMarkerStyle(3); ttH_Eta_Eff_b_T->SetMarkerColor(3); ttH_Eta_Eff_b_T->SetLineColor(3); Eta_Eff_b_T->Add(ttH_Eta_Eff_b_T);
 ttbar_semilep_Eta_Eff_b_T->SetMarkerStyle(4); ttbar_semilep_Eta_Eff_b_T->SetMarkerColor(4); ttbar_semilep_Eta_Eff_b_T->SetLineColor(4); Eta_Eff_b_T->Add(ttbar_semilep_Eta_Eff_b_T);
 ttbar_dilep_Eta_Eff_b_T->SetMarkerStyle(5); ttbar_dilep_Eta_Eff_b_T->SetMarkerColor(5); ttbar_dilep_Eta_Eff_b_T->SetLineColor(5); Eta_Eff_b_T->Add(ttbar_dilep_Eta_Eff_b_T);
 ttbar_inc_Eta_Eff_b_T->SetMarkerStyle(6); ttbar_inc_Eta_Eff_b_T->SetMarkerColor(6); ttbar_inc_Eta_Eff_b_T->SetLineColor(6); Eta_Eff_b_T->Add(ttbar_inc_Eta_Eff_b_T);
 t_schan_Eta_Eff_b_T->SetMarkerStyle(7); t_schan_Eta_Eff_b_T->SetMarkerColor(7); t_schan_Eta_Eff_b_T->SetLineColor(7); Eta_Eff_b_T->Add(t_schan_Eta_Eff_b_T);
 t_tchan_Eta_Eff_b_T->SetMarkerStyle(23); t_tchan_Eta_Eff_b_T->SetMarkerColor(23); t_tchan_Eta_Eff_b_T->SetLineColor(23); Eta_Eff_b_T->Add(t_tchan_Eta_Eff_b_T);
 t_tWchan_Eta_Eff_b_T->SetMarkerStyle(28); t_tWchan_Eta_Eff_b_T->SetMarkerColor(28); t_tWchan_Eta_Eff_b_T->SetLineColor(28); Eta_Eff_b_T->Add(t_tWchan_Eta_Eff_b_T);
 Wjets_Eta_Eff_b_T->SetMarkerStyle(30); Wjets_Eta_Eff_b_T->SetMarkerColor(30); Wjets_Eta_Eff_b_T->SetLineColor(30); Eta_Eff_b_T->Add(Wjets_Eta_Eff_b_T);
 Eta_Eff_b_T->Draw("nostack");
 
 // legends
 TLegend *leg05 = new TLegend(.83, .75, .99, .99);
 leg05->SetHeader("Process");
 leg05->AddEntry(tHq_nc_Eta_Eff_b_T, "tHq-nc");
 leg05->AddEntry(tHq_sm_Eta_Eff_b_T, "tHq-sm");
 leg05->AddEntry(ttH_Eta_Eff_b_T, "ttH");
 leg05->AddEntry(ttbar_semilep_Eta_Eff_b_T, "ttbar-semilep");
 leg05->AddEntry(ttbar_dilep_Eta_Eff_b_T, "ttbar-dilep");
 leg05->AddEntry(ttbar_inc_Eta_Eff_b_T, "ttbar-inc");
 leg05->AddEntry(t_schan_Eta_Eff_b_T, "t-schan");
 leg05->AddEntry(t_tchan_Eta_Eff_b_T, "t-tchan");
 leg05->AddEntry(t_tWchan_Eta_Eff_b_T, "t-tWchan");
 leg05->AddEntry(Wjets_Eta_Eff_b_T, "Wjets");
 leg05->Draw();

 c5->SaveAs((outDir + "Eta_Eff_b_T.png").c_str());
 c5->SaveAs((outDir + "Eta_Eff_b_T.pdf").c_str());

 c6->cd();
 tHq_nc_Eta_Eff_c_T->SetMarkerStyle(1); tHq_nc_Eta_Eff_c_T->SetMarkerColor(1); tHq_nc_Eta_Eff_c_T->SetLineColor(1); Eta_Eff_c_T->Add(tHq_nc_Eta_Eff_c_T);
 tHq_sm_Eta_Eff_c_T->SetMarkerStyle(2); tHq_sm_Eta_Eff_c_T->SetMarkerColor(2); tHq_sm_Eta_Eff_c_T->SetLineColor(2); Eta_Eff_c_T->Add(tHq_sm_Eta_Eff_c_T);
 ttH_Eta_Eff_c_T->SetMarkerStyle(3); ttH_Eta_Eff_c_T->SetMarkerColor(3); ttH_Eta_Eff_c_T->SetLineColor(3); Eta_Eff_c_T->Add(ttH_Eta_Eff_c_T);
 ttbar_semilep_Eta_Eff_c_T->SetMarkerStyle(4); ttbar_semilep_Eta_Eff_c_T->SetMarkerColor(4); ttbar_semilep_Eta_Eff_c_T->SetLineColor(4); Eta_Eff_c_T->Add(ttbar_semilep_Eta_Eff_c_T);
 ttbar_dilep_Eta_Eff_c_T->SetMarkerStyle(5); ttbar_dilep_Eta_Eff_c_T->SetMarkerColor(5); ttbar_dilep_Eta_Eff_c_T->SetLineColor(5); Eta_Eff_c_T->Add(ttbar_dilep_Eta_Eff_c_T);
 ttbar_inc_Eta_Eff_c_T->SetMarkerStyle(6); ttbar_inc_Eta_Eff_c_T->SetMarkerColor(6); ttbar_inc_Eta_Eff_c_T->SetLineColor(6); Eta_Eff_c_T->Add(ttbar_inc_Eta_Eff_c_T);
 t_schan_Eta_Eff_c_T->SetMarkerStyle(7); t_schan_Eta_Eff_c_T->SetMarkerColor(7); t_schan_Eta_Eff_c_T->SetLineColor(7); Eta_Eff_c_T->Add(t_schan_Eta_Eff_c_T);
 t_tchan_Eta_Eff_c_T->SetMarkerStyle(23); t_tchan_Eta_Eff_c_T->SetMarkerColor(23); t_tchan_Eta_Eff_c_T->SetLineColor(23); Eta_Eff_c_T->Add(t_tchan_Eta_Eff_c_T);
 t_tWchan_Eta_Eff_c_T->SetMarkerStyle(28); t_tWchan_Eta_Eff_c_T->SetMarkerColor(28); t_tWchan_Eta_Eff_c_T->SetLineColor(28); Eta_Eff_c_T->Add(t_tWchan_Eta_Eff_c_T);
 Wjets_Eta_Eff_c_T->SetMarkerStyle(30); Wjets_Eta_Eff_c_T->SetMarkerColor(30); Wjets_Eta_Eff_c_T->SetLineColor(30); Eta_Eff_c_T->Add(Wjets_Eta_Eff_c_T);
 Eta_Eff_c_T->Draw("nostack");
 
 // legends
 TLegend *leg06 = new TLegend(.83, .75, .99, .99);
 leg06->SetHeader("Process");
 leg06->AddEntry(tHq_nc_Eta_Eff_c_T, "tHq-nc");
 leg06->AddEntry(tHq_sm_Eta_Eff_c_T, "tHq-sm");
 leg06->AddEntry(ttH_Eta_Eff_c_T, "ttH");
 leg06->AddEntry(ttbar_semilep_Eta_Eff_c_T, "ttbar-semilep");
 leg06->AddEntry(ttbar_dilep_Eta_Eff_c_T, "ttbar-dilep");
 leg06->AddEntry(ttbar_inc_Eta_Eff_c_T, "ttbar-inc");
 leg06->AddEntry(t_schan_Eta_Eff_c_T, "t-schan");
 leg06->AddEntry(t_tchan_Eta_Eff_c_T, "t-tchan");
 leg06->AddEntry(t_tWchan_Eta_Eff_c_T, "t-tWchan");
 leg06->AddEntry(Wjets_Eta_Eff_c_T, "Wjets");
 leg06->Draw();

 c6->SaveAs((outDir + "Eta_Eff_c_T.png").c_str());
 c6->SaveAs((outDir + "Eta_Eff_c_T.pdf").c_str());

 c7->cd();
 tHq_nc_Eta_Eff_uds_T->SetMarkerStyle(1); tHq_nc_Eta_Eff_uds_T->SetMarkerColor(1); tHq_nc_Eta_Eff_uds_T->SetLineColor(1); Eta_Eff_uds_T->Add(tHq_nc_Eta_Eff_uds_T);
 tHq_sm_Eta_Eff_uds_T->SetMarkerStyle(2); tHq_sm_Eta_Eff_uds_T->SetMarkerColor(2); tHq_sm_Eta_Eff_uds_T->SetLineColor(2); Eta_Eff_uds_T->Add(tHq_sm_Eta_Eff_uds_T);
 ttH_Eta_Eff_uds_T->SetMarkerStyle(3); ttH_Eta_Eff_uds_T->SetMarkerColor(3); ttH_Eta_Eff_uds_T->SetLineColor(3); Eta_Eff_uds_T->Add(ttH_Eta_Eff_uds_T);
 ttbar_semilep_Eta_Eff_uds_T->SetMarkerStyle(4); ttbar_semilep_Eta_Eff_uds_T->SetMarkerColor(4); ttbar_semilep_Eta_Eff_uds_T->SetLineColor(4); Eta_Eff_uds_T->Add(ttbar_semilep_Eta_Eff_uds_T);
 ttbar_dilep_Eta_Eff_uds_T->SetMarkerStyle(5); ttbar_dilep_Eta_Eff_uds_T->SetMarkerColor(5); ttbar_dilep_Eta_Eff_uds_T->SetLineColor(5); Eta_Eff_uds_T->Add(ttbar_dilep_Eta_Eff_uds_T);
 ttbar_inc_Eta_Eff_uds_T->SetMarkerStyle(6); ttbar_inc_Eta_Eff_uds_T->SetMarkerColor(6); ttbar_inc_Eta_Eff_uds_T->SetLineColor(6); Eta_Eff_uds_T->Add(ttbar_inc_Eta_Eff_uds_T);
 t_schan_Eta_Eff_uds_T->SetMarkerStyle(7); t_schan_Eta_Eff_uds_T->SetMarkerColor(7); t_schan_Eta_Eff_uds_T->SetLineColor(7); Eta_Eff_uds_T->Add(t_schan_Eta_Eff_uds_T);
 t_tchan_Eta_Eff_uds_T->SetMarkerStyle(23); t_tchan_Eta_Eff_uds_T->SetMarkerColor(23); t_tchan_Eta_Eff_uds_T->SetLineColor(23); Eta_Eff_uds_T->Add(t_tchan_Eta_Eff_uds_T);
 t_tWchan_Eta_Eff_uds_T->SetMarkerStyle(28); t_tWchan_Eta_Eff_uds_T->SetMarkerColor(28); t_tWchan_Eta_Eff_uds_T->SetLineColor(28); Eta_Eff_uds_T->Add(t_tWchan_Eta_Eff_uds_T);
 Wjets_Eta_Eff_uds_T->SetMarkerStyle(30); Wjets_Eta_Eff_uds_T->SetMarkerColor(30); Wjets_Eta_Eff_uds_T->SetLineColor(30); Eta_Eff_uds_T->Add(Wjets_Eta_Eff_uds_T);
 Eta_Eff_uds_T->Draw("nostack");
 
 // legends
 TLegend *leg07 = new TLegend(.83, .75, .99, .99);
 leg07->SetHeader("Process");
 leg07->AddEntry(tHq_nc_Eta_Eff_uds_T, "tHq-nc");
 leg07->AddEntry(tHq_sm_Eta_Eff_uds_T, "tHq-sm");
 leg07->AddEntry(ttH_Eta_Eff_uds_T, "ttH");
 leg07->AddEntry(ttbar_semilep_Eta_Eff_uds_T, "ttbar-semilep");
 leg07->AddEntry(ttbar_dilep_Eta_Eff_uds_T, "ttbar-dilep");
 leg07->AddEntry(ttbar_inc_Eta_Eff_uds_T, "ttbar-inc");
 leg07->AddEntry(t_tchan_Eta_Eff_uds_T, "t-schan");
 leg07->AddEntry(t_tchan_Eta_Eff_uds_T, "t-tchan");
 leg07->AddEntry(t_tWchan_Eta_Eff_uds_T, "t-tWchan");
 leg07->AddEntry(Wjets_Eta_Eff_uds_T, "Wjets");
 leg07->Draw();

 c7->SaveAs((outDir + "Eta_Eff_uds_T.png").c_str());
 c7->SaveAs((outDir + "Eta_Eff_uds_T.pdf").c_str());

 c8->cd();
 tHq_nc_Eta_Eff_g_T->SetMarkerStyle(1); tHq_nc_Eta_Eff_g_T->SetMarkerColor(1); tHq_nc_Eta_Eff_g_T->SetLineColor(1); Eta_Eff_g_T->Add(tHq_nc_Eta_Eff_g_T);
 tHq_sm_Eta_Eff_g_T->SetMarkerStyle(2); tHq_sm_Eta_Eff_g_T->SetMarkerColor(2); tHq_sm_Eta_Eff_g_T->SetLineColor(2); Eta_Eff_g_T->Add(tHq_sm_Eta_Eff_g_T);
 ttH_Eta_Eff_g_T->SetMarkerStyle(3); ttH_Eta_Eff_g_T->SetMarkerColor(3); ttH_Eta_Eff_g_T->SetLineColor(3); Eta_Eff_g_T->Add(ttH_Eta_Eff_g_T);
 ttbar_semilep_Eta_Eff_g_T->SetMarkerStyle(4); ttbar_semilep_Eta_Eff_g_T->SetMarkerColor(4); ttbar_semilep_Eta_Eff_g_T->SetLineColor(4); Eta_Eff_g_T->Add(ttbar_semilep_Eta_Eff_g_T);
 ttbar_dilep_Eta_Eff_g_T->SetMarkerStyle(5); ttbar_dilep_Eta_Eff_g_T->SetMarkerColor(5); ttbar_dilep_Eta_Eff_g_T->SetLineColor(5); Eta_Eff_g_T->Add(ttbar_dilep_Eta_Eff_g_T);
 ttbar_inc_Eta_Eff_g_T->SetMarkerStyle(6); ttbar_inc_Eta_Eff_g_T->SetMarkerColor(6); ttbar_inc_Eta_Eff_g_T->SetLineColor(6); Eta_Eff_g_T->Add(ttbar_inc_Eta_Eff_g_T);
 t_schan_Eta_Eff_g_T->SetMarkerStyle(7); t_schan_Eta_Eff_g_T->SetMarkerColor(7); t_schan_Eta_Eff_g_T->SetLineColor(7); Eta_Eff_g_T->Add(t_schan_Eta_Eff_g_T);
 t_tchan_Eta_Eff_g_T->SetMarkerStyle(23); t_tchan_Eta_Eff_g_T->SetMarkerColor(23); t_tchan_Eta_Eff_g_T->SetLineColor(23); Eta_Eff_g_T->Add(t_tchan_Eta_Eff_g_T);
 t_tWchan_Eta_Eff_g_T->SetMarkerStyle(28); t_tWchan_Eta_Eff_g_T->SetMarkerColor(28); t_tWchan_Eta_Eff_g_T->SetLineColor(28); Eta_Eff_g_T->Add(t_tWchan_Eta_Eff_g_T);
 Wjets_Eta_Eff_g_T->SetMarkerStyle(30); Wjets_Eta_Eff_g_T->SetMarkerColor(30); Wjets_Eta_Eff_g_T->SetLineColor(30); Eta_Eff_g_T->Add(Wjets_Eta_Eff_g_T);
 Eta_Eff_g_T->Draw("nostack");
 
 // legends
 TLegend *leg08 = new TLegend(.83, .75, .99, .99);
 leg08->SetHeader("Process");
 leg08->AddEntry(tHq_nc_Eta_Eff_g_T, "tHq-nc");
 leg08->AddEntry(tHq_sm_Eta_Eff_g_T, "tHq-sm");
 leg08->AddEntry(ttH_Eta_Eff_g_T, "ttH");
 leg08->AddEntry(ttbar_semilep_Eta_Eff_g_T, "ttbar-semilep");
 leg08->AddEntry(ttbar_dilep_Eta_Eff_g_T, "ttbar-dilep");
 leg08->AddEntry(ttbar_inc_Eta_Eff_g_T, "ttbar-inc");
 leg08->AddEntry(t_schan_Eta_Eff_g_T, "t-schan");
 leg08->AddEntry(t_tchan_Eta_Eff_g_T, "t-tchan");
 leg08->AddEntry(t_tWchan_Eta_Eff_g_T, "t-tWchan");
 leg08->AddEntry(Wjets_Eta_Eff_g_T, "Wjets");
 leg08->Draw();

 c8->SaveAs((outDir + "Eta_Eff_g_T.png").c_str());
 c8->SaveAs((outDir + "Eta_Eff_g_T.pdf").c_str());

 // Do the KS test based on the ttbar-semilep hists
 ofstream kolm_test;
 
 kolm_test.open((outDir + "comProcess.txt").c_str());
 kolm_test << "Output of TH1::KolmogorovTest, relative to the ttbar_semilep rates" << endl;
 kolm_test << endl;

 kolm_test << "b Pt hists"<< endl;
 kolm_test << "tHq-nc: "<< ttbar_semilep_Pt_Eff_b_T->KolmogorovTest(tHq_nc_Pt_Eff_b_T) << endl;
 kolm_test << "tHq-sm: "<< ttbar_semilep_Pt_Eff_b_T->KolmogorovTest(tHq_sm_Pt_Eff_b_T) << endl;
 kolm_test << "ttH: "<< ttbar_semilep_Pt_Eff_b_T->KolmogorovTest(ttH_Pt_Eff_b_T) << endl;
 kolm_test << "ttbar-semilep: " << ttbar_semilep_Pt_Eff_b_T->KolmogorovTest(ttbar_semilep_Pt_Eff_b_T) << endl;
 kolm_test << "ttbar-dilep: " << ttbar_semilep_Pt_Eff_b_T->KolmogorovTest(ttbar_dilep_Pt_Eff_b_T) << endl;
 kolm_test << "ttbar-inc: " << ttbar_semilep_Pt_Eff_b_T->KolmogorovTest(ttbar_inc_Pt_Eff_b_T) << endl;
 kolm_test << "t-schan: " << ttbar_semilep_Pt_Eff_b_T->KolmogorovTest(t_schan_Pt_Eff_b_T) << endl;
 kolm_test << "t-tchan: " << ttbar_semilep_Pt_Eff_b_T->KolmogorovTest(t_tchan_Pt_Eff_b_T) << endl;
 kolm_test << "t-tWchan: " << ttbar_semilep_Pt_Eff_b_T->KolmogorovTest(t_tWchan_Pt_Eff_b_T) << endl;
 kolm_test << "Wjets: " << ttbar_semilep_Pt_Eff_b_T->KolmogorovTest(Wjets_Pt_Eff_b_T) << endl;
 kolm_test << endl;

 kolm_test << "c Pt hists"<< endl;
 kolm_test << "tHq-nc: "<< ttbar_semilep_Pt_Eff_c_T->KolmogorovTest(tHq_nc_Pt_Eff_c_T) << endl;
 kolm_test << "tHq-sm: "<< ttbar_semilep_Pt_Eff_c_T->KolmogorovTest(tHq_sm_Pt_Eff_c_T) << endl;
 kolm_test << "ttH: "<< ttbar_semilep_Pt_Eff_c_T->KolmogorovTest(ttH_Pt_Eff_c_T) << endl;
 kolm_test << "ttbar-semilep: " << ttbar_semilep_Pt_Eff_c_T->KolmogorovTest(ttbar_semilep_Pt_Eff_c_T) << endl;
 kolm_test << "ttbar-dilep: " << ttbar_semilep_Pt_Eff_c_T->KolmogorovTest(ttbar_dilep_Pt_Eff_c_T) << endl;
 kolm_test << "ttbar-inc: " << ttbar_semilep_Pt_Eff_c_T->KolmogorovTest(ttbar_inc_Pt_Eff_c_T) << endl;
 kolm_test << "t-schan: " << ttbar_semilep_Pt_Eff_c_T->KolmogorovTest(t_schan_Pt_Eff_c_T) << endl;
 kolm_test << "t-tchan: " << ttbar_semilep_Pt_Eff_c_T->KolmogorovTest(t_tchan_Pt_Eff_c_T) << endl;
 kolm_test << "t-tWchan: " << ttbar_semilep_Pt_Eff_c_T->KolmogorovTest(t_tWchan_Pt_Eff_c_T) << endl;
 kolm_test << "Wjets: " << ttbar_semilep_Pt_Eff_c_T->KolmogorovTest(Wjets_Pt_Eff_c_T) << endl;
 kolm_test << endl;

 kolm_test << "uds Pt hists"<< endl;
 kolm_test << "tHq-nc: "<< ttbar_semilep_Pt_Eff_uds_T->KolmogorovTest(tHq_nc_Pt_Eff_uds_T) << endl;
 kolm_test << "tHq-sm: "<< ttbar_semilep_Pt_Eff_uds_T->KolmogorovTest(tHq_sm_Pt_Eff_uds_T) << endl;
 kolm_test << "ttH: "<< ttbar_semilep_Pt_Eff_uds_T->KolmogorovTest(ttH_Pt_Eff_uds_T) << endl;
 kolm_test << "ttbar-semilep: " << ttbar_semilep_Pt_Eff_uds_T->KolmogorovTest(ttbar_semilep_Pt_Eff_uds_T) << endl;
 kolm_test << "ttbar-dilep: " << ttbar_semilep_Pt_Eff_uds_T->KolmogorovTest(ttbar_dilep_Pt_Eff_uds_T) << endl;
 kolm_test << "ttbar-inc: " << ttbar_semilep_Pt_Eff_uds_T->KolmogorovTest(ttbar_inc_Pt_Eff_uds_T) << endl;
 kolm_test << "t-schan: " << ttbar_semilep_Pt_Eff_uds_T->KolmogorovTest(t_schan_Pt_Eff_uds_T) << endl;
 kolm_test << "t-tchan: " << ttbar_semilep_Pt_Eff_uds_T->KolmogorovTest(t_tchan_Pt_Eff_uds_T) << endl;
 kolm_test << "t-tWchan: " << ttbar_semilep_Pt_Eff_uds_T->KolmogorovTest(t_tWchan_Pt_Eff_uds_T) << endl;
 kolm_test << "Wjets: " << ttbar_semilep_Pt_Eff_uds_T->KolmogorovTest(Wjets_Pt_Eff_uds_T) << endl;
 kolm_test << endl;

 kolm_test << "g Pt hists"<< endl;
 kolm_test << "tHq-nc: "<< ttbar_semilep_Pt_Eff_g_T->KolmogorovTest(tHq_nc_Pt_Eff_g_T) << endl;
 kolm_test << "tHq-sm: "<< ttbar_semilep_Pt_Eff_g_T->KolmogorovTest(tHq_sm_Pt_Eff_g_T) << endl;
 kolm_test << "ttH: "<< ttbar_semilep_Pt_Eff_g_T->KolmogorovTest(ttH_Pt_Eff_g_T) << endl;
 kolm_test << "ttbar-semilep: " << ttbar_semilep_Pt_Eff_g_T->KolmogorovTest(ttbar_semilep_Pt_Eff_g_T) << endl;
 kolm_test << "ttbar-dilep: " << ttbar_semilep_Pt_Eff_g_T->KolmogorovTest(ttbar_dilep_Pt_Eff_g_T) << endl;
 kolm_test << "ttbar-inc: " << ttbar_semilep_Pt_Eff_g_T->KolmogorovTest(ttbar_inc_Pt_Eff_g_T) << endl;
 kolm_test << "t-schan: " << ttbar_semilep_Pt_Eff_g_T->KolmogorovTest(t_schan_Pt_Eff_g_T) << endl;
 kolm_test << "t-tchan: " << ttbar_semilep_Pt_Eff_g_T->KolmogorovTest(t_tchan_Pt_Eff_g_T) << endl;
 kolm_test << "t-tWchan: " << ttbar_semilep_Pt_Eff_g_T->KolmogorovTest(t_tWchan_Pt_Eff_g_T) << endl;
 kolm_test << "Wjets: " << ttbar_semilep_Pt_Eff_g_T->KolmogorovTest(Wjets_Pt_Eff_g_T) << endl;
 kolm_test << endl;

 kolm_test.close();

 delete c1; delete c2; delete c3; delete c4;
 delete c5; delete c6; delete c7; delete c8;

 gROOT->Reset();

}

void setTDRStyle() {

  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-DR");

  gROOT->SetStyle("Plain");
  gROOT->ForceStyle();

  tdrStyle->SetFrameBorderMode(0);
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetPadBorderMode(0);
  tdrStyle->SetPadBorderMode(0);

  //	tdrStyle->SetFrameColor(0);
  tdrStyle->SetPadColor(0);
  tdrStyle->SetCanvasColor(0);
  tdrStyle->SetStatColor(0);
  tdrStyle->SetFillColor(0);

  tdrStyle->SetPaperSize(20,26);
  //	tdrStyle->SetPadTopMargin(0.08);
  //	tdrStyle->SetPadBottomMargin(0.14);
  tdrStyle->SetPadRightMargin(0.04);
  tdrStyle->SetPadLeftMargin(0.05);
  //	tdrStyle->SetCanvasDefH(800);
  //	tdrStyle->SetCanvasDefW(800);
  //	tdrStyle->SetPadGridX(1);
  //	tdrStyle->SetPadGridY(1);
  tdrStyle->SetPadTickX(1);
  tdrStyle->SetPadTickY(1);

  tdrStyle->SetTextFont(42); //132
  tdrStyle->SetTextSize(0.09);
  tdrStyle->SetLabelFont(42,"xyz");
  tdrStyle->SetTitleFont(42,"xyz");
  tdrStyle->SetLabelSize(0.045,"xyz"); //0.035
  tdrStyle->SetTitleSize(0.045,"xyz");
  tdrStyle->SetTitleOffset(1.5,"y");
    
  tdrStyle->SetTitleX(0.16);
  tdrStyle->SetTitleY(0.93);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(0);
  tdrStyle->SetTitleBorderSize(1);
  tdrStyle->SetTitleFontSize(0.04);
  //	tdrStyle->SetPadTopMargin(0.05);
  //	tdrStyle->SetPadBottomMargin(0.13);
  //	tdrStyle->SetPadLeftMargin(0.14);
  //	tdrStyle->SetPadRightMargin(0.02);

  // use bold lines and markers
  tdrStyle->SetMarkerSize(4);
  tdrStyle->SetHistLineWidth(4);
  tdrStyle->SetLineWidth(2);
  
  tdrStyle->SetOptTitle(kFALSE);
  tdrStyle->SetOptStat(0);

  tdrStyle->cd();

}





