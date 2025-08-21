# Customisation Modules

This `customiser.py` module uses the `custom_jme_cff.py` to customise the nanoAOD. `patchVertexTable(process)` remove decay length significance cut and `reclusterJets(process, runOnMC)` removes all default transverse momenta cuts in for AK4 jets set by `jets_cff.py` and reclusters the jets with customised transverse momenta cuts.  

## The customisation module: `custom_jme_cff.py`

The `custom_jme__cff.py` is `nanoAOD` customisation module focusing on the Jet and MET (JME) collections.

1. `config_genjets` are lists which allows one to write out additional generator-level jet collection that are available in `miniAOD` to write to `nanoAOD`. By default, the following collections are saved in `nanoAOD`:
	1. `ak4jets` - `GenJet` in `nanoAOD`, `slimmedGenJets` in `miniAOD`
	2. `ak8jets` - `GenJetAK8` in `nanoAOD`, `slimmedGenJetsAK8` in `miniAOD`

	Additional collection that we can add to the `nanoAOD` is - `ak6jets` from the `custom_jme_cff.py` which is not added to `nanoAOD` by default.

2. `config_recojets` are lists which allow one to write out additional reconstructed jet collection that are available in `miniAOD` to write to `nanoAOD`. By default, the following collection are saved in `nanoAOD`:
	1. `ak4pfchs` - `Jet` in `nanoAOD`, `slimmedJets` in `miniAOD`
	2. `ak8pfpuppi` - `FatJet` in `nanoAOD`, `slimmedJetsAK8` in `miniAOD`
	Additional collection that we can add to the `nanoAOD`: `ak4calo`, `ak4pf`, `ak4pfpuppi`, `ak8pf`.
3. `cms.PSet` are used to define the different variables we want to store in our `nanoAOD` for jets and gen jets. For example:
```python
GENJETVARS = cms.PSet(P4Vars,
  nConstituents   = jetTable.variables.nConstituents,
)
PFJETVARS = cms.PSet(P4Vars,
  rawFactor       = Var("1.-jecFactor('Uncorrected')",float,doc="1 - Factor to get back to raw pT",precision=6),
  area            = jetTable.variables.area,
  chHEF           = jetTable.variables.chHEF,
  neHEF           = jetTable.variables.neHEF,
  chEmEF          = jetTable.variables.chEmEF,
  neEmEF          = jetTable.variables.neEmEF,
  muEF            = jetTable.variables.muEF,
  hfHEF           = Var("HFHadronEnergyFraction()",float,doc = "hadronic energy fraction in HF",precision = 6),
  hfEmEF          = Var("HFEMEnergyFraction()",float,doc = "electromagnetic energy fraction in HF",precision = 6),
  nMuons          = jetTable.variables.nMuons,
  nElectrons      = jetTable.variables.nElectrons,
  nConstituents   = jetTable.variables.nConstituents,
  nConstChHads    = Var("chargedHadronMultiplicity()",int,doc="number of charged hadrons in the jet"),
  nConstNeuHads   = Var("neutralHadronMultiplicity()",int,doc="number of neutral hadrons in the jet"),
  nConstHFHads    = Var("HFHadronMultiplicity()", int,doc="number of HF hadrons in the jet"),
  nConstHFEMs     = Var("HFEMMultiplicity()",int,doc="number of HF EMs in the jet"),
  nConstMuons     = Var("muonMultiplicity()",int,doc="number of muons in the jet"),
  nConstElecs     = Var("electronMultiplicity()",int,doc="number of electrons in the jet"),
  nConstPhotons   = Var("photonMultiplicity()",int,doc="number of photons in the jet"),
```
Here we see