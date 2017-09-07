import sys
import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

process = cms.Process("WTF")

options = VarParsing('analysis')
options.register(
    "inputName",
    "",
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Python file listing GENSIM inputs w/o ext"
    )
options.register(
    "outputName",
    "",
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Output root filename w/o ext"
    )
options.parseArguments()

if (options.inputName == ""):
    sys.exit("Need an input file!")

if (options.outputName == ""):
    sys.exit("Output file not specified!")

process.load("Configuration.StandardSequences.Services_cff")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(10000)
process.load('RecoJets.Configuration.GenJetParticles_cff')
process.load('RecoJets.JetProducers.ak4GenJets_cfi')
process.load('RecoMET.Configuration.GenMETParticles_cff')
process.load('RecoMET.METProducers.genMetTrue_cfi')

process.load(options.inputName)

process.ttSel = cms.EDAnalyzer("ttSelector",
        outputName = cms.string( options.outputName + ".root" ),
        decayType = cms.int32( 2 ),
        includeTau = cms.bool( True ),
        doKinSel = cms.bool( False ),
        kinSelection = cms.PSet(jetPtCut = cms.double( 30. ),
                                jetEtaCut = cms.double( 4.5 ),
                                lepPtCut  = cms.double( 20. ),
                                lepEtaCut = cms.double( 3.0 )
                            ), 
        )
#process.p = cms.Path(process.genParticlesForJets + process.ak4GenJets + process.genMETParticles + process.genMetTrue + process.ttSel)
process.p = cms.Path(process.ttSel)

                                        
