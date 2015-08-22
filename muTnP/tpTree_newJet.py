# Jan 27: Based on MC02, included new jet definition for Z/schan study
# Also remove the stand-alone section, not needed

import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

process.load('FWCore.MessageService.MessageLogger_cfi')
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.source = cms.Source("PoolSource", 
    fileNames = cms.untracked.vstring(
        #'/store/mc/Fall11/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/PU_S6_START44_V9B-v1/0000/002612AC-463D-E111-802A-E0CB4E19F9BC.root',
        #'/store/mc/Fall11/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/PU_S6_START44_V9B-v1/0000/004F0141-A43C-E111-AE80-20CF305616E0.root',
        #'/store/mc/Fall11/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/PU_S6_START44_V9B-v1/0000/00536037-AF3C-E111-A6EA-20CF300E9ECB.root',
        #'/store/mc/Fall11/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/PU_S6_START44_V9B-v1/0000/005F7E58-AF3C-E111-8694-E0CB4E19F96D.root',
        #'/store/mc/Fall11/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/PU_S6_START44_V9B-v1/0000/0067C5E1-D63C-E111-B2BD-90E6BA442F23.root',
    ),
)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )    

process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")
process.GlobalTag.globaltag = cms.string('START44_V9B::All')

## ==== Fast Filters ====
process.goodVertexFilter = cms.EDFilter("VertexSelector",
    src = cms.InputTag("offlinePrimaryVertices"),
    cut = cms.string("!isFake && ndof > 4 && abs(z) <= 24 && position.Rho <= 2"),
    filter = cms.bool(True),
)
process.noScraping = cms.EDFilter("FilterOutScraping",
    applyfilter = cms.untracked.bool(True),
    debugOn = cms.untracked.bool(False), ## Or 'True' to get some per-event info
    numtrack = cms.untracked.uint32(10),
    thresh = cms.untracked.double(0.2)
)
process.fastFilter = cms.Sequence(process.goodVertexFilter + process.noScraping)

##    __  __                       
##   |  \/  |_   _  ___  _ __  ___ 
##   | |\/| | | | |/ _ \| '_ \/ __|
##   | |  | | |_| | (_) | | | \__ \
##   |_|  |_|\__,_|\___/|_| |_|___/
##                                 
## ==== Merge CaloMuons and Tracks into the collection of reco::Muons  ====
from RecoMuon.MuonIdentification.calomuons_cfi import calomuons;
process.mergedMuons = cms.EDProducer("CaloMuonMerger",
    mergeTracks = cms.bool(True),
    mergeCaloMuons = cms.bool(False), # AOD
    muons     = cms.InputTag("muons"), 
    caloMuons = cms.InputTag("calomuons"),
    tracks    = cms.InputTag("generalTracks"),
    minCaloCompatibility = calomuons.minCaloCompatibility,
    ## Apply some minimal pt cut
    muonsCut     = cms.string("pt > 10 && track.isNonnull"),
    caloMuonsCut = cms.string("pt > 10"),
    tracksCut    = cms.string("pt > 10"),
)

## ==== Trigger matching
process.load("MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff")
## with some customization
process.muonMatchHLTL2.maxDeltaR = 0.3 # Zoltan tuning - it was 0.5
process.muonMatchHLTL3.maxDeltaR = 0.1
from MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff import *
changeRecoMuonInput(process, "mergedMuons")
changeTriggerProcessName(process, "*") # auto-guess

from MuonAnalysis.TagAndProbe.common_variables_cff import *
process.load("MuonAnalysis.TagAndProbe.common_modules_cff")

# cuts are to be synchronized with the s-channel group (refer to Oct 24 2014 mail)
process.tagMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("patMuonsWithTrigger"),
    cut = cms.string("pt > 24 && abs(eta) < 2.1 && isPFMuon && isGlobalMuon && isTrackerMuon" # kinematics and muon type
                     + " && numberOfMatches() > 1 && muonID('GlobalMuonPromptTight') > 0 && abs(dB) < 0.02" # ID cuts
                     + " && innerTrack.numberOfValidHits > 10 && innerTrack.hitPattern.pixelLayersWithMeasurement() >= 1" # track-related cuts
                     + " && (pfIsolationR03().sumChargedHadronPt + pfIsolationR03().sumNeutralHadronEt + pfIsolationR03().sumPhotonEt) / pt < 0.15" # combined isolation without dBeta correction
                     + " && !triggerObjectMatchesByPath('HLT_IsoMu24_v*', 1, 0).empty()" # IsoMu17 trigger matching
                    ),
)

