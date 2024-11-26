const ll mod=123454321;
const ll a[]={1,2,3,4,3,2};
const ll N=100000000000000ll;


void add(ll &res,ll y) {
	res+=y;
	res%=mod;
}

struct mat {
	ll a[3][3];
	void clear() {
		memset(a,0,sizeof(a));
	}
};
mat operator *(mat &a,mat &b) {
	mat c;c.clear();
	rep(k,0,2) rep(i,0,2) rep(j,0,2) {
		add(c.a[i][j],a.a[i][k]*b.a[k][j]%mod);
	}
	return c;
}
ll go(ll x, ll y, ll z) {
	if (!z) return 0;
	
	mat ans;ans.clear();
	mat tmp;tmp.clear();
	
	ans.a[0][0]=x;ans.a[0][1]=y;
	
	tmp.a[0][0]=1000000;tmp.a[1][0]=tmp.a[0][2]=tmp.a[1][1]=tmp.a[2][2]=1;
	
	while (z) {
		if (z&1) ans=ans*tmp;
		tmp=tmp*tmp;
		z>>=1;
	}
	return ans.a[0][2];
}

int main()
{
	ll res=10;
	
	add(res, go(123,432123,(N-6)/15+1));
	add(res, go(1234,321234,(N-10)/15+1));
	add(res, go(123432,123432,(N-15)/15+1));
	add(res, go(1234321,234321,(N-16)/15+1));
	
	
	add(res, go(23432,123432,(N-14)/15+1));
	add(res, go(2343212,343212,(N-17)/15+1));
	
	
	add(res, go(34321,234321,(N-13)/15+1));
	add(res, go(3432123,432123,(N-18)/15+1));
	
	
	add(res, go(43,212343,(N-7)/15+1));
	add(res, go(432,123432,(N-9)/15+1));
	add(res, go(43212,343212,(N-12)/15+1));
	add(res, go(4321234,321234,(N-19)/15+1));
	
	
	add(res, go(32,123432,(N-5)/15+1));
	add(res, go(32123,432123,(N-11)/15+1));
	
	
	add(res, go(2123,432123,(N-8)/15+1));
	
	cout << res << endl;
	
	return 0;
}