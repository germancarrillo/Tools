#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

#define arraysize 110

int partitionset(vector<double>&X,uint a,uint b){

  double pivot=X[b]; 
  uint i=a;
  uint j=b;

  while(true){
    if(X[j-1]>pivot){
      swap(X[j-1],X[j]);    
      j--;      
    }else if(X[i]>pivot){
      swap(X[i],X[j-1]);
    }else i++;    
    if(i>=j) return j-1; 
  }  
}

void doquicksort(vector<double>&X,uint a=0,uint b=arraysize-1){
  if(a<b){   
    uint p=partitionset(X,a,b);
    doquicksort(X,a,p);
    doquicksort(X,p+1,b);
  }
  return;
}

int main(){
  vector<double> X;
  for(uint i=0; i<arraysize;i++) X.push_back(rand()%10);   

  cout<<"ORIGIN "; for(int x:X){cout<<x<<",";} cout<<endl;
  //
  doquicksort(X);
  //
  cout<<"SORTED "; for(int x:X){cout<<x<<",";} cout<<endl;

  return 0; 
}

 
