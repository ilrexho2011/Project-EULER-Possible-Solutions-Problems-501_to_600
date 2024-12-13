#include<bits/stdc++.h>
using namespace std;

#define for2(a,b,c) for(int a = b; a < c; a++)
const int maxn = 31;
int a[maxn];
int dp[maxn][maxn];
double E[maxn];

inline void shift(int len)
{
	int last = a[0];
	for2(i,1,len)
	{
		int tmp = a[i];
		a[i] = last;
		last = tmp;
	}
	a[0] = last;
}

int32_t main()
{
	for2(i,2,maxn) for2(j,0,i){
		for2(t,0,i) a[t] = t+(t >= j);
		a[i-1] = j;
		while(1)
		{
			bool b = 0;
			for2(t,1,i)
			{
				if( a[t] < a[t-1] )
				{
					dp[i][j] ++;
					b = 1;
					shift(t+1);
					break;
				}
			}
			if(!b)  break;
		}
	}
	E[1] = 0;
	E[2] = 0.5;
	for2(i,3,maxn)
	{
		int sum = 0;
		for2(j,0,i) sum += dp[i][j];
		E[i] = double(sum)/i + E[i-1];
	}
	cout << fixed << setprecision(2) << endl;
	cout << E[maxn-1] << endl;
	return 0;
}