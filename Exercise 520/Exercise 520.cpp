#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<vector<ll>> mat;

ll MOD = 1000000123LL;
ll ADD(ll x, ll y) { return (x+y)%MOD; }
ll MUL(ll x, ll y) { return (x*y)%MOD; }

mat mat_mult(mat A, mat B) {
  mat C(A.size(), vector<ll>(B[0].size(), 0));
  for(ll i=0; i<A.size(); i++) {
    for(ll k=0; k<A[i].size(); k++) {
      for(ll j=0; j<B[k].size(); j++) {
        C[i][j] = ADD(C[i][j], MUL(A[i][k], B[k][j]));
      }
    }
  }
  return C;
}
mat mat_pow(mat A, ll e) {
  if(e==1) { return A; }
  else if(e%2==0) { return mat_pow(mat_mult(A, A), e/2); }
  else { return mat_mult(A, mat_pow(A, e-1)); }
}

vector<ll> DP;
ll f(ll n, ll bad, ll good, ll good2) {
  ll key = n*11*11*11 + bad*11*11 + good*11 + good2;
  if(DP[key] >= 0) { return DP[key]; }

  ll ans = (bad==0 ? 1 : 0);
  if(n==0) { return ans; }
  if(bad > 0) {
    ans = ADD(ans, MUL(bad, f(n-1, bad-1, good+1, good2)));
  }
  if(good > 0) {
    ans = ADD(ans, MUL(good, f(n-1, bad+1, good-1, good2)));
  }
  if(good2 > 0) {
    ans = ADD(ans, MUL(good2, f(n-1, bad, good+1, good2-1)));
  }

  DP[key] = ans;
  return ans;
}
ll Q(ll n) {
  ll ans = 0;
  for(ll d=1; d<=9; d++) {
    if(d%2==0) {
      ans = ADD(ans, f(n-1, 1, 4, 5));
    } else {
      ans = ADD(ans, f(n-1, 0, 6, 4));
    }
  }
  return ans;
}
ll ix(ll bad, ll good) { return bad*11 + good; }
ll fastQ(ll n) {
  mat M(122, vector<ll>(122, 0));
  for(ll bad=0; bad<=10; bad++) {
    for(ll good=0; bad+good<=10; good++) {
      ll good2 = 10 - bad - good;
      if(bad > 0) { M[ix(bad-1, good+1)][ix(bad, good)] = bad; }
      if(good > 0) { M[ix(bad+1, good-1)][ix(bad, good)] = good; }
      if(good2 > 0) { M[ix(bad, good+1)][ix(bad, good)] = good2; }
      if(bad==0) { M[121][ix(bad, good)] = 1; }
    }
  }
  M[121][121] = 1;

  mat V(122, vector<ll>(1, 0));
  V[ix(1, 4)][0] = 4;
  V[ix(0, 6)][0] = 5;
  V[121][0] = 0;
  mat M2 = mat_pow(M, n);
  mat V2 = mat_mult(M2, V);

  return V2[121][0];
}

int main() {
  ll U = 39;
  ll ans = 0;
  for(ll u=1; u<=U; u++) {
    printf("%lld\n", u);
    ans = ADD(ans, fastQ(1L<<u));
  }
  printf("%lld\n", ans);
}