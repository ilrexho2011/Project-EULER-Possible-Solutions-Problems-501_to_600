const int maxp = 100000;
#include <pe>

int data[100][2];
map<pair<int64, int64>, int64> mem;
void dfs0(int now, int m, int64 x, int64 y)
{
  if (now == m)
  {
    int64 d = gcd(x, y);
    ++mem[{x/d,y/d}];
    return;
  }
  for (int i = 0; i <= data[now][1]; ++i)
  {
    dfs0(now+1, m, x*(i+1), y*(data[now][1]-i+1));
  }
}

int64 ans = 0;
int64 dfs1_impl(int now, int m, int64 x, int64 y)
{
  if (now == m)
  {
    int64 d = gcd(x, y);
    x /= d, y /= d;
    auto where = mem.find({y, x});
    if (where != mem.end()) return where->second;
    return 0;
  }
  int64 ret = 0;
  for (int i = 0; i <= data[now][1]; ++i)
  {
    ret += dfs1_impl(now+1, m, x*(i+1), y*(data[now][1]-i+1));
  }
  return ret;
}
void dfs1(int now, int m, int64 x, int64 y)
{
  if (now == m)
  {
    int64 d = gcd(x, y);
    x /= d, y /= d;
    auto where = mem.find({y, x});
    if (where != mem.end()) ans += where->second;
    return;
  }
  int64 me = 0;
  #pragma omp parallel for schedule(dynamic, 1) num_threads(30) reduction(+:me)
  for (int i = 0; i <= data[now][1]; ++i)
  {
    me += dfs1_impl(now+1, m, x*(i+1), y*(data[now][1]-i+1));
  }
  ans = me;
}

int main()
{
  init_primes();
  int top = 0;
  const int n = 100;
  int64 total0 = 1;
  int64 total1 = 1;
  const int T = 5;
  for (int i = 0; ; ++i)
  {
    int p = plist[i];
    if (p > n) break;
    int c = 0;
    int x = p;
    while (x <= n)
    {
      c += n / x;
      x *= p;
    }
    data[top][0] = p;
    data[top++][1] = c;
    if (i < T) total0 *= c + 1;
    else total1 *= c + 1;
  }
  dbg(total0);
  dbg(total1);
  dfs0(0, T, 1, 1);
  dbg(sz(mem));
  dfs1(T, top, 1, 1);
  dbg(ans/2);
  return 0;
}