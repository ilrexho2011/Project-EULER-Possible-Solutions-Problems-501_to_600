#include <stdio.h>
#include <quadmath.h>

static struct { long u, v; } pq[64], ab[32];
const long max = (long)1e13; // 48      20

int convergents(int n)
{ // The convergents of continued fraction of √n.
  int i = 0;
  for (long r = (long)sqrtq(n), t = r, m = 0, s = 1,
    a = 0, b = 1, c = 1, d = 0; c <= max; i++)
    pq[i].u = c * t + a, a = c, c = pq[i].u,
    pq[i].v = d * t + b, b = d, d = pq[i].v,
    m = s * t - m, t = (r + m) / (s = (n - m * m) / s);
  return i; // i < 48
}

void g(__float128 r, __float128 *pe, int *pk, int i, int j, int s)
{
  long a = ab[j].u + s * pq[i].u, b = ab[j].v - s * pq[i].v;
  __float128 e = fabsq(a + b * r - M_PIq);
  if (e >= *pe || labs(a) > max) return;
  *pe = e, ab[++*pk].u = a, ab[*pk].v = b;
}

long f(int d)
{ // The integral part of best approximation (about √d).
  int k = ab[0].v = 0; ab[0].u = (int)M_PIq;
  __float128 r = sqrtq(d), e = fabsq(M_PIq - ab[0].u);
  for (int i9 = convergents(d), i = 0; i < i9; i++) {
    for (int j = 0; j <= k; j++)
      g(r, &e, &k, i, j, 1), g(r, &e, &k, i, j, -1);
    if (k > 1) ab[0] = ab[k - 1], ab[1] = ab[k], k = 1;
  }  // k < 20
  return ab[k].u;
}

int main(void)
{ // https://projecteuler.net/problem=591
  long z = 0;
  for (int d, i = 2; i < 100; i++)
    if (sqrtq(i) != roundq(sqrtq(i))) z += labs(f(i));
  printf("%ld\n", z);
}