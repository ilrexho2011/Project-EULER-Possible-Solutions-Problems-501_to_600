#include<bits/stdc++.h>
using namespace std;
const long N=1e9;
long s=0;
bool cnt(long u,long v){
	long a=(u+v)*(u+v),b=N/(v*v);
	if(a<=b){
		long  c=b/a;
		s+=(c*(c+1)>>1)*(a*(u*u+v*v)+u*v*u*v);
	}
	return a>b;
}
void gen(long a,long b,long c,long d){
	long t=a+c,s=b+d;
	if(s*s>N)return;
	if(cnt(t,s))return;
	gen(a,b,t,s);
	gen(t,s,c,d);
}
int main(){
	cnt(1,1);
	gen(0,1,1,1);
	cout << s << endl;
}