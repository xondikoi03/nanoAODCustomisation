// Creates Ana.C and Ana.h Files 
// Original Author: Raj Handqiue
// ROOT Framework - CERN

#include <iostream>
#include "TFile.h"
#include "TTree.h"

using namespace std;

void anafile(){
  
  TFile *file = TFile::Open("../output_files/testCentral2016nanoAOD.root");   // Name of the file to open
  TTree *tree = (TTree*)file->Get("Events");
  tree->MakeSelector("nanoAna3"); //Name of the .C & .h files
}


