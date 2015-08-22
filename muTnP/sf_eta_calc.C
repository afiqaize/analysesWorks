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

    mc_eta_gr->SetPoint(0,-1.86838,0.7995214);
    mc_eta_gr->SetPointError(0,0.2316202,0.2183798,0.0005931561,0.0005918513);
    mc_eta_gr->SetPoint(1,-1.417241,0.8617826);
    mc_eta_gr->SetPointError(1,0.2327595,0.2172405,0.0004556456,0.0004543949);
    mc_eta_gr->SetPoint(2,-1.047956,0.8586515);
    mc_eta_gr->SetPointError(2,0.1520436,0.1479564,0.0005296333,0.0005279902);
    mc_eta_gr->SetPoint(3,-0.66943,0.9096112);
    mc_eta_gr->SetPointError(3,0.23057,0.21943,0.0003358943,0.0003347802);
    mc_eta_gr->SetPoint(4,-0.2240906,0.919867);
    mc_eta_gr->SetPointError(4,0.2259094,0.2240906,0.0003106755,0.0003095861);
    mc_eta_gr->SetPoint(5,0.2240117,0.920754);
    mc_eta_gr->SetPointError(5,0.2240117,0.2259883,0.0003101179,0.0003090191);
    mc_eta_gr->SetPoint(6,0.6694087,0.9077555);
    mc_eta_gr->SetPointError(6,0.2194087,0.2305913,0.0003403255,0.0003392076);
    mc_eta_gr->SetPoint(7,1.047288,0.8595425);
    mc_eta_gr->SetPointError(7,0.1472878,0.1527122,0.000532236,0.000530564);
    mc_eta_gr->SetPoint(8,1.417839,0.8565741);
    mc_eta_gr->SetPointError(8,0.2178395,0.2321605,0.0004671892,0.0004659327);
    mc_eta_gr->SetPoint(9,1.869129,0.7849424);
    mc_eta_gr->SetPointError(9,0.2191293,0.2308707,0.0006172086,0.0006159323);

    data_eta_gr->SetPoint(0,-1.868882,0.82801);
    data_eta_gr->SetPointError(0,0.2311176,0.2188824,0.002314924,0.002301582);
    data_eta_gr->SetPoint(1,-1.417679,0.8635589);
    data_eta_gr->SetPointError(1,0.2323207,0.2176793,0.001844261,0.001834545);
    data_eta_gr->SetPoint(2,-1.047022,0.868548);
    data_eta_gr->SetPointError(2,0.1529783,0.1470217,0.002081084,0.002063542);
    data_eta_gr->SetPoint(3,-0.6692046,0.8947471);
    data_eta_gr->SetPointError(3,0.2307954,0.2192046,0.001420159,0.001441598);
    data_eta_gr->SetPoint(4,-0.2243651,0.9000754);
    data_eta_gr->SetPointError(4,0.2256349,0.2243651,0.001382941,0.001380326);
    data_eta_gr->SetPoint(5,0.2235801,0.902705);
    data_eta_gr->SetPointError(5,0.2235801,0.2264199,0.001359295,0.001353093);
    data_eta_gr->SetPoint(6,0.6692666,0.8955032);
    data_eta_gr->SetPointError(6,0.2192666,0.2307334,0.00144139,0.001457894);
    data_eta_gr->SetPoint(7,1.04765,0.8633123);
    data_eta_gr->SetPointError(7,0.1476503,0.1523497,0.002098349,0.002099758);
    data_eta_gr->SetPoint(8,1.417202,0.8478178);
    data_eta_gr->SetPointError(8,0.217202,0.232798,0.001936715,0.001923869);
    data_eta_gr->SetPoint(9,1.867179,0.8412232);
    data_eta_gr->SetPointError(9,0.2171791,0.2328209,0.002212608,0.002206214);

  }

  else if (scenario == "r11ab_03") {

    mc_eta_gr->SetPoint(0,-1.868171,0.782932);
    mc_eta_gr->SetPointError(0,0.2318294,0.2181706,0.0006107667,0.0006095339);
    mc_eta_gr->SetPoint(1,-1.417316,0.8403162);
    mc_eta_gr->SetPointError(1,0.2326838,0.2173162,0.0004827777,0.0004816048);
    mc_eta_gr->SetPoint(2,-1.04792,0.8402417);
    mc_eta_gr->SetPointError(2,0.1520805,0.1479195,0.0005555163,0.0005539652);
    mc_eta_gr->SetPoint(3,-0.6695814,0.8921657);
    mc_eta_gr->SetPointError(3,0.2304186,0.2195814,0.0003626095,0.0003615467);
    mc_eta_gr->SetPoint(4,-0.2240705,0.9047071);
    mc_eta_gr->SetPointError(4,0.2259295,0.2240705,0.0003352504,0.0003342044);
    mc_eta_gr->SetPoint(5,0.2239957,0.906056);
    mc_eta_gr->SetPointError(5,0.2239957,0.2260043,0.0003341179,0.0003330621);
    mc_eta_gr->SetPoint(6,0.6692371,0.8902333);
    mc_eta_gr->SetPointError(6,0.2192371,0.2307629,0.0003669275,0.0003658612);
    mc_eta_gr->SetPoint(7,1.047165,0.8416174);
    mc_eta_gr->SetPointError(7,0.1471655,0.1528345,0.0005581294,0.0005565464);
    mc_eta_gr->SetPoint(8,1.417878,0.8348124);
    mc_eta_gr->SetPointError(8,0.2178779,0.2321221,0.0004942594,0.0004930825);
    mc_eta_gr->SetPoint(9,1.869087,0.7699485);
    mc_eta_gr->SetPointError(9,0.2190873,0.2309127,0.000632439,0.0006312288);

    data_eta_gr->SetPoint(0,-1.871494,0.7961821);
    data_eta_gr->SetPointError(0,0.2285056,0.2214944,0.001634904,0.001644249);
    data_eta_gr->SetPoint(1,-1.417084,0.8409349);
    data_eta_gr->SetPointError(1,0.2329158,0.2170842,0.00130698,0.001302522);
    data_eta_gr->SetPoint(2,-1.046806,0.8543268);
    data_eta_gr->SetPointError(2,0.1531945,0.1468055,0.001434821,0.00142465);
    data_eta_gr->SetPoint(3,-0.6702068,0.8774799);
    data_eta_gr->SetPointError(3,0.2297932,0.2202068,0.0010267,0.001020332);
    data_eta_gr->SetPoint(4,-0.2238056,0.8836152);
    data_eta_gr->SetPointError(4,0.2261944,0.2238056,0.000976152,0.0009762142);
    data_eta_gr->SetPoint(5,0.2234861,0.8866499);
    data_eta_gr->SetPointError(5,0.2234861,0.2265139,0.0009692998,0.0009617757);
    data_eta_gr->SetPoint(6,0.6688665,0.8797154);
    data_eta_gr->SetPointError(6,0.2188665,0.2311335,0.001019392,0.001014589);
    data_eta_gr->SetPoint(7,1.04662,0.8536259);
    data_eta_gr->SetPointError(7,0.1466205,0.1533795,0.001431579,0.001427786);
    data_eta_gr->SetPoint(8,1.41611,0.8273635);
    data_eta_gr->SetPointError(8,0.2161098,0.2338902,0.001359048,0.00135852);
    data_eta_gr->SetPoint(9,1.86979,0.8093114);
    data_eta_gr->SetPointError(9,0.2197902,0.2302098,0.001597748,0.001589389);

  }

  else if (scenario == "r11b_04") {

    mc_eta_gr->SetPoint(0,-1.868021,0.7753776);
    mc_eta_gr->SetPointError(0,0.2319786,0.2180214,0.0006184966,0.0006172958);
    mc_eta_gr->SetPoint(1,-1.41741,0.8304193);
    mc_eta_gr->SetPointError(1,0.2325896,0.2174104,0.0004944344,0.0004932961);
    mc_eta_gr->SetPoint(2,-1.047899,0.8319871);
    mc_eta_gr->SetPointError(2,0.1521005,0.1478995,0.0005667252,0.0005652123);
    mc_eta_gr->SetPoint(3,-0.6696206,0.8840301);
    mc_eta_gr->SetPointError(3,0.2303794,0.2196206,0.0003743403,0.0003732992);
    mc_eta_gr->SetPoint(4,-0.2240717,0.8979218);
    mc_eta_gr->SetPointError(4,0.2259283,0.2240717,0.0003455848,0.0003445567);
    mc_eta_gr->SetPoint(5,0.224021,0.8991673);
    mc_eta_gr->SetPointError(5,0.224021,0.225979,0.0003447555,0.0003437179);
    mc_eta_gr->SetPoint(6,0.6691805,0.882004);
    mc_eta_gr->SetPointError(6,0.2191805,0.2308195,0.0003785452,0.0003775019);
    mc_eta_gr->SetPoint(7,1.047185,0.8332385);
    mc_eta_gr->SetPointError(7,0.1471847,0.1528153,0.0005696473,0.0005681039);
    mc_eta_gr->SetPoint(8,1.417844,0.8249634);
    mc_eta_gr->SetPointError(8,0.2178442,0.2321558,0.000505789,0.0005046464);
    mc_eta_gr->SetPoint(9,1.869038,0.7628416);
    mc_eta_gr->SetPointError(9,0.2190382,0.2309618,0.0006394743,0.0006382947);

    data_eta_gr->SetPoint(0,-1.87186,0.7735479);
    data_eta_gr->SetPointError(0,0.22814,0.22186,0.002680643,0.002668542);
    data_eta_gr->SetPoint(1,-1.417005,0.8211248);
    data_eta_gr->SetPointError(1,0.2329954,0.2170046,0.002186533,0.002173973);
    data_eta_gr->SetPoint(2,-1.046489,0.8036982);
    data_eta_gr->SetPointError(2,0.1535106,0.1464894,0.002517941,0.00250351);
    data_eta_gr->SetPoint(3,-0.6689632,0.8695973);
    data_eta_gr->SetPointError(3,0.2310368,0.2189632,0.001643221,0.001627639);
    data_eta_gr->SetPoint(4,-0.2243822,0.8774297);
    data_eta_gr->SetPointError(4,0.2256178,0.2243822,0.00155731,0.001557406);
    data_eta_gr->SetPoint(5,0.2231291,0.8779198);
    data_eta_gr->SetPointError(5,0.2231291,0.2268709,0.001562685,0.001552265);
    data_eta_gr->SetPoint(6,0.6695505,0.8712197);
    data_eta_gr->SetPointError(6,0.2195505,0.2304495,0.001652604,0.001638263);
    data_eta_gr->SetPoint(7,1.045993,0.7968811);
    data_eta_gr->SetPointError(7,0.1459928,0.1540072,0.002562149,0.002558131);
    data_eta_gr->SetPoint(8,1.416851,0.8102566);
    data_eta_gr->SetPointError(8,0.2168512,0.2331488,0.002223707,0.00220749);
    data_eta_gr->SetPoint(9,1.869563,0.7828316);
    data_eta_gr->SetPointError(9,0.219563,0.230437,0.002650316,0.002629268);

  }

  else {

    cout << "Scenario not supported, exiting." << endl;
    return 0;

  }

  const Int_t nBin = 10;
  Float_t etaEdges[nBin + 1] = {-2.1, -1.65, -1.2, -0.9, -0.45, 0., 0.45, 0.9, 1.2, 1.65, 2.1};

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

  Float_t l1[nBin + 1] = {1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1.};
  TGraph *liner = new TGraph(nBin + 1, etaEdges, l1);
  liner->SetLineColor(kYellow + 1);
  liner->SetLineWidth(2);

  Double_t x_mc, y_mc, ye_mc, yer_mc, x_data, y_data, ye_data, yer_data;
  Double_t sum_sf = 0., dif_sf = 0., max_sf = 0., min_sf = 0.;

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
    //sume_sf += ((y_data / y_mc) * quadSum(yer_data, yer_mc)) * ((y_data / y_mc) * quadSum(yer_data, yer_mc));

    if (i == 0) {

      max_sf = (y_data / y_mc);
      min_sf = (y_data / y_mc);

    }

    else if (i != 0) {

      if ((y_data / y_mc) > max_sf) max_sf = (y_data / y_mc);
      if ((y_data / y_mc) < min_sf) min_sf = (y_data / y_mc);

    }

    cout<< "Bin "<< i + 1 << " scale factor: "<< y_data / y_mc << " +- " << (y_data / y_mc) * quadSum(yer_data, yer_mc) << endl;
    //cout<< "  Efficiencies mc: "<< y_mc << " +- " << ye_mc << " data " << y_data << " +- " << ye_data <<endl;

  }

  dif_sf = max_sf - min_sf;

  cout << "\nAverage scale factor: " << sum_sf / nBin << " +- " << dif_sf / (2 * sqrt(nBin)) << endl;

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
  sf_eta_hist->Draw("same");

  c1->cd();
  //c1->SaveAs(("/home/ieeya/Downloads/t_schan/Part1_TagProbe/img/isomu17/sf_eta_" + scenario + ".png").c_str());
  c1->Close();

  return 0;

}
