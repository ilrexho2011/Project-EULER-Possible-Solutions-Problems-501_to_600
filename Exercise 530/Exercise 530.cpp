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

unordered_map<ll, ll> S;

ll ct = 0;

ll solve(ll N) {
	if (S.find(N) != S.end()) return S[N];
	ll sum = 0;
	ll crt = 1;
	while (crt <= N) {
		ll j = N / crt;
		ll nex = N / j;
		nex = min(nex, N);
		sum += (nex - crt + 1) * j;
		crt = nex + 1;
	}
	for (ll i = 2;i <= sqrt(N);i++) {
		sum -= solve(N / i / i);
	}
	S[N] = sum;
	ct++;
	if (ct % 10000 == 0) cout << ct << endl;
	return S[N];
}

ll calculate(ll N) {
	ll i,j,k,n;
	ll ans = 0;
	for (i = 1;i <= sqrt(N);i++) {
		ans += i * solve(N / i / i);
	}
	return ans;
}

int main() {
    ios::sync_with_stdio(false);
    S[1] = 1;
    cout << calculate(1000000000000000) << endl;
    return 0;
}