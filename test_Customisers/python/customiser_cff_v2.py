import FWCore.ParameterSet.Config as cms
from PhysicsTools.NanoAOD.nano_cff import *

def default_TauIdsCustomisation(process):
    print("###########################################")
    print("Default TauID Customisations")
    print("###########################################")
    from PhysicsTools.NanoAOD.nano_cff import nanoAOD_activateVID
    process = nanoAOD_activateVID(process)    
    # By Default this adds only "deepTauId2017v2p1"
    from PhysicsTools.NanoAOD.nano_cff import nanoAOD_addTauIds    
    process = nanoAOD_addTauIds(process)

    # By Default this add only "2017v2", "dR0p32017v2", "newDM2017v2", "againstEle2018"

    from PhysicsTools.NanoAOD.nano_cff import nanoAOD_addBoostedTauIds
    process = nanoAOD_addBoostedTauIds(process)

    # Let's see how this changes or adds anything new to the tau table
    return process

def Customise_TauIdsCustomisation(process):
    print("###########################################")
    print("Running TauID Customisations")
    print("###########################################")
    from PhysicsTools.NanoAOD.nano_cff import nanoAOD_activateVID
    process = nanoAOD_activateVID(process)
    import RecoTauTag.RecoTau.tools.runTauIdMVA as tauIdConfig
    def nanoAOD_customiseAddTauIds(process):
        updatedTauName = "slimmedTausUpdatedCustom"
        tauIdEmbedder = tauIdConfig.TauIDEmbedder(
            process, cms, debug=False, updatedTauName=updatedTauName,
            toKeep = ["deepTau2017v1", "deepTau2017v2"])
        tauIdEmbedder.runTauID()
        process.patTauMVAIDsSeq.index(getattr(process, updatedTauName)), process.rerunMvaIsolationSequence
        return process
    process = nanoAOD_customiseAddTauIds(process)

    def nanoAOD_customiseAddBoostedIds(process):
        updatedBoostedTauName = "slimmedTausBoostedNewIDCustom"
        boostedTauIdEmbedder = tauIdConfig.TauIDEmbedder(process, cms, debug=False, 
                                                        originalTauName = "slimmedTausBoosted",
                                                        updatedTauName = updatedBoostedTauName,
                                                        postfix="Boosted",
                                                        toKeep = [ "2017v2", "dR0p32017v2", "newDM2017v2", "againstEle2018",])
        boostedTauIdEmbedder.runTauID()
        process.boostedTauSequence.insert(process.boostedTauSequence.index(process.finalBoostedTaus),
                                        process.rerunMvaIsolationSequenceBoosted)

        process.boostedTauSequence.insert(process.boostedTauSequence.index(process.finalBoostedTaus),
                                        getattr(process, updatedBoostedTauName))

        return process    
    process = nanoAOD_customiseAddBoostedIds(process)

    return process



