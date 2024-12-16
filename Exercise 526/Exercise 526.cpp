#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long mulmod(long long a, long long b, long long mod)
{
    long long x = 0,y = a % mod;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            x = (x + y) % mod;
        }
        y = (y * 2) % mod;
        b /= 2;
    }
    return x % mod;
}

bool good(long long n, const vector<bool> &p)
{
    for (long long i = 31; i < p.size(); ++i)
    {
        if ((p[i])&&((n%i==0)||(i-9 < n%i)))
        {
            return false;
        }
    }
    return true;
}

pair<long long,long long> ext_euc(long long a, long long b)
{
    long long s = 0;
    long long old_s = 1;
    long long t = 1;
    long long old_t = 0;
    long long r = b;
    long long old_r = a;
    while (r!=0)
    {
        long long aux;
        long long q = old_r/r;
        aux = r;
        r = old_r - q*r;
        old_r = aux;
        aux = s;
        s = old_s - q*s;
        old_s = aux;
        aux = t;
        t = old_t - q*t;
        old_t = aux;
    }
    pair<long long,long long> ret(old_s,old_t);
    return ret;
}

long long crt(long long a, long long b, long long m, long long n)
{
    pair<long long, long long> c = ext_euc(m,n);
    long long s = c.first;
    long long t = c.second;
    s = ((s%(m*n))+(m*n))%(m*n);
    t = ((t%(m*n))+(m*n))%(m*n);
    return (m*n+(mulmod(mulmod(b,s,m*n),m,m*n) + mulmod(mulmod(a,t,m*n),n,m*n))%(m*n))%(m*n);
}

long long fa(long long x, const vector<bool> &p)
{
    for (long long i = 0; i*i < x; ++i)
    {
        if (p[i])
        {
            while (x%i == 0)
            {
                x/=i;
            }
        }
    }
    return x;
}

long long fa23(long long x)
{
    while (x%2==0)
    {
        x/=2;
    }
    while(x%3==0)
    {
        x/=3;
    }
    return x;
}

long long fa357(long long x)
{
    while (x%3==0)
    {
        x/=3;
    }
    while(x%5==0)
    {
        x/=5;
    }
    while(x%7==0)
    {
        x/=7;
    }
    return x;
}

int main()
{
    cout << "Sieving" << endl;
    vector<bool> ps(100000001,true);
    ps[0] = ps[1] = false;
    for (long long i = 0; i < ps.size(); ++i)
    {
        if (ps[i])
        {
            for (long long j = i*i; j < ps.size(); j+=i)
            {
                ps[j] = false;
            }
        }
    }
    cout << "Done sieving" << endl;
    vector<long long> mods = {11,13,17,19,23,29};
    vector<long long> residues = {311,4721};
    long long mod = 5040;
    for (long long i = 0; i < mods.size(); ++i)
    {
        vector<long long> newmods = {};
        long long p = mods[i];
        cout << "Modding with " << p << endl;
        for (long long j = p-9; j > 0; --j)
        {
            for (long long k = 0; k < residues.size(); ++k)
            {
                newmods.push_back(crt(residues[k],j,mod,p));
            }
        }
        residues = newmods;
        mod*=p;
    }

    cout << "Modulus is " << mod << endl;
    cout << "Number of acceptable residues is " << residues.size() << endl;

    cout << "Sorting residues" << endl;
    sort(residues.begin(),residues.end());

    cout << "Starting search" << endl;
    long long lim = 10000000000000000;
    long long best = 0;
    long long mul = (lim/mod)*mod;
    while (best == 0)
    {
        for (long long i = residues.size()-1; i >= 0; --i)
        {
            long long n = mul + residues[i];
            if ((n<=lim)&&(good(n,ps)))
            {
                cout << "Found sequence at " << n << endl;
                long long ans = 4*(n+4)+fa357(n+4);
                ans+=(fa23(n+1)+fa23(n+3)+fa23(n+5)+fa23(n+7));
                cout << "Answer is " << ans << " at " << n << endl;
                best = ans;
            }
        }
        mul -= mod;
    }
    return 0;
}