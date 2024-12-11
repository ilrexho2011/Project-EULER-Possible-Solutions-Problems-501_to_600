#include <iostream>
#include <vector>
#include <cmath>

std::vector<int> prs;

int D( int N, int i )
{
  if ( i == 0 )
    return N;
  return D( N, i-1 ) - D( N/prs[i], i-1 );
}

int S( int N, int i )
{
  if ( i == 0 )
    return N*(N+1)/2;
  return S( N, i-1 ) - prs[i]*S( N/prs[i], i-1 );
}

int main()
{
  char* prime = new char[1000000];
  for ( int i = 0 ; i < 1000000 ; ++i )
    prime[i] = 1;
  prime[0] = 0;
  prime[1] = 0;
  for ( int i = 2 ; i < 1000 ; ++i )
    if ( prime[i] )
      for (int goUp = i+i ; goUp < 1000000 ; goUp += i)
        prime[goUp] = 0;

  int* numpr = new int[1000000];
  numpr[0] = 0;
  prs.push_back(-1);    // Dummy to get ith prime at location i
  for ( int i = 1 ; i < 1000000 ; ++i )
  {
    numpr[i] = numpr[i-1];
    if ( !prime[i] )
      continue;
    numpr[i] += 1;
    prs.push_back(i);
  }

  int N = 100;
  int n = numpr[int(sqrt(N))];
  int R = S(N,n)-1;
  for ( int i = 1 ; i <= n ; ++i )
    R += prs[i]*D(N/prs[i],i-1);

  std::cout << R << std::endl;
}