#include<bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef vector<int> vi;
int n;
i64 target,tmp;
vi can,perm;
vector<pair<int,int>> x;
int p,premax;

i64 cnt;
bool dfs(int k){
	++cnt;
	if(!(cnt&(1LL<<28)-1)){
		cout << cnt <<" times goes, continue? " << endl;
		int x;cin >>x;
		if(x==0)throw 0;
	}
	if(k<p)return tmp==0;
	i64 tt=0;
	int tmax=premax;
	tmax=max(max_element(x.begin(),x.end())->first,premax);
	for(auto p:x)if(p.first!=tmax)
		tt+=1LL<<p.second;
	if(tt<tmp)return false;
	int si=0;
	for(int i=1;i<x.size();++i)
		if(x[i].second == k) {swap(x[0],x[si=i]);break;}
	for(int i=x.size()-1;i>=0;--i){
		int rk=x[i].second;
		i64 ss=rk!=k?1LL<<rk:0;
		if(tmp<ss)continue;
		int uu=perm[k]=x[i].first;
		for(int j=i+1;j<x.size();++j)
			x[j-1]=x[j];
		x.pop_back();
		for(int j=0;j<x.size();++j)
			if(uu<x[j].first)--x[j].second;
		tmp-=ss;
		if(dfs(k-1))
			return true;
		for(int j=0;j<x.size();++j)
			if(uu<x[j].first)++x[j].second;
		x.resize(x.size()+1);
		for(int j=x.size()-1;j>i;--j)
			x[j]=x[j-1];
		x[i]={uu,rk};
		tmp+=ss;
	}
	if(si)swap(x[0],x[si]);
	return false;
}

bool ok(int p,vi can){
	tmp=target;
	for(int i=1,c;i<p;++i){
		for(int j=c=0;j<i;++j)c+=(perm[i]>perm[j]);
		if(c!=i) tmp -= 1LL<<c;
	}
	x.clear();
	for(int t:can)if(t!=perm[p-1])
		x.push_back({t,t-1-(t==n)});
	::p=p;
	premax=*max_element(perm.begin(),perm.begin()+p);
	cnt=0;
	try{
		return dfs(n-2);
	} catch ( ... ){
		cout << "think it's false" << endl;
		return false; 
	}
}

int main(){
	cin >> target;
	for(n=1;target>>n-1;n+=1);
	cout << n << endl;
	target-=1LL<<n-2;
	can.resize(n-1);
	perm.resize(n);
	perm[n-1]=n-1;
	for(int i=1;i<n;++i)can[i-1]=i;
	can[n-2]=n;
	for(int i=0;i<n-1;++i){
		for(int t:can){
			perm[i]=t;
			for(int j=0;j<=i;++j)cout << perm[j] << " "; cout << endl;
			if(ok(i+1,can))break;
		}
		can.erase(find(can.begin(), can.end(), perm[i]));
	}
	for(int t:perm)cout << t << " ";
	cout << endl;
	vector<i64> fac(n);
	i64 ans=1;
	for(int i=fac[0]=1;i<n;++i)fac[i]=fac[i-1]*i;
	for(int i=0;i<n;++i){
		ans+=(perm[i]-1)*fac[n-i-1];
		for(int j=i+1;j<n;++j)
			if(perm[j]>perm[i])perm[j]--;
	}
	cout << ans << endl;
}