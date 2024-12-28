#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;

const int N = 20000;
const int K = 20000;
const int MOD = 1004535809;

vi primes, bs;
void sieve(int n) {
  bs = vi(n + 1, 1);
  bs[0] = bs[1] = 0;
  for (ll i = 2; i <= n; i++) {
    if (bs[i]) {
      primes.push_back(i);
      for (ll j = i*i; j <= n; j += i) bs[j] = 0;
    } 
  }
}

vi pi(1), freq(N + 1);
map<int, vi> memo;
vi f(int k) {
  if (k == 1) return freq;
  if (memo.count(k)) return memo[k];

  int k1 = k/2;
  int k2 = k-k1;

  vi ans1 = f(k1);
  vi ans2 = f(k2);
  vi ans(N+1);
  for (int i = 0; i <= N; i++) {
    for (int j = 0; j <= N; j++) {
      if (i + j > N) break;
      ans[i+j] += (((ll)ans1[i]*ans2[j]) % MOD);
      if (ans[i+j] >= MOD) ans[i+j] -= MOD;
    }
  }
  memo[k] = ans;
  return ans;
}

int main() {
  sieve(1e6);
  for (int i = 1; i <= 1e6; i++) {
    pi.push_back(pi.back());
    if (bs[i]) pi[i]++;
  }
  int i = 1;
  while (pi[i] <= N) {
    freq[pi[i]]++;
    i++;
  }
  vi ans = f(K);
  cout << ans[N] << endl;
  return 0;
}