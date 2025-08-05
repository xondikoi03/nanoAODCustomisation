# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: NANO --python_filename softCharmTaggingNano_v2_2016ULpostVFP_MC_cfg.py --fileout file:tree.root -s NANO --mc --conditions 106X_mcRun2_asymptotic_v17 --era Run2_2016,run2_nanoAOD_106Xv2 --eventcontent NANOAODSIM --datatier NANOAODSIM --customise NanoAODCustomisation/SoftCharmTagging/Customisers.patchVertexTable --customise_commands=process.add_(cms.Service('InitRootHandlers',     EnableIMT = cms.untracked.bool(False)));     process.MessageLogger.cerr.FwkReport.reportEvery=1000;     process.NANOAODSIMoutput.fakeNameForCrab=cms.untracked.bool(True);     from NanoAODCustomisation.SoftCharmTagging.Customisers import reclusterJets;     reclusterJets(process, runOnMC=True) --nThreads 2 -n -1 --no_exec
import FWCore.ParameterSet.Config as cms
import FWCore.Utilities.FileUtils as FileUtils

from Configuration.Eras.Era_Run2_2016_cff import Run2_2016
from Configuration.Eras.Modifier_run2_nanoAOD_106Xv2_cff import run2_nanoAOD_106Xv2

process = cms.Process('NANO',Run2_2016,run2_nanoAOD_106Xv2)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('PhysicsTools.NanoAOD.nano_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10000)
)

# Input source
files = FileUtils.loadListFromFile("datasets/CMS_mc_RunIISummer20UL16MiniAODv2_TTToHadronic_TuneCP5_13TeV-powheg-pythia8_MINIAODSIM_106X_mcRun2_asymptotic_v17-v1_130000_file_index.txt")
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(*files),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('NANO nevts:-1'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.NANOAODSIMoutput = cms.OutputModule("NanoAODOutputModule",
    compressionAlgorithm = cms.untracked.string('LZMA'),
    compressionLevel = cms.untracked.int32(9),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('NANOAODSIM'),
        filterName = cms.untracked.string('')
    ),
    fileName = cms.untracked.string('../output_files/test2016.root'),
    outputCommands = process.NANOAODSIMEventContent.outputCommands
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '106X_mcRun2_asymptotic_v17', '')

# Path and EndPath definitions
process.nanoAOD_step = cms.Path(process.nanoSequenceMC)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.NANOAODSIMoutput_step = cms.EndPath(process.NANOAODSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.nanoAOD_step,process.endjob_step,process.NANOAODSIMoutput_step)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

#Setup FWK for multithreaded
process.options.numberOfThreads=cms.untracked.uint32(16)
process.options.numberOfStreams=cms.untracked.uint32(0)
process.options.numberOfConcurrentLuminosityBlocks=cms.untracked.uint32(1)

# customisation of the process.

# Automatic addition of the customisation function from PhysicsTools.NanoAOD.nano_cff
from PhysicsTools.NanoAOD.nano_cff import nanoAOD_customizeMC 

#call to customisation function nanoAOD_customizeMC imported from PhysicsTools.NanoAOD.nano_cff
process = nanoAOD_customizeMC(process)

# Automatic addition of the customisation function from NanoAODCustomisation.SoftCharmTagging.Customisers
from NanoAODCustomisation.SoftCharmTagging.Customisers import patchVertexTable 

#call to customisation function patchVertexTable imported from NanoAODCustomisation.SoftCharmTagging.Customisers
process = patchVertexTable(process)

# End of customisation functions

# Customisation from command line

process.add_(cms.Service('InitRootHandlers',     EnableIMT = cms.untracked.bool(False)));     process.MessageLogger.cerr.FwkReport.reportEvery=1000;     process.NANOAODSIMoutput.fakeNameForCrab=cms.untracked.bool(True);     from NanoAODCustomisation.SoftCharmTagging.Customisers import reclusterJets;     reclusterJets(process, runOnMC=True)
# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion
