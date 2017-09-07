// -*- C++ -*-

#include <memory>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/METReco/interface/GenMET.h"
#include "DataFormats/METReco/interface/GenMETCollection.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Common/interface/ValueMap.h"

#include "TLorentzVector.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

#include <string>
#include <iostream>

const int maxLep = 2;
const int maxQua = 6; // includes b
const int maxJet = 10;

class ttSelector : public edm::EDAnalyzer {
public:
  explicit ttSelector(const edm::ParameterSet&);
  ~ttSelector();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  const reco::Candidate* getGeneratorFinalStateFor(const reco::Candidate*);
  virtual void beginRun(const edm::Run& run,const edm::EventSetup& setup);
  virtual void beginJob();
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob();
  void resetTree();

  // ----------member data ---------------------------
  edm::EDGetTokenT<reco::GenParticleCollection> genParToken;
  edm::EDGetTokenT<reco::GenJetCollection> genJetToken;
  edm::EDGetTokenT<reco::GenMETCollection> genMetToken;
  edm::EDGetTokenT<GenEventInfoProduct> genEvtToken;

  double gEvt_wgt;
  int nJet;
  double jetPt[maxJet], jetEta[maxJet], jetPhi[maxJet], jetE[maxJet];
  int nEvt, nRun, nLumi;

  int nLep, lepId[maxLep];
  double lepPt[maxLep], lepEta[maxLep], lepPhi[maxLep], lepE[maxLep];
  int nNeu, neuId[maxLep];
  double neuPt[maxLep], neuEta[maxLep], neuPhi[maxLep], neuE[maxLep];
  int nQua, quaId[maxQua];
  double quaPt[maxQua], quaEta[maxQua], quaPhi[maxQua], quaE[maxQua];
  int nFat, fatId[4];
  double fatPt[4], fatEta[4], fatPhi[4], fatE[4];
  double metPx, metPy, metPt, metPhi, metSumEt;

  int accEvt, decayType;
  bool doKinSel, includeTau;
  double lepPtCut, lepEtaCut;
  double jetPtCut, jetEtaCut;
  bool includeGenJetMET;

  typedef std::pair<int, double> OrderPair;
  struct IndexByPt {
    const bool operator() (const OrderPair& j1, const OrderPair& j2) const {return j1.second > j2.second;}
  };

  std::string outputName;
  TFile* f;
  TTree* t;
  TH1D *sumWgt, *sumEvt;

};

void ttSelector::beginRun(const edm::Run& run,const edm::EventSetup& setup) {}


ttSelector::ttSelector(const edm::ParameterSet& iParSet) {
  outputName      = iParSet.getParameter<std::string>("outputName"); 
  decayType       = iParSet.getParameter<int>("decayType");
  includeTau      = iParSet.getParameter<bool>("includeTau");
  doKinSel        = iParSet.getParameter<bool>("doKinSel");

  includeGenJetMET = false;

  /*/ GEN
  genParToken     = consumes<reco::GenParticleCollection>(edm::InputTag("genParticles"));
  if (includeGenJetMET) {
    genJetToken     = consumes<reco::GenJetCollection>(edm::InputTag("ak4GenJets"));
    genMetToken     = consumes<reco::GenMETCollection>(edm::InputTag("genMetTrue"));
  }
  */

  // mAOD
  genParToken     = consumes<reco::GenParticleCollection>(edm::InputTag("prunedGenParticles"));
  if (includeGenJetMET) {
    genJetToken     = consumes<reco::GenJetCollection>(edm::InputTag("slimmedGenJets"));
    genMetToken     = consumes<reco::GenMETCollection>(edm::InputTag("genMetTrue"));
  }

  genEvtToken     = consumes<GenEventInfoProduct>(edm::InputTag("generator"));

  lepPtCut = 0.; 
  lepEtaCut = 20.;
  jetPtCut = 0.;
  jetEtaCut = 20.;

  // Kinematic selection at gen level
  if (doKinSel) {
    edm::ParameterSet selectionCuts = iParSet.getParameter<edm::ParameterSet>("kinSelection");
    if (selectionCuts.existsAs<double>("jetPtCut"))
      jetPtCut = selectionCuts.getParameter<double>("jetPtCut");
    if (selectionCuts.existsAs<double>("jetEtaCut"))
      jetEtaCut = selectionCuts.getParameter<double>("jetEtaCut");
    if (selectionCuts.existsAs<double>("lepPtCut"))
      lepPtCut = selectionCuts.getParameter<double>("lepPtCut");
    if (selectionCuts.existsAs<double>("lepEtaCut"))
      lepEtaCut = selectionCuts.getParameter<double>("lepEtaCut");
  }

  std::cout << "JetCuts: " << jetPtCut << "\t" << jetEtaCut << std::endl;
  std::cout << "LepCuts: " << lepPtCut << "\t" << lepEtaCut << std::endl;

  sumWgt = new TH1D("sumWgt", "", 1, 0.5, 1.5);
  sumEvt = new TH1D("sumEvt", "", 1, 0.5, 1.5);
}

