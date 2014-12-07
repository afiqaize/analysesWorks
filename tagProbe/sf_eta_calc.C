Double_t quadSum(Double_t a, Double_t b) {

  Double_t c = 0.;
  c = sqrt((a*a) + (b*b));

  return c;

}

Int_t sf_eta_calc() {

  // Code to calculate draw the scale factor
  // Save the (fit) eff canvases in .C and then take the relevant graphs, port them here
  // MC is red, data is blue

  gStyle->SetOptStat(0);

  string scenario = "r11a_02";
  Float_t eff_ymin = 0., eff_ymax = 1.;
  Float_t sf_ymin = .8, sf_ymax = 1.2;

  // Make sure uncertainty in histogram bins is calculated correctly
  TH1::SetDefaultSumw2(kTRUE);

  TGraphAsymmErrors *mc_eta_gr = new TGraphAsymmErrors(8);
  mc_eta_gr->SetName("mc_eta_gr");
  mc_eta_gr->SetTitle("Efficiency of IsoMu17::pass");
  mc_eta_gr->SetFillColor(1);
  mc_eta_gr->SetLineWidth(2);

  TGraphAsymmErrors *data_eta_gr = new TGraphAsymmErrors(8);
  data_eta_gr->SetName("data_eta_gr");
  data_eta_gr->SetTitle("Efficiency of IsoMu17::pass");
  data_eta_gr->SetFillColor(1);
  data_eta_gr->SetLineWidth(2);

  if (scenario == "r11a_02") {

    mc_eta_gr->SetPoint(0,-1.785611,0.8172771);
    mc_eta_gr->SetPointError(0,0.3143887,0.2856113,0.0004854486,0.0004844546);
    mc_eta_gr->SetPoint(1,-1.190907,0.859932);
    mc_eta_gr->SetPointError(1,0.3090925,0.2909075,0.0003809205,0.0003800598);
    mc_eta_gr->SetPoint(2,-0.6435093,0.9115699);
    mc_eta_gr->SetPointError(2,0.2564907,0.2435093,0.0003144192,0.0003134185);
    mc_eta_gr->SetPoint(3,-0.1984736,0.9188173);
    mc_eta_gr->SetPointError(3,0.2015264,0.1984736,0.0003319273,0.0003307019);
    mc_eta_gr->SetPoint(4,0.1985477,0.9197997);
    mc_eta_gr->SetPointError(4,0.1985477,0.2014523,0.0003310543,0.0003298189);
    mc_eta_gr->SetPoint(5,0.643595,0.9099236);
    mc_eta_gr->SetPointError(5,0.243595,0.256405,0.0003183809,0.0003173758);
    mc_eta_gr->SetPoint(6,1.190122,0.8584668);
    mc_eta_gr->SetPointError(6,0.2901221,0.3098779,0.0003860938,0.0003852209);
    mc_eta_gr->SetPoint(7,1.78535,0.8048112);
    mc_eta_gr->SetPointError(7,0.2853502,0.3146498,0.0005038087,0.0005028308);

    data_eta_gr->SetPoint(0,-1.784993,0.8389081);
    data_eta_gr->SetPointError(0,0.3150069,0.2849931,0.001900529,0.00188168);
    data_eta_gr->SetPoint(1,-1.190229,0.865089);
    data_eta_gr->SetPointError(1,0.3097705,0.2902295,0.001510729,0.001506748);
    data_eta_gr->SetPoint(2,-0.6429913,0.8967099);
    data_eta_gr->SetPointError(2,0.2570087,0.2429913,0.001325808,0.001329979);
    data_eta_gr->SetPoint(3,-0.1983636,0.8980814);
    data_eta_gr->SetPointError(3,0.2016364,0.1983636,0.001469743,0.001462846);
    data_eta_gr->SetPoint(4,0.1977112,0.9008767);
    data_eta_gr->SetPointError(4,0.1977112,0.2022888,0.001434065,0.001429383);
    data_eta_gr->SetPoint(5,0.6431362,0.8975736);
    data_eta_gr->SetPointError(5,0.2431362,0.2568638,0.001351592,0.001344478);
    data_eta_gr->SetPoint(6,1.188803,0.8548193);
    data_eta_gr->SetPointError(6,0.2888032,0.3111968,0.001566127,0.001545654);
    data_eta_gr->SetPoint(7,1.785407,0.8438683);
    data_eta_gr->SetPointError(7,0.2854069,0.3145931,0.001871042,0.001840095);

  }

  else if (scenario == "r11ab_03") {

    mc_eta_gr->SetPoint(0,-1.785218,0.8004836);
    mc_eta_gr->SetPointError(0,0.3147822,0.2852178,0.0005017261,0.0005007856);
    mc_eta_gr->SetPoint(1,-1.190709,0.8392132);
    mc_eta_gr->SetPointError(1,0.3092915,0.2907085,0.0004023478,0.0004015397);
    mc_eta_gr->SetPoint(2,-0.6436553,0.894207);
    mc_eta_gr->SetPointError(2,0.2563447,0.2436553,0.0003399324,0.0003389773);
    mc_eta_gr->SetPoint(3,-0.198463,0.9038508);
    mc_eta_gr->SetPointError(3,0.201537,0.198463,0.0003574728,0.0003562958);
    mc_eta_gr->SetPoint(4,0.1985287,0.9053184);
    mc_eta_gr->SetPointError(4,0.1985287,0.2014713,0.000355972,0.0003547845);
    mc_eta_gr->SetPoint(5,0.643416,0.8925212);
    mc_eta_gr->SetPointError(5,0.243416,0.256584,0.0003437495,0.0003427904);
    mc_eta_gr->SetPoint(6,1.189847,0.8376233);
    mc_eta_gr->SetPointError(6,0.2898468,0.3101532,0.0004078721,0.0004070522);
    mc_eta_gr->SetPoint(7,1.785072,0.7894055);
    mc_eta_gr->SetPointError(7,0.2850718,0.3149282,0.0005180978,0.0005171698);

    data_eta_gr->SetPoint(0,-1.787331,0.8126398);
    data_eta_gr->SetPointError(0,0.3126694,0.2873306,0.001345817,0.001343351);
    data_eta_gr->SetPoint(1,-1.188963,0.8449417);
    data_eta_gr->SetPointError(1,0.3110373,0.2889627,0.001058864,0.001064367);
    data_eta_gr->SetPoint(2,-0.6442679,0.8792217);
    data_eta_gr->SetPointError(2,0.2557321,0.2442679,0.0009613358,0.0009634586);
    data_eta_gr->SetPoint(3,-0.19836,0.882069);
    data_eta_gr->SetPointError(3,0.20164,0.19836,0.001040228,0.001047428);
    data_eta_gr->SetPoint(4,0.1981361,0.8855454);
    data_eta_gr->SetPointError(4,0.1981361,0.2018639,0.001023869,0.001018245);
    data_eta_gr->SetPoint(5,0.6432538,0.881163);
    data_eta_gr->SetPointError(5,0.2432538,0.2567462,0.0009521884,0.0009491548);
    data_eta_gr->SetPoint(6,1.188552,0.8368238);
    data_eta_gr->SetPointError(6,0.2885517,0.3114483,0.00108716,0.00108259);
    data_eta_gr->SetPoint(7,1.787525,0.8198208);
    data_eta_gr->SetPointError(7,0.2875251,0.3124749,0.001322629,0.001323188);

  }

  else if (scenario == "r11b_04") {

    mc_eta_gr->SetPoint(0,-1.784969,0.7928592);
    mc_eta_gr->SetPointError(0,0.3150305,0.2849695,0.0005087742,0.0005078575);
    mc_eta_gr->SetPoint(1,-1.190658,0.8297483);
    mc_eta_gr->SetPointError(1,0.3093423,0.2906577,0.000411629,0.0004108436);
    mc_eta_gr->SetPoint(2,-0.6436895,0.8861458);
    mc_eta_gr->SetPointError(2,0.2563105,0.2436895,0.0003510714,0.0003501355);
    mc_eta_gr->SetPoint(3,-0.1984793,0.8971488);
    mc_eta_gr->SetPointError(3,0.2015207,0.1984793,0.0003682344,0.0003670774);
    mc_eta_gr->SetPoint(4,0.1985597,0.8985416);
    mc_eta_gr->SetPointError(4,0.1985597,0.2014403,0.0003670223,0.000365855);
    mc_eta_gr->SetPoint(5,0.6433753,0.8843396);
    mc_eta_gr->SetPointError(5,0.2433753,0.2566247,0.0003548451,0.0003539065);
    mc_eta_gr->SetPoint(6,1.189758,0.828067);
    mc_eta_gr->SetPointError(6,0.2897584,0.3102416,0.000417248,0.0004164513);
    mc_eta_gr->SetPoint(7,1.784988,0.7821654);
    mc_eta_gr->SetPointError(7,0.2849878,0.3150122,0.0005246916,0.0005237861);

    data_eta_gr->SetPoint(0,-1.787827,0.7913129);
    data_eta_gr->SetPointError(0,0.3121727,0.2878273,0.002272479,0.002252167);
    data_eta_gr->SetPoint(1,-1.187769,0.8086454);
    data_eta_gr->SetPointError(1,0.3122307,0.2877693,0.001866329,0.001851775);
    data_eta_gr->SetPoint(2,-0.6431265,0.8716632);
    data_eta_gr->SetPointError(2,0.2568735,0.2431265,0.001531727,0.001523636);
    data_eta_gr->SetPoint(3,-0.1986915,0.8754946);
    data_eta_gr->SetPointError(3,0.2013085,0.1986915,0.001644972,0.001636653);
    data_eta_gr->SetPoint(4,0.1977053,0.8760325);
    data_eta_gr->SetPointError(4,0.1977053,0.2022947,0.001663243,0.001661933);
    data_eta_gr->SetPoint(5,0.6437529,0.8732783);
    data_eta_gr->SetPointError(5,0.2437529,0.2562471,0.001543742,0.001536492);
    data_eta_gr->SetPoint(6,1.186747,0.7984327);
    data_eta_gr->SetPointError(6,0.2867469,0.3132531,0.001864916,0.001858276);
    data_eta_gr->SetPoint(7,1.786663,0.7963776);
    data_eta_gr->SetPointError(7,0.286663,0.313337,0.002194154,0.002183899);

  }

  else {

    cout << "Scenario not supported, exiting." << endl;
    return 0;

  }

  Float_t etaEdges[9] = {-2.1, -1.5, -0.9, -0.4, 0., 0.4, 0.9, 1.5, 2.1};
  const Int_t nBin = 8;

  TH1F *mc_eta_hist = new TH1F("eta_mc", "", nBin, etaEdges);
  mc_eta_hist->SetMarkerColor(kRed + 1);
  mc_eta_hist->SetLineColor(kRed);
  mc_eta_hist->SetLineWidth(2);
  mc_eta_hist->GetYaxis()->SetTitle("Efficiency");
  mc_eta_hist->GetYaxis()->SetTitleSize(30);
  mc_eta_hist->GetYaxis()->SetTitleFont(43);
  mc_eta_hist->GetYaxis()->SetTitleOffset(.8);
  mc_eta_hist->SetAxisRange(eff_ymin, eff_ymax, "y");

  TH1F *data_eta_hist = new TH1F("eta_data", "", nBin, etaEdges);
  data_eta_hist->SetMarkerColor(kBlue + 1);
  data_eta_hist->SetLineColor(kBlue);
  data_eta_hist->SetLineWidth(2);

  Float_t l1[nBin + 1] = {1., 1., 1., 1., 1., 1., 1., 1., 1.};
  TGraph *liner = new TGraph(nBin + 1, etaEdges, l1);
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

    mc_eta_gr->GetPoint(i, x_mc, y_mc);
    ye_mc = mc_eta_gr->GetErrorY(i);
    if (y_mc != 0.) yer_mc = ye_mc / y_mc;
    mc_eta_hist->SetBinContent(i+1, y_mc);
    mc_eta_hist->SetBinError(i+1, ye_mc);

    data_eta_gr->GetPoint(i, x_data, y_data);
    ye_data = data_eta_gr->GetErrorY(i);
    if (y_data != 0.) yer_data = ye_data / y_data;
    data_eta_hist->SetBinContent(i+1, y_data);
    data_eta_hist->SetBinError(i+1, ye_data);

    sum_sf += (y_data / y_mc);
    sume_sf += ((y_data / y_mc) * quadSum(yer_data, yer_mc));

    cout<< "Bin "<< i + 1 << " scale factor: "<< y_data / y_mc << " +- " << (y_data / y_mc) * quadSum(yer_data, yer_mc) << endl;
    //cout<< "  Efficiencies mc: "<< y_mc << " +- " << ye_mc << " data " << y_data << " +- " << ye_data <<endl;

  }

  cout << "\nAverage scale factor: " << sum_sf / nBin << " +- " << sqrt(sume_sf) / nBin <<endl;

  TH1F *sf_eta_hist = (TH1F*) data_eta_hist->Clone("");
  sf_eta_hist->Divide(mc_eta_hist);
  sf_eta_hist->SetMarkerColor(kBlack);
  sf_eta_hist->SetLineColor(kBlack);
  sf_eta_hist->SetTitle("");
  sf_eta_hist->GetYaxis()->SetTitle("Data / MC");
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

  TCanvas *c1 = new TCanvas("c1","eta sf", 200, 10, 1600, 900);

  // Upper plot will be in pad1
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad

  mc_eta_hist->Draw();
  data_eta_hist->Draw("same");

  // lower plot will be in pad
  c1->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad);

  sf_eta_hist->Draw();
  liner->Draw("lsame");

  c1->cd();
  c1->SaveAs(("/home/ieeya/Downloads/t_schan/Part1_TagProbe/img/isomu17/sf_eta_" + scenario + ".png").c_str());
  c1->Close();

  return 0;

}
