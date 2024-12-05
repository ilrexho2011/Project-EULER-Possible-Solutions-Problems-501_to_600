#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

const int MAX = 100000;
const int prime_count = 9592;

bool isPrime[MAX];
int prime[prime_count];

ll modpow(ll a, ll p, ll n) {
    ll r = a % n;
    if (p == 0) {
        return ll(1);
    }
    if (p == 1) {
        return r;
    }
    if (p % 2 == 1) {
        r = modpow(a, p / 2, n) % n;
        r = r * r % n;
        return r * a % n;
    } else {
        r = modpow(a, p / 2, n) % n;
        r = r * r % n;
        return r;
    }
}

ll modInverse(ll a, ll p) {
    return modpow(a, p - 2, p);
}

bool isPrime_large(ll n) {
    for (ll i = 0; prime[i] * prime[i] <= n; i++) {
        if (n % prime[i] == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    ll a = 1000000000LL;
    ll b = 100000LL;
    ll k = 100000LL;
    for (int i = 2; i < MAX; i++) {
        if (!isPrime[i]) {
            int j = i + i;
            while (j < MAX) {
                isPrime[j] = true;
                j += i;
            }
        }
    }
    int pi = 0;
    for (int i = 2; i < MAX; i++) {
        if (!isPrime[i]) {
            prime[pi] = i;
            pi++;
        }
    }
    k--;
    ll sum = 0LL;
    for (ll p = a + 1LL;r p <= a + b; p += 2) { 
        if (isPrime_large(p)) {
            ll temp = modInverse(k, p);
            sum += temp;
        }
    }
    printf("D(%lld, %lld, %lld) = %lld\n", a, b, (k + 1), sum);
    printf("No. of primes in the range is %d\n", c);
    cout << "Time elapsed : " << (1.0 * clock() / CLOCKS_PER_SEC) << " seconds" << endl;
    return 0;
}