#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
void driver(int sample=0)
{
  const char *hstfilename, *sumfilename; 
  TChain *chain = new TChain("Events");
  nanoAna m_selec;//declared an instance of our class.
  
  //--------------------------------------------------------------------------//
  //               Choose the sample you want to run over                     //
  //--------------------------------------------------------------------------//

  if(sample==0){
    chain->Add("../output_files/CMS_mcRunIISummer20UL16MiniAODv2_TTToHadronic_TuneCP5_13TeV-powheg-pythia8_NANOAODSIMCUSTOM106X_mcRun2_asymptotic_v17.root");
    hstfilename = "nanoAna_hist.root";
  }

  if(sample==1){
    chain->Add("../output_files/tree.root");
    hstfilename = "nanoAnaTree_hist.root";
  }

  std::cout<<"Output : "<<hstfilename<<std::endl;
  m_selec.SetHstFileName(hstfilename);
  m_selec.SetSumFileName(sumfilename);
  m_selec.SetVerbose(0);//set verbosity level for output.
  
  //this calls the Process function for each event in the chain
  //and runs the m_selec code over it.
  chain->Process(&m_selec);
    
}
