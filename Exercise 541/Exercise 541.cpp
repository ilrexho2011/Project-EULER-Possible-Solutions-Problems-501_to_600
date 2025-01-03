#include <iostream>
#include <vector>

unsigned long long int reduc[100];
unsigned long long int ans[100];

unsigned long long int invert( unsigned long long int num, unsigned long long int base )
{
  reduc[0] = base;
  reduc[1] = num%base;
  ans[0] = 0;
  ans[1] = 1;
  int curr = 1;
  while ( reduc[curr] != 1 )
  {
    unsigned long long int div = reduc[curr-1]/reduc[curr];
    reduc[curr+1]=reduc[curr-1]-div*reduc[curr];
    ans[curr+1] = ans[curr-1]-div*ans[curr];
    ++curr;
  }
  return (ans[curr]+base)%base;
}

std::vector<unsigned long long int> pow;

struct info {
  int power;
  unsigned long long int len;
  unsigned long long int val;
};

std::vector<info> infos;

int starter( unsigned long long int targ, unsigned long long int p )
{
  unsigned long long int targcp = targ;
  int sz = 0;
  while ( targcp )
  {
    ++sz;
    targcp /= p;
  }
  info tmp;
  unsigned long long int sum = 0;
  for ( int z = 1 ; z < sz ; ++z )
  {
    unsigned long long int zsum = 0;
    unsigned long long int upper = (targ/pow[z])%pow[z+1];
    int best = -1;
    unsigned long long int bestlen = 0;
    int isz = infos.size();
    for ( int k = 0 ; k < isz ; ++k )
    {
      if ( infos[k].power != z )
        continue;
      if ( infos[k].len > upper )
        continue;
      if ( infos[k].len > bestlen )
      {
        bestlen = infos[k].len;
        best = k;
      }
    }
    if ( bestlen == upper )
      zsum = infos[best].val;
    if ( bestlen > 0 )
    {
      zsum = infos[best].val;
      for ( unsigned long long int i = bestlen+1 ; i <= upper ; ++i )
        if ( i%p )
          zsum = (zsum+invert(i,pow[z+1]))%pow[z+1];
    }
    else
      for ( unsigned long long int i = 1 ; i <= upper ; ++i )
        if ( i%p )
          zsum = (zsum+invert(i,pow[z+1]))%pow[z+1];
    tmp.power = z;
    tmp.len = upper;
    tmp.val = zsum;
    infos.push_back(tmp);
    sum = p*((sum+zsum)%pow[z+1]);
  }
  return (sum/pow[sz])%p;
}

int main(){
  unsigned long long int p = 137;
  pow.push_back(1);
  for ( int i = 0 ; i < 20 ; ++i )
    pow.push_back(pow.back()*p);

  std::vector<int> inv(p,0);
  std::vector<int> suminv(p,0);
  std::vector<int> tab(p*p);
  for ( unsigned int i = 1 ; i < p ; ++i )
  {
    inv[i] = invert(i,p);
    suminv[i] = suminv[i-1]+inv[i];
  }
  for ( unsigned int i = 0 ; i < p*p ; ++i )
    tab[i] = (suminv[i%p]+i/p)%p;

  std::vector<unsigned long long int> crit(1,0);
  unsigned int pt = 0;
  while ( pt < crit.size() )
  {
    unsigned long long int base = crit[pt];
    std::cout << base << "-" << base+p-1 << " :   ";
    int st = starter(base,p);
    for ( unsigned int i = 0 ; i < p ; ++i )
    {
      if ( tab[st*p+i] )
        continue;
      unsigned long long int next = (base+i)*p;
      if ( !next )
        continue;
      std::cout << next << " ";
      crit.push_back(next);
    }
    std::cout << std::endl;
    ++pt;
  }
  std::cout << crit.back()+p-1 << std::endl;
}
