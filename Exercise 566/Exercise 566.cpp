#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
#define rep(i,a,b) for(int i = (a); i < (b); ++i)
typedef long long ll;
typedef pair<ll, ll> pll;

ll inv(ll a, ll b){ return a>1 ? b - inv(b%a, a) * b / a : 1; }

pll bad(0, 0);
pll crt(const pll &a, const pll &b){
	if(a == bad || b == bad) return bad;
	ll d = __gcd(a.second, b.second);
	if(a.first % d != b.first % d) return bad;
	ll c2 = a.second * b.second / d;
	ll c1 = (a.first + (b.first - a.first)/d * a.second * inv(a.second/d, b.second)) % c2;
	return {c1 + (c1 < 0 ? c2 : 0), c2};
}

const ll base = 3;
pll phase(const string &s, const string &t){
	ll bpow = 1, sval = 0, tval = 0;
	rep(i,0,s.size()){
		bpow *= base;
		sval = s[i] + sval * base;
		tval = t[i] + tval * base;
	}
	rep(i,0,s.size()){
		tval = tval * base + (1 - bpow) * t[i];
		if(tval == sval) return {i+1, s.size()};
	}
	return bad;
}

const double eps = 1e-8;
ll F(const vector<double> &xyz){
	ll ans = 1;
	vector<pll> cong(2, {0, 1});
	bool vis[3][2] = {};
	rep(t,0,3) rep(k,0,2) if(!vis[t][k]){
		double pos = k ? xyz[t]-eps : eps;
		bool ud = true;
		int i = t;
		vector<string> uds(3);
		do {    uds[i].push_back(ud ? 'U' : 'D');
			double nx = pos - xyz[i];
			if(0 < nx && nx < 1) pos = nx;
			else pos = 1-pos, ud = !ud;
			i = (i+1) % 3;
			if(ud && abs(pos - (k ? xyz[i]-eps : eps)) < eps) vis[i][k] = true;
		} while(!vis[t][k]);
		if(i) rep(i,t,3) uds[i] = uds[i].substr(1, uds[i].size()-1) + uds[i][0];
		uds[0].resize(phase(uds[0],uds[0]).first);
		ans = ans / __gcd(ans, (ll)uds[0].size()) * uds[0].size();
		rep(j,0,2) cong[j] = crt(cong[j], phase(uds[0], uds[1+j]));
	}
	ans *= 3;
	rep(j,0,2) if(cong[j] != bad) ans = min(ans, 3 * cong[j].first + j+1);
	return ans;
}

int main(){
	ll ans = 0;
	rep(a,9,52) rep(b,a+1,53) rep(c,b+1,54) ans += F({1./a, 1./b, 1/sqrt(c)});
	cout << ans << endl;
}