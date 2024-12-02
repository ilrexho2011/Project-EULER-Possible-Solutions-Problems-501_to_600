#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;

long long N = 100000;
unordered_map < long long , vector <int> > mem;
long long bound = 0;
long long delta = 1;
int nextX[100001];
int nextB[100001];

int main()
{
	long long ans = 0;
	for(int i = 1; i <= N; i++)
	{
		nextX[i] = 1;
		nextB[i] = i;
	}

	while(bound * bound <= N*N*4)
	{
		bound += delta;
		mem.clear();

		vector <int> empty;
		for(long long c = 1; c <= N; c++)
		{
			for(long long x = nextX[c]; x <= c; x++)
			{
				long long t = 4*x*x + c*c;
				if(t > bound * bound)
					break;
				nextX[c] = x + 1;
				if(mem.count(t) == 0)
					mem[t] = empty;
				mem[t].push_back(c);
			}
		}

		for(long long a = 1; a <= N; a++)
		{
			
			for(long long b = nextB[a]; b <= N; b++)
			{
				long long t = 2 * (a*a + b*b);
				if(t > bound * bound)
					break;	
				nextB[a] = b+1;
				if(mem.count(t))
				{
					for(int i = 0; i < mem[t].size(); i++)
					{
						int c = mem[t][i];
						if(a+b > c && c >= b)
							ans ++;
					}
				}
			}
		}
	}
	cout << ans << endl;
	return 0;
}