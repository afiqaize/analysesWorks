import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbeFit")

process.load('FWCore.MessageService.MessageLogger_cfi')

process.source = cms.Source("EmptySource")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.TnP_fitMu = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",

    InputFileNames = cms.vstring("file:z_tp.root"),
    InputTreeName = cms.string("fitter_tree"),
    InputDirectoryName = cms.string("tpTree"),
    OutputFileName = cms.string("z_tp_eta.root"),

    NumCPU = cms.uint32(1),
    SaveWorkspace = cms.bool(False),

    Variables = cms.PSet(
        mass = cms.vstring("Tag-muon Mass", "70.", "110.", "GeV/c^{2}"),
        pt = cms.vstring("muon p_{T}", "20.", "200.", "GeV/c"),
        eta    = cms.vstring("muon #eta", "-2.1", "2.1", ""),
        abseta = cms.vstring("muon |#eta|", "0.", "2.1", ""),
        tag_nVertices = cms.vstring("Number of vertices", "0", "999", ""),
        pair_nTightJet = cms.vstring("Number of tight jets", "0", "10", ""),
        pair_nTaggedJet = cms.vstring("Number of tagged jets", "0", "10", ""),
        weight = cms.vstring("PU Weight", "0.", "10.", ""),
    ),

    Categories = cms.PSet(
        mcTrue = cms.vstring("MC true", "dummy[true=1,false=0]"),
        tag_IsoMu17 = cms.vstring("Tag Passing IsoMu17 Path", "dummy[pass=1,fail=0]"),
        IsoMu17 = cms.vstring("Probe Passing IsoMu17 Path", "dummy[pass=1,fail=0]"),
        tag_IsoMu17_leg = cms.vstring("Tag Passing IsoMu17_eta2p1 leg", "dummy[pass=1,fail=0]"),
        IsoMu17_leg = cms.vstring("Probe Passing IsoMu17_eta2p1 leg", "dummy[pass=1,fail=0]"),
    ),
    Cuts = cms.PSet(
    ),
    PDFs = cms.PSet(
        voigtPlusExpo = cms.vstring(
            "Voigtian::signal(mass, mean[90,80,100], width[2.495], sigma[3,1,20])",
            "Exponential::backgroundPass(mass, lp[0,-5,5])",
            "Exponential::backgroundFail(mass, lf[0,-5,5])",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),
        vpvPlusExpo = cms.vstring(
            "Voigtian::signal1(mass, mean1[90,80,100], width[2.495], sigma1[2,1,3])",
            "Voigtian::signal2(mass, mean2[90,80,100], width,        sigma2[4,2,10])",
            "SUM::signal(vFrac[0.8,0,1]*signal1, signal2)",
            "Exponential::backgroundPass(mass, lp[-0.1,-1,0.1])",
            "Exponential::backgroundFail(mass, lf[-0.1,-1,0.1])",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),
        vpvPlusExpoMin70 = cms.vstring(
            "Voigtian::signal1(mass, mean1[90,80,100], width[2.495], sigma1[2,1,3])",
            "Voigtian::signal2(mass, mean2[90,80,100], width,        sigma2[4,3,10])",
            "SUM::signal(vFrac[0.8,0.5,1]*signal1, signal2)",
            "Exponential::backgroundPass(mass, lp[-0.1,-1,0.1])",
            "Exponential::backgroundFail(mass, lf[-0.1,-1,0.1])",
            "efficiency[0.9,0.7,1]",
            "signalFractionInPassing[0.9]"
        )
    ),

    binnedFit = cms.bool(True),
    binsForFit = cms.uint32(40),
    #WeightVariable = cms.string("weight"), # no weight for data
    saveDistributionsPlot = cms.bool(False),
    Efficiencies = cms.PSet(
        IsoMu17 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("IsoMu17", "pass"), # IsoMu17(_leg) for MC (data)
            #UnbinnedVariables = cms.vstring("mass", "weight"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                ## Binning in continuous variables
                #pt = cms.vdouble(20., 30., 50., 80., 130., 200.),
                pt = cms.vdouble(20., 200.),
                eta = cms.vdouble(-2.1, -1.65, -1.2, -0.9, -0.45, 0., 0.45, 0.9, 1.2, 1.65, 2.1),
                #eta = cms.vdouble(-2.1, 2.1),
                #pair_nTightJet = cms.vdouble(0., 1., 2., 3., 4., 5.),
                #pair_nTightJet = cms.vdouble(1.8, 2.2),
                #pair_nTaggedJet = cms.vdouble(0., 1., 2., 3.),
                ## flags and conditions required at the denominator, 
            ),
            BinToPDFmap = cms.vstring("voigtPlusExpo"),
        )
    )
)

process.path = cms.Path(process.TnP_fitMu)
