# Oct 05: Changed to match the definition on data03 (RunB config)
# Oct 08: Revert back to IsoMu17_v because no er_xtrig path in MC
# Oct 13: Rewrote to a much simpler, no-fluff version

import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

process.load('FWCore.MessageService.MessageLogger_cfi')
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.source = cms.Source("PoolSource", 
    fileNames = cms.untracked.vstring(
        '/store/mc/Fall11/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/PU_S6_START44_V9B-v1/0000/002612AC-463D-E111-802A-E0CB4E19F9BC.root',
        '/store/mc/Fall11/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/PU_S6_START44_V9B-v1/0000/004F0141-A43C-E111-AE80-20CF305616E0.root',
        '/store/mc/Fall11/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/PU_S6_START44_V9B-v1/0000/00536037-AF3C-E111-A6EA-20CF300E9ECB.root',
        #'/store/mc/Fall11/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/PU_S6_START44_V9B-v1/0000/005F7E58-AF3C-E111-8694-E0CB4E19F96D.root',
        #'/store/mc/Fall11/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/PU_S6_START44_V9B-v1/0000/0067C5E1-D63C-E111-B2BD-90E6BA442F23.root',
    ),
)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )    

process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")
process.GlobalTag.globaltag = cms.string('START44_V9B::All')

## ==== Fast Filters ====
process.goodVertexFilter = cms.EDFilter("VertexSelector",
    src = cms.InputTag("offlinePrimaryVertices"),
    cut = cms.string("!isFake && ndof > 4 && abs(z) <= 25 && position.Rho <= 2"),
    filter = cms.bool(True),
)
process.noScraping = cms.EDFilter("FilterOutScraping",
    applyfilter = cms.untracked.bool(True),
    debugOn = cms.untracked.bool(False), ## Or 'True' to get some per-event info
    numtrack = cms.untracked.uint32(10),
    thresh = cms.untracked.double(0.25)
)
process.fastFilter = cms.Sequence(process.goodVertexFilter + process.noScraping)

## Muons
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
    muonsCut     = cms.string("pt > 15 && track.isNonnull"),
    caloMuonsCut = cms.string("pt > 15"),
    tracksCut    = cms.string("pt > 15"),
)

## ==== Trigger matching
process.load("MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff")
## with some customization
process.muonMatchHLTL2.maxDeltaR = 0.3 # Zoltan tuning - it was 0.5
process.muonMatchHLTL3.maxDeltaR = 0.1
from MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff import *
changeRecoMuonInput(process, "mergedMuons")
changeTriggerProcessName(process, "*") # auto-guess

process.load("MuonAnalysis.TagAndProbe.common_modules_cff")

# cuts are to be synchronized with the s-channel group (refer to 22 Sept 2014 mail)
process.tagMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("patMuonsWithTrigger"),
    cut = cms.string("pt > 20 && abs(eta) < 2.1 && isGlobalMuon && isTrackerMuon" # kinematics and muon type
                     + " && numberOfMatches() > 1 && muonID('GlobalMuonPromptTight') > 0" # ID cuts
                     + " && innerTrack.numberOfValidHits > 10 && innerTrack.hitPattern.pixelLayersWithMeasurement() >=1" # track-related cuts
                     + " && (pfIsolationR03().sumChargedHadronPt + max(pfIsolationR03().sumNeutralHadronEt + pfIsolationR03().sumPhotonEt - pfIsolationR03().sumPUPt/2, 0.0))/pt < 0.1" # combined isolation
                     + " && !triggerObjectMatchesByPath('HLT_IsoMu17_v*', 1, 0).empty()" # IsoMu17 trigger matching
                    ),
)

process.oneTag  = cms.EDFilter("CandViewCountFilter", src = cms.InputTag("tagMuons"), minNumber = cms.uint32(1))

