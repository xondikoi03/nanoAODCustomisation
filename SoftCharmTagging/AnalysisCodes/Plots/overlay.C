/* ===========================================
   
  This is a graphing script to make histograms
  look presentable and ready for journal uses.
  This one is particularly made as an overlay 
  script.
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

void decLegend(TLegend *g, float txtsize, TString lgHeader){
  g->SetTextSize(txtsize);
  g->SetFillStyle(1);
  g->SetFillColor(10);
  g->SetBorderSize(1);
  g->SetLineColor(10);
}

void overlay(){

  // The name of the input files (.root files)
  TString filename1 = "../Histograms/nanoAnaCentral2016_hist.root";
  TString filename2 = "../Histograms/nanoAnaCustom2016_hist.root";  

  // The name of the plot(s) to be accessed from the histogram file
  TString plotname1 = "nJets";
  TString plotname2 = "Jet_pt";
  TString plotname3 = "Jet_eta";
  TString plotname4 = "Jet_phi";

  // Opening the files using TFile
  TFile *file1 = new TFile(filename1);
  TFile *file2 = new TFile(filename2);

  // Opening and Assigning the histograms from the input file(s)
  // filename 1
  TH1F *h1 = (TH1F*)file1->Get(plotname1);
  TH1F *h2 = (TH1F*)file1->Get(plotname2);
  TH1F *h3 = (TH1F*)file1->Get(plotname3);
  TH1F *h4 = (TH1F*)file1->Get(plotname4);
  // filename 2
  TH1F *h5 = (TH1F*)file2->Get(plotname1);
  TH1F *h6 = (TH1F*)file2->Get(plotname2);
  TH1F *h7 = (TH1F*)file2->Get(plotname3);
  TH1F *h8 = (TH1F*)file2->Get(plotname4);

  // Scaling the histograms
  h1->Scale(1.0/h1->Integral());
  h2->Scale(1.0/h2->Integral());
  h3->Scale(1.0/h3->Integral());
  h4->Scale(1.0/h4->Integral());
  h5->Scale(1.0/h5->Integral());
  h6->Scale(1.0/h6->Integral());
  h7->Scale(1.0/h7->Integral());
  h8->Scale(1.0/h8->Integral());

  // Plot1: nJets
  decorate(h1, kRed+0, 3);
  decorate(h5, kBlue+0, 3);
  TCanvas *c1 = new TCanvas("c1","CMS Open Data", 1800, 1200);
  // Legend
  TLegend *lg1 = new TLegend(0.6, 0.5, 0.9, 0.6,NULL,"NDC");
  lg1->AddEntry(h5,"customNanoAOD","lp");
  lg1->AddEntry(h1,"centralNanoAOD","lf");
  h1->Draw("hist");
  gPad->Update();
  TPaveStats* stats1 = (TPaveStats*)h1->FindObject("stats");
  stats1->SetTextColor(kRed);
  stats1->SetX1NDC(0.50); stats1->SetX2NDC(0.70);
  stats1->SetY1NDC(0.75); stats1->SetY2NDC(0.90);
  h5->Draw("hist sames");
  gPad->Update();
  TPaveStats* stats2 = (TPaveStats*)h5->FindObject("stats");
  stats2->SetTextColor(kBlue);
  stats2->SetX1NDC(0.70); stats2->SetX2NDC(0.90);
  stats2->SetY1NDC(0.75); stats2->SetY2NDC(0.90);
  lg1->Draw();
  TLatex t1, t2, t3;
  t1.SetTextSize(0.05);
  t2.SetTextSize(0.04);
  t3.SetTextSize(0.03);
  t1.DrawLatexNDC(0.1, 0.95, "CMS Open Data");
  t2.DrawLatexNDC(0.1, 0.91, "#it{#bf{Simulation}}");
//   t3.DrawLatexNDC(0.1, 0.95, "CMS_mc_RunIISummer20UL16NanoAODv9_TTToHadronic_TuneCP5_13TeV-powheg-pythia8");
  c1->Update();
  c1->SaveAs("Overlay_plots/nJets_plot.png");

  // Plot2: Jet_pt
  decorate(h2, kRed+0, 3);
  decorate(h6, kBlue+0, 3);
  h2->GetXaxis()->SetRangeUser(0, 50);
  h6->GetXaxis()->SetRangeUser(0, 50);
  TCanvas *c2 = new TCanvas("c2","CMS Open Data", 1800, 1200);
  // Legend
  TLegend *lg2 = new TLegend(0.6, 0.5, 0.9, 0.6,NULL,"NDC");
  decLegend(lg2,0.0285,""); 
  lg2->AddEntry(h6,"customNanoAOD","lp");
  lg2->AddEntry(h2,"centralNanoAOD","lf");
  h6->Draw("hist");
  gPad->Update();
  TPaveStats* stats3 = (TPaveStats*)h6->FindObject("stats");
  stats3->SetTextColor(kRed);
  stats3->SetX1NDC(0.50); stats3->SetX2NDC(0.70);
  stats3->SetY1NDC(0.75); stats3->SetY2NDC(0.90);
  h2->Draw("hist sames");
  gPad->Update();
  TPaveStats* stats4 = (TPaveStats*)h2->FindObject("stats");
  stats4->SetTextColor(kBlue);
  stats4->SetX1NDC(0.70); stats4->SetX2NDC(0.90);
  stats4->SetY1NDC(0.75); stats4->SetY2NDC(0.90);
  t1.DrawLatexNDC(0.1, 0.95, "CMS Open Data");
  t2.DrawLatexNDC(0.1, 0.91, "#it{#bf{Simulation}}");
//   t3.DrawLatexNDC(0.1, 0.95, "CMS_mc_RunIISummer20UL16NanoAODv9_TTToHadronic_TuneCP5_13TeV-powheg-pythia8");
  lg2->Draw();
  c2->Update();
  c2->SaveAs("Overlay_plots/Jet_pt_plot.png");

  // Plot3: Jet_eta
  decorate(h3, kRed+0, 3);
  decorate(h7, kBlue+0, 3);
  TCanvas *c3 = new TCanvas("c3","CMS Open Data", 1800, 1200);
  // Legend
  TLegend *lg3 = new TLegend(0.37, 0.2, 0.625, 0.3,NULL,"NDC");
  decLegend(lg1,0.0285,""); 
  lg3->AddEntry(h7,"customNanoAOD","lp"); 
  lg3->AddEntry(h3,"centralNanoAOD","lf");
  h3->Draw("hist");
  gPad->Update();
  TPaveStats* stats5 = (TPaveStats*)h3->FindObject("stats");
  stats5->SetTextColor(kBlue);
  stats5->SetX1NDC(0.70); stats5->SetX2NDC(0.90);
  stats5->SetY1NDC(0.79); stats5->SetY2NDC(0.89);
  h7->Draw("hist sames");
  gPad->Update();
  TPaveStats* stats6 = (TPaveStats*)h7->FindObject("stats");
  stats6->SetTextColor(kRed);
  stats6->SetX1NDC(0.70); stats6->SetX2NDC(0.90);
  stats6->SetY1NDC(0.69); stats6->SetY2NDC(0.79);
  t1.DrawLatexNDC(0.1, 0.95, "CMS Open Data");
  t2.DrawLatexNDC(0.1, 0.91, "#it{#bf{Simulation}}");
//   t3.DrawLatexNDC(0.1, 0.95, "CMS_mc_RunIISummer20UL16NanoAODv9_TTToHadronic_TuneCP5_13TeV-powheg-pythia8");
  lg3->Draw();
  c3->Update();
  c3->SaveAs("Overlay_plots/Jet_eta_plot.png");

  // Plot4: Jet_phi
  decorate(h4, kRed+0, 3);
  decorate(h8, kBlue+0, 3);
  h4->GetXaxis()->SetRangeUser(-5, 5);
  TCanvas *c4 = new TCanvas("c4","CMS Open Data", 1800, 1200);
  // Legend
  TLegend *lg4 = new TLegend(0.37, 0.2, 0.625, 0.3,NULL,"NDC");
  decLegend(lg1,0.0285,"");
  lg4->AddEntry(h8,"customNanoAOD","lp");
  lg4->AddEntry(h4,"centralNanoAOD","lf");
  h8->Draw("hist");
  gPad->Update();
  TPaveStats* stats7 = (TPaveStats*)h8->FindObject("stats");
  stats7->SetTextColor(kRed);
  stats7->SetX1NDC(0.4); stats7->SetX2NDC(0.6);
  stats7->SetY1NDC(0.42); stats7->SetY2NDC(0.52);
  h4->Draw("hist sames");
  gPad->Update();
  TPaveStats* stats8 = (TPaveStats*)h4->FindObject("stats");
  stats8->SetTextColor(kBlue);
  stats8->SetX1NDC(0.4); stats8->SetX2NDC(0.6);
  stats8->SetY1NDC(0.32); stats8->SetY2NDC(0.42);
  t1.DrawLatexNDC(0.1, 0.95, "CMS Open Data");
  t2.DrawLatexNDC(0.1, 0.91, "#it{#bf{Simulation}}");
//   t3.DrawLatexNDC(0.1, 0.95, "CMS_mc_RunIISummer20UL16NanoAODv9_TTToHadronic_TuneCP5_13TeV-powheg-pythia8");
  lg4->Draw();
  c4->Update();
  c4->SaveAs("Overlay_plots/Jet_phi_plot.png");
}

