def patchVertexTable(process):
    """
    _patchVertexTable_

    Patch the vertexTable to remove decay length significance cut
    """
    import FWCore.ParameterSet.Config as cms

    process.vertexTable.dlenSigMin = cms.double(0)

    return process


def reclusterJets(process, runOnMC):

    if (runOnMC):
        from PhysicsTools.PatAlgos.tools.jetCollectionTools import GenJetAdder
        from PhysicsTools.NanoAOD.custom_jme_cff import ReclusterAK4GenJets, AddVariablesForAK4GenJets
    from PhysicsTools.PatAlgos.tools.jetCollectionTools import RecoJetAdder
    from PhysicsTools.NanoAOD.custom_jme_cff import ReclusterAK4CHSJets

    ###########################################################################
    # Remove default pt cuts for all AK4 jets set in jets_cff.py
    ###########################################################################

    process.finalJets.cut             = "" # 15 -> 10
    # process.finalJetsAK8.cut          = "" # 170 -> 170
    process.genJetTable.cut           = "" # 10 -> 8
    process.genJetFlavourTable.cut    = "" # 10 -> 8
    # process.genJetAK8Table.cut        = "" # 100 -> 80
    # process.genJetAK8FlavourTable.cut = "" # 100 -> 80

    if (runOnMC):
        ###########################################################################
        # Recluster AK4 GEN jets
        ###########################################################################
        genJA = GenJetAdder()
        # This yields jets with pT > 3 GeV
        # See https://github.com/cms-sw/cmssw/blob/3e2a9e5279b56471f0cd8c7ae1ea0aac28800508/PhysicsTools/NanoAOD/python/custom_jme_cff.py#L924
        process = ReclusterAK4GenJets(process, genJA)
        process = AddVariablesForAK4GenJets(process)

    ###########################################################################
    # Recluster AK4 CHS jets and replace "slimmedJets"
    ###########################################################################
    recoJA = RecoJetAdder(runOnMC=runOnMC)
    # This yields jets with pT >= 8 GeV and for MC also jets with pT < 8 GeV if matched to an AK4GenJet"
    # See https://github.com/cms-sw/cmssw/blob/3e2a9e5279b56471f0cd8c7ae1ea0aac28800508/PhysicsTools/NanoAOD/python/custom_jme_cff.py#L631
    process = ReclusterAK4CHSJets(process, recoJA, runOnMC)

    return process

