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

double W[53]; // Wrong permutation.

double NK[110][110];
double F[110];

void init() {
	memset(NK, 0, sizeof(NK));
	NK[0][0] = 1.0;
	for (int i = 0;i < 100;i++) {
		for (int j = 0;j <= i;j++) {
			NK[i + 1][j + 1] += NK[i][j];
			NK[i + 1][j] += NK[i][j];
		}
	}
	F[0] = 1.0;
	for (int i = 1;i < 100;i++) F[i] = F[i - 1] * double(i);
	return;
}

void make() {
	W[0] = 0.0;
	W[1] = 0.0;
	W[2] = 1.0;
	for (int i = 3;i <= 52;i++) {
		double all = F[i];
		all -= 1.0; // All in one row;
		for (int j = 2;j < i;j++) {
			// In j part.
			double num = NK[i - 1][j - 1];
			all -= num * W[j];
		}
		W[i] = all; // Total number of Place N parts wrongly is W[n]
	}
	return;
}

double T[53], G[53];

void make2() {
	T[0] = 0.0;
	T[1] = 0.0;
	T[2] = 1.0;
	G[0] = 0.0;
	G[1] = 0.0;
	G[2] = 2.0;
	for (int i = 3;i <= 52;i++) {
		vector<double> Q(i + 1);
		Q[0] = 0.0;
		Q[1] = 1.0 / F[i];
		for (int j = 2;j <= i;j++) {
			Q[j] = NK[i - 1][j - 1] * W[j] / F[i];
		}
		double ans = 0.0;
		for (int j = 1;j < i;j++) ans += Q[j] * G[j];
		// Handling All wrong case.
		double crt = 1.0 + ans;
	    double p = 1.0 - Q[i];
	    G[i] = crt / p;
	    T[i] = G[i] * Q[i] + ans;
	}
	return;
}

int main() {
    ios::sync_with_stdio(false);
    init();
    make();
    make2();
    cout.precision(20);
    cout << T[5] << ' ' << 4213.0 / 871.0 << endl;
    cout << T[52] << endl;
    return 0;
}