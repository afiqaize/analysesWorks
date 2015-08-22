import FWCore.ParameterSet.Config as cms

options = dict()

options['MC_FLAG']                 = cms.bool(True)
options['HLTProcessName']          = "HLT"
options['OUTPUT_FILE_NAME']        = "TnPTreeMC.root"

options['ELECTRON_COLL']           = "slimmedElectrons"
options['ELECTRON_CUTS']           = "(abs(superCluster.eta) <= 2.1) && pt >= 30.0"
options['ELECTRON_TAG_CUTS']       = "(abs(superCluster.eta) <= 2.1) && !(1.4442 <= abs(superCluster.eta) <= 1.566) && pt >= 30.0"

options['TnPPATHS']                = cms.vstring("HLT_Ele27_eta2p1_WP75_Gsf_v1")
options['TnPHLTTagFilters']        = cms.vstring("hltEle27WP75GsfTrackIsoFilter")

options['HLTPathToMeasure']        = cms.vstring("HLT_Ele27_eta2p1_WP75_Gsf_v1")
options['HLTFILTERTOMEASURE']      = cms.vstring("hltEle27WP75GsfTrackIsoFilter")

options['GLOBALTAG']               = 'MCRUN2_74_V9A'

options['useAOD']                  = cms.bool(False)
options['OUTPUTEDMFILENAME']       = 'edmFile.root'
options['DEBUG']                   = cms.bool(False)
