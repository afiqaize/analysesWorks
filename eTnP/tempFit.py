### The template fitter for single electron TnP
### Oct 16 First used with run15D_act02, need the template files
### Jan 02: Fitter now outputs all variables in a single root file

import sys
import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing
import PhysicsTools.TagAndProbe.fitAll_pp15bx25 as common

process = cms.Process("TagProbe")
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.destinations = ['cout', 'cerr']

################################################
### Initialization
################################################

options = VarParsing('analysis')
options.register(
    "isMC",
    True,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Compute efficiency for MC"
    )
options.register(
    "inputName",
    "TnPTree.root",
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Input filename"
    )

options.register(
    "outputPrefix",
    "out",
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Output filename prefix"
    )
options.parseArguments()

if (options.inputName = ""):
    sys.exit("Need an input file!")
else:
    InputFileName = "file:" + options.inputName

################################################
#specifies the binning of parameters
EfficiencyBinsEt = cms.PSet(## conditions to be satisfied by all probes, weirdly causing large errors
                            #pair_mass70to110 = cms.vstring("true"),
                            ## variables to be checked as a function of
                            probe_et = cms.vdouble( 25., 30., 35., 40., 45., 50., 65., 90., 135., 190., 250. ),
                            #probe_eta = cms.vdouble( -2.5, 2.5 ),
                           )

EfficiencyBinsEta = cms.PSet(## conditions to be satisfied by all probes, weirdly causing large errors
                             #pair_mass70to110 = cms.vstring("true"),
                             ## variables to be checked as a function of
                             #probe_et = cms.vdouble( 25., 250. ),
                             probe_eta = cms.vdouble( -2.5, -2.1, -1.6, -1.4, -0.7, 0., 0.7, 1.4, 1.6, 2.1, 2.5 ),
                            )

EfficiencyBinsPhi = cms.PSet(## conditions to be satisfied by all probes, weirdly causing large errors
                             #pair_mass70to110 = cms.vstring("true"),
                             ## variables to be checked as a function of
                             #probe_et = cms.vdouble( 25., 250. ),
                             probe_phi = cms.vdouble( -3.142, -2.514, -1.885, -1.257, -0.628, 0., 0.628, 1.257, 1.885, 2.514, 3.142 ),
                            )

EfficiencyBinsnJet = cms.PSet(## conditions to be satisfied by all probes, weirdly causing large errors
                              #pair_mass70to110 = cms.vstring("true"),
                              ## variables to be checked as a function of
                              #probe_et = cms.vdouble( 25., 250. ),
                              pair_nJet = cms.vdouble( -0.5, 0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5 ),
                             )

EfficiencyBinsnPV = cms.PSet(## conditions to be satisfied by all probes, weirdly causing large errors
                             #pair_mass70to110 = cms.vstring("true"),
                             ## variables to be checked as a function of
                             #probe_et = cms.vdouble( 25., 250. ),
                             event_nPV = cms.vdouble( 0., 2., 4., 6., 8., 10., 13., 17., 21., 25., 40. ),
                            )

EfficiencyBins2d = cms.PSet(## conditions to be satisfied by all probes, weirdly causing large errors
                            #pair_mass60to120 = cms.vstring("true"),
                            ## variables to be checked as a function of
                            probe_et = cms.vdouble( 25., 30., 35., 40., 45., 50., 65., 90., 135., 190., 250. ),
                            probe_eta = cms.vdouble( -2.5, -2.1, -1.6, -1.4, -0.7, 0., 0.7, 1.4, 1.6, 2.1, 2.5 ),
                           )

EfficiencyBinningSpecificationEt = cms.PSet(
    #specifies the binning of parameters
    BinnedVariables = cms.PSet(EfficiencyBinsEt),
    # Map the PDF to bins: first default, then the map
    BinToPDFmap = cms.vstring(
        "pdf_25p0To250p0_m2p5To2p5",

        "*et_bin0*", "pdf_25p0To30p0_m2p5To2p5",
        "*et_bin1*", "pdf_30p0To35p0_m2p5To2p5",
        "*et_bin2*", "pdf_35p0To40p0_m2p5To2p5",
        "*et_bin3*", "pdf_40p0To45p0_m2p5To2p5",
        "*et_bin4*", "pdf_45p0To50p0_m2p5To2p5",
        "*et_bin5*", "pdf_50p0To65p0_m2p5To2p5",
        "*et_bin6*", "pdf_65p0To90p0_m2p5To2p5",
        "*et_bin7*", "pdf_90p0To135p0_m2p5To2p5",
        "*et_bin8*", "pdf_135p0To190p0_m2p5To2p5",
        "*et_bin9*", "pdf_190p0To250p0_m2p5To2p5",
        )
)

