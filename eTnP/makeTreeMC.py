### Now in v2: 1 HLT path relative to 3 ID points

import FWCore.ParameterSet.Config as cms
import sys

from PhysicsTools.TagAndProbe.treeMakerOptionsMC_cfi import options

process = cms.Process("tnp")

process.pileupReweightingProducer = cms.EDProducer("PileupWeightProducer",
                                                   hardcodedWeights = cms.untracked.bool(True)
                                                   )

process.load('HLTrigger.HLTfilters.hltHighLevel_cfi')
process.hltHighLevel.throw = cms.bool(True)
process.hltHighLevel.HLTPaths = options['TnPPATHS']

###################################################################
##    ___            _           _      
##   |_ _|_ __   ___| |_   _  __| | ___ 
##    | || '_ \ / __| | | | |/ _` |/ _ \
##    | || | | | (__| | |_| | (_| |  __/
##   |___|_| |_|\___|_|\__,_|\__,_|\___|
##
###################################################################

process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.EventContent.EventContent_cff')

process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")
process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.GlobalTag.globaltag = options['GLOBALTAG']

process.load("Configuration.StandardSequences.MagneticField_cff")
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )

process.MessageLogger.cerr.threshold = ''
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

###################################################################
##   ____             _ ____ 
##  |  _ \ ___   ___ | / ___|  ___  _   _ _ __ ___ ___ 
##  | |_) / _ \ / _ \| \___ \ / _ \| | | | '__/ __/ _ \
##  |  __/ (_) | (_) | |___) | (_) | |_| | | | (_|  __/
##  |_|   \___/ \___/|_|____/ \___/ \__,_|_|  \___\___|
##  
###################################################################

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
                                #"/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/00000/00C4781D-6B08-E511-8A0A-0025905A6084.root",
                                #"/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/00000/02DE3B74-6C08-E511-ABE3-0025905A60D0.root",
                                #"/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/00000/08CEA172-6C08-E511-8097-0025905A6090.root",
                                #"/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/00000/0A13F3AC-5308-E511-8833-00266CFCE03C.root",
                                #"/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/00000/0AF07047-5D09-E511-829B-A0040420FE80.root",
                                #"/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/00000/0EA4C7BB-4908-E511-BD18-002590200938.root",
                                #"/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/00000/10CC7773-6C08-E511-A352-0025905A612A.root",
                                #"/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/00000/10E13BE4-5408-E511-BDC2-549F35AD8BA2.root",
                                #"/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/00000/147C50C2-6D08-E511-B5F2-0025905A60B6.root",
                                #"/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/00000/1680EE4B-5408-E511-B421-B8CA3A70A520.root",
                                ### /DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v2/MINIAODSIM
                                ### tableName: string tracked  = '/frozen/2015/50ns_5e33/v1.2/HLT/V2'
                            ),
                            )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( -1 ) )
    
###################################################################
##    ____      __ _____ _           _                   
##   / ___|___ / _| ____| | ___  ___| |_ _ __ ___  _ __  
##  | |  _/ __| |_|  _| | |/ _ \/ __| __| '__/ _ \| '_ \ 
##  | |_| \__ \  _| |___| |  __/ (__| |_| | | (_) | | | |
##   \____|___/_| |_____|_|\___|\___|\__|_|  \___/|_| |_|
##  
###################################################################

process.goodElectrons = cms.EDFilter("PATElectronRefSelector",
                                     src = cms.InputTag(options['ELECTRON_COLL']),
                                     cut = cms.string(options['ELECTRON_CUTS'])    
                                     )

###################################################################
##    _____ _           _                     ___    _ 
##   | ____| | ___  ___| |_ _ __ ___  _ __   |_ _|__| |
##   |  _| | |/ _ \/ __| __| '__/ _ \| '_ \   | |/ _` |
##   | |___| |  __/ (__| |_| | | (_) | | | |  | | (_| |
##   |_____|_|\___|\___|\__|_|  \___/|_| |_| |___\__,_|
##   
###################################################################

from PhysicsTools.SelectorUtils.tools.vid_id_tools import *

dataFormat = DataFormat.MiniAOD
if (options['useAOD']):
    dataFormat = DataFormat.AOD

switchOnVIDElectronIdProducer(process, dataFormat)

# define which IDs we want to produce
my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_PHYS14_PU20bx25_V2_cff',
                 'RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV51_cff']

for idmod in my_id_modules:
    setupAllVIDIdsInModule(process, idmod, setupVIDElectronSelection)

