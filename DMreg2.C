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

//#include "TMVARegGui.C"
#include "TMVA/Tools.h"
#include "TMVA/Factory.h"

using namespace TMVA;


void DMreg2(){
  
  TMVA::Tools::Instance();
  std::cout << "==> Start TMVARegression" << std::endl;
  
  
  
  //Output file 
  TString outfileName( "dmREG22.root" );
  TFile* outputFile = TFile::Open( outfileName, "RECREATE" );
  
  //Declaring the factory
  TMVA::Factory *factory = new TMVA::Factory( "TMVARegression", outputFile, 
					      "!V:!Silent:Color:DrawProgressBar" );
  
  
  //Declaring Input Varibles 
  
  factory->AddVariable( "tsin", "angle", "units", 'F' );
  factory->AddVariable( "tMetch1","Met ch1","units", 'F' );
  factory->AddVariable( "tMetch2","Met ch2","units", 'F' );
  factory->AddVariable("abs(tStM -  tChM)","Caluclated stop mass","units",'F');
  
  


  factory->AddSpectator("tChM","Calculated charg mass","units",'F');
  
  factory->AddSpectator("tActSM","Actual Stop Mass","units",'F');
  factory->AddSpectator("tActChM","Actual Chargino Mass","units",'F');
  //Declaring Target
  factory->AddTarget("abs(tActSM -tActChM)");

  //Input file 

  TFile *input(0);
  
  TString fname = "/cms/data18/kyriacou/RANDOM/HADD_ed/AnalySIS.root";
  
  input = TFile::Open( fname );
  
  // --- Register the regression tree
  
  TTree *regTree = (TTree*)input->Get("t1");
  

  //Just Some more settings
   Double_t regWeight  = 1.0;   

   // You can add an arbitrary number of regression trees
   factory->AddRegressionTree( regTree, regWeight );
    TCut mycut = ""; 
    
    
   //************

    factory->PrepareTrainingAndTestTree( mycut, 
					 "nTrain_Regression=0:nTest_Regression=0:SplitMode=Random:NormMode=NumEvents:!V" );
    
    
    
    
    factory->BookMethod( TMVA::Types::kBDT, "BDTG",
			 "!H:!V:NTrees=1000::BoostType=Grad:Shrinkage=0.1:UseBaggedGrad:GradBaggingFraction=0.5:nCuts=1000:MaxDepth=7:NNodesMax=20" );
    
 
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
