#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vl;
const ll oo = 0x3f3f3f3f3f3f3f3f;
#define sz(c) ll((c).size())
#define all(c) begin(c), end(c)
#define FOR(i,a,b) for (ll i = (a); i < (b); i++)
#define pb push_back
#define has(c,i) ((c).find(i) != end(c))

const ll L = 1e16, p[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};

void normalize(vl& a) {
	sort(all(a),greater<ll>());
	while (sz(a) && a[sz(a)-1] == 0) a.pop_back();
}

map<vl,ll> g;
ll G(vl a) {
	if (!sz(a)) return 1;
	if (has(g,a)) return 2*g[a];
	ll n = sz(a), res = 0;
	FOR(mask,1,1 << n) {
		vl b = a;
		FOR(i,0,n) if (mask & (1 << i)) b[i]--;
		normalize(b);
		ll cur = G(b);
		if (cur == oo) return g[a] = oo;
		if (__builtin_popcount(mask) & 1) res += cur; else res -= cur;
	}
	if (res > L) return g[a] = oo;
	g[a] = res;
	return 2*res;	
}

vl factorize(ll n) {
	vl pf;
	for (ll i = 2; i*i <= n; i++) if (n % i == 0) {
		ll a = 0;
		while (n % i == 0) n /= i, a++;
		pf.pb(a);
	}
	if (n > 1) pf.pb(1);
	return pf;
}

ll res = 0;

void gen(vl a, ll n, ll bnd) {
	ll i = sz(a);
	G(a);
	if (g[a] > L) return;
	
	vl b = factorize(g[a]);
	normalize(b);
	if (b == a) res += g[a];

	for (a.pb(1), n *= p[i]; a[i] <= bnd; a[i]++, n *= p[i]) {
		if (n > L) break;
		gen(a,n,a[i]);
	}
}

int main() {
	g[{}] = 1;
	gen({},1,60);
	cout << res << endl;
}