process.goodElectronsPROBEVeto = cms.EDProducer("PatElectronSelectorByValueMap",
                                                input     = cms.InputTag("goodElectrons"),
                                                cut       = cms.string(options['ELECTRON_CUTS']),
                                                selection = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-veto"),
                                                id_cut    = cms.bool(True)
                                                )

process.goodElectronsPROBELoose = process.goodElectronsPROBEVeto.clone()
process.goodElectronsPROBELoose.selection = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-loose")
process.goodElectronsPROBEMedium = process.goodElectronsPROBEVeto.clone()
process.goodElectronsPROBEMedium.selection = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-medium")
process.goodElectronsPROBETight = process.goodElectronsPROBEVeto.clone()
process.goodElectronsPROBETight.selection = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-tight")

process.goodElectronsTAGVeto = cms.EDProducer("PatElectronSelectorByValueMap",
                                              input     = cms.InputTag("goodElectrons"),
                                              cut       = cms.string(options['ELECTRON_TAG_CUTS']),
                                              selection = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-veto"),
                                              id_cut    = cms.bool(True)
                                              )

process.goodElectronsTAGLoose = process.goodElectronsTAGVeto.clone()
process.goodElectronsTAGLoose.selection = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-loose")
process.goodElectronsTAGMedium = process.goodElectronsTAGVeto.clone()
process.goodElectronsTAGMedium.selection = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-medium")
process.goodElectronsTAGTight = process.goodElectronsTAGVeto.clone()
process.goodElectronsTAGTight.selection = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-tight")

###################################################################
##    _____     _                         __  __       _       _     _             
##   |_   _| __(_) __ _  __ _  ___ _ __  |  \/  | __ _| |_ ___| |__ (_)_ __   __ _ 
##     | || '__| |/ _` |/ _` |/ _ \ '__| | |\/| |/ _` | __/ __| '_ \| | '_ \ / _` |
##     | || |  | | (_| | (_| |  __/ |    | |  | | (_| | || (__| | | | | | | | (_| |
##     |_||_|  |_|\__, |\__, |\___|_|    |_|  |_|\__,_|\__\___|_| |_|_|_| |_|\__, |
##                |___/ |___/                                                |___/ 
###################################################################

process.goodElectronsTagHLT = cms.EDProducer("PatElectronTriggerCandProducer",
                                             filterNames = options['TnPHLTTagFilters'],
                                             inputs      = cms.InputTag("goodElectronsTAGTight"),
                                             bits        = cms.InputTag('TriggerResults::HLT'),
                                             objects     = cms.InputTag('selectedPatTrigger'),
                                             dR          = cms.double(0.3),
                                             isAND       = cms.bool(True)
                                             )

process.goodElectronsLooseMeasureHLT = cms.EDProducer("PatElectronTriggerCandProducer",
                                                 filterNames = options['HLTFILTERTOMEASURE'],
                                                 inputs      = cms.InputTag("goodElectronsPROBELoose"),
                                                 bits        = cms.InputTag('TriggerResults::HLT'),
                                                 objects     = cms.InputTag('selectedPatTrigger'),
                                                 dR          = cms.double(0.3),
                                                 isAND       = cms.bool(True)
                                                 )

process.goodElectronsMediumMeasureHLT = process.goodElectronsLooseMeasureHLT.clone()
process.goodElectronsMediumMeasureHLT.inputs = cms.InputTag("goodElectronsPROBEMedium")

process.goodElectronsTightMeasureHLT = process.goodElectronsLooseMeasureHLT.clone()
process.goodElectronsTightMeasureHLT.inputs = cms.InputTag("goodElectronsPROBETight")

process.egmGsfElectronIDs.physicsObjectSrc = cms.InputTag(options['ELECTRON_COLL'])
process.ele_sequence = cms.Sequence(
    process.goodElectrons +
    process.egmGsfElectronIDSequence +
    process.goodElectronsPROBEVeto +
    process.goodElectronsPROBELoose +
    process.goodElectronsPROBEMedium +
    process.goodElectronsPROBETight +
    process.goodElectronsTAGVeto +
    process.goodElectronsTAGLoose +
    process.goodElectronsTAGMedium +
    process.goodElectronsTAGTight +
    process.goodElectronsTagHLT +
    process.goodElectronsLooseMeasureHLT +
    process.goodElectronsMediumMeasureHLT +
    process.goodElectronsTightMeasureHLT
    )

