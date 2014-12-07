/*** evtGet.cpp
- A code to print out in text file etc the values of a particular branch in a root file
- Primarily to investigate the weird event yields of ttbar with every run
- For now only scalar variables are supported
- Root macro as usual
- no ranged for loop in Root, ugh
***/

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

void evtGet() {

  string inDir, fileName;

  // where to find the files (update just this part)
  inDir = "/home/ieeya/Downloads/tHq/Part3_OpMVA/Classification/newFiles/tuples_deBug02/";

  /*vector<string> fileNames;
  fileNames.push_back("thq-nc-mg_train");
  fileNames.push_back("thq-nc-mg_exam");
  fileNames.push_back("ttbar-semilep-mg_train");
  fileNames.push_back("ttbar-semilep-mg_exam");
  fileNames.push_back("ttbar-dilep-mg_train");
  fileNames.push_back("ttbar-dilep-mg_exam");
  fileNames.push_back("tth_train");
  fileNames.push_back("tth_exam");
  fileNames.push_back("t-tchan-pw_train");
  fileNames.push_back("t-tchan-pw_exam");
  fileNames.push_back("t-tWchan-pw_train");
  fileNames.push_back("t-tWchan-pw_exam");
  fileNames.push_back("Wjets-mg_train");
  fileNames.push_back("Wjets-mg_exam");*/

  /*string fileNames[14] = {"thq-nc-mg_train", "thq-nc-mg_exam", "ttbar-semilep-mg_train", "ttbar-semilep-mg_exam",
                          "ttbar-dilep-mg_train", "ttbar-dilep-mg_exam", "tth_train", "tth_exam",
                          "t-tchan-pw_train", "t-tchan-pw_exam", "t-tWchan-pw_train", "t-tWchan-pw_exam",
                          "Wjets-mg_train", "Wjets-mg_exam"};*/

  //string fileNames[2] = {"ttbar-semilep-mg-p1_mu", "ttbar-semilep-mg-p1_ele"};
  string fileNames[8] = {"ttbar-semilep-mg-p1_53X.02.01_VNz_p1_ele", "ttbar-semilep-mg-p1_53X.02.01_VNz_p1_mu", 
                         "ttbar-semilep-mg-p1_53X.02.01_VNz_p2_ele", "ttbar-semilep-mg-p1_53X.02.01_VNz_p2_mu", 
                         "ttbar-semilep-mg-p1_53X.02.01_VNz_p3_ele", "ttbar-semilep-mg-p1_53X.02.01_VNz_p3_mu",
                         "ttbar-semilep-mg-p1_53X.02.01_VNz_p4_ele", "ttbar-semilep-mg-p1_53X.02.01_VNz_p4_mu"};

  //for (Int_t a = 0; a < 14; a++) {
  for (Int_t a = 0; a < 8; a++) {

    fileName = fileNames[a];

    // output text
    ofstream outVar;

    outVar.open((inDir + fileName + ".txt").c_str());
    outVar << inDir << endl;
    outVar << "List of event numbers in " << fileName << ":" << endl;
    outVar << endl;

    TChain *vars = new TChain("Vars");
    vars->Add((inDir + fileName + ".root").c_str());

    // declare the branches to be copied over
    Long_t evtNo;
    vars->SetBranchAddress("EventNumber", &evtNo);

    Int_t nEvt = vars->GetEntries();

    for (Int_t b = 0; b < nEvt; b++) {

      vars->GetEntry(b);
      outVar << evtNo << endl;

    }

    outVar.close();

  } 
}
