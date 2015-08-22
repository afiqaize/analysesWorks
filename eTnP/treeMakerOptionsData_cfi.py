import FWCore.ParameterSet.Config as cms

options = dict()

options['MC_FLAG']                 = cms.bool(False)
options['HLTProcessName']          = "HLT"
options['OUTPUT_FILE_NAME']        = "TnPTreeData.root"

options['ELECTRON_COLL']           = "slimmedElectrons"
options['ELECTRON_CUTS']           = "(abs(superCluster.eta) <= 2.1) && pt >= 30.0"
options['ELECTRON_TAG_CUTS']       = "(abs(superCluster.eta) <= 2.1) && !(1.4442 <= abs(superCluster.eta) <= 1.566) && pt >= 30.0"

options['TnPPATHS']                = cms.vstring("HLT_Ele27_eta2p1_WPLoose_Gsf_v1")
options['TnPHLTTagFilters']        = cms.vstring("hltEle27WPLooseGsfTrackIsoFilter")

options['HLTPathToMeasure']        = cms.vstring("HLT_Ele27_eta2p1_WPLoose_Gsf_v1")
options['HLTFILTERTOMEASURE']      = cms.vstring("hltEle27WPLooseGsfTrackIsoFilter")

options['GLOBALTAG']               = '74X_dataRun2_Prompt_v1'

options['useAOD']                  = cms.bool(False)
options['OUTPUTEDMFILENAME']       = 'edmFile.root'
options['DEBUG']                   = cms.bool(False)