if (not options.isMC):
    setattr(EfficiencyBinningSpecificationEt, "UnbinnedVariables", cms.vstring("mass"))
else:
    setattr(EfficiencyBinningSpecificationEt, "UnbinnedVariables", cms.vstring("mass", "puWgt"))

EfficiencyBinningSpecificationEta = EfficiencyBinningSpecificationEt.clone()
EfficiencyBinningSpecificationEta.BinnedVariables = cms.PSet(EfficiencyBinsEta)
EfficiencyBinningSpecificationEta.BinToPDFmap = cms.vstring(
        "pdf_25p0To250p0_m2p5To2p5",

        "*eta_bin0*", "pdf_25p0To250p0_m2p5Tom2p1",
        "*eta_bin1*", "pdf_25p0To250p0_m2p1Tom1p6",
        "*eta_bin2*", "pdf_25p0To250p0_m1p6Tom1p4",
        "*eta_bin3*", "pdf_25p0To250p0_m1p4Tom0p7",
        "*eta_bin4*", "pdf_25p0To250p0_m0p7To0p0",
        "*eta_bin5*", "pdf_25p0To250p0_0p0To0p7",
        "*eta_bin6*", "pdf_25p0To250p0_0p7To1p4",
        "*eta_bin7*", "pdf_25p0To250p0_1p4To1p6",
        "*eta_bin8*", "pdf_25p0To250p0_1p6To2p1",
        "*eta_bin9*", "pdf_25p0To250p0_2p1To2p5",
)

EfficiencyBinningSpecificationPhi = EfficiencyBinningSpecificationEt.clone()
EfficiencyBinningSpecificationPhi.BinnedVariables = cms.PSet(EfficiencyBinsPhi)
EfficiencyBinningSpecificationPhi.BinToPDFmap = cms.vstring("pdf_25p0To250p0_m2p5To2p5")

EfficiencyBinningSpecificationnJet = EfficiencyBinningSpecificationPhi.clone()
EfficiencyBinningSpecificationnJet.BinnedVariables = cms.PSet(EfficiencyBinsnJet)

EfficiencyBinningSpecificationnPV = EfficiencyBinningSpecificationPhi.clone()
EfficiencyBinningSpecificationnPV.BinnedVariables = cms.PSet(EfficiencyBinsnPV)

