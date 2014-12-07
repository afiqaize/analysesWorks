/***
effHists.cpp
- Defines the event selection and saves the jet information with BTagEff plugin
***/

#include <GenericEventSelection.hpp>
#include <Dataset.hpp>
#include <PECReader.hpp>
#include <BTagger.hpp>
#include <BTagDatabase.hpp>
#include <TriggerSelection.hpp>
#include <WeightPileUp.hpp>
#include <RunManager.hpp>
#include <JetPtFilterPlugin.hpp>
#include <BTagEff.hpp>
#include <iostream>

using namespace std;

// Registration channel
enum class RegChannel
{
    Electron,
    Muon
};

int main(int argc, char const **argv)
{
    
    string const regChannelArg(argv[1]);
    RegChannel regChannel;
    
    if (regChannelArg.find("mu") not_eq string::npos)
        regChannel = RegChannel::Muon;
    else if (regChannelArg.find("e") not_eq string::npos)
        regChannel = RegChannel::Electron;
    else
    {
        cout << "Cannot recognise lepton channel \"" << regChannelArg << "\"\n";
        return 1;
    }
        
    // Define the b-tagging objects
    BTagger bTagger(BTagger::Algorithm::CSV, BTagger::WorkingPoint::Tight);
    BTagDatabase bTagDatabase(bTagger);
    
    // Define the event selection
    GenericEventSelection sel(20., bTagger);
    
    if (regChannel == RegChannel::Muon)
        sel.AddLeptonThreshold(Lepton::Flavour::Muon, 26.);
    else
        sel.AddLeptonThreshold(Lepton::Flavour::Electron, 30.);

    for (int i = 5; i <= 5; i++) {

      for (int j = 0; j <= i; j++) sel.AddJetTagBin(i, j);
   
    }
    
    // Define datasets (consult [1] for a complete list)
    //[1] https://twiki.cern.ch/twiki/bin/view/CMS/PlainEventContentTuples
    list<Dataset> datasets;
    string const filePrefix("/afs/cern.ch/user/a/aapopov/workspace/data/2012Bravo/");
    
    // Exotic t-channel single top plus higgs
    datasets.emplace_back(Dataset::Process::thqExotic, Dataset::Generator::MadGraph,
     Dataset::ShowerGenerator::Pythia);
    datasets.back().AddFile(filePrefix + "thq-nc-mg_53X.02.01_Wyg.root", 36.4e-3, 4847334);

    // SM t-channel single top plus higgs
    datasets.emplace_back(Dataset::Process::thqSM, Dataset::Generator::MadGraph,
     Dataset::ShowerGenerator::Pythia);
    datasets.back().AddFile(filePrefix + "thq-sm-mg_53X.02.01_rFg.root", 2.85e-3, 4795361);
    
    // Semileptonic and dileptonic ttbar
    datasets.emplace_back(Dataset::Process::ttbar, Dataset::Generator::MadGraph,
     Dataset::ShowerGenerator::Pythia);
    datasets.back().AddFile(filePrefix + "ttbar-semilep-mg-p1_53X.02.01_VNz_p1.root", 107.7, 86814792);
    datasets.back().AddFile(filePrefix + "ttbar-semilep-mg-p1_53X.02.01_VNz_p2.root", 107.7, 86814792);
    datasets.back().AddFile(filePrefix + "ttbar-semilep-mg-p1_53X.02.01_VNz_p3.root", 107.7, 86814792);
    datasets.back().AddFile(filePrefix + "ttbar-semilep-mg-p1_53X.02.01_VNz_p4.root", 107.7, 86814792);
    datasets.back().AddFile(filePrefix + "ttbar-semilep-mg-p2_53X.02.01_Ptw_p1.root", 107.7, 86814792);
    datasets.back().AddFile(filePrefix + "ttbar-semilep-mg-p2_53X.02.01_Ptw_p2.root", 107.7, 86814792);
    datasets.back().AddFile(filePrefix + "ttbar-semilep-mg-p2_53X.02.01_Ptw_p3.root", 107.7, 86814792);
    datasets.back().AddFile(filePrefix + "ttbar-semilep-mg-p2_53X.02.01_Ptw_p4.root", 107.7, 86814792);
    datasets.back().AddFile(filePrefix + "ttbar-semilep-mg-p2_53X.02.01_Ptw_p5.root", 107.7, 86814792);
    datasets.back().AddFile(filePrefix + "ttbar-semilep-mg-p3_53X.02.01_MXn_p1.root", 107.7, 86814792);
    datasets.back().AddFile(filePrefix + "ttbar-semilep-mg-p3_53X.02.01_MXn_p2.root", 107.7, 86814792);
    datasets.back().AddFile(filePrefix + "ttbar-semilep-mg-p3_53X.02.01_MXn_p3.root", 107.7, 86814792);
    datasets.back().AddFile(filePrefix + "ttbar-semilep-mg-p3_53X.02.01_MXn_p4.root", 107.7, 86814792);
    datasets.back().AddFile(filePrefix + "ttbar-semilep-mg-p3_53X.02.01_MXn_p5.root", 107.7, 86814792);
    datasets.back().AddFile(filePrefix + "ttbar-dilep-mg_53X.02.01_FFe_p1.root", 25.8, 11991428);
    datasets.back().AddFile(filePrefix + "ttbar-dilep-mg_53X.02.01_FFe_p2.root", 25.8, 11991428);
    datasets.back().AddFile(filePrefix + "ttbar-mgms_53X.02.01_zEC_p1.root", 245.8, 62119286);
    datasets.back().AddFile(filePrefix + "ttbar-mgms_53X.02.01_zEC_p2.root", 245.8, 62119286);
    datasets.back().AddFile(filePrefix + "ttbar-mgms_53X.02.01_zEC_p3.root", 245.8, 62119286);
    datasets.back().AddFile(filePrefix + "ttbar-mgms_53X.02.01_zEC_p4.root", 245.8, 62119286);
    datasets.back().AddFile(filePrefix + "ttbar-mgms_53X.02.01_zEC_p5.root", 245.8, 62119286);
    datasets.back().AddFile(filePrefix + "ttbar-mgms_53X.02.01_zEC_p6.root", 245.8, 62119286);
    datasets.back().AddFile(filePrefix + "ttbar-mgms_53X.02.01_zEC_p7.root", 245.8, 62119286);

    // Top-quark pair production plus higgs
    datasets.emplace_back(Dataset::Process::tth, Dataset::Generator::Pythia,
     Dataset::ShowerGenerator::Pythia);
    datasets.back().AddFile(filePrefix + "tth_53X.02.01_bVJ.root", 130.2e-3, 995697);

    // t-channel single top
    datasets.emplace_back(Dataset::Process::ttchan, Dataset::Generator::POWHEG,
     Dataset::ShowerGenerator::Undefined);
    datasets.back().AddFile(filePrefix + "t-tchan-pw_53X.02.01_PIN.root", 18.27, 3915598);
    datasets.back().AddFile(filePrefix + "tbar-tchan-pw_53X.02.01_VcT.root", 9.95, 1711403);

    // tW-channel single top
    datasets.emplace_back(Dataset::Process::ttWchan, Dataset::Generator::POWHEG,
     Dataset::ShowerGenerator::Undefined);
    datasets.back().AddFile(filePrefix + "t-tWchan-pw_53X.02.01_LxG.root", 11.1, 497658);
    datasets.back().AddFile(filePrefix + "tbar-tWchan-pw_53X.02.01_tge.root", 11.1, 493460);

    // s-channel single top
    datasets.emplace_back(Dataset::Process::ttchan, Dataset::Generator::POWHEG,
     Dataset::ShowerGenerator::Undefined);
    datasets.back().AddFile(filePrefix + "t-schan-pw_53X.02.01_wYe.root", 1.23, 3932710);
    datasets.back().AddFile(filePrefix + "tbar-schan-pw_53X.02.01_Vth.root ", 0.57, 1999667);

    // Inclusive W+jets dataset
    datasets.emplace_back(Dataset::Process::Wjets, Dataset::Generator::MadGraph,
     Dataset::ShowerGenerator::Pythia);
    datasets.back().AddFile(filePrefix + "Wjets-mg_53X.02.01_jOE.root", 37509., 57709905);
    
    // Exclude events with more than one additional parton
    datasets.back().SetFlag("WjetsKeep0p1p");

    // Exclusive W+jets datasets
    datasets.emplace_back(Dataset::Process::Wjets, Dataset::Generator::MadGraph,
     Dataset::ShowerGenerator::Pythia);
    datasets.back().AddFile(filePrefix + "Wjets-2p-mg_53X.02.01_Dhm.root", 2116., 34044921);
    datasets.back().AddFile(filePrefix + "Wjets-3p-mg_53X.02.01_YDn.root", 637., 15539503);
    datasets.back().AddFile(filePrefix + "Wjets-4p-mg_53X.02.01_FxU.root", 262., 13382803);

    // Define triggers
    list<TriggerRange> triggerRanges;

    if (regChannel == RegChannel::Muon)
        triggerRanges.emplace_back(0, -1, "HLT_IsoMu24_eta2p1_v", 18.897e3, "HLT_IsoMu24_eta2p1_v");

    else
        triggerRanges.emplace_back(0, -1, "HLT_Ele27_WP80_v", 18.932e3, "HLT_Ele27_WP80_v");
    
    TriggerSelection triggerSel(triggerRanges);
      
    // An object to reweight for pile-up
    WeightPileUp weightPileUp("SingleMu2012ABCD_Alpha-v2_pixelLumi.pileupTruth_finebin.root", 0.06);
        
    // Construct the run manager
    RunManager manager(datasets.begin(), datasets.end());
    
    // Set the configuration for PECReader
    auto &config = manager.GetPECReaderConfig();
    config.SetModule(&triggerSel);
    config.SetModule(&sel);
    config.SetModule(&bTagger);
    config.SetModule(&bTagDatabase);
    config.SetModule(&weightPileUp);
    
    // Register a plugin
    string outDirectory("../tuples/");
    
    if (regChannel == RegChannel::Muon)
        outDirectory += "muon/";
    else
        outDirectory += "electron/";
    
    // Register the plugins
    manager.RegisterPlugin(new JetPtFilterPlugin(5, 30.));
    manager.RegisterPlugin(new BTagEff(outDirectory, bTagger));
    
    // Process the datasets
    manager.Process(10);

    return 0;

}
