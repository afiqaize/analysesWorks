### Madgraph SM tt

import FWCore.ParameterSet.Config as cms

inDir = "file:/nfs/dust/cms/user/afiqaize/cms/sim/gensim/smtt_nlo/smtt_nlo"

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source( "PoolSource", 
                fileNames = readFiles, secondaryFileNames = secFiles,
                duplicateCheckMode = cms.untracked.string("noDuplicateCheck")
)
readFiles.extend( [
    ##inDir + 'test.root',
    inDir + '_0.root',
] );

secFiles.extend( [
               ] )