###################################################################
##    _____ ___   ____    ____       _          
##   |_   _( _ ) |  _ \  |  _ \ __ _(_)_ __ ___ 
##     | | / _ \/\ |_) | | |_) / _` | | '__/ __|
##     | || (_>  <  __/  |  __/ (_| | | |  \__ \
##     |_| \___/\/_|     |_|   \__,_|_|_|  |___/
##   
###################################################################

process.tagTightProbeLoose = cms.EDProducer("CandViewShallowCloneCombiner",
                                            decay = cms.string("goodElectronsTagHLT@+ goodElectronsPROBELoose@-"), 
                                            checkCharge = cms.bool(True),
                                            cut = cms.string("60. < mass < 120."),
                                           )

process.tagTightProbeMedium = process.tagTightProbeLoose.clone()
process.tagTightProbeMedium.decay = cms.string("goodElectronsTagHLT@+ goodElectronsPROBEMedium@-")

process.tagTightProbeTight = process.tagTightProbeLoose.clone()
process.tagTightProbeTight.decay = cms.string("goodElectronsTagHLT@+ goodElectronsPROBETight@-")

process.allTagsAndProbes = cms.Sequence(
    process.tagTightProbeLoose +
    process.tagTightProbeMedium +
    process.tagTightProbeTight
    )

###################################################################
##    __  __  ____   __  __       _       _               
##   |  \/  |/ ___| |  \/  | __ _| |_ ___| |__   ___  ___ 
##   | |\/| | |     | |\/| |/ _` | __/ __| '_ \ / _ \/ __|
##   | |  | | |___  | |  | | (_| | || (__| | | |  __/\__ \
##   |_|  |_|\____| |_|  |_|\__,_|\__\___|_| |_|\___||___/
##                                   
###################################################################

process.McMatchProbeLoose = cms.EDProducer("MCTruthDeltaRMatcherNew",
                                           matchPDGId = cms.vint32(11),
                                           src = cms.InputTag("goodElectronsPROBELoose"),
                                           distMin = cms.double(0.3),
                                           matched = cms.InputTag("prunedGenParticles"),
                                           checkCharge = cms.bool(True)
                                          )

process.McMatchProbeMedium = process.McMatchProbeLoose.clone()
process.McMatchProbeMedium.src = cms.InputTag("goodElectronsPROBEMedium")

process.McMatchProbeTight = process.McMatchProbeLoose.clone()
process.McMatchProbeTight.src = cms.InputTag("goodElectronsPROBETight")

process.McMatchTag = cms.EDProducer("MCTruthDeltaRMatcherNew",
                                    matchPDGId = cms.vint32(11),
                                    src = cms.InputTag("goodElectronsTAGTight"),
                                    distMin = cms.double(0.2),
                                    matched = cms.InputTag("prunedGenParticles"),
                                    checkCharge = cms.bool(True)
                                    )

process.mc_sequence = cms.Sequence()

if (options['MC_FLAG']):
    process.mc_sequence *= (process.McMatchProbeLoose + process.McMatchProbeMedium + process.McMatchProbeTight + process.McMatchTag)

##########################################################################
##    _____           _       _ ____            _            _   _  ____  
##   |_   _|_ _  __ _( )_ __ ( )  _ \ _ __ ___ | |__   ___  | \ | |/ ___| 
##     | |/ _` |/ _` |/| '_ \|/| |_) | '__/ _ \| '_ \ / _ \ |  \| | |  _  
##     | | (_| | (_| | | | | | |  __/| | | (_) | |_) |  __/ | |\  | |_| | 
##     |_|\__,_|\__, | |_| |_| |_|   |_|  \___/|_.__/ \___| |_| \_|\____| 
##              |___/                                                     
##                                                                        
##########################################################################
##    ____                      _     _           
##   |  _ \ ___ _   _ ___  __ _| |__ | | ___  ___ 
##   | |_) / _ \ | | / __|/ _` | '_ \| |/ _ \/ __|
##   |  _ <  __/ |_| \__ \ (_| | |_) | |  __/\__ \
##   |_| \_\___|\__,_|___/\__,_|_.__/|_|\___||___/
##
## I define some common variables for re-use later.
## This will save us repeating the same code for each efficiency category
#########################################################################

process.nJetCounterLoose = cms.EDProducer("CandCleanedMultiplicityCounter",
                                          pairs = cms.InputTag("tagTightProbeLoose"),
                                          objects = cms.InputTag("slimmedJets"),
                                          objectSelection = cms.string("pt() > 30."),
                                          minTagObjDR = cms.double(0.3),
                                          minProbeObjDR = cms.double(0.3),
                                         )

