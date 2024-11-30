#include <stdio.h>
#include <stdint.h>

#define N       500000000
//#define       N       1000000

int primes[10000];
int pcount = 0;

int phi(int n)
{
        int c = 1;
        for( int i = 0 ; i < pcount && primes[i]*primes[i] <= n ; i++ )
        {
                int p = primes[i];
                if( n%p ) continue;
                c *= p-1; n /= p;
                while( n%p == 0 ) { c *= p; n /= p; }
        }
        if( n > 1 ) return c*(n-1);
        return c;
}

int main()
{
        primes[pcount++] = 2;
        primes[pcount++] = 3;
        primes[pcount++] = 5;
        primes[pcount++] = 7;
        for( int i = 11 ; i*i < N ; i += 2 )
        {
                bool isPrime = true;
                for( int j = 1 ; primes[j]*primes[j] <= i ; j++ )
                        if( i%primes[j] == 0 ) { isPrime=false; break; }
                if( isPrime ) primes[pcount++] = i;
        }
        uint64_t s = 1;
        int k = 100;
        for( int i = 3 ; i <= N ; i+=2 )
        {
                if( i > k ) { printf("processing %d...\n", i); k *= 10; }
                s += (uint64_t)(phi(i)%(i+1));
        }
        printf("ans = %ju\n", s);
}