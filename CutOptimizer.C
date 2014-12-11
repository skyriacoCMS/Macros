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
#include "TMVA/Tools.h"
#include "TMVA/Factory.h"
#include <sstream>
#include <string.h>

using namespace TMVA;
void CutOptimizer(int reg){
  TMVA::Tools::Instance();
  std::cout << "==> Start TMVARegression" << std::endl;
    
  //Output file: 
  TString outfileName( "CutBasedID.root" );
  TFile* outputFile = TFile::Open( outfileName, "RECREATE" );
  
  //Declaring the factory
  TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile, 
					      "!V:!Silent:Color:DrawProgressBar");

					      //:Transformations=I;D;G;D:AnalysisType=Classification" );
  
  
  //Declaring Input Varibles 
  //  factory->AddVariable( "isoP","isoP","units",'F' );
  // factory->AddVariable( "isoC","isoC","units",'F' );
  //factory->AddVariable( "isoN","isoN","units",'F' );
  // factory->AddVariable( "ToE","ToE","units",'F' );
  factory->AddVariable( "Sieie","Sieie","units",'F' );
  

  //Input file:
  TString fname = "../CutTMVATrees_Barrel.root";
  input = TFile::Open( fname );
  
  // --- Register the regression tree  
  TTree *signal = (TTree*)input->Get("t_S");
  TTree *background = (TTree*)input->Get("t_B");
  

  //Just Some more settings
  Double_t signalWeight      = 1.0; 
  Double_t backgroundWeight  = 1.0; 
   
  // You can add an arbitrary number of regression trees
  factory->AddSignalTree( signal,1);
  factory->AddBackgroundTree( background ,1);



  TCut mycuts = "";
  TCut mycutb = "";

    factory->PrepareTrainingAndTestTree(mycuts,mycutb,
                               "nTrain_Signal=100000:nTrain_Background=100000" );
  // factory->SetBackgroundWeightExpression("weighT");
  //factory->SetSignalWeightExpression("weighT");    
 //************
  
  
 /* 
    factory->BookMethod( TMVA::Types::kCuts, "CutsGA",
    "H:!V:FitMethod=GA:CutRangeMin[0] = 0:CutRangeMin[1] = 0:CutRangeMin[2] = 0:CutRangeMin[3] = 0:CutRangeMin[4] = 0:CutRangeMax[0] = 22:CutRangeMax[1] = 22:CutRangeMax[2] = 4.5:CutRangeMax[3] = 2.5:CutRangeMax[4] = 0.15:Steps=30:Cycles=3:PopSize=30:SC_steps=10:SC_rate=10:SC_factor=0.95:EffSel:SaveBestCycle=10:VarProp[1]=FMax" );
    
 */
 //  factory->BookMethod( TMVA::Types::kCuts, "CutsGA","H:!V:FitMethod=GA:CutRangeMin[0] = 0:CutRangeMin[1] = 0:CutRangeMin[2] = 0:CutRangeMin[3] = 0:CutRangeMin[4] = 0:CutRangeMax[0] = 22:CutRangeMax[1] = 22:CutRangeMax[2] = 4.5:CutRangeMax[3] = 2.5:CutRangeMax[4] = 0.15:Steps=30:Cycles=3:PopSize=30:SC_steps=10:SC_rate=10:SC_factor=0.95:EffSel:SaveBestCycle=10:VarProp[1]=FMax" );
 
 
 
 /*factory->BookMethod( TMVA::Types::kCuts, "CutsGA",
			     "H:!V:FitMethod=GA:CutRangeMin[0]=-1:CutRangeMax[0]=10:CutRangeMin[1]=-1:CutRangeMax[1]=10:VarProp[0]=FMax:VarProp[1]=FMax:EffSel:Steps=30:Cycles=1:PopSize=30:SC_steps=10:SC_rate=5:SC_factor=0.95" );
   */

 // factory->BookMethod( TMVA::Types::kCuts, "CutsGA","H:!V:FitMethod=GA:EffSel:CutRangeMin[0]=0::CutRangeMin[1]=0:CutRangeMin[2]=0:CutRangeMin[3]=0:CutRangeMin[4]=0:CutRangeMax[0]=5.0:CutRangeMax[1]=4.0:CutRangeMax[2]=2.0:CutRangeMax[3]=1.5:CutRangeMax[4]=0.02");
 
 factory->BookMethod( TMVA::Types::kCuts, "CutsGA","H:!V:FitMethod=GA:EffSel:CutRangeMin[0]=:CutRangeMax[0]=0.02");
 

 
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