# like tag without trigger matching
process.probeMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("patMuonsWithTrigger"),
    cut = cms.string("pt > 20 && abs(eta) < 2.1 && isGlobalMuon && isTrackerMuon" # kinematics and muon type
                     + " && numberOfMatches() > 1 && muonID('GlobalMuonPromptTight') > 0" # ID cuts
                     + " && innerTrack.numberOfValidHits > 10 && innerTrack.hitPattern.pixelLayersWithMeasurement() >=1" # track-related cuts
                     + " && (pfIsolationR03().sumChargedHadronPt + max(pfIsolationR03().sumNeutralHadronEt + pfIsolationR03().sumPhotonEt - pfIsolationR03().sumPUPt/2, 0.0))/pt < 0.1" # combined isolation
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
        l2dr = cms.string("? triggerObjectMatchesByCollection('hltL2MuonCandidates').empty() ? 999 : "+
                          " deltaR( eta, phi, " +
                          " triggerObjectMatchesByCollection('hltL2MuonCandidates').at(0).eta, "+
                          " triggerObjectMatchesByCollection('hltL2MuonCandidates').at(0).phi ) "),
        # L3
        l3pt = cms.string("? triggerObjectMatchesByCollection('hltL3MuonCandidates').empty() ? 0 : triggerObjectMatchesByCollection('hltL3MuonCandidates').at(0).pt"),
        l3dr = cms.string("? triggerObjectMatchesByCollection('hltL3MuonCandidates').empty() ? 999 : "+
                          " deltaR( eta, phi, " +
                          " triggerObjectMatchesByCollection('hltL3MuonCandidates').at(0).eta, "+
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
        IsoMu17 = cms.string("!triggerObjectMatchesByPath('HLT_IsoMu17_v*',1,0).empty()"),
        IsoMu17_leg = cms.string("!triggerObjectMatchesByCollection('hltL2MuonCandidates').empty() && !triggerObjectMatchesByCollection('hltL3MuonCandidates').empty()" # same as trigger part of tag definition
                                + " && !triggerObjectMatchesByFilter('hltMuEta2p1IsoCenJetL3withL2QIsoFiltered17').empty()"
                               ),
    ),
    tagVariables =  cms.PSet(
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
        l2dr = cms.string("? triggerObjectMatchesByCollection('hltL2MuonCandidates').empty() ? 999 : "+
                          " deltaR( eta, phi, " +
                          " triggerObjectMatchesByCollection('hltL2MuonCandidates').at(0).eta, "+
                          " triggerObjectMatchesByCollection('hltL2MuonCandidates').at(0).phi ) "),
        # L3
        l3pt = cms.string("? triggerObjectMatchesByCollection('hltL3MuonCandidates').empty() ? 0 : triggerObjectMatchesByCollection('hltL3MuonCandidates').at(0).pt"),
        l3dr = cms.string("? triggerObjectMatchesByCollection('hltL3MuonCandidates').empty() ? 999 : "+
                          " deltaR( eta, phi, " +
                          " triggerObjectMatchesByCollection('hltL3MuonCandidates').at(0).eta, "+
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
        IsoMu17 = cms.string("!triggerObjectMatchesByPath('HLT_IsoMu17_v*',1,0).empty()"),
        IsoMu17_leg = cms.string("!triggerObjectMatchesByCollection('hltL2MuonCandidates').empty() && !triggerObjectMatchesByCollection('hltL3MuonCandidates').empty()" # same as trigger part of tag definition
                                + " && !triggerObjectMatchesByFilter('hltMuEta2p1IsoCenJetL3withL2QIsoFiltered17').empty()"
                               ),
    ),
    pairVariables = cms.PSet(
        nJets15 = cms.InputTag("njets15Module"),
        nJets30 = cms.InputTag("njets30Module"),
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


process.load('RecoJets.Configuration.RecoPFJets_cff')
##-------------------- Turn-on the FastJet density calculation -----------------------
process.kt6PFJets.doRhoFastjet = True
##-------------------- FastJet density calculation for Iso -----------------------
process.kt6PFJetsForIso = process.kt6PFJets.clone( Rho_EtaMax = cms.double(2.5), Ghost_EtaMax = cms.double(2.5) )

process.load("MuonAnalysis.TagAndProbe.muon.tag_probe_muon_extraIso_cfi")

process.tnpSimpleSequence = cms.Sequence(
    process.tagMuons   * process.tagMuonsMCMatch   +
    process.probeMuons * process.probeMuonsMCMatch +
    process.tpPairs    +
    process.nverticesModule +
    process.muonDxyPVdzmin +
    process.muonSIP +
    process.offlinePrimaryVerticesDA100um * process.nverticesDAModule +
    process.njets15Module +
    process.njets30Module +
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

## Tracking

## Then make another collection for standalone muons, using standalone track to define the 4-momentum
process.muonsSta = cms.EDProducer("RedefineMuonP4FromTrack",
    src   = cms.InputTag("muons"),
    track = cms.string("outer"),
)
## Match to trigger, to measure the efficiency of HLT tracking
from PhysicsTools.PatAlgos.tools.helpers import *
process.patMuonsWithTriggerSequenceSta = cloneProcessingSnippet(process, process.patMuonsWithTriggerSequence, "Sta")
process.muonMatchHLTL2Sta.maxDeltaR = 0.5
process.muonMatchHLTL3Sta.maxDeltaR = 0.5
massSearchReplaceAnyInputTag(process.patMuonsWithTriggerSequenceSta, "mergedMuons", "muonsSta")

## Define probes and T&P pairs
process.probeMuonsSta = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("patMuonsWithTriggerSta"),
    cut = cms.string("outerTrack.isNonnull"), # no real cut now
)
process.probeMuonsMCMatchSta = process.tagMuonsMCMatch.clone(src = "probeMuonsSta")

process.tpPairsSta = process.tpPairs.clone(decay = "tagMuons@+ probeMuonsSta@-", cut = '40 < mass < 140')

process.staToTkMatch.maxDeltaR     = 0.3
process.staToTkMatch.maxDeltaPtRel = 2.
process.staToTkMatchNoZ.maxDeltaR     = 0.3
process.staToTkMatchNoZ.maxDeltaPtRel = 2.

process.tpTreeSta = process.tpTree.clone(
    tagProbePairs = "tpPairsSta",
    variables = cms.PSet(
        # Basics
        pt = cms.string("pt"),
        p = cms.string("p"),
        eta = cms.string("eta"),
        phi = cms.string("phi"),
        abseta = cms.string("abs(eta)"),
        charge = cms.string("charge"),
        ## track matching variables
        tk_deltaR     = cms.InputTag("staToTkMatch", "deltaR"),
        tk_deltaEta   = cms.InputTag("staToTkMatch", "deltaEta"),
        tk_deltaR_NoZ   = cms.InputTag("staToTkMatchNoZ", "deltaR"),
        tk_deltaEta_NoZ = cms.InputTag("staToTkMatchNoZ", "deltaEta"),
    ),
    flags = cms.PSet(
        outerValidHits = cms.string("outerTrack.numberOfValidHits > 0"),
        TM  = cms.string("isTrackerMuon"),
        Glb = cms.string("isGlobalMuon"),
    ),
    allProbes     = "probeMuonsSta",
    probeMatches  = "probeMuonsMCMatchSta",
)
process.tpTreeSta.pairVariables.nJets15 = "njets15ModuleSta"
process.tpTreeSta.pairVariables.nJets30 = "njets30ModuleSta"
process.njets15ModuleSta = process.njets15Module.clone(pairs = "tpPairsSta")
process.njets30ModuleSta = process.njets30Module.clone(pairs = "tpPairsSta")

process.tnpSimpleSequenceSta = cms.Sequence(
    process.tagMuons   * process.tagMuonsMCMatch   +
    process.probeMuonsSta * process.probeMuonsMCMatchSta +
    process.tpPairsSta      +
    process.nverticesModule +
    process.offlinePrimaryVerticesDA100um * process.nverticesDAModule +
    process.staToTkMatchSequenceZ +
    process.njets15ModuleSta +
    process.njets30ModuleSta +
    process.tpTreeSta
)

process.tagAndProbeSta = cms.Path( 
    process.fastFilter +
    process.muonsSta *
    process.patMuonsWithTriggerSequenceSta +
    process.tnpSimpleSequenceSta
)

process.TFileService = cms.Service("TFileService", fileName = cms.string("tnpZ_simple_MC.root"))
