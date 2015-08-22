Double_t quadSum(Double_t a, Double_t b) {

  Double_t c = 0.;
  c = sqrt((a*a) + (b*b));

  return c;

}

Int_t sf_eta() {

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
  Float_t binEdges[nBin + 1] = {-2.1, -1.6, -1.4, -0.9, -0.45, 0., 0.45, 0.9, 1.4, 1.6, 2.1};

  // Make sure uncertainty in histogram bins is calculated correctly
  TH1::SetDefaultSumw2(kTRUE);

  TGraphAsymmErrors *mc_eta_gr = new TGraphAsymmErrors();
  mc_eta_gr->SetName("mc_eta_gr");
  mc_eta_gr->SetMarkerColor(kRed + 1);
  mc_eta_gr->SetMarkerStyle(2);
  mc_eta_gr->SetMarkerSize(1);
  mc_eta_gr->SetLineColor(kRed);
  mc_eta_gr->SetLineWidth(2);

  TGraphAsymmErrors *data_eta_gr = new TGraphAsymmErrors();
  data_eta_gr->SetName("data_eta_gr");
  data_eta_gr->SetMarkerColor(kBlue + 1);
  data_eta_gr->SetMarkerStyle(2);
  data_eta_gr->SetMarkerSize(1);
  data_eta_gr->SetLineColor(kBlue);
  data_eta_gr->SetLineWidth(2);

  if (argv == "loo") {

    mc_eta_gr->SetPoint(0,-1.829622,0.9004187);
    mc_eta_gr->SetPointError(0,0.2703783,0.2296217,0.0009005865,0.0009021275);
    mc_eta_gr->SetPoint(1,-1.494667,0.8599293);
    mc_eta_gr->SetPointError(1,0.1053335,0.09466653,0.001697629,0.001690569);
    mc_eta_gr->SetPoint(2,-1.138123,0.8881825);
    mc_eta_gr->SetPointError(2,0.2618765,0.2381235,0.0007371101,0.0007397476);
    mc_eta_gr->SetPoint(3,-0.67021,0.9134232);
    mc_eta_gr->SetPointError(3,0.22979,0.22021,0.0006299075,0.0006312126);
    mc_eta_gr->SetPoint(4,-0.2253727,0.9170051);
    mc_eta_gr->SetPointError(4,0.2246273,0.2253727,0.0006080148,0.0006102254);
    mc_eta_gr->SetPoint(5,0.2251495,0.916473);
    mc_eta_gr->SetPointError(5,0.2251495,0.2248505,0.0006044487,0.0006111711);
    mc_eta_gr->SetPoint(6,0.670119,0.9119334);
    mc_eta_gr->SetPointError(6,0.220119,0.229881,0.0006326811,0.0006369905);
    mc_eta_gr->SetPoint(7,1.137958,0.8855015);
    mc_eta_gr->SetPointError(7,0.237958,0.262042,0.0007561855,0.0007549785);
    mc_eta_gr->SetPoint(8,1.495775,0.8566586);
    mc_eta_gr->SetPointError(8,0.0957749,0.1042251,0.001743132,0.001735236);
    mc_eta_gr->SetPoint(9,1.832142,0.8988641);
    mc_eta_gr->SetPointError(9,0.2321423,0.2678577,0.0009142311,0.0009192134);

    data_eta_gr->SetPoint(0,-1.835707,0.8362782);
    data_eta_gr->SetPointError(0,0.264293,0.235707,0.009824314,0.009547206);
    data_eta_gr->SetPoint(1,-1.499942,0.8367056);
    data_eta_gr->SetPointError(1,0.100058,0.09994204,0.01698651,0.01623462);
    data_eta_gr->SetPoint(2,-1.134366,0.8479274);
    data_eta_gr->SetPointError(2,0.2656338,0.2343662,0.007847383,0.007642353);
    data_eta_gr->SetPoint(3,-0.6686036,0.8809022);
    data_eta_gr->SetPointError(3,0.2313964,0.2186036,0.006684059,0.006478008);
    data_eta_gr->SetPoint(4,-0.2284533,0.8936994);
    data_eta_gr->SetPointError(4,0.2215467,0.2284533,0.0003845017,0.0003845017);
    data_eta_gr->SetPoint(5,0.2254793,0.8915235);
    data_eta_gr->SetPointError(5,0.2254793,0.2245207,0.01436592,0.005853673);
    data_eta_gr->SetPoint(6,0.6706857,0.8919494);
    data_eta_gr->SetPointError(6,0.2206857,0.2293143,0.006391775,0.006120441);
    data_eta_gr->SetPoint(7,1.141339,0.8805725);
    data_eta_gr->SetPointError(7,0.2413389,0.2586611,0.006912996,0.006678627);
    data_eta_gr->SetPoint(8,1.493501,0.7858726);
    data_eta_gr->SetPointError(8,0.0935008,0.1064992,0.01889994,0.01830262);
    data_eta_gr->SetPoint(9,1.836226,0.8495346);
    data_eta_gr->SetPointError(9,0.2362258,0.2637742,0.009510228,0.009389427);

  }

  else if (argv == "med") {

    mc_eta_gr->SetPoint(0,-1.830166,0.924022);
    mc_eta_gr->SetPointError(0,0.2698338,0.2301662,0.0008288646,0.000824799);
    mc_eta_gr->SetPoint(1,-1.49474,0.8947927);
    mc_eta_gr->SetPointError(1,0.1052603,0.09473973,0.001596232,0.001585022);
    mc_eta_gr->SetPoint(2,-1.135999,0.9184917);
    mc_eta_gr->SetPointError(2,0.2640009,0.2359991,0.000670703,0.0006674197);
    mc_eta_gr->SetPoint(3,-0.670204,0.9394283);
    mc_eta_gr->SetPointError(3,0.229796,0.220204,0.000558617,0.0005509523);
    mc_eta_gr->SetPoint(4,-0.2250824,0.941637);
    mc_eta_gr->SetPointError(4,0.2249176,0.2250824,0.0005399698,0.0005352159);
    mc_eta_gr->SetPoint(5,0.2250167,0.9409556);
    mc_eta_gr->SetPointError(5,0.2250167,0.2249833,0.0005378494,0.0005366716);
    mc_eta_gr->SetPoint(6,0.670161,0.9377669);
    mc_eta_gr->SetPointError(6,0.220161,0.229839,0.0005652061,0.0005566717);
    mc_eta_gr->SetPoint(7,1.135826,0.9169506);
    mc_eta_gr->SetPointError(7,0.2358261,0.2641739,0.0006815493,0.0006885499);
    mc_eta_gr->SetPoint(8,1.496074,0.8958269);
    mc_eta_gr->SetPointError(8,0.0960738,0.1039262,0.001631588,0.00161359);
    mc_eta_gr->SetPoint(9,1.833044,0.9226088);
    mc_eta_gr->SetPointError(9,0.233044,0.266956,0.0008415083,0.0008418999);

    data_eta_gr->SetPoint(0,-1.832538,0.8628653);
    data_eta_gr->SetPointError(0,0.2674616,0.2325384,0.009639257,0.009143806);
    data_eta_gr->SetPoint(1,-1.499204,0.8807988);
    data_eta_gr->SetPointError(1,0.1007959,0.09920408,0.01635313,0.01539554);
    data_eta_gr->SetPoint(2,-1.129966,0.8947592);
    data_eta_gr->SetPointError(2,0.2700335,0.2299665,0.007165044,0.006935738);
    data_eta_gr->SetPoint(3,-0.6693043,0.9142542);
    data_eta_gr->SetPointError(3,0.2306957,0.2193043,0.005961434,0.005735923);
    data_eta_gr->SetPoint(4,-0.2294668,0.9279297);
    data_eta_gr->SetPointError(4,0.2205332,0.2294668,0.005217369,0.0050385);
    data_eta_gr->SetPoint(5,0.2249342,0.9214477);
    data_eta_gr->SetPointError(5,0.2249342,0.2250658,0.001827277,0.001827277);
    data_eta_gr->SetPoint(6,0.6704476,0.9221645);
    data_eta_gr->SetPointError(6,0.2204476,0.2295524,0.005420911,0.005194437);
    data_eta_gr->SetPoint(7,1.137054,0.9221397);
    data_eta_gr->SetPointError(7,0.2370538,0.2629462,0.006023341,0.005789154);
    data_eta_gr->SetPoint(8,1.492992,0.835933);
    data_eta_gr->SetPointError(8,0.0929917,0.1070083,0.01869774,0.01779254);
    data_eta_gr->SetPoint(9,1.837815,0.8781402);
    data_eta_gr->SetPointError(9,0.2378148,0.2621852,0.008639377,0.008223691);

  }

  else if (argv == "tig") {

    mc_eta_gr->SetPoint(0,-1.831449,0.9418561);
    mc_eta_gr->SetPointError(0,0.2685515,0.2314485,0.0007755087,0.0007734475);
    mc_eta_gr->SetPoint(1,-1.496294,0.9237062);
    mc_eta_gr->SetPointError(1,0.1037063,0.09629371,0.001522144,0.001494914);
    mc_eta_gr->SetPoint(2,-1.130232,0.9421603);
    mc_eta_gr->SetPointError(2,0.2697685,0.2302315,0.0006167363,0.0006137165);
    mc_eta_gr->SetPoint(3,-0.669897,0.9569116);
    mc_eta_gr->SetPointError(3,0.230103,0.219897,0.0004992373,0.0004961595);
    mc_eta_gr->SetPoint(4,-0.2250323,0.9614123);
    mc_eta_gr->SetPointError(4,0.2249677,0.2250323,0.0004643127,0.0004652798);
    mc_eta_gr->SetPoint(5,0.2251417,0.9610095);
    mc_eta_gr->SetPointError(5,0.2251417,0.2248583,0.000464859,0.0004657206);
    mc_eta_gr->SetPoint(6,0.6700029,0.9551258);
    mc_eta_gr->SetPointError(6,0.2200029,0.2299971,0.0005076248,0.0005047349);
    mc_eta_gr->SetPoint(7,1.130131,0.9405041);
    mc_eta_gr->SetPointError(7,0.2301309,0.2698691,0.0006341242,0.0006316168);
    mc_eta_gr->SetPoint(8,1.497894,0.9229235);
    mc_eta_gr->SetPointError(8,0.0978938,0.1021062,0.001554063,0.001535365);
    mc_eta_gr->SetPoint(9,1.834473,0.9408337);
    mc_eta_gr->SetPointError(9,0.2344732,0.2655268,0.0007843827,0.0007865533);

    data_eta_gr->SetPoint(0,-1.834136,0.9001948);
    data_eta_gr->SetPointError(0,0.2658637,0.2341363,0.008893735,0.008414741);
    data_eta_gr->SetPoint(1,-1.503345,0.9292717);
    data_eta_gr->SetPointError(1,0.09665515,0.1033448,0.0148296,0.01349699);
    data_eta_gr->SetPoint(2,-1.122961,0.9310696);
    data_eta_gr->SetPointError(2,0.2770393,0.2229607,0.006364384,0.006058997);
    data_eta_gr->SetPoint(3,-0.6702087,0.9491204);
    data_eta_gr->SetPointError(3,0.2297913,0.2202087,0.005732156,0.004527402);
    data_eta_gr->SetPoint(4,-0.2303704,0.9572794);
    data_eta_gr->SetPointError(4,0.2196296,0.2303704,0.004274528,0.003988787);
    data_eta_gr->SetPoint(5,0.2252881,0.9524109);
    data_eta_gr->SetPointError(5,0.2252881,0.2247119,-0,0.00442478);
    data_eta_gr->SetPoint(6,0.6688907,0.9445236);
    data_eta_gr->SetPointError(6,0.2188907,0.2311093,0.004938905,0.004661192);
    data_eta_gr->SetPoint(7,1.132275,0.9520203);
    data_eta_gr->SetPointError(7,0.2322749,0.2677251,0.005341613,0.005046528);
    data_eta_gr->SetPoint(8,1.493848,0.8730771);
    data_eta_gr->SetPointError(8,0.09384767,0.1061523,0.01862347,0.01782706);
    data_eta_gr->SetPoint(9,1.840039,0.9144067);
    data_eta_gr->SetPointError(9,0.2400389,0.2599611,0.00784205,0.007424896);

  }

  else {

    cout << "ID WP not supported." << endl;
    return 0;

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

  TH1F *mc_eta_hist = new TH1F("", "", nBin, binEdges);
  mc_eta_hist->SetMarkerColor(kRed + 1);
  mc_eta_hist->SetLineColor(kRed);
  mc_eta_hist->SetLineWidth(2);
  mc_eta_hist->GetYaxis()->SetTitle("Efficiency");
  mc_eta_hist->GetYaxis()->SetTitleSize(23);
  mc_eta_hist->GetYaxis()->SetTitleFont(43);
  mc_eta_hist->GetYaxis()->SetTitleOffset(1.25);
  mc_eta_hist->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  mc_eta_hist->GetYaxis()->SetLabelSize(21);
  mc_eta_hist->SetAxisRange(eff_ymin, eff_ymax, "y");

  TH1F *data_eta_hist = new TH1F("", "", nBin, binEdges);
  data_eta_hist->SetMarkerColor(kBlue + 1);
  data_eta_hist->SetLineColor(kBlue);
  data_eta_hist->SetLineWidth(2);

  Float_t l1[nBin + 1];

  Double_t x_mc, y_mc, ye_mc, yer_mc, x_data, y_data, ye_data, yer_data;
  Double_t sum_sf = 0., dif_sf = 0., max_sf = 0., min_sf = 0.;

  for (Int_t i = 0; i < nBin; i++) {

    l1[i] = 1.;

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

  l1[nBin] = 1.;

  TGraph *liner = new TGraph(nBin + 1, binEdges, l1);
  liner->SetLineColor(kYellow + 1);
  liner->SetLineWidth(2);

  TH1F *sf_eta_hist = new TH1F("", "", nBin, binEdges);
  sf_eta_hist->Divide(data_eta_hist, mc_eta_hist, 1., 1., "B");
  sf_eta_hist->SetMarkerColor(kBlack);
  sf_eta_hist->SetLineColor(kBlack);
  sf_eta_hist->SetTitle("");
  sf_eta_hist->GetYaxis()->SetTitle("Data / MC");
  sf_eta_hist->GetYaxis()->SetNdivisions(505);
  sf_eta_hist->GetYaxis()->SetTitleSize(23);
  sf_eta_hist->GetYaxis()->SetTitleFont(43);
  sf_eta_hist->GetYaxis()->SetTitleOffset(1.25);
  sf_eta_hist->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  sf_eta_hist->GetYaxis()->SetLabelSize(21);
  sf_eta_hist->SetAxisRange(sf_ymin, sf_ymax, "y");

  sf_eta_hist->GetXaxis()->SetTitle("Probe #eta");
  sf_eta_hist->GetXaxis()->SetTitleSize(23);
  sf_eta_hist->GetXaxis()->SetTitleFont(43);
  sf_eta_hist->GetXaxis()->SetTitleOffset(2.9);
  sf_eta_hist->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  sf_eta_hist->GetXaxis()->SetLabelSize(21);

  TCanvas *c1 = new TCanvas("c1","eta sf", 200, 10, 1000, 1000);

  // Upper plot will be in pad1
  TPad *pad1 = new TPad("pad1", "pad1", 0., 0.29, 1., 1.);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetGrid();
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad

  mc_eta_gr->SetHistogram(frame_hist);
  data_eta_gr->SetHistogram(frame_hist);
  frame_hist->Draw("func");

  mc_eta_gr->Draw("p");
  data_eta_gr->Draw("samep");

  TLatex txt;
  txt.SetTextSize(0.04);
  txt.SetTextAlign(13);

  txt.DrawLatexNDC(0.06, 0.933, "#bf{CMS} #it{Preliminary}");
  txt.DrawLatexNDC(0.767, 0.941, "40.2 pb^{-1} (13 TeV)");

  TLegend *leg = new TLegend(.75, .05, .93, .19);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.03);

  leg->AddEntry(mc_eta_gr, "MC WP75", "lp");
  leg->AddEntry(data_eta_gr, "Data WPLoose", "lp");
  leg->Draw();

  // lower plot will be in pad
  c1->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0., 0., 1., 0.29);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  pad2->SetGrid();
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad);

  sf_eta_hist->Draw();
  liner->Draw("lsame");
  sf_eta_hist->Draw("same");

  c1->cd();
  c1->SaveAs(("/home/ieeya/Downloads/EGM/TnP/files/act03/plot/eff_eta_" + argv + ".pdf").c_str());
  c1->Close();

  return 0;

}
