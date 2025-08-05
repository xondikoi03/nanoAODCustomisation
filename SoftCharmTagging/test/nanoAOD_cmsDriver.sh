# don't shebang, SOURCE

TAG="v1" 

function mycmsDriver(){
    cmsDriver.py NANO --python_filename test_${TAG}_$1_MC_config.py --fileout ../output_files/nanoTest.root -s NANO --mc --conditions $2 --era $3 --eventcontent NANOAODSIM --datatier NANOAODSIM --nThreads 16 -n -1 --no_exec
    }
mycmsDriver 2016ULpostVFP 106X_mcRun2_asymptotic_v17 Run2_2016,run2_nanoAOD_106Xv2