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

struct Point {
	ll x, y;

	bool operator <(const Point &p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
};

// 2D cross product of OA and OB vectors, i.e. z-component of their 3D cross product.
// Returns a positive value, if OAB makes a counter-clockwise turn,
// negative for clockwise turn, and zero if the points are collinear.
ll cross(const Point &O, const Point &A, const Point &B)
{
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Returns a list of points on the convex hull in counter-clockwise order.
// Note: the last point in the returned list is the same as the first one.
vector<Point> convex_hull(vector<Point> P)
{
	int n = P.size(), k = 0;
	vector<Point> H(2*n);

	// Sort points lexicographically
	sort(P.begin(), P.end());

	// Build lower hull
	for (int i = 0; i < n; ++i) {
		while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}

	// Build upper hull
	for (int i = n-2, t = k+1; i >= 0; i--) {
		while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}

	H.resize(k-1);
	return H;
}


ll m = 100000000;

bool P[100000000];

vector<ll> p;

void init() {
	memset(P, 0, sizeof(P));
	for (ll n = 2;n < m;n++) {
		if (P[n] == 0) {
			p.push_back(n);
			for (ll j = n;j < m;j += n) P[j] = 1;
		}
	}
	cout << p.size() << endl;
	return;
}

struct node {
	ll h;
	ll x;
};

bool operator > (node a, node b) {
	return a.h * b.x < b.h * a.x;
}

ll cal(ll n) {
	vector<ll> sum(n, 0);
	vector<ll> peak(n, 0);
	ll crt = p[0];
	ll pk = p[0];
	vector<Point> base(n);
	for (ll x = 0;x < n;x++) {
		sum[x] = crt;
		peak[x] = pk;
		base[x].x = crt;
		base[x].y = pk;
		crt += p[x * 2 + 1];
		crt += p[x * 2 + 2];
		pk -= p[x * 2 + 1];
		pk += p[x * 2 + 2];
	}
	vector<Point> con = convex_hull(base);
	sort(con.begin(), con.end());
	ll res = 0;
	int seg = 0;
	for (int i = 1;i < n;i++) {
		if (i % 10000 == 0) cout << double(i) / double(n) << endl;
		node crt;
		crt.x = 0;
		crt.h = 0;
		while (seg + 1 < con.size() && con[seg + 1].x < base[i].x) seg++;
		ll idx = con[seg].x;
		for (int j = i - 1;base[j].x > idx;j--) {
			node tmp;
			tmp.x = base[i].x - base[j].x;
			tmp.h = base[i].y - base[j].y;
			if (tmp > crt || crt.x == 0) {
				res++;
				crt = tmp;
			}
		}
		for (int j = seg;j >= 0;j--) {
			node tmp;
			tmp.x = base[i].x - con[j].x;
			tmp.h = base[i].y - con[j].y;
			if (tmp > crt || crt.x == 0) {
				res++;
				crt = tmp;
			}
			break;
		}
	}
	return res;
}

int main() {
    ios::sync_with_stdio(false);
    init();
    cout << cal(2500000) << endl;
    //cout << cal(100) << endl;
    return 0;
}