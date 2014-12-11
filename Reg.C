#include <cstdlib>
#include <iostream> 
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"



#include "TMVA/GeneticAlgorithm.h"
#include "TMVA/GeneticFitter.h"
#include "TMVA/IFitterTarget.h"

//#include "TMVARegGui.C"
#include "TMVA/Tools.h"
#include "TMVA/Factory.h"

using namespace TMVA;


void Reg(){
  
  TMVA::Tools::Instance();
  std::cout << "==> Start TMVARegression" << std::endl;
  

  
  
  //Output file 
  TString outfileName( "CutBasedID.root" );
  TFile* outputFile = TFile::Open( outfileName, "RECREATE" );
  
  //Declaring the factory
  TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile, 
					      "!V:!Silent:Color:DrawProgressBar" );
  
  
  //Declaring Input Varibles 
  
  factory->AddVariable( "iso", 'F' );
  factory->AddVariable( "iso2",'F' );
  factory->AddVariable( "iso3",'F' );
  
  //Declaring Target
  //  factory->AddTarget("pri");

  //Input file 

  // TFile *input = TFile::Open("GAlgo.root");
  
  TString fname = "GAlgo.root";
  
  input = TFile::Open( fname );
  
  // --- Register the regression tree
  
  TTree *signal = (TTree*)input->Get("t1S");
  TTree *background = (TTree*)input->Get("t1B");
  

  //Just Some more settings
   Double_t signalWeight      = 1.0; 
   Double_t backgroundWeight  = 1.0; 

   // You can add an arbitrary number of regression trees
   factory->AddSignalTree( signal, signalWeight );
   factory->AddBackgroundTree( background , backgroundWeight );
   // TCut mycut = ""; 
    
    
   //************

     
    
   factory->BookMethod( TMVA::Types::kCuts, "CutsGA",
			"H:!V:FitMethod=GA:CutRangeMin[0]=0:CutRangeMax[0]=1.4:CutRangeMin[1]=0:CutRangeMax[1]=1:CutRangeMin[2]=0:CutRangeMax[2]=1000:Steps=40:Cycles=3:PopSize=300:SC_steps=10:SC_rate=10:SC_factor=0.95:EffMethod=EffSel:VarProp=FSmart:VarProp=FSmart" );
    
   
    
 
    factory->TrainAllMethods();
    factory->TestAllMethods();
    factory->EvaluateAllMethods();    

   // --------------------------------------------------------------
   
   // Save the output
   outputFile->Close();

   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVARegression is done!" << std::endl;      

   delete factory;
    
}
