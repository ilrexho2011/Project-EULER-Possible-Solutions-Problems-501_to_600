const int maxp = 100000;
#include <pe>

const int64 N = 100000000000000000LL;
vector<pair<int64, int64>> vec;

int64 pv[1000];
int64 pc[1000];

void iterate_factors(const int limit, int64 value, int64 n, int64& result)
{
  if (n % value % value != 0) return;
  if (value > 1)
  {
    int64 a = value - 1;
    int64 b = value;
    int64 s = n;
    int64 now = n;
    while (now % b == 0)
    {
      now = now / b * a;
      s += now;
    }
    if (s > result) result = s;
  }
  for (int i = 0; i < limit; ++i)
  {
    int64 temp = value;
    for (int j = 0; j < pc[i] / 2; ++j)
    {
      temp *= pv[i];
      iterate_factors(i, temp, n, result);
    }
  }
}

void dfs(int limit, int64 a, int top)
{
  if (top > 4) return;
  if (top > 0)
  {
    int64 result = 0;
    iterate_factors(top, 1, a, result);
    if (result > 0) vec.pb({a, result});
  }
  for (int i = 0; i < limit; ++i)
  {
    const int64 p = plist[i];
    if (p > N / a) break;
    pv[top] = p;
    pc[top] = 0;
    for (int64 x = a; p <= N / x;)
    {
      x *= p;
      ++pc[top];
      dfs(i, x, top+1);
    }
  }
}

int main()
{
  init_primes();
  int limit = 0;
  while (plist[limit] <= 47) ++limit;
  dfs(limit, 1, 0);
  vec.pb({N+1, 0L});
  sort(vec.begin(), vec.end());
  int64 ans = 0;
  const int size = sz(vec);
  for (int i = 0; i + 1 < size;)
  {
    int j = i + 1;
    while (vec[j].first <= N && vec[j].second <= vec[i].second) ++j;
    if ((vec[j].first - vec[i].first)&1)
    {
      if (vec[i].first&1) ans -= vec[i].second;
      else ans += vec[i].second;
    }
    i = j;
  }
  dbg(ans);
  return 0;
}