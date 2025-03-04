const int maxp = 100000;
#include <pe>

const int64 mod = 1000000000;
const int64 pmod = mod / 2 / 5 * 4;
const int n = 50000;
map<int64, int64> pre[20][2];
int64 comb[6000][6000];

int64 dfs(int now, int n, int mask, int64 value, int64 cnt)
{
  int64 ret = 0;
  if (now == n)
  {
    return power_mod(2, value, mod) * cnt % mod;
  }
  else
  {
    int64 ret = 0;
    for (auto& iter: (1 << now) & mask ? pre[now][1] : pre[now][0])
    {
      ret += dfs(now+1, n, mask, value*iter.first%pmod, cnt*iter.second%mod);
    }
    return ret % mod;
  }
}

int main()
{
  init_primes();
  for (int i = 0; i < 6000; ++i)
    for (int j = 0; j <= i; ++j)
      comb[i][j] = j == 0 ? 1 : add_mod(comb[i-1][j], comb[i-1][j-1], mod);
  map<int, int> mem;
  for (int i = 0; plist[i] <= n; ++i)
  {
    int64 p = plist[i];
    int64 c = 1;
    int64 v = p;
    while (v * p <= n) v *= p, ++c;
    mem[c]++;
  }
  int top = 0;
  for (auto& iter: mem)
  {
    for (int64 v = 0; v <= iter.second; ++v)
    {
      int64 u = iter.second - v;
      int64 a = power_mod(iter.first+1, u, pmod);
      int64 b = power_mod(iter.first, v, pmod);
      int64 c = comb[iter.second][v];
      int64 now = a * b % pmod;
      if (v & 1) pre[top][1][now] = add_mod(pre[top][1][now], c, mod);
      else pre[top][0][now] = add_mod(pre[top][0][now], c, mod);
    }
    ++top;
  }
  int limit = 1 << top;
  int64 ans = 0;
  for (int mask = 0; mask < limit; ++mask)
  {
    cerr << mask << " " << limit << endl;
    int64 t = dfs(0, top, mask, 1, 1);
    if (__builtin_popcount(mask)&1) ans -= t; else ans += t;
    ans = regulate_mod(ans, mod);
  }
  dbg(ans);
  return 0;
}