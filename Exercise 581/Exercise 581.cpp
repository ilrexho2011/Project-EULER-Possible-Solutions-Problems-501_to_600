#include <stdio.h>
#include <set>
typedef long long ll;
using namespace std;
static const int M=47;
int main(void){
    bool sieve[M+1];
    int primes[M],num_primes=0;
    for(int i=0;i<=M;++i)sieve[i]=true;
    for(int i=2;i<=M;++i){
        if(sieve[i]){
            primes[num_primes++]=i;
            for(int j=i;j<=M;j+=i)sieve[j]=false;
        }
    }
    //A more efficient way to do this is to generate the set of m-smooth numbers
    set<ll> Q;
    Q.insert(1);
    ll prev=-1,total=0,count=0;
    while(!Q.empty()){
        ll top=*Q.begin();
        //printf("%lld\n",top);
        if(top==prev+1){
            total+=prev;
            ++count;
            printf("#%lld: %lld %lld [total %lld]\n",count,prev,top,total);
        }
        prev=top;
        Q.erase(top);
        int min_index=0;
        for(int i=0;i<num_primes;++i){
            if(top%primes[i]==0)min_index=i;
        }
        for(int i=min_index;i<num_primes;++i){
            Q.insert(top*primes[i]);
        }
    }
    return 0;
}