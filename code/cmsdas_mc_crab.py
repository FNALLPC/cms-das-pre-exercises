from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'cmsdas_minbias_test0'
config.General.workArea = 'crabsubmit'

config.section_("JobType")
config.JobType.pluginName = 'PrivateMC'
config.JobType.psetName = 'cmsdas_minbias_cfg.py'
config.JobType.allowUndistributedCMSSW = True

config.section_("Data")
config.Data.outputPrimaryDataset = 'MinBias'
config.Data.splitting = 'EventBased'
config.Data.unitsPerJob = 20
NJOBS = 10  # This is not a configuration parameter, but an auxiliary variable that we use in the next line.
config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.publication = True
config.Data.outputDatasetTag = 'MinBias_TuneCP5_13p6TeV-pythia8_cmsdas2024_test0'

config.section_("Site")
config.Site.storageSite = 'T3_US_FNALLPC'