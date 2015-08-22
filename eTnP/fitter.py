### The fitter for single electron TnP
### Careful about specifying the cut and bin ranges

import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.destinations = ['cout', 'cerr']

################################################
##                      _              _       
##   ___ ___  _ __  ___| |_ __ _ _ __ | |_ ___ 
##  / __/ _ \| '_ \/ __| __/ _` | '_ \| __/ __|
## | (_| (_) | | | \__ \ || (_| | | | | |_\__ \
##  \___\___/|_| |_|___/\__\__,_|_| |_|\__|___/
##                                              
################################################

InputFileName = "tnp_mc_ele27.root"
Prefix = "fit_mc_ele27_"
PDFName = "vgtPlusExpMC" #"pdfSigBkgData"

################################################
#specifies the binning of parameters
OutputFilePrefixPt = Prefix + "pt" 
EfficiencyBinsPt = cms.PSet(## conditions to be satisfied by all probes, weirdly causing large errors
                            #pair_mass60to120 = cms.vstring("true"),
                            ## variables to be checked as a function of
                            probe_pt = cms.vdouble( 30., 35., 40., 45., 50., 60., 70., 85., 100., 150., 200., 350. ),
                            #probe_pt = cms.vdouble( 30., 31., 32., 33., 34., 35., 36., 37.5, 40., 42.5, 45., 47.5, 50., 55., 60., 70., 82.5, 100. ),
                            #probe_eta = cms.vdouble( -2.1, 2.1 ),
                           )

OutputFilePrefixEta = Prefix + "eta" 
EfficiencyBinsEta = cms.PSet(## variables to be checked as a function of
                             #probe_pt = cms.vdouble( 30., 350. ),
                             probe_eta = cms.vdouble( -2.1, -1.6, -1.4, -0.9, -0.45, 0., 0.45, 0.9, 1.4, 1.6, 2.1 ),
                            )

OutputFilePrefixPhi = Prefix + "phi" 
EfficiencyBinsPhi = cms.PSet(## variables to be checked as a function of
                             #probe_pt = cms.vdouble( 30., 350. ),
                             #probe_eta = cms.vdouble( -2.1, 2.1 ),
                             probe_phi = cms.vdouble( -3.14, -2.617, -2.093, -1.57, -1.047, -0.523, 0., 0.523, 1.047, 1.57, 2.093, 2.617, 3.14 ),
                            )

OutputFilePrefixnJet = Prefix + "nJet" 
EfficiencyBinsnJet = cms.PSet(## variables to be checked as a function of
                              #probe_pt = cms.vdouble( 30., 350. ),
                              #probe_eta = cms.vdouble( -2.1, 2.1 ),
                              pair_nJet = cms.vdouble( -0.5, 0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5 ),
                             )

OutputFilePrefixnPV = Prefix + "nPV" 
EfficiencyBinsnPV = cms.PSet(## variables to be checked as a function of
                             #probe_pt = cms.vdouble( 30., 350. ),
                             #probe_eta = cms.vdouble( -2.1, 2.1 ),
                             event_nPV = cms.vdouble( 0., 5., 10., 15., 20., 25., 30. ),
                            )

#### For data: except for HLT step
EfficiencyBinningSpecificationPt = cms.PSet(
    #specifies what unbinned variables to include in the dataset, the mass is needed for the fit
    UnbinnedVariables = cms.vstring("mass"),
    #specifies the binning of parameters
    BinnedVariables = cms.PSet(EfficiencyBinsPt),
    #first string is the default followed by binRegExp - PDFname pairs
    BinToPDFmap = cms.vstring(PDFName)
)

EfficiencyBinningSpecificationEta = EfficiencyBinningSpecificationPt.clone()
EfficiencyBinningSpecificationEta.BinnedVariables = cms.PSet(EfficiencyBinsEta)

EfficiencyBinningSpecificationPhi = EfficiencyBinningSpecificationPt.clone()
EfficiencyBinningSpecificationPhi.BinnedVariables = cms.PSet(EfficiencyBinsPhi)

EfficiencyBinningSpecificationnJet = EfficiencyBinningSpecificationPt.clone()
EfficiencyBinningSpecificationnJet.BinnedVariables = cms.PSet(EfficiencyBinsnJet)

EfficiencyBinningSpecificationnPV = EfficiencyBinningSpecificationPt.clone()
EfficiencyBinningSpecificationnPV.BinnedVariables = cms.PSet(EfficiencyBinsnPV)

############################################################################################
############################################################################################
############################################################################################
####### GsfElectron -> Trigger / selection efficiency assuming some ID 
############################################################################################
############################################################################################

