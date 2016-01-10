void HistArray(){
   
  TH1F **hclus; 
  hclus=new TH1F*[5];
  hclus[0] = new TH1F("","",10,0,10);
  hclus[0]->Fill(0); 
  hclus[0]->Fill(3); 
  hclus[0]->Draw(); 

}
