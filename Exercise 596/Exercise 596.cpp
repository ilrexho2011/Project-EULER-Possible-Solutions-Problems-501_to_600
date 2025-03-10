const int maxp = 100000;
#include <pe>

const int64 mod = 1000000007;
const int64 n = 10000000000000000LL;

int main()
{
  init_primes();
  int64 ans = 0;
  for (int64 d = 1; d <= n;)
  {
    int64 v = n / d;
    int64 maxd = n / v;
    int128 x = d;
    int128 y = maxd;
    int128 z = (x + y) * (y - x + 1) / 2;
    int64 zz = z % mod;
    int64 now = v * zz % mod;
    ans = add_mod(ans, now, mod);
    d = maxd + 1;
  }
  for (int64 d = 1; d <= n / 4;)
  {
    int64 v = n / 4 / d;
    int64 maxd = n / v / 4;
    int128 x = d;
    int128 y = maxd;
    int128 z = (4 * x + 4 * y) * (y - x + 1) / 2;
    int64 zz = z % mod;
    int64 now = v * zz % mod;
    ans = sub_mod(ans, now, mod);
    d = maxd + 1;
  }
  cerr << (ans * 8 + 1) % mod << endl;
  return 0;
}