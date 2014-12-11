#include <iostream>
#include <cstdlib>


void Reader_fromTXT(){


  ifstream myfile; 
  myfile.open("RandomNUMS.txt");
  
  if(myfile.is_open()){
    while(!myfile.eof()){

      int k1, k2 ,k3; 
      
      myfile>>k1>>k2>>k3; 
      cout<<k1<<endl; 
      cout<<k2<<endl; 
      cout<<k3<<endl;
      
    }
  }

}