process.nJetCounterMedium = process.nJetCounterLoose.clone()
process.nJetCounterMedium.pairs = cms.InputTag("tagTightProbeMedium")

process.nJetCounterTight = process.nJetCounterLoose.clone()
process.nJetCounterTight.pairs = cms.InputTag("tagTightProbeTight")

ZVariablesLoose = cms.PSet(
    eta = cms.string("eta"),
    phi = cms.string("phi"),
    abseta = cms.string("abs(eta)"),
    pt  = cms.string("pt"),
    mass  = cms.string("mass"),
    nJet = cms.InputTag("nJetCounterLoose"),
    weight = cms.InputTag("pileupWeights")
    )

ZVariablesMedium = ZVariablesLoose.clone()
ZVariablesMedium.nJet = cms.InputTag("nJetCounterMedium")

ZVariablesTight = ZVariablesLoose.clone()
ZVariablesTight.nJet = cms.InputTag("nJetCounterTight")

ProbeVariables = cms.PSet(
    probe_eta    = cms.string("eta"),
    probe_phi    = cms.string("phi"),
    probe_abseta = cms.string("abs(eta)"),
    probe_pt     = cms.string("pt"),
    probe_et     = cms.string("et"),
    probe_e      = cms.string("energy"),
    probe_q      = cms.string("charge"),
    #probe_Ele_trackiso = cms.string("dr03TkSumPt"),
    #probe_Ele_reltrackiso = cms.string("dr03TkSumPt/pt"),
    ## super cluster quantities
    probe_sc_energy = cms.string("superCluster.energy"),
    probe_sc_et     = cms.string("superCluster.energy*sin(superClusterPosition.theta)"),    
    probe_sc_eta    = cms.string("superCluster.eta"),
    probe_sc_phi    = cms.string("superCluster.phi"),
    probe_sc_abseta = cms.string("abs(superCluster.eta)"),

    ## id based
    probe_Ele_dEtaIn        = cms.string("deltaEtaSuperClusterTrackAtVtx"),
    probe_Ele_dPhiIn        = cms.string("deltaPhiSuperClusterTrackAtVtx"),
    probe_Ele_sigmaIEtaIEta = cms.string("sigmaIetaIeta"),
    probe_Ele_hoe           = cms.string("hadronicOverEm"),
    probe_Ele_ooemoop       = cms.string("(1.0/ecalEnergy - eSuperClusterOverP/ecalEnergy)"),
    #probe_Ele_mHits         = cms.string("gsfTrack.trackerExpectedHitsInner.numberOfHits")
)

TagVariables = cms.PSet(
    eta    = cms.string("eta"),
    phi    = cms.string("phi"),
    abseta = cms.string("abs(eta)"),
    pt     = cms.string("pt"),
    et     = cms.string("et"),
    e      = cms.string("energy"),
    q      = cms.string("charge"),
    
    ## super cluster quantities
    sc_energy = cms.string("superCluster.energy"),
    sc_et     = cms.string("superCluster.energy*sin(superClusterPosition.theta)"),    
    sc_eta    = cms.string("superCluster.eta"),
    sc_phi    = cms.string("superCluster.phi"),
    sc_abseta = cms.string("abs(superCluster.eta)"),
)

CommonStuffForGsfElectronProbeLoose = cms.PSet(
    variables = cms.PSet(ProbeVariables),
    ignoreExceptions =  cms.bool (True),
    addRunLumiInfo   =  cms.bool (True),
    addEventVariablesInfo   =  cms.bool(True),
    vertexCollection = cms.InputTag("offlineSlimmedPrimaryVertices"),
    beamSpot = cms.InputTag("offlineBeamSpot"),
    pairVariables =  cms.PSet(ZVariablesLoose),
    pairFlags     =  cms.PSet(
        mass60to120 = cms.string("60 < mass < 120")
        ),
    tagVariables   =  cms.PSet(TagVariables),
    tagFlags       =  cms.PSet(),
    tagProbePairs = cms.InputTag("tagTightProbeLoose"),
    arbitration   = cms.string("None"),
    flags         = cms.PSet( passingHLT = cms.InputTag("goodElectronsLooseMeasureHLT") ),    
    allProbes     = cms.InputTag("goodElectronsPROBELoose"),
    PUWeightSrc   = cms.InputTag("pileupReweightingProducer", "pileupWeights") 
    )

