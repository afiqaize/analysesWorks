import FWCore.ParameterSet.Config as cms

options = dict()

options['MC_FLAG']                 = cms.bool(False)
options['HLTProcessName']          = "HLT"
options['OUTPUT_FILE_NAME']        = "TnPTreeData.root"

options['ELECTRON_COLL']           = "slimmedElectrons"
options['ELECTRON_CUTS']           = "(abs(superCluster.eta) <= 2.1) && et >= 25.0"
options['ELECTRON_TAG_CUTS']       = "(abs(superCluster.eta) <= 2.1) && !(1.4442 <= abs(superCluster.eta) <= 1.566) && et >= 25.0"

#options['TnPPATHS']                = cms.vstring("HLT_Ele27_eta2p1_WPLoose_Gsf_v2")
#options['TnPHLTTagFilters']        = cms.vstring("hltEle27WPLooseGsfTrackIsoFilter")

#options['HLTPathToMeasure']        = cms.vstring("HLT_Ele27_eta2p1_WPLoose_Gsf_v2")
#options['HLTFILTERTOMEASURE']      = cms.vstring("hltEle27WPLooseGsfTrackIsoFilter")

options['TnPPATHS']                = cms.vstring("HLT_Ele23_WPLoose_Gsf_v*")
options['TnPHLTTagFilters']        = cms.vstring("hltEle23WPLooseGsfTrackIsoFilter")

options['HLTPathToMeasure']        = cms.vstring("HLT_Ele23_WPLoose_Gsf_v*")
options['HLTFILTERTOMEASURE']      = cms.vstring("hltEle23WPLooseGsfTrackIsoFilter")

options['GLOBALTAG']               = '74X_dataRun2_Prompt_v4'

options['useAOD']                  = cms.bool(False)
options['OUTPUTEDMFILENAME']       = 'edmFile.root'
options['DEBUG']                   = cms.bool(False)
