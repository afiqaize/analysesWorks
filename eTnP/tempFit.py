### The template fitter for single electron TnP
### Oct16 First used with run15D_act02, need the template files

import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing
import PhysicsTools.TagAndProbe.fitAll_pp15bx25 as common

################################################
##                      _              _       
##   ___ ___  _ __  ___| |_ __ _ _ __ | |_ ___ 
##  / __/ _ \| '_ \/ __| __/ _` | '_ \| __/ __|
## | (_| (_) | | | \__ \ || (_| | | | | |_\__ \
##  \___\___/|_| |_|___/\__\__,_|_| |_|\__|___/
##                                              
################################################

InputFileName = "tnp_mc_pp15bx25.root"
Prefix = "pdf_mc_pp15bx25_"

options = VarParsing('analysis')
options.register(
    "isMC",
    True,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Compute efficiency for MC"
    )
options.parseArguments()

process = cms.Process("TagProbe")
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.destinations = ['cout', 'cerr']

################################################
#specifies the binning of parameters
OutputFilePrefixEt = Prefix + "et" 
EfficiencyBinsEt = cms.PSet(## conditions to be satisfied by all probes, weirdly causing large errors
                            #pair_mass70to110 = cms.vstring("true"),
                            ## variables to be checked as a function of
                            probe_et = cms.vdouble( 25., 30., 35., 40., 45., 50., 65., 90., 135., 190., 250. ),
                            #probe_eta = cms.vdouble( -2.5, 2.5 ),
                           )

OutputFilePrefixEta = Prefix + "eta" 
EfficiencyBinsEta = cms.PSet(## conditions to be satisfied by all probes, weirdly causing large errors
                             #pair_mass70to110 = cms.vstring("true"),
                             ## variables to be checked as a function of
                             #probe_et = cms.vdouble( 25., 250. ),
                             probe_eta = cms.vdouble( -2.5, -2.1, -1.6, -1.4, -0.7, 0., 0.7, 1.4, 1.6, 2.1, 2.5 ),
                            )

OutputFilePrefixPhi = Prefix + "phi" 
EfficiencyBinsPhi = cms.PSet(## conditions to be satisfied by all probes, weirdly causing large errors
                             #pair_mass70to110 = cms.vstring("true"),
                             ## variables to be checked as a function of
                             #probe_et = cms.vdouble( 25., 250. ),
                             probe_phi = cms.vdouble( -3.142, -2.514, -1.885, -1.257, -0.628, 0., 0.628, 1.257, 1.885, 2.514, 3.142 ),
                            )

OutputFilePrefixnJet = Prefix + "nJet" 
EfficiencyBinsnJet = cms.PSet(## conditions to be satisfied by all probes, weirdly causing large errors
                              #pair_mass70to110 = cms.vstring("true"),
                              ## variables to be checked as a function of
                              #probe_et = cms.vdouble( 25., 250. ),
                              pair_nJet = cms.vdouble( -0.5, 0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5 ),
                             )

OutputFilePrefixnPV = Prefix + "nPV" 
EfficiencyBinsnPV = cms.PSet(## conditions to be satisfied by all probes, weirdly causing large errors
                             #pair_mass70to110 = cms.vstring("true"),
                             ## variables to be checked as a function of
                             #probe_et = cms.vdouble( 25., 250. ),
                             event_nPV = cms.vdouble( 0., 2., 4., 6., 8., 10., 13., 17., 21., 25., 40. ),
                            )

OutputFilePrefix2d = Prefix + "2d" 
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
############################################################################################
####### GsfElectron -> Trigger / selection efficiency assuming some ID 
############################################################################################
############################################################################################

process.FitHLTLooseEt = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",

              InputFileNames = cms.vstring("file:" + InputFileName),
              InputDirectoryName = cms.string("GsfElectronHLTLoose"),
              InputTreeName = cms.string("fitter_tree"), 
              OutputFileName = cms.string(OutputFilePrefixEt + "_loo.root"),

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
                                   pair_nJet = cms.vstring("nJet > 30 GeV", "0", "6", ""),
                                   event_nPV = cms.vstring("nPV", "0", "40", ""),
                                   puWgt = cms.vstring("PU Weight", "0.", "10000.", ""),          
                                  ),

              # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations
              Categories = cms.PSet(passingHLT = cms.vstring("sinEle HLT", "dummy[pass=1,fail=0]"),
                                    pair_mass60to120 = cms.vstring("60 < mass < 120", "dummy[true=1,false=0]"),
                                    pair_mass70to110 = cms.vstring("70 < mass < 110", "dummy[true=1,false=0]"),
                                    pair_mass80to100 = cms.vstring("80 < mass < 100", "dummy[true=1,false=0]"),
                                   ),
 
              PDFs = common.all_pdfs,

              # defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
              # there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 
              # the name of the parameter set becomes the name of the directory
              Efficiencies = cms.PSet(HLT = cms.PSet(EfficiencyBinningSpecificationEt,
                                      EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass"),
                                     ),
                                    )
                                   )

