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
    samples.emplace_back(Sample("tHq-nc", {"thq-nc-mg_53X.02.01_Wyg.root"}));
    samples.emplace_back(Sample("tHq-sm", {"thq-sm-mg_53X.02.01_rFg.root"}));
    samples.emplace_back(Sample("ttH", {"tth_53X.02.01_bVJ.root"}));
    samples.emplace_back(Sample("t-tchan", {"t-tchan-pw_53X.02.01_PIN.root", "tbar-tchan-pw_53X.02.01_VcT.root"}));
    samples.emplace_back(Sample("t-schan", {"t-schan-pw_53X.02.01_wYe.root", "tbar-schan-pw_53X.02.01_Vth.root"}));
    samples.emplace_back(Sample("t-tWchan", {"t-tWchan-pw_53X.02.01_LxG.root", "tbar-tWchan-pw_53X.02.01_tge.root"}));
    samples.emplace_back(Sample("ttbar-dilep", {"ttbar-dilep-mg_53X.02.01_FFe_p1.root", "ttbar-dilep-mg_53X.02.01_FFe_p2.root"}));
    samples.emplace_back(Sample("ttbar-semilep", {
       "ttbar-semilep-mg-p1_53X.02.01_VNz_p1.root", "ttbar-semilep-mg-p1_53X.02.01_VNz_p2.root", "ttbar-semilep-mg-p1_53X.02.01_VNz_p3.root", "ttbar-semilep-mg-p1_53X.02.01_VNz_p4.root",
       "ttbar-semilep-mg-p2_53X.02.01_Ptw_p1.root", "ttbar-semilep-mg-p2_53X.02.01_Ptw_p2.root", "ttbar-semilep-mg-p2_53X.02.01_Ptw_p3.root", "ttbar-semilep-mg-p2_53X.02.01_Ptw_p4.root", "ttbar-semilep-mg-p2_53X.02.01_Ptw_p5.root",
       "ttbar-semilep-mg-p3_53X.02.01_MXn_p1.root", "ttbar-semilep-mg-p3_53X.02.01_MXn_p2.root", "ttbar-semilep-mg-p3_53X.02.01_MXn_p3.root", "ttbar-semilep-mg-p3_53X.02.01_MXn_p4.root", "ttbar-semilep-mg-p3_53X.02.01_MXn_p5.root"
       }));
    samples.emplace_back(Sample("ttbar-inc", {
       "ttbar-mgms_53X.02.01_zEC_p1.root", "ttbar-mgms_53X.02.01_zEC_p2.root", "ttbar-mgms_53X.02.01_zEC_p3.root", "ttbar-mgms_53X.02.01_zEC_p4.root",
       "ttbar-mgms_53X.02.01_zEC_p5.root", "ttbar-mgms_53X.02.01_zEC_p6.root", "ttbar-mgms_53X.02.01_zEC_p7.root"}));
    samples.emplace_back(Sample("Wjets", {"Wjets-mg_53X.02.01_jOE.root", "Wjets-2p-mg_53X.02.01_Dhm.root", "Wjets-3p-mg_53X.02.01_YDn.root", "Wjets-4p-mg_53X.02.01_FxU.root"}));
    
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
        Int_t etaBin = 8; Float_t etaMin = -2.4, etaMax = 2.4;

        // Test binning
        //Float_t ptEdges[13] = {20., 40., 60., 80., 100., 130., 160., 190., 220., 250., 300., 350., 400.};
        //Float_t etaEdges[13] = {0., 0.2, 0.4, 0.6, 0.8, 1., 1.2, 1.4, 1.6, 1.8, 2., 2.2, 2.4};

        // BTV POG recommended bins
        //Float_t ptEdges[16] = {20., 30., 40., 50., 60., 70., 80., 100., 120., 160., 210., 260., 320., 400., 500., 670.};
        //Float_t etaEdges[5] = {0., .6, 1.2, 1.8, 2.4};

        // Dan-extended BTV bins
        Float_t ptEdges[17] = {20., 30., 40., 50., 60., 70., 80., 100., 120., 160., 210., 260., 320., 400., 500., 600., 800.};
        Float_t etaEdges[9] = {-2.4, -1.8, -1.2, -.6, 0., .6, 1.2, 1.8, 2.4};

        // b hists for hosting hists from sample
        TH2D *pteta_num_b_T =  new TH2D("PtEta_Num_b_T", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
        TH2D *pteta_den_b_T =  new TH2D("PtEta_Den_b_T", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
        TH2D *pteta_eff_b_T =  new TH2D("PtEta_Eff_b_T", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
        
        TH1D *pt_num_b_T = new TH1D("Pt_Num_b_T", ";p_{T} [GeV]", ptBin, ptEdges);
        TH1D *pt_den_b_T = new TH1D("Pt_Den_b_T", ";p_{T} [GeV]", ptBin, ptEdges);
        TH1D *pt_eff_b_T = new TH1D("Pt_Eff_b_T", ";p_{T} [GeV]", ptBin, ptEdges);

        TH1D *eta_num_b_T = new TH1D("Eta_Num_b_T", ";#eta", etaBin, etaMin, etaMax);
        TH1D *eta_den_b_T = new TH1D("Eta_Den_b_T", ";#eta", etaBin, etaMin, etaMax);
        TH1D *eta_eff_b_T = new TH1D("Eta_Eff_b_T", ";#eta", etaBin, etaMin, etaMax);

        // c hists for hosting hists from sample
        TH2D *pteta_num_c_T =  new TH2D("PtEta_Num_c_T", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
        TH2D *pteta_den_c_T =  new TH2D("PtEta_Den_c_T", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
        TH2D *pteta_eff_c_T =  new TH2D("PtEta_Eff_c_T", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
        
        TH1D *pt_num_c_T = new TH1D("Pt_Num_c_T", ";p_{T} [GeV]", ptBin, ptEdges);
        TH1D *pt_den_c_T = new TH1D("Pt_Den_c_T", ";p_{T} [GeV]", ptBin, ptEdges);
        TH1D *pt_eff_c_T = new TH1D("Pt_Eff_c_T", ";p_{T} [GeV]", ptBin, ptEdges);

        TH1D *eta_num_c_T = new TH1D("Eta_Num_c_T", ";#eta", etaBin, etaMin, etaMax);
        TH1D *eta_den_c_T = new TH1D("Eta_Den_c_T", ";#eta", etaBin, etaMin, etaMax);
        TH1D *eta_eff_c_T = new TH1D("Eta_Eff_c_T", ";#eta", etaBin, etaMin, etaMax);

        // uds hists for hosting hists from sample
        TH2D *pteta_num_uds_T =  new TH2D("PtEta_Num_uds_T", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
        TH2D *pteta_den_uds_T =  new TH2D("PtEta_Den_uds_T", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
        TH2D *pteta_eff_uds_T =  new TH2D("PtEta_Eff_uds_T", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
        
        TH1D *pt_num_uds_T = new TH1D("Pt_Num_uds_T", ";p_{T} [GeV]", ptBin, ptEdges);
        TH1D *pt_den_uds_T = new TH1D("Pt_Den_uds_T", ";p_{T} [GeV]", ptBin, ptEdges);
        TH1D *pt_eff_uds_T = new TH1D("Pt_Eff_uds_T", ";p_{T} [GeV]", ptBin, ptEdges);

        TH1D *eta_num_uds_T = new TH1D("Eta_Num_uds_T", ";#eta", etaBin, etaMin, etaMax);
        TH1D *eta_den_uds_T = new TH1D("Eta_Den_uds_T", ";#eta", etaBin, etaMin, etaMax);
        TH1D *eta_eff_uds_T = new TH1D("Eta_Eff_uds_T", ";#eta", etaBin, etaMin, etaMax);

        // g hists for hosting hists from sample
        TH2D *pteta_num_g_T =  new TH2D("PtEta_Num_g_T", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
        TH2D *pteta_den_g_T =  new TH2D("PtEta_Den_g_T", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
        TH2D *pteta_eff_g_T =  new TH2D("PtEta_Eff_g_T", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
        
        TH1D *pt_num_g_T = new TH1D("Pt_Num_g_T", ";p_{T} [GeV]", ptBin, ptEdges);
        TH1D *pt_den_g_T = new TH1D("Pt_Den_g_T", ";p_{T} [GeV]", ptBin, ptEdges);
        TH1D *pt_eff_g_T = new TH1D("Pt_Eff_g_T", ";p_{T} [GeV]", ptBin, ptEdges);

        TH1D *eta_num_g_T = new TH1D("Eta_Num_g_T", ";#eta", etaBin, etaMin, etaMax);
        TH1D *eta_den_g_T = new TH1D("Eta_Den_g_T", ";#eta", etaBin, etaMin, etaMax);
        TH1D *eta_eff_g_T = new TH1D("Eta_Eff_g_T", ";#eta", etaBin, etaMin, etaMax);

        // Loop over source files for the current sample
        for (auto const &fName: sample.fileNames) {
                
            // There are two version of each file: in muon and in electron channel
          for (auto const &channel: {"muon", "electron"}) {
                    
                // Open the source ROOT file
                TFile srcFile((filePrefix + channel + "/" + fName).c_str());

                // Get the right histograms and add them up
                TH2D *PtEta_Num_b_T = dynamic_cast<TH2D *>(srcFile.Get("PtEta_Num_b_T")); TH2D *PtEta_Den_b_T = dynamic_cast<TH2D *>(srcFile.Get("PtEta_Den_b_T"));
                TH1D *Pt_Num_b_T = dynamic_cast<TH1D *>(srcFile.Get("Pt_Num_b_T")); TH1D *Pt_Den_b_T = dynamic_cast<TH1D *>(srcFile.Get("Pt_Den_b_T"));
                TH1D *Eta_Num_b_T = dynamic_cast<TH1D *>(srcFile.Get("Eta_Num_b_T")); TH1D *Eta_Den_b_T = dynamic_cast<TH1D *>(srcFile.Get("Eta_Den_b_T"));

                pteta_num_b_T->Add(PtEta_Num_b_T);
                pt_num_b_T->Add(Pt_Num_b_T);
                eta_num_b_T->Add(Eta_Num_b_T);

                pteta_den_b_T->Add(PtEta_Den_b_T);
                pt_den_b_T->Add(Pt_Den_b_T);
                eta_den_b_T->Add(Eta_Den_b_T);

                TH2D *PtEta_Num_c_T = dynamic_cast<TH2D *>(srcFile.Get("PtEta_Num_c_T")); TH2D *PtEta_Den_c_T = dynamic_cast<TH2D *>(srcFile.Get("PtEta_Den_c_T"));
                TH1D *Pt_Num_c_T = dynamic_cast<TH1D *>(srcFile.Get("Pt_Num_c_T")); TH1D *Pt_Den_c_T = dynamic_cast<TH1D *>(srcFile.Get("Pt_Den_c_T"));
                TH1D *Eta_Num_c_T = dynamic_cast<TH1D *>(srcFile.Get("Eta_Num_c_T")); TH1D *Eta_Den_c_T = dynamic_cast<TH1D *>(srcFile.Get("Eta_Den_c_T"));

                pteta_num_c_T->Add(PtEta_Num_c_T);
                pt_num_c_T->Add(Pt_Num_c_T);
                eta_num_c_T->Add(Eta_Num_c_T);

                pteta_den_c_T->Add(PtEta_Den_c_T);
                pt_den_c_T->Add(Pt_Den_c_T);
                eta_den_c_T->Add(Eta_Den_c_T);

                TH2D *PtEta_Num_uds_T = dynamic_cast<TH2D *>(srcFile.Get("PtEta_Num_uds_T")); TH2D *PtEta_Den_uds_T = dynamic_cast<TH2D *>(srcFile.Get("PtEta_Den_uds_T"));
                TH1D *Pt_Num_uds_T = dynamic_cast<TH1D *>(srcFile.Get("Pt_Num_uds_T")); TH1D *Pt_Den_uds_T = dynamic_cast<TH1D *>(srcFile.Get("Pt_Den_uds_T"));
                TH1D *Eta_Num_uds_T = dynamic_cast<TH1D *>(srcFile.Get("Eta_Num_uds_T")); TH1D *Eta_Den_uds_T = dynamic_cast<TH1D *>(srcFile.Get("Eta_Den_uds_T"));

                pteta_num_uds_T->Add(PtEta_Num_uds_T);
                pt_num_uds_T->Add(Pt_Num_uds_T);
                eta_num_uds_T->Add(Eta_Num_uds_T);

                pteta_den_uds_T->Add(PtEta_Den_uds_T);
                pt_den_uds_T->Add(Pt_Den_uds_T);
                eta_den_uds_T->Add(Eta_Den_uds_T);

                TH2D *PtEta_Num_g_T = dynamic_cast<TH2D *>(srcFile.Get("PtEta_Num_g_T")); TH2D *PtEta_Den_g_T = dynamic_cast<TH2D *>(srcFile.Get("PtEta_Den_g_T"));
                TH1D *Pt_Num_g_T = dynamic_cast<TH1D *>(srcFile.Get("Pt_Num_g_T")); TH1D *Pt_Den_g_T = dynamic_cast<TH1D *>(srcFile.Get("Pt_Den_g_T"));
                TH1D *Eta_Num_g_T = dynamic_cast<TH1D *>(srcFile.Get("Eta_Num_g_T")); TH1D *Eta_Den_g_T = dynamic_cast<TH1D *>(srcFile.Get("Eta_Den_g_T"));

                pteta_num_g_T->Add(PtEta_Num_g_T);
                pt_num_g_T->Add(Pt_Num_g_T);
                eta_num_g_T->Add(Eta_Num_g_T);

                pteta_den_g_T->Add(PtEta_Den_g_T);
                pt_den_g_T->Add(Pt_Den_g_T);
                eta_den_g_T->Add(Eta_Den_g_T);

            }
        }

        // Obtain the efficiencies
        pt_eff_b_T->Divide(pt_num_b_T, pt_den_b_T, 1., 1., "B");
        eta_eff_b_T->Divide(eta_num_b_T, eta_den_b_T, 1., 1., "B");
        pteta_eff_b_T->Divide(pteta_num_b_T, pteta_den_b_T, 1., 1., "B");

        pt_eff_c_T->Divide(pt_num_c_T, pt_den_c_T, 1., 1., "B");
        eta_eff_c_T->Divide(eta_num_c_T, eta_den_c_T, 1., 1., "B");
        pteta_eff_c_T->Divide(pteta_num_c_T, pteta_den_c_T, 1., 1., "B");

        pt_eff_uds_T->Divide(pt_num_uds_T, pt_den_uds_T, 1., 1., "B");
        eta_eff_uds_T->Divide(eta_num_uds_T, eta_den_uds_T, 1., 1., "B");
        pteta_eff_uds_T->Divide(pteta_num_uds_T, pteta_den_uds_T, 1., 1., "B");

        pt_eff_g_T->Divide(pt_num_g_T, pt_den_g_T, 1., 1., "B");
        eta_eff_g_T->Divide(eta_num_g_T, eta_den_g_T, 1., 1., "B");
        pteta_eff_g_T->Divide(pteta_num_g_T, pteta_den_g_T, 1., 1., "B");

        // Write the efficiency histograms into file
        outFile.cd();
            
        pt_eff_b_T->Write("", TObject::kOverwrite);
        eta_eff_b_T->Write("", TObject::kOverwrite);
        pteta_eff_b_T->Write("", TObject::kOverwrite);

        pt_eff_c_T->Write("", TObject::kOverwrite);
        eta_eff_c_T->Write("", TObject::kOverwrite);
        pteta_eff_c_T->Write("", TObject::kOverwrite);

        pt_eff_uds_T->Write("", TObject::kOverwrite);
        eta_eff_uds_T->Write("", TObject::kOverwrite);
        pteta_eff_uds_T->Write("", TObject::kOverwrite);

        pt_eff_g_T->Write("", TObject::kOverwrite);
        eta_eff_g_T->Write("", TObject::kOverwrite);
        pteta_eff_g_T->Write("", TObject::kOverwrite);

    }

    return 0;

}