process.oneTag  = cms.EDFilter("CandViewCountFilter", src = cms.InputTag("tagMuons"), minNumber = cms.uint32(1))

# like tag without trigger matching
process.probeMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("patMuonsWithTrigger"),
    cut = cms.string("pt > 20 && abs(eta) < 2.1 && isPFMuon && isGlobalMuon && isTrackerMuon" # kinematics and muon type
                     + " && numberOfMatches() > 1 && muonID('GlobalMuonPromptTight') > 0 && abs(dB) < 0.02" # ID cuts
                     + " && innerTrack.numberOfValidHits > 10 && innerTrack.hitPattern.pixelLayersWithMeasurement() >= 1" # track-related cuts
                     + " && (pfIsolationR03().sumChargedHadronPt + pfIsolationR03().sumNeutralHadronEt + pfIsolationR03().sumPhotonEt) / pt < 0.15" # see tag
                    ),
)

process.tpPairs = cms.EDProducer("CandViewShallowCloneCombiner",
    cut = cms.string('70 < mass < 110 && abs(daughter(0).vz - daughter(1).vz) < 4'),
    decay = cms.string('tagMuons@+ probeMuons@-')
)
process.onePair = cms.EDFilter("CandViewCountFilter", src = cms.InputTag("tpPairs"), minNumber = cms.uint32(1))

process.tagMuonsMCMatch = cms.EDProducer("MCTruthDeltaRMatcherNew",
    src = cms.InputTag("tagMuons"),
    matched = cms.InputTag("genParticles"),
    pdgId = cms.vint32(13),
    distMin = cms.double(0.3),
)
process.probeMuonsMCMatch = process.tagMuonsMCMatch.clone(src = "probeMuons")

##   _______           _               
##  |__   __| ____   _| |_   _____
##     | |   / __ \ |_   _| /  ___\
##   _ | |  | ____/   | |   \  \
##  | \/ /  | \ ___   | | ___\  \
##   \ _/    \____/   |_| \ ____/                     
## ==== Section describing the jet selection  ====

process.load('RecoJets.Configuration.RecoPFJets_cff')
##-------------------- Turn-on the FastJet density calculation -----------------------
process.kt6PFJets.doRhoFastjet = True
##-------------------- FastJet density calculation for Iso -----------------------
process.kt6PFJetsForIso = process.kt6PFJets.clone( Rho_EtaMax = cms.double(2.5), Ghost_EtaMax = cms.double(2.5) )

from RecoJets.JetProducers.ak5PFJets_cfi import ak5PFJets
process.ak5PFJets = ak5PFJets.clone(src = 'particleFlow', doAreaFastjet = True)

process.load('RecoBTag.Configuration.RecoBTag_cff')
from RecoBTag.ImpactParameter.impactParameter_cff import *
process.btagging = cms.Sequence(impactParameterTagInfos * trackCountingHighPurBJetTags)

process.load('RecoJets.Configuration.RecoJetAssociations_cff')
process.ak5JetTracksAssociatorAtVertex.jets = cms.InputTag("ak5PFJets")

process.load("PhysicsTools.PatAlgos.producersLayer1.jetProducer_cff")

process.patAK5PFJetCorrFactors = process.patJetCorrFactors.clone(src = "ak5PFJets",
                                                                 payload = 'AK5PF',
                                                                )

process.patAK5PFJetPartonMatch = process.patJetPartonMatch.clone(src = "ak5PFJets")

process.patAK5PFJetGenJetMatch = process.patJetGenJetMatch.clone(src = "ak5PFJets")

process.patAK5PFJetPartonAssociation = process.patJetPartonAssociation.clone(jets = "ak5PFJets")

process.patAK5PFJetFlavourAssociation = process.patJetFlavourAssociation.clone(srcByReference = "patAK5PFJetPartonAssociation")

process.patAK5PFJetFlavourId = cms.Sequence(process.patJetPartons * process.patAK5PFJetPartonAssociation * process.patAK5PFJetFlavourAssociation)