ttSelector::~ttSelector() 
{}

void ttSelector::resetTree() {

  // Reset the variables to its default state
  accEvt = false;
  gEvt_wgt = 0.;

  metPx = 0.;
  metPy = 0.;
  metPt = -1.;
  metPhi = 9999.;
  metSumEt = -1.;

  nFat = 0;
  for (int i = 0; i < 4; ++i) {
    fatId[i]  = 0;
    fatPt[i]  = -1.;
    fatEta[i] = 9999.;
    fatPhi[i] = 9999.;
    fatE[i]   = -1.;
  }

  nJet = 0;
  for (int i = 0; i < maxJet; ++i) {
    jetPt[i]  = -1.;
    jetEta[i] = 9999.;
    jetPhi[i] = 9999.;
    jetE[i]   = -1.;
  }

  nLep = 0;
  nNeu = 0;
  for (int i = 0; i < maxLep; ++i) {
    lepId[i]  = 0;
    lepPt[i]  = -1.;
    lepEta[i] = 9999.;
    lepPhi[i] = 9999.;
    lepE[i]   = -1.;

    neuId[i]  = 0;
    neuPt[i]  = -1.;
    neuEta[i] = 9999.;
    neuPhi[i] = 9999.;
    neuE[i]   = -1.;
  }

  nQua = 0;
  for (int i = 0; i < maxQua; ++i) {
    quaId[i]  = 0;
    quaPt[i]  = -1.;
    quaEta[i] = 9999.;
    quaPhi[i] = 9999.;
    quaE[i]   = -1.;
  }
}

//
// member functions
//

const reco::Candidate* ttSelector::getGeneratorFinalStateFor(const reco::Candidate *p) {

  // Ensures that any candidate is really its generator final state
  if (p == 0) return 0; // No candidate so reject the event

  const reco::Candidate *prevState = p;
  do {

    const reco::Candidate *nextState = 0;
    int nDaughter = prevState->numberOfDaughters();
    for (int iDaughter=0; iDaughter < nDaughter; iDaughter++) {

      const reco::Candidate *dau = prevState->daughter(iDaughter);
      if(dau == 0) continue;
      if(dau->pdgId() != p->pdgId()) continue;
      nextState = dau;
      break;

    }
    if (nextState == 0) break;
    if (nextState == prevState) break;
    prevState = nextState;
  } while (1);

  return prevState;
}

