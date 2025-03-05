#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef unsigned __int64 u64;
#define L 0x21C3677C82B40000ULL

u64 trailzero(u64 x){u64 s=0;while(x>>=1)s+=x;return s;}
u64 oddmul(u64 a,u64 b){
  u64 s=1;
#pragma omp parallel for reduction(*:s)
  for(u64 n=a|1;n<=b;n+=2)s*=n;
  return s;
}

int main(){
  vector<u64> v; 
  for(u64 x=L; x; x>>=1) v.push_back(x&0x3FFFFFFFFFFF); 
  sort(v.begin(),v.end());

  u64 r=1,r0=1,a=0;
  for(auto x:v) {
    r0*=oddmul(a,x);
    a=x+1;
    r*=r0;
  }
  r<<=trailzero(L)&3;
  cout<<hex<<r;
}