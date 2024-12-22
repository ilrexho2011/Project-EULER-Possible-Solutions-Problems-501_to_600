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

ll Mod;

long long gcd(long long n,long long m) {
    if (n < m) {
        n = n ^ m;
        m = n ^ m;
        n = n ^ m;
    }
    if (n % m == 0) return m;
    return gcd(m,n % m);
}


long long Extend_Euclid(long long a, long long b, long long&x, long long& y)
{
    if(b==0)
    {
        x=1,y=0;
        return a;
    }
    long long d = Extend_Euclid(b,a%b,x,y);
    long long t = x;
    x = y;
    y = t - a/b*y;
    return d;
}

//a在模n乘法下的逆元，没有则返回-1
long long inv(long long a, long long n)
{
    long long x,y;
    long long t = Extend_Euclid(a,n,x,y);
    if(t != 1)
        return -1;
    return (x%n+n)%n;
}

//将两个方程合并为一个
bool merge(long long a1, long long n1, long long a2, long long n2, long long& a3, long long& n3)
{
    long long d = gcd(n1,n2);
    long long c = a2-a1;
    if(c%d)
        return false;
    c = (c%n2+n2)%n2;
    c /= d;
    n1 /= d;
    n2 /= d;
    c *= inv(n1,n2);
    c %= n2;
    c *= n1*d;
    c += a1;
    n3 = n1*n2*d;
    a3 = (c%n3+n3)%n3;
    return true;
}

//求模线性方程组x=ai(mod ni),ni可以不互质
long long China_Reminder2(long long len, vector<long long> a, vector<long long> n)
{
    long long a1=a[0],n1=n[0];
    long long a2,n2;
    for(int i = 1; i < len; i++)
    {
        long long aa,nn;
        a2 = a[i],n2=n[i];
        if(!merge(a1,n1,a2,n2,aa,nn))
            return 0;
        a1 = aa;
        n1 = nn;
    }
    Mod = n1;
    return (a1%n1+n1)%n1;
}

vector<ll> F(1010000);
vector<ll> G(1010000);

int main() {
    ios::sync_with_stdio(false);
    ll n,m;
    for (ll i = 1;i < 1010000;i++) {
    	F[i] = i;
    	G[i] = 1;
    }
    for (ll i = 2;i < 1010000;i++) {
    	if (F[i] == i) {
    		for (ll j = i;j < 1010000;j += i) {
    			F[j] /= i;
    			G[j] *= (i - 1);
    			while (F[j] % i == 0) {
    				F[j] /= i;
    				G[j] *= i;
    			}
    		}
    	}
    }
    ll sum = 0;
    vector<long long> a(2);
    vector<long long> x(2);
    for (n = 1000000;n < 1005000;n++) {
    	cout << n << endl;
    	for (m = n + 1;m < 1005000;m++) {
    		a[0] = G[n];
    		a[1] = G[m];
    		x[0] = n;
    		x[1] = m;
    		sum += China_Reminder2(2, a, x);
    	}
    }
    cout << sum << endl;
    return 0;
}