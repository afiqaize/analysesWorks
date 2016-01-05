### The fitter for single electron TnP
### Careful about specifying the cut and bin ranges
### Jan 02: Fitter now outputs all variables in a single root file
### Jan 02: Also includes a testing None directory for ID fits

import sys
import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

process = cms.Process("TagProbe")
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.destinations = ['cout', 'cerr']

################################################
### Initialization
################################################

PDFName = "pdfSigBkgMC" # "vgtPlusExpData" "pdfSigBkgMC"

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
options.register(
    "doID",
    False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Compute efficiency for MC"
    )
options.parseArguments()

if (options.inputName == ""):
    sys.exit("Need an input file!")
else:
    InputFileName = "file:" + options.inputName

################################################
#specifies the binning of parameters
EfficiencyBinsEt = cms.PSet(## conditions to be satisfied by all probes, weirdly causing large errors
                            #pair_mass60to120 = cms.vstring("true"),
                            ## variables to be checked as a function of
                            probe_et = cms.vdouble( 25., 30., 35., 40., 45., 50., 65., 90., 135., 190., 250. ),
                            #probe_et = cms.vdouble( 25., 26., 27., 28., 29., 30., 31., 32., 33., 34., 35., 36., 37.5, 40., 42.5, 45., 47.5, 50., 55., 60., 70., 82.5, 100. ),
                            #probe_eta = cms.vdouble( -2.5, 2.5 ),
                           )

EfficiencyBinsEta = cms.PSet(## variables to be checked as a function of
                             #probe_et = cms.vdouble( 25., 250. ),
                             probe_eta = cms.vdouble( -2.5, -2.1, -1.6, -1.4, -0.7, 0., 0.7, 1.4, 1.6, 2.1, 2.5 ),
                            )

EfficiencyBinsPhi = cms.PSet(## variables to be checked as a function of
                             #probe_et = cms.vdouble( 25., 250. ),
                             probe_phi = cms.vdouble( -3.142, -2.514, -1.885, -1.257, -0.628, 0., 0.628, 1.257, 1.885, 2.514, 3.142 ),
                            )

EfficiencyBinsnJet = cms.PSet(## variables to be checked as a function of
                              #probe_et = cms.vdouble( 25., 250. ),
                              pair_nJet = cms.vdouble( -0.5, 0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5 ),
                             )

EfficiencyBinsnPV = cms.PSet(## variables to be checked as a function of
                             #probe_et = cms.vdouble( 25., 250. ),
                             event_nPV = cms.vdouble( 0., 2., 4., 6., 8., 10., 13., 17., 21., 25., 40. ),
                            )

#### For data: except for HLT step
EfficiencyBinningSpecificationEt = cms.PSet(
    #specifies the binning of parameters
    BinnedVariables = cms.PSet(EfficiencyBinsEt),
    #first string is the default followed by binRegExp - PDFname pairs
    BinToPDFmap = cms.vstring(PDFName)
)

if (not options.isMC):
    setattr(EfficiencyBinningSpecificationEt, "UnbinnedVariables", cms.vstring("mass"))
else:
    setattr(EfficiencyBinningSpecificationEt, "UnbinnedVariables", cms.vstring("mass", "puWgt"))

EfficiencyBinningSpecificationEta = EfficiencyBinningSpecificationEt.clone()
EfficiencyBinningSpecificationEta.BinnedVariables = cms.PSet(EfficiencyBinsEta)

EfficiencyBinningSpecificationPhi = EfficiencyBinningSpecificationEt.clone()
EfficiencyBinningSpecificationPhi.BinnedVariables = cms.PSet(EfficiencyBinsPhi)

EfficiencyBinningSpecificationnJet = EfficiencyBinningSpecificationEt.clone()
EfficiencyBinningSpecificationnJet.BinnedVariables = cms.PSet(EfficiencyBinsnJet)

