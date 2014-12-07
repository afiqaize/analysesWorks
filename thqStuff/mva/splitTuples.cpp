/**
 * The programs splits tuples with input variables into training and testing/examination set.
 */

#include <TFile.h>
#include <TTree.h>

#include <boost/filesystem.hpp>

#include <string>
#include <list>
#include <memory>
#include <initializer_list>


using namespace std;


void DoSplitTuples(initializer_list<string> const &srcFileNames, string const &outFileBaseName) {
   
    // Define the source files
    string const srcDirectory("../InputVars/tuples_fullRap_4t/");
    string const treeName("Vars");
    
    // Names of output files and directory
    string const outDirectory("tuples_fullRap_4t/");
    
    // Create the output files
    boost::filesystem::create_directory(outDirectory);
    
    TFile trainFile((outDirectory + outFileBaseName + "_train.root").c_str(), "recreate");
    TFile examFile((outDirectory + outFileBaseName + "_exam.root").c_str(), "recreate");
    
    unique_ptr<TTree> trainTree, examTree;
    
    
    // Loop over the source files
    for (string const &srcFileName: srcFileNames)
    {
        // Open the source file and get the tree
        TFile srcFile((srcDirectory + srcFileName).c_str());
        unique_ptr<TTree> srcTree(dynamic_cast<TTree *>(srcFile.Get(treeName.c_str())));
        unsigned long const nEntries = srcTree->GetEntries();
        
        // Set buffers to access event ID and signal flag
        ULong64_t run, lumi, event;
        
        srcTree->SetBranchAddress("RunNumber", &run);
        srcTree->SetBranchAddress("LumiSection", &lumi);
        srcTree->SetBranchAddress("EventNumber", &event);
        
        
        // Create output trees or reset their buffer addresses
        if (not trainTree)  // this is the first source file
        {
            trainTree.reset(srcTree->CloneTree(0));
            trainTree->SetDirectory(&trainFile);
            
            examTree.reset(srcTree->CloneTree(0));
            examTree->SetDirectory(&examFile);
        }

        else
        {
            srcTree->CopyAddresses(trainTree.get());
            srcTree->CopyAddresses(examTree.get());
        }
        
        
        // Loop over events in the source tree and fill the output trees
        for (unsigned long ev = 0; ev < nEntries; ++ev)
        {
            srcTree->GetEntry(ev);

            // If the event is in the first half, it goes to training set, otherwise exam
            if (ev <= (nEntries / 2) - 1) // half-divide if even, train has 1 less events if odd
                trainTree->Fill();
            else
                examTree->Fill();

        }
    }
    
    
    // The output trees has been filled. Write them
    trainFile.cd();
    trainTree->Write("Vars", TObject::kOverwrite);
    
    examFile.cd();
    examTree->Write("Vars", TObject::kOverwrite);

}


