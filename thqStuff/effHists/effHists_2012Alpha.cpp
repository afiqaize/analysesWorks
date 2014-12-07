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

    for (int i = 4; i < MAX_LEN; i++) {

      for (int j = 0; j <= i; j++) sel.AddJetTagBin(i, j);
   
    }
    
    // Define datasets (consult [1] for a complete list)
    //[1] https://twiki.cern.ch/twiki/bin/view/CMS/PlainEventContentTuples
    string const filePrefix("/afs/cern.ch/user/a/aapopov/workspace/data/2012Alpha/");
    list<Dataset> datasets;
    
    // t-channel single top plus higgs
    datasets.emplace_back(Dataset::Process::thqExotic, Dataset::Generator::MadGraph,
     Dataset::ShowerGenerator::Pythia);
    datasets.back().AddFile(filePrefix + "tqh-nc-mg-v2_rev468_Goi.root", 34.1e-3, 499958);
    
    // Top-quark pair production plus higgs
    datasets.emplace_back(Dataset::Process::tth, Dataset::Generator::Pythia,
     Dataset::ShowerGenerator::Pythia);
    datasets.back().AddFile(filePrefix + "tth_rev468_swr.root", 130.2e-3, 995697);
    
    // Top-quark pair production
    datasets.emplace_back(Dataset::Process::ttbar, Dataset::Generator::MadGraph,
     Dataset::ShowerGenerator::Pythia);
    datasets.back().AddFile(filePrefix + "ttbar-semilep-mg_rev468_SQQ.root", 102.5, 25274818);
    datasets.back().AddFile(filePrefix + "ttbar-dilep-mg_rev468_Ple.root", 24.6, 12119013);
    
    // t-channel single top
    datasets.emplace_back(Dataset::Process::ttchan, Dataset::Generator::POWHEG,
     Dataset::ShowerGenerator::Undefined);
    datasets.back().AddFile(filePrefix + "t-tchan-pw_rev468_QJd.root", 18.27, 3915598);
    datasets.back().AddFile(filePrefix + "tbar-tchan-pw_rev468_koy.root", 9.95, 1711403);
    
    // tW-channel single top
    datasets.emplace_back(Dataset::Process::ttWchan, Dataset::Generator::POWHEG,
     Dataset::ShowerGenerator::Undefined);
    datasets.back().AddFile(filePrefix + "t-tWchan-DR-pw_rev468_trK.root", 11.1, 497658);
    datasets.back().AddFile(filePrefix + "tbar-tWchan-DR-pw_rev468_bqK.root", 11.1, 493460);
    
    // Inclusive W+jets dataset
    datasets.emplace_back(Dataset::Process::Wjets, Dataset::Generator::MadGraph,
     Dataset::ShowerGenerator::Pythia);
    datasets.back().AddFile(filePrefix + "Wjets-mg_rev468_tkF.root", 37509., 57509905);
    
    // Exclude events with more than one additional parton
    datasets.back().SetFlag("WjetsKeep0p1p");
    
    // Exclusive W+jets datasets
    datasets.emplace_back(Dataset::Process::Wjets, Dataset::Generator::MadGraph,
     Dataset::ShowerGenerator::Pythia);
    datasets.back().AddFile(filePrefix + "Wjets-2p-mg_rev468.root", 2116., 33894921);
    datasets.back().AddFile(filePrefix + "Wjets-3p-mg_rev468.root", 637., 15289503);
    datasets.back().AddFile(filePrefix + "Wjets-4p-mg_rev468.root", 262., 13382803);

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
    
    manager.RegisterPlugin(new BTagEff(outDirectory, bTagger));
    
    // Process the datasets
    manager.Process(10);

    return 0;

}