EfficiencyBinningSpecification2d = EfficiencyBinningSpecificationEt.clone()
EfficiencyBinningSpecification2d.BinnedVariables = cms.PSet(EfficiencyBins2d)
EfficiencyBinningSpecification2d.BinToPDFmap = cms.vstring(
        "pdf_25p0To250p0_m2p5To2p5",

        "*et_bin0*eta_bin0*", "pdf_25p0To30p0_m2p5Tom2p1",
        "*et_bin0*eta_bin1*", "pdf_25p0To30p0_m2p1Tom1p6",
        "*et_bin0*eta_bin2*", "pdf_25p0To30p0_m1p6Tom1p4",
        "*et_bin0*eta_bin3*", "pdf_25p0To30p0_m1p4Tom0p7",
        "*et_bin0*eta_bin4*", "pdf_25p0To30p0_m0p7To0p0",
        "*et_bin0*eta_bin5*", "pdf_25p0To30p0_0p0To0p7",
        "*et_bin0*eta_bin6*", "pdf_25p0To30p0_0p7To1p4",
        "*et_bin0*eta_bin7*", "pdf_25p0To30p0_1p4To1p6",
        "*et_bin0*eta_bin8*", "pdf_25p0To30p0_1p6To2p1",
        "*et_bin0*eta_bin9*", "pdf_25p0To30p0_2p1To2p5",

        "*et_bin1*eta_bin0*", "pdf_30p0To35p0_m2p5Tom2p1",
        "*et_bin1*eta_bin1*", "pdf_30p0To35p0_m2p1Tom1p6",
        "*et_bin1*eta_bin2*", "pdf_30p0To35p0_m1p6Tom1p4",
        "*et_bin1*eta_bin3*", "pdf_30p0To35p0_m1p4Tom0p7",
        "*et_bin1*eta_bin4*", "pdf_30p0To35p0_m0p7To0p0",
        "*et_bin1*eta_bin5*", "pdf_30p0To35p0_0p0To0p7",
        "*et_bin1*eta_bin6*", "pdf_30p0To35p0_0p7To1p4",
        "*et_bin1*eta_bin7*", "pdf_30p0To35p0_1p4To1p6",
        "*et_bin1*eta_bin8*", "pdf_30p0To35p0_1p6To2p1",
        "*et_bin1*eta_bin9*", "pdf_30p0To35p0_2p1To2p5",

        "*et_bin2*eta_bin0*", "pdf_35p0To40p0_m2p5Tom2p1",
        "*et_bin2*eta_bin1*", "pdf_35p0To40p0_m2p1Tom1p6",
        "*et_bin2*eta_bin2*", "pdf_35p0To40p0_m1p6Tom1p4",
        "*et_bin2*eta_bin3*", "pdf_35p0To40p0_m1p4Tom0p7",
        "*et_bin2*eta_bin4*", "pdf_35p0To40p0_m0p7To0p0",
        "*et_bin2*eta_bin5*", "pdf_35p0To40p0_0p0To0p7",
        "*et_bin2*eta_bin6*", "pdf_35p0To40p0_0p7To1p4",
        "*et_bin2*eta_bin7*", "pdf_35p0To40p0_1p4To1p6",
        "*et_bin2*eta_bin8*", "pdf_35p0To40p0_1p6To2p1",
        "*et_bin2*eta_bin9*", "pdf_35p0To40p0_2p1To2p5",

        "*et_bin3*eta_bin0*", "pdf_40p0To45p0_m2p5Tom2p1",
        "*et_bin3*eta_bin1*", "pdf_40p0To45p0_m2p1Tom1p6",
        "*et_bin3*eta_bin2*", "pdf_40p0To45p0_m1p6Tom1p4",
        "*et_bin3*eta_bin3*", "pdf_40p0To45p0_m1p4Tom0p7",
        "*et_bin3*eta_bin4*", "pdf_40p0To45p0_m0p7To0p0",
        "*et_bin3*eta_bin5*", "pdf_40p0To45p0_0p0To0p7",
        "*et_bin3*eta_bin6*", "pdf_40p0To45p0_0p7To1p4",
        "*et_bin3*eta_bin7*", "pdf_40p0To45p0_1p4To1p6",
        "*et_bin3*eta_bin8*", "pdf_40p0To45p0_1p6To2p1",
        "*et_bin3*eta_bin9*", "pdf_40p0To45p0_2p1To2p5",

        "*et_bin4*eta_bin0*", "pdf_45p0To50p0_m2p5Tom2p1",
        "*et_bin4*eta_bin1*", "pdf_45p0To50p0_m2p1Tom1p6",
        "*et_bin4*eta_bin2*", "pdf_45p0To50p0_m1p6Tom1p4",
        "*et_bin4*eta_bin3*", "pdf_45p0To50p0_m1p4Tom0p7",
        "*et_bin4*eta_bin4*", "pdf_45p0To50p0_m0p7To0p0",
        "*et_bin4*eta_bin5*", "pdf_45p0To50p0_0p0To0p7",
        "*et_bin4*eta_bin6*", "pdf_45p0To50p0_0p7To1p4",
        "*et_bin4*eta_bin7*", "pdf_45p0To50p0_1p4To1p6",
        "*et_bin4*eta_bin8*", "pdf_45p0To50p0_1p6To2p1",
        "*et_bin4*eta_bin9*", "pdf_45p0To50p0_2p1To2p5",

        "*et_bin5*eta_bin0*", "pdf_50p0To65p0_m2p5Tom2p1",
        "*et_bin5*eta_bin1*", "pdf_50p0To65p0_m2p1Tom1p6",
        "*et_bin5*eta_bin2*", "pdf_50p0To65p0_m1p6Tom1p4",
        "*et_bin5*eta_bin3*", "pdf_50p0To65p0_m1p4Tom0p7",
        "*et_bin5*eta_bin4*", "pdf_50p0To65p0_m0p7To0p0",
        "*et_bin5*eta_bin5*", "pdf_50p0To65p0_0p0To0p7",
        "*et_bin5*eta_bin6*", "pdf_50p0To65p0_0p7To1p4",
        "*et_bin5*eta_bin7*", "pdf_50p0To65p0_1p4To1p6",
        "*et_bin5*eta_bin8*", "pdf_50p0To65p0_1p6To2p1",
        "*et_bin5*eta_bin9*", "pdf_50p0To65p0_2p1To2p5",

        "*et_bin6*eta_bin0*", "pdf_65p0To90p0_m2p5Tom2p1",
        "*et_bin6*eta_bin1*", "pdf_65p0To90p0_m2p1Tom1p6",
        "*et_bin6*eta_bin2*", "pdf_65p0To90p0_m1p6Tom1p4",
        "*et_bin6*eta_bin3*", "pdf_65p0To90p0_m1p4Tom0p7",
        "*et_bin6*eta_bin4*", "pdf_65p0To90p0_m0p7To0p0",
        "*et_bin6*eta_bin5*", "pdf_65p0To90p0_0p0To0p7",
        "*et_bin6*eta_bin6*", "pdf_65p0To90p0_0p7To1p4",
        "*et_bin6*eta_bin7*", "pdf_65p0To90p0_1p4To1p6",
        "*et_bin6*eta_bin8*", "pdf_65p0To90p0_1p6To2p1",
        "*et_bin6*eta_bin9*", "pdf_65p0To90p0_2p1To2p5",

        "*et_bin7*eta_bin0*", "pdf_90p0To135p0_m2p5Tom2p1",
        "*et_bin7*eta_bin1*", "pdf_90p0To135p0_m2p1Tom1p6",
        "*et_bin7*eta_bin2*", "pdf_90p0To135p0_m1p6Tom1p4",
        "*et_bin7*eta_bin3*", "pdf_90p0To135p0_m1p4Tom0p7",
        "*et_bin7*eta_bin4*", "pdf_90p0To135p0_m0p7To0p0",
        "*et_bin7*eta_bin5*", "pdf_90p0To135p0_0p0To0p7",
        "*et_bin7*eta_bin6*", "pdf_90p0To135p0_0p7To1p4",
        "*et_bin7*eta_bin7*", "pdf_90p0To135p0_1p4To1p6",
        "*et_bin7*eta_bin8*", "pdf_90p0To135p0_1p6To2p1",
        "*et_bin7*eta_bin9*", "pdf_90p0To135p0_2p1To2p5",

        "*et_bin8*eta_bin0*", "pdf_135p0To190p0_m2p5Tom2p1",
        "*et_bin8*eta_bin1*", "pdf_135p0To190p0_m2p1Tom1p6",
        "*et_bin8*eta_bin2*", "pdf_135p0To190p0_m1p6Tom1p4",
        "*et_bin8*eta_bin3*", "pdf_135p0To190p0_m1p4Tom0p7",
        "*et_bin8*eta_bin4*", "pdf_135p0To190p0_m0p7To0p0",
        "*et_bin8*eta_bin5*", "pdf_135p0To190p0_0p0To0p7",
        "*et_bin8*eta_bin6*", "pdf_135p0To190p0_0p7To1p4",
        "*et_bin8*eta_bin7*", "pdf_135p0To190p0_1p4To1p6",
        "*et_bin8*eta_bin8*", "pdf_135p0To190p0_1p6To2p1",
        "*et_bin8*eta_bin9*", "pdf_135p0To190p0_2p1To2p5",

        "*et_bin9*eta_bin0*", "pdf_190p0To250p0_m2p5Tom2p1",
        "*et_bin9*eta_bin1*", "pdf_190p0To250p0_m2p1Tom1p6",
        "*et_bin9*eta_bin2*", "pdf_190p0To250p0_m1p6Tom1p4",
        "*et_bin9*eta_bin3*", "pdf_190p0To250p0_m1p4Tom0p7",
        "*et_bin9*eta_bin4*", "pdf_190p0To250p0_m0p7To0p0",
        "*et_bin9*eta_bin5*", "pdf_190p0To250p0_0p0To0p7",
        "*et_bin9*eta_bin6*", "pdf_190p0To250p0_0p7To1p4",
        "*et_bin9*eta_bin7*", "pdf_190p0To250p0_1p4To1p6",
        "*et_bin9*eta_bin8*", "pdf_190p0To250p0_1p6To2p1",
        "*et_bin9*eta_bin9*", "pdf_190p0To250p0_2p1To2p5",
)