int main() {
    
    /*/ Split the tuples for each processes
    DoSplitTuples({"thq-nc-mg_mu.root", "thq-nc-mg_ele.root"}, "thq-nc-mg");
    //DoSplitTuples({"thq-sm-mg_mu.root", "thq-sm-mg_ele.root"}, "thq-sm-mg");
    DoSplitTuples({"ttbar-semilep-mg-p1_mu.root", "ttbar-semilep-mg-p1_ele.root", "ttbar-semilep-mg-p2_mu.root", "ttbar-semilep-mg-p2_ele.root", "ttbar-semilep-mg-p3_mu.root", "ttbar-semilep-mg-p3_ele.root"}, "ttbar-semilep-mg");
    DoSplitTuples({"ttbar-dilep-mg_mu.root", "ttbar-dilep-mg_ele.root"}, "ttbar-dilep-mg");
    DoSplitTuples({"tth_mu.root", "tth_ele.root"}, "tth");
    DoSplitTuples({"t-tchan-pw_mu.root", "t-tchan-pw_ele.root", "tbar-tchan-pw_mu.root", "tbar-tchan-pw_ele.root"}, "t-tchan-pw");
    DoSplitTuples({"t-tWchan-pw_mu.root", "t-tWchan-pw_ele.root", "tbar-tWchan-pw_mu.root", "tbar-tWchan-pw_ele.root"}, "t-tWchan-pw");
    //DoSplitTuples({"t-schan-pw_mu.root", "t-schan-pw_ele.root", "tbar-schan-pw_mu.root", "tbar-schan-pw_ele.root"}, "t-schan-pw");
    DoSplitTuples({"Wjets-mg_mu.root", "Wjets-mg_ele.root", "Wjets-2p-mg_mu.root", "Wjets-2p-mg_ele.root", "Wjets-3p-mg_mu.root", "Wjets-3p-mg_ele.root", "Wjets-4p-mg_mu.root", "Wjets-4p-mg_ele.root"}, "Wjets-mg");*/

    // Split the tuples for each processes
    DoSplitTuples({"thq-nc-mg_53X.02.01_Wyg_mu.root", "thq-nc-mg_53X.02.01_Wyg_ele.root"}, "thq-nc");
    //DoSplitTuples({}, "thq-sm");
    DoSplitTuples({"ttbar-semilep-mg-p1_53X.02.01_VNz_p1_mu.root", "ttbar-semilep-mg-p1_53X.02.01_VNz_p1_ele.root", "ttbar-semilep-mg-p1_53X.02.01_VNz_p2_mu.root", "ttbar-semilep-mg-p1_53X.02.01_VNz_p2_ele.root",
                   "ttbar-semilep-mg-p1_53X.02.01_VNz_p3_mu.root", "ttbar-semilep-mg-p1_53X.02.01_VNz_p3_ele.root", "ttbar-semilep-mg-p1_53X.02.01_VNz_p4_mu.root", "ttbar-semilep-mg-p1_53X.02.01_VNz_p4_ele.root",
                   "ttbar-semilep-mg-p2_53X.02.01_Ptw_p1_mu.root", "ttbar-semilep-mg-p2_53X.02.01_Ptw_p1_ele.root", "ttbar-semilep-mg-p2_53X.02.01_Ptw_p2_mu.root", "ttbar-semilep-mg-p2_53X.02.01_Ptw_p2_ele.root",
                   "ttbar-semilep-mg-p2_53X.02.01_Ptw_p3_mu.root", "ttbar-semilep-mg-p2_53X.02.01_Ptw_p3_ele.root", "ttbar-semilep-mg-p2_53X.02.01_Ptw_p4_mu.root", "ttbar-semilep-mg-p2_53X.02.01_Ptw_p4_ele.root",
                   "ttbar-semilep-mg-p2_53X.02.01_Ptw_p5_mu.root", "ttbar-semilep-mg-p2_53X.02.01_Ptw_p5_ele.root",
                   "ttbar-semilep-mg-p3_53X.02.01_MXn_p1_mu.root", "ttbar-semilep-mg-p3_53X.02.01_MXn_p1_ele.root", "ttbar-semilep-mg-p3_53X.02.01_MXn_p2_mu.root", "ttbar-semilep-mg-p3_53X.02.01_MXn_p2_ele.root",
                   "ttbar-semilep-mg-p3_53X.02.01_MXn_p3_mu.root", "ttbar-semilep-mg-p3_53X.02.01_MXn_p3_ele.root", "ttbar-semilep-mg-p3_53X.02.01_MXn_p4_mu.root", "ttbar-semilep-mg-p3_53X.02.01_MXn_p4_ele.root",
                   "ttbar-semilep-mg-p3_53X.02.01_MXn_p5_mu.root", "ttbar-semilep-mg-p3_53X.02.01_MXn_p5_ele.root",}, "ttbar-semilep");
    DoSplitTuples({"ttbar-dilep-mg_53X.02.01_FFe_p1_mu.root", "ttbar-dilep-mg_53X.02.01_FFe_p1_ele.root", "ttbar-dilep-mg_53X.02.01_FFe_p2_mu.root", "ttbar-dilep-mg_53X.02.01_FFe_p2_ele.root"}, "ttbar-dilep");
    DoSplitTuples({"tth_53X.02.01_bVJ_mu.root", "tth_53X.02.01_bVJ_ele.root"}, "tth");
    DoSplitTuples({"t-tchan-pw_53X.02.01_PIN_mu.root", "t-tchan-pw_53X.02.01_PIN_ele.root", "tbar-tchan-pw_53X.02.01_VcT_mu.root", "tbar-tchan-pw_53X.02.01_VcT_ele.root"}, "t-tchan");
    DoSplitTuples({"t-tWchan-pw_53X.02.01_LxG_mu.root", "t-tWchan-pw_53X.02.01_LxG_ele.root", "tbar-tWchan-pw_53X.02.01_tge_mu.root", "tbar-tWchan-pw_53X.02.01_tge_ele.root"}, "t-tWchan");
    //DoSplitTuples({}, "t-schan");
    DoSplitTuples({"Wjets-2p-mg_53X.02.01_Dhm_mu.root", "Wjets-2p-mg_53X.02.01_Dhm_ele.root", "Wjets-3p-mg_53X.02.01_YDn_mu.root", "Wjets-3p-mg_53X.02.01_YDn_ele.root",
                   "Wjets-4p-mg_53X.02.01_FxU_mu.root", "Wjets-4p-mg_53X.02.01_FxU_ele.root"}, "Wjets");

    return 0;

}
