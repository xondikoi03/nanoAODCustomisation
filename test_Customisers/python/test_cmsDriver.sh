TAG=v1

function cmsDriverGenerator{
    cmsDriver.py NANO --python_filename test_${TAG}_$1_MC_config.py \
        --fileout ../outputfiles/nanoMCTest.root -s NANO --mc --conditions $2 --era $3 \
        --eventcontent NANOAODSIM --datatier NANOAODSIM \
        --customise_commands="from PhysicsTools.NanoAOD.nano_cff.py import ; \
        process.add_(cms.Service('InitRootHandlers', EnableIMT = cms.untracked.bool(False))); \
        process.MessageLogger.cerr.FwkReport.reportEvery=1000; \
        process.load("FWCore.MessageLogger.MessageLogger_cfi"); \
        process.MessageLogger.cerr.threshold = "INFO"; \
        process.MessageLogger.categories.append("CMSOPENDATAPIPELINE"); \
        process.MessageLogger.cerr.INFO = cms.untracked.PSet(limit=cms.untracked.int32(-1));" \ 
        --nThreads 16 -n -1 --no_exec
}

cmsDriverGenerator 2016ULpostVFP    106X_mcRun2_asymptotic_v17  Run2_2016,run2_nanoAOD_106Xv2   MC