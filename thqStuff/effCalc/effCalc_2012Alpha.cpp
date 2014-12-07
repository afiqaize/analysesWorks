/***
effCalc.cpp
- takes the information provided by BTagEff plugin and obtains the (mis)tagging efficiency for each process
- why is there no (easy) way to rebin 2D histogram non-uniformly?
***/

#include <TFile.h>
#include <TTree.h>
#include <TTreeFormula.h>
#include <TH1D.h>
#include <TH2D.h>

#include <boost/filesystem.hpp>

#include <string>
#include <vector>
#include <initializer_list>
#include <memory>


using namespace std;


/// A structure to describe a source sample
struct Sample
{
    /// Constructor without parameters
    Sample() = default;
    
    /// Constructor from sampe name and names of files
    Sample(string const &processName_, initializer_list<string> const &fileNames_):
        processName(processName_), fileNames(fileNames_)
    {}
    
    /// Human-readable name of the sample
    string processName;
    
    /// Names of files joined into the sample
    vector<string> fileNames;
};

int main() {
   
    // Define a list of samples to be read in each folder
    vector<Sample> samples;
    samples.emplace_back(Sample("thq", {"tqh-nc-mg-v2_rev468_Goi.root"}));
    samples.emplace_back(Sample("tth", {"tth_rev468_swr.root"}));
    samples.emplace_back(Sample("t-tchan",
     {"t-tchan-pw_rev468_QJd.root", "tbar-tchan-pw_rev468_koy.root"}));
    samples.emplace_back(Sample("t-tWchan",
     {"t-tWchan-DR-pw_rev468_trK.root", "tbar-tWchan-DR-pw_rev468_bqK.root"}));
    samples.emplace_back(Sample("ttbar",
     {"ttbar-semilep-mg_rev468_SQQ.root", "ttbar-dilep-mg_rev468_Ple.root"}));
    samples.emplace_back(Sample("ttbar-dilep",
     {"ttbar-dilep-mg_rev468_Ple.root"}));
    samples.emplace_back(Sample("ttbar-semilep",
     {"ttbar-semilep-mg_rev468_SQQ.root"}));
    samples.emplace_back(Sample("Wjets", {"Wjets-mg_rev468_tkF.root", "Wjets-2p-mg_rev468.root",
     "Wjets-3p-mg_rev468.root", "Wjets-4p-mg_rev468.root"}));
    
    // Directory containing the tuples
    string const filePrefix("../tuples/");
    
    // Make sure uncertainty in histogram bins is calculated correctly
    TH1::SetDefaultSumw2(kTRUE);

    // Loop over the samples
    for (auto const &sample: samples) {

        // Create a directory to host files with histograms
        string const outDirectory(string("../hists/"));
        boost::filesystem::create_directories(outDirectory);

        // A file to store histograms for the current sample
        TFile outFile((outDirectory + sample.processName + ".root").c_str(), "recreate");

        // Decide the parameters to be used
        Int_t ptBin = 16; Float_t ptMin = 0., ptMax = 400.;
        Int_t etaBin = 4; Float_t etaMin = 0., etaMax = 2.4;

        // Test binning
        //Float_t ptEdges[13] = {20., 40., 60., 80., 100., 130., 160., 190., 220., 250., 300., 350., 400.};
        //Float_t etaEdges[13] = {0., 0.2, 0.4, 0.6, 0.8, 1., 1.2, 1.4, 1.6, 1.8, 2., 2.2, 2.4};

        // BTV POG recommended bins
        //Float_t ptEdges[16] = {20., 30., 40., 50., 60., 70., 80., 100., 120., 160., 210., 260., 320., 400., 500., 670.};
        //Float_t etaEdges[5] = {0., .6, 1.2, 1.8, 2.4};

        // Dan-extended BTV bins
        Float_t ptEdges[17] = {20., 30., 40., 50., 60., 70., 80., 100., 120., 160., 210., 260., 320., 400., 500., 600., 800.};
        Float_t etaEdges[5] = {0., .6, 1.2, 1.8, 2.4};

        // b hists for hosting hists from sample
        TH2D *pteta_num_b =  new TH2D("PtEta_Num_b", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
        TH2D *pteta_den_b =  new TH2D("PtEta_Den_b", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
        TH2D *pteta_eff_b =  new TH2D("PtEta_Eff_b", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
        
        TH1D *pt_num_b = new TH1D("Pt_Num_b", ";p_{T} [GeV]", ptBin, ptEdges);
        TH1D *pt_den_b = new TH1D("Pt_Den_b", ";p_{T} [GeV]", ptBin, ptEdges);
        TH1D *pt_eff_b = new TH1D("Pt_Eff_b", ";p_{T} [GeV]", ptBin, ptEdges);

        TH1D *eta_num_b = new TH1D("Eta_Num_b", ";#eta", etaBin, etaMin, etaMax);
        TH1D *eta_den_b = new TH1D("Eta_Den_b", ";#eta", etaBin, etaMin, etaMax);
        TH1D *eta_eff_b = new TH1D("Eta_Eff_b", ";#eta", etaBin, etaMin, etaMax);

        // c hists for hosting hists from sample
        TH2D *pteta_num_c =  new TH2D("PtEta_Num_c", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
        TH2D *pteta_den_c =  new TH2D("PtEta_Den_c", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
        TH2D *pteta_eff_c =  new TH2D("PtEta_Eff_c", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
        
        TH1D *pt_num_c = new TH1D("Pt_Num_c", ";p_{T} [GeV]", ptBin, ptEdges);
        TH1D *pt_den_c = new TH1D("Pt_Den_c", ";p_{T} [GeV]", ptBin, ptEdges);
        TH1D *pt_eff_c = new TH1D("Pt_Eff_c", ";p_{T} [GeV]", ptBin, ptEdges);

        TH1D *eta_num_c = new TH1D("Eta_Num_c", ";#eta", etaBin, etaMin, etaMax);
        TH1D *eta_den_c = new TH1D("Eta_Den_c", ";#eta", etaBin, etaMin, etaMax);
        TH1D *eta_eff_c = new TH1D("Eta_Eff_c", ";#eta", etaBin, etaMin, etaMax);

        // uds hists for hosting hists from sample
        TH2D *pteta_num_uds =  new TH2D("PtEta_Num_uds", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
        TH2D *pteta_den_uds =  new TH2D("PtEta_Den_uds", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
        TH2D *pteta_eff_uds =  new TH2D("PtEta_Eff_uds", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
        
        TH1D *pt_num_uds = new TH1D("Pt_Num_uds", ";p_{T} [GeV]", ptBin, ptEdges);
        TH1D *pt_den_uds = new TH1D("Pt_Den_uds", ";p_{T} [GeV]", ptBin, ptEdges);
        TH1D *pt_eff_uds = new TH1D("Pt_Eff_uds", ";p_{T} [GeV]", ptBin, ptEdges);

        TH1D *eta_num_uds = new TH1D("Eta_Num_uds", ";#eta", etaBin, etaMin, etaMax);
        TH1D *eta_den_uds = new TH1D("Eta_Den_uds", ";#eta", etaBin, etaMin, etaMax);
        TH1D *eta_eff_uds = new TH1D("Eta_Eff_uds", ";#eta", etaBin, etaMin, etaMax);

        // g hists for hosting hists from sample
        TH2D *pteta_num_g =  new TH2D("PtEta_Num_g", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
        TH2D *pteta_den_g =  new TH2D("PtEta_Den_g", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
        TH2D *pteta_eff_g =  new TH2D("PtEta_Eff_g", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
        
        TH1D *pt_num_g = new TH1D("Pt_Num_g", ";p_{T} [GeV]", ptBin, ptEdges);
        TH1D *pt_den_g = new TH1D("Pt_Den_g", ";p_{T} [GeV]", ptBin, ptEdges);
        TH1D *pt_eff_g = new TH1D("Pt_Eff_g", ";p_{T} [GeV]", ptBin, ptEdges);

        TH1D *eta_num_g = new TH1D("Eta_Num_g", ";#eta", etaBin, etaMin, etaMax);
        TH1D *eta_den_g = new TH1D("Eta_Den_g", ";#eta", etaBin, etaMin, etaMax);
        TH1D *eta_eff_g = new TH1D("Eta_Eff_g", ";#eta", etaBin, etaMin, etaMax);

        // Loop over source files for the current sample
        for (auto const &fName: sample.fileNames) {
                
            // There are two version of each file: in muon and in electron channel
          for (auto const &channel: {"muon", "electron"}) {
                    
                // Open the source ROOT file
                TFile srcFile((filePrefix + channel + "/" + fName).c_str());

                // Get the right histograms and add them up
                TH2D *PtEta_Num_b = dynamic_cast<TH2D *>(srcFile.Get("PtEta_Num_b")); TH2D *PtEta_Den_b = dynamic_cast<TH2D *>(srcFile.Get("PtEta_Den_b"));
                TH1D *Pt_Num_b = dynamic_cast<TH1D *>(srcFile.Get("Pt_Num_b")); TH1D *Pt_Den_b = dynamic_cast<TH1D *>(srcFile.Get("Pt_Den_b"));
                TH1D *Eta_Num_b = dynamic_cast<TH1D *>(srcFile.Get("Eta_Num_b")); TH1D *Eta_Den_b = dynamic_cast<TH1D *>(srcFile.Get("Eta_Den_b"));

                pteta_num_b->Add(PtEta_Num_b);
                pt_num_b->Add(Pt_Num_b);
                eta_num_b->Add(Eta_Num_b);

                pteta_den_b->Add(PtEta_Den_b);
                pt_den_b->Add(Pt_Den_b);
                eta_den_b->Add(Eta_Den_b);

                TH2D *PtEta_Num_c = dynamic_cast<TH2D *>(srcFile.Get("PtEta_Num_c")); TH2D *PtEta_Den_c = dynamic_cast<TH2D *>(srcFile.Get("PtEta_Den_c"));
                TH1D *Pt_Num_c = dynamic_cast<TH1D *>(srcFile.Get("Pt_Num_c")); TH1D *Pt_Den_c = dynamic_cast<TH1D *>(srcFile.Get("Pt_Den_c"));
                TH1D *Eta_Num_c = dynamic_cast<TH1D *>(srcFile.Get("Eta_Num_c")); TH1D *Eta_Den_c = dynamic_cast<TH1D *>(srcFile.Get("Eta_Den_c"));

                pteta_num_c->Add(PtEta_Num_c);
                pt_num_c->Add(Pt_Num_c);
                eta_num_c->Add(Eta_Num_c);

                pteta_den_c->Add(PtEta_Den_c);
                pt_den_c->Add(Pt_Den_c);
                eta_den_c->Add(Eta_Den_c);

                TH2D *PtEta_Num_uds = dynamic_cast<TH2D *>(srcFile.Get("PtEta_Num_uds")); TH2D *PtEta_Den_uds = dynamic_cast<TH2D *>(srcFile.Get("PtEta_Den_uds"));
                TH1D *Pt_Num_uds = dynamic_cast<TH1D *>(srcFile.Get("Pt_Num_uds")); TH1D *Pt_Den_uds = dynamic_cast<TH1D *>(srcFile.Get("Pt_Den_uds"));
                TH1D *Eta_Num_uds = dynamic_cast<TH1D *>(srcFile.Get("Eta_Num_uds")); TH1D *Eta_Den_uds = dynamic_cast<TH1D *>(srcFile.Get("Eta_Den_uds"));

                pteta_num_uds->Add(PtEta_Num_uds);
                pt_num_uds->Add(Pt_Num_uds);
                eta_num_uds->Add(Eta_Num_uds);

                pteta_den_uds->Add(PtEta_Den_uds);
                pt_den_uds->Add(Pt_Den_uds);
                eta_den_uds->Add(Eta_Den_uds);

                TH2D *PtEta_Num_g = dynamic_cast<TH2D *>(srcFile.Get("PtEta_Num_g")); TH2D *PtEta_Den_g = dynamic_cast<TH2D *>(srcFile.Get("PtEta_Den_g"));
                TH1D *Pt_Num_g = dynamic_cast<TH1D *>(srcFile.Get("Pt_Num_g")); TH1D *Pt_Den_g = dynamic_cast<TH1D *>(srcFile.Get("Pt_Den_g"));
                TH1D *Eta_Num_g = dynamic_cast<TH1D *>(srcFile.Get("Eta_Num_g")); TH1D *Eta_Den_g = dynamic_cast<TH1D *>(srcFile.Get("Eta_Den_g"));

                pteta_num_g->Add(PtEta_Num_g);
                pt_num_g->Add(Pt_Num_g);
                eta_num_g->Add(Eta_Num_g);

                pteta_den_g->Add(PtEta_Den_g);
                pt_den_g->Add(Pt_Den_g);
                eta_den_g->Add(Eta_Den_g);

            }
        }

        // Obtain the efficiencies
        pt_eff_b->Divide(pt_num_b, pt_den_b, 1., 1., "B");
        eta_eff_b->Divide(eta_num_b, eta_den_b, 1., 1., "B");
        pteta_eff_b->Divide(pteta_num_b, pteta_den_b, 1., 1., "B");

        pt_eff_c->Divide(pt_num_c, pt_den_c, 1., 1., "B");
        eta_eff_c->Divide(eta_num_c, eta_den_c, 1., 1., "B");
        pteta_eff_c->Divide(pteta_num_c, pteta_den_c, 1., 1., "B");

        pt_eff_uds->Divide(pt_num_uds, pt_den_uds, 1., 1., "B");
        eta_eff_uds->Divide(eta_num_uds, eta_den_uds, 1., 1., "B");
        pteta_eff_uds->Divide(pteta_num_uds, pteta_den_uds, 1., 1., "B");

        pt_eff_g->Divide(pt_num_g, pt_den_g, 1., 1., "B");
        eta_eff_g->Divide(eta_num_g, eta_den_g, 1., 1., "B");
        pteta_eff_g->Divide(pteta_num_g, pteta_den_g, 1., 1., "B");

        // Write the efficiency histograms into file
        outFile.cd();
            
        pt_eff_b->Write("", TObject::kOverwrite);
        eta_eff_b->Write("", TObject::kOverwrite);
        pteta_eff_b->Write("", TObject::kOverwrite);

        pt_eff_c->Write("", TObject::kOverwrite);
        eta_eff_c->Write("", TObject::kOverwrite);
        pteta_eff_c->Write("", TObject::kOverwrite);

        pt_eff_uds->Write("", TObject::kOverwrite);
        eta_eff_uds->Write("", TObject::kOverwrite);
        pteta_eff_uds->Write("", TObject::kOverwrite);

        pt_eff_g->Write("", TObject::kOverwrite);
        eta_eff_g->Write("", TObject::kOverwrite);
        pteta_eff_g->Write("", TObject::kOverwrite);

    }

    return 0;

}
