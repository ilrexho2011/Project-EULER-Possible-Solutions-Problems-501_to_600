#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll ans, n, a;

int main()
{
	scanf("%lld", &n); // input n: even
	a = n/2;
	for(ll e=1; e<=60; ++e) ans += (ll)(a/(1LL<<e));
	ans *= 904962LL;
	printf("ANS: %lld\n", ans);
	return 0;
}