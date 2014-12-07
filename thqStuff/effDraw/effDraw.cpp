/*** effDraw.cpp
- plots the things effCalc combined together and saves them as png and pdf files
- execute directly from ROOT
- automatic folder creation seems to require promoting this to a full C++ program instead of a ROOT macro...
- Afiq A. Anuar
***/

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

void effDraw() {

 string binName, eraName, inDir, processName, outDir;

 // the name of the bin/event conf used
 binName = "in4";

 // data comes from which campaign
 eraName = "2012Bravo";

 // input directory (updates itself with conf above)
 inDir = "/home/ieeya/Downloads/Part2_BTagEff/root_files/" + eraName + "_eff/hists_" + binName + "/";

 // choose which process to use [tHq-nc, tHq-sm, ttH, t-tchan, t-tWchan, ttbar, ttbar-semilep, ttbar-dilep, Wjets] (effCalc for more)
 processName = "ttbar-inc";

 // upper scale for 2D efficiency plots. .6 for CSVT
 Float_t maxEff1 = .6, maxEff2 = .6;

 // output directory
 outDir = "/home/ieeya/Downloads/Part2_BTagEff/img/" + eraName + "_eff/" + binName + "/" + processName + "/";

 // number of bins (for mean efficiency definition) [stdBin = 15 pT 4 eta] [Dan-ext = 16 pT 4 eta] [Dan-extsym = 16 pT 8 eta]
 Int_t ptBin = 16, etaBin = 8;

 TCanvas *c1 = new TCanvas("c1","pT", 200, 10, 1600, 900);
 TCanvas *c2 = new TCanvas("c2","eta", 200, 10, 1600, 900);
 TCanvas *c3 = new TCanvas("c3","2D b", 200, 10, 1600, 900);
 TCanvas *c4 = new TCanvas("c4","2D c", 200, 10, 1600, 900);
 TCanvas *c5 = new TCanvas("c5","2D uds", 200, 10, 1600, 900);
 TCanvas *c6 = new TCanvas("c6","2D g", 200, 10, 1600, 900);

 TFile *f = new TFile((inDir + processName + ".root").c_str());

 c3->cd();
 PtEta_Eff_b_T->GetZaxis()->SetRangeUser(0., maxEff2); PtEta_Eff_b_T->SetStats(false);
 PtEta_Eff_b_T->Draw("PCOLZ");
 c3->SaveAs((outDir + binName + "_" + processName + "_PtEta_Eff_b_T.png").c_str());
 c3->SaveAs((outDir + binName + "_" + processName + "_PtEta_Eff_b_T.pdf").c_str());

 c4->cd();
 PtEta_Eff_c_T->GetZaxis()->SetRangeUser(0., maxEff2); PtEta_Eff_c_T->SetStats(false);
 PtEta_Eff_c_T->Draw("PCOLZ");
 c4->SaveAs((outDir + binName + "_" + processName + "_PtEta_Eff_c_T.png").c_str());
 c4->SaveAs((outDir + binName + "_" + processName + "_PtEta_Eff_c_T.pdf").c_str());

 c5->cd();
 PtEta_Eff_uds_T->GetZaxis()->SetRangeUser(0., maxEff2); PtEta_Eff_uds_T->SetStats(false);
 PtEta_Eff_uds_T->Draw("PCOLZ");
 c5->SaveAs((outDir + binName + "_" + processName + "_PtEta_Eff_uds_T.png").c_str());
 c5->SaveAs((outDir + binName + "_" + processName + "_PtEta_Eff_uds_T.pdf").c_str());

 c6->cd();
 PtEta_Eff_g_T->GetZaxis()->SetRangeUser(0., maxEff2); PtEta_Eff_g_T->SetStats(false);
 PtEta_Eff_g_T->Draw("PCOLZ");
 c6->SaveAs((outDir + binName + "_" + processName + "_PtEta_Eff_g_T.png").c_str());
 c6->SaveAs((outDir + binName + "_" + processName + "_PtEta_Eff_g_T.pdf").c_str());

 // Styling (for 1D histos only)
 setTDRStyle();

 ofstream mean_eff;
 mean_eff.open((outDir + binName + "_" + processName + "_Eff.txt").c_str());

 mean_eff<<processName<<" Eff"<<endl;
 mean_eff<<endl;
 mean_eff<<processName<<" b pt mean =  "<<Pt_Eff_b_T->Integral() / ptBin<<endl;
 mean_eff<<processName<<" c pt mean =  "<<Pt_Eff_c_T->Integral() / ptBin<<endl;
 mean_eff<<processName<<" uds pt mean =  "<<Pt_Eff_uds_T->Integral() / ptBin<<endl;
 mean_eff<<processName<<" g pt mean =  "<<Pt_Eff_g_T->Integral() / ptBin<<endl;
 mean_eff<<endl;
 mean_eff<<processName<<" b eta mean =  "<<Eta_Eff_b_T->Integral() / etaBin<<endl;
 mean_eff<<processName<<" c eta mean =  "<<Eta_Eff_c_T->Integral() / etaBin<<endl;
 mean_eff<<processName<<" uds eta mean =  "<<Eta_Eff_uds_T->Integral() / etaBin<<endl;
 mean_eff<<processName<<" g eta mean =  "<<Eta_Eff_g_T->Integral() / etaBin<<endl;

 mean_eff.close();

 // Testing out THStack
 THStack *Pt_Eff = new THStack("Pt_Eff", "Pt_Eff");
 THStack *Eta_Eff = new THStack("Eta_Eff", "Eta_Eff");

 // Histogram scalers (update the legends as well)
 Float_t c_scale = 2., uds_scale = 10., g_scale = 10.;

 c1->cd();

 // When y-range needs to be uniform
 Pt_Eff_b_T->GetYaxis()->SetRangeUser(0., maxEff1); Pt_Eff_b_T->SetStats(false);
 Pt_Eff_b_T->SetMarkerStyle(2); Pt_Eff_b_T->SetMarkerColor(2); Pt_Eff_b_T->SetLineColor(2); Pt_Eff_b_T->Draw();
 Pt_Eff_c_T->Scale(c_scale); Pt_Eff_c_T->SetMarkerStyle(3); Pt_Eff_c_T->SetMarkerColor(3); Pt_Eff_c_T->SetLineColor(3); Pt_Eff_c_T->Draw("same");
 Pt_Eff_uds_T->Scale(uds_scale); Pt_Eff_uds_T->SetMarkerStyle(4); Pt_Eff_uds_T->SetMarkerColor(4); Pt_Eff_uds_T->SetLineColor(4); Pt_Eff_uds_T->Draw("same");
 Pt_Eff_g_T->Scale(g_scale); Pt_Eff_g_T->SetMarkerStyle(5); Pt_Eff_g_T->SetMarkerColor(5); Pt_Eff_g_T->SetLineColor(5); Pt_Eff_g_T->Draw("same");

 // For easier stacking
 /*Pt_Eff_b_T->SetMarkerStyle(2); Pt_Eff_b_T->SetMarkerColor(2); Pt_Eff_b_T->SetLineColor(2); Pt_Eff->Add(Pt_Eff_b_T);
 Pt_Eff_c_T->Scale(c_scale); Pt_Eff_c_T->SetMarkerStyle(3); Pt_Eff_c_T->SetMarkerColor(3); Pt_Eff_c_T->SetLineColor(3); Pt_Eff->Add(Pt_Eff_c_T);
 Pt_Eff_uds_T->Scale(uds_scale); Pt_Eff_uds_T->SetMarkerStyle(4); Pt_Eff_uds_T->SetMarkerColor(4); Pt_Eff_uds_T->SetLineColor(4); Pt_Eff->Add(Pt_Eff_uds_T);
 Pt_Eff_g_T->Scale(g_scale); Pt_Eff_g_T->SetMarkerStyle(5); Pt_Eff_g_T->SetMarkerColor(5); Pt_Eff_g_T->SetLineColor(5); Pt_Eff->Add(Pt_Eff_g_T);
 Pt_Eff->Draw("nostack");*/

 TLegend *leg01 = new TLegend(.83, .79, .99, .97);
 leg01->SetHeader("Jet Flavors");
 leg01->AddEntry(Pt_Eff_b_T, "b");
 leg01->AddEntry(Pt_Eff_c_T, "c x 2.");
 leg01->AddEntry(Pt_Eff_uds_T, "uds x 10.");
 leg01->AddEntry(Pt_Eff_g_T, "g x 10.");
 leg01->Draw();

 c1->SaveAs((outDir + binName + "_" + processName + "_Pt_Eff.png").c_str());
 c1->SaveAs((outDir + binName + "_" + processName + "_Pt_Eff.pdf").c_str());

 c2->cd();

 // When y-range needs to be uniform
 Eta_Eff_b_T->GetYaxis()->SetRangeUser(0., maxEff1); Eta_Eff_b_T->SetStats(false);
 Eta_Eff_b_T->SetMarkerStyle(2); Eta_Eff_b_T->SetMarkerColor(2); Eta_Eff_b_T->SetLineColor(2); Eta_Eff_b_T->Draw();
 Eta_Eff_c_T->Scale(c_scale); Eta_Eff_c_T->SetMarkerStyle(3); Eta_Eff_c_T->SetMarkerColor(3); Eta_Eff_c_T->SetLineColor(3); Eta_Eff_c_T->Draw("same");
 Eta_Eff_uds_T->Scale(uds_scale); Eta_Eff_uds_T->SetMarkerStyle(4); Eta_Eff_uds_T->SetMarkerColor(4); Eta_Eff_uds_T->SetLineColor(4); Eta_Eff_uds_T->Draw("same");
 Eta_Eff_g_T->Scale(g_scale); Eta_Eff_g_T->SetMarkerStyle(5); Eta_Eff_g_T->SetMarkerColor(5); Eta_Eff_g_T->SetLineColor(5); Eta_Eff_g_T->Draw("same");

 // For easier stacking
 /*Eta_Eff_b_T->SetMarkerStyle(2); Eta_Eff_b_T->SetMarkerColor(2); Eta_Eff_b_T->SetLineColor(2); Eta_Eff->Add(Eta_Eff_b_T);
 Eta_Eff_c_T->Scale(c_scale); Eta_Eff_c_T->SetMarkerStyle(3); Eta_Eff_c_T->SetMarkerColor(3); Eta_Eff_c_T->SetLineColor(3); Eta_Eff->Add(Eta_Eff_c_T);
 Eta_Eff_uds_T->Scale(uds_scale); Eta_Eff_uds_T->SetMarkerStyle(4); Eta_Eff_uds_T->SetMarkerColor(4); Eta_Eff_uds_T->SetLineColor(4); Eta_Eff->Add(Eta_Eff_uds_T);
 Eta_Eff_g_T->Scale(g_scale); Eta_Eff_g_T->SetMarkerStyle(5); Eta_Eff_g_T->SetMarkerColor(5); Eta_Eff_g_T->SetLineColor(5); Eta_Eff->Add(Eta_Eff_g_T);
 Eta_Eff->Draw("nostack");*/

 TLegend *leg02 = new TLegend(.83, .79, .99, .97);
 leg02->SetHeader("Jet Flavors");
 leg02->AddEntry(Eta_Eff_b_T, "b");
 leg02->AddEntry(Eta_Eff_c_T, "c x 2.");
 leg02->AddEntry(Eta_Eff_uds_T, "uds x 10.");
 leg02->AddEntry(Eta_Eff_g_T, "g x 10.");
 leg02->Draw();

 c2->SaveAs((outDir + binName + "_" + processName + "_Eta_Eff.png").c_str());
 c2->SaveAs((outDir + binName + "_" + processName + "_Eta_Eff.pdf").c_str());

 delete c1; delete c2; delete c3;
 delete c4; delete c5; delete c6;

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
