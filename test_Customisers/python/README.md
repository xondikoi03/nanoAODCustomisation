# Customisation Modules

In this directory we will make use of the `nano_cff.py` file to test out customisations in nanoAOD. This will be only available in the `devel` branch and will not be pushed to the `master` branch.

## `nano_cff.py`

The <a href="https://github.com/cms-sw/cmssw/blob/CMSSW_10_6_X/PhysicsTools/NanoAOD/python/nano_cff.py">`nano_cff.py`</a> is a customisation module that defines which physics objects are to be saved.

### `nanoAOD_activateVID(process)`
---
This is a function that configures the **ValueMap-based Identification(VID)** framework for electrons and photons in the nanoAOD. In context of **EGamma VID**, the information of an particle being identified(ID) as an electron or a photon is stored as a float or a boolean in the ValueMap (`edm::ValueMap`). 

This function activates the electrons/photons VID for miniAOD, registers the electron/photon ID modules, ensures that the electron/photon ID sequence runs before the bitmap calculations and does era-specific modifications.

1. Switch on Electron VID Producer: `switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)` function activates the electron VID producer for miniAOD input format. 

2. Setup Electron ID Modules: `setupAllVIDIdsInModule(process,modname,setupVIDElectronSelection)` function registers ID modules with the process. This is looped over all the electron ID modules.
```python
for modname in electron_id_modules_WorkingPoints_nanoAOD.modules:
    
    setupAllVIDIdsInModule(process,modname,setupVIDElectronSelection)
```
3. Insert the Electron ID modules: `process.electronSequence.insert(process.electronSequence.index(process.bitmapVIDForEle), process.egmGsfElectronIDSequence)` which ensures that the electron ID sequence is runs before the bitmap calculation for the electrons. 

4. Era-dependent modifications: 
```python
    for modifier in run2_miniAOD_80XLegacy,
    run2_nanoAOD_94XMiniAODv1,
    run2_nanoAOD_94XMiniAODv2,
    run2_nanoAOD_94X2016,
    run2_nanoAOD_102Xv1,
    run2_nanoAOD_106Xv1:

        modifier.toModify(process.electronMVAValueMapProducer, srcMiniAOD = "slimmedElectronsUpdated")

        modifier.toModify(process.egmGsfElectronIDs, physicsObjectSrc = "slimmedElectronsUpdated")

    run2_nanoAOD_106Xv2.toModify(process.electronMVAValueMapProducer, src = "slimmedElectrons")
    run2_nanoAOD_106Xv2.toModify(process.egmGsfElectronIDs, physicsObjectSrc = "slimmedElectrons")
```
This part makes changes depending upon the different eras of miniAOD - the input source for electron MVA and ID modules to `slimmedElectronsUpdated`. Special case for `106Xv2` era, which uses `slimmedElectrons`.

5. Similarly for photons VID are done:
```python
    switchOnVIDPhotonIdProducer(process,DataFormat.MiniAOD) # do not call this to avoid resetting photon IDs in VID, if called before inside makePuppiesFromMiniAOD
    for modname in photon_id_modules_WorkingPoints_nanoAOD.modules:
        setupAllVIDIdsInModule(process,modname,setupVIDPhotonSelection)
    process.photonSequence.insert(process.photonSequence.index(bitmapVIDForPho),process.egmPhotonIDSequence)
    for modifier in run2_miniAOD_80XLegacy,run2_nanoAOD_94XMiniAODv1,run2_nanoAOD_94XMiniAODv2,run2_nanoAOD_94X2016 ,run2_nanoAOD_102Xv1:
        modifier.toModify(process.photonMVAValueMapProducer, srcMiniAOD = "slimmedPhotonsTo106X")
        modifier.toModify(process.egmPhotonIDs, physicsObjectSrc = "slimmedPhotonsTo106X")
```
In summary, this function does the following:

- Switches on VID Producer for Electron/Photons.
- Loops over all the Electron/Photon ID working point modules and looks for Electron/Photon ID definitions (basically all the selection criteria).
- Inserts the Electron/Photon ID sequence runs before the bitmap calculations.
- Makes Era-Dependent changes or any special cases for specific eras.