process.patAK5PFJets = process.patJets.clone(jetSource = cms.InputTag("ak5PFJets"),
                                             jetCorrFactorsSource = cms.VInputTag(cms.InputTag("patAK5PFJetCorrFactors")),
                                             genPartonMatch = cms.InputTag("patAK5PFJetPartonMatch"),
                                             genJetMatch = cms.InputTag("patAK5PFJetGenJetMatch"),
                                             JetPartonMapSource = cms.InputTag("patAK5PFJetFlavourAssociation"),
                                             discriminatorSources = cms.VInputTag(cms.InputTag("trackCountingHighPurBJetTags")),
                                            )


process.makePatAK5PFJets = cms.Sequence(process.patAK5PFJetCorrFactors * # reco pre-production
                                        process.patJetCharge *
                                        # pat specifics
                                        process.patAK5PFJetPartonMatch *
                                        process.patAK5PFJetGenJetMatch *
                                        process.patAK5PFJetFlavourId *
                                        # object production
                                        process.patAK5PFJets
                                       )

process.tightJets = cms.EDFilter("PATJetSelector",
                         preselection = cms.string(''),
                         src = cms.InputTag("patAK5PFJets"),
                         cut = cms.string("numberOfDaughters()>1 && pt()> 40 && abs(eta())<4.5 && ((abs(eta())>=2.4)"
                                          + " || ( chargedHadronEnergyFraction() > 0 && chargedMultiplicity()>0 && neutralEmEnergyFraction() < 0.99"
                                          + " && neutralHadronEnergyFraction() < 0.99 && chargedEmEnergyFraction()<0.99))"
                                         ),
                         checkOverlaps = cms.PSet(),
                         )

process.taggedJets = cms.EDFilter("PATJetSelector",
                         preselection = cms.string(''),
                         src = cms.InputTag("tightJets"),
                         cut = cms.string('bDiscriminator(\"trackCountingHighPurBJetTags\") > 3.41'),
                         checkOverlaps = cms.PSet(),
                         )

process.nTightJetCounter = cms.EDProducer("CandCleanedMultiplicityCounter",
                                       pairs = cms.InputTag("tpPairs"),
                                       objects = cms.InputTag("tightJets"),
                                       objectSelection = cms.string(""),
                                       minTagObjDR = cms.double(0.3),
                                       minProbeObjDR = cms.double(0.3),
                                      )

process.nTaggedJetCounter = cms.EDProducer("CandCleanedMultiplicityCounter",
                                       pairs = cms.InputTag("tpPairs"),
                                       objects = cms.InputTag("taggedJets"),
                                       objectSelection = cms.string(""),
                                       minTagObjDR = cms.double(0.3),
                                       minProbeObjDR = cms.double(0.3),
                                      )

### ------------------- TP Tree --------------------------- ###

from MuonAnalysis.TagAndProbe.muon.tag_probe_muon_extraIso_cff import ExtraIsolationVariables

