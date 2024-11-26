#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
const u64 M=(1uLL<<60)-1,N=1e12;
const size_t s=ceil(log2(N)/2+0.5), l=1<<s, m=l-1;
u64 x[l*3],*a=x+l,*b=a+l;
u64 m23(u64 a,u64 b){return (a<<1)+(b<<1)+b;}
u64 xx(u64 n){
	if(n<l)return x[n];
	return a[n&m]*x[n>>s] + b[n&m]*x[n>>s+1] & M;
}
u64 y(u64 k){
	return (k>=N)?xx(k): M-max(y(k<<1),y(k<<1|1));
}
int main(){
	x[1]=1;
	for(int i=2;i<l+l+l;++i)
		x[i]=i&1?m23(x[i>>1],x[i>>2]):m23(x[i>>2],x[i>>1]);
	for(int i=0;i<l;++i)
		b[i]-=a[i]*3;
	u64 y[128];
	#pragma omp parallel for
	for(int i=64;i<128;++i){
		cerr << "p" << i << " started" << endl;
		y[i]=::y(i);
		cerr << "p" << i << " ok" << endl;
	}
	for(int i=63;i>=1;--i)
		y[i]=i>=N?xx(i) : M-max(y[i<<1],y[i<<1|1]);
	cout << y[1] << endl;
}