EfficiencyBinningSpecificationnPV = EfficiencyBinningSpecificationEt.clone()
EfficiencyBinningSpecificationnPV.BinnedVariables = cms.PSet(EfficiencyBinsnPV)

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

              # defines all the PDFs that will be available for the efficiency calculations; 
              # uses RooFit's "factory" syntax;
              # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]"
              # and "signalFractionInPassing[0.9]" are used for initial values  
              PDFs = cms.PSet(pdfSigBkgMC = cms.vstring(
        "RooCBExGaussShape::signalResPass(mass,meanP[0., -1., 1.],sigmaP[.1, 0., 1.],alphaP[1., 0., 5.],nP[1., 0., 5.],sigmaP_2[.5, 0., 1.])",
        "RooCBExGaussShape::signalResFail(mass,meanF[.5, -1., 1.],sigmaF[.1, 0., 1.],alphaF[1., 0., 5.],nF[1., 0., 5.],sigmaF_2[.5, 0., 1.])",
        "ZGeneratorLineShape::signalPhy(mass)", ### NLO line shape
        "RooCMSShape::backgroundPass(mass, alphaPass[60.,50.,70.], betaPass[0.001, 0.,0.1], gammaPass[0.1, 0, 1], peakPass[90.0])",
        "RooCMSShape::backgroundFail(mass, alphaFail[60.,50.,70.], betaFail[0.001, 0.,0.1], gammaFail[0.1, 0, 1], peakFail[90.0])",
        "FCONV::signalPass(mass, signalPhy, signalResPass)",
        "FCONV::signalFail(mass, signalPhy, signalResFail)",     
        "efficiency[0.9, 0., 1.]",
        "signalFractionInPassing[1.0]"     
    ),
                              pdfSigBkgData = cms.vstring(
        "RooCBExGaussShape::signalResPass(mass,meanP[0., -1., 1.],sigmaP[.5, 0., 1.],alphaP[1., 0., 5.],nP[1., 0., 5.],sigmaP_2[.5, 0., 1.])",
        "RooCBExGaussShape::signalResFail(mass,meanF[0., -1., 1.],sigmaF[.5, 0., 1.],alphaF[1., 0., 5.],nF[1., 0., 5.],sigmaF_2[.5, 0., 1.])",
        "ZGeneratorLineShape::signalPhy(mass)", ### NLO line shape
        "RooExponential::backgroundPass(mass, aPass[-.1, -1., 0.])", 
        "RooExponential::backgroundFail(mass, aFail[-.1, -1., 0.])",
        "FCONV::signalPass(mass, signalPhy, signalResPass)",
        "FCONV::signalFail(mass, signalPhy, signalResFail)",     
        "efficiency[0.9, 0., 1.]",
        "signalFractionInPassing[0.9]"
    ),
                              vgtPlusExpMC = cms.vstring(
        "Voigtian::signal(mass, mean[90., 80., 100.], width[2.495], sigma[3., 1., 20.])",
        "Exponential::backgroundPass(mass, lp[0., -5., 5.])",
        "Exponential::backgroundFail(mass, lf[0., -5., 5.])",
        "efficiency[0.9, 0., 1.]",
        "signalFractionInPassing[1.0]"
    ),
                              vgtPlusExpData = cms.vstring(
        "Voigtian::signal(mass, mean[90., 80., 100.], width[2.495], sigma[3., 1., 20.])",
        "Exponential::backgroundPass(mass, lp[0., -5., 5.])",
        "Exponential::backgroundFail(mass, lf[0., -5., 5.])",
        "efficiency[0.9, 0., 1.]",
        "signalFractionInPassing[0.9]"
    ),
                                       ),
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
                                    )
                                   )

if (not options.isMC):
    delattr(process.FitLoose, "WeightVariable")

else:
    setattr(process.FitLoose, "doCutAndCount", cms.bool(True))

### ------------------------------------------------- ###

process.FitMedium = process.FitLoose.clone()
process.FitMedium.InputDirectoryName = cms.string("ElectronTnPMedium")
process.FitMedium.OutputFileName = cms.string(options.outputPrefix + "_med.root")

### ------------------------------------------------- ###

process.FitTight = process.FitLoose.clone()
process.FitTight.InputDirectoryName = cms.string("ElectronTnPTight")
process.FitTight.OutputFileName = cms.string(options.outputPrefix + "_tig.root")

### ------------------------------------------------- ###

process.FitNone = process.FitLoose.clone()
process.FitNone.InputDirectoryName = cms.string("ElectronTnPNone")
process.FitNone.OutputFileName = cms.string(options.outputPrefix + "_non.root")
process.FitNone.Efficiencies = cms.PSet(passTight_et = cms.PSet(EfficiencyBinningSpecificationEt,
                                        EfficiencyCategoryAndState = cms.vstring("passingTight", "pass"),
                                       ),
                                        passTight_eta = cms.PSet(EfficiencyBinningSpecificationEta,
                                        EfficiencyCategoryAndState = cms.vstring("passingTight", "pass"),
                                       ),
                                        passTight_nJet = cms.PSet(EfficiencyBinningSpecificationnJet,
                                        EfficiencyCategoryAndState = cms.vstring("passingTight", "pass"),
                                       ),
                                        passTight_nPV = cms.PSet(EfficiencyBinningSpecificationnPV,
                                        EfficiencyCategoryAndState = cms.vstring("passingTight", "pass"),
                                       ),
                                        passTight_phi = cms.PSet(EfficiencyBinningSpecificationPhi,
                                        EfficiencyCategoryAndState = cms.vstring("passingTight", "pass"),
                                       ),
                                      )

### ------------------------------------------------- ###

process.fitloo = cms.Path( process.FitLoose )
process.fitmed = cms.Path( process.FitMedium )
process.fittig = cms.Path( process.FitTight )
process.fitnone = cms.Path( )

if (options.doID):
    process.fitnone = cms.Path( process.FitNone )
