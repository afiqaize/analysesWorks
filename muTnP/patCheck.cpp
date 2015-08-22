/*** plotHist.cpp
- grab 2 histograms from files, divide them and plot the resulting
- save in another file
- included a way to do two at once
***/

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include <TFile.h>
#include <TH2.h>
#include <TH1.h>
#include <TH1D.h>

using namespace std;

void patCheck() {

  gStyle->SetOptStat(0);

  // names and such
  string inDir, inFile, inFile02, numHist01, denHist01, numHist02, denHist02, numHist03, denHist03, numHist04, denHist04;

  inDir = "/home/ieeya/Downloads/t_schan/Part1_TagProbe/rootfiles/pre7/";

  // specify input and output files, 01 is numerator, 02 is denominator
  // same for 03, 04 etc

  inFile = inDir + "schan_hist.root";

  numHist01 = "drawHist/ptMuon_patPass";
  denHist01 = "drawHist/ptMuon_pat";

  numHist02 = "drawHist/etaMuon_patPass";
  denHist02 = "drawHist/etaMuon_pat";

  numHist03 = "drawHist/nJet_patPass";
  denHist03 = "drawHist/nJet_pat";

  numHist04 = "drawHist/nTag_patPass";
  denHist04 = "drawHist/nTag_pat";

  TFile *inPut = new TFile(inFile.c_str());

  // ---------------------------------------- //

  // create the histograms
  TH1::SetDefaultSumw2(true);

  TH1D *inNum01 = dynamic_cast<TH1D *>(inPut->Get(numHist01.c_str()));
  inNum01->SetNameTitle("", "");

  TH1D *inDen01 = dynamic_cast<TH1D *>(inPut->Get(denHist01.c_str()));
  inDen01->SetNameTitle("", "");

  TH1D *inNum02 = dynamic_cast<TH1D *>(inPut->Get(numHist02.c_str()));
  inNum02->SetNameTitle("", "");

  TH1D *inDen02 = dynamic_cast<TH1D *>(inPut->Get(denHist02.c_str()));
  inDen02->SetNameTitle("", "");

  TH1D *inNum03 = dynamic_cast<TH1D *>(inPut->Get(numHist03.c_str()));
  inNum03->SetNameTitle("", "");

  TH1D *inDen03 = dynamic_cast<TH1D *>(inPut->Get(denHist03.c_str()));
  inDen03->SetNameTitle("", "");

  TH1D *inNum04 = dynamic_cast<TH1D *>(inPut->Get(numHist04.c_str()));
  inNum04->SetNameTitle("", "");

  TH1D *inDen04 = dynamic_cast<TH1D *>(inPut->Get(denHist04.c_str()));
  inDen04->SetNameTitle("", "");

  const Int_t ptBin = 5;
  const Int_t etaBin = 10;
  const Int_t nJetBin = 5;
  const Int_t nTagBin = 3; 

  Float_t ptBins[ptBin + 1] = {20., 30., 50., 80., 130., 200.};
  Float_t etaBins[etaBin + 1] = {-2.1, -1.65, -1.2, -0.9, -0.45, 0., 0.45, 0.9, 1.2, 1.65, 2.1};
  Float_t nJetBins[nJetBin + 1] = {0., 1., 2., 3., 4., 5.};
  Float_t nTagBins[nTagBin + 1] = {0., 1., 2., 3.};

  // ---------------------------------------- //

  Float_t eff_ymin = 0., eff_ymax = 1.;
  Float_t sf_ymin = .8, sf_ymax = 1.2;

  TGraphAsymmErrors *z_tp_pt_gr = new TGraphAsymmErrors(5);
  z_tp_pt_gr->SetName("z_tp_pt_gr");
  z_tp_pt_gr->SetTitle("Efficiency of IsoMu17::pass");
  z_tp_pt_gr->SetFillColor(1);
  z_tp_pt_gr->SetLineWidth(2);

  z_tp_pt_gr->SetPoint(0,26.1127,0.85043);
  z_tp_pt_gr->SetPointError(0,6.112695,3.887305,0.0004223505,0.0004213751);
  z_tp_pt_gr->SetPoint(1,40.50132,0.8572637);
  z_tp_pt_gr->SetPointError(1,10.50132,9.498677,0.0001664271,0.0001662662);
  z_tp_pt_gr->SetPoint(2,57.41799,0.8544323);
  z_tp_pt_gr->SetPointError(2,7.417993,22.58201,0.0004215657,0.0004205607);
  z_tp_pt_gr->SetPoint(3,94.41355,0.835761);
  z_tp_pt_gr->SetPointError(3,14.41355,35.58645,0.001614262,0.001601732);
  z_tp_pt_gr->SetPoint(4,154.0486,0.8224155);
  z_tp_pt_gr->SetPointError(4,24.04856,45.95144,0.004667862,0.004575329);

  TH1F *z_tp_pt = new TH1F("pt_mc", "", ptBin, ptBins);
  z_tp_pt->SetMarkerColor(kRed + 1);
  z_tp_pt->SetLineColor(kRed);
  z_tp_pt->SetLineWidth(2);
  z_tp_pt->GetYaxis()->SetTitle("Efficiency");
  z_tp_pt->GetYaxis()->SetTitleSize(30);
  z_tp_pt->GetYaxis()->SetTitleFont(43);
  z_tp_pt->GetYaxis()->SetTitleOffset(.8);
  z_tp_pt->SetAxisRange(eff_ymin, eff_ymax, "y");

  Float_t l1[ptBin + 1] = {1., 1., 1., 1., 1., 1.};
  TGraph *liner_pt = new TGraph(ptBin + 1, ptBins, l1);
  liner_pt->SetLineColor(kYellow + 1);
  liner_pt->SetLineWidth(2);

  Double_t x_pt, y_pt, ye_pt;

  for (Int_t a = 0; a < ptBin; a++) {

    x_pt = 0.;
    y_pt = 0.;
    ye_pt = 0.;

    z_tp_pt_gr->GetPoint(a, x_pt, y_pt);
    ye_pt = z_tp_pt_gr->GetErrorY(a);
    z_tp_pt->SetBinContent(a + 1, y_pt);
    z_tp_pt->SetBinError(a + 1, ye_pt);

  }

  TGraphAsymmErrors *z_tp_eta_gr = new TGraphAsymmErrors(5);
  z_tp_eta_gr->SetName("z_tp_eta_gr");
  z_tp_eta_gr->SetTitle("Efficiency of IsoMu17::pass");
  z_tp_eta_gr->SetFillColor(1);
  z_tp_eta_gr->SetLineWidth(2);

  z_tp_eta_gr->SetPoint(0,-1.867956,0.779611);
  z_tp_eta_gr->SetPointError(0,0.2320441,0.2179559,0.000614731,0.0006135102);
  z_tp_eta_gr->SetPoint(1,-1.417434,0.8359238);
  z_tp_eta_gr->SetPointError(1,0.2325661,0.2174339,0.0004885598,0.0004873997);
  z_tp_eta_gr->SetPoint(2,-1.047891,0.8368649);
  z_tp_eta_gr->SetPointError(2,0.1521086,0.1478914,0.0005612629,0.0005597215);
  z_tp_eta_gr->SetPoint(3,-0.6695421,0.8881372);
  z_tp_eta_gr->SetPointError(3,0.2304579,0.2195421,0.0003691586,0.0003681027);
  z_tp_eta_gr->SetPoint(4,-0.2240927,0.9016688);
  z_tp_eta_gr->SetPointError(4,0.2259073,0.2240927,0.0003405018,0.0003394603);
  z_tp_eta_gr->SetPoint(5,0.2240881,0.9024274);
  z_tp_eta_gr->SetPointError(5,0.2240881,0.2259119,0.0003404465,0.0003393963);
  z_tp_eta_gr->SetPoint(6,0.6693526,0.8859882);
  z_tp_eta_gr->SetPointError(6,0.2193526,0.2306474,0.0003734897,0.0003724325);
  z_tp_eta_gr->SetPoint(7,1.047338,0.8374544);
  z_tp_eta_gr->SetPointError(7,0.1473384,0.1526616,0.0005646873,0.0005631198);
  z_tp_eta_gr->SetPoint(8,1.417752,0.8308622);
  z_tp_eta_gr->SetPointError(8,0.217752,0.232248,0.0004996085,0.0004984423);
  z_tp_eta_gr->SetPoint(9,1.868991,0.7663211);
  z_tp_eta_gr->SetPointError(9,0.2189909,0.2310091,0.000636459,0.0006352629);

  TH1F *z_tp_eta = new TH1F("eta_mc", "", etaBin, etaBins);
  z_tp_eta->SetMarkerColor(kRed + 1);
  z_tp_eta->SetLineColor(kRed);
  z_tp_eta->SetLineWidth(2);
  z_tp_eta->GetYaxis()->SetTitle("Efficiency");
  z_tp_eta->GetYaxis()->SetTitleSize(30);
  z_tp_eta->GetYaxis()->SetTitleFont(43);
  z_tp_eta->GetYaxis()->SetTitleOffset(.8);
  z_tp_eta->SetAxisRange(eff_ymin, eff_ymax, "y");

  Float_t l2[etaBin + 1] = {1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1.};
  TGraph *liner_eta = new TGraph(etaBin + 1, etaBins, l2);
  liner_eta->SetLineColor(kYellow + 1);
  liner_eta->SetLineWidth(2);

  Double_t x_eta, y_eta, ye_eta;

  for (Int_t b = 0; b < etaBin; b++) {

    x_eta = 0.;
    y_eta = 0.;
    ye_eta = 0.;

    z_tp_eta_gr->GetPoint(b, x_eta, y_eta);
    ye_eta = z_tp_eta_gr->GetErrorY(b);
    z_tp_eta->SetBinContent(b + 1, y_eta);
    z_tp_eta->SetBinError(b + 1, ye_eta);

  }

  TGraphAsymmErrors *z_tp_nJet_gr = new TGraphAsymmErrors(5);
  z_tp_nJet_gr->SetName("z_tp_nJet_gr");
  z_tp_nJet_gr->SetTitle("Efficiency of IsoMu17::pass");
  z_tp_nJet_gr->SetFillColor(1);
  z_tp_nJet_gr->SetLineWidth(2);

  z_tp_nJet_gr->SetPoint(0,0,0.8590315);
  z_tp_nJet_gr->SetPointError(0,-0,1,0.0001533574,0.0001532187);
  z_tp_nJet_gr->SetPoint(1,1,0.837395);
  z_tp_nJet_gr->SetPointError(1,-0,1,0.0004801182,0.0004789848);
  z_tp_nJet_gr->SetPoint(2,2,0.8260742);
  z_tp_nJet_gr->SetPointError(2,-0,1,0.001064338,0.001059258);
  z_tp_nJet_gr->SetPoint(3,3,0.8022258);
  z_tp_nJet_gr->SetPointError(3,-0,1,0.002713938,0.002686491);
  z_tp_nJet_gr->SetPoint(4,4.130147,0.7790192);
  z_tp_nJet_gr->SetPointError(4,0.1301469,0.8698531,0.006163897,0.006045567);

  TH1F *z_tp_nJet = new TH1F("nJet_mc", "", nJetBin, nJetBins);
  z_tp_nJet->SetMarkerColor(kRed + 1);
  z_tp_nJet->SetLineColor(kRed);
  z_tp_nJet->SetLineWidth(2);
  z_tp_nJet->GetYaxis()->SetTitle("Efficiency");
  z_tp_nJet->GetYaxis()->SetTitleSize(30);
  z_tp_nJet->GetYaxis()->SetTitleFont(43);
  z_tp_nJet->GetYaxis()->SetTitleOffset(.8);
  z_tp_nJet->SetAxisRange(eff_ymin, eff_ymax, "y");

  Float_t l3[nJetBin + 1] = {1., 1., 1., 1., 1., 1.};
  TGraph *liner_nJet = new TGraph(nJetBin + 1, nJetBins, l3);
  liner_nJet->SetLineColor(kYellow + 1);
  liner_nJet->SetLineWidth(2);

  Double_t x_nJet, y_nJet, ye_nJet;

  for (Int_t c = 0; c < nJetBin; c++) {

    x_nJet = 0.;
    y_nJet = 0.;
    ye_nJet = 0.;

    z_tp_nJet_gr->GetPoint(c, x_nJet, y_nJet);
    ye_nJet = z_tp_nJet_gr->GetErrorY(c);
    z_tp_nJet->SetBinContent(c + 1, y_nJet);
    z_tp_nJet->SetBinError(c + 1, ye_nJet);

  }

  TGraphAsymmErrors *z_tp_nTag_gr = new TGraphAsymmErrors(5);
  z_tp_nTag_gr->SetName("z_tp_nTag_gr");
  z_tp_nTag_gr->SetTitle("Efficiency of IsoMu17::pass");
  z_tp_nTag_gr->SetFillColor(1);
  z_tp_nTag_gr->SetLineWidth(2);

  z_tp_nTag_gr->SetPoint(0,0,0.8259203);
  z_tp_nTag_gr->SetPointError(0,-0,1,0.001084236,0.001078972);
  z_tp_nTag_gr->SetPoint(1,1,0.8292964);
  z_tp_nTag_gr->SetPointError(1,-0,1,0.005939711,0.005783582);
  z_tp_nTag_gr->SetPoint(2,2,0.8455882);
  z_tp_nTag_gr->SetPointError(2,-0,1,0.02523189,0.02246368);

  TH1F *z_tp_nTag = new TH1F("nTag_mc", "", nTagBin, nTagBins);
  z_tp_nTag->SetMarkerColor(kRed + 1);
  z_tp_nTag->SetLineColor(kRed);
  z_tp_nTag->SetLineWidth(2);
  z_tp_nTag->GetYaxis()->SetTitle("Efficiency");
  z_tp_nTag->GetYaxis()->SetTitleSize(30);
  z_tp_nTag->GetYaxis()->SetTitleFont(43);
  z_tp_nTag->GetYaxis()->SetTitleOffset(.8);
  z_tp_nTag->SetAxisRange(eff_ymin, eff_ymax, "y");

  Float_t l4[nTagBin + 1] = {1., 1., 1., 1.};
  TGraph *liner_nTag = new TGraph(nTagBin + 1, nTagBins, l4);
  liner_nTag->SetLineColor(kYellow + 1);
  liner_nTag->SetLineWidth(2);

  Double_t x_nTag, y_nTag, ye_nTag;

  for (Int_t d = 0; d < nTagBin; d++) {

    x_nTag = 0.;
    y_nTag = 0.;
    ye_nTag = 0.;

    z_tp_nTag_gr->GetPoint(d, x_nTag, y_nTag);
    ye_nTag = z_tp_nTag_gr->GetErrorY(d);
    z_tp_nTag->SetBinContent(d + 1, y_nTag);
    z_tp_nTag->SetBinError(d + 1, ye_nTag);

  }

  // ---------------------------------------- //

  // bins etc is still manual
  TH1D *schan_gen_pt = new TH1D("effMuon_pt", "muon pt", ptBin, ptBins);
  schan_gen_pt->SetXTitle("Muon PAT p_{T} (GeV/c)");
  schan_gen_pt->SetLineColor(kAzure - 1);
  schan_gen_pt->SetLineWidth(3);

  schan_gen_pt->Divide(inNum01, inDen01, 1., 1., "B");
  schan_gen_pt->SetMinimum(0.);
  schan_gen_pt->SetMaximum(1.);

  TH1D *schan_gen_eta = new TH1D("effMuon_eta", "muon eta", etaBin, etaBins);
  schan_gen_eta->SetXTitle("Muon PAT #eta");
  schan_gen_eta->SetLineColor(kAzure - 1);
  schan_gen_eta->SetLineWidth(3);

  schan_gen_eta->Divide(inNum02, inDen02, 1., 1., "B");
  schan_gen_eta->SetMinimum(0.);
  schan_gen_eta->SetMaximum(1.);

  TH1D *schan_gen_nJet = new TH1D("effMuon_nJet", "muon nJet", nJetBin, nJetBins);
  schan_gen_nJet->SetXTitle("Muon nJet");
  schan_gen_nJet->SetLineColor(kAzure - 1);
  schan_gen_nJet->SetLineWidth(3);

  schan_gen_nJet->Divide(inNum03, inDen03, 1., 1., "B");
  schan_gen_nJet->SetMinimum(0.);
  schan_gen_nJet->SetMaximum(1.);

  TH1D *schan_gen_nTag = new TH1D("effMuon_nTag", "muon nTag", nTagBin, nTagBins);
  schan_gen_nTag->SetXTitle("Muon nTag");
  schan_gen_nTag->SetLineColor(kAzure - 1);
  schan_gen_nTag->SetLineWidth(3);

  schan_gen_nTag->Divide(inNum04, inDen04, 1., 1., "B");
  schan_gen_nTag->SetMinimum(0.);
  schan_gen_nTag->SetMaximum(1.);

  // ---------------------------------------- //

  TH1F *sf_pt_hist = (TH1F*) z_tp_pt->Clone("");
  sf_pt_hist->Divide(schan_gen_pt);
  sf_pt_hist->SetMarkerColor(kBlack);
  sf_pt_hist->SetLineColor(kBlack);
  sf_pt_hist->SetTitle("");
  sf_pt_hist->GetYaxis()->SetTitle("Z / t-schan");
  sf_pt_hist->GetYaxis()->SetNdivisions(505);
  sf_pt_hist->GetYaxis()->SetTitleSize(30);
  sf_pt_hist->GetYaxis()->SetTitleFont(43);
  sf_pt_hist->GetYaxis()->SetTitleOffset(.8);
  sf_pt_hist->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  sf_pt_hist->GetYaxis()->SetLabelSize(20);
  sf_pt_hist->SetAxisRange(sf_ymin, sf_ymax, "y");

  sf_pt_hist->GetXaxis()->SetTitle("p_{T}");
  sf_pt_hist->GetXaxis()->SetTitleSize(30);
  sf_pt_hist->GetXaxis()->SetTitleFont(43);
  sf_pt_hist->GetXaxis()->SetTitleOffset(5.);
  sf_pt_hist->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  sf_pt_hist->GetXaxis()->SetLabelSize(30);

  Double_t sum_pt = 0., max_pt = 0., min_pt = 0., dif_pt = 0.;

  for (Int_t i = 0; i < ptBin; i++) {

    cout<< "Bin "<< i + 1 << " pt process normalizer: "<< sf_pt_hist->GetBinContent(i + 1) << " +- " << sf_pt_hist->GetBinError(i + 1) << endl;

    sum_pt += sf_pt_hist->GetBinContent(i + 1);
    
    if (i == 0) {

      max_pt = sf_pt_hist->GetBinContent(i + 1);
      min_pt = sf_pt_hist->GetBinContent(i + 1);

    }

    else {

      if (sf_pt_hist->GetBinContent(i + 1) > max_pt) max_pt = sf_pt_hist->GetBinContent(i + 1);
      if (sf_pt_hist->GetBinContent(i + 1) < min_pt) min_pt = sf_pt_hist->GetBinContent(i + 1);

    }

  }

  dif_pt = max_pt - min_pt;

  cout << "\nAverage pt process normalizer: " << sum_pt / ptBin << " +- " << dif_pt / (2 * sqrt(ptBin)) << "\n" << endl;

  TH1F *sf_eta_hist = (TH1F*) z_tp_eta->Clone("");
  sf_eta_hist->Divide(schan_gen_eta);
  sf_eta_hist->SetMarkerColor(kBlack);
  sf_eta_hist->SetLineColor(kBlack);
  sf_eta_hist->SetTitle("");
  sf_eta_hist->GetYaxis()->SetTitle("Z / t-schan");
  sf_eta_hist->GetYaxis()->SetNdivisions(505);
  sf_eta_hist->GetYaxis()->SetTitleSize(30);
  sf_eta_hist->GetYaxis()->SetTitleFont(43);
  sf_eta_hist->GetYaxis()->SetTitleOffset(.8);
  sf_eta_hist->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  sf_eta_hist->GetYaxis()->SetLabelSize(20);
  sf_eta_hist->SetAxisRange(sf_ymin, sf_ymax, "y");

  sf_eta_hist->GetXaxis()->SetTitle("#eta");
  sf_eta_hist->GetXaxis()->SetTitleSize(30);
  sf_eta_hist->GetXaxis()->SetTitleFont(43);
  sf_eta_hist->GetXaxis()->SetTitleOffset(5.);
  sf_eta_hist->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  sf_eta_hist->GetXaxis()->SetLabelSize(30);

  Double_t sum_eta = 0., max_eta = 0., min_eta = 0., dif_eta = 0.;

  for (Int_t j = 0; j < etaBin; j++) {

    cout<< "Bin "<< j + 1 << " eta process normalizer: "<< sf_eta_hist->GetBinContent(j + 1) << " +- " << sf_eta_hist->GetBinError(j + 1) << endl;

    sum_eta += sf_eta_hist->GetBinContent(j + 1);
    
    if (j == 0) {

      max_eta = sf_eta_hist->GetBinContent(j + 1);
      min_eta = sf_eta_hist->GetBinContent(j + 1);

    }

    else {

      if (sf_eta_hist->GetBinContent(j + 1) > max_eta) max_eta = sf_eta_hist->GetBinContent(j + 1);
      if (sf_eta_hist->GetBinContent(j + 1) < min_eta) min_eta = sf_eta_hist->GetBinContent(j + 1);

    }

  }

  dif_eta = max_eta - min_eta;

  cout << "\nAverage eta process normalizer: " << sum_eta / etaBin << " +- " << dif_eta / (2 * sqrt(etaBin)) <<  "\n" << endl;

  TH1F *sf_nJet_hist = (TH1F*) z_tp_nJet->Clone("");
  sf_nJet_hist->Divide(schan_gen_nJet);
  sf_nJet_hist->SetMarkerColor(kBlack);
  sf_nJet_hist->SetLineColor(kBlack);
  sf_nJet_hist->SetTitle("");
  sf_nJet_hist->GetYaxis()->SetTitle("Z / t-schan");
  sf_nJet_hist->GetYaxis()->SetNdivisions(505);
  sf_nJet_hist->GetYaxis()->SetTitleSize(30);
  sf_nJet_hist->GetYaxis()->SetTitleFont(43);
  sf_nJet_hist->GetYaxis()->SetTitleOffset(.8);
  sf_nJet_hist->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  sf_nJet_hist->GetYaxis()->SetLabelSize(20);
  sf_nJet_hist->SetAxisRange(sf_ymin, sf_ymax, "y");

  sf_nJet_hist->GetXaxis()->SetTitle("nJet");
  sf_nJet_hist->GetXaxis()->SetTitleSize(30);
  sf_nJet_hist->GetXaxis()->SetTitleFont(43);
  sf_nJet_hist->GetXaxis()->SetTitleOffset(5.);
  sf_nJet_hist->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  sf_nJet_hist->GetXaxis()->SetLabelSize(30);

  Double_t sum_nJet = 0., max_nJet = 0., min_nJet = 0., dif_nJet = 0.;

  for (Int_t k = 0; k < nJetBin; k++) {

    cout<< "Bin "<< k + 1 << " nJet process normalizer: "<< sf_nJet_hist->GetBinContent(k + 1) << " +- " << sf_nJet_hist->GetBinError(k + 1) << endl;

    sum_nJet += sf_nJet_hist->GetBinContent(k + 1);
    
    if (k == 0) {

      max_nJet = sf_nJet_hist->GetBinContent(k + 1);
      min_nJet = sf_nJet_hist->GetBinContent(k + 1);

    }

    else {

      if (sf_nJet_hist->GetBinContent(k + 1) > max_nJet) max_nJet = sf_nJet_hist->GetBinContent(k + 1);
      if (sf_nJet_hist->GetBinContent(k + 1) < min_nJet) min_nJet = sf_nJet_hist->GetBinContent(k + 1);

    }

  }

  dif_nJet = max_nJet - min_nJet;

  cout << "\nAverage nJet process normalizer: " << sum_nJet / nJetBin << " +- " << dif_nJet / (2 * sqrt(nJetBin)) <<  "\n" << endl;

  TH1F *sf_nTag_hist = (TH1F*) z_tp_nTag->Clone("");
  sf_nTag_hist->Divide(schan_gen_nTag);
  sf_nTag_hist->SetMarkerColor(kBlack);
  sf_nTag_hist->SetLineColor(kBlack);
  sf_nTag_hist->SetTitle("");
  sf_nTag_hist->GetYaxis()->SetTitle("Z / t-schan");
  sf_nTag_hist->GetYaxis()->SetNdivisions(505);
  sf_nTag_hist->GetYaxis()->SetTitleSize(30);
  sf_nTag_hist->GetYaxis()->SetTitleFont(43);
  sf_nTag_hist->GetYaxis()->SetTitleOffset(.8);
  sf_nTag_hist->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  sf_nTag_hist->GetYaxis()->SetLabelSize(20);
  sf_nTag_hist->SetAxisRange(sf_ymin, sf_ymax, "y");

  sf_nTag_hist->GetXaxis()->SetTitle("nTag");
  sf_nTag_hist->GetXaxis()->SetTitleSize(30);
  sf_nTag_hist->GetXaxis()->SetTitleFont(43);
  sf_nTag_hist->GetXaxis()->SetTitleOffset(5.);
  sf_nTag_hist->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  sf_nTag_hist->GetXaxis()->SetLabelSize(30);

  Double_t sum_nTag = 0., max_nTag = 0., min_nTag = 0., dif_nTag = 0.;

  for (Int_t l = 0; l < nTagBin; l++) {

    cout<< "Bin "<< l + 1 << " nTag process normalizer: "<< sf_nTag_hist->GetBinContent(l + 1) << " +- " << sf_nTag_hist->GetBinError(l + 1) << endl;

    sum_nTag += sf_nTag_hist->GetBinContent(l + 1);
    
    if (l == 0) {

      max_nTag = sf_nTag_hist->GetBinContent(l + 1);
      min_nTag = sf_nTag_hist->GetBinContent(l + 1);

    }

    else {

      if (sf_nTag_hist->GetBinContent(l + 1) > max_nTag) max_nTag = sf_nTag_hist->GetBinContent(l + 1);
      if (sf_nTag_hist->GetBinContent(l + 1) < min_nTag) min_nTag = sf_nTag_hist->GetBinContent(l + 1);

    }

  }

  dif_nTag = max_nTag - min_nTag;

  cout << "\nAverage nTag process normalizer: " << sum_nTag / nTagBin << " +- " << dif_nTag / (2 * sqrt(nTagBin)) <<  "\n" << endl;

  // ---------------------------------------- //
  
  TCanvas *c01 = new TCanvas("c01", "c01", 200, 10, 1600, 900);
  c01->cd();

  // Upper plot will be in pad1
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad

  z_tp_pt->Draw();
  schan_gen_pt->Draw("same");

  // lower plot will be in pad
  c01->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad);

  sf_pt_hist->Draw();
  liner_pt->Draw("lsame");
  sf_pt_hist->Draw("same");

  TCanvas *c02 = new TCanvas("c02", "c02", 200, 10, 1600, 900);
  c02->cd();

  // Upper plot will be in pad1
  TPad *pad3 = new TPad("pad3", "pad3", 0, 0.3, 1, 1.0);
  pad3->SetBottomMargin(0); // Upper and lower plot are joined
  pad3->SetGridx();         // Vertical grid
  pad3->Draw();             // Draw the upper pad: pad3
  pad3->cd();               // pad3 becomes the current pad

  z_tp_eta->Draw();
  schan_gen_eta->Draw("same");

  // lower plot will be in pad
  c02->cd();          // Go back to the main canvas before defining pad4
  TPad *pad4 = new TPad("pad4", "pad4", 0, 0.05, 1, 0.3);
  pad4->SetTopMargin(0);
  pad4->SetBottomMargin(0.2);
  pad4->SetGridx(); // vertical grid
  pad4->Draw();
  pad4->cd();       // pad4 becomes the current pad);

  sf_eta_hist->Draw();
  liner_eta->Draw("lsame");
  sf_eta_hist->Draw("same");
  /*
  TCanvas *c03 = new TCanvas("c03", "c03", 200, 10, 1600, 900);
  c03->cd();

  // Upper plot will be in pad1
  TPad *pad5 = new TPad("pad5", "pad5", 0, 0.3, 1, 1.0);
  pad5->SetBottomMargin(0); // Upper and lower plot are joined
  pad5->SetGridx();         // Vertical grid
  pad5->Draw();             // Draw the upper pad: pad3
  pad5->cd();               // pad3 becomes the current pad

  z_tp_nJet->Draw();
  schan_gen_nJet->Draw("same");

  // lower plot will be in pad
  c03->cd();          // Go back to the main canvas before defining pad4
  TPad *pad6 = new TPad("pad6", "pad6", 0, 0.05, 1, 0.3);
  pad6->SetTopMargin(0);
  pad6->SetBottomMargin(0.2);
  pad6->SetGridx(); // vertical grid
  pad6->Draw();
  pad6->cd();       // pad4 becomes the current pad);

  sf_nJet_hist->Draw();
  liner_nJet->Draw("lsame");
  sf_nJet_hist->Draw("same");

  TCanvas *c04 = new TCanvas("c04", "c04", 200, 10, 1600, 900);
  c04->cd();

  // Upper plot will be in pad1
  TPad *pad7 = new TPad("pad7", "pad7", 0, 0.3, 1, 1.0);
  pad7->SetBottomMargin(0); // Upper and lower plot are joined
  pad7->SetGridx();         // Vertical grid
  pad7->Draw();             // Draw the upper pad: pad3
  pad7->cd();               // pad3 becomes the current pad

  z_tp_nTag->Draw();
  schan_gen_nTag->Draw("same");

  // lower plot will be in pad
  c04->cd();          // Go back to the main canvas before defining pad4
  TPad *pad8 = new TPad("pad8", "pad8", 0, 0.05, 1, 0.3);
  pad8->SetTopMargin(0);
  pad8->SetBottomMargin(0.2);
  pad8->SetGridx(); // vertical grid
  pad8->Draw();
  pad8->cd();       // pad4 becomes the current pad);

  sf_nTag_hist->Draw();
  liner_nTag->Draw("lsame");
  sf_nTag_hist->Draw("same");
  */
}
