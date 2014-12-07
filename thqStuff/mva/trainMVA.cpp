/**
 * The program trains an MVA to perform jet assignment for semileptonic decay of a top quark.
**/

#include <TMVA/Factory.h>
#include <TFile.h>
#include <string>
#include <memory>


using namespace std;


int main()
{
    // Create a log file and a factory
    string const jobName("THvsTTbar_Global");
    TFile infoFile((string("info") + jobName + ".root").c_str(), "recreate");
    TMVA::Factory factory(jobName, &infoFile, "Color=True");
    
    // Specifiy signal and background trees and event weights

    string tupDir("tuples_fullRap/");

    // thq-nc
    TFile sgnTrainFile01((tupDir + "thq-nc_train.root").c_str());
    unique_ptr<TTree> sgnTrainTree01(dynamic_cast<TTree *>(sgnTrainFile01.Get("Vars")));
    
    TFile sgnExamFile01((tupDir + "thq-nc_exam.root").c_str());
    unique_ptr<TTree> sgnExamTree01(dynamic_cast<TTree *>(sgnExamFile01.Get("Vars")));

    // ttbar-semilep    
    TFile bkgTrainFile01((tupDir + "ttbar-semilep_train.root").c_str());
    unique_ptr<TTree> bkgTrainTree01(dynamic_cast<TTree *>(bkgTrainFile01.Get("Vars")));
    
    TFile bkgExamFile01((tupDir + "ttbar-semilep_exam.root").c_str());
    unique_ptr<TTree> bkgExamTree01(dynamic_cast<TTree *>(bkgExamFile01.Get("Vars")));

    // ttbar-dilep
    TFile bkgTrainFile02((tupDir + "ttbar-dilep_train.root").c_str());
    unique_ptr<TTree> bkgTrainTree02(dynamic_cast<TTree *>(bkgTrainFile02.Get("Vars")));
    
    TFile bkgExamFile02((tupDir + "ttbar-dilep_exam.root").c_str());
    unique_ptr<TTree> bkgExamTree02(dynamic_cast<TTree *>(bkgExamFile02.Get("Vars")));

    // tth
    TFile bkgTrainFile03((tupDir + "tth_train.root").c_str());
    unique_ptr<TTree> bkgTrainTree03(dynamic_cast<TTree *>(bkgTrainFile03.Get("Vars")));
    
    TFile bkgExamFile03((tupDir + "tth_exam.root").c_str());
    unique_ptr<TTree> bkgExamTree03(dynamic_cast<TTree *>(bkgExamFile03.Get("Vars")));

    /*/ t-tchan
    TFile bkgTrainFile04((tupDir + "t-tchan_train.root").c_str());
    unique_ptr<TTree> bkgTrainTree04(dynamic_cast<TTree *>(bkgTrainFile04.Get("Vars")));
    
    TFile bkgExamFile04((tupDir + "t-tchan_exam.root").c_str());
    unique_ptr<TTree> bkgExamTree04(dynamic_cast<TTree *>(bkgExamFile04.Get("Vars")));

    // t-schan
    TFile bkgTrainFile05((tupDir + "t-schan_train.root").c_str());
    unique_ptr<TTree> bkgTrainTree05(dynamic_cast<TTree *>(bkgTrainFile05.Get("Vars")));

    TFile bkgExamFile05((tupDir + "t-schan_exam.root").c_str());
    unique_ptr<TTree> bkgExamTree05(dynamic_cast<TTree *>(bkgExamFile05.Get("Vars")));

    // t-tWchan
    TFile bkgTrainFile06((tupDir + "t-tWchan_train.root").c_str());
    unique_ptr<TTree> bkgTrainTree06(dynamic_cast<TTree *>(bkgTrainFile06.Get("Vars")));
    
    TFile bkgExamFile06((tupDir + "t-tWchan_exam.root").c_str());
    unique_ptr<TTree> bkgExamTree06(dynamic_cast<TTree *>(bkgExamFile06.Get("Vars")));

    // Wjets
    TFile bkgTrainFile07((tupDir + "Wjets_train.root").c_str());
    unique_ptr<TTree> bkgTrainTree07(dynamic_cast<TTree *>(bkgTrainFile07.Get("Vars")));
    
    TFile bkgExamFile07((tupDir + "Wjets_exam.root").c_str());
    unique_ptr<TTree> bkgExamTree07(dynamic_cast<TTree *>(bkgExamFile07.Get("Vars")));*/

    // A parameter to control which background to be included in the training
    int bkgUsed = 0;    

    factory.AddSignalTree(sgnTrainTree01.get(), 1., TMVA::Types::kTraining);
    if (bkgUsed == 0 or bkgUsed == 1) factory.AddBackgroundTree(bkgTrainTree01.get(), 1., TMVA::Types::kTraining);
    if (bkgUsed == 0 or bkgUsed == 2) factory.AddBackgroundTree(bkgTrainTree02.get(), 1., TMVA::Types::kTraining);
    if (bkgUsed == 0 or bkgUsed == 3) factory.AddBackgroundTree(bkgTrainTree03.get(), 1., TMVA::Types::kTraining);
    //if (bkgUsed == 0 or bkgUsed == 4) factory.AddBackgroundTree(bkgTrainTree04.get(), 1., TMVA::Types::kTraining);
    //if (bkgUsed == 0 or bkgUsed == 5) factory.AddBackgroundTree(bkgTrainTree05.get(), 1., TMVA::Types::kTraining);
    //if (bkgUsed == 0 or bkgUsed == 6) factory.AddBackgroundTree(bkgTrainTree06.get(), 1., TMVA::Types::kTraining);
    //if (bkgUsed == 0 or bkgUsed == 7) factory.AddBackgroundTree(bkgTrainTree07.get(), 1., TMVA::Types::kTraining);

    factory.AddSignalTree(sgnExamTree01.get(), 1., TMVA::Types::kTesting);
    if (bkgUsed == 0 or bkgUsed == 1) factory.AddBackgroundTree(bkgExamTree01.get(), 1., TMVA::Types::kTesting);
    if (bkgUsed == 0 or bkgUsed == 2) factory.AddBackgroundTree(bkgExamTree02.get(), 1., TMVA::Types::kTesting);
    if (bkgUsed == 0 or bkgUsed == 3) factory.AddBackgroundTree(bkgExamTree03.get(), 1., TMVA::Types::kTesting);
    //if (bkgUsed == 0 or bkgUsed == 4) factory.AddBackgroundTree(bkgExamTree04.get(), 1., TMVA::Types::kTesting);
    //if (bkgUsed == 0 or bkgUsed == 5) factory.AddBackgroundTree(bkgExamTree05.get(), 1., TMVA::Types::kTesting);
    //if (bkgUsed == 0 or bkgUsed == 6) factory.AddBackgroundTree(bkgExamTree06.get(), 1., TMVA::Types::kTesting);
    //if (bkgUsed == 0 or bkgUsed == 7) factory.AddBackgroundTree(bkgExamTree07.get(), 1., TMVA::Types::kTesting);
    
    factory.SetWeightExpression("Weight");

    // Refer to test299 for the 'essential' set, 312, 342 for test candidate
    
    // Specify the input variables
    // Global variables
    factory.AddVariable("glb_Charge_Lep", 'F');
    factory.AddVariable("glb_Sphericity", 'F');
    // thq hypothesis variables
    factory.AddVariable("thq_NumBTag_Higgs", 'F');
    factory.AddVariable("log(thq_Pt_Higgs)", 'F');
    factory.AddVariable("log(thq_Pt_Recoil)", 'F');
    factory.AddVariable("abs(thq_Rap_Recoil)", 'F');
    // tt hypothesis variables
    factory.AddVariable("tt_DeltaR_Light", 'F');
    factory.AddVariable("log(tt_Mass_TopHad)", 'F');
    factory.AddVariable("tt_NumPassBTag_Light", 'F');

    // Make the factory copy the trees
    factory.PrepareTrainingAndTestTree("", "NormMode=EqualNumEvents");
    
    // Book a BFGS NN, default hidden layer 30
    factory.BookMethod(TMVA::Types::kMLP, jobName + "_BFGS",
    "VarTransform=N:NeuronType=tanh:NCycles=500:HiddenLayers=30:TrainingMethod=BFGS:TestRate=5");
    
    // Train and test the MVA
    factory.TrainAllMethods();
    factory.TestAllMethods();
    factory.EvaluateAllMethods();
    
    return 0;
}
