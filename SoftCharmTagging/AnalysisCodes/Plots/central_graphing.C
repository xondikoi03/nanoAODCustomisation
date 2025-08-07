/* ===========================================
   
  This is a graphing script to make histograms
  look presentable and ready for journal uses.
  Created on: 10 Jul, 2024
  Original Author: Raj Handique

  Steps to the execute/run the code:

  1. In the ROOT prompt,
  root [0] .x graphing.C -> will produce the desired plot
  =========================================== */

// user include header files 

#include <iostream>
#include <string>
#include <fstream>
#include <TFile.h>
#include <TH1.h>
#include <TH1F.h>
#include <TPaveText.h>
#include <TString.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TGraph.h>

// Declaring all the functions necessary. The descriptions can be found commented
// along with them.

void decorate(TH1 *h, int linecolor, double linewidth){

  // This functions decorates the histogram with color and linewidth

  h->SetLineColor(linecolor);
  h->SetLineWidth(linewidth);
}


void central_graphing(){

  // The name of the input files (.root files)
  TString filename = "../Histograms/nanoAnaCentral2016_hist.root";
  
  // The name of the plot(s) to be accessed from the histogram file
  TString plotname1 = "nJets";
  TString plotname2 = "Jet_pt";
  TString plotname3 = "Jet_eta";
  TString plotname4 = "Jet_phi";

  // Opening the files using TFile
  TFile *file1 = new TFile(filename);

  // Opening and Assigning the histograms from the input file(s)
  TH1F *h1 = (TH1F*)file1->Get(plotname1);
  TH1F *h2 = (TH1F*)file1->Get(plotname2);
  TH1F *h3 = (TH1F*)file1->Get(plotname3);
  TH1F *h4 = (TH1F*)file1->Get(plotname4);

  // Plot1: nJets
  decorate(h1, kRed+0, 3);
  h1->SetStats(4);
  TCanvas *c1 = new TCanvas("c1","CMS Open Data", 1800, 1200);
  h1->Draw("hist");
  TLatex t1, t2, t3;
  t1.SetTextSize(0.05);
  t2.SetTextSize(0.04);
  t3.SetTextSize(0.03);
  // t1.DrawLatexNDC(0.66, 0.84, "CMS Open Data");
  // t2.DrawLatexNDC(0.66, 0.79, "#it{#bf{Simulation}}");
  t3.DrawLatexNDC(0.1, 0.95, "CMS_mc_RunIISummer20UL16NanoAODv9_TTToHadronic_TuneCP5_13TeV-powheg-pythia8");
  c1->Update();
  c1->SaveAs("central_nanoAOD_plots/nJets_plot.png");

  // Plot2: Jet_pt
  decorate(h2, kRed+0, 3);
  h2->SetStats(4);
  h2->GetXaxis()->SetRangeUser(0, 400);
  TCanvas *c2 = new TCanvas("c2","CMS Open Data", 1800, 1200);
  h2->Draw("hist");
  // t1.DrawLatexNDC(0.66, 0.84, "CMS Open Data");
  // t2.DrawLatexNDC(0.66, 0.79, "#it{#bf{Simulation}}");
  t3.DrawLatexNDC(0.1, 0.95, "CMS_mc_RunIISummer20UL16NanoAODv9_TTToHadronic_TuneCP5_13TeV-powheg-pythia8");
  c2->Update();
  c2->SaveAs("central_nanoAOD_plots/Jet_pt_plot.png");

  // Plot3: Jet_eta
  decorate(h3, kRed+0, 3);
  h3->SetStats(4);
  TCanvas *c3 = new TCanvas("c3","CMS Open Data", 1800, 1200);
  h3->Draw("hist");
  // t1.DrawLatexNDC(0.66, 0.84, "CMS Open Data");
  // t2.DrawLatexNDC(0.66, 0.79, "#it{#bf{Simulation}}");
  t3.DrawLatexNDC(0.1, 0.95, "CMS_mc_RunIISummer20UL16NanoAODv9_TTToHadronic_TuneCP5_13TeV-powheg-pythia8");
  c3->Update();
  c3->SaveAs("central_nanoAOD_plots/Jet_eta_plot.png");


  // Plot4: Jet_phi
  decorate(h4, kRed+0, 3);
  h4->SetStats(4);
  h4->GetXaxis()->SetRangeUser(-5, 5);
  h4->SetMinimum(0);
  h4->SetMaximum(1300);
  TCanvas *c4 = new TCanvas("c4","CMS Open Data", 1800, 1200);
  h4->Draw("hist");
  // t1.DrawLatexNDC(0.66, 0.84, "CMS Open Data");
  // t2.DrawLatexNDC(0.66, 0.79, "#it{#bf{Simulation}}");
  t3.DrawLatexNDC(0.1, 0.95, "CMS_mc_RunIISummer20UL16NanoAODv9_TTToHadronic_TuneCP5_13TeV-powheg-pythia8");
  c4->Update();
  c4->SaveAs("central_nanoAOD_plots/Jet_phi_plot.png");
}