process.tpTree = cms.EDAnalyzer("TagProbeFitTreeProducer",
    # choice of tag and probe pairs, and arbitration
    tagProbePairs = cms.InputTag("tpPairs"),
    arbitration   = cms.string("OneProbe"),
    # probe variables: all useful ones
    variables = cms.PSet(
        # Basics
        pt = cms.string("pt"),
        p = cms.string("p"),
        eta = cms.string("eta"),
        phi = cms.string("phi"),
        abseta = cms.string("abs(eta)"),
        charge = cms.string("charge"),
        # Combined relative isolation for R = 0.3 and 0.4
        combRelIsoPF03 = cms.string("(pfIsolationR03().sumChargedHadronPt + pfIsolationR03().sumNeutralHadronEt + pfIsolationR03().sumPhotonEt)/pt"),
        combRelIsoPF03dBeta = cms.string("(pfIsolationR03().sumChargedHadronPt + max(pfIsolationR03().sumNeutralHadronEt + pfIsolationR03().sumPhotonEt - pfIsolationR03().sumPUPt/2,0.0))/pt"),
        combRelIsoPF04 = cms.string("(pfIsolationR04().sumChargedHadronPt + pfIsolationR04().sumNeutralHadronEt + pfIsolationR04().sumPhotonEt)/pt"),
        combRelIsoPF04dBeta = cms.string("(pfIsolationR04().sumChargedHadronPt + max(pfIsolationR04().sumNeutralHadronEt + pfIsolationR04().sumPhotonEt - pfIsolationR04().sumPUPt/2,0.0))/pt"),
        # Muon ID
        numberOfMatches = cms.string("? isMatchesValid ? numberOfMatches : -1"),
        numberOfMatchedStations = cms.string("? isMatchesValid ? numberOfMatchedStations : -1"),
        # Transverse IP
        dB = cms.string("dB"),
        edB = cms.string("edB"),
        # 3D IP
        IP = cms.string('abs(dB("PV3D"))'),
        IPError = cms.string('edB("PV3D")'),
        SIP = cms.string('abs(dB("PV3D")/edB("PV3D"))'),
        # L2
        l2pt = cms.string("? triggerObjectMatchesByCollection('hltL2MuonCandidates').empty() ? 0 : triggerObjectMatchesByCollection('hltL2MuonCandidates').at(0).pt"),
        l2eta = cms.string("? triggerObjectMatchesByCollection('hltL2MuonCandidates').empty() ? 0 : triggerObjectMatchesByCollection('hltL2MuonCandidates').at(0).eta"),
        l2dr = cms.string("? triggerObjectMatchesByCollection('hltL2MuonCandidates').empty() ? 999 : " +
                          " deltaR( eta, phi, " +
                          " triggerObjectMatchesByCollection('hltL2MuonCandidates').at(0).eta, "+
                          " triggerObjectMatchesByCollection('hltL2MuonCandidates').at(0).phi ) "),
        # L3
        l3pt = cms.string("? triggerObjectMatchesByCollection('hltL3MuonCandidates').empty() ? 0 : triggerObjectMatchesByCollection('hltL3MuonCandidates').at(0).pt"),
        l3dr = cms.string("? triggerObjectMatchesByCollection('hltL3MuonCandidates').empty() ? 999 : " +
                          " deltaR( eta, phi, " +
                          " triggerObjectMatchesByCollection('hltL3MuonCandidates').at(0).eta, " +
                          " triggerObjectMatchesByCollection('hltL3MuonCandidates').at(0).phi ) "),
    ),
    flags = cms.PSet(
        # Muon ID
        Calo = cms.string("isCaloMuon"),
        Glb = cms.string("isGlobalMuon"),
        GlbPT = cms.string("muonID('GlobalMuonPromptTight')"),
        TM = cms.string("isTrackerMuon"),
        TMA = cms.string("muonID('TrackerMuonArbitrated')"),
        PF = cms.string("isPFMuon()"),
        # Trigger
        IsoMu17 = cms.string("!triggerObjectMatchesByPath('HLT_IsoMu17_v*', 1, 0).empty()"),
        IsoMu24 = cms.string("!triggerObjectMatchesByPath('HLT_IsoMu24_v*', 1, 0).empty()"),
    ),
    tagVariables =  cms.PSet(
        # Basics
        pt = cms.string("pt"),
        p = cms.string("p"),
        eta = cms.string("eta"),
        phi = cms.string("phi"),
        abseta = cms.string("abs(eta)"),
        charge = cms.string("charge"),
        nVertices = cms.InputTag("nverticesModule"),
        # Combined relative isolation for R = 0.3 and 0.4
        combRelIsoPF03 = cms.string("(pfIsolationR03().sumChargedHadronPt + pfIsolationR03().sumNeutralHadronEt + pfIsolationR03().sumPhotonEt)/pt"),
        combRelIsoPF03dBeta = cms.string("(pfIsolationR03().sumChargedHadronPt + max(pfIsolationR03().sumNeutralHadronEt + pfIsolationR03().sumPhotonEt - pfIsolationR03().sumPUPt/2,0.0))/pt"),
        combRelIsoPF04 = cms.string("(pfIsolationR04().sumChargedHadronPt + pfIsolationR04().sumNeutralHadronEt + pfIsolationR04().sumPhotonEt)/pt"),
        combRelIsoPF04dBeta = cms.string("(pfIsolationR04().sumChargedHadronPt + max(pfIsolationR04().sumNeutralHadronEt + pfIsolationR04().sumPhotonEt - pfIsolationR04().sumPUPt/2,0.0))/pt"),
        # Muon ID
        numberOfMatches = cms.string("? isMatchesValid ? numberOfMatches : -1"),
        numberOfMatchedStations = cms.string("? isMatchesValid ? numberOfMatchedStations : -1"),
        # Transverse IP
        dB = cms.string("dB"),
        edB = cms.string("edB"),
        # 3D IP
        IP = cms.string('abs(dB("PV3D"))'),
        IPError = cms.string('edB("PV3D")'),
        SIP = cms.string('abs(dB("PV3D")/edB("PV3D"))'),
        # L2
        l2pt = cms.string("? triggerObjectMatchesByCollection('hltL2MuonCandidates').empty() ? 0 : triggerObjectMatchesByCollection('hltL2MuonCandidates').at(0).pt"),
        l2eta = cms.string("? triggerObjectMatchesByCollection('hltL2MuonCandidates').empty() ? 0 : triggerObjectMatchesByCollection('hltL2MuonCandidates').at(0).eta"),
        l2dr = cms.string("? triggerObjectMatchesByCollection('hltL2MuonCandidates').empty() ? 999 : " +
                          " deltaR( eta, phi, " +
                          " triggerObjectMatchesByCollection('hltL2MuonCandidates').at(0).eta, " +
                          " triggerObjectMatchesByCollection('hltL2MuonCandidates').at(0).phi ) "),
        # L3
        l3pt = cms.string("? triggerObjectMatchesByCollection('hltL3MuonCandidates').empty() ? 0 : triggerObjectMatchesByCollection('hltL3MuonCandidates').at(0).pt"),
        l3dr = cms.string("? triggerObjectMatchesByCollection('hltL3MuonCandidates').empty() ? 999 : " +
                          " deltaR( eta, phi, " +
                          " triggerObjectMatchesByCollection('hltL3MuonCandidates').at(0).eta, " +
                          " triggerObjectMatchesByCollection('hltL3MuonCandidates').at(0).phi ) "),
    ),
    tagFlags = cms.PSet(
        # Muon ID
        Calo = cms.string("isCaloMuon"),
        Glb = cms.string("isGlobalMuon"),
        GlbPT = cms.string("muonID('GlobalMuonPromptTight')"),
        TM = cms.string("isTrackerMuon"),
        TMA = cms.string("muonID('TrackerMuonArbitrated')"),
        PF = cms.string("isPFMuon()"),
        # Trigger
        IsoMu24 = cms.string("!triggerObjectMatchesByPath('HLT_IsoMu24_v*', 1, 0).empty()"),
        IsoMu17 = cms.string("!triggerObjectMatchesByPath('HLT_IsoMu17_v*', 1, 0).empty()"),
    ),
    pairVariables = cms.PSet(
        nTightJet = cms.InputTag("nTightJetCounter"),
        nTaggedJet = cms.InputTag("nTaggedJetCounter"),
        dz      = cms.string("daughter(0).vz - daughter(1).vz"),
        pt      = cms.string("pt"), # let's do some bump hunt in the T&P too
    ),
    pairFlags = cms.PSet(),
    isMC           = cms.bool(True),
    tagMatches       = cms.InputTag("tagMuonsMCMatch"),
    probeMatches     = cms.InputTag("probeMuonsMCMatch"),
    motherPdgId      = cms.vint32(22, 23),
    makeMCUnbiasTree       = cms.bool(False), 
    checkMotherInUnbiasEff = cms.bool(True),
    allProbes              = cms.InputTag("probeMuons"),
)

process.load("MuonAnalysis.TagAndProbe.muon.tag_probe_muon_extraIso_cfi")

process.tnpSimpleSequence = cms.Sequence(
    process.tagMuons   * process.tagMuonsMCMatch   + process.oneTag +
    process.probeMuons * process.probeMuonsMCMatch +
    process.tpPairs    + process.onePair +
    process.nverticesModule +
    process.muonDxyPVdzmin +
    process.muonSIP +
    process.ak5PFJets + process.ak5JetTracksAssociatorAtVertex + process.btagging +
    process.makePatAK5PFJets +
    process.tightJets * process.nTightJetCounter +
    process.taggedJets * process.nTaggedJetCounter +
    process.muonsPassingPF +
    process.probeMuonsIsoSequence +
    process.kt6PFJetsForIso * process.computeCorrectedIso + 
    process.tpTree
)

process.tagAndProbe = cms.Path( 
    process.fastFilter +
    process.mergedMuons *
    process.patMuonsWithTriggerSequence +
    process.tnpSimpleSequence
)

process.TFileService = cms.Service("TFileService", fileName = cms.string("tp_nJet.root"))