if (not options.isMC):
    delattr(process.FitHLTLooseEt, "WeightVariable")

    for pdf in process.FitHLTLooseEt.PDFs.__dict__:
        param =  process.FitHLTLooseEt.PDFs.getParameter(pdf)
        if (type(param) is not cms.vstring):
            continue
        for i, l in enumerate(getattr(process.FitHLTLooseEt.PDFs, pdf)):
            if l.find("signalFractionInPassing") != -1:
                getattr(process.FitHLTLooseEt.PDFs, pdf)[i] = l.replace("[1.0]","[0.5,0.,1.]")
else:
    setattr(process.FitHLTLooseEt, "doCutAndCount", cms.bool(True))

    for pdf in process.FitHLTLooseEt.PDFs.__dict__:
        param =  process.FitHLTLooseEt.PDFs.getParameter(pdf)
        if (type(param) is not cms.vstring):
            continue
        for i, l in enumerate(getattr(process.FitHLTLooseEt.PDFs, pdf)):
            if l.find("backgroundPass") != -1:
                getattr(process.FitHLTLooseEt.PDFs, pdf)[i] = "RooPolynomial::backgroundPass(mass, a[0.0])"
            if l.find("backgroundFail") != -1:
                getattr(process.FitHLTLooseEt.PDFs, pdf)[i] = "RooPolynomial::backgroundFail(mass, a[0.0])"

process.FitHLTLooseEta = process.FitHLTLooseEt.clone()
process.FitHLTLooseEta.OutputFileName = OutputFileName = cms.string(OutputFilePrefixEta + "_loo.root")
process.FitHLTLooseEta.Efficiencies.HLT = cms.PSet(EfficiencyBinningSpecificationEta,
                                                   EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass")
                                                  )

process.FitHLTLoosePhi = process.FitHLTLooseEt.clone()
process.FitHLTLoosePhi.OutputFileName = OutputFileName = cms.string(OutputFilePrefixPhi + "_loo.root")
process.FitHLTLoosePhi.Efficiencies.HLT = cms.PSet(EfficiencyBinningSpecificationPhi,
                                                   EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass")
                                                  )

process.FitHLTLoosenJet = process.FitHLTLooseEt.clone()
process.FitHLTLoosenJet.OutputFileName = OutputFileName = cms.string(OutputFilePrefixnJet + "_loo.root")
process.FitHLTLoosenJet.Efficiencies.HLT = cms.PSet(EfficiencyBinningSpecificationnJet,
                                                   EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass")
                                                  )

process.FitHLTLoosenPV = process.FitHLTLooseEt.clone()
process.FitHLTLoosenPV.OutputFileName = OutputFileName = cms.string(OutputFilePrefixnPV + "_loo.root")
process.FitHLTLoosenPV.Efficiencies.HLT = cms.PSet(EfficiencyBinningSpecificationnPV,
                                                   EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass")
                                                  )

process.FitHLTLoose2d = process.FitHLTLooseEt.clone()
process.FitHLTLoose2d.OutputFileName = OutputFileName = cms.string(OutputFilePrefix2d + "_loo.root")
process.FitHLTLoose2d.Efficiencies.HLT = cms.PSet(EfficiencyBinningSpecification2d,
                                                   EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass")
                                                  )

### ------------------------------------------------- ###

process.FitHLTMediumEt = process.FitHLTLooseEt.clone()
process.FitHLTMediumEt.InputDirectoryName = cms.string("GsfElectronHLTMedium")
process.FitHLTMediumEt.OutputFileName = cms.string(OutputFilePrefixEt + "_med.root")

process.FitHLTMediumEta = process.FitHLTMediumEt.clone()
process.FitHLTMediumEta.OutputFileName = OutputFileName = cms.string(OutputFilePrefixEta + "_med.root")
process.FitHLTMediumEta.Efficiencies.HLT = cms.PSet(EfficiencyBinningSpecificationEta,
                                                   EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass")
                                                  )

