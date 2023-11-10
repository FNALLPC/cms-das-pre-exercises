import os
from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'cmsdas_zpeak_test0'
config.General.workArea = 'crabsubmit'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = os.path.expandvars('$CMSSW_BASE/src/MyAnalysis/LearnCMSSW/test/zpeak_cfg.py')
config.JobType.allowUndistributedCMSSW = True

config.section_("Data")
config.Data.inputDataset = '/DoubleMuon/Run2016C-03Feb2017-v1/MINIAOD'
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 50
config.Data.lumiMask = 'https://cms-service-dqmdc.web.cern.ch/CAF/certification/Collisions16/13TeV/Cert_271036-275783_13TeV_PromptReco_Collisions16_JSON.txt'
config.Data.runRange = '275776-275782'

config.section_("Site")
config.Site.storageSite = 'T3_US_FNALLPC'
