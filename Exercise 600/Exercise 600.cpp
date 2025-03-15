const int maxp = 100000;
#include <pe>

vi regulate(vi x)
{
  vi ret;
  for (int i = 0; i < 6; ++i)
  {
    rotate(x.begin(), x.begin() + 1, x.end());
    if (sz(ret) == 0 || x < ret) ret = x;
  }
  reverse(all(x));
  for (int i = 0; i < 6; ++i)
  {
    rotate(x.begin(), x.begin() + 1, x.end());
    if (sz(ret) == 0 || x < ret) ret = x;
  }
  return ret;
}

int64 dp[1000000];
int main()
{
  init_primes();
  for (int64 n = 2; n <= 50; ++n)
  {
    int64 ans = 0;
    map<vi, int> mem;
    for (int L = 1; L <= n; ++L)
    for (int64 x = 1; x <= L; ++x)
    for (int64 y = 1; y <= L; ++y)
    {
      if (x + y >= L) break;
      for (int64 z = 1; z <= L; ++z)
      {
        if (x + z >= L) break;
        if (y + z >= L) break;
        {
          if (L*3-x-y-z > n) continue;
          vi orz;
          orz.pb(x);
          orz.pb(L-x-y);
          orz.pb(y);
          orz.pb(L-y-z);
          orz.pb(z);
          orz.pb(L-x-z);
          mem[regulate(orz)]++;
        }
      }
    }
    dp[n] = sz(mem);
  }
  for (int i = 50; i <= 55106; ++i)
  {
    dp[i] = dp[i-1] + dp[i-2] - 2*dp[i-5]
    +dp[i-6] - dp[i-7] + dp[i-9] - dp[i-10]
    +2*dp[i-11] -dp[i-14]-dp[i-15]+dp[i-16];
  }
  cerr << dp[100] << endl;
  cerr << dp[55106] << endl;
  return 0;
}