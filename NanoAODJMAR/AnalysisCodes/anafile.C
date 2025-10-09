// Creates Ana.C and Ana.h Files 
// Original Author: Raj Handqiue
// ROOT Framework - CERN

#include <iostream>
#include "TFile.h"
#include "TTree.h"

using namespace std;

void anafile(){
  
  TFile *file = TFile::Open("datasets/nano106X_on_mini106X_2017_mc_NANO.root");   // Name of the file to open
  TTree *tree = (TTree*)file->Get("Events");
  tree->MakeSelector("nanoAna106x"); //Name of the .C & .h files
}


