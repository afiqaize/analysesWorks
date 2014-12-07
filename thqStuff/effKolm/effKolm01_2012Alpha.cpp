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

 string binName, inDir, outDir;

 // the name of the bin/event conf used
 binName = "in4hi";

 // input and output directory (updates itself with conf above)
 inDir = "/home/ieeya/Downloads/Part2_BtagEff/root_files/hists_" + binName + "/";
 outDir = "/home/ieeya/Downloads/Part2_BtagEff/img/comProcess/";

 // set up all the canvases and files
 TCanvas *c1 = new TCanvas("c1", "b pT", 200, 10, 1600, 900);
 TCanvas *c2 = new TCanvas("c2", "c pT", 200, 10, 1600, 900);
 TCanvas *c3 = new TCanvas("c3", "uds pT", 200, 10, 1600, 900);
 TCanvas *c4 = new TCanvas("c4", "g pT", 200, 10, 1600, 900);
 TCanvas *c5 = new TCanvas("c5", "b eta", 200, 10, 1600, 900);
 TCanvas *c6 = new TCanvas("c6", "c eta", 200, 10, 1600, 900);
 TCanvas *c7 = new TCanvas("c7", "uds eta", 200, 10, 1600, 900);
 TCanvas *c8 = new TCanvas("c8", "g eta", 200, 10, 1600, 900);

 TFile *f_thq = new TFile((inDir + "thq.root").c_str());
 TFile *f_tth = new TFile((inDir + "tth.root").c_str());
 TFile *f_ttbar = new TFile((inDir + "ttbar.root").c_str());
 TFile *f_ttbar_semilep = new TFile((inDir + "ttbar-semilep.root").c_str());
 TFile *f_ttbar_dilep = new TFile((inDir + "ttbar-dilep.root").c_str());
 TFile *f_t_tchan = new TFile((inDir + "t-tchan.root").c_str());
 TFile *f_t_tWchan = new TFile((inDir + "t-tWchan.root").c_str());
 TFile *f_Wjets = new TFile((inDir + "Wjets.root").c_str());

 // link up all the histograms
 // stacked hists
 THStack *Pt_Eff_b = new THStack("Pt_Eff_b", "Pt_Eff_b");
 THStack *Pt_Eff_c = new THStack("Pt_Eff_c", "Pt_Eff_c");
 THStack *Pt_Eff_uds = new THStack("Pt_Eff_uds", "Pt_Eff_uds");
 THStack *Pt_Eff_g = new THStack("Pt_Eff_g", "Pt_Eff_c");

 THStack *Eta_Eff_b = new THStack("Eta_Eff_b", "Eta_Eff_b");
 THStack *Eta_Eff_c = new THStack("Eta_Eff_c", "Eta_Eff_c");
 THStack *Eta_Eff_uds = new THStack("Eta_Eff_uds", "Eta_Eff_uds");
 THStack *Eta_Eff_g = new THStack("Eta_Eff_g", "Eta_Eff_g");

 // thq
 TH1D *thq_Pt_Eff_b = dynamic_cast<TH1D *>(f_thq->Get("Pt_Eff_b")); TH1D *thq_Eta_Eff_b = dynamic_cast<TH1D *>(f_thq->Get("Eta_Eff_b"));
 TH1D *thq_Pt_Eff_c = dynamic_cast<TH1D *>(f_thq->Get("Pt_Eff_c")); TH1D *thq_Eta_Eff_c = dynamic_cast<TH1D *>(f_thq->Get("Eta_Eff_c"));
 TH1D *thq_Pt_Eff_uds = dynamic_cast<TH1D *>(f_thq->Get("Pt_Eff_uds")); TH1D *thq_Eta_Eff_uds = dynamic_cast<TH1D *>(f_thq->Get("Eta_Eff_uds"));
 TH1D *thq_Pt_Eff_g = dynamic_cast<TH1D *>(f_thq->Get("Pt_Eff_g")); TH1D *thq_Eta_Eff_g = dynamic_cast<TH1D *>(f_thq->Get("Eta_Eff_g"));

 // tth
 TH1D *tth_Pt_Eff_b = dynamic_cast<TH1D *>(f_tth->Get("Pt_Eff_b")); TH1D *tth_Eta_Eff_b = dynamic_cast<TH1D *>(f_tth->Get("Eta_Eff_b"));
 TH1D *tth_Pt_Eff_c = dynamic_cast<TH1D *>(f_tth->Get("Pt_Eff_c")); TH1D *tth_Eta_Eff_c = dynamic_cast<TH1D *>(f_tth->Get("Eta_Eff_c"));
 TH1D *tth_Pt_Eff_uds = dynamic_cast<TH1D *>(f_tth->Get("Pt_Eff_uds")); TH1D *tth_Eta_Eff_uds = dynamic_cast<TH1D *>(f_tth->Get("Eta_Eff_uds"));
 TH1D *tth_Pt_Eff_g = dynamic_cast<TH1D *>(f_tth->Get("Pt_Eff_g")); TH1D *tth_Eta_Eff_g = dynamic_cast<TH1D *>(f_tth->Get("Eta_Eff_g"));

 // ttbar
 TH1D *ttbar_Pt_Eff_b = dynamic_cast<TH1D *>(f_ttbar->Get("Pt_Eff_b")); TH1D *ttbar_Eta_Eff_b = dynamic_cast<TH1D *>(f_ttbar->Get("Eta_Eff_b"));
 TH1D *ttbar_Pt_Eff_c = dynamic_cast<TH1D *>(f_ttbar->Get("Pt_Eff_c")); TH1D *ttbar_Eta_Eff_c = dynamic_cast<TH1D *>(f_ttbar->Get("Eta_Eff_c"));
 TH1D *ttbar_Pt_Eff_uds = dynamic_cast<TH1D *>(f_ttbar->Get("Pt_Eff_uds")); TH1D *ttbar_Eta_Eff_uds = dynamic_cast<TH1D *>(f_ttbar->Get("Eta_Eff_uds"));
 TH1D *ttbar_Pt_Eff_g = dynamic_cast<TH1D *>(f_ttbar->Get("Pt_Eff_g")); TH1D *ttbar_Eta_Eff_g = dynamic_cast<TH1D *>(f_ttbar->Get("Eta_Eff_g"));

 // ttbar-semilep
 TH1D *ttbar_semilep_Pt_Eff_b = dynamic_cast<TH1D *>(f_ttbar_semilep->Get("Pt_Eff_b")); TH1D *ttbar_semilep_Eta_Eff_b = dynamic_cast<TH1D *>(f_ttbar_semilep->Get("Eta_Eff_b"));
 TH1D *ttbar_semilep_Pt_Eff_c = dynamic_cast<TH1D *>(f_ttbar_semilep->Get("Pt_Eff_c")); TH1D *ttbar_semilep_Eta_Eff_c = dynamic_cast<TH1D *>(f_ttbar_semilep->Get("Eta_Eff_c"));
 TH1D *ttbar_semilep_Pt_Eff_uds = dynamic_cast<TH1D *>(f_ttbar_semilep->Get("Pt_Eff_uds")); TH1D *ttbar_semilep_Eta_Eff_uds = dynamic_cast<TH1D *>(f_ttbar_semilep->Get("Eta_Eff_uds"));
 TH1D *ttbar_semilep_Pt_Eff_g = dynamic_cast<TH1D *>(f_ttbar_semilep->Get("Pt_Eff_g")); TH1D *ttbar_semilep_Eta_Eff_g = dynamic_cast<TH1D *>(f_ttbar_semilep->Get("Eta_Eff_g"));

 // ttbar-dilep
 TH1D *ttbar_dilep_Pt_Eff_b = dynamic_cast<TH1D *>(f_ttbar_dilep->Get("Pt_Eff_b")); TH1D *ttbar_dilep_Eta_Eff_b = dynamic_cast<TH1D *>(f_ttbar_dilep->Get("Eta_Eff_b"));
 TH1D *ttbar_dilep_Pt_Eff_c = dynamic_cast<TH1D *>(f_ttbar_dilep->Get("Pt_Eff_c")); TH1D *ttbar_dilep_Eta_Eff_c = dynamic_cast<TH1D *>(f_ttbar_dilep->Get("Eta_Eff_c"));
 TH1D *ttbar_dilep_Pt_Eff_uds = dynamic_cast<TH1D *>(f_ttbar_dilep->Get("Pt_Eff_uds")); TH1D *ttbar_dilep_Eta_Eff_uds = dynamic_cast<TH1D *>(f_ttbar_dilep->Get("Eta_Eff_uds"));
 TH1D *ttbar_dilep_Pt_Eff_g = dynamic_cast<TH1D *>(f_ttbar_dilep->Get("Pt_Eff_g")); TH1D *ttbar_dilep_Eta_Eff_g = dynamic_cast<TH1D *>(f_ttbar_dilep->Get("Eta_Eff_g"));

 // t-tchan
 TH1D *t_tchan_Pt_Eff_b = dynamic_cast<TH1D *>(f_t_tchan->Get("Pt_Eff_b")); TH1D *t_tchan_Eta_Eff_b = dynamic_cast<TH1D *>(f_t_tchan->Get("Eta_Eff_b"));
 TH1D *t_tchan_Pt_Eff_c = dynamic_cast<TH1D *>(f_t_tchan->Get("Pt_Eff_c")); TH1D *t_tchan_Eta_Eff_c = dynamic_cast<TH1D *>(f_t_tchan->Get("Eta_Eff_c"));
 TH1D *t_tchan_Pt_Eff_uds = dynamic_cast<TH1D *>(f_t_tchan->Get("Pt_Eff_uds")); TH1D *t_tchan_Eta_Eff_uds = dynamic_cast<TH1D *>(f_t_tchan->Get("Eta_Eff_uds"));
 TH1D *t_tchan_Pt_Eff_g = dynamic_cast<TH1D *>(f_t_tchan->Get("Pt_Eff_g")); TH1D *t_tchan_Eta_Eff_g = dynamic_cast<TH1D *>(f_t_tchan->Get("Eta_Eff_g"));

 // t-tWchan
 TH1D *t_tWchan_Pt_Eff_b = dynamic_cast<TH1D *>(f_t_tWchan->Get("Pt_Eff_b")); TH1D *t_tWchan_Eta_Eff_b = dynamic_cast<TH1D *>(f_t_tWchan->Get("Eta_Eff_b"));
 TH1D *t_tWchan_Pt_Eff_c = dynamic_cast<TH1D *>(f_t_tWchan->Get("Pt_Eff_c")); TH1D *t_tWchan_Eta_Eff_c = dynamic_cast<TH1D *>(f_t_tWchan->Get("Eta_Eff_c"));
 TH1D *t_tWchan_Pt_Eff_uds = dynamic_cast<TH1D *>(f_t_tWchan->Get("Pt_Eff_uds")); TH1D *t_tWchan_Eta_Eff_uds = dynamic_cast<TH1D *>(f_t_tWchan->Get("Eta_Eff_uds"));
 TH1D *t_tWchan_Pt_Eff_g = dynamic_cast<TH1D *>(f_t_tWchan->Get("Pt_Eff_g")); TH1D *t_tWchan_Eta_Eff_g = dynamic_cast<TH1D *>(f_t_tWchan->Get("Eta_Eff_g"));

 // Wjets
 TH1D *Wjets_Pt_Eff_b = dynamic_cast<TH1D *>(f_Wjets->Get("Pt_Eff_b")); TH1D *Wjets_Eta_Eff_b = dynamic_cast<TH1D *>(f_Wjets->Get("Eta_Eff_b"));
 TH1D *Wjets_Pt_Eff_c = dynamic_cast<TH1D *>(f_Wjets->Get("Pt_Eff_c")); TH1D *Wjets_Eta_Eff_c = dynamic_cast<TH1D *>(f_Wjets->Get("Eta_Eff_c"));
 TH1D *Wjets_Pt_Eff_uds = dynamic_cast<TH1D *>(f_Wjets->Get("Pt_Eff_uds")); TH1D *Wjets_Eta_Eff_uds = dynamic_cast<TH1D *>(f_Wjets->Get("Eta_Eff_uds"));
 TH1D *Wjets_Pt_Eff_g = dynamic_cast<TH1D *>(f_Wjets->Get("Pt_Eff_g")); TH1D *Wjets_Eta_Eff_g = dynamic_cast<TH1D *>(f_Wjets->Get("Eta_Eff_g"));

 // styling (for 1D histos only)
 setTDRStyle();

 // stacks the histogram, one canvas for one flavor
 c1->cd();
 thq_Pt_Eff_b->SetMarkerStyle(1); thq_Pt_Eff_b->SetMarkerColor(1); thq_Pt_Eff_b->SetLineColor(1); Pt_Eff_b->Add(thq_Pt_Eff_b);
 tth_Pt_Eff_b->SetMarkerStyle(2); tth_Pt_Eff_b->SetMarkerColor(2); tth_Pt_Eff_b->SetLineColor(2); Pt_Eff_b->Add(tth_Pt_Eff_b);
 ttbar_Pt_Eff_b->SetMarkerStyle(3); ttbar_Pt_Eff_b->SetMarkerColor(3); ttbar_Pt_Eff_b->SetLineColor(3); Pt_Eff_b->Add(ttbar_Pt_Eff_b);
 ttbar_semilep_Pt_Eff_b->SetMarkerStyle(4); ttbar_semilep_Pt_Eff_b->SetMarkerColor(4); ttbar_semilep_Pt_Eff_b->SetLineColor(4); Pt_Eff_b->Add(ttbar_semilep_Pt_Eff_b);
 ttbar_dilep_Pt_Eff_b->SetMarkerStyle(5); ttbar_dilep_Pt_Eff_b->SetMarkerColor(5); ttbar_dilep_Pt_Eff_b->SetLineColor(5); Pt_Eff_b->Add(ttbar_dilep_Pt_Eff_b);
 t_tchan_Pt_Eff_b->SetMarkerStyle(6); t_tchan_Pt_Eff_b->SetMarkerColor(6); t_tchan_Pt_Eff_b->SetLineColor(6); Pt_Eff_b->Add(t_tchan_Pt_Eff_b);
 t_tWchan_Pt_Eff_b->SetMarkerStyle(7); t_tWchan_Pt_Eff_b->SetMarkerColor(7); t_tWchan_Pt_Eff_b->SetLineColor(7); Pt_Eff_b->Add(t_tWchan_Pt_Eff_b);
 Wjets_Pt_Eff_b->SetMarkerStyle(8); Wjets_Pt_Eff_b->SetMarkerColor(8); Wjets_Pt_Eff_b->SetLineColor(8); Pt_Eff_b->Add(Wjets_Pt_Eff_b);
 Pt_Eff_b->Draw("nostack");
 
 // legends
 TLegend *leg01 = new TLegend(.83, .75, .99, .99);
 leg01->SetHeader("Process");
 leg01->AddEntry(thq_Pt_Eff_b, "thq");
 leg01->AddEntry(tth_Pt_Eff_b, "tth");
 leg01->AddEntry(ttbar_Pt_Eff_b, "ttbar");
 leg01->AddEntry(ttbar_semilep_Pt_Eff_b, "ttbar-semilep");
 leg01->AddEntry(ttbar_dilep_Pt_Eff_b, "ttbar-dilep");
 leg01->AddEntry(t_tchan_Pt_Eff_b, "t-tchan");
 leg01->AddEntry(t_tWchan_Pt_Eff_b, "t-tWchan");
 leg01->AddEntry(Wjets_Pt_Eff_b, "Wjets");
 leg01->Draw();

 c1->SaveAs((outDir + "Pt_Eff_b.png").c_str());

 c2->cd();
 thq_Pt_Eff_c->SetMarkerStyle(1); thq_Pt_Eff_c->SetMarkerColor(1); thq_Pt_Eff_c->SetLineColor(1); Pt_Eff_c->Add(thq_Pt_Eff_c);
 tth_Pt_Eff_c->SetMarkerStyle(2); tth_Pt_Eff_c->SetMarkerColor(2); tth_Pt_Eff_c->SetLineColor(2); Pt_Eff_c->Add(tth_Pt_Eff_c);
 ttbar_Pt_Eff_c->SetMarkerStyle(3); ttbar_Pt_Eff_c->SetMarkerColor(3); ttbar_Pt_Eff_c->SetLineColor(3); Pt_Eff_c->Add(ttbar_Pt_Eff_c);
 ttbar_semilep_Pt_Eff_c->SetMarkerStyle(4); ttbar_semilep_Pt_Eff_c->SetMarkerColor(4); ttbar_semilep_Pt_Eff_c->SetLineColor(4); Pt_Eff_c->Add(ttbar_semilep_Pt_Eff_c);
 ttbar_dilep_Pt_Eff_c->SetMarkerStyle(5); ttbar_dilep_Pt_Eff_c->SetMarkerColor(5); ttbar_dilep_Pt_Eff_c->SetLineColor(5); Pt_Eff_c->Add(ttbar_dilep_Pt_Eff_c);
 t_tchan_Pt_Eff_c->SetMarkerStyle(6); t_tchan_Pt_Eff_c->SetMarkerColor(6); t_tchan_Pt_Eff_c->SetLineColor(6); Pt_Eff_c->Add(t_tchan_Pt_Eff_c);
 t_tWchan_Pt_Eff_c->SetMarkerStyle(7); t_tWchan_Pt_Eff_c->SetMarkerColor(7); t_tWchan_Pt_Eff_c->SetLineColor(7); Pt_Eff_c->Add(t_tWchan_Pt_Eff_c);
 Wjets_Pt_Eff_c->SetMarkerStyle(8); Wjets_Pt_Eff_c->SetMarkerColor(8); Wjets_Pt_Eff_c->SetLineColor(8); Pt_Eff_c->Add(Wjets_Pt_Eff_c);
 Pt_Eff_c->Draw("nostack");

 // legends
 TLegend *leg02 = new TLegend(.83, .75, .99, .99);
 leg02->SetHeader("Process");
 leg02->AddEntry(thq_Pt_Eff_c, "thq");
 leg02->AddEntry(tth_Pt_Eff_c, "tth");
 leg02->AddEntry(ttbar_Pt_Eff_c, "ttbar");
 leg02->AddEntry(ttbar_semilep_Pt_Eff_c, "ttbar-semilep");
 leg02->AddEntry(ttbar_dilep_Pt_Eff_c, "ttbar-dilep");
 leg02->AddEntry(t_tchan_Pt_Eff_c, "t-tchan");
 leg02->AddEntry(t_tWchan_Pt_Eff_c, "t-tWchan");
 leg02->AddEntry(Wjets_Pt_Eff_c, "Wjets");
 leg02->Draw();

 c2->SaveAs((outDir + "Pt_Eff_c.png").c_str());

 c3->cd();
 thq_Pt_Eff_uds->SetMarkerStyle(1); thq_Pt_Eff_uds->SetMarkerColor(1); thq_Pt_Eff_uds->SetLineColor(1); Pt_Eff_uds->Add(thq_Pt_Eff_uds);
 tth_Pt_Eff_uds->SetMarkerStyle(2); tth_Pt_Eff_uds->SetMarkerColor(2); tth_Pt_Eff_uds->SetLineColor(2); Pt_Eff_uds->Add(tth_Pt_Eff_uds);
 ttbar_Pt_Eff_uds->SetMarkerStyle(3); ttbar_Pt_Eff_uds->SetMarkerColor(3); ttbar_Pt_Eff_uds->SetLineColor(3); Pt_Eff_uds->Add(ttbar_Pt_Eff_uds);
 ttbar_semilep_Pt_Eff_uds->SetMarkerStyle(4); ttbar_semilep_Pt_Eff_uds->SetMarkerColor(4); ttbar_semilep_Pt_Eff_uds->SetLineColor(4); Pt_Eff_uds->Add(ttbar_semilep_Pt_Eff_uds);
 ttbar_dilep_Pt_Eff_uds->SetMarkerStyle(5); ttbar_dilep_Pt_Eff_uds->SetMarkerColor(5); ttbar_dilep_Pt_Eff_uds->SetLineColor(5); Pt_Eff_uds->Add(ttbar_dilep_Pt_Eff_uds);
 t_tchan_Pt_Eff_uds->SetMarkerStyle(6); t_tchan_Pt_Eff_uds->SetMarkerColor(6); t_tchan_Pt_Eff_uds->SetLineColor(6); Pt_Eff_uds->Add(t_tchan_Pt_Eff_uds);
 t_tWchan_Pt_Eff_uds->SetMarkerStyle(7); t_tWchan_Pt_Eff_uds->SetMarkerColor(7); t_tWchan_Pt_Eff_uds->SetLineColor(7); Pt_Eff_uds->Add(t_tWchan_Pt_Eff_uds);
 Wjets_Pt_Eff_uds->SetMarkerStyle(8); Wjets_Pt_Eff_uds->SetMarkerColor(8); Wjets_Pt_Eff_uds->SetLineColor(8); Pt_Eff_uds->Add(Wjets_Pt_Eff_uds);
 Pt_Eff_uds->Draw("nostack");

 // legends
 TLegend *leg03 = new TLegend(.83, .75, .99, .99);
 leg03->SetHeader("Process");
 leg03->AddEntry(thq_Pt_Eff_uds, "thq");
 leg03->AddEntry(tth_Pt_Eff_uds, "tth");
 leg03->AddEntry(ttbar_Pt_Eff_uds, "ttbar");
 leg03->AddEntry(ttbar_semilep_Pt_Eff_uds, "ttbar-semilep");
 leg03->AddEntry(ttbar_dilep_Pt_Eff_uds, "ttbar-dilep");
 leg03->AddEntry(t_tchan_Pt_Eff_uds, "t-tchan");
 leg03->AddEntry(t_tWchan_Pt_Eff_uds, "t-tWchan");
 leg03->AddEntry(Wjets_Pt_Eff_uds, "Wjets");
 leg03->Draw();

 c3->SaveAs((outDir + "Pt_Eff_uds.png").c_str());

 c4->cd();
 thq_Pt_Eff_g->SetMarkerStyle(1); thq_Pt_Eff_g->SetMarkerColor(1); thq_Pt_Eff_g->SetLineColor(1); Pt_Eff_g->Add(thq_Pt_Eff_g);
 tth_Pt_Eff_g->SetMarkerStyle(2); tth_Pt_Eff_g->SetMarkerColor(2); tth_Pt_Eff_g->SetLineColor(2); Pt_Eff_g->Add(tth_Pt_Eff_g);
 ttbar_Pt_Eff_g->SetMarkerStyle(3); ttbar_Pt_Eff_g->SetMarkerColor(3); ttbar_Pt_Eff_g->SetLineColor(3); Pt_Eff_g->Add(ttbar_Pt_Eff_g);
 ttbar_semilep_Pt_Eff_g->SetMarkerStyle(4); ttbar_semilep_Pt_Eff_g->SetMarkerColor(4); ttbar_semilep_Pt_Eff_g->SetLineColor(4); Pt_Eff_g->Add(ttbar_semilep_Pt_Eff_g);
 ttbar_dilep_Pt_Eff_g->SetMarkerStyle(5); ttbar_dilep_Pt_Eff_g->SetMarkerColor(5); ttbar_dilep_Pt_Eff_g->SetLineColor(5); Pt_Eff_g->Add(ttbar_dilep_Pt_Eff_g);
 t_tchan_Pt_Eff_g->SetMarkerStyle(6); t_tchan_Pt_Eff_g->SetMarkerColor(6); t_tchan_Pt_Eff_g->SetLineColor(6); Pt_Eff_g->Add(t_tchan_Pt_Eff_g);
 t_tWchan_Pt_Eff_g->SetMarkerStyle(7); t_tWchan_Pt_Eff_g->SetMarkerColor(7); t_tWchan_Pt_Eff_g->SetLineColor(7); Pt_Eff_g->Add(t_tWchan_Pt_Eff_g);
 Wjets_Pt_Eff_g->SetMarkerStyle(8); Wjets_Pt_Eff_g->SetMarkerColor(8); Wjets_Pt_Eff_g->SetLineColor(8); Pt_Eff_g->Add(Wjets_Pt_Eff_g);
 Pt_Eff_g->Draw("nostack");

 // legends
 TLegend *leg04 = new TLegend(.83, .75, .99, .99);
 leg04->SetHeader("Process");
 leg04->AddEntry(thq_Pt_Eff_g, "thq");
 leg04->AddEntry(tth_Pt_Eff_g, "tth");
 leg04->AddEntry(ttbar_Pt_Eff_g, "ttbar");
 leg04->AddEntry(ttbar_semilep_Pt_Eff_g, "ttbar-semilep");
 leg04->AddEntry(ttbar_dilep_Pt_Eff_g, "ttbar-dilep");
 leg04->AddEntry(t_tchan_Pt_Eff_g, "t-tchan");
 leg04->AddEntry(t_tWchan_Pt_Eff_g, "t-tWchan");
 leg04->AddEntry(Wjets_Pt_Eff_g, "Wjets");
 leg04->Draw();

 c4->SaveAs((outDir + "Pt_Eff_g.png").c_str());

 c5->cd();
 thq_Eta_Eff_b->SetMarkerStyle(1); thq_Eta_Eff_b->SetMarkerColor(1); thq_Eta_Eff_b->SetLineColor(1); Eta_Eff_b->Add(thq_Eta_Eff_b);
 tth_Eta_Eff_b->SetMarkerStyle(2); tth_Eta_Eff_b->SetMarkerColor(2); tth_Eta_Eff_b->SetLineColor(2); Eta_Eff_b->Add(tth_Eta_Eff_b);
 ttbar_Eta_Eff_b->SetMarkerStyle(3); ttbar_Eta_Eff_b->SetMarkerColor(3); ttbar_Eta_Eff_b->SetLineColor(3); Eta_Eff_b->Add(ttbar_Eta_Eff_b);
 ttbar_semilep_Eta_Eff_b->SetMarkerStyle(4); ttbar_semilep_Eta_Eff_b->SetMarkerColor(4); ttbar_semilep_Eta_Eff_b->SetLineColor(4); Eta_Eff_b->Add(ttbar_semilep_Eta_Eff_b);
 ttbar_dilep_Eta_Eff_b->SetMarkerStyle(5); ttbar_dilep_Eta_Eff_b->SetMarkerColor(5); ttbar_dilep_Eta_Eff_b->SetLineColor(5); Eta_Eff_b->Add(ttbar_dilep_Eta_Eff_b);
 t_tchan_Eta_Eff_b->SetMarkerStyle(6); t_tchan_Eta_Eff_b->SetMarkerColor(6); t_tchan_Eta_Eff_b->SetLineColor(6); Eta_Eff_b->Add(t_tchan_Eta_Eff_b);
 t_tWchan_Eta_Eff_b->SetMarkerStyle(7); t_tWchan_Eta_Eff_b->SetMarkerColor(7); t_tWchan_Eta_Eff_b->SetLineColor(7); Eta_Eff_b->Add(t_tWchan_Eta_Eff_b);
 Wjets_Eta_Eff_b->SetMarkerStyle(8); Wjets_Eta_Eff_b->SetMarkerColor(8); Wjets_Eta_Eff_b->SetLineColor(8); Eta_Eff_b->Add(Wjets_Eta_Eff_b);
 Eta_Eff_b->Draw("nostack");

 // legends
 TLegend *leg05 = new TLegend(.83, .75, .99, .99);
 leg05->SetHeader("Process");
 leg05->AddEntry(thq_Eta_Eff_b, "thq");
 leg05->AddEntry(tth_Eta_Eff_b, "tth");
 leg05->AddEntry(ttbar_Eta_Eff_b, "ttbar");
 leg05->AddEntry(ttbar_semilep_Eta_Eff_b, "ttbar-semilep");
 leg05->AddEntry(ttbar_dilep_Eta_Eff_b, "ttbar-dilep");
 leg05->AddEntry(t_tchan_Eta_Eff_b, "t-tchan");
 leg05->AddEntry(t_tWchan_Eta_Eff_b, "t-tWchan");
 leg05->AddEntry(Wjets_Eta_Eff_b, "Wjets");
 leg05->Draw();

 c5->SaveAs((outDir + "Eta_Eff_b.png").c_str());

 c6->cd();
 thq_Eta_Eff_c->SetMarkerStyle(1); thq_Eta_Eff_c->SetMarkerColor(1); thq_Eta_Eff_c->SetLineColor(1); Eta_Eff_c->Add(thq_Eta_Eff_c);
 tth_Eta_Eff_c->SetMarkerStyle(2); tth_Eta_Eff_c->SetMarkerColor(2); tth_Eta_Eff_c->SetLineColor(2); Eta_Eff_c->Add(tth_Eta_Eff_c);
 ttbar_Eta_Eff_c->SetMarkerStyle(3); ttbar_Eta_Eff_c->SetMarkerColor(3); ttbar_Eta_Eff_c->SetLineColor(3); Eta_Eff_c->Add(ttbar_Eta_Eff_c);
 ttbar_semilep_Eta_Eff_c->SetMarkerStyle(4); ttbar_semilep_Eta_Eff_c->SetMarkerColor(4); ttbar_semilep_Eta_Eff_c->SetLineColor(4); Eta_Eff_c->Add(ttbar_semilep_Eta_Eff_c);
 ttbar_dilep_Eta_Eff_c->SetMarkerStyle(5); ttbar_dilep_Eta_Eff_c->SetMarkerColor(5); ttbar_dilep_Eta_Eff_c->SetLineColor(5); Eta_Eff_c->Add(ttbar_dilep_Eta_Eff_c);
 t_tchan_Eta_Eff_c->SetMarkerStyle(6); t_tchan_Eta_Eff_c->SetMarkerColor(6); t_tchan_Eta_Eff_c->SetLineColor(6); Eta_Eff_c->Add(t_tchan_Eta_Eff_c);
 t_tWchan_Eta_Eff_c->SetMarkerStyle(7); t_tWchan_Eta_Eff_c->SetMarkerColor(7); t_tWchan_Eta_Eff_c->SetLineColor(7); Eta_Eff_c->Add(t_tWchan_Eta_Eff_c);
 Wjets_Eta_Eff_c->SetMarkerStyle(8); Wjets_Eta_Eff_c->SetMarkerColor(8); Wjets_Eta_Eff_c->SetLineColor(8); Eta_Eff_c->Add(Wjets_Eta_Eff_c);
 Eta_Eff_c->Draw("nostack");

 // legends
 TLegend *leg06 = new TLegend(.83, .75, .99, .99);
 leg06->SetHeader("Process");
 leg06->AddEntry(thq_Eta_Eff_c, "thq");
 leg06->AddEntry(tth_Eta_Eff_c, "tth");
 leg06->AddEntry(ttbar_Eta_Eff_c, "ttbar");
 leg06->AddEntry(ttbar_semilep_Eta_Eff_c, "ttbar-semilep");
 leg06->AddEntry(ttbar_dilep_Eta_Eff_c, "ttbar-dilep");
 leg06->AddEntry(t_tchan_Eta_Eff_c, "t-tchan");
 leg06->AddEntry(t_tWchan_Eta_Eff_c, "t-tWchan");
 leg06->AddEntry(Wjets_Eta_Eff_c, "Wjets");
 leg06->Draw();

 c6->SaveAs((outDir + "Eta_Eff_c.png").c_str());

 c7->cd();
 thq_Eta_Eff_uds->SetMarkerStyle(1); thq_Eta_Eff_uds->SetMarkerColor(1); thq_Eta_Eff_uds->SetLineColor(1); Eta_Eff_uds->Add(thq_Eta_Eff_uds);
 tth_Eta_Eff_uds->SetMarkerStyle(2); tth_Eta_Eff_uds->SetMarkerColor(2); tth_Eta_Eff_uds->SetLineColor(2); Eta_Eff_uds->Add(tth_Eta_Eff_uds);
 ttbar_Eta_Eff_uds->SetMarkerStyle(3); ttbar_Eta_Eff_uds->SetMarkerColor(3); ttbar_Eta_Eff_uds->SetLineColor(3); Eta_Eff_uds->Add(ttbar_Eta_Eff_uds);
 ttbar_semilep_Eta_Eff_uds->SetMarkerStyle(4); ttbar_semilep_Eta_Eff_uds->SetMarkerColor(4); ttbar_semilep_Eta_Eff_uds->SetLineColor(4); Eta_Eff_uds->Add(ttbar_semilep_Eta_Eff_uds);
 ttbar_dilep_Eta_Eff_uds->SetMarkerStyle(5); ttbar_dilep_Eta_Eff_uds->SetMarkerColor(5); ttbar_dilep_Eta_Eff_uds->SetLineColor(5); Eta_Eff_uds->Add(ttbar_dilep_Eta_Eff_uds);
 t_tchan_Eta_Eff_uds->SetMarkerStyle(6); t_tchan_Eta_Eff_uds->SetMarkerColor(6); t_tchan_Eta_Eff_uds->SetLineColor(6); Eta_Eff_uds->Add(t_tchan_Eta_Eff_uds);
 t_tWchan_Eta_Eff_uds->SetMarkerStyle(7); t_tWchan_Eta_Eff_uds->SetMarkerColor(7); t_tWchan_Eta_Eff_uds->SetLineColor(7); Eta_Eff_uds->Add(t_tWchan_Eta_Eff_uds);
 Wjets_Eta_Eff_uds->SetMarkerStyle(8); Wjets_Eta_Eff_uds->SetMarkerColor(8); Wjets_Eta_Eff_uds->SetLineColor(8); Eta_Eff_uds->Add(Wjets_Eta_Eff_uds);
 Eta_Eff_uds->Draw("nostack");

 // legends
 TLegend *leg07 = new TLegend(.83, .75, .99, .99);
 leg07->SetHeader("Process");
 leg07->AddEntry(thq_Eta_Eff_uds, "thq");
 leg07->AddEntry(tth_Eta_Eff_uds, "tth");
 leg07->AddEntry(ttbar_Eta_Eff_uds, "ttbar");
 leg07->AddEntry(ttbar_semilep_Eta_Eff_uds, "ttbar-semilep");
 leg07->AddEntry(ttbar_dilep_Eta_Eff_uds, "ttbar-dilep");
 leg07->AddEntry(t_tchan_Eta_Eff_uds, "t-tchan");
 leg07->AddEntry(t_tWchan_Eta_Eff_uds, "t-tWchan");
 leg07->AddEntry(Wjets_Eta_Eff_uds, "Wjets");
 leg07->Draw();

 c7->SaveAs((outDir + "Eta_Eff_uds.png").c_str());

 c8->cd();
 thq_Eta_Eff_g->SetMarkerStyle(1); thq_Eta_Eff_g->SetMarkerColor(1); thq_Eta_Eff_g->SetLineColor(1); Eta_Eff_g->Add(thq_Eta_Eff_g);
 tth_Eta_Eff_g->SetMarkerStyle(2); tth_Eta_Eff_g->SetMarkerColor(2); tth_Eta_Eff_g->SetLineColor(2); Eta_Eff_g->Add(tth_Eta_Eff_g);
 ttbar_Eta_Eff_g->SetMarkerStyle(3); ttbar_Eta_Eff_g->SetMarkerColor(3); ttbar_Eta_Eff_g->SetLineColor(3); Eta_Eff_g->Add(ttbar_Eta_Eff_g);
 ttbar_semilep_Eta_Eff_g->SetMarkerStyle(4); ttbar_semilep_Eta_Eff_g->SetMarkerColor(4); ttbar_semilep_Eta_Eff_g->SetLineColor(4); Eta_Eff_g->Add(ttbar_semilep_Eta_Eff_g);
 ttbar_dilep_Eta_Eff_g->SetMarkerStyle(5); ttbar_dilep_Eta_Eff_g->SetMarkerColor(5); ttbar_dilep_Eta_Eff_g->SetLineColor(5); Eta_Eff_g->Add(ttbar_dilep_Eta_Eff_g);
 t_tchan_Eta_Eff_g->SetMarkerStyle(6); t_tchan_Eta_Eff_g->SetMarkerColor(6); t_tchan_Eta_Eff_g->SetLineColor(6); Eta_Eff_g->Add(t_tchan_Eta_Eff_g);
 t_tWchan_Eta_Eff_g->SetMarkerStyle(7); t_tWchan_Eta_Eff_g->SetMarkerColor(7); t_tWchan_Eta_Eff_g->SetLineColor(7); Eta_Eff_g->Add(t_tWchan_Eta_Eff_g);
 Wjets_Eta_Eff_g->SetMarkerStyle(8); Wjets_Eta_Eff_g->SetMarkerColor(8); Wjets_Eta_Eff_g->SetLineColor(8); Eta_Eff_g->Add(Wjets_Eta_Eff_g);
 Eta_Eff_g->Draw("nostack");

 // legends
 TLegend *leg08 = new TLegend(.83, .75, .99, .99);
 leg08->SetHeader("Process");
 leg08->AddEntry(thq_Eta_Eff_g, "thq");
 leg08->AddEntry(tth_Eta_Eff_g, "tth");
 leg08->AddEntry(ttbar_Eta_Eff_g, "ttbar");
 leg08->AddEntry(ttbar_semilep_Eta_Eff_g, "ttbar-semilep");
 leg08->AddEntry(ttbar_dilep_Eta_Eff_g, "ttbar-dilep");
 leg08->AddEntry(t_tchan_Eta_Eff_g, "t-tchan");
 leg08->AddEntry(t_tWchan_Eta_Eff_g, "t-tWchan");
 leg08->AddEntry(Wjets_Eta_Eff_g, "Wjets");
 leg08->Draw();

 c8->SaveAs((outDir + "Eta_Eff_g.png").c_str());

 // Do the KS test based on the ttbar-semilep hists
 ofstream kolm_test;
 
 kolm_test.open((outDir + "comProcess.txt").c_str());
 kolm_test<<"Output of TH1::KolmogorovTest, relative to the ttbar_semilep rates"<<endl;
 kolm_test<<endl;
 kolm_test<<"b hists"<<endl;
 kolm_test<<"thq: "<<ttbar_semilep_Pt_Eff_b->KolmogorovTest(thq_Pt_Eff_b)<<endl;
 kolm_test<<"tth: "<<ttbar_semilep_Pt_Eff_b->KolmogorovTest(tth_Pt_Eff_b)<<endl;
 kolm_test<<"ttbar: "<<ttbar_semilep_Pt_Eff_b->KolmogorovTest(ttbar_Pt_Eff_b)<<endl;
 kolm_test<<"ttbar-semilep: "<<ttbar_semilep_Pt_Eff_b->KolmogorovTest(ttbar_semilep_Pt_Eff_b)<<endl;
 kolm_test<<"ttbar-dilep: "<<ttbar_semilep_Pt_Eff_b->KolmogorovTest(ttbar_dilep_Pt_Eff_b)<<endl;
 kolm_test<<"t-tchan: "<<ttbar_semilep_Pt_Eff_b->KolmogorovTest(t_tchan_Pt_Eff_b)<<endl;
 kolm_test<<"t-tWchan: "<<ttbar_semilep_Pt_Eff_b->KolmogorovTest(t_tWchan_Pt_Eff_b)<<endl;
 kolm_test<<"Wjets: "<<ttbar_semilep_Pt_Eff_b->KolmogorovTest(Wjets_Pt_Eff_b)<<endl;
 kolm_test<<endl;
 kolm_test<<"c hists"<<endl;
 kolm_test<<"thq: "<<ttbar_semilep_Pt_Eff_c->KolmogorovTest(thq_Pt_Eff_c)<<endl;
 kolm_test<<"tth: "<<ttbar_semilep_Pt_Eff_c->KolmogorovTest(tth_Pt_Eff_c)<<endl;
 kolm_test<<"ttbar: "<<ttbar_semilep_Pt_Eff_c->KolmogorovTest(ttbar_Pt_Eff_c)<<endl;
 kolm_test<<"ttbar-semilep: "<<ttbar_semilep_Pt_Eff_c->KolmogorovTest(ttbar_semilep_Pt_Eff_c)<<endl;
 kolm_test<<"ttbar-dilep: "<<ttbar_semilep_Pt_Eff_c->KolmogorovTest(ttbar_dilep_Pt_Eff_c)<<endl;
 kolm_test<<"t-tchan: "<<ttbar_semilep_Pt_Eff_c->KolmogorovTest(t_tchan_Pt_Eff_c)<<endl;
 kolm_test<<"t-tWchan: "<<ttbar_semilep_Pt_Eff_c->KolmogorovTest(t_tWchan_Pt_Eff_c)<<endl;
 kolm_test<<"Wjets: "<<ttbar_semilep_Pt_Eff_c->KolmogorovTest(Wjets_Pt_Eff_c)<<endl;
 kolm_test<<endl;
 kolm_test<<"uds hists"<<endl;
 kolm_test<<"thq: "<<ttbar_semilep_Pt_Eff_uds->KolmogorovTest(thq_Pt_Eff_uds)<<endl;
 kolm_test<<"tth: "<<ttbar_semilep_Pt_Eff_uds->KolmogorovTest(tth_Pt_Eff_uds)<<endl;
 kolm_test<<"ttbar: "<<ttbar_semilep_Pt_Eff_uds->KolmogorovTest(ttbar_Pt_Eff_uds)<<endl;
 kolm_test<<"ttbar-semilep: "<<ttbar_semilep_Pt_Eff_uds->KolmogorovTest(ttbar_semilep_Pt_Eff_uds)<<endl;
 kolm_test<<"ttbar-dilep: "<<ttbar_semilep_Pt_Eff_uds->KolmogorovTest(ttbar_dilep_Pt_Eff_uds)<<endl;
 kolm_test<<"t-tchan: "<<ttbar_semilep_Pt_Eff_uds->KolmogorovTest(t_tchan_Pt_Eff_uds)<<endl;
 kolm_test<<"t-tWchan: "<<ttbar_semilep_Pt_Eff_uds->KolmogorovTest(t_tWchan_Pt_Eff_uds)<<endl;
 kolm_test<<"Wjets: "<<ttbar_semilep_Pt_Eff_uds->KolmogorovTest(Wjets_Pt_Eff_uds)<<endl;
 kolm_test<<endl;
 kolm_test<<"g hists"<<endl;
 kolm_test<<"thq: "<<ttbar_semilep_Pt_Eff_g->KolmogorovTest(thq_Pt_Eff_g)<<endl;
 kolm_test<<"tth: "<<ttbar_semilep_Pt_Eff_g->KolmogorovTest(tth_Pt_Eff_g)<<endl;
 kolm_test<<"ttbar: "<<ttbar_semilep_Pt_Eff_g->KolmogorovTest(ttbar_Pt_Eff_g)<<endl;
 kolm_test<<"ttbar-semilep: "<<ttbar_semilep_Pt_Eff_g->KolmogorovTest(ttbar_semilep_Pt_Eff_g)<<endl;
 kolm_test<<"ttbar-dilep: "<<ttbar_semilep_Pt_Eff_g->KolmogorovTest(ttbar_dilep_Pt_Eff_g)<<endl;
 kolm_test<<"t-tchan: "<<ttbar_semilep_Pt_Eff_g->KolmogorovTest(t_tchan_Pt_Eff_g)<<endl;
 kolm_test<<"t-tWchan: "<<ttbar_semilep_Pt_Eff_g->KolmogorovTest(t_tWchan_Pt_Eff_g)<<endl;
 kolm_test<<"Wjets: "<<ttbar_semilep_Pt_Eff_g->KolmogorovTest(Wjets_Pt_Eff_g)<<endl;
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
  tdrStyle->SetMarkerStyle(8);
  tdrStyle->SetHistLineWidth(3);
  tdrStyle->SetLineWidth(1);
  
  tdrStyle->SetOptTitle(kFALSE);
  tdrStyle->SetOptStat(0);

  tdrStyle->cd();

}