### `nanoAOD_addDeepInfo`
---
This function configures the CMSSW process to rerun deep-learning based flavor-tagging and jet substructure algorithms for **AK4 jets** in nanoAOD production. It takes in boolean values for which tagging algorithms to re-run in the process and updates the jet collection accordingly. 

1. Initialise Discriminator List: `_btagDiscriminators=[]` which creates an empty list for collecting all b-tagging and substructure dicriminators to be recalculated.

2. Add DeepCSV Discriminators: If `addDeepBTag==True`, then add the DeepCSV discriminators for `b`, `bb` and `c` quarks.
```python
if addDeepBTag:
    print("Updating process to run DeepCSV btag")
    _btagDiscriminators += ['pfDeepCSVJetTags:probb','pfDeepCSVJetTags:probbb','pfDeepCSVJetTags:probc']
``` 
3. Add DeepFlavour Discriminators: If `addDeepFlavour==True` then add the DeepFlavour discriminators for b, bb and c quarks.
```python
if addDeepFlavour:
    print("Updating process to run DeepFlavour btag")
        _btagDiscriminators +=['pfDeepFlavourJetTags:probb','pfDeepFlavourJetTags:probbb','pfDeepFlavourJetTags:problepb','pfDeepFlavourJetTags:probc']
```
If none of the above discriminators are requested or set to `TRUE`, the function exits without modifying the process.
```python
if len(_btagDiscriminators)==0: return process
```
4. Updating the jet collection: The `updateJetCollection` function reruns all the selected discriminators on the AK4Jet collection with the specificed Jet energy corrections(`AK4PFchs`).
```python
    print("Will recalculate the following discriminators: "+", ".join(_btagDiscriminators))
    updateJetCollection(
               process,
               jetSource = cms.InputTag('slimmedJets'),
               jetCorrections = ('AK4PFchs', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute','L2L3Residual']), 'None'),
               btagDiscriminators = _btagDiscriminators,
               postfix = 'WithDeepInfo',
           )
    process.load("Configuration.StandardSequences.MagneticField_cff")
    process.jetCorrFactorsNano.src="selectedUpdatedPatJetsWithDeepInfo"
    process.updatedJets.jetSource="selectedUpdatedPatJetsWithDeepInfo"
    return process
```
### `nanoAOD_addDeepInfoAK8`
---
This function configures the CMSSW process to rerun deep-learning based flavor-tagging and jet substructure algorithms for fat-jets or **AK8 jets** in nanoAOD production. It takes in boolean values for which tagging algorithms to re-run in the process and updates the jet collection accordingly. 

1. Initialise Discriminator List:
`_btagDiscriminators=[]` which creates an empty list for collecting all b-tagging and substructure dicriminators to be recalculated.

2. DeepCSV Discriminators: If `addDeepBTag==True`, then DeepCSV b-tagging dicriminators are added for AK8 jets.

```python
if addDeepBTag:
    print("Updating process to run DeepCSV btag to AK8 jets")
    _btagDiscriminators += ['pfDeepCSVJetTags:probb','pfDeepCSVJetTags:probbb']
```
3. DeepBoostedJet Discriminators: If `addDeepBoostedJet==True`, then DeepBoostedJet discriminators are imported and added for AK8Jets.

