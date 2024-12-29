#include<bits/stdc++.h>

using namespace std;

const int N = 3000000;

long long u[N+31];

int B(int x)
{
	if (x==0)
		return 0;
	return B(x/2)+x%2;
}

long long pw(int a,int b)
{
	long long res=1;
	for (int i=1;i<=b;i++)
		res=res*a;
	return res;
}

long long ans;

multiset<long long> vals;
multiset<long long>::iterator it;

int main(){
	ios_base::sync_with_stdio(0);
	//cin.tie(0);
	
	for (int i=1;i<=N;i++)
	{
		u[i]=pw(2,B(3*i))+pw(3,B(2*i))+B(i+1);
	}
	
	long long q=0;
	
	for (int i=1;i<=3;i++)
		vals.insert(u[i]);
	
	long double bst=0;
	
	for (int i=4;i<=N;i++)
	{
		
		vals.insert(u[i]);
		it=vals.lower_bound(u[i]);
		
		
		for (int iter=1;iter<=4;iter++)
			if (it!=vals.begin())
				--it;
		
		vector<long long> v;
		for (int iter=1;iter<=9;iter++)
		{
			v.push_back(*it);
			++it;
			if (it==vals.end())
				break;
		}
		sort(v.begin(),v.end());
		for (int j=0;j+3<v.size();j++)
		{
			if (v[j]+v[j+1]+v[j+2]<v[j+3])
				continue;
			long double p=(v[j]+v[j+1]+v[j+2]+v[j+3]);
			p/=2;
			long double area=sqrt((p-v[j])*(p-v[j+1])*(p-v[j+2])*(p-v[j+3]));
			if (area>bst-1e-12)
			{
				bst=area;
				q=v[j]+v[j+1]+v[j+2]+v[j+3];
			}
		}
		ans+=q;
		if (i%100000==0)
			cout<<i<<" "<<q<<" "<<ans<<endl;
		
	}
	
	cout<<ans<<endl;
	
	return 0;
}