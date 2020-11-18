#include "TF1.h"
#include "TH1.h"
#include "TMath.h"
#include "TROOT.h"
#include "BW.C"

#include <iostream>
#include <string>

void FitZPeak(bool save = false, vector<string> formats = {".eps"}){

   gROOT->Macro("rootlogon.C");
   gStyle->SetOptFit(111111);

   std::string fname = "myZPeakCRAB.root";
   TFile *f = new TFile(fname.c_str(),"READ");
   TH1F *Z_mass;
   if (f && f->IsOpen()) {
      Z_mass = (TH1F*)f->Get("analyzeBasicPat/mumuMass");
      if (!Z_mass) {
         std::cout << "ERROR::Unable to find the histogram analyzeBasicPat/mumuMass in file " << f->GetName() << std::endl;
         return;
      }
   }
   else {
      std::cout << "ERROR::Unable to open the file " << fname << std::endl;
      return;
   }

   //float massMIN = Z_mass->GetBinLowEdge(1);
   //float massMAX = Z_mass->GetBinLowEdge(Z_mass->GetNbinsX()+1);

   float massMIN = 88.0; // 80.0
   float massMAX = 94.0; // 100.0

   ////////////////
   //For Gaussian//
   ////////////////

   TF1 *func = new TF1("mygauss",mygauss,massMIN, massMAX,3); 
   func->SetParameter(0,100.0); func->SetParName(0,"const");  
   func->SetParameter(2,5.0);   func->SetParName(2,"sigma");  
   func->SetParameter(1,95.0);  func->SetParName(1,"mean");

   Z_mass->Fit("mygauss","QR");
   TF1 *fit = Z_mass->GetFunction("mygauss");

   ////////////////////
   //For Breit-Wigner//
   ////////////////////
   /*
   TF1 *func = new TF1("mybw",mybw,massMIN, massMAX,3);
   func->SetParameter(0,1.0);   func->SetParName(0,"const");
   func->SetParameter(2,5.0);     func->SetParName(1,"sigma");
   func->SetParameter(1,94.0);    func->SetParName(2,"mean");
   
   Z_mass->Fit("mybw","QR");
   TF1 *fit = Z_mass->GetFunction("mybw");
   */
   //////////////
   //Formatting//
   //////////////

   fit->SetLineColor(4);
   fit->SetLineWidth(3);

   Z_mass->SetMarkerStyle(20);
   Z_mass->SetMarkerSize(1.0);
   Z_mass->SetMarkerColor(2);
   Z_mass->SetLineWidth(2.0);
   Z_mass->SetXTitle("Z Mass (in GeV/c^{2})"); 
   // Z_mass->GetXaxis()->SetTitleOffset(1.0);

   //////////////
   //Processing//
   //////////////

   Z_mass->Draw("PE0");

   if (save) {
      TCanvas* c1 = (TCanvas*)gROOT->GetListOfCanvases()->At(0);
      for (auto format : formats) {
         //c1->Print (("myZmass_BWfitted"+format).c_str());
         c1->Print (("myZmass_Gausfitted"+format).c_str());
      }
   }
}