process.FitHLTLoosePt = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",

              InputFileNames = cms.vstring("file:" + InputFileName),
              InputDirectoryName = cms.string("GsfElectronHLTLoose"),
              InputTreeName = cms.string("fitter_tree"), 
              OutputFileName = cms.string(OutputFilePrefixPt + "_loo.root"),

              NumCPU = cms.uint32(8),
              SaveWorkspace = cms.bool(False),
              floatShapeParameters = cms.bool(True),

              binnedFit = cms.bool(True),
              binsForFit = cms.uint32(60),
              #WeightVariable = cms.string("PUweight"),
              #fixVars = cms.vstring("mean"),
                                                 
              # defines all the real variables of the probes available in the input tree and intended for use in the efficiencies
              Variables = cms.PSet(mass = cms.vstring("Tag-Probe Mass", "60.", "120.", "GeV/c^{2}"),
                                   probe_pt = cms.vstring("Probe E_{T}", "30.", "350.", "GeV/c"),
                                   probe_eta = cms.vstring("Probe #eta", "-2.1", "2.1", ""),
                                   probe_phi = cms.vstring("Probe #phi", "-3.14", "3.14", ""),
                                   pair_nJet = cms.vstring("nJet > 30 GeV", "0", "6", ""),
                                   event_nPV = cms.vstring("nPV", "0", "30", ""),          
                                  ),

              # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations
              Categories = cms.PSet(passingHLT = cms.vstring("Ele27_eta2p1", "dummy[pass=1,fail=0]"),
                                    pair_mass60to120 = cms.vstring("60 < mass < 120", "dummy[true=1,false=0]"),
                                   ),

              # defines all the PDFs that will be available for the efficiency calculations; 
              # uses RooFit's "factory" syntax;
              # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]"
              # and "signalFractionInPassing[0.9]" are used for initial values  
              PDFs = cms.PSet(pdfSigBkgMC = cms.vstring(
        "RooCBExGaussShape::signalResPass(mass,meanP[-0.0,-5.000,5.000],sigmaP[0.956,0.00,5.000],alphaP[0.999, 0.0,50.0],nP[1.405,0.000,50.000],sigmaP_2[1.000,0.500,15.00])",
        "RooCBExGaussShape::signalResFail(mass,meanF[-0.0,-5.000,5.000],sigmaF[3.331,0.00,5.000],alphaF[1.586, 0.0,50.0],nF[0.464,0.000,20.00],sigmaF_2[1.675,0.500,2.000])",
        "ZGeneratorLineShape::signalPhy(mass)", ### NLO line shape
        "RooCMSShape::backgroundPass(mass, alphaPass[60.,50.,70.], betaPass[0.001, 0.,0.1], gammaPass[0.1, 0, 1], peakPass[90.0])",
        "RooCMSShape::backgroundFail(mass, alphaFail[60.,50.,70.], betaFail[0.001, 0.,0.1], gammaFail[0.1, 0, 1], peakFail[90.0])",
        "FCONV::signalPass(mass, signalPhy, signalResPass)",
        "FCONV::signalFail(mass, signalPhy, signalResFail)",     
        "efficiency[0.5,0,1]",
        "signalFractionInPassing[1.0]"     
    ),
                              pdfSigBkgData = cms.vstring(
        "RooCBExGaussShape::signalResPass(mass,meanP[0,-5.000,5.000],sigmaP[1.419,1.00,15.000],alphaP[0.130],nP[50.08],sigmaP_2[1, 1, 15.000])",
        "RooCBExGaussShape::signalResFail(mass,meanF[1.1,-5.000,5.000],sigmaF[1.331,0.100,15.000],alphaF[0.284], nF[3.350],sigmaF_2[1, 1, 15.000])",
        "ZGeneratorLineShape::signalPhy(mass)", ### NLO line shape
        "RooExponential::backgroundPass(mass, aPass[-0.1, -1., 0])", 
        "RooExponential::backgroundFail(mass, aFail[-0.1, -1., 0])", 
        "FCONV::signalPass(mass, signalPhy, signalResPass)",
        "FCONV::signalFail(mass, signalPhy, signalResFail)",     
        "efficiency[0.5,0,1]",
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
              Efficiencies = cms.PSet(HLT = cms.PSet(EfficiencyBinningSpecificationPt,
                                      EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass"),
                                     ),
                                    )
                                   )

process.FitHLTLooseEta = process.FitHLTLoosePt.clone()
process.FitHLTLooseEta.OutputFileName = OutputFileName = cms.string(OutputFilePrefixEta + "_loo.root")
process.FitHLTLooseEta.Efficiencies.HLT = cms.PSet(EfficiencyBinningSpecificationEta,
                                                   EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass")
                                                  )

process.FitHLTLoosePhi = process.FitHLTLoosePt.clone()
process.FitHLTLoosePhi.OutputFileName = OutputFileName = cms.string(OutputFilePrefixPhi + "_loo.root")
process.FitHLTLoosePhi.Efficiencies.HLT = cms.PSet(EfficiencyBinningSpecificationPhi,
                                                   EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass")
                                                  )

process.FitHLTLoosenJet = process.FitHLTLoosePt.clone()
process.FitHLTLoosenJet.OutputFileName = OutputFileName = cms.string(OutputFilePrefixnJet + "_loo.root")
process.FitHLTLoosenJet.Efficiencies.HLT = cms.PSet(EfficiencyBinningSpecificationnJet,
                                                   EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass")
                                                  )

process.FitHLTLoosenPV = process.FitHLTLoosePt.clone()
process.FitHLTLoosenPV.OutputFileName = OutputFileName = cms.string(OutputFilePrefixnPV + "_loo.root")
process.FitHLTLoosenPV.Efficiencies.HLT = cms.PSet(EfficiencyBinningSpecificationnPV,
                                                   EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass")
                                                  )

### ------------------------------------------------- ###

process.FitHLTMediumPt = process.FitHLTLoosePt.clone()
process.FitHLTMediumPt.InputDirectoryName = cms.string("GsfElectronHLTMedium")
process.FitHLTMediumPt.OutputFileName = cms.string(OutputFilePrefixPt + "_med.root")

process.FitHLTMediumEta = process.FitHLTMediumPt.clone()
process.FitHLTMediumEta.OutputFileName = OutputFileName = cms.string(OutputFilePrefixEta + "_med.root")
process.FitHLTMediumEta.Efficiencies.HLT = cms.PSet(EfficiencyBinningSpecificationEta,
                                                   EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass")
                                                  )

process.FitHLTMediumPhi = process.FitHLTMediumPt.clone()
process.FitHLTMediumPhi.OutputFileName = OutputFileName = cms.string(OutputFilePrefixPhi + "_med.root")
process.FitHLTMediumPhi.Efficiencies.HLT = cms.PSet(EfficiencyBinningSpecificationPhi,
                                                   EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass")
                                                  )

process.FitHLTMediumnJet = process.FitHLTMediumPt.clone()
process.FitHLTMediumnJet.OutputFileName = OutputFileName = cms.string(OutputFilePrefixnJet + "_med.root")
process.FitHLTMediumnJet.Efficiencies.HLT = cms.PSet(EfficiencyBinningSpecificationnJet,
                                                   EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass")
                                                  )

process.FitHLTMediumnPV = process.FitHLTMediumPt.clone()
process.FitHLTMediumnPV.OutputFileName = OutputFileName = cms.string(OutputFilePrefixnPV + "_med.root")
process.FitHLTMediumnPV.Efficiencies.HLT = cms.PSet(EfficiencyBinningSpecificationnPV,
                                                   EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass")
                                                  )

### ------------------------------------------------- ###

process.FitHLTTightPt = process.FitHLTLoosePt.clone()
process.FitHLTTightPt.InputDirectoryName = cms.string("GsfElectronHLTTight")
process.FitHLTTightPt.OutputFileName = cms.string(OutputFilePrefixPt + "_tig.root")

process.FitHLTTightEta = process.FitHLTTightPt.clone()
process.FitHLTTightEta.OutputFileName = OutputFileName = cms.string(OutputFilePrefixEta + "_tig.root")
process.FitHLTTightEta.Efficiencies.HLT = cms.PSet(EfficiencyBinningSpecificationEta,
                                                   EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass")
                                                  )

process.FitHLTTightPhi = process.FitHLTTightPt.clone()
process.FitHLTTightPhi.OutputFileName = OutputFileName = cms.string(OutputFilePrefixPhi + "_tig.root")
process.FitHLTTightPhi.Efficiencies.HLT = cms.PSet(EfficiencyBinningSpecificationPhi,
                                                   EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass")
                                                  )

process.FitHLTTightnJet = process.FitHLTTightPt.clone()
process.FitHLTTightnJet.OutputFileName = OutputFileName = cms.string(OutputFilePrefixnJet + "_tig.root")
process.FitHLTTightnJet.Efficiencies.HLT = cms.PSet(EfficiencyBinningSpecificationnJet,
                                                   EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass")
                                                  )

process.FitHLTTightnPV = process.FitHLTTightPt.clone()
process.FitHLTTightnPV.OutputFileName = OutputFileName = cms.string(OutputFilePrefixnPV + "_tig.root")
process.FitHLTTightnPV.Efficiencies.HLT = cms.PSet(EfficiencyBinningSpecificationnPV,
                                                   EfficiencyCategoryAndState = cms.vstring("passingHLT", "pass")
                                                  )

### ------------------------------------------------- ###

process.fitloo = cms.Path( process.FitHLTLoosePt +
                           process.FitHLTLooseEta +
                           process.FitHLTLoosePhi +
                           process.FitHLTLoosenJet +
                           process.FitHLTLoosenPV
                         )

process.fitmed = cms.Path( process.FitHLTMediumPt +
                           process.FitHLTMediumEta +
                           process.FitHLTMediumPhi +
                           process.FitHLTMediumnJet +
                           process.FitHLTMediumnPV
                         )

process.fittig = cms.Path( process.FitHLTTightPt +
                           process.FitHLTTightEta +
                           process.FitHLTTightPhi +
                           process.FitHLTTightnJet +
                           process.FitHLTTightnPV
                         )
