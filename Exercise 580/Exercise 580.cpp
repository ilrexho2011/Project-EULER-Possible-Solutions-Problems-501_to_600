#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>

using namespace std;

typedef long long ll;
typedef pair<int,int> PP;

/*
    freopen("input","r",stdin);
    freopen("output","w",stdout);
*/

ll calh(ll n); // Square Free Hilbert Number.

unordered_map<ll, ll> G, H;

ll calh(ll n) {
	if (H.find(n) != H.end()) return H[n];
	ll total = (n - 1) / 4 + 1;
	ll k = 3;
	while (k * k <= n) {
		ll r = n / k / k;
		ll nex = sqrt(n / r);
		total -= calh(r) * ((nex - k) / 2 + 1);
		k = nex + 1;
		if (k % 2 == 0) k++;
	}
	H[n] = total;
	return total;
}

const int L = 1E8;

int main() {
    ios::sync_with_stdio(false);
    const ll B = 1E16;
    ll all = calh(B);
    H[0] = 0;
    int sieve[L];
    memset(sieve, 0, sizeof(sieve));
    for (int i = 3;i < L;i += 2) {
    	if (sieve[i] == 0) {
    		sieve[i] = 1;
    		for (int j = 2 * i;j < L;j += i) {
    			sieve[j] = 2;
    		}
    	}
    }
    for (ll i = 3;i * i < B;i += 4) {
    	if (sieve[i] == 1) {
    		all += calh(B / i / i);
    	}
    }
    cout << all << endl;
    return 0;
}