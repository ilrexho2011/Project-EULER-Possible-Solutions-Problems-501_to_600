#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll p=1e9+7;
#define clr(a) memset(a,0,sizeof(a))

template<const int N>
void mul(ll a[][N],ll b[][N]){
	static ll t[N][N];
	for(int i=0;i<N;++i)
		for(int j=0;j<N;++j){
			ll& tmp=t[i][j]=0;
			for(int k=0;k<N;++k)tmp=(tmp+a[i][k]*b[k][j])%p;
		}
	memcpy(a,t,sizeof(t));
} 

template<const int h>
ll no_more_than(ll w){
	const int S=h*2;
	ll a[S][S],r[S][S];
	clr(a);clr(r);
	for(int h1=0;h1<h;++h1)for(int oe:{0,h})
	for(int h2=0;h2<h;++h2)
		if(h2>=h1 || (h1-h2&1)==0)a[h2+oe][h1+oe]=1;
		else a[h2+h-oe][h1+oe]=1;
	for(int i=0;i<h+h;++i)r[i][i]=1;
	for(ll t=w-1;t;t>>=1,mul(a,a))
		if(t&1)mul(r,a);
	ll ret=0;
	for(int i=0;i<h;++i)
		for(int j=0;j<h;++j)
			ret+=r[i][j+((h-j&1)?h:0)];
	return ret%p;
}

template<const int h>
ll F_small_h(ll w){
	return (no_more_than<h>(w)-no_more_than<h-1>(w)+p)%p;
}


ll no_more_than_med(int h,int w){
	ll f[10000][2],g[10000][2];
	for(int i=0;i<h;++i)for(int j:{0,1})f[i][j]=(h^i^j^1)&1;
	for(int _=1;_<w;++_){
		g[0][0]=g[0][1]=0;
		for(int i=0;i<h;++i)for(int j:{0,1})
			g[0][1&(i^j)]+=f[i][j];
		for(int j:{0,1})g[1][j]=g[0][!j]+f[0][j]-f[0][!j];
		for(int i=2;i<h;++i)for(int j:{0,1})
			g[i][j]=g[i-2][j]+f[i-1][j]-f[i-1][!j];
		for(int i=0;i<h;++i)for(int j:{0,1})f[i][j]=g[i][j]%p;
	}
	ll ret=0;
	for(int j=0;j<h;++j)ret+=f[j][0];
	return (ret%p+p)%p;
}

ll F_med_h(ll h,ll w){
	return (no_more_than_med(h,w)-no_more_than_med(h-1,w)+p)%p;
}


template<const int w>
ll F_small_w(ll h){
	const int N=w+1;
	ll a[N][N+1];
	for(int k=h%2+2,i=0;i<N;++i,k+=2){
		a[i][N]=F_med_h(k,w);
		for(int j=a[i][0]=1;j<N;++j)a[i][j]=a[i][j-1]*k%p;
	}
	for(int i=0,j,k;i<N;++i){
		for(j=i;j<N;++j)if(a[j][i])break;
		if(j!=i)for(k=i;k<=N;++k)swap(a[i][k],a[j][k]);
		ll t=a[i][i],s=1;
		for(int c=p-2;c;c>>=1,t=t*t%p)
			if(c&1)s=s*t%p;
		for(k=i;k<=N;++k)(a[i][k]*=s)%=p;
		for(j=i+1;j<N;++j)if(a[j][i])
			for(k=i,t=p-a[j][i];k<=N;++k)(a[j][k]+=a[i][k]*t)%=p;
	}
	ll ret=0;
	for(int i=N-1;i>=0;--i){
		ret=(h%p*ret+a[i][N])%p;
		for(int j=0;j<i;++j)(a[j][N]-=a[j][i]*a[i][N])%=p;
	}
	return (ret+p)%p;
}
int main(){
	cout <<	(	F_small_h<100>(1e12)
			+	F_med_h(10000,10000)
			+	F_small_w<100>(1e12))%p << endl;
}