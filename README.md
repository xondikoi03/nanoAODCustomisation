# nanoAODCustomisation

This particular setup was run on a `CMSSW_10_6_30` docker container. 

## IMPORTANT: LXPLUS OR CERN-VM USERS:

You shall run the following commands:
```shell
cmsrel CMSSW_10_6_30
cd CMSSW_10_6_30/src/
cmsenv
```

## Setup:

The following steps shall be done to setup the environment and build the CMSSW EDM modules:

1. SCRAM build the EDM modules (or compile any other modules relevant for production.)

```shell
scram b -j 8
```
2. Run the `cmsDriver.py` with customised commands for a private version of `nanoAOD`.

```shell
cd $CMSSW_BASE/src/nanoAODCustomisation/SoftCharmTagging/test
source softCharmTagging_cmsDrivers.sh
```

3. `cmsRun` the config file to produce the desired custom `nanoAOD`. (I have used the `softCharmTaggingNano_v2_2016ULpostVFP_MC_cfg.py`)

```shell
cmsRun softCharmTaggingNano_v2_2016ULpostVFP_MC_cfg.py
```
> **Note:** The `miniAOD` and `nanoAOD` datasets from CERN open data portal are located in the `$CMSSW_BASE/src/nanoAODCustomisation/SoftCharmTagging/test/datasets` directory.

## AnalysisCodes for custom nanoAODs:

1. In the `$CMSSW_BASE/src/nanoAODCustomisation/SoftCharmTagging/AnalysisCodes/custom_nanoAOD/` directory, the analysis files are located. Compile them from the `ROOT` prompt:
```shell
.L nanoAna2.C+
```
2. Next, the driver file is executed to feed the appropriate values to the input-output parameters and run the analysis.
```shell
.x driver.C(0)
```
3. This will produce histograms from the custom nanoAODs (for now only `nJets`, `Jet_pt`, `Jet_eta`, `Jet_phi`).


## AnalysisCodes for centrally produced nanoAODs:

1. In the `$CMSSW_BASE/src/nanoAODCustomisation/SoftCharmTagging/AnalysisCodes/central_nanoAOD/` directory, the analysis files are located. Compile them from the `ROOT` prompt:
```shell
.L nanoAna3.C+
```
2. Next, the driver file is executed to feed the appropriate values to the input-output parameters and run the analysis.
```shell
.x driver.C(0)
```
3. This will produce histograms from the central nanoAODs (for now only `nJets`, `Jet_pt`, `Jet_eta`, `Jet_phi`).

## Making Plots:

1. Navigate to `$CMSSW_BASE/src/nanoAODCustomisation/SoftCharmTagging/AnalysisCodes/Plots/`.
2. For plots from custom nanoAOD histograms, run this in the `ROOT` prompt:
```shell
.x custom_graphing.C
```
3. For plots from central nanoAOD histograms, run this in the `ROOT` prompt:
```shell
.x central_graphing.C
```  

