#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
void driver(int sample=0)
{
  const char *hstfilename, *sumfilename; 
  TChain *chain = new TChain("Events");
  nanoAna2 m_selec;//declared an instance of our class.
  
  //--------------------------------------------------------------------------//
  //               Choose the sample you want to run over                     //
  //--------------------------------------------------------------------------//

  if(sample==0){
    chain->Add("../output_files/test.root");
    hstfilename = "nanoAna_hist1.root";
  }

  if(sample==1){
    chain->Add("../output_files/tree.root");
    hstfilename = "nanoAna_hist2.root";
  }

  if(sample==2){
    chain->Add("../output_files/test2016.root");
    hstfilename = "nanoAna_hist3.root";
  }

  std::cout<<"Output : "<<hstfilename<<std::endl;
  m_selec.SetHstFileName(hstfilename);
  m_selec.SetSumFileName(sumfilename);
  m_selec.SetVerbose(0);//set verbosity level for output.
  
  //this calls the Process function for each event in the chain
  //and runs the m_selec code over it.
  chain->Process(&m_selec);
    
}
