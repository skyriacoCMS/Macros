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

  int points = 40;
  
  TFile *input(0);
  input = TFile::Open("../CutTMVATrees_Barrel.root");
  ofstream mFil;
  ofstream myfile; 
  myfile.open("Eff_cuts.txt");
  myfile<<"Min/Max"<<"Sign Eff"<<"  "<<"Sieie     "<<"ToE     "<<"isoP     "<<"isoC     "<<"isoN     "<<endl;
  


  TTree *theTreeS = (TTree*)input->Get("t_S");
  TTree *theTreeB = (TTree*)input->Get("t_B");

  float isoP,isoN,isoC,Sieie,ToE;
  int Pix; 
  theTreeS->SetBranchAddress("isoP",&isoP);
  theTreeS->SetBranchAddress("isoC",&isoC);
  theTreeS->SetBranchAddress("isoN",&isoN);
  theTreeS->SetBranchAddress("ToE",&ToE);
  theTreeS->SetBranchAddress("Sieie",&Sieie);
  theTreeS->SetBranchAddress("Pix",&Pix);


  
  theTreeB->SetBranchAddress("isoP",&isoP);
  theTreeB->SetBranchAddress("isoC",&isoC);
  theTreeB->SetBranchAddress("isoN",&isoN);
  theTreeB->SetBranchAddress("ToE",&ToE);
  theTreeB->SetBranchAddress("Sieie",&Sieie);
  theTreeB->SetBranchAddress("Pix",&Pix);


 
  //setting a 40 points roc curve

  double sigEff_[40];
  double bkgRej_[40];
  mFil.open("Results_ROC.txt");
  
  
  //Declaring the reader
  
  TString methodName = "CutsGA method";
  TString weightfile = "./weights/TMVAClassification_CutsGA.weights.xml";    
  TMVA::Reader *reader = new TMVA::Reader( "!Color" );  
  
  //    reader->AddVariable("isoP",&isoP);
  //reader->AddVariable("isoC",&isoC);
  //reader->AddVariable("isoN",&isoN);
  //reader->AddVariable("ToE",&ToE);
  reader->AddVariable("Sieie",&Sieie);
  
  
  reader->BookMVA(methodName,weightfile ); 
  TMVA::MethodCuts* mcuts = dynamic_cast<TMVA::MethodCuts*>(reader->FindCutsMVA(methodName) );
  std::vector<Double_t> cutsMin;
  std::vector<Double_t> cutsMax;
  
  
  for( int i = 0; i < 40; i ++){
    double SEF = (1.0)/(40.0)*i;
    
    
    
    cout<<i<<endl;
    
   
    //caclualating actual efficiency 
    int nP = 0;
    int nB = 0;
    for(Long64_t ievt = 0; ievt < theTreeS->GetEntries();ievt++){
      theTreeS->GetEntry(ievt);
      if(Pix) continue;
      int value = reader->EvaluateMVA("CutsGA method",SEF);
      if(value)nP++;
    }
    for(Long64_t ievt = 0; ievt < theTreeB->GetEntries();ievt++){
      theTreeB->GetEntry(ievt);
      if(Pix) continue;
      int value = reader->EvaluateMVA("CutsGA method",SEF);
      if(value)nB++;
    }

    
    // printing actual efficiency 
    double s = theTreeS->GetEntries();
    double b = theTreeB->GetEntries();
    double sigEff =nP*1.0/s;
    double bckEff =nB*1.0/b;

    sigEff_[i] = (sigEff);
    bkgRej_[i] = (1 - bckEff);
    cout<<" sig eff :"<<sigEff<<endl;
    cout<<" Bck eff :"<<bckEff<<endl;

    mFil<<bckEff<<" "<<sigEff<<endl;
   
  
       
    if(mcuts)mcuts->GetCuts(SEF, cutsMin, cutsMax );
    myfile<<"Max:"<<sigEff<<"|"<<cutsMax[0]<<endl; //"|"<<cutsMax[1]<<"|"<<cutsMax[2]<<"|"<<cutsMax[3]<<"|"<<cutsMax[4]<<"|"<<endl; 
    myfile<<"Min :"<<sigEff<<"|"<<cutsMin[0]<<endl; //"|"<<cutsMin[1]<<"|"<<cutsMin[2]<<"|"<<cutsMin[3]<<"|"<<cutsMin[4]<<"|"<<endl;
    myfile<<"--------------------------------------------------------------------------------"<<endl;




    
  }


  delete reader;


  myfile.close();
 

}

