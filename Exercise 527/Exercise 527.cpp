#include <vector>
#include <cmath>

using namespace std;

typedef long long ll;
typedef double ld;

vector<ld> B_DP;
vector<int> B_S;
ld B(ll n) {
  if(n<=0) { return 0; }
  if(n<B_DP.size() && B_S[n]) {
    return B_DP[n];
  }
  ll m = (n+1)/2 - 1;
  ld ans = 1 + B(m)*ld(m)/n + B(n-1-m)*ld(n-1-m)/n;
  if(n < B_DP.size()) {
    B_S[n] = true;
    B_DP[n] = ans;
  }
  return ans;
}

vector<ld> R_DP;
vector<int> R_S;
ld RSlow(ll n) {
  if(n <= 0) { return 0; }
  if(R_S[n]) { return R_DP[n]; }
  ld ans = 0;
  for(ll i=2; i<=n; i++) {
    ans += ld(2*n-2*i+2)/i;
  }
  ans += n;
  ans /= n;
  R_S[n] = true;
  R_DP[n] = ans;
  return ans;
}

// n + (2n-2)/2 + (2n-4)/3 + ... + 2/(n-1)
ld R(ll n) {
  if(n <= 0) { return 0; }
  ld euler_mach = 0.57721566490153286060651209008;
  ld hn = log(n)+euler_mach;

  ld ans = 2*((n+1)*hn - 2*n);
  return (ans+n)/n;
  /*
  ld ans = 0;
  for(ll i=2; i<=n; i++) {
    ans += ld(2*n-2*i+2)/i;
  }
  ans += n;
  ans /= n;
  return ans;
  */
}

ll p10(ll n) {
  if(n==0) { return 1LL; }
  else { return 10LL*p10(n-1); }
}


int main() {
  B_DP = vector<ld>(p10(6), 0.0);
  B_S = vector<int>(B_DP.size(), false);
  R_DP = vector<ld>(B_DP.size(), 0.0);
  R_S = vector<int>(B_DP.size(), false);

  printf("%f %f\n", R(p10(10)), B(p10(10)));
  printf("%.8f\n", R(p10(10))-B(p10(10)));
}