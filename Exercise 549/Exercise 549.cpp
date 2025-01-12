#include <stdio.h>
#include <vector>
#include <utility>
#define LIM 100000000
//#define LIM 100
using namespace std;
short sieve[LIM+1];
//10^8 is rather large, sieve for primes?
//m! = 1 * 2 * 3 * 2^2 * 5 * ... * m
//If n divides m!, then n will divide (m+c)!
int legrende(int p,int n){
    int r=0;
    while(n){
        r+=(n/=p);
    }
    return r;
}
int S(int n){
    //factorize n
    vector<pair<int,int> > factors;
    int u=n;
    {
        int c=0;
        while(u%2==0){
            c++;
            u/=2;
        }
        if(c){
            factors.push_back(make_pair(2,c));
        }
    }
    while(u>1){
        if(sieve[u]){
            int p=sieve[u],c=0;
            while(sieve[u]==p){
                c++;
                u/=sieve[u];
            }
            factors.push_back(make_pair(p,c));
            //factors.push_back(sieve[u]);
            //u/=sieve[u];
        }else{
            factors.push_back(make_pair(u,1));
            break;
        }
    }
    //binary search?
    int lo=1,hi=n;
    while(lo!=hi){
        int mid=(lo+hi)/2;
        bool sat=true;
        for(int i=0;i<factors.size();++i){
            if(legrende(factors[i].first,mid)<factors[i].second){
                sat=false;
                break;
            }
        }
        if(sat)hi=mid;
        else lo=mid+1;
    }
    return lo;
}
int main(void){
    //eratosthenes
    bool s=true;
    for(int i=3;i<=LIM;i+=2){
        if(i&1&&!sieve[i]){
            //sieve[i]=i;
            if(i*i>LIM)s=false;
            if(s){
                for(int j=i;j<=LIM;j+=i){
                    if(!sieve[j])sieve[j]=i;
                }
            }
        }
    }
    printf("sieving complete\n");
    long long total=0;
    for(int i=2;i<=LIM;++i){
        int u=S(i);
        total+=u;
        if(i%100000==0){
            printf("%d: %d %lld\n",i,u,total);
        }
    }
    printf("%lld\n",total);
    return 0;
}