############################################################################################
############################################################################################
####### GsfElectron -> Trigger / selection efficiency assuming some ID 
############################################################################################
############################################################################################

process.FitLoose = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",

              InputFileNames = cms.vstring(InputFileName),
              InputDirectoryName = cms.string("ElectronTnPLoose"),
              InputTreeName = cms.string("fitter_tree"), 
              OutputFileName = cms.string(options.outputPrefix + "_loo.root"),

              NumCPU = cms.uint32(8),
              SaveWorkspace = cms.bool(False),
              doCutAndCount = cms.bool(False),
              floatShapeParameters = cms.bool(True),

              binnedFit = cms.bool(True),
              binsForFit = cms.uint32(60),
              WeightVariable = cms.string("puWgt"),
                                                 
              # defines all the real variables of the probes available in the input tree and intended for use in the efficiencies
              Variables = cms.PSet(mass = cms.vstring("Tag-Probe Mass", "60.", "120.", "GeV/c^{2}"),
                                   probe_et = cms.vstring("Probe E_{T}", "25.", "250.", "GeV/c"),
                                   probe_eta = cms.vstring("Probe #eta", "-2.5", "2.5", ""),
                                   probe_phi = cms.vstring("Probe #phi", "-3.142", "3.142", ""),
                                   pair_nJet = cms.vstring("nJet > 30 GeV", "0", "100", ""),
                                   event_nPV = cms.vstring("nPV", "0", "100", ""),
                                   puWgt = cms.vstring("PU Weight", "0.", "10000.", ""),          
                                  ),

              # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations
              Categories = cms.PSet(passingHLT = cms.vstring("sinEle HLT", "dummy[pass=1,fail=0]"),
                                    passingVeto = cms.vstring("Veto ID", "dummy[pass=1,fail=0]"),
                                    passingLoose = cms.vstring("Loose ID", "dummy[pass=1,fail=0]"),
                                    passingMedium = cms.vstring("Medium ID", "dummy[pass=1,fail=0]"),
                                    passingTight = cms.vstring("Tight ID", "dummy[pass=1,fail=0]"),
                                    pair_mass60to120 = cms.vstring("60 < mass < 120", "dummy[true=1,false=0]"),
                                    pair_mass70to110 = cms.vstring("70 < mass < 110", "dummy[true=1,false=0]"),
                                    pair_mass80to100 = cms.vstring("80 < mass < 100", "dummy[true=1,false=0]"),
                                   ),
 
              PDFs = common.all_pdfs,

              # defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
              # there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 
              # the name of the parameter set becomes the name of the directory
              Efficiencies = cms.PSet(passHLT_et = cms.PSet(EfficiencyBinningSpecificationEt,
                                      EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass"),
                                     ),
                                      passHLT_eta = cms.PSet(EfficiencyBinningSpecificationEta,
                                      EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass"),
                                     ),
                                      passHLT_nJet = cms.PSet(EfficiencyBinningSpecificationnJet,
                                      EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass"),
                                     ),
                                      passHLT_nPV = cms.PSet(EfficiencyBinningSpecificationnPV,
                                      EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass"),
                                     ),
                                      passHLT_phi = cms.PSet(EfficiencyBinningSpecificationPhi,
                                      EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass"),
                                     ),
                                      passHLT_2d = cms.PSet(EfficiencyBinningSpecification2d,
                                      EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass"),
                                     ),
                                    )
                                   )

