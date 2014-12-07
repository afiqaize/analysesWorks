Double_t quadSum(Double_t a, Double_t b) {

  Double_t c = 0.;
  c = sqrt((a*a) + (b*b));

  return c;

}

void sf_pt_calc() {

  // Code to calculate draw the scale factor
  // Save the (fit) eff canvases in .C and then take the relevant graphs, port them here
  // MC is red, data is blue

  gStyle->SetOptStat(0);

  string scenario = "r11a_02";
  Float_t eff_ymin = 0., eff_ymax = 1.;
  Float_t sf_ymin = .8, sf_ymax = 1.2;

  // Make sure uncertainty in histogram bins is calculated correctly
  TH1::SetDefaultSumw2(kTRUE);

  TGraphAsymmErrors *mc_pt_gr = new TGraphAsymmErrors(5);
  mc_pt_gr->SetName("mc_pt_gr");
  mc_pt_gr->SetTitle("Efficiency of IsoMu17::pass");
  mc_pt_gr->SetFillColor(1);
  mc_pt_gr->SetLineWidth(2);

  TGraphAsymmErrors *data_pt_gr = new TGraphAsymmErrors(5);
  data_pt_gr->SetName("data_pt_gr");
  data_pt_gr->SetTitle("Efficiency of IsoMu17::pass");
  data_pt_gr->SetFillColor(1);
  data_pt_gr->SetLineWidth(2);

  if (scenario == "r11a_02") {

    mc_pt_gr->SetPoint(0,26.10275,0.8678677);
    mc_pt_gr->SetPointError(0,6.102746,3.897254,0.0003989205,0.0003979076);
    mc_pt_gr->SetPoint(1,40.4893,0.8788368);
    mc_pt_gr->SetPointError(1,10.4893,9.510703,0.0001553876,0.0001552167);
    mc_pt_gr->SetPoint(2,57.42309,0.8772322);
    mc_pt_gr->SetPointError(2,7.423094,22.57691,0.0003927223,0.0003916507);
    mc_pt_gr->SetPoint(3,94.41197,0.8575331);
    mc_pt_gr->SetPointError(3,14.41197,35.58803,0.001525968,0.00151259);
    mc_pt_gr->SetPoint(4,153.9028,0.8458356);
    mc_pt_gr->SetPointError(4,23.90283,46.09717,0.004381868,0.004284223);

    data_pt_gr->SetPoint(0,26.11605,0.8738348);
    data_pt_gr->SetPointError(0,6.11605,3.88395,0.00153866,0.001542476);
    data_pt_gr->SetPoint(1,40.40988,0.8759402);
    data_pt_gr->SetPointError(1,10.40988,9.590124,0.0006046918,0.0005995796);
    data_pt_gr->SetPoint(2,57.51622,0.8701713);
    data_pt_gr->SetPointError(2,7.516216,22.48378,0.001688522,0.001659703);
    data_pt_gr->SetPoint(3,94.50093,0.8702318);
    data_pt_gr->SetPointError(3,14.50093,35.49907,0.006396395,0.1297682);
    data_pt_gr->SetPoint(4,153.9644,0.8454503);
    data_pt_gr->SetPointError(4,23.9644,46.0356,0.016609,0.01568832);

  }

  else if (scenario == "r11ab_03") {

    mc_pt_gr->SetPoint(0,26.1096,0.8534341);
    mc_pt_gr->SetPointError(0,6.109604,3.890396,0.0004176521,0.0004166739);
    mc_pt_gr->SetPoint(1,40.49903,0.8611888);
    mc_pt_gr->SetPointError(1,10.49903,9.500968,0.0001643094,0.0001641472);
    mc_pt_gr->SetPoint(2,57.42543,0.8584056);
    mc_pt_gr->SetPointError(2,7.425435,22.57457,0.0004160828,0.0004150698);
    mc_pt_gr->SetPoint(3,94.4594,0.8384746);
    mc_pt_gr->SetPointError(3,14.4594,35.5406,0.001598902,0.001586344);
    mc_pt_gr->SetPoint(4,154.0375,0.8235704);
    mc_pt_gr->SetPointError(4,24.0375,45.9625,0.004642725,0.004550392);

    data_pt_gr->SetPoint(0,26.11845,0.8575253);
    data_pt_gr->SetPointError(0,6.118454,3.881546,0.001089103,0.001095801);
    data_pt_gr->SetPoint(1,40.43821,0.8565638);
    data_pt_gr->SetPointError(1,10.43821,9.561788,0.0004199336,0.0004318203);
    data_pt_gr->SetPoint(2,57.44712,0.8552367);
    data_pt_gr->SetPointError(2,7.447123,22.55288,0.001069149,0.001118564);
    data_pt_gr->SetPoint(3,94.35571,0.8290091);
    data_pt_gr->SetPointError(3,14.35571,35.64429,0.004420808,0.004343487);
    data_pt_gr->SetPoint(4,152.8977,0.8146582);
    data_pt_gr->SetPointError(4,22.89774,47.10226,0.01153205,0.01112003);

  }

  else if (scenario == "r11b_04") {

    mc_pt_gr->SetPoint(0,26.11353,0.8467212);
    mc_pt_gr->SetPointError(0,6.113531,3.886469,0.0004262802,0.0004253167);
    mc_pt_gr->SetPoint(1,40.50367,0.8530283);
    mc_pt_gr->SetPointError(1,10.50367,9.496333,0.0001682131,0.0001680545);
    mc_pt_gr->SetPoint(2,57.42328,0.8497785);
    mc_pt_gr->SetPointError(2,7.423282,22.57672,0.0004262536,0.0004252656);
    mc_pt_gr->SetPoint(3,94.44993,0.830558);
    mc_pt_gr->SetPointError(3,14.44993,35.55007,0.001628126,0.001615882);
    mc_pt_gr->SetPoint(4,154.0971,0.8137117);
    mc_pt_gr->SetPointError(4,24.09714,45.90286,0.004755818,0.004665667);

    data_pt_gr->SetPoint(0,26.12424,0.8323456);
    data_pt_gr->SetPointError(0,6.124239,3.875761,0.00183284,0.001853688);
    data_pt_gr->SetPoint(1,40.44695,0.8389729);
    data_pt_gr->SetPointError(1,10.44695,9.553052,0.000694316,0.0006960483);
    data_pt_gr->SetPoint(2,57.48906,0.8335857);
    data_pt_gr->SetPointError(2,7.489064,22.51094,0.001768503,0.001746502);
    data_pt_gr->SetPoint(3,94.28154,0.8188415);
    data_pt_gr->SetPointError(3,14.28154,35.71846,0.006759456,0.1811585);
    data_pt_gr->SetPoint(4,152.5486,0.7750756);
    data_pt_gr->SetPointError(4,22.54859,47.45141,0.03315329,0.02222351);

  }

  else {

    cout << "Scenario not supported, exiting." << endl;
    return 0;

  }

  Float_t ptEdges[6] = {20., 30., 50., 80., 130., 200};
  const Int_t nBin = 5;

  TH1F *mc_pt_hist = new TH1F("pt_mc", "", nBin, ptEdges);
  mc_pt_hist->SetMarkerColor(kRed + 1);
  mc_pt_hist->SetLineColor(kRed);
  mc_pt_hist->SetLineWidth(2);
  mc_pt_hist->GetYaxis()->SetTitle("Efficiency");
  mc_pt_hist->GetYaxis()->SetTitleSize(30);
  mc_pt_hist->GetYaxis()->SetTitleFont(43);
  mc_pt_hist->GetYaxis()->SetTitleOffset(.8);
  mc_pt_hist->SetAxisRange(eff_ymin, eff_ymax, "y");

  TH1F *data_pt_hist = new TH1F("pt_data", "", nBin, ptEdges);
  data_pt_hist->SetMarkerColor(kBlue + 1);
  data_pt_hist->SetLineColor(kBlue);
  data_pt_hist->SetLineWidth(2);

  Float_t l1[nBin + 1] = {1., 1., 1., 1., 1., 1.};
  TGraph *liner = new TGraph(nBin + 1, ptEdges, l1);
  liner->SetLineColor(kYellow + 1);
  liner->SetLineWidth(2);

  Double_t x_mc, y_mc, ye_mc, yer_mc, x_data, y_data, ye_data, yer_data;
  Double_t sum_sf = 0., sume_sf = 0.;

  for (Int_t i = 0; i < nBin; i++) {

    x_mc = 0.;
    y_mc = 0.;
    ye_mc = 0.;
    yer_mc = 0.;

    x_data = 0.;
    y_data = 0.;
    ye_data = 0.;
    yer_data = 0.;

    mc_pt_gr->GetPoint(i, x_mc, y_mc);
    ye_mc = mc_pt_gr->GetErrorY(i);
    if (y_mc != 0.) yer_mc = ye_mc / y_mc;
    mc_pt_hist->SetBinContent(i+1, y_mc);
    mc_pt_hist->SetBinError(i+1, ye_mc);

    data_pt_gr->GetPoint(i, x_data, y_data);
    ye_data = data_pt_gr->GetErrorY(i);
    if (y_data != 0.) yer_data = ye_data / y_data;
    data_pt_hist->SetBinContent(i+1, y_data);
    data_pt_hist->SetBinError(i+1, ye_data);

    sum_sf += (y_data / y_mc);
    sume_sf += ((y_data / y_mc) * quadSum(yer_data, yer_mc));

    cout<< "Bin "<< i + 1 << " scale factor: "<< y_data / y_mc << " +- " << (y_data / y_mc) * quadSum(yer_data, yer_mc) << endl;
    //cout<< "  Efficiencies mc: "<< y_mc << " +- " << ye_mc << " data " << y_data << " +- " << ye_data <<endl;

  }

  cout << "\nAverage scale factor: " << sum_sf / nBin << " +- " << sqrt(sume_sf) / nBin << endl;

  TH1F *sf_pt_hist = (TH1F*) data_pt_hist->Clone("");
  sf_pt_hist->Divide(mc_pt_hist);
  sf_pt_hist->SetMarkerColor(kBlack);
  sf_pt_hist->SetLineColor(kBlack);
  sf_pt_hist->SetTitle("");
  sf_pt_hist->GetYaxis()->SetTitle("Data / MC");
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

  TCanvas *c1 = new TCanvas("c1","pt sf", 200, 10, 1600, 900);

  // Upper plot will be in pad1
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad

  mc_pt_hist->Draw();
  data_pt_hist->Draw("same");

  // lower plot will be in pad
  c1->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad);

  sf_pt_hist->Draw();
  liner->Draw("lsame");

  c1->cd();
  c1->SaveAs(("/home/ieeya/Downloads/t_schan/Part1_TagProbe/img/isomu17/sf_pt_" + scenario + ".png").c_str());
  c1->Close();

}
