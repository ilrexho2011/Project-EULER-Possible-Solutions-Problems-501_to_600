const int maxp = 100000;
#include <pe>
const int N = 1000000;
double dp[N+1];

int main()
{
  dp[N] = 1.*(N+1)/2;
  for (int i = N-1; i >= 1; --i)
  {
    /*
      j = 0, i*(N+1) / (i+1)
      j = 1, (i-1)*(N+1) / (i+1)
      ...
      j = i - 1, (N+1) / (i+1)
    */
    const double last = dp[i+1];
    int l = 0, r = i - 1;
    while (l <= r)
    {
      const int mid = l + r >> 1;
      if (1.*(i-mid) * (N+1) < last * (i+1))
        r = mid - 1;
      else l = mid + 1;
    }
    double ans = last * (r + 1) + 1. * (1 + i - l) * (i - l) / 2 * (N+1) / (i + 1);
    dp[i] = ans / i;
  }
  printf("%.16f\n", dp[1]);
  return 0;
}