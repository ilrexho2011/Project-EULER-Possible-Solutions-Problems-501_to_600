#include <bits/stdc++.h>
using namespace std;

bool have[1001];
int ans = 0;
int dp[25];


int minFactor[10000001];
int nFactor[10000001];
long long cnt[64];

long long mod = 987654321;
const int N = 65;

struct matrix
{
	long long x[N+1][N+1];
	matrix(){memset(x, 0, sizeof(x));}
	matrix(long long init)
	{
		memset(x, 0, sizeof(x));
		for(int i = 0; i <= N; i++)
			x[i][i] = init;
	}
	matrix operator +(matrix that)
	{
		matrix ret;
		for(int i = 0; i <= N; i++)
			for(int j = 0; j <= N; j++)
				ret.x[i][j] = (x[i][j] + that.x[i][j]) % mod;
		return ret;
	}
	matrix operator -(matrix that)
	{
		matrix ret;
		for(int i = 0; i <= N; i++)
			for(int j = 0; j <= N; j++)
				ret.x[i][j] = (x[i][j] - that.x[i][j] + mod) % mod;
		return ret;
	}
	matrix operator *(matrix that)
	{
		matrix ret;
		for(int i = 0; i <= N; i++)
			for(int j = 0; j <= N; j++)
				for(int k = 0; k <= N; k++)
					ret.x[i][j] = (ret.x[i][j] + x[i][k] * that.x[k][j]) % mod;
		return ret;
	}	
}I(1);

matrix power(matrix b, long long e)
{
	matrix ret = I;
	while(e)
	{
		if(e&1) ret = ret * b;
		b = b * b;
		e /= 2;
	}
	return ret;
}

/*  Note
	1. Set N: matrix size
	2. Set mod
*/

/*  Eaxmple
	matrix init, trans;
	init.x[1][1] = 2, init.x[2][1] = 1;
	trans.x[1][1] = 2, trans.x[1][2] = 1, trans.x[2][2] = 2;
	cout << (power(trans, 5) * init).x[1][1] << endl;
*/


int main()
{
	memset(minFactor, 0, sizeof(minFactor));
	for(int i = 2; i <= 10000000; i++)
		if(minFactor[i] == 0)
			for(int j = i; j <= 10000000; j+=i)
				minFactor[j] = i;
	nFactor[1] = 0;
	for(int i = 2; i <= 10000000; i++)
		nFactor[i] = 1 + nFactor[i / minFactor[i]];


	dp[0] = 0;
	dp[1] = 0;
	memset(cnt, 0, sizeof(cnt));

	for(int i = 2; i <= 24; i++)
	{
		memset(have, false, sizeof(have));
		for(int j = 1; j < i; j++)
			for(int k = 1; k < i; k++)
				have[dp[j]^dp[k]] = true;
		for(int j = 0; ; j++)
			if(!have[j])
			{
				dp[i] = j;
				break;
			}
		//cout << i << " : " << dp[i] << endl;
	}

	for(int i = 2; i <= 10000000; i++)
		cnt[dp[nFactor[i]]] ++;

	matrix init, trans;
	init.x[0][0] = 1;
	for(int i = 0; i <= 63; i++)
		for(int j = 0; j <= 63; j++)
		{
			trans.x[i^j][i] += cnt[j];
		}


	matrix res = power(trans, 1000000000000LL) * init;

	long long ans = 0;
	for(int i = 1; i <= 63; i++)
	{
		ans += res.x[i][0];
		ans %= mod;
	}
	cout << ans << endl;	
	return 0;
}
