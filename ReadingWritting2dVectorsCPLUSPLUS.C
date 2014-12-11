
void TWOD_vector_RW(){

  srand(123456);
  vector<vector<double>> pt_subs; 
  
  for(int i  = 0; i < 4; i ++){


    int k  = rand() % 10; 
    
        cout<<k<<endl;

	int  enter_t = pt_subs.size();
    for(int j  = 0; j < k ; j++){ 

      double pt = 40*(rand() %100 / 100. );
      
      
      if(j == 0)pt_subs.push_back(vector <double> (1,pt));
      if(j != 0) pt_subs.at(enter_t).push_back(pt);

      
      
      cout<<"subjets: "<< pt <<endl;

    }

  }


  cout<<"                      "<<endl;
  cout<<"-------------------- "<<endl;
  cout<<"                      "<<endl;


  //lets print the results


  for(int i  = 0; i < pt_subs.size(); i++){
    cout<<"JET :"<<i<<endl;
    
    int s_zz = pt_subs.at(i).size();
    
    cout<<s_zz<<endl;
    for(int k  = 0; k < s_zz; k++) cout<<" sub  "<<pt_subs.at(i).at(k)<<endl;

    
  }


}
