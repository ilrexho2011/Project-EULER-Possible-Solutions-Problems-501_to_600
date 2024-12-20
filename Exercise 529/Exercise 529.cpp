#include <cstdio>
#include <vector>
#include <queue>
#include <cassert>
#include <map>

using namespace std;

typedef long long ll;
typedef vector<ll> row;
typedef vector<row> mat;

ll MOD = 1000000007LL;
ll ADD(ll x, ll y) { return (x+y)%MOD; }
ll MUL(ll x, ll y) { return (x*y)%MOD; }

bool is_good(ll n, ll B) {
  vector<ll> D;
  while(n>0) {
    D.insert(D.begin(), n%B);
    n/=B;
  }
  vector<int> ok(D.size(), 0);
  for(ll st=0; st<D.size(); st++) {
    for(ll ed=0; ed<D.size(); ed++) {
      ll sum = 0;
      for(ll i=st; i<=ed; i++) {
        sum += D[i];
      }
      if(sum==B) {
        for(ll i=st; i<=ed; i++) {
          ok[i] = true;
        }
      }
    }
  }
  for(ll i=0; i<D.size(); i++) {
    if(!ok[i]) {
      return false;
    }
  }
  return true;
}

ll slow(ll n, ll B) {
  ll pB = 1;
  for(ll i=1l; i<=n; i++) {
    pB *= B;
  }
  ll ans = 0;
  for(ll n=1; n<=pB; n++) {
    if(is_good(n, B)) {
      //printf("%lld\n", n);
      ans++;
    }
  }
  return ans;
}

bool bit_set(int set, int bit) {
  return ((set>>bit)&1)==1;
}

mat mat_mult(mat A, mat B) {
  mat C(A.size(), row(B[0].size(), 0));
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
  if(e==1) {
    return A;
  } else if(e%2==0) {
    return mat_pow(mat_mult(A, A), e/2);
  } else {
    return mat_mult(A, mat_pow(A, e-1));
  }
}

ll mk_state(ll bits, ll unfilled, ll B) {
  return bits + (1L<<(B-1))*unfilled;
}

void show_state(ll state, ll B) {
  ll unfilled = state/(1L<<(B-1));
  for(ll b=0; b<B-1; b++) {
    printf("%d", bit_set(state, b));
  }
  printf(" %lld\n", unfilled);
}
void show_mat(mat M) {
  for(ll i=0; i<M.size(); i++) {
    for(ll j=0; j<M[i].size(); j++) {
      printf("%lld ", M[i][j]);
    }
    printf("\n");
  }
}

int main() {
  ll B = 3;
  ll n = 1000LL*1000*1000*1000*1000*1000;
  ll S = (1L<<(B-1))*B;

  mat M(S, row(S, 0));
  for(ll a=0; a<S; a++) {
    for(ll d=0; d<=B-1; d++) {
      bool ok = true;
      ll next = 0;
      if(d > 0) {
        next |= 1L<<(d-1);
      }
      ll unfilled = a/(1L<<(B-1));
      ll next_unfilled = d==0 ? unfilled : unfilled+1;
      ll n_suffixes = 0;
      for(ll b=0; b<B-1; b++) {
        if(bit_set(a, b)) {
          n_suffixes++;
          if(b+1+d > B && n_suffixes<=unfilled) {
            ok = false;
          } else if(b+1+d == B) {
            next_unfilled = 0;
          } else if(b+1+d < B) {
            next |= 1L<<(b+1+d-1);
          }
        }
      }
      if(n_suffixes < unfilled) { continue; }
      next = mk_state(next, next_unfilled, B);
      if(ok) {
        if(next >= M.size()) {
          show_state(a, B);
          printf("%lld\n", d);
          printf("BAD\n");
        }
        M[a][next]++;
        bool show = false;
        for(ll b=0; b<B-1; b++) {
          if(a == (1L<<b)) {
            show = true;
          }
        }
        if(show) {
        }
      }
    }
  }

  vector<int> SEEN(S, 0);
  queue<int> Q;
  Q.push(0);
  while(!Q.empty()) {
    ll x = Q.front(); Q.pop();
    if(SEEN[x]) { continue; }
    SEEN[x] = true;
    for(ll a=0; a<S; a++) {
      if(M[x][a] > 0) {
        Q.push(a);
      }
    }
  }
  ll count = 0;
  for(ll a=0; a<S; a++) {
    if(!SEEN[a]) {
      count++;
    }
  }
  printf("used=%lld unused=%lld\n", M.size()-count, count);

  mat N = mat(M.size()-count, row(M.size()-count, 0));
  vector<ll> state_to_row(M.size(), 0);
  ll si = 0;
  for(ll i=0; i<M.size(); i++) {
    if(SEEN[i]) {
      state_to_row[i] = si;
      si++;
    }
  }
  for(ll i=0; i<M.size(); i++) {
    for(ll j=0; j<M.size(); j++) {
      if(SEEN[i] && SEEN[j]) {
        N[state_to_row[i]][state_to_row[j]] = M[i][j];
      }
    }
  }

  mat N2 = mat_pow(N, n);

  show_mat(N);
  printf("\n\n");
  show_mat(N2);

  ll ans = 0;
  for(ll a=0; a<S; a++) {
    ll unfilled = a/(1L<<(B-1));
    if(unfilled==0) {
      ans += N2[0][state_to_row[a]];
    }
  }
  ans = ADD(ans, MOD-1);
  printf("%lld\n", ans);
  printf("%lld\n", slow(n, B));
  assert(ans == slow(n, B));
}