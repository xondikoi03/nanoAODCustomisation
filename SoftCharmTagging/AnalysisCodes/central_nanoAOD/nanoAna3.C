#define nanoAna3_cxx
// The class definition in nanoAna3.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("nanoAna3.C")
// root> T->Process("nanoAna3.C","some options")
// root> T->Process("nanoAna3.C+")
//


#include "nanoAna3.h"
#include <TH2.h>
#include <TStyle.h>

//Additional headers:
#include <iostream>
#include <fstream>

void nanoAna3::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

  //Initialization of some global variables:
  time(&start);
  nEvtTotal = 0;

  //Creating the output file:
  _HstFile = new TFile(_HstFileName,"recreate");
  BookHistograms();

  TString option = GetOption();
}

void nanoAna3::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();

}

bool nanoAna3::Process(Long64_t entry)
{
  // The Process() function is called for each entry in the tree (or possibly
  // keyed object in the case of PROOF) to be processed. The entry argument
  // specifies which entry in the currently loaded tree is to be processed.
  // When processing keyed objects with PROOF, the object is already loaded
  // and is available via the fObject pointer.
  //
  // This function should contain the \"body\" of the analysis. It can contain
  // simple or elaborate selection criteria, run algorithms on the data
  // of the event and typically fill histograms.
  //
  // The processing can be stopped by calling Abort().
  //
  // Use fStatus to set the return value of TTree::Process().
  //
  // The return value is currently not used.

  fReader.SetLocalEntry(entry);
  //Setting verbosity:
  //Verbosity determines the number of processed events after which
  //the root prompt is supposed to display a status update.
  if(_verbosity==0 && nEvtTotal%100==0)cout<<"Processed "<<nEvtTotal<<" event..."<<endl;      
  else if(_verbosity>0 && nEvtTotal%100==0)cout<<"Processed "<<nEvtTotal<<" event..."<<endl;

  nEvtTotal++;

  // Analysis Block //
  int njets = 0;
  RecoJets.clear();

  if(nEvtTotal > 10000) return kFALSE;
  for(int i=0; i<(*nJet); i++){

    Particle temp;
    temp.index = i;
    temp.v.SetPtEtaPhiM(Jet_pt[i], Jet_eta[i], Jet_phi[i], Jet_mass[i]);
         
    bool kinematic_cuts = temp.v.Pt() > 10 && fabs(temp.v.Eta()) < 3;
    if(kinematic_cuts){
      RecoJets.push_back(temp);
      njets++;
    }
  }

  // Fill histograms
  h.hist[1]->Fill(int(RecoJets.size()));

  for(int i=0; i<((int)RecoJets.size()); i++){
    h.hist[2]->Fill(RecoJets.at(i).v.Pt());
    h.hist[3]->Fill(RecoJets.at(i).v.Eta());
    h.hist[4]->Fill(RecoJets.at(i).v.Phi());
  }

  return kTRUE;
}

void nanoAna3::BookHistograms(){

  h.hist[1] = new TH1F("nJets", ";nJets; Events/GeV", 20, 0, 20);
  h.hist[2] = new TH1F("Jet_pt", ";Jet_pt; nJets", 100, 0, 500);
  h.hist[3] = new TH1F("Jet_eta", ";Jet_eta; nJets", 100, -4, 4);
  h.hist[4] = new TH1F("Jet_phi", ";Jet_phi; nJets", 100, -4, 4);
}

void nanoAna3::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.

}

void nanoAna3::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.

  //Writing the saving the output file:
  _HstFile->Write();
  _HstFile->Close();
      
  //Printing out some information using the event counters after the event loop has run.
  cout<<"----------------------------------------------------------"<<endl;
  cout<<"Summary:"                    <<endl;
  cout<<"nEvtTotal = "  <<nEvtTotal   <<endl;
  cout<<"----------------------------------------------------------"<<endl;

  time(&end);

  double time_taken = double(end-start);
  cout<<"\nTime taken by the program is : "<<(int)time_taken<<" seconds \n"<<endl;

}
