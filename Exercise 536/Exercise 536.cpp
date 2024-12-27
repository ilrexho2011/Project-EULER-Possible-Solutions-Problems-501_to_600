#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned int modinv(unsigned int a, unsigned int n, unsigned int *g)
{
  unsigned int b = n, q;
  int u = 0, v = 1;

  while(1) {
    if (b == 0) {
      *g = a;
      return (v + n) % n;
    }
    q = a / b;
    a -= q * b;
    v -= q * u;

    if (a == 0) {
      *g = b;
      return (u + n) % n;
    }
    q = b / a;
    b -= q * a;
    u -= q * v;
  }  
}

unsigned long long count(unsigned long long N, 
			 unsigned long long n, 
			 unsigned int *primes,  
			 unsigned int *f, unsigned int k, 
			 char *iscomp)
{
  unsigned long long total = 0, s, a, q;
  unsigned int *p, i, g;
  
  if (k && *primes) {
    if (n % 3 == 0 && (f[k-1] - 1) % 3 == 0) {
      q = (f[k-1] - 1) / 3;
      s = q - modinv(n / 3 % q, q, &g);
    }
    else {
      q = (f[k-1] - 1);
      s = (q - 3) * (unsigned long long)modinv(n % q , q, &g) % q;
    }
    
    if (g == 1) {
      a = *primes / q * q + s;
      if (a < *primes)
	a += q;
      for(; n * a <= N && a * (a - 4) <= N; a += q)
	if (!iscomp[a]) {
	  if ((n * a + 3) % (a - 1) != 0)
	    continue;
	  for(i = 0; i < k - 1; i++)
	    if ((n * a + 3) % (f[i] - 1) != 0)
	      break;
	  if (i == k - 1)
	    total += n * a;
	}
    }
  }
  
  for(p = primes; *p && n <= N / ((unsigned long long)*p * *p); p++) {
    f[k] = *p;
    total += count(N, n * *p, p + 1, f, k + 1, iscomp);
  }

  return total;
}

int main(int argc, char **argv)
{
  unsigned long long N = argc > 1 ? atoll(argv[1]) : 1;
  unsigned int S = sqrt(4 + N) + 3;
  unsigned long long i, j;
  char *s = calloc(S + 1, 1);
  unsigned int *primes = calloc(S + 1, sizeof(int)), nprimes = 0;
  unsigned int f[20];
  
  for(i = 2; i <= S; i++)
    if (s[i] == 0) {
      primes[nprimes++] = i;
      if (i * i <= S)
	for(j = i * 2; j <= S; j += i)
	  s[j] = 1;     
    }
  
  printf("%llu\n", count(N, 1, primes + 1, f, 0, s) + 11);
  
  return 0;
}