process.FitHLTMediumPhi = process.FitHLTMediumEt.clone()
process.FitHLTMediumPhi.OutputFileName = OutputFileName = cms.string(OutputFilePrefixPhi + "_med.root")
process.FitHLTMediumPhi.Efficiencies.HLT = cms.PSet(EfficiencyBinningSpecificationPhi,
                                                   EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass")
                                                  )

process.FitHLTMediumnJet = process.FitHLTMediumEt.clone()
process.FitHLTMediumnJet.OutputFileName = OutputFileName = cms.string(OutputFilePrefixnJet + "_med.root")
process.FitHLTMediumnJet.Efficiencies.HLT = cms.PSet(EfficiencyBinningSpecificationnJet,
                                                   EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass")
                                                  )

process.FitHLTMediumnPV = process.FitHLTMediumEt.clone()
process.FitHLTMediumnPV.OutputFileName = OutputFileName = cms.string(OutputFilePrefixnPV + "_med.root")
process.FitHLTMediumnPV.Efficiencies.HLT = cms.PSet(EfficiencyBinningSpecificationnPV,
                                                   EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass")
                                                  )

process.FitHLTMedium2d = process.FitHLTMediumEt.clone()
process.FitHLTMedium2d.OutputFileName = OutputFileName = cms.string(OutputFilePrefix2d + "_med.root")
process.FitHLTMedium2d.Efficiencies.HLT = cms.PSet(EfficiencyBinningSpecification2d,
                                                   EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass")
                                                  )

### ------------------------------------------------- ###

process.FitHLTTightEt = process.FitHLTLooseEt.clone()
process.FitHLTTightEt.InputDirectoryName = cms.string("GsfElectronHLTTight")
process.FitHLTTightEt.OutputFileName = cms.string(OutputFilePrefixEt + "_tig.root")

process.FitHLTTightEta = process.FitHLTTightEt.clone()
process.FitHLTTightEta.OutputFileName = OutputFileName = cms.string(OutputFilePrefixEta + "_tig.root")
process.FitHLTTightEta.Efficiencies.HLT = cms.PSet(EfficiencyBinningSpecificationEta,
                                                   EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass")
                                                  )

process.FitHLTTightPhi = process.FitHLTTightEt.clone()
process.FitHLTTightPhi.OutputFileName = OutputFileName = cms.string(OutputFilePrefixPhi + "_tig.root")
process.FitHLTTightPhi.Efficiencies.HLT = cms.PSet(EfficiencyBinningSpecificationPhi,
                                                   EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass")
                                                  )

process.FitHLTTightnJet = process.FitHLTTightEt.clone()
process.FitHLTTightnJet.OutputFileName = OutputFileName = cms.string(OutputFilePrefixnJet + "_tig.root")
process.FitHLTTightnJet.Efficiencies.HLT = cms.PSet(EfficiencyBinningSpecificationnJet,
                                                   EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass")
                                                  )

process.FitHLTTightnPV = process.FitHLTTightEt.clone()
process.FitHLTTightnPV.OutputFileName = OutputFileName = cms.string(OutputFilePrefixnPV + "_tig.root")
process.FitHLTTightnPV.Efficiencies.HLT = cms.PSet(EfficiencyBinningSpecificationnPV,
                                                   EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass")
                                                  )

process.FitHLTTight2d = process.FitHLTTightEt.clone()
process.FitHLTTight2d.OutputFileName = OutputFileName = cms.string(OutputFilePrefix2d + "_tig.root")
process.FitHLTTight2d.Efficiencies.HLT = cms.PSet(EfficiencyBinningSpecification2d,
                                                   EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass")
                                                  )

### ------------------------------------------------- ###

process.fitloo = cms.Path( process.FitHLTLooseEt +
                           process.FitHLTLooseEta +
                           process.FitHLTLoosePhi +
                           process.FitHLTLoosenJet +
                           process.FitHLTLoosenPV +
                           process.FitHLTLoose2d
                         )

process.fitmed = cms.Path( process.FitHLTMediumEt +
                           process.FitHLTMediumEta +
                           process.FitHLTMediumPhi +
                           process.FitHLTMediumnJet +
                           process.FitHLTMediumnPV +
                           process.FitHLTMedium2d
                         )

process.fittig = cms.Path( process.FitHLTTightEt +
                           process.FitHLTTightEta +
                           process.FitHLTTightPhi +
                           process.FitHLTTightnJet +
                           process.FitHLTTightnPV +
                           process.FitHLTTight2d
                         )
