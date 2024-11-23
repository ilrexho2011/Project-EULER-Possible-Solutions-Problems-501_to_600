#include <windows.h>
#include <iostream>
#include <math.h>
#include <map>
using namespace std;
typedef unsigned __int8  u8;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;
#define N 1000000000000LL
#define L 100000000

u8 np[L+1];
u32 cp[L+1],p[L+1],pp;

map<u64,u64> C;
u64 phi(u64 x, u64 a){
  if(a==1 || !x)return (x+1)/2;
  u64 &c=C[(x<<10)+a];if(c)return c;
  return c=phi(x,a-1)-phi(x/p[a],a-1);
}
u64 pi(u64 n){
  if(n<=L)return cp[n];
  u64 a=pi(pow(n,1./4));
  u64 b=pi(sqrt(n));
  u64 c=pi(pow(n,1./3));
  u64 s=phi(n,a)+(b+a-2)*(b-a+1)/2;
  for(u64 i=a+1; i<=b; i++){
    u64 w=n/p[i];
    s-=pi(w);
    if(i<=c) for(u64 j=i;j<=pi(sqrt(w));j++) s+=j-1-pi(w/p[j]);
  }
  return s;
}
                             
int main() {
  u64 t0=GetTickCount();
  u64 s=0;
                              
  for(u64 n=2,c=0; n<=L; n++) {
    if(!np[n]) {
      for(u64 x=n*n; x<=L; x+=n) np[x]=1;
      p[++pp]=n;
    }
    cp[n]=pp;
  }

  for(u64 i=1; p[i]<=pow(N,1./7); i++) s++;
  for(u64 i=1,a,b=p[i]; (a=N/(b*b*b))>=2; b=p[++i]) s+=pi(a)-(a>=b?1:0);
  for(u64 i=1,a=p[i]; a*a*a<=N; a=p[++i]) 
    for(u64 j=i+1,b=p[j],c; p[j+1]<=(c=N/(a*b)); b=p[++j]) 
      s+=pi(c)-pi(b);
 
  cout << s;
  cout << endl << GetTickCount()-t0;
  return 0;
}