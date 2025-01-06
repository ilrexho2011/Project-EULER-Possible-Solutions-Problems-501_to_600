#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

//    Values for F(10^5)
#define PLIM 100000000
#define MLIM 3000000
#define TARG 100000

//    Values for F(10^6)
// #define PLIM 2000000000
// #define MLIM 35000000
// #define TARG 1000000

char* prime;

bool isPrime( long long int num )
{
  if ( num < PLIM )
    return prime[num];
  for ( long long int p = 3 ; p*p <= num ; p+=2 )
    if ( prime[p] && !(num%p) )
      return false;
  return true;
}

struct cand {
  long long int val;
  std::vector< long long int > div;
};

int main()
{
  prime = new char[PLIM];
  int plimsq = sqrt(PLIM);
  for ( int i = 0 ; i < PLIM ; ++i )
    prime[i] = 1;
  prime[1] = 0;
  for ( int i = 3 ; i < plimsq ; i+=2 )
    if ( prime[i] )
      for ( int goUp = 3*i ; goUp < PLIM ; goUp += 2*i )
        prime[goUp] = 0;

  long long int divs[8] = { 2,  4,  14,  22,
                           28, 44, 154, 308 };
  std::vector<cand> reg;
  std::vector<cand> nex;
  std::vector<long long int> good;
  cand tmp;
  tmp.val = 1;
  tmp.div.push_back(1);
  reg.push_back(tmp);
  long long int breakPoint = (MLIM/142)*2;
  for ( int p = 3 ; p < breakPoint ; p+=2 )
  {
    if ( !isPrime(p) )
      continue;
    bool ok = true;
    for ( int i = 0 ; i < 8 ; ++i )
    {
      if ( isPrime(p*divs[i]+1) )
      {
        ok = false;
        break;
      }
    }
    if ( !ok )
      continue;
    int sz = reg.size();
    for ( int i = 0 ; i < sz ; ++i )
    {
      tmp = reg[i];
      int dsz = tmp.div.size();
      long long int currp = p;
      while ( tmp.val*currp < MLIM )
      {
        tmp.val *= currp;
        for ( int j = 0 ; j < dsz ; ++j )
          tmp.div.push_back(tmp.div[j]*currp);
        reg.push_back(tmp);
        tmp.val = reg[i].val;
        currp *= p;
      }
    }
    sz = reg.size();
    nex.clear();
    for ( int i = 0 ; i < sz ; ++i )
    {
      if ( reg[i].val*p > MLIM )
      {
        bool ok = true;
        int dsz = reg[i].div.size();
        for ( int j = 2 ; j < dsz ; ++j )
        {
          long long int d = reg[i].div[j];
          for ( int k = 0 ; k < 8 ; ++k )
          {
            if ( isPrime(d*divs[k]+1) )
            {
              ok = false;
              break;
            }
          }
          if ( !ok )
            break;
        }
        if ( ok )
          good.push_back(reg[i].val);
      }
      else
        nex.push_back(reg[i]);
    }
    reg = nex;
  }
  for ( unsigned int i = 0 ; i < reg.size() ; ++i )
    good.push_back(reg[i].val);

  for ( int p = breakPoint+1 ; p < MLIM ; p+=2 )
  {
    if ( !isPrime(p) )
      continue;
    bool ok = true;
    for ( int i = 0 ; i < 8 ; ++i )
    {
      if ( isPrime(p*divs[i]+1) )
      {
        ok = false;
        break;
      }
    }
    if ( ok )
      good.push_back(p);
  }

  std::sort(good.begin(),good.end());
  std::cout << "Target: " << TARG << "   Multiplier: " << good[TARG-1]
            << "   Value: " << 308*good[TARG-1] << std::endl;
}
