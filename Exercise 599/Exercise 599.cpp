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

int N = 10;

ll s, d;

ll gcd(ll a, ll b) {
	if (a < b) swap(a, b);
	if (b == 0) return a;
	return gcd(b, a % b);
}

ll nchoosek(ll a, ll b) {
	ll res = 1;
	ll base = 1;
	for (int i = 1;i <= b;i++) base *= i;
	for (int i = 1;i <= b;i++) {
		res *= (a + 1 - i);
		ll g = gcd(res, base);
		base /= g;
		res /= g;
	}
	return res;
}

int main() {
    ios::sync_with_stdio(false);
    s = N;
    d = N * (N - 1) + N * (N - 1) * (N - 2) / 3;
    ll K = nchoosek(8 + (s + d) - 1, 8);
    ll Q = nchoosek(8 + d - 1, 8) * 2;
    cout << K + Q << endl;
    return 0;
}