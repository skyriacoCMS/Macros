#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TH2.h"
#include "TRandom.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TMVA/Tools.h"
#include "TMVA/Factory.h"
#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"

using namespace TMVA;


void Reader1(){
  
  TMVA::Tools::Instance();  
  TMVA::Reader *reader = new TMVA::Reader( "!Color" );  

  
  TFile *input(0);
  //  ofstream myfile;
  
  //  myfile.open("Roc_C.txt");
  
  input = TFile::Open("GAlgo.root");

  TTree *theTreeS = (TTree*)input->Get("t1S");
  TTree *theTreeB = (TTree*)input->Get("t1B");

  float iso,iso2,iso3;

  theTreeS->SetBranchAddress("iso",&iso);
  theTreeS->SetBranchAddress("iso2",&iso2);
  theTreeS->SetBranchAddress("iso3",&iso3);


  theTreeB->SetBranchAddress("iso",&iso);
  theTreeB->SetBranchAddress("iso2",&iso2);
  theTreeB->SetBranchAddress("iso3",&iso3);


  


  TString methodName = "CutsGA method";
  TString weightfile = "./weights/TMVAClassification_CutsGA.weights.xml";

  
  reader->AddVariable("iso",&iso);
  reader->AddVariable("iso2",&iso2);
  reader->AddVariable("iso3",&iso3);




  

  reader->BookMVA(methodName,weightfile ); 
  
  
  TMVA::MethodCuts* mcuts = dynamic_cast<TMVA::MethodCuts*>(reader->FindCutsMVA(methodName) );
  std::vector<Double_t> cutsMin;
  std::vector<Double_t> cutsMax;




  double sigEff_[100];
  double bkgRej_[100];
  
  
  for( int i = 0; i < 100; i ++){
    double SEF = 0.01*i;
    
    cout<<i<<endl;
    
    int nP = 0;
    int nB = 0;
    /*
  if(mcuts)mcuts->GetCuts(SEF, cutsMin, cutsMax );

    for (UInt_t ivar=0; ivar<cutsMin.size(); ivar++) {
      cout << "... Cut: "<<endl; 
      cout << cutsMax[ivar]<<endl;
    }

    */


    
    for(Long64_t ievt = 0; ievt < theTreeS->GetEntries();ievt++){
      
      theTreeS->GetEntry(ievt);
      
      
      
      
      int value = reader->EvaluateMVA("CutsGA method",SEF);
      if(value)nP++;
      
      
    }
   

    for(Long64_t ievt = 0; ievt < theTreeB->GetEntries();ievt++){
      
      theTreeB->GetEntry(ievt);
      int value = reader->EvaluateMVA("CutsGA method",SEF);
      if(value)nB++;
      
      
    }

    //    cout<<"nS:"<<nP<<" nB:"<<nB<<endl;

    double s = theTreeS->GetEntries();
    double b = theTreeB->GetEntries();
 

    double sigEff =nP*1.0/s;
    double bckEff =nB*1.0/b;

    sigEff_[i] = (sigEff);
    bkgRej_[i] = (1 - bckEff);

    //    cout<<sigEff<<" "<<bckEff<<endl;
   
    //myfile<<sigEff<<" "<<bckEff<<endl;






    
  }

  


  TCanvas *c1 = new TCanvas("c1"," ROC cuts",10,430,900,700);

  TGraph *ROC_Curve1 = new TGraph(10,bkgRej_,sigEff_);

  ROC_Curve1->SetMarkerStyle(24);
  ROC_Curve1->SetMarkerStyle(24);
  ROC_Curve1->GetXaxis()->SetTitle("Bkg Rejection");
  ROC_Curve1->GetYaxis()->SetTitle("Sig Efficiency");
  ROC_Curve1->Draw("ACP");

  //myfile.close();

  delete reader;


}
