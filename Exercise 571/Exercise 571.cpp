#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

int n, m;
ll ans;
int cnt;

int a[100];

int va(ll x, int b){
	ll ret = 0;
	while(x){
		ret |= (1 << (x % b));
		x /= b;
	}
	return ret + 1 == (1ll << b);
}

int check(ll x){
	for(int i = m-1; i >=2; i--)
		if (!va(x, i)) 
			return 0;
	return 1;
}

void solve(int x, ll now, int use){
	if ((n-x+1+use) < m) return ;
	if (x > n){
		if (check(now)){
			cnt++;
			cout<<use<<' '<<cnt<<' '<<now<<endl;
			ans += now;
		}
		return ;
	}
	for(int i = (x == 1) ? 1 : 0; i < m; i++){
		if (a[i] == 0) use++;
		a[i]++;
		solve(x+1, now * m + i, use);
		if (cnt >= 10) return ;
		if (a[i] == 1) use--;
		a[i]--;
	}
}	

int main(){
	ans = 0;
	cnt = 0;
	m = 12;
//	cout<<check(978)<<endl;
	n = m-1;
	while(cnt < 10){
		n++;
		for(int i = 0; i < m; i++)
			a[i] = 0;
		solve(1, 0, 0);
		puts("END");
	}
	cout<<"ANS: "<<ans<<endl;
	return 0;
} 
