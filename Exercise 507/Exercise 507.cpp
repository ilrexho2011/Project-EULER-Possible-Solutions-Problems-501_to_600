#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  int N = argc > 1 ? atoi(argv[1]) : 20000000;
  long long i, m, j, k, u, v, a, b, q, e, f, t;
  long long V[3], W[3], T[12], total = 0;
  __int128_t x, s;
  
  T[9] = -1;
  T[10] = 1;
  T[11] = 0;
  
  for(i = 1; i <= N; i++) {
    for(j = 0; j < 12; j++)
      T[j] = (T[(j + 9) % 12] + T[(j + 10) % 12] + T[(j + 11) % 12]) % 10000000;
    
    V[0] = T[0] - T[1];
    V[1] = T[2] + T[3];
    V[2] = T[4] * T[5];
    
    W[0] = T[6] - T[7];
    W[1] = T[8] + T[9];
    W[2] = T[10] * T[11];
    
    m = 1LL << 62;
    
    for(j = 0; j < 3; j++) {      
      a = V[j], b = W[j];
      u = 0, v = 1;
      e = 1, f = 0;
      
      while(b != 0) {
	for(k = s = 0; k < 3; k++) {
	  x = v * (__int128_t)V[k] + f * (__int128_t)W[k];
	  s += x < 0 ? -x : x;
	}
	
	m = s < m ? s : m;
	
	q = a / b;
        t = b, b = a - q * b, a = t;
	t = u, u = v - q * u, v = t;
	t = e, e = f - q * e, f = t;
      }
    }
    total += m;
  }
  
  printf("%lld\n", total);
  
  return 0;
}