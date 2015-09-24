#include "TTree.h"
#include "TFile.h"
#include "TStopwatch.h"
#include "TChain.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TCanvas.h"
#include <vector>
#include <iostream>

void addNVtxWeight(TString cut = "nvtx > 0") {

    if (gROOT->GetListOfFiles()->GetSize() < 2) {
        std::cerr << "USAGE: root.exe -b -l -q mcFile.root dataFile.root addNVtxWeight.cxx+" << std::endl;
        return;
    }

    TString outfile = "pts2cw1_chi0.root";

    std::cout << "Gathering trees ..." << std::endl;
    TTree  &tMC = * (TTree *) ((TFile*)gROOT->GetListOfFiles()->At(0))->Get("tree");

    TTree  &tData = * (TTree *) ((TFile*)gROOT->GetListOfFiles()->At(1))->Get("tree");

    //TCanvas *c1 = new TCanvas("c1","c1");
    //c1->cd();

    std::cout << "Filling distributions of vertices ..." << std::endl;
    tData.Draw("nvtx>>hData(100, -0.5, 99.5)", cut);

    tMC.Draw("nvtx>>hMC(100, -0.5, 99.5)", cut, "same");

    std::cout << "Computing weights ..." << std::endl;
    TH1F *hData = (TH1F*) gROOT->FindObject("hData");
    hData->SetLineColor(kRed);

    TH1F *hMC = (TH1F*) gROOT->FindObject("hMC");
    hMC->SetLineColor(kBlue);

    hData->Scale(1.0 / hData->Integral());
    hMC->Scale(1.0 / hMC->Integral());

    //c1->cd();
    //hData->Draw();
    //hMC->Draw("same");

    //c1->Print("nVtx.png");

    std::vector<double> weights(hData->GetNbinsX() + 1, 1.0);

    for (int i = 1, n = weights.size(); i < n; ++i) {

        double nMC = hMC->GetBinContent(i), nData = hData->GetBinContent(i);
        weights[i - 1] = (nMC > 0. ? nData/nMC : 1.0);

    }

    std::cout << "Adding weight column ..." << std::endl;
    Int_t nVtx;
    Float_t weight;
    tMC.SetBranchAddress("nvtx", &nVtx);

    TFile *fOut = new TFile(outfile, "RECREATE");

    TTree *tOut = tMC.CloneTree(0);
    tOut->SetAutoSave(3000000);
    tOut->Branch("puWgt", &weight, "puWgt/F");

    int step = tMC.GetEntries() / 100;
    double evDenom = 100.0 / double(tMC.GetEntries());

    TStopwatch timer; timer.Start();

    for (int i = 0, n = tMC.GetEntries(); i < n; ++i) {

        tMC.GetEntry(i);
        weight = weights[int(nVtx)];

        if (i < 20) {

            printf("event with %d primary vertices gets a weight of %.4f\n", int(nVtx), weight);

        }

        tOut->Fill();

        if ((i+1) % step == 0) { 

            double totalTime = timer.RealTime() / 60.; timer.Continue();
            double fraction = double(i + 1)/double(n + 1), remaining = totalTime * (1 - fraction) / fraction;

            printf("Done %9d/%9d   %5.1f%%   (elapsed %5.1f min, remaining %5.1f min)\n", i, n, i*evDenom, totalTime, remaining); 
            fflush(stdout); 

        }
    }

    fOut->cd();
    tOut->Write();

    std::cout << "Wrote output to " << fOut->GetName() << std::endl;
    fOut->Close();

}
