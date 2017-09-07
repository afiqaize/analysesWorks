import sys
import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

process = cms.Process("LOLK")

options = VarParsing('analysis')
options.register(
    "outputName",
    "",
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Output root filename w/o ext"
    )
options.parseArguments()

if (options.outputName == ""):
    sys.exit("Output file not specified!")

process.load("Configuration.StandardSequences.Services_cff")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(100000)
process.load('RecoJets.Configuration.GenJetParticles_cff')
process.load('RecoJets.JetProducers.ak4GenJets_cfi')
process.load('RecoMET.Configuration.GenMETParticles_cff')
process.load('RecoMET.METProducers.genMetTrue_cfi')

process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32(-1)
)

readFiles = cms.untracked.vstring()
readFiles.extend( [
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00001.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00002.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00003.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00004.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00005.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00006.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00007.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00008.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00009.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00010.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00011.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00012.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00013.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00014.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00015.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00016.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00017.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00018.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00019.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00020.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00021.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00022.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00023.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00024.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00025.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00026.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00027.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00028.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00029.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00030.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00031.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00032.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00033.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00034.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00035.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00036.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00037.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00038.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00039.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00040.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00041.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00042.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00043.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00044.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00045.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00046.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00047.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00048.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00049.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00050.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00051.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00052.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00053.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00054.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00055.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00056.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00057.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00058.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00059.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00060.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00061.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00062.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00063.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00064.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00065.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00066.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00067.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00068.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00069.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00070.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00071.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00072.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00073.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00074.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00075.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00076.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00077.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00078.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00079.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00080.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00081.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00082.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00083.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00084.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00085.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00086.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00087.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00088.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00089.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00090.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00091.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00092.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00093.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00094.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00095.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00096.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00097.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00098.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00099.root',
    'file:/nfs/dust/cms/user/agrohsje/samples/cms/validation/powheg/evgen/ttbar_nnpdf30_SMspin_13TeV_dilepton_CUETP8M2T4/TTbar_TuneCUETP8M2T4_13TeV_NNPDF30_Powheg_Pythia8__GENSIM__00100.root'
] )

# Input source
process.source = cms.Source("PoolSource",
                            fileNames = readFiles
)

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
process.p = cms.Path(process.genParticlesForJets + process.ak4GenJets + process.genMETParticles + process.genMetTrue + process.ttSel)

                                        
