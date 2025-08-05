// Creates Ana.C and Ana.h Files 
// Original Author: Raj Handqiue
// ROOT Framework - CERN

#include <iostream>
#include "TFile.h"
#include "TTree.h"

using namespace std;

void anafile(){
  
  TFile *file = TFile::Open("../output_files/CMS_mcRunIISummer20UL16MiniAODv2_TTToHadronic_TuneCP5_13TeV-powheg-pythia8_NANOAODSIMCUSTOM106X_mcRun2_asymptotic_v17.root");   // Name of the file to open
  TTree *tree = (TTree*)file->Get("Events");
  tree->MakeSelector("nanoAna"); //Name of the .C & .h files
}