CommonStuffForGsfElectronProbeMedium = CommonStuffForGsfElectronProbeLoose.clone()
CommonStuffForGsfElectronProbeMedium.pairVariables = cms.PSet(ZVariablesMedium)
CommonStuffForGsfElectronProbeMedium.tagProbePairs = cms.InputTag("tagTightProbeMedium")
CommonStuffForGsfElectronProbeMedium.flags = cms.PSet( passingHLT = cms.InputTag("goodElectronsMediumMeasureHLT") )
CommonStuffForGsfElectronProbeMedium.allProbes = cms.InputTag("goodElectronsPROBEMedium")

CommonStuffForGsfElectronProbeTight = CommonStuffForGsfElectronProbeLoose.clone()
CommonStuffForGsfElectronProbeTight.pairVariables = cms.PSet(ZVariablesTight)
CommonStuffForGsfElectronProbeTight.tagProbePairs = cms.InputTag("tagTightProbeTight")
CommonStuffForGsfElectronProbeTight.flags = cms.PSet( passingHLT = cms.InputTag("goodElectronsTightMeasureHLT") )
CommonStuffForGsfElectronProbeTight.allProbes = cms.InputTag("goodElectronsPROBETight")

if options['MC_FLAG']:
    mcTruthCommonStuff = cms.PSet(
        isMC = cms.bool(True),
        tagMatches = cms.InputTag("McMatchTag"),
        motherPdgId = cms.vint32(22,23),
        #motherPdgId = cms.vint32(443), # JPsi
        #motherPdgId = cms.vint32(553), # Yupsilon
        makeMCUnbiasTree = cms.bool(False),
        checkMotherInUnbiasEff = cms.bool(False),
        mcVariables = cms.PSet(
            probe_eta = cms.string("eta"),
            probe_abseta = cms.string("abs(eta)"),
            probe_et  = cms.string("et"),
            probe_e  = cms.string("energy"),
            ),
        mcFlags     =  cms.PSet(
            probe_flag = cms.string("pt>0")
            ),      
        )
else:
    mcTruthCommonStuff = cms.PSet(
        isMC = cms.bool(False)
        )
    
##########################################################################
##   ____      __       __    ___                 ___    _ 
##  / ___|___ / _|      \ \  |_ _|___  ___       |_ _|__| |
## | |  _/ __| |_   _____\ \  | |/ __|/ _ \       | |/ _` |
## | |_| \__ \  _| |_____/ /  | |\__ \ (_) |  _   | | (_| |
##  \____|___/_|        /_/  |___|___/\___/  ( ) |___\__,_|
##                                           |/            
##########################################################################

process.GsfElectronHLTLoose = cms.EDAnalyzer("TagProbeFitTreeProducer",
                                             CommonStuffForGsfElectronProbeLoose, mcTruthCommonStuff,
                                            )

process.GsfElectronHLTMedium = cms.EDAnalyzer("TagProbeFitTreeProducer",
                                              CommonStuffForGsfElectronProbeMedium, mcTruthCommonStuff,
                                             )

process.GsfElectronHLTTight = cms.EDAnalyzer("TagProbeFitTreeProducer",
                                             CommonStuffForGsfElectronProbeTight, mcTruthCommonStuff,
                                            )

if (options['MC_FLAG']):
    process.GsfElectronHLTLoose.probeMatches  = cms.InputTag("McMatchProbeLoose")
    process.GsfElectronHLTMedium.probeMatches  = cms.InputTag("McMatchProbeMedium")
    process.GsfElectronHLTTight.probeMatches  = cms.InputTag("McMatchProbeTight")

process.tree_sequence = cms.Sequence(
    process.GsfElectronHLTLoose +
    process.GsfElectronHLTMedium +
    process.GsfElectronHLTTight
    )

##########################################################################
##    ____       _   _     
##   |  _ \ __ _| |_| |__  
##   | |_) / _` | __| '_ \ 
##   |  __/ (_| | |_| | | |
##   |_|   \__,_|\__|_| |_|
##
##########################################################################

process.out = cms.OutputModule("PoolOutputModule", 
                               fileName = cms.untracked.string(options['OUTPUTEDMFILENAME']),
                               SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring("p"))
                               )
process.outpath = cms.EndPath(process.out)
if (not options['DEBUG']):
    process.outpath.remove(process.out)

process.p = cms.Path(
    process.hltHighLevel +
    process.ele_sequence + 
    process.allTagsAndProbes +
    process.pileupReweightingProducer +
    process.mc_sequence +
    process.nJetCounterLoose +
    process.nJetCounterMedium +
    process.nJetCounterTight +
    process.tree_sequence
    )

process.TFileService = cms.Service(
    "TFileService", fileName = cms.string(options['OUTPUT_FILE_NAME'])
    )
