import FWCore.ParameterSet.Config as cms

process = cms.Process("Test")

process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring(
      # Multiple file should be comma separated
      # This is the format for using a remote file
      'root://cmseos.fnal.gov//store/user/cmsdas/2022/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_1.root',
      # The format for using a local file can be found in the commented line below
      # 'file:slimMiniAOD_data_MuEle_1.root'
  )
)

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.maxEvents = cms.untracked.PSet( 
    input = cms.untracked.int32(-1) 
)

process.analyzeBasicPat = cms.EDAnalyzer("MyZPeakAnalyzer",
  muonSrc = cms.untracked.InputTag("slimmedMuons"),                  
  elecSrc = cms.untracked.InputTag("slimmedElectrons"),
)

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('myZPeakCRAB.root')
                                   )

process.p = cms.Path(process.analyzeBasicPat)

