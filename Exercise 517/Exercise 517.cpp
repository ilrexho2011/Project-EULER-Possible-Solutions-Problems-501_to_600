#include <iostream>
#include <cmath>
#include <vector>

long int reduc[100];
long int ans[100];

long int invert( long int num, long int base )
{
  reduc[0] = base;
  reduc[1] = num;
  ans[0] = 0;
  ans[1] = 1;
  int curr = 1;
  while ( reduc[curr] != 1 )
  {
    long int div = reduc[curr-1]/reduc[curr];
    reduc[curr+1]=reduc[curr-1]-div*reduc[curr];
    ans[curr+1] = ans[curr-1]-div*ans[curr];
    ++curr;
  }
  return (ans[curr]+base)%base;
}

int main() {
  long int mod = 1000000007;

  char* prime = new char[11000000];
  for ( int i = 0 ; i < 11000000 ; ++i )
    prime[i] = 1;
  prime[0] = 0;
  prime[1] = 0;
  for ( int i = 2 ; i < 4000 ; ++i )
    if ( prime[i] )
      for ( int goUp = i+i ; goUp < 11000000 ; goUp += i )
        prime[goUp] = 0;

  long int* fact = new long int [10100000];
  long int* factinv = new long int[10100000];
  fact[0] = 1;
  factinv[0] = 1;
  for ( int i = 1 ; i < 10100000 ; ++i )
  {
    fact[i] = (fact[i-1]*i)%mod;
    factinv[i] = invert(fact[i],mod);
  }

  long int sum = 0;
  for ( int x = 10000000 ; x < 10010000 ; ++x )
  {
    if ( !prime[x] )
      continue;
    double a = sqrt(x);
    sum += 1;
    for ( int k = 1 ; k < a ; ++k )
    {
      int top = k+x-a*k;
      long int val = fact[top];
      val *= factinv[k];
      val %= mod;
      val *= factinv[top-k];
      val %= mod;
      sum += val;
    }
  }
  std::cout << sum%mod << std::endl;
}
