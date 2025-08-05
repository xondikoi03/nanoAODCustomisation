// Creates Ana.C and Ana.h Files 
// Original Author: Raj Handqiue
// ROOT Framework - CERN

#include <iostream>
#include "TFile.h"
#include "TTree.h"

using namespace std;

void anafile(){
  
  TFile *file = TFile::Open("../output_files/test2016.root");   // Name of the file to open
  TTree *tree = (TTree*)file->Get("Events");
  tree->MakeSelector("nanoAna2"); //Name of the .C & .h files
}


