import FWCore.ParameterSet.Config as cms
from PhysicsTools.NanoAOD.nano_cff import *

def nanoAODCustomise_DeepInfoAK8(process):

    from PhysicsTools.PatAlgos.slimming.puppiForMET_cff import makePuppiesFromMiniAOD
    makePuppiesFromMiniAOD(process, True)
    process.puppiNoLep.useExistingWeights = False
    process.puppi.useExistingWeights = False

    from PhysicsTools.NanoAOD.nano_cff import nanoAOD_activateVID
    process = nanoAOD_activateVID(process)
    # Switches for DeepInfoAK8 (only AK8PFPuppi - 106X)
    print("###########################################")
    print("Re-running all the Deep-tagging algorithms")
    print("###########################################")

    nanoAOD_addDeepInfoAK8_switch = cms.PSet(
        nanoAOD_addDeepBTag_switch = cms.untracked.bool(False),
        nanoAOD_addDeepBoostedJet_switch = cms.untracked.bool(True),
        nanoAOD_addDeepDoubleX_switch = cms.untracked.bool(True),
        nanoAOD_addDeepDoubleXV2_switch = cms.untracked.bool(True),
        nanoAOD_addParticleNet_switch = cms.untracked.bool(True),
        nanoAOD_addParticleNetMass_switch = cms.untracked.bool(True),
        jecPayload=cms.untracked.string("AK8PFPuppi")
    )
    from PhysicsTools.NanoAOD.nano_cff import nanoAOD_addDeepInfoAK8
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

    from PhysicsTools.NanoAOD.nano_cff import nanoAOD_addTauIds  
    from PhysicsTools.NanoAOD.nano_cff import nanoAOD_addBoostedTauIds
    
    addTauIds_switch = cms.PSet(
        nanoAOD_addTauIds_switch = cms.untracked.bool(True),
        nanoAOD_addBoostedTauIds_switch = cms.untracked.bool(True)
    ) # For run2_nanoAOD_106Xv2
    
    ((run2_nanoAOD_106Xv2 | run2_miniAOD_devel | run2_tau_ul_2016 | run2_tau_ul_2018) & \
    (~(run2_nanoAOD_94X2016 | run2_nanoAOD_94XMiniAODv1 | run2_nanoAOD_94XMiniAODv2 | run2_nanoAOD_102Xv1 | run2_nanoAOD_106Xv1))).toModify(addTauIds_switch, nanoAOD_addTauIds_switch = False)
    (run2_miniAOD_80XLegacy | run2_nanoAOD_92X | run2_nanoAOD_94X2016 | run2_nanoAOD_94XMiniAODv1 | run2_nanoAOD_94XMiniAODv2 | run2_nanoAOD_102Xv1 | run2_nanoAOD_106Xv1).toModify(addTauIds_switch, nanoAOD_addBoostedTauIds_switch = False)

    if addTauIds_switch.nanoAOD_addTauIds_switch:
        process = nanoAOD_addTauIds(process)
    if addTauIds_switch.nanoAOD_addBoostedTauIds_switch:
        process = nanoAOD_addBoostedTauIds(process)
    return process



    