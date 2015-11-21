Double_t quadSum(Double_t a, Double_t b) {

  Double_t c = 0.;
  c = sqrt((a*a) + (b*b));

  return c;

}

void sf_et() {

  // Code to calculate draw the scale factor
  // Save the (fit) eff canvases in .C and then take the relevant graphs, port them here
  // MC is red, data is blue

  gROOT->ProcessLine(".L tdrstyle.C");
  setTDRStyle();

  string plotTitle = "Single Electron Path Efficiency";
  string argv = "loo";

  Float_t eff_ymin = .51, eff_ymax = 1.05;
  Float_t sf_ymin = .81, sf_ymax = 1.19;

  const Int_t nBin = 10;
  Float_t binEdges[nBin + 1] = {25., 30., 35., 40., 45., 50., 65., 90., 135., 190., 250.};
  //Float_t binEdges[nBin + 1] = {30., 31., 32., 33., 34., 35., 36., 37.5, 40., 42.5, 45., 47.5, 50., 55., 60., 70., 82.5, 100.};

  // Make sure uncertainty in histogram bins is calculated correctly
  TH1::SetDefaultSumw2(kTRUE);

  TGraphAsymmErrors *mc_et_gr = new TGraphAsymmErrors();
  mc_et_gr->SetName("mc_et_gr");
  mc_et_gr->SetMarkerColor(kRed + 1);
  mc_et_gr->SetMarkerStyle(2);
  mc_et_gr->SetMarkerSize(2);
  mc_et_gr->SetLineColor(kRed);
  mc_et_gr->SetLineWidth(2);

  TGraphAsymmErrors *dat_et_gr = new TGraphAsymmErrors();
  dat_et_gr->SetName("dat_et_gr");
  dat_et_gr->SetMarkerColor(kBlue + 1);
  dat_et_gr->SetMarkerStyle(2);
  dat_et_gr->SetMarkerSize(2);
  dat_et_gr->SetLineColor(kBlue);
  dat_et_gr->SetLineWidth(2);

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

  Double_t px_mc, py_mc, px_dat, py_dat;

  for (Int_t i = 0; i < nBin; i++) {

    mc_et_gr->GetPoint(i, px_mc, py_mc);
    mc_et_gr->SetPointEXlow(i, px_mc - binEdges[i]);
    mc_et_gr->SetPointEXhigh(i, binEdges[i + 1] - px_mc);

    dat_et_gr->GetPoint(i, px_dat, py_dat);
    dat_et_gr->SetPointEXlow(i, px_dat - binEdges[i]);
    dat_et_gr->SetPointEXhigh(i, binEdges[i + 1] - px_dat);

  }

  TH1F *frame_hist = new TH1F("", plotTitle.c_str(), nBin, binEdges);
  //frame_hist->SetEntries(0);
  frame_hist->SetLineWidth(0);
  frame_hist->GetYaxis()->SetTitle("Efficiency");
  frame_hist->GetYaxis()->SetTitleSize(23);
  frame_hist->GetYaxis()->SetTitleFont(43);
  frame_hist->GetYaxis()->SetTitleOffset(1.25);
  frame_hist->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  frame_hist->GetYaxis()->SetLabelSize(21);
  frame_hist->SetAxisRange(eff_ymin, eff_ymax, "y");

  TH1F *mc_et_hist = new TH1F("", "", nBin, binEdges);
  mc_et_hist->SetMarkerColor(kRed + 1);
  mc_et_hist->SetLineColor(kRed);
  mc_et_hist->SetLineWidth(2);
  mc_et_hist->GetYaxis()->SetTitle("Efficiency");
  mc_et_hist->GetYaxis()->SetTitleSize(23);
  mc_et_hist->GetYaxis()->SetTitleFont(43);
  mc_et_hist->GetYaxis()->SetTitleOffset(1.25);
  mc_et_hist->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  mc_et_hist->GetYaxis()->SetLabelSize(21);
  mc_et_hist->SetAxisRange(eff_ymin, eff_ymax, "y");

  TH1F *dat_et_hist = new TH1F("", "", nBin, binEdges);
  dat_et_hist->SetMarkerColor(kBlue + 1);
  dat_et_hist->SetLineColor(kBlue);
  dat_et_hist->SetLineWidth(2);

  Float_t l1[nBin + 1];

  Double_t x_mc, y_mc, ye_mc, x_dat, y_dat, ye_dat;

  for (Int_t i = 0; i < nBin; i++) {

    l1[i] = 1.;

    x_mc = 0.;
    y_mc = 0.;
    ye_mc = 0.;

    x_dat = 0.;
    y_dat = 0.;
    ye_dat = 0.;

    mc_et_gr->GetPoint(i, x_mc, y_mc);
    ye_mc = mc_et_gr->GetErrorY(i);
    mc_et_hist->SetBinContent(i+1, y_mc);
    mc_et_hist->SetBinError(i+1, ye_mc);

    dat_et_gr->GetPoint(i, x_dat, y_dat);
    ye_dat = dat_et_gr->GetErrorY(i);
    dat_et_hist->SetBinContent(i+1, y_dat);
    dat_et_hist->SetBinError(i+1, ye_dat);

  }

  l1[nBin] = 1.;

  TGraph *liner = new TGraph(nBin + 1, binEdges, l1);
  liner->SetLineColor(kYellow + 1);
  liner->SetLineWidth(2);

  TH1F *sf_et_hist = new TH1F("", "", nBin, binEdges);
  sf_et_hist->Divide(dat_et_hist, mc_et_hist, 1., 1., "B");
  sf_et_hist->SetMarkerColor(kBlack);
  sf_et_hist->SetLineColor(kBlack);
  //sf_et_hist->SetLineWidth(2);
  sf_et_hist->SetTitle("");
  sf_et_hist->GetYaxis()->SetTitle("Data / MC");
  sf_et_hist->GetYaxis()->SetNdivisions(505);
  sf_et_hist->GetYaxis()->SetTitleSize(23);
  sf_et_hist->GetYaxis()->SetTitleFont(43);
  sf_et_hist->GetYaxis()->SetTitleOffset(1.25);
  sf_et_hist->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  sf_et_hist->GetYaxis()->SetLabelSize(21);
  sf_et_hist->SetAxisRange(sf_ymin, sf_ymax, "y");

  sf_et_hist->GetXaxis()->SetTitle("Probe E_{T} (GeV)");
  sf_et_hist->GetXaxis()->SetTitleSize(23);
  sf_et_hist->GetXaxis()->SetTitleFont(43);
  sf_et_hist->GetXaxis()->SetTitleOffset(2.9);
  sf_et_hist->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  sf_et_hist->GetXaxis()->SetLabelSize(21);

  for (Int_t i = 0; i < nBin; i++)
    cout<< "Bin "<< i + 1 << " scale factor: "<< sf_et_hist->GetBinContent(i + 1) << " +- " << sf_et_hist->GetBinError(i + 1) << endl;

  TCanvas *c1 = new TCanvas("c1","eta sf", 200, 10, 1000, 1000);

  // Upper plot will be in pad1
  TPad *pad1 = new TPad("pad1", "pad1", 0., 0.29, 1., 1.);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetGrid();
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad

  mc_et_gr->SetHistogram(frame_hist);
  dat_et_gr->SetHistogram(frame_hist);
  frame_hist->Draw("func");

  mc_et_gr->Draw("p");
  dat_et_gr->Draw("samep");

  TLatex txt;
  txt.SetTextSize(0.04);
  txt.SetTextAlign(13);

  txt.DrawLatexNDC(0.06, 0.933, "#bf{CMS} #it{Preliminary}");
  txt.DrawLatexNDC(0.758, 0.939, "2.094 fb^{-1} (13 TeV)");

  TLegend *leg = new TLegend(.77, .03, .95, .17);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.03);

  leg->AddEntry(mc_et_gr, "MC WP75", "lp");
  leg->AddEntry(dat_et_gr, "Data WPLoose", "lp");
  leg->Draw();

  // lower plot will be in pad
  c1->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0., 0., 1., 0.29);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  pad2->SetGrid();
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad);

  sf_et_hist->Draw();
  liner->Draw("lsame");
  sf_et_hist->Draw("same");

  c1->cd();
  c1->SaveAs(("/home/ieeya/Downloads/EGM/TnP/files/run15CD_25ns/act04_ppGoldNov18/plot/eff_et_" + argv + ".pdf").c_str());
  c1->Close();

  gROOT->ProcessLine(".q");

}
