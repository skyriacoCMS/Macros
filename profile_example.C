void test(){
  TCanvas *c1 = new TCanvas("c1","Profile histogram example",200,10,700,500);
  hprof  = new TProfile("hprof","Profile of pz versus px",100,-4,4,0,20);
  Float_t px, py, pz;
  for ( Int_t i=0; i<25000; i++) {
     gRandom->Rannor(px,py);
     pz = px*px + py*py;
     hprof->Fill(px,pz,1);
  }
  hprof->Draw();
}
