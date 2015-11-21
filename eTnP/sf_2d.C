void sf_2d() {

  // Code to save the 2D effs SFs prettily

  gStyle->SetFrameBorderMode(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetPaintTextFormat("4.3f");
  gStyle->SetOptStat(0);

  gStyle->SetPadColor(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetStatColor(0);
  gStyle->SetFillColor(0);

  //gStyle->SetPaperSize(20, 26);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.075);
  gStyle->SetPadRightMargin(0.12);
  gStyle->SetPadLeftMargin(0.07);

  gStyle->SetTextFont(42);
  gStyle->SetTextSize(0.03);
  gStyle->SetLabelFont(42, "xyz");
  gStyle->SetTitleFont(42, "xyz");
  gStyle->SetLabelSize(0.025, "xyz");
  gStyle->SetTitleSize(0.027, "xyz");
  gStyle->SetTitleOffset(1.1, "y");
  gStyle->SetTitleOffset(1.1, "x");

  gStyle->SetTitleX(0.5); // suit the plot
  gStyle->SetTitleY(0.97);
  gStyle->SetTitleAlign(23);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleFontSize(0.03);
  gStyle->SetHistLineWidth(2);
  gStyle->SetLineWidth(2);

  string plotTitle = "Single Electron Path ";
  string argv = "loo";

  Float_t eff_ymin = .3, eff_ymax = 1.;
  Float_t sf_ymin = .76, sf_ymax = 1.24;

  const Int_t nBin = 10;
  Float_t et_binEdges[nBin + 1] = {25., 30., 35., 40., 45., 50., 65., 90., 135., 190., 250.};
  Float_t eta_binEdges[nBin + 1] = {-2.5, -2.1, -1.6, -1.4, -0.7, 0, 0.7, 1.4, 1.6, 2.1, 2.5};

  // Make sure uncertainty in histogram bins is calculated correctly
  TH1::SetDefaultSumw2(kTRUE);

  TH2F *mc_2d_gr = new TH2F("", (plotTitle + "Efficiency").c_str(), 10, eta_binEdges, 10, et_binEdges);
  mc_2d_gr->GetYaxis()->SetTitle("Probe E_{T} (GeV)");
  mc_2d_gr->GetXaxis()->SetTitle("Probe #eta");
  mc_2d_gr->GetZaxis()->SetTitle("Efficiency");
  mc_2d_gr->GetZaxis()->SetTitleSize(19);
  mc_2d_gr->GetZaxis()->SetTitleFont(43);
  mc_2d_gr->GetZaxis()->SetTitleOffset(1.55);
  mc_2d_gr->GetZaxis()->SetLabelFont(43);
  mc_2d_gr->GetZaxis()->SetLabelSize(21);
  mc_2d_gr->GetYaxis()->SetTitleSize(19);
  mc_2d_gr->GetYaxis()->SetTitleFont(43);
  mc_2d_gr->GetYaxis()->SetTitleOffset(1.55);
  mc_2d_gr->GetYaxis()->SetLabelFont(43);
  mc_2d_gr->GetYaxis()->SetLabelSize(21);
  mc_2d_gr->GetXaxis()->SetTitleSize(19);
  mc_2d_gr->GetXaxis()->SetTitleFont(43);
  mc_2d_gr->GetXaxis()->SetTitleOffset(1.15);
  mc_2d_gr->GetXaxis()->SetLabelFont(43);
  mc_2d_gr->GetXaxis()->SetLabelSize(21);
  mc_2d_gr->SetMarkerSize(0.5);
  mc_2d_gr->SetAxisRange(eff_ymin, eff_ymax, "z");

  TH2F *dat_2d_gr = new TH2F("", (plotTitle + "Efficiency").c_str(), 10, eta_binEdges, 10, et_binEdges);
  dat_2d_gr->GetYaxis()->SetTitle("Probe E_{T} (GeV)");
  dat_2d_gr->GetXaxis()->SetTitle("Probe #eta");
  dat_2d_gr->GetZaxis()->SetTitle("Efficiency");
  dat_2d_gr->GetZaxis()->SetTitleSize(19);
  dat_2d_gr->GetZaxis()->SetTitleFont(43);
  dat_2d_gr->GetZaxis()->SetTitleOffset(1.55);
  dat_2d_gr->GetZaxis()->SetLabelFont(43);
  dat_2d_gr->GetZaxis()->SetLabelSize(21);
  dat_2d_gr->GetYaxis()->SetTitleSize(19);
  dat_2d_gr->GetYaxis()->SetTitleFont(43);
  dat_2d_gr->GetYaxis()->SetTitleOffset(1.55);
  dat_2d_gr->GetYaxis()->SetLabelFont(43);
  dat_2d_gr->GetYaxis()->SetLabelSize(21);
  dat_2d_gr->GetXaxis()->SetTitleSize(19);
  dat_2d_gr->GetXaxis()->SetTitleFont(43);
  dat_2d_gr->GetXaxis()->SetTitleOffset(1.15);
  dat_2d_gr->GetXaxis()->SetLabelFont(43);
  dat_2d_gr->GetXaxis()->SetLabelSize(21);
  dat_2d_gr->SetMarkerSize(0.5);
  dat_2d_gr->SetAxisRange(eff_ymin, eff_ymax, "z");


  if (argv == "loo") {

  }

  else if (argv == "med") {

  }

  else if (argv == "tig") {

  }

  else {

    cout << "ID WP not supported." << endl;
    return 0;

  }

  TH2F *sf_2d_gr = new TH2F("", (plotTitle + "Scale Factor").c_str(), 10, eta_binEdges, 10, et_binEdges);
  sf_2d_gr->Divide(dat_2d_gr, mc_2d_gr, 1., 1., "B");
  sf_2d_gr->GetYaxis()->SetTitle("Probe E_{T} (GeV)");
  sf_2d_gr->GetXaxis()->SetTitle("Probe #eta");
  sf_2d_gr->GetZaxis()->SetTitle("Data / MC");
  sf_2d_gr->GetZaxis()->SetTitleSize(19);
  sf_2d_gr->GetZaxis()->SetTitleFont(43);
  sf_2d_gr->GetZaxis()->SetTitleOffset(1.55);
  sf_2d_gr->GetZaxis()->SetLabelFont(43);
  sf_2d_gr->GetZaxis()->SetLabelSize(21);
  sf_2d_gr->GetYaxis()->SetTitleSize(19);
  sf_2d_gr->GetYaxis()->SetTitleFont(43);
  sf_2d_gr->GetYaxis()->SetTitleOffset(1.55);
  sf_2d_gr->GetYaxis()->SetLabelFont(43);
  sf_2d_gr->GetYaxis()->SetLabelSize(21);
  sf_2d_gr->GetXaxis()->SetTitleSize(19);
  sf_2d_gr->GetXaxis()->SetTitleFont(43);
  sf_2d_gr->GetXaxis()->SetTitleOffset(1.15);
  sf_2d_gr->GetXaxis()->SetLabelFont(43);
  sf_2d_gr->GetXaxis()->SetLabelSize(21);
  sf_2d_gr->SetMarkerSize(0.5);
  sf_2d_gr->SetAxisRange(sf_ymin, sf_ymax, "z");

  // simple loop to zero the 2.1 < absEta < 2.5 bins
  for (Int_t i = 1; i < 11; i++) {

    Int_t negEdge = (12 * i) + 1, posEdge = (12 * (i + 1)) - 2;

    mc_2d_gr->SetBinContent(negEdge, 0.);
    mc_2d_gr->SetBinError(negEdge, 0.);
    mc_2d_gr->SetBinContent(posEdge, 0.);
    mc_2d_gr->SetBinError(posEdge, 0.);

    dat_2d_gr->SetBinContent(negEdge, 0.);
    dat_2d_gr->SetBinError(negEdge, 0.);
    dat_2d_gr->SetBinContent(posEdge, 0.);
    dat_2d_gr->SetBinError(posEdge, 0.);

    sf_2d_gr->SetBinContent(negEdge, 0.);
    sf_2d_gr->SetBinError(negEdge, 0.);
    sf_2d_gr->SetBinContent(posEdge, 0.);
    sf_2d_gr->SetBinError(posEdge, 0.);

  }

  TLatex txt;
  txt.SetTextSize(0.025);
  txt.SetTextAlign(13);

  string outDir = "/home/ieeya/Downloads/EGM/TnP/files/run15CD_25ns/act04_ppGoldNov18/plot/";
  string cmsPrem = "#bf{CMS} #it{Preliminary}";
  string intLumi = "2.094 fb^{-1} (13 TeV)";

  TCanvas *c1 = new TCanvas("c1","", 200, 10, 1000, 1000);
  c1->cd();

  mc_2d_gr->Draw("pcolztexte");

  txt.DrawLatexNDC(0.07, 0.921, cmsPrem.c_str());
  txt.DrawLatexNDC(0.74, 0.923, intLumi.c_str());

  c1->cd();
  c1->SaveAs((outDir + "mc_2d_" + argv + ".pdf").c_str());
  c1->Close();

  TCanvas *c2 = new TCanvas("c2","", 200, 10, 1000, 1000);
  c2->cd();

  dat_2d_gr->Draw("pcolztexte");

  txt.DrawLatexNDC(0.07, 0.921, cmsPrem.c_str());
  txt.DrawLatexNDC(0.74, 0.923, intLumi.c_str());

  c2->cd();
  c2->SaveAs((outDir + "dat_2d_" + argv + ".pdf").c_str());
  c2->Close();

  TCanvas *c3 = new TCanvas("c3","", 200, 10, 1000, 1000);
  c3->cd();

  sf_2d_gr->Draw("pcolztexte");

  txt.DrawLatexNDC(0.07, 0.921, cmsPrem.c_str());
  txt.DrawLatexNDC(0.74, 0.923, intLumi.c_str());

  c3->cd();
  c3->SaveAs((outDir + "sf_2d_" + argv + ".pdf").c_str());
  c3->Close();

  gROOT->ProcessLine(".q");

  //return 0;

}
