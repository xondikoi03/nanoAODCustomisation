# NanoAODCustomisation

Scripts and tools for NanoAOD customisation

## Setup

```shell
cmsrel CMSSW_10_6_26
cd CMSSW_10_6_26/src
cmsenv
```

Then clone this repository in the current working directory.

```shell
scram b
cd $CMSSW_BASE/src/NanoAODCustomisation/SoftCharmTagging/test
source softCharmTagging_cmsDrivers.sh
```

This will provide you with a list of configs you can run.

## Production

```shell
voms-proxy-init --rfc --voms cms --valid 192:00
source /cvmfs/cms.cern.ch/common/crab-setup.sh
cd $CMSSW_BASE/src/NanoAODCustomisation/SoftCharmTagging/test
./runSoftCharmTaggingOnGrid.py -d samples.yml -o crab_tasks -s T3_CH_PSI
```

Then the jobs can be submitted:

```shell
cd crab_tasks
crab submit [yourcfg.py]
```