void ttSelector::analyze(const edm::Event& iEvt, const edm::EventSetup& iSetup) {

  nRun = iEvt.eventAuxiliary().run();
  nEvt = iEvt.eventAuxiliary().event();
  nLumi = iEvt.eventAuxiliary().luminosityBlock();

  using reco::GenParticleCollection;
  using reco::GenJetCollection;
  using reco::GenMETCollection;

  IndexByPt indexComparator;

  resetTree();

  edm::Handle<GenEventInfoProduct> gEvtH;
  iEvt.getByToken(genEvtToken, gEvtH);
  gEvt_wgt = gEvtH->weight();
  sumWgt->Fill(1., gEvt_wgt);
  sumEvt->Fill(1.);

  edm::Handle<GenParticleCollection> gpH;
  iEvt.getByToken(genParToken, gpH);

  std::vector<double> fat_pts, fat_etas, fat_phis, fat_es; 
  std::vector<double> lep_pts, lep_etas, lep_phis, lep_es;
  std::vector<double> neu_pts, neu_etas, neu_phis, neu_es; 
  std::vector<double> qua_pts, qua_etas, qua_phis, qua_es;
  std::vector<int> fat_ids, lep_ids, neu_ids, qua_ids;
  std::vector<OrderPair> lep_ordered, qua_ordered;
  for (size_t i = 0; i < gpH->size(); ++i ) {

    const reco::GenParticle &p = (*gpH)[i];
    if ( p.status() < 20 or p.status() > 30 ) continue;

    // Dump t/b qua properties
    if(std::abs(p.pdgId()) ==  6 and p.status()==22) {

      const reco::Candidate *top = getGeneratorFinalStateFor(&p); // Find the top

      fat_pts.push_back(top->pt());
      fat_etas.push_back(top->eta());
      fat_phis.push_back(top->phi());
      fat_es.push_back(top->energy());
      fat_ids.push_back(top->pdgId());
      nFat++;

      int nTopDau = top->numberOfDaughters();

      for (int j = 0; j < nTopDau; ++j) { // Loop on the top daughters

        const reco::Candidate *top_daughter;
        top_daughter = getGeneratorFinalStateFor(top->daughter(j));

        int dauId = top_daughter->pdgId();
        if (std::abs(dauId) ==  5) {
          qua_pts.push_back(top_daughter->pt());
          qua_etas.push_back(top_daughter->eta());
          qua_phis.push_back(top_daughter->phi());
          qua_es.push_back(top_daughter->energy());
          qua_ids.push_back(top_daughter->pdgId());
          qua_ordered.push_back(std::make_pair(nQua, top_daughter->pt()));
          nQua++;
        }

        if (std::abs(dauId) == 24) {

          fat_pts.push_back(top_daughter->pt());
          fat_etas.push_back(top_daughter->eta());
          fat_phis.push_back(top_daughter->phi());
          fat_es.push_back(top_daughter->energy());
          fat_ids.push_back(top_daughter->pdgId());
          nFat++;

          int nWDau = top_daughter->numberOfDaughters();

          for (int k = 0; k < nWDau; ++ k) { // Loop on the W daughters

            const reco::Candidate *w_daughter;
            w_daughter = getGeneratorFinalStateFor(top_daughter->daughter(k));

            if (std::abs(w_daughter->pdgId()) == 11 or std::abs(w_daughter->pdgId()) == 13 or (includeTau and std::abs(w_daughter->pdgId()) == 15)) { // Leptonic W daughters

              if (nLep < maxLep) {
                lep_pts.push_back(w_daughter->pt());
                lep_etas.push_back(w_daughter->eta());
                lep_phis.push_back(w_daughter->phi());
                lep_es.push_back(w_daughter->energy());
                lep_ids.push_back(w_daughter->pdgId());
                lep_ordered.push_back(std::make_pair(nLep, w_daughter->pt()));
              }
              nLep++;
            }

            if (std::abs(w_daughter->pdgId()) == 12 or std::abs(w_daughter->pdgId()) == 14 or (includeTau and std::abs(w_daughter->pdgId()) == 16)) {

              if (nNeu < maxLep) {
                neu_pts.push_back(w_daughter->pt());
                neu_etas.push_back(w_daughter->eta());
                neu_phis.push_back(w_daughter->phi());
                neu_es.push_back(w_daughter->energy());
                neu_ids.push_back(w_daughter->pdgId());;
              }
              nNeu++;
            }

            if (std::abs(w_daughter->pdgId()) > 0 and std::abs(w_daughter->pdgId()) < 5 ) { // Hadronic W daughters

              if (nQua < maxQua) {
                qua_pts.push_back(w_daughter->pt());
                qua_etas.push_back(w_daughter->eta());
                qua_phis.push_back(w_daughter->phi());
                qua_es.push_back(w_daughter->energy());
                qua_ids.push_back(w_daughter->pdgId());
                qua_ordered.push_back(std::make_pair(nQua, w_daughter->pt()));
              }

              nQua++;
            }
          }
        }
      }
    }
  }

  std::sort(lep_ordered.begin(), lep_ordered.end(), indexComparator);
  std::sort(qua_ordered.begin(),  qua_ordered.end(), indexComparator);

  for (int i = 0; i < nFat; i++) {
    fatId [i] = fat_ids [i];
    fatPt [i] = fat_pts [i];
    fatEta[i] = fat_etas[i];
    fatPhi[i] = fat_phis[i];
    fatE  [i] = fat_es  [i];
  }

  for (int i = 0; i < nNeu; i++) {
    neuId [i] = neu_ids [i];
    neuPt [i] = neu_pts [i];
    neuEta[i] = neu_etas[i];
    neuPhi[i] = neu_phis[i];
    neuE  [i] = neu_es  [i];
  }

  int lepi = 0;
  for (std::vector<OrderPair>::const_iterator it = lep_ordered.begin();
       it != lep_ordered.end(); ++it, ++lepi) {
    int index = it->first;
    if (lepi < maxLep) {
      lepId [lepi] = lep_ids [index];
      lepPt [lepi] = lep_pts [index];
      lepEta[lepi] = lep_etas[index];
      lepPhi[lepi] = lep_phis[index];
      lepE  [lepi] = lep_es  [index];
    }
  }

  int quai = 0;
  for (std::vector<OrderPair>::const_iterator it = qua_ordered.begin();
       it != qua_ordered.end(); ++it, ++quai) {
    int index = it->first;
    if (quai < maxQua) {
      quaId [quai] = qua_ids [index];
      quaPt [quai] = qua_pts [index];
      quaEta[quai] = qua_etas[index];
      quaPhi[quai] = qua_phis[index];
      quaE  [quai] = qua_es  [index];
    }
  }

  bool quaOk = false;
  bool lepOk = false;
  int nL = 0, nLkin = 0;
  bool jetOk = false;
  int nJ = 0, nJkin = 0;

  if (includeGenJetMET) {
    edm::Handle<GenJetCollection> genJets;
    iEvt.getByToken(genJetToken, genJets);

    for (size_t i=0; i < genJets->size(); ++i) {

      if (i > maxJet - 1) break;
      const reco::GenJet &jet = (*genJets)[i];
      jetPt [i] = jet.pt();
      jetEta[i] = jet.eta();
      jetPhi[i] = jet.phi();
      jetE  [i] = jet.energy();

      nJ++;
      if (doKinSel) {
        if ((jetPt[i] > jetPtCut) and std::abs(jetEta[i]) < jetEtaCut)
          nJkin++;
      }
    }

    nJet = nJ;
    if (nJ >= nQua) quaOk = true;

    edm::Handle<GenMETCollection> genMet;
    iEvt.getByToken(genMetToken, genMet);

    const reco::GenMET &met = (*genMet)[0];
    metPx = met.px();
    metPy = met.py();
    metPt = met.pt();
    metPhi = met.phi();
    metSumEt = met.sumEt();
  }
  else quaOk = true;

  for (int k = 0; k < nLep; k++) {

    if (std::abs(lepId[k]) != 11 and std::abs(lepId[k]) != 13 and (!includeTau and std::abs(lepId[k]) != 15))
      continue;

    nL++;
    if ((lepPt[k] > lepPtCut) and (std::abs(lepEta[k]) < lepEtaCut))
      nLkin++;
  }

  if (decayType == 1) { // semileptonic
    if (doKinSel) {
      lepOk = (nLkin == 1);
      jetOk = (nJkin >= 4);
    }
    else {
      lepOk = (nL == 1);
      jetOk = (nJ >= 4);
    }
  }

  else if (decayType == 2) { // dileptonic
    if (doKinSel) {
      lepOk = (nLkin == 2);
      jetOk = (nJkin >= 2);
    }
    else {
      lepOk = (nL == 2);
      jetOk = (nJ >= 2);
    }
  }
   
  else if (decayType == 3) { // hadronic
    if (doKinSel) {
      lepOk = (nLkin == 0);
      jetOk = (nJkin >= 6);
    }
    else {
      lepOk = (nL == 0);
      jetOk = (nJ >= 6);
    }
  }

  accEvt = (quaOk and lepOk and (jetOk or !includeGenJetMET));
  if (accEvt) t->Fill();
}
 
