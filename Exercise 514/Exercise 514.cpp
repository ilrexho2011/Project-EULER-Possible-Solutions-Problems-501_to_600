#include <bits/stdc++.h>

#define FO(i,a,b) for (int i = (a); i < (b); i++)
#define sz(v) int(v.size())

using namespace std;

int N = 100+1;

int gcd(int a, int b) {
    if (a == 0) return b;
    else return gcd(b%a, a);
}

double p;

vector<pair<int,int>> v;
vector<int> k[30000];

int main() {
    p = 1. / N;
    FO(x0,0,N) FO(y0,0,N) FO(x1,0,N) FO(y1,0,N) if (x0!=x1 || y0!=y1) {
        int a = y1-y0, b = x0-x1;
        int g = gcd(abs(a),abs(b));
        a /= g; b /= g;
        v.push_back(make_pair(a,b));
    }
    sort(v.begin(),v.end());
    v.resize(unique(v.begin(),v.end())-v.begin());
    printf("%d\n", sz(v)); fflush(stdout);

    FO(x,0,N) FO(y,0,N) {
        FO(i,0,sz(v)) {
            int a = v[i].first, b = v[i].second;
            k[i].push_back(a*x + b*y);
        }
    }
    FO(i,0,sz(v)) sort(k[i].begin(), k[i].end());

    printf("CALCED POINTS\n"); fflush(stdout);

    double res = 0;
    FO(x0,0,N) FO(y0,0,N) FO(x1,0,N) FO(y1,0,N) if (x0!=x1 || y0!=y1) {
        int g = gcd(abs(x1-x0), abs(y1-y0));
        int K = 0;
        if (x1 != x0) K = g-1;
        else K = g-1;

        int a = y1-y0, b = x0-x1;
        a /= g; b /= g;

        int li = lower_bound(v.begin(),v.end(),make_pair(a,b))-v.begin();
        int val = a*x0 + b*y0;

        int m = lower_bound(k[li].begin(), k[li].end(), val) - k[li].begin();

        //printf("K=%d, m=%d (%d,%d)->(%d,%d)\n", K, m, x0, y0, x1, y1);
        res += p * p * pow(1-p,m+K) * (y1*x0 - x1*y0) / 2.;
    }
    printf("%.20lf\n", abs(res));
}