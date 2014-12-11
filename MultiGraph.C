#include <iostream>
#include <fstream>




void MultiGraph_B(){

  fstream mf; 
  mf.open("Results_ROC.txt");


  double bkRJ[40];
  double sigEF[40];

  double bk, sig;

  for(int i  = 0; i < 40; i++){

    
    
    mf>>bk>>sig; 

    bkRJ[i] = 1- bk;
    sigEF[i] = sig;

  }




  TGraph *GA_ROC = new TGraph(40,bkRJ,sigEF);
  GA_ROC->SetMarkerStyle(20);
  GA_ROC->SetMarkerColor(kRed);
  

  
  double ObkRJ[3]; 
  double OsigEF[3];


  //bARREL OLD POINTS
  ObkRJ[0] = 0.67;
  ObkRJ[1] = 0.7604;
  ObkRJ[2] = 0.8180;


  
  OsigEF[0] = 0.9213;
  OsigEF[1] = 0.916;
  OsigEF[2] = 0.9156;



  TGraph *old_ROC = new TGraph(3,ObkRJ,OsigEF);
  old_ROC->SetMarkerStyle(26);
  old_ROC->SetMarkerColor(kBlack);

  TMultiGraph *RocksB = new TMultiGraph();
  RocksB->Add(GA_ROC,"p");
  RocksB->Add(old_ROC,"p");

  RocksB->Draw("APL");

  RocksB->GetXaxis()->SetTitle("Background Rejection");
  RocksB->GetYaxis()->SetTitle("Signal Efficiency");




  
}

