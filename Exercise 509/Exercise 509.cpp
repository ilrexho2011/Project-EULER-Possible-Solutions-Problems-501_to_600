#include <bits/stdc++.h>
using namespace std;

int f(int i,int j,int k)
{
	if(i==j&&j==k)
		return 1;
	else if(i==j||j==k)
	{
		return 3;
	}
	else
		return 6;
}

int main() 
{
	vector <long long> v(66,0);
	long long k=123456787654321;
	int y=0;
	while(k>0)
	{
		v[y]=(k+1)/2;
		k-=v[y];
		y++;
	}
	long long ans=0,mod=1234567890;
	for(int i=0;i<47;i++)
	{
		for(int j=i;j<47;j++)
		{
			for(int k=j;k<47;k++)
			{
				int u=f(i,j,k);
				if(((i^j)^k)!=0)
				{
					ans+=((((((u%mod)*(v[i]%mod))%mod)*(v[j]%mod))%mod)*(v[k]%mod))%mod;
					ans%=mod;
				}
			}
		}
	}
	cout<<ans;
	return 0;
}