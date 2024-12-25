const int maxp = 100000;
#include <pe>

int mat[32][32];
const int N = 14;
const int M = N + 1;
int L;

int64 dfs(int curr)
{
  if (curr == N) return 1;
  int64 ret = 0;
  for (int i = 0; i < N; ++i)
  if (mat[curr][i] == 0)
  {
    for (int j = 1; j <= L; ++j)
    {
      if (curr + j < N)
      {
        ++mat[curr+j][i];
        if (i - j >= 0) ++mat[curr+j][i-j];
        if (i + j < N) ++mat[curr+j][i+j];
      }
    }
    ret += dfs(curr+1);
    for (int j = 1; j <= L; ++j)
    {
      if (curr + j < N)
      {
        --mat[curr+j][i];
        if (i - j >= 0) --mat[curr+j][i-j];
        if (i + j < N) --mat[curr+j][i+j];
      }
    }
  }
  return ret;
}

int64 dp(int L)
{
  map<int, int64> last;
  last[0] = 1;
  for (int i = 1; i <= N; ++i)
  {
    map<int, int64> curr;
    for (auto& iter: last)
    {
      int data[32];
      for (int i = 1, j = iter.first; i <= L; ++i, j /= M)
      {
        data[i] = j % M;
      }
      for (int k = 1; k <= N; ++k)
      {
        int ok = 1;
        for (int x = 1; x <= L; ++x)
        {
          if (data[x] == 0) continue;
          if (data[x] == k) {ok = 0; break;}
          if (data[x] + x == k) {ok = 0; break;}
          if (data[x] - x == k) {ok = 0; break;}
        }
        if (ok)
        {
          int s = 0;
          for (int x = L - 1; x >= 1; --x) s = s * M + data[x];
          s = s * M + k;
          curr[s] += iter.second;
        }
      }
    }
    curr.swap(last);
  }
  int64 ret = 0;
  for (auto& iter: last) ret += iter.second;
  return ret;
}

int main()
{
  int64 ans = 0;
  for (L = 0; L <= N - 1; ++L)
  {
    ans += L <= 7 ? dp(L) : dfs(0);
  }
  dbg(ans);
  return 0;
}