#include <cstdio>
#include <vector>
#include <map>
using namespace std;

typedef long long LL;
typedef vector<LL> VL;

const int MOD = 1000000007;

LL ceil2(LL x) {
  return x%2==0 || x<=0 ? x/2 : x/2+1;
}

LL floor2(LL x) {
  return x%2==0 || x>=0 ? x/2 : x/2-1;
}

map<VL,int> DP1,DP2;
typedef map<VL,int>::iterator Iter;

int dp1(LL L1, LL L2, LL R1, LL R2);

// sum of f(a+bi) over L1<=a+b<=L2, R1<=a-b<=R2
int dp2(LL L1, LL L2, LL R1, LL R2) {
  if(L1>L2 || R1>R2) return 0;
  LL x[4]={L1,L2,R1,R2};
  VL v(x,x+4);
  pair<Iter, bool> p = DP2.insert(make_pair(v,0));
  int& res = p.first->second;
  if(!p.second) {
    return res;
  }
  LL dx = floor2(L2+1)-ceil2(L1+1)+1;
  LL dy = floor2(R2+1)-ceil2(R1+1)+1;
  res = (res + (dx%MOD) * (dy%MOD)) % MOD;
  res = (res + dp1(ceil2(-R2), floor2(-R1), ceil2(-L2), floor2(-L1))) % MOD;
  res = (res + dp1(ceil2(1-R2), floor2(1-R1), ceil2(1-L2), floor2(1-L1))) % MOD;
  return res;
}

// sum of f(a+bi) over L1<=a<=L2, R1<=b<=R2
int dp1(LL L1, LL L2, LL R1, LL R2) {
  if(L1>L2 || R1>R2) return 0;
  if(R1==0 && R2==0 && L1==0 && L2==0) return 0;
  LL x[4]={L1,L2,R1,R2};
  VL v(x,x+4);
  pair<Iter, bool> p = DP1.insert(make_pair(v,0));
  int& res = p.first->second;
  if(!p.second) {
    return res;
  }
  LL dx = L2-L1+1;
  LL dy = R2-R1+1;
  // dx*dy/2 % MOD
  int num = ((dx%MOD) * (dy%MOD) - (dx%2) * (dy%2)) % MOD * ((MOD+1)/2) % MOD;
  if(dx%2 && dy%2 && (L1+R1)%2) num++;
  res = num;
  res = (res + dp2(-L2,-L1,R1,R2)) % MOD;
  res = (res + dp2(1-L2,1-L1,R1,R2)) % MOD;
  return res;
}

int main()
{
  LL L = 1000000000000000LL;
  printf("%d\n", dp1(-L,L,-L,L));
  return 0;
}