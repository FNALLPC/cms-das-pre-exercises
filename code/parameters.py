import FWCore.ParameterSet.Config as cms

process = cms.Process("FWLitePlots")

process.MuonAnalyzer = cms.PSet(
    ## common input for wrapped analyzers
    fileNames   = cms.vstring(
        # Multiple file should be comma separated
        # This is the format for using a remote file
        'root://cmseos.fnal.gov//store/user/cmsdas/2022/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_1.root',
        # The format for using a local file can be found in the commented line below
        # 'file:slimMiniAOD_data_MuEle_1.root'
  ),


    outputFile  = cms.string('myZPeakCRAB_fwlite.root'),## mandatory
    outputEvery  = cms.uint32(1000),
    maxEvents   = cms.int32(-1),                      ## optional
    ##reportAfter = cms.uint32(100),                   ## optional
    ## input specific for this analyzer
    muons = cms.InputTag('slimmedMuons')

)


