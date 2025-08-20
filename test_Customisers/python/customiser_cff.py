import FWCore.ParameterSet.Config as cms
from PhysicsTools.NanoAOD.nano_cff import *

def nanoAODCustomise_DeepInfoAK8(process):
    """
        Customization function for NanoAOD V1.

        Adding Deep tagging information for ak8Jets.
    """
    # Switches for DeepInfoAK8 (only AK8PFPuppi - 106X)

    print("Customising ")
    nanoAOD_addDeepInfoAK8_switch = cms.PSet(
        nanoAOD_addDeepBTag_switch = cms.untracked.bool(True),
        nanoAOD_addDeepBoostedJet_switch = cms.untracked.bool(True),
        nanoAOD_addDeepDoubleX_switch = cms.untracked.bool(True),
        nanoAOD_addDeepDoubleXV2_switch = cms.untracked.bool(True),
        nanoAOD_addParticleNet_switch = cms.untracked.bool(True),
        nanoAOD_addParticleNetMass_switch = cms.untracked.bool(True),
        jecPayload=cms.untracked.string("AK8PFPuppi")
    )

    process = nanoAOD_addDeepInfoAK8(
        process,
        addDeepBTag=nanoAOD_addDeepInfoAK8_switch.nanoAOD_addDeepBTag_switch,
        addDeepBoostedJet=nanoAOD_addDeepInfoAK8_switch.nanoAOD_addDeepBoostedJet_switch,
        addDeepDoubleX=nanoAOD_addDeepInfoAK8_switch.nanoAOD_addDeepDoubleX_switch,
        addDeepDoubleXV2=nanoAOD_addDeepInfoAK8_switch.nanoAOD_addDeepDoubleXV2_switch,
        addParticleNet=nanoAOD_addDeepInfoAK8_switch.nanoAOD_addParticleNet_switch,
        addParticleNetMass=nanoAOD_addDeepInfoAK8_switch.nanoAOD_addParticleNetMass_switch,
        jecPayload=nanoAOD_addDeepInfoAK8_switch.jecPayload
    )
    return process



    