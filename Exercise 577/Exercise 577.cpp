#include <iostream>
using namespace std;
unsigned long long int sol[12400];
int extPoints(int a)
{
	if(a==1)
		return 1;

	return 3*(a-1);
}
unsigned long long int solve(int n)
{
	unsigned long long int sum=0;
		int a=0;
		for(int i=n-3;i>=1;i-=3)
		{

			sum+=(++a)*extPoints(i);
		}
		if(n>=7)
			sum+=sol[n-3];
		return sum;
}
int main()
{
	unsigned long long int sum=0,temp;
	for(int i=4;i<=12346;i++)
	{
	    temp=solve(i);
		sum+=temp;
		sol[i]=temp;



	}
	cout<<sum<<'\n';


	return 0;
}