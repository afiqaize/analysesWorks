/***
BTagEff.cpp
Summary Refer to its hpp file
***/

#include <BTagEff.hpp>

#include <Processor.hpp>
#include <ROOTLock.hpp>

#include <sys/stat.h>
#include <iostream>

using namespace std;

BTagEff::BTagEff(string const &outDirectory_, BTagger const &bTagger_):
    Plugin("BTagEff"),
    bTagger(bTagger_), outDirectory(outDirectory_)
{

    // Make sure the directory path ends with a slash
    if (outDirectory.back() != '/')
        outDirectory += '/';
    
    // Create the output directory if it does not exist
    struct stat dirStat;
    
    if (stat(outDirectory.c_str(), &dirStat) != 0) // the directory does not exist
        mkdir(outDirectory.c_str(), 0755);

}

Plugin *BTagEff::Clone() const
{
    return new BTagEff(outDirectory, bTagger);
}

void BTagEff::BeginRun(Dataset const &dataset)
{

    // Save pointers to other required plugins
    reader = dynamic_cast<PECReaderPlugin const *>(processor->GetPluginBefore("Reader", name));    
    
    // Creation of ROOT objects is not thread-safe and must be protected
    ROOTLock::Lock();
    
    // Create the output file
    file = new TFile((outDirectory + dataset.GetFiles().front().GetBaseName() + ".root").c_str(),
     "recreate");

    // Create the histograms

    TH1::SetDefaultSumw2(true);

    // Decide the parameters to be used
    ptBin = 16; ptMin = 0.; ptMax = 400.;
    etaBin = 8; etaMin = -2.4; etaMax = 2.4;

    // Test binning
    //Float_t ptEdges[13] = {20., 40., 60., 80., 100., 130., 160., 190., 220., 250., 300., 350., 400.};
    //Float_t etaEdges[13] = {0., 0.2, 0.4, 0.6, 0.8, 1., 1.2, 1.4, 1.6, 1.8, 2., 2.2, 2.4};

    // BTV POG recommended bins
    //Float_t ptEdges[16] = {20., 30., 40., 50., 60., 70., 80., 100., 120., 160., 210., 260., 320., 400., 500., 670.};
    //Float_t etaEdges[5] = {0., .6, 1.2, 1.8, 2.4};

    // Dan-extended BTV bins
    Float_t ptEdges[17] = {20., 30., 40., 50., 60., 70., 80., 100., 120., 160., 210., 260., 320., 400., 500., 600., 800.};
    Float_t etaEdges[9] = {-2.4, -1.8, -1.2, -.6, 0., .6, 1.2, 1.8, 2.4};
   
    // b hists
    PtEta_Num_b_T = new TH2D("PtEta_Num_b_T", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
    PtEta_Den_b_T = new TH2D("PtEta_Den_b_T", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
        
    Pt_Num_b_T = new TH1D("Pt_Num_b_T", ";p_{T} [GeV]", ptBin, ptEdges);
    Pt_Den_b_T = new TH1D("Pt_Den_b_T", ";p_{T} [GeV]", ptBin, ptEdges);

    Eta_Num_b_T = new TH1D("Eta_Num_b_T", ";#eta", etaBin, etaMin, etaMax);
    Eta_Den_b_T = new TH1D("Eta_Den_b_T", ";#eta", etaBin, etaMin, etaMax);

    // c hists
    PtEta_Num_c_T = new TH2D("PtEta_Num_c_T", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
    PtEta_Den_c_T = new TH2D("PtEta_Den_c_T", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
        
    Pt_Num_c_T = new TH1D("Pt_Num_c_T", ";p_{T} [GeV]", ptBin, ptEdges);
    Pt_Den_c_T = new TH1D("Pt_Den_c_T", ";p_{T} [GeV]", ptBin, ptEdges);

    Eta_Num_c_T = new TH1D("Eta_Num_c_T", ";#eta", etaBin, etaMin, etaMax);
    Eta_Den_c_T = new TH1D("Eta_Den_c_T", ";#eta", etaBin, etaMin, etaMax);

    // uds hists
    PtEta_Num_uds_T = new TH2D("PtEta_Num_uds_T", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
    PtEta_Den_uds_T = new TH2D("PtEta_Den_uds_T", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
        
    Pt_Num_uds_T = new TH1D("Pt_Num_uds_T", ";p_{T} [GeV]", ptBin, ptEdges);
    Pt_Den_uds_T = new TH1D("Pt_Den_uds_T", ";p_{T} [GeV]", ptBin, ptEdges);

    Eta_Num_uds_T = new TH1D("Eta_Num_uds_T", ";#eta", etaBin, etaMin, etaMax);
    Eta_Den_uds_T = new TH1D("Eta_Den_uds_T", ";#eta", etaBin, etaMin, etaMax);

    // gluon hists
    PtEta_Num_g_T = new TH2D("PtEta_Num_g_T", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
    PtEta_Den_g_T = new TH2D("PtEta_Den_g_T", ";p_{T} [GeV];#eta", ptBin, ptEdges, etaBin, etaEdges);
        
    Pt_Num_g_T = new TH1D("Pt_Num_g_T", ";p_{T} [GeV]", ptBin, ptEdges);
    Pt_Den_g_T = new TH1D("Pt_Den_g_T", ";p_{T} [GeV]", ptBin, ptEdges);

    Eta_Num_g_T = new TH1D("Eta_Num_g_T", ";#eta", etaBin, etaMin, etaMax);
    Eta_Den_g_T = new TH1D("Eta_Den_g_T", ";#eta", etaBin, etaMin, etaMax);
    
    // End of critical block
    ROOTLock::Unlock();
    
}

void BTagEff::EndRun()
{

    // Operations with ROOT objects performed here are not thread-safe and must be guarded
    ROOTLock::Lock();
    
    // Write the histograms in the right folder and close the file
    file->cd();
    
    PtEta_Num_b_T->Write("", TObject::kOverwrite);
    PtEta_Den_b_T->Write("", TObject::kOverwrite);
    Pt_Num_b_T->Write("", TObject::kOverwrite);
    Pt_Den_b_T->Write("", TObject::kOverwrite);
    Eta_Num_b_T->Write("", TObject::kOverwrite);
    Eta_Den_b_T->Write("", TObject::kOverwrite);

    PtEta_Num_c_T->Write("", TObject::kOverwrite);
    PtEta_Den_c_T->Write("", TObject::kOverwrite);
    Pt_Num_c_T->Write("", TObject::kOverwrite);
    Pt_Den_c_T->Write("", TObject::kOverwrite);
    Eta_Num_c_T->Write("", TObject::kOverwrite);
    Eta_Den_c_T->Write("", TObject::kOverwrite);

    PtEta_Num_uds_T->Write("", TObject::kOverwrite);
    PtEta_Den_uds_T->Write("", TObject::kOverwrite);
    Pt_Num_uds_T->Write("", TObject::kOverwrite);
    Pt_Den_uds_T->Write("", TObject::kOverwrite);
    Eta_Num_uds_T->Write("", TObject::kOverwrite);
    Eta_Den_uds_T->Write("", TObject::kOverwrite);

    PtEta_Num_g_T->Write("", TObject::kOverwrite);
    PtEta_Den_g_T->Write("", TObject::kOverwrite);
    Pt_Num_g_T->Write("", TObject::kOverwrite);
    Pt_Den_g_T->Write("", TObject::kOverwrite);
    Eta_Num_g_T->Write("", TObject::kOverwrite);
    Eta_Den_g_T->Write("", TObject::kOverwrite);

    file->Close();

    // Delete the objects
    delete file;
    
    ROOTLock::Unlock();

}

bool BTagEff::ProcessEvent()
{

   // Define some other physics parameters
   MET = (*reader)->GetMET().Pt();

   // Apply basic event cuts
   if (MET < 35.) return false;

   // Put all the reconstructed jets into a single vector
   allJets.clear();
   allJets.insert(allJets.end(), (*reader)->GetJets().begin(), (*reader)->GetJets().end());
   allJets.insert(allJets.end(), (*reader)->GetAdditionalJets().begin(),
     (*reader)->GetAdditionalJets().end());

   // Evaluate the tagging efficiency
   for (auto const &j: allJets) {

      // Base pt and eta cut
      if ((j.Pt() < 20.) || (fabs(j.Eta()) > 2.4)) continue;

      // b numerator/denominator
      if (fabs(j.GetParentID()) == 5) {

      Pt_Den_b_T->Fill(j.Pt());
      Eta_Den_b_T->Fill(fabs(j.Eta()));
      PtEta_Den_b_T->Fill(j.Pt(), fabs(j.Eta()));

      // Also fill the negative side
      Eta_Den_b_T->Fill(-1. * fabs(j.Eta()));
      PtEta_Den_b_T->Fill(j.Pt(), -1. * fabs(j.Eta()));

      if (bTagger(j)) {

        Pt_Num_b_T->Fill(j.Pt());
        Eta_Num_b_T->Fill(fabs(j.Eta()));
        PtEta_Num_b_T->Fill(j.Pt(), fabs(j.Eta()));

        Eta_Num_b_T->Fill(-1. * fabs(j.Eta()));
        PtEta_Num_b_T->Fill(j.Pt(), -1. * fabs(j.Eta()));

        }
      }

      // c numerator/denominator
      else if (fabs(j.GetParentID()) == 4) {

      Pt_Den_c_T->Fill(j.Pt());
      Eta_Den_c_T->Fill(fabs(j.Eta()));
      PtEta_Den_c_T->Fill(j.Pt(), fabs(j.Eta()));

      // Also fill the negative side
      Eta_Den_c_T->Fill(-1. * fabs(j.Eta()));
      PtEta_Den_c_T->Fill(j.Pt(), -1. * fabs(j.Eta()));

      if (bTagger(j)) {

        Pt_Num_c_T->Fill(j.Pt());
        Eta_Num_c_T->Fill(fabs(j.Eta()));
        PtEta_Num_c_T->Fill(j.Pt(), fabs(j.Eta()));

        Eta_Num_c_T->Fill(-1. * fabs(j.Eta()));
        PtEta_Num_c_T->Fill(j.Pt(), -1. * fabs(j.Eta()));

        }
      }

      // uds numerator/denominator
      else if ((fabs(j.GetParentID()) == 3) || (fabs(j.GetParentID()) == 2) || (fabs(j.GetParentID()) == 1))  {

      Pt_Den_uds_T->Fill(j.Pt());
      Eta_Den_uds_T->Fill(fabs(j.Eta()));
      PtEta_Den_uds_T->Fill(j.Pt(), fabs(j.Eta()));

      // Also fill the negative side
      Eta_Den_uds_T->Fill(-1. * fabs(j.Eta()));
      PtEta_Den_uds_T->Fill(j.Pt(), -1. * fabs(j.Eta()));

      if (bTagger(j)) {

        Pt_Num_uds_T->Fill(j.Pt());
        Eta_Num_uds_T->Fill(fabs(j.Eta()));
        PtEta_Num_uds_T->Fill(j.Pt(), fabs(j.Eta()));

        Eta_Num_uds_T->Fill(-1. * fabs(j.Eta()));
        PtEta_Num_uds_T->Fill(j.Pt(), -1. * fabs(j.Eta()));

        }
      }

      // gluon numerator/denominator
      else if ((fabs(j.GetParentID()) == 21) || (fabs(j.GetParentID()) == 0)) {

      Pt_Den_g_T->Fill(j.Pt());
      Eta_Den_g_T->Fill(fabs(j.Eta()));
      PtEta_Den_g_T->Fill(j.Pt(), fabs(j.Eta()));

      // Also fill the negative side
      Eta_Den_g_T->Fill(-1. * fabs(j.Eta()));
      PtEta_Den_g_T->Fill(j.Pt(), -1. * fabs(j.Eta()));

      if (bTagger(j)) {

        Pt_Num_g_T->Fill(j.Pt());
        Eta_Num_g_T->Fill(fabs(j.Eta()));
        PtEta_Num_g_T->Fill(j.Pt(), fabs(j.Eta()));

        Eta_Num_g_T->Fill(-1. * fabs(j.Eta()));
        PtEta_Num_g_T->Fill(j.Pt(), -1. * fabs(j.Eta()));

        }
      }

      else continue;

  }
 
   return true;

}
