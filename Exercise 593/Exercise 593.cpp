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

vector<ll> P;

void init() {
	bool sieve[300000000];
	memset(sieve, 0, sizeof(sieve));
	for (int i = 2;i < 3E8;i++) {
		if (sieve[i] == 0) {
			P.push_back(i);
			for (int j = i;j < 3E8;j += i) {
				sieve[j] = 1;
			}
		}
	}
	cout << P.size() << endl;
	return;
}

ll MOD = 10007;

ll power(ll a, ll b) {
	ll res = 1;
	while (b > 0) {
		if (b % 2) {
			res *= a;
			res %= MOD;
		}
		a *= a;
		a %= MOD;
		b /= 2;
	}
	return res;
}

ll S[10000010], S2[10000010];

void genS() {
	for (int i = 1;i <= 1E7;i++) {
		S[i] = power(P[i - 1], i);
	}
	for (int i = 1;i <= 1E7;i++) {
		S2[i] = S[i] + S[(i / 10000) + 1];
	}
	return;
}

int main() {
    ios::sync_with_stdio(false);
    init();
    genS();
    int N = 10000000, M = 100000;
    multiset<ll> L, R;
    // Size of L = M / 2, Size of R = M / 2.
    vector<ll> T;
    for (int i = 1;i <= M;i++) {
    	T.push_back(S2[i]);
    }
    sort(T.begin(), T.end());
    for (int i = 0; i < M / 2;i++) L.insert(T[i]);
    for (int i = M / 2;i < M;i++) R.insert(T[i]);
    ll res = 0;
    multiset<ll>::iterator it1, it2, itx;
    for (int i = 0;i <= N - M;i++) {
    	it1 = L.end();
    	it1--;
    	ll x = *it1;
    	it2 = R.begin();
    	ll y = *it2;
    	res += x + y;
    	ll now = S2[i + M + 1];
    	ll old = S2[i + 1];
    	if (old <= x) {
    		itx = L.find(old);
    		L.erase(itx);
    		if (now <= y) L.insert(now);
    		else {
    			R.erase(it2);
    			L.insert(y);
    			R.insert(now);
    		}
    	}
    	else {
    		itx = R.find(old);
    		R.erase(itx);
    		if (now >= x) R.insert(now);
    		else {
    			L.erase(it1);
    			L.insert(now);
    			R.insert(x);
    		}
    	}
    }
    cout << res << ' ' << res / 2 << endl;
    return 0;
}