/*** effKolm02.cpp (comBin)
- Kolmogorov-Smirnov goodness of fit test on the eff hists (compare the inclusive and exclusive jet bins)
- Draw the hists for a visual comparison
- Afiq A. Anuar
***/

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

void effKolm02() {

 string inDir, eraName, processName, outDir;

 // data comes from which campaign
 eraName = "2012Bravo";

 // input directory (updates itself with conf above)
 inDir = "/home/ieeya/Downloads/Part2_BTagEff/root_files/" + eraName + "_eff/hists_";

 // choose which process to use [tHq-nc, tHq-sm, ttH, t-schan, t-tchan, t-tWchan, ttbar-inc, ttbar-semilep, ttbar-dilep, Wjets] (effCalc for more)
 processName = "Wjets";

 // output directory
 outDir = "/home/ieeya/Downloads/Part2_BTagEff/img/" + eraName + "_eff/comBin/" + processName + "/";

 // set up all the canvases and files
 TCanvas *c1 = new TCanvas("c1", "b pT", 200, 10, 1600, 900);
 TCanvas *c2 = new TCanvas("c2", "c pT", 200, 10, 1600, 900);
 TCanvas *c3 = new TCanvas("c3", "uds pT", 200, 10, 1600, 900);
 TCanvas *c4 = new TCanvas("c4", "g pT", 200, 10, 1600, 900);
 TCanvas *c5 = new TCanvas("c5", "b eta", 200, 10, 1600, 900);
 TCanvas *c6 = new TCanvas("c6", "c eta", 200, 10, 1600, 900);
 TCanvas *c7 = new TCanvas("c7", "uds eta", 200, 10, 1600, 900);
 TCanvas *c8 = new TCanvas("c8", "g eta", 200, 10, 1600, 900);

 TFile *f_in4 = new TFile((inDir + "in4/" + processName + ".root").c_str());
 TFile *f_ex4 = new TFile((inDir + "ex4/" + processName + ".root").c_str());
 TFile *f_ex5 = new TFile((inDir + "ex5/" + processName + ".root").c_str());
 TFile *f_ex6 = new TFile((inDir + "ex6/" + processName + ".root").c_str());

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

 // in4
 TH1D *in4_Pt_Eff_b_T = dynamic_cast<TH1D *>(f_in4->Get("Pt_Eff_b_T")); TH1D *in4_Eta_Eff_b_T = dynamic_cast<TH1D *>(f_in4->Get("Eta_Eff_b_T"));
 TH1D *in4_Pt_Eff_c_T = dynamic_cast<TH1D *>(f_in4->Get("Pt_Eff_c_T")); TH1D *in4_Eta_Eff_c_T = dynamic_cast<TH1D *>(f_in4->Get("Eta_Eff_c_T"));
 TH1D *in4_Pt_Eff_uds_T = dynamic_cast<TH1D *>(f_in4->Get("Pt_Eff_uds_T")); TH1D *in4_Eta_Eff_uds_T = dynamic_cast<TH1D *>(f_in4->Get("Eta_Eff_uds_T"));
 TH1D *in4_Pt_Eff_g_T = dynamic_cast<TH1D *>(f_in4->Get("Pt_Eff_g_T")); TH1D *in4_Eta_Eff_g_T = dynamic_cast<TH1D *>(f_in4->Get("Eta_Eff_g_T"));

 // ex4
 TH1D *ex4_Pt_Eff_b_T = dynamic_cast<TH1D *>(f_ex4->Get("Pt_Eff_b_T")); TH1D *ex4_Eta_Eff_b_T = dynamic_cast<TH1D *>(f_ex4->Get("Eta_Eff_b_T"));
 TH1D *ex4_Pt_Eff_c_T = dynamic_cast<TH1D *>(f_ex4->Get("Pt_Eff_c_T")); TH1D *ex4_Eta_Eff_c_T = dynamic_cast<TH1D *>(f_ex4->Get("Eta_Eff_c_T"));
 TH1D *ex4_Pt_Eff_uds_T = dynamic_cast<TH1D *>(f_ex4->Get("Pt_Eff_uds_T")); TH1D *ex4_Eta_Eff_uds_T = dynamic_cast<TH1D *>(f_ex4->Get("Eta_Eff_uds_T"));
 TH1D *ex4_Pt_Eff_g_T = dynamic_cast<TH1D *>(f_ex4->Get("Pt_Eff_g_T")); TH1D *ex4_Eta_Eff_g_T = dynamic_cast<TH1D *>(f_ex4->Get("Eta_Eff_g_T"));

 // ex5
 TH1D *ex5_Pt_Eff_b_T = dynamic_cast<TH1D *>(f_ex5->Get("Pt_Eff_b_T")); TH1D *ex5_Eta_Eff_b_T = dynamic_cast<TH1D *>(f_ex5->Get("Eta_Eff_b_T"));
 TH1D *ex5_Pt_Eff_c_T = dynamic_cast<TH1D *>(f_ex5->Get("Pt_Eff_c_T")); TH1D *ex5_Eta_Eff_c_T = dynamic_cast<TH1D *>(f_ex5->Get("Eta_Eff_c_T"));
 TH1D *ex5_Pt_Eff_uds_T = dynamic_cast<TH1D *>(f_ex5->Get("Pt_Eff_uds_T")); TH1D *ex5_Eta_Eff_uds_T = dynamic_cast<TH1D *>(f_ex5->Get("Eta_Eff_uds_T"));
 TH1D *ex5_Pt_Eff_g_T = dynamic_cast<TH1D *>(f_ex5->Get("Pt_Eff_g_T")); TH1D *ex5_Eta_Eff_g_T = dynamic_cast<TH1D *>(f_ex5->Get("Eta_Eff_g_T"));

 // ex6
 TH1D *ex6_Pt_Eff_b_T = dynamic_cast<TH1D *>(f_ex6->Get("Pt_Eff_b_T")); TH1D *ex6_Eta_Eff_b_T = dynamic_cast<TH1D *>(f_ex6->Get("Eta_Eff_b_T"));
 TH1D *ex6_Pt_Eff_c_T = dynamic_cast<TH1D *>(f_ex6->Get("Pt_Eff_c_T")); TH1D *ex6_Eta_Eff_c_T = dynamic_cast<TH1D *>(f_ex6->Get("Eta_Eff_c_T"));
 TH1D *ex6_Pt_Eff_uds_T = dynamic_cast<TH1D *>(f_ex6->Get("Pt_Eff_uds_T")); TH1D *ex6_Eta_Eff_uds_T = dynamic_cast<TH1D *>(f_ex6->Get("Eta_Eff_uds_T"));
 TH1D *ex6_Pt_Eff_g_T = dynamic_cast<TH1D *>(f_ex6->Get("Pt_Eff_g_T")); TH1D *ex6_Eta_Eff_g_T = dynamic_cast<TH1D *>(f_ex6->Get("Eta_Eff_g_T"));

 // styling (for 1D histos only)
 setTDRStyle();

 // stacks the histogram, one canvas for one flavor
 c1->cd();
 in4_Pt_Eff_b_T->SetMarkerStyle(1); in4_Pt_Eff_b_T->SetMarkerColor(1); in4_Pt_Eff_b_T->SetLineColor(1); Pt_Eff_b_T->Add(in4_Pt_Eff_b_T);
 ex4_Pt_Eff_b_T->SetMarkerStyle(2); ex4_Pt_Eff_b_T->SetMarkerColor(2); ex4_Pt_Eff_b_T->SetLineColor(2); Pt_Eff_b_T->Add(ex4_Pt_Eff_b_T);
 ex5_Pt_Eff_b_T->SetMarkerStyle(3); ex5_Pt_Eff_b_T->SetMarkerColor(3); ex5_Pt_Eff_b_T->SetLineColor(3); Pt_Eff_b_T->Add(ex5_Pt_Eff_b_T);
 ex6_Pt_Eff_b_T->SetMarkerStyle(4); ex6_Pt_Eff_b_T->SetMarkerColor(4); ex6_Pt_Eff_b_T->SetLineColor(4); Pt_Eff_b_T->Add(ex6_Pt_Eff_b_T);
 Pt_Eff_b_T->Draw("nostack");
 
 // legends
 TLegend *leg01 = new TLegend(.83, .79, .99, .97);
 leg01->SetHeader("Process");
 leg01->AddEntry(in4_Pt_Eff_b_T, "in4");
 leg01->AddEntry(ex4_Pt_Eff_b_T, "ex4");
 leg01->AddEntry(ex5_Pt_Eff_b_T, "ex5");
 leg01->AddEntry(ex6_Pt_Eff_b_T, "ex6");
 leg01->Draw();

 c1->SaveAs((outDir + processName + "_Pt_Eff_b_T.png").c_str());
 c1->SaveAs((outDir + processName + "_Pt_Eff_b_T.pdf").c_str());

 c2->cd();
 in4_Pt_Eff_c_T->SetMarkerStyle(1); in4_Pt_Eff_c_T->SetMarkerColor(1); in4_Pt_Eff_c_T->SetLineColor(1); Pt_Eff_c_T->Add(in4_Pt_Eff_c_T);
 ex4_Pt_Eff_c_T->SetMarkerStyle(2); ex4_Pt_Eff_c_T->SetMarkerColor(2); ex4_Pt_Eff_c_T->SetLineColor(2); Pt_Eff_c_T->Add(ex4_Pt_Eff_c_T);
 ex5_Pt_Eff_c_T->SetMarkerStyle(3); ex5_Pt_Eff_c_T->SetMarkerColor(3); ex5_Pt_Eff_c_T->SetLineColor(3); Pt_Eff_c_T->Add(ex5_Pt_Eff_c_T);
 ex6_Pt_Eff_c_T->SetMarkerStyle(4); ex6_Pt_Eff_c_T->SetMarkerColor(4); ex6_Pt_Eff_c_T->SetLineColor(4); Pt_Eff_c_T->Add(ex6_Pt_Eff_c_T);
 Pt_Eff_c_T->Draw("nostack");

 // legends
 TLegend *leg02 = new TLegend(.83, .79, .99, .97);
 leg02->SetHeader("Process");
 leg02->AddEntry(in4_Pt_Eff_c_T, "in4");
 leg02->AddEntry(ex4_Pt_Eff_c_T, "ex4");
 leg02->AddEntry(ex5_Pt_Eff_c_T, "ex5");
 leg02->AddEntry(ex6_Pt_Eff_c_T, "ex6");
 leg02->Draw();

 c2->SaveAs((outDir + processName + "_Pt_Eff_c_T.png").c_str());
 c2->SaveAs((outDir + processName + "_Pt_Eff_c_T.pdf").c_str());

 c3->cd();
 in4_Pt_Eff_uds_T->SetMarkerStyle(1); in4_Pt_Eff_uds_T->SetMarkerColor(1); in4_Pt_Eff_uds_T->SetLineColor(1); Pt_Eff_uds_T->Add(in4_Pt_Eff_uds_T);
 ex4_Pt_Eff_uds_T->SetMarkerStyle(2); ex4_Pt_Eff_uds_T->SetMarkerColor(2); ex4_Pt_Eff_uds_T->SetLineColor(2); Pt_Eff_uds_T->Add(ex4_Pt_Eff_uds_T);
 ex5_Pt_Eff_uds_T->SetMarkerStyle(3); ex5_Pt_Eff_uds_T->SetMarkerColor(3); ex5_Pt_Eff_uds_T->SetLineColor(3); Pt_Eff_uds_T->Add(ex5_Pt_Eff_uds_T);
 ex6_Pt_Eff_uds_T->SetMarkerStyle(4); ex6_Pt_Eff_uds_T->SetMarkerColor(4); ex6_Pt_Eff_uds_T->SetLineColor(4); Pt_Eff_uds_T->Add(ex6_Pt_Eff_uds_T);
 Pt_Eff_uds_T->Draw("nostack");

 // legends
 TLegend *leg03 = new TLegend(.83, .79, .99, .97);
 leg03->SetHeader("Process");
 leg03->AddEntry(in4_Pt_Eff_uds_T, "in4");
 leg03->AddEntry(ex4_Pt_Eff_uds_T, "ex4");
 leg03->AddEntry(ex5_Pt_Eff_uds_T, "ex5");
 leg03->AddEntry(ex6_Pt_Eff_uds_T, "ex6");
 leg03->Draw();

 c3->SaveAs((outDir + processName + "_Pt_Eff_uds_T.png").c_str());
 c3->SaveAs((outDir + processName + "_Pt_Eff_uds_T.pdf").c_str());

 c4->cd();
 in4_Pt_Eff_g_T->SetMarkerStyle(1); in4_Pt_Eff_g_T->SetMarkerColor(1); in4_Pt_Eff_g_T->SetLineColor(1); Pt_Eff_g_T->Add(in4_Pt_Eff_g_T);
 ex4_Pt_Eff_g_T->SetMarkerStyle(2); ex4_Pt_Eff_g_T->SetMarkerColor(2); ex4_Pt_Eff_g_T->SetLineColor(2); Pt_Eff_g_T->Add(ex4_Pt_Eff_g_T);
 ex5_Pt_Eff_g_T->SetMarkerStyle(3); ex5_Pt_Eff_g_T->SetMarkerColor(3); ex5_Pt_Eff_g_T->SetLineColor(3); Pt_Eff_g_T->Add(ex5_Pt_Eff_g_T);
 ex6_Pt_Eff_g_T->SetMarkerStyle(4); ex6_Pt_Eff_g_T->SetMarkerColor(4); ex6_Pt_Eff_g_T->SetLineColor(4); Pt_Eff_g_T->Add(ex6_Pt_Eff_g_T);
 Pt_Eff_g_T->Draw("nostack");

 // legends
 TLegend *leg04 = new TLegend(.83, .79, .99, .97);
 leg04->SetHeader("Process");
 leg04->AddEntry(in4_Pt_Eff_g_T, "in4");
 leg04->AddEntry(ex4_Pt_Eff_g_T, "ex4");
 leg04->AddEntry(ex5_Pt_Eff_g_T, "ex5");
 leg04->AddEntry(ex6_Pt_Eff_g_T, "ex6");
 leg04->Draw();

 c4->SaveAs((outDir + processName + "_Pt_Eff_g_T.png").c_str());
 c4->SaveAs((outDir + processName + "_Pt_Eff_g_T.pdf").c_str());

 c5->cd();
 in4_Eta_Eff_b_T->SetMarkerStyle(1); in4_Eta_Eff_b_T->SetMarkerColor(1); in4_Eta_Eff_b_T->SetLineColor(1); Eta_Eff_b_T->Add(in4_Eta_Eff_b_T);
 ex4_Eta_Eff_b_T->SetMarkerStyle(2); ex4_Eta_Eff_b_T->SetMarkerColor(2); ex4_Eta_Eff_b_T->SetLineColor(2); Eta_Eff_b_T->Add(ex4_Eta_Eff_b_T);
 ex5_Eta_Eff_b_T->SetMarkerStyle(3); ex5_Eta_Eff_b_T->SetMarkerColor(3); ex5_Eta_Eff_b_T->SetLineColor(3); Eta_Eff_b_T->Add(ex5_Eta_Eff_b_T);
 ex6_Eta_Eff_b_T->SetMarkerStyle(4); ex6_Eta_Eff_b_T->SetMarkerColor(4); ex6_Eta_Eff_b_T->SetLineColor(4); Eta_Eff_b_T->Add(ex6_Eta_Eff_b_T);
 Eta_Eff_b_T->Draw("nostack");

 // legends
 TLegend *leg05 = new TLegend(.83, .79, .99, .97);
 leg05->SetHeader("Process");
 leg05->AddEntry(in4_Eta_Eff_b_T, "in4");
 leg05->AddEntry(ex4_Eta_Eff_b_T, "ex4");
 leg05->AddEntry(ex5_Eta_Eff_b_T, "ex5");
 leg05->AddEntry(ex6_Eta_Eff_b_T, "ex6");
 leg05->Draw();

 c5->SaveAs((outDir + processName + "_Eta_Eff_b_T.png").c_str());
 c5->SaveAs((outDir + processName + "_Eta_Eff_b_T.pdf").c_str());

 c6->cd();
 in4_Eta_Eff_c_T->SetMarkerStyle(1); in4_Eta_Eff_c_T->SetMarkerColor(1); in4_Eta_Eff_c_T->SetLineColor(1); Eta_Eff_c_T->Add(in4_Eta_Eff_c_T);
 ex4_Eta_Eff_c_T->SetMarkerStyle(2); ex4_Eta_Eff_c_T->SetMarkerColor(2); ex4_Eta_Eff_c_T->SetLineColor(2); Eta_Eff_c_T->Add(ex4_Eta_Eff_c_T);
 ex5_Eta_Eff_c_T->SetMarkerStyle(3); ex5_Eta_Eff_c_T->SetMarkerColor(3); ex5_Eta_Eff_c_T->SetLineColor(3); Eta_Eff_c_T->Add(ex5_Eta_Eff_c_T);
 ex6_Eta_Eff_c_T->SetMarkerStyle(4); ex6_Eta_Eff_c_T->SetMarkerColor(4); ex6_Eta_Eff_c_T->SetLineColor(4); Eta_Eff_c_T->Add(ex6_Eta_Eff_c_T);
 Eta_Eff_c_T->Draw("nostack");

 // legends
 TLegend *leg06 = new TLegend(.83, .79, .99, .97);
 leg06->SetHeader("Process");
 leg06->AddEntry(in4_Eta_Eff_c_T, "in4");
 leg06->AddEntry(ex4_Eta_Eff_c_T, "ex4");
 leg06->AddEntry(ex5_Eta_Eff_c_T, "ex5");
 leg06->AddEntry(ex6_Eta_Eff_c_T, "ex6");
 leg06->Draw();

 c6->SaveAs((outDir + processName + "_Eta_Eff_c_T.png").c_str());
 c6->SaveAs((outDir + processName + "_Eta_Eff_c_T.pdf").c_str());

 c7->cd();
 in4_Eta_Eff_uds_T->SetMarkerStyle(1); in4_Eta_Eff_uds_T->SetMarkerColor(1); in4_Eta_Eff_uds_T->SetLineColor(1); Eta_Eff_uds_T->Add(in4_Eta_Eff_uds_T);
 ex4_Eta_Eff_uds_T->SetMarkerStyle(2); ex4_Eta_Eff_uds_T->SetMarkerColor(2); ex4_Eta_Eff_uds_T->SetLineColor(2); Eta_Eff_uds_T->Add(ex4_Eta_Eff_uds_T);
 ex5_Eta_Eff_uds_T->SetMarkerStyle(3); ex5_Eta_Eff_uds_T->SetMarkerColor(3); ex5_Eta_Eff_uds_T->SetLineColor(3); Eta_Eff_uds_T->Add(ex5_Eta_Eff_uds_T);
 ex6_Eta_Eff_uds_T->SetMarkerStyle(4); ex6_Eta_Eff_uds_T->SetMarkerColor(4); ex6_Eta_Eff_uds_T->SetLineColor(4); Eta_Eff_uds_T->Add(ex6_Eta_Eff_uds_T);
 Eta_Eff_uds_T->Draw("nostack");

 // legends
 TLegend *leg07 = new TLegend(.83, .79, .99, .97);
 leg07->SetHeader("Process");
 leg07->AddEntry(in4_Eta_Eff_uds_T, "in4");
 leg07->AddEntry(ex4_Eta_Eff_uds_T, "ex4");
 leg07->AddEntry(ex5_Eta_Eff_uds_T, "ex5");
 leg07->AddEntry(ex6_Eta_Eff_uds_T, "ex6");
 leg07->Draw();

 c7->SaveAs((outDir + processName + "_Eta_Eff_uds_T.png").c_str());
 c7->SaveAs((outDir + processName + "_Eta_Eff_uds_T.pdf").c_str());

 c8->cd();
 in4_Eta_Eff_g_T->SetMarkerStyle(1); in4_Eta_Eff_g_T->SetMarkerColor(1); in4_Eta_Eff_g_T->SetLineColor(1); Eta_Eff_g_T->Add(in4_Eta_Eff_g_T);
 ex4_Eta_Eff_g_T->SetMarkerStyle(2); ex4_Eta_Eff_g_T->SetMarkerColor(2); ex4_Eta_Eff_g_T->SetLineColor(2); Eta_Eff_g_T->Add(ex4_Eta_Eff_g_T);
 ex5_Eta_Eff_g_T->SetMarkerStyle(3); ex5_Eta_Eff_g_T->SetMarkerColor(3); ex5_Eta_Eff_g_T->SetLineColor(3); Eta_Eff_g_T->Add(ex5_Eta_Eff_g_T);
 ex6_Eta_Eff_g_T->SetMarkerStyle(4); ex6_Eta_Eff_g_T->SetMarkerColor(4); ex6_Eta_Eff_g_T->SetLineColor(4); Eta_Eff_g_T->Add(ex6_Eta_Eff_g_T);
 Eta_Eff_g_T->Draw("nostack");

 // legends
 TLegend *leg08 = new TLegend(.83, .79, .99, .97);
 leg08->SetHeader("Process");
 leg08->AddEntry(in4_Eta_Eff_g_T, "in4");
 leg08->AddEntry(ex4_Eta_Eff_g_T, "ex4");
 leg08->AddEntry(ex5_Eta_Eff_g_T, "ex5");
 leg08->AddEntry(ex6_Eta_Eff_g_T, "ex6");
 leg08->Draw();

 c8->SaveAs((outDir + processName + "_Eta_Eff_g_T.png").c_str());
 c8->SaveAs((outDir + processName + "_Eta_Eff_g_T.pdf").c_str());

 // Do the KS test based on the ttbar-semilep hists
 ofstream kolm_test;
 
 kolm_test.open((outDir + processName + "_comBin.txt").c_str());
 kolm_test<<"Output of TH1::KolmogorovTest, relative to the in4 hists"<<endl;
 kolm_test<<endl;
 kolm_test<<"b hists"<<endl;
 kolm_test<<"in4: "<<in4_Pt_Eff_b_T->KolmogorovTest(in4_Pt_Eff_b_T)<<endl;
 kolm_test<<"ex4: "<<in4_Pt_Eff_b_T->KolmogorovTest(ex4_Pt_Eff_b_T)<<endl;
 kolm_test<<"ex5: "<<in4_Pt_Eff_b_T->KolmogorovTest(ex5_Pt_Eff_b_T)<<endl;
 kolm_test<<"ex6: "<<in4_Pt_Eff_b_T->KolmogorovTest(ex6_Pt_Eff_b_T)<<endl;
 kolm_test<<endl;
 kolm_test<<"c hists"<<endl;
 kolm_test<<"in4: "<<in4_Pt_Eff_c_T->KolmogorovTest(in4_Pt_Eff_c_T)<<endl;
 kolm_test<<"ex4: "<<in4_Pt_Eff_c_T->KolmogorovTest(ex4_Pt_Eff_c_T)<<endl;
 kolm_test<<"ex5: "<<in4_Pt_Eff_c_T->KolmogorovTest(ex5_Pt_Eff_c_T)<<endl;
 kolm_test<<"ex6: "<<in4_Pt_Eff_c_T->KolmogorovTest(ex6_Pt_Eff_c_T)<<endl;
 kolm_test<<endl;
 kolm_test<<"uds hists"<<endl;
 kolm_test<<"in4: "<<in4_Pt_Eff_uds_T->KolmogorovTest(in4_Pt_Eff_uds_T)<<endl;
 kolm_test<<"ex4: "<<in4_Pt_Eff_uds_T->KolmogorovTest(ex4_Pt_Eff_uds_T)<<endl;
 kolm_test<<"ex5: "<<in4_Pt_Eff_uds_T->KolmogorovTest(ex5_Pt_Eff_uds_T)<<endl;
 kolm_test<<"ex6: "<<in4_Pt_Eff_uds_T->KolmogorovTest(ex6_Pt_Eff_uds_T)<<endl;
 kolm_test<<endl;
 kolm_test<<"g hists"<<endl;
 kolm_test<<"in4: "<<in4_Pt_Eff_g_T->KolmogorovTest(in4_Pt_Eff_g_T)<<endl;
 kolm_test<<"ex4: "<<in4_Pt_Eff_g_T->KolmogorovTest(ex4_Pt_Eff_g_T)<<endl;
 kolm_test<<"ex5: "<<in4_Pt_Eff_g_T->KolmogorovTest(ex5_Pt_Eff_g_T)<<endl;
 kolm_test<<"ex6: "<<in4_Pt_Eff_g_T->KolmogorovTest(ex6_Pt_Eff_g_T)<<endl;
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
