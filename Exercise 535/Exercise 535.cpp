const int maxp = 100000;
#include <pe>

const int N = 1000000;
int pre[] = {0,1,1,2,1,3,2,4,1,5,3,6,2,7,8,4,9,1,10,11,5};
int64* data;
int64* ps1;
int64* ps2;
const int64 mod = 1000000000;
void init()
{
  data = new int64[N+1];
  ps1 = new int64[N+1];
  ps2 = new int64[N+1];
  for (int i = 1; i <= 20; ++i) data[i] = pre[i];
  int i = 10;
  int64 j = 12;
  int top = 21;
  while (top <= N)
  {
    int how = sqrt(data[i]);
    for (int t = 0; top <= N && t < how; ++t)
      data[top++] = j++;
    if (top <= N)
    data[top++] = data[i++];
  }
  int64 last1 = 0;
  int64 last2 = 0;
  for (int i = 1; i <= N; ++i)
  {
    last1 = (last1 + data[i]) % mod;
    last2 += sqrt(data[i]);
    ps1[i] = last1;
    ps2[i] = last2;
  }
}

map<int64, int64> mem1;
map<int64, int64> mem2;
int64 compute1(int64 n)
{
  return n&1 ?
    mul_mod((n+1>>1)%mod, n%mod, mod) :
    mul_mod((n+1)%mod, (n>>1)%mod, mod);
}

int64 compute2(int64 n)
{
  if (n <= 3) return n;
  int64 t = sqrt(n);
  int64 ret = 0;
  int64 i = 1;
  while ((i + 1) * (i + 1) <= n)
  {
    ret += i * ((i + 1) * (i + 1) - i * i);
    ++i;
  }
  ret += i * (n - i * i + 1);
  return ret;
}

int64 find_sum2(int64 n);
int64 find_sum1(int64 n)
{
  if (n <= N) return ps1[n];
  auto where = mem1.find(n);
  if (where != mem1.end()) return where->second;
  int64 l = 1, r = min(10000000000000LL, n);
  while (l <= r)
  {
    int64 mid = l + r >> 1;
    if (find_sum2(mid) + mid >= n) r = mid - 1; else l = mid + 1;
  }
  const int64 how = find_sum2(l);
  const int64 extra = how + l - n;
  const int64 remain = extra > 1 ? how - extra + 1 : how;
  int64 ret = compute1(remain);
  ret += find_sum1(n - remain);
  return mem1[n] = ret % mod;
}

int64 find_sum2(int64 n)
{
  if (n <= N) return ps2[n];
  auto where = mem2.find(n);
  if (where != mem2.end()) return where->second;
  int64 l = 1, r = min(10000000000000LL, n);
  while (l <= r)
  {
    int64 mid = l + r >> 1;
    if (find_sum2(mid) + mid >= n) r = mid - 1; else l = mid + 1;
  }
  const int64 how = find_sum2(l);
  const int64 extra = how + l - n;
  const int64 remain = extra > 1 ? how - extra + 1 : how;
  int64 ret = compute2(remain);
  ret += find_sum2(n - remain);
  return mem2[n] = ret;
}

int main()
{
  init();
  cerr << find_sum1(1000000000000000000LL) << endl;
  return 0;
}