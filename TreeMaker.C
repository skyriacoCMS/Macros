#include <TMath.h>
#include <cstdlib>
#include <TRandom.h>

void TreeMaker(){


  TFile *f1 = new TFile("GAlgo.root","recreate");

  TTree *t1S = new TTree("t1S","GA needs this");
  TTree *t1B = new TTree("t1B","GA needs this");

  TH1F *Gaus1 = new TH1F("Gaus1","Gauss Distr",1000,0,1000);
  TH1F *Gaus2 = new TH1F("Gaus2","Gauss Distr",1000,0,1000);


  TRandom r1; 


  int sb ; 
  float iso,iso2,iso3; 

  // t1->Branch("sb",&sb,"sb/I");


  t1S->Branch("iso",&iso,"iso/F");
  t1S->Branch("iso2",&iso2,"iso2/F");
  t1S->Branch("iso3",&iso3,"iso3/F");

  
  t1B->Branch("iso",&iso,"iso/F");
  t1B->Branch("iso2",&iso2,"iso2/F");
  t1B->Branch("iso3",&iso3,"iso3/F");


  srand(1235564);


  for(int i  = 0; i < 300000; i++){

    double x =( rand() % 1000) /1000.0;
    double y =( rand() % 1000) /1000.0;
  


    if(i%2 == 0){

      sb = 1; 
      
      iso = 0.25*(6 - TMath::Sqrt((36 - 36*x)));
      iso2 = ( 4+TMath::Sqrt(4 + 24*y))/6.193;
     
     
      iso3 = r1.Gaus(500,30);
      Gaus1->Fill(iso3);
      t1S->Fill();	  
 
    }else{
   
      sb = 0;


      iso = x*1.5;
      iso2 = ( rand() % 1000/1000.)*1.5;

      
      
      iso3 = r1.Gaus(300,60);
      
     
      
      
      Gaus2->Fill(r1.Gaus(300,60));
      
      t1B->Fill();
      
    }


  }

  t1S->Write();
  t1B->Write();
  Gaus1->Write();
  Gaus2->Write();

}

