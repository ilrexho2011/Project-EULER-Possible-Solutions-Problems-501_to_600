#include <iostream>

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

long int doPower( long int n, long int k, long int base )
{
   long int val = 1;
   long int pow = n;
   while ( k )
   {
      if ( k%2 )
      {
         val *= pow;
         val %= base;
      }
      pow *= pow;
      pow %= base;
      k /= 2;
   }
   return val;
}

int main()
{
  long int n = 12344321;
  long int mod = 135707531;
  
  long int sum = doPower(n-2,n-1,mod);
  sum *= n;
  sum %= mod;
  sum *= n-1;
  sum %= mod;

  long int loopbase = n;
  for ( long int l = 2 ; l < n-1 ; ++l )
  {
    loopbase *= n-l+1;
    loopbase %= mod;
    loopbase *= l-1;
    loopbase %= mod;
    loopbase *= invert(l,mod);
    loopbase %= mod;
    sum += loopbase*doPower(n-l-1,n-l,mod);
    sum %= mod;
  }
  
  std::cout << sum << std::endl;
}
