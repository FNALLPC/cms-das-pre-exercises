import FWCore.ParameterSet.Config as cms

process = cms.Process("Test")

process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring(

			'file:/uscms_data/d2/malik/CMSDAS2012/YOURWORKINGAREA/CMSSW_4_2_8/src/crab_2011a/res/simple_PAT_data_MuEle_1_1_hMR.root',			
			'file:/uscms_data/d2/malik/CMSDAS2012/YOURWORKINGAREA/CMSSW_4_2_8/src/crab_2011b/res/simple_PAT_data_MuEle_1_1_FFG.root',
                        'file:/uscms_data/d2/malik/CMSDAS2012/YOURWORKINGAREA/CMSSW_4_2_8/src/crab_2011b/res/simple_PAT_data_MuEle_2_1_3MA.root',                                      
                        'file:/uscms_data/d2/malik/CMSDAS2012/YOURWORKINGAREA/CMSSW_4_2_8/src/crab_2011b/res/simple_PAT_data_MuEle_3_1_f1d.root',                                      
                        'file:/uscms_data/d2/malik/CMSDAS2012/YOURWORKINGAREA/CMSSW_4_2_8/src/crab_2011b/res/simple_PAT_data_MuEle_4_1_fhn.root',                                      
                        'file:/uscms_data/d2/malik/CMSDAS2012/YOURWORKINGAREA/CMSSW_4_2_8/src/crab_2011b/res/simple_PAT_data_MuEle_5_1_RTu.root',                                      
                        'file:/uscms_data/d2/malik/CMSDAS2012/YOURWORKINGAREA/CMSSW_4_2_8/src/crab_2011b/res/simple_PAT_data_MuEle_6_1_HOT.root',                                      
                        'file:/uscms_data/d2/malik/CMSDAS2012/YOURWORKINGAREA/CMSSW_4_2_8/src/crab_2011b/res/simple_PAT_data_MuEle_7_1_9Tx.root',                                      
                        'file:/uscms_data/d2/malik/CMSDAS2012/YOURWORKINGAREA/CMSSW_4_2_8/src/crab_2011b/res/simple_PAT_data_MuEle_8_1_KxU.root'


  )
)

process.MessageLogger = cms.Service("MessageLogger")

process.analyzeBasicPat = cms.EDAnalyzer("MyZPeakAnalyzer",

  electronSrc = cms.untracked.InputTag("selectedPatElectrons"),
  muonSrc     = cms.untracked.InputTag("selectedPatMuons"),                                             
)

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('myZPeakCRAB.root')
                                   )

process.p = cms.Path(process.analyzeBasicPat)
