#include <cstdio>
#include <cmath>

typedef long long LL;

const int MOD = 1000000000;
const int N = 20000001;
bool a[N];
int prod[N];
double logP[N];

void add(int k, int x) {
  prod[k] = LL(prod[k]) * x % MOD;
  logP[k] += log(x+0.);
}

int main()
{
  for(int n=1;n<N;n++) {
    logP[n]=0.0;
    prod[n]=1;
    int k=0;
    for(int m=n;m%2==0;m/=2) k++;
    add(n, k==0 ? 2 : 1<<(k+2));
  }
  for(int p=2;p<N;p++) if(!a[p]) {
    for(int n=p;n<N;n+=p) a[n]=1;
    if(p>2) {
      int step = p-1;
      for(int k=step;k<N;k+=step) {
        int x=p;
        for(int j=k;j%p==0;j/=p) x*=p;
        add(k, x);
      }
    }
  }
  double maxP = 0;
  for(int n=1;n<N;n++)
    if(maxP < logP[n]) maxP = logP[n];
  for(int n=1;n<N;n++)
    if(logP[n]>maxP-1e-9) {
      printf("%d %d %.9lf\n",n,prod[n]+1,logP[n]);
    }
  return 0;
}