if (not options.isMC):
    delattr(process.FitLoose, "WeightVariable")

    for pdf in process.FitLoose.PDFs.__dict__:
        param =  process.FitLoose.PDFs.getParameter(pdf)
        if (type(param) is not cms.vstring):
            continue
        for i, l in enumerate(getattr(process.FitLoose.PDFs, pdf)):
            if l.find("signalFractionInPassing") != -1:
                getattr(process.FitLoose.PDFs, pdf)[i] = l.replace("[1.0]","[0.5,0.,1.]")
else:
    setattr(process.FitLoose, "doCutAndCount", cms.bool(True))

    for pdf in process.FitLoose.PDFs.__dict__:
        param =  process.FitLoose.PDFs.getParameter(pdf)
        if (type(param) is not cms.vstring):
            continue
        for i, l in enumerate(getattr(process.FitLoose.PDFs, pdf)):
            if l.find("backgroundPass") != -1:
                getattr(process.FitLoose.PDFs, pdf)[i] = "RooPolynomial::backgroundPass(mass, a[0.0])"
            if l.find("backgroundFail") != -1:
                getattr(process.FitLoose.PDFs, pdf)[i] = "RooPolynomial::backgroundFail(mass, a[0.0])"

### ------------------------------------------------- ###

process.FitMedium = process.FitLoose.clone()
process.FitMedium.InputDirectoryName = cms.string("ElectronTnPMedium")
process.FitMedium.OutputFileName = cms.string(options.outputPrefix + "_med.root")

### ------------------------------------------------- ###

process.FitTight = process.FitLoose.clone()
process.FitTight.InputDirectoryName = cms.string("ElectronTnPTight")
process.FitTight.OutputFileName = cms.string(options.outputPrefix + "_tig.root")

### ------------------------------------------------- ###

process.fitloo = cms.Path( process.FitLoose )
process.fitmed = cms.Path( process.FitMedium )
process.fittig = cms.Path( process.FitTight )