```python
if addDeepBoostedJet:
    print("Updating process to run DeepBoostedJet on datasets before 103X")
    
    from RecoBTag.ONNXRuntime.pfDeepBoostedJet_cff import _pfDeepBoostedJetTagsAll as pfDeepBoostedJetTagsAll
    
    _btagDiscriminators += pfDeepBoostedJetTagsAll
```
4. ParticleNet Discriminators: If `addParticleNet==True`, then ParticleNet discriminators are imported and added for AK8Jets. 
```python
if addParticleNet:
    print("Updating process to run ParticleNet before it's included in MiniAOD")
    from RecoBTag.ONNXRuntime.pfParticleNet_cff import _pfParticleNetJetTagsAll as pfParticleNetJetTagsAll
    _btagDiscriminators += pfParticleNetJetTagsAll
```
5. ParticleNet Mass Regression Outputs: If `addParticleNetMass==True`, then imports and adds all PaticleNet mass regression outputs for AK8Jets.
```python
if addParticleNetMass:
    from RecoBTag.ONNXRuntime.pfParticleNet_cff import _pfParticleNetMassRegressionOutputs
    _btagDiscriminators += _pfParticleNetMassRegressionOutputs
```
6. DeepDoubleX Discriminators: If `addDeepDoubleX==True`, then imports and adds all discriminators for Hbb and Hcc tagging.
```python
if addDeepDoubleX:
    print("Updating process to run DeepDoubleX on datasets before 104X")
        
    _btagDiscriminators += ['pfDeepDoubleBvLJetTags:probHbb', \
        'pfDeepDoubleCvLJetTags:probHcc', \
        'pfDeepDoubleCvBJetTags:probHcc', \
        'pfMassIndependentDeepDoubleBvLJetTags:probHbb', 'pfMassIndependentDeepDoubleCvLJetTags:probHcc', 'pfMassIndependentDeepDoubleCvBJetTags:probHcc']
```
7. DeepDoubleXv2 Discriminators: If `addDeepDoubleXv2==True`, then imports and adds all DeepDoubleXv2 discriminators.
```python
if addDeepDoubleXV2:
    print("Updating process to run DeepDoubleXv2 on datasets before 11X")
    _btagDiscriminators += [
        'pfMassIndependentDeepDoubleBvLV2JetTags:probHbb',
        'pfMassIndependentDeepDoubleCvLV2JetTags:probHcc',
        'pfMassIndependentDeepDoubleCvBV2JetTags:probHcc'
        ]
```
If none of the above discriminators are requested or set to `TRUE`, the function exits without modifying the process.
```python
if len(_btagDiscriminators)==0: return process
```
8. Updating the jet collection: The `updateJetCollection` function reruns all the selected discriminators on the AK8Jet collection with the specificed Jet energy corrections(`jecPayload`).
```python
print("Will recalculate the following discriminators on AK8 jets: "+", ".join(_btagDiscriminators))
    updateJetCollection(
       process,
       jetSource = cms.InputTag('slimmedJetsAK8'),
       pvSource = cms.InputTag('offlineSlimmedPrimaryVertices'),
       svSource = cms.InputTag('slimmedSecondaryVertices'),
       rParam = 0.8,
       jetCorrections = (jecPayload.value(), cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual']), 'None'),
       btagDiscriminators = _btagDiscriminators,
       postfix='AK8WithDeepInfo',
       printWarning = False
       )
    process.jetCorrFactorsAK8.src="selectedUpdatedPatJetsAK8WithDeepInfo"
    process.updatedJetsAK8.jetSource="selectedUpdatedPatJetsAK8WithDeepInfo"
    return process
```
### `nanoAOD_CustomiseCommon(process)`:


### `nanoAOD_CustomiseMC(process)`:

### `nanoAOD_CustomiseData(process)`:

## `electrons_cff.py`

The following objects can be found in <a href="https://github.com/cms-sw/cmssw/blob/CMSSW_10_6_X/PhysicsTools/NanoAOD/python/electrons_cff.py">`electrons_cff.py`</a> that are used in the function:

`electronSequence`: A CMSSW sequence(`cms.Sequence` object) that defines an ordered set of electron-related processing modules in the nanoAOD workflow. 

```python
electronSequence = cms.Sequence(
    bitmapVIDForEle + bitmapVIDForEleHEEP + isoForEle + 
    ptRatioRelForEle + seedGainEle +
    slimmedElectronsWithUserData + finalElectrons)
```
`bitmapVIDForEle`: This defines a CMSSW EDProducer module, `EleVIDBNestedWPBitmapProducer` that creates a bitmap encoding the results of electron ID working points. The module checks which working points each electron passes and encodes this information in a bitmap. The bitmap is stored in the nanoAOD. 

```python
bitmapVIDForEle = cms.EDProducer("EleVIDNestedWPBitmapProducer",
    src = cms.InputTag("slimmedElectrons"),
    WorkingPoints = electron_id_modules_WorkingPoints_nanoAOD.WorkingPoints,
)
```
> **Electron ID Working Points**: These are predefined sets of selection criteria (passCuts) used in the identification of electrons in analysis. Some of the common working points are: **veto**, **loose**, **medium** and **tight**.