void ttSelector::beginJob() {
  f = new TFile(outputName.c_str(), "recreate");
  t = new TTree("tree", "tree");
  t->SetAutoSave(5000000);

  t->Branch("nRun", &nRun, "nRun/I");
  t->Branch("nEvt", &nEvt, "nEvt/I");
  t->Branch("nLumi", &nLumi, "nLumi/I");
  
  t->Branch("gEvt_wgt", &gEvt_wgt, "gEvt_wgt/D");
  t->Branch("accEvt", &accEvt, "accEvt/I");

  if (includeGenJetMET) {
    t->Branch("nJet",   &nJet,  "nJet/I");
    t->Branch("jetPt",  jetPt,  "jetPt[nJet]/D");
    t->Branch("jetEta", jetEta, "jetEta[nJet]/D");
    t->Branch("jetPhi", jetPhi, "jetPhi[nJet]/D");
    t->Branch("jetE",   jetE,   "jetE[nJet]/D");

    t->Branch("metPx",    &metPx,    "metPx/D");
    t->Branch("metPy",    &metPy,    "metPy/D");
    t->Branch("metPt",    &metPt,    "metPt/D");
    t->Branch("metPhi",   &metPhi,   "metPhi/D");
    t->Branch("metSumEt", &metSumEt, "metSumEt/D");
  }

  t->Branch("nFat",   &nFat,  "nFat/I");
  t->Branch("fatPt",  fatPt,  "fatPt[nFat]/D");
  t->Branch("fatEta", fatEta, "fatEta[nFat]/D");
  t->Branch("fatPhi", fatPhi, "fatPhi[nFat]/D");
  t->Branch("fatE",   fatE,   "fatE[nFat]/D");
  t->Branch("fatId",  fatId,  "fatId[nFat]/I");

  t->Branch("nLep",   &nLep,  "nLep/I");
  t->Branch("lepPt",  lepPt,  "lepPt[nLep]/D");
  t->Branch("lepEta", lepEta, "lepEta[nLep]/D");
  t->Branch("lepPhi", lepPhi, "lepPhi[nLep]/D");
  t->Branch("lepE",   lepE,   "lepE[nLep]/D");
  t->Branch("lepId",  lepId,  "lepId[nLep]/I");

  t->Branch("nNeu",   &nNeu,  "nNeu/I");
  t->Branch("neuPt",  neuPt,  "neuPt[nNeu]/D");
  t->Branch("neuEta", neuEta, "neuEta[nNeu]/D");
  t->Branch("neuPhi", neuPhi, "neuPhi[nNeu]/D");
  t->Branch("neuE",   neuE,   "neuE[nNeu]/D");
  t->Branch("neuId",  neuId,  "neuId[nNeu]/I");

  t->Branch("nQua",   &nQua,  "nQua/I");
  t->Branch("quaPt",  quaPt,  "quaPt[nQua]/D");
  t->Branch("quaEta", quaEta, "quaEta[nQua]/D");
  t->Branch("quaPhi", quaPhi, "quaPhi[nQua]/D");
  t->Branch("quaE",   quaE,   "quaE[nQua]/D");
  t->Branch("quaId",  quaId,  "quaId[nQua]/I");
}

void ttSelector::endJob() {
  f->cd();
  t->Write();
  sumWgt->Write();
  sumEvt->Write();
  f->Close();
}

void ttSelector::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  // The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

DEFINE_FWK_MODULE(ttSelector);
