#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int below[100];
int mxbits;
ll mod = 987654321;

unordered_map<int,pair<ll,ll> > mem;
pair<ll,ll> S(int bits, int at, bool lr, bool last, bool less) {
    if (at == bits) {
        if (!last) return make_pair(0LL,0LL);
        if (less || bits < mxbits) {
            return make_pair(0LL,1LL);
        }
        return make_pair(0LL,0LL);
    }
    int st = ((at*2+lr)*2+last)*2+less;
    if (mem.find(st) != mem.end()) return mem[st];
    ll sm = 0,
       cnt = 0;
    for (int d = 0; d <= 1; d++) {
        pair<ll,ll> ans = S(bits, at+1, !lr, d==1, d < below[at] || (d == below[at] && less));

        sm += ans.first;
        sm %= mod;
        if (at != bits-1 && (lr || d == 1)) {
            sm += ((1LL<<at)%mod) * ans.second % mod;
            sm %= mod;
        }
        cnt += ans.second;
        cnt %= mod;
    }
    return mem[st] = make_pair(sm,cnt);
}

int main() {
    ll bel = 1000000000000000000LL;
    while (bel) below[mxbits++] = bel % 2, bel /= 2;

    ll res = 0;
    for (int b = 1; b <= mxbits; b++) {
        mem.clear();
        pair<ll,ll> ans = S(b,0,true, false, true);
        res += ans.first + ans.second;
        res %= mod;
    }
    cout << res << endl;
    return 0;
}