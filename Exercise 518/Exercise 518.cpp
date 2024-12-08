#include<iostream>
#include<algorithm>
#include<cmath>

#define MAX 100000000
#define ll long long

using namespace std;

bool sieveprime[MAX/2+5];
ll prime[11522910];

void precalc_prime()
{
	int MAX_2=MAX/2+3;
	
	for(int i=1;i<=MAX_2;i++)
		sieveprime[i]=0;
		
	double SQRT_MAX=sqrt(MAX);
	
	for(int i=3;i<=SQRT_MAX;i+=2)
		if(!sieveprime[i/2])
			for(int j=i*i;j<=MAX;j+=2*i)
				sieveprime[j/2]=1;
}

bool check(ll x)
{
	if(x<2) return 0;
	if(x==2)  return 1;
	
	if(x%2==0) return 0;
	
	if(!sieveprime[x/2] ) return 1;
	
	return 0;
}

ll ans=0;

int mem[10][2];
void solve(ll prev,ll start,ll end,ll n)
{
	if(prev>=n) return;
	
	if(start==end)
	{
		if(check(prev-1))
		{ 
			ll p2=(n*n)/prev-1; 
			
			if(p2>MAX) return;
			
			if(check(p2)) 
			{ 
				if(n!=(p2+1)&&prev!=(p2+1)) 
				{
					ans+=prev+n+p2-2; 
				}
			}
		}
		return;
	}
	ll x=1;
	for(int i=0;i<=mem[start][1];i++)
	{
		solve(prev*x,start+1,end,n);
		x*=mem[start][0];
	}
}

void get_divisor_list(int n)
{
	int k=-1,curr=-1;
	ll temp=n;
	
	for(int i=0;i<10;i++) mem[i][1]=0;
	
	while(prime[++k]*prime[k]<=n)
	{
		if(n%prime[k]==0) mem[++curr][0]=prime[k];
		while(n%prime[k]==0)
		{
			n/=prime[k];
			mem[curr][1]+=2;
		}
	}
	if(n!=1)
	{
		mem[++curr][0]=n;
		mem[curr][1]+=2;
	}
	curr++;
	solve(1,0,curr,temp);
}

int main()
{
	precalc_prime();
	prime[0]=2;
	
	int curr=1;
	
	for(int i=3;i<MAX;i++)
		if(!sieveprime[i/2]) prime[curr++]=i;
	
	for(int i=2;i<curr;i++)
		get_divisor_list(prime[i]+1);	
	
	cout<<ans<<endl;
}