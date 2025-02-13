#include <cstdio>
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;
const int N=1000;
long double a[N*N+5],b[N*N+5],degrees[N*N+5];
inline bool neighbor(int x,int y)
{
    return abs(x-y)<=1 && !(x<y && x%N==0 && y%N==1 || x>y && x%N==1 && y%N==0) || abs(x-y)==N;
}
int main()
{
    long double delta=100;
    long long total_deg=0;
    for (int i=1;i<=N*N;++i)
    {
        if (i>N) degrees[i]++;
        if (i<=N*(N-1)) degrees[i]++;
        for (int j=max(1,i-1);j<=min(i+1,N*N);++j)
            if (j>=1 && j<=N*N && neighbor(i,j))
                degrees[i]++;
        total_deg+=degrees[i];
    }
    // if starting with equi-probability, it will take hours to converge!
    for (int i=1;i<=N*N;++i)
        a[i]=degrees[i]*1.0/total_deg;
    printf("init finished\n");
    int step=0;
    while (delta>1e-14)
    {
        for (int i=1;i<=N*N;++i)
        {
            b[i]=0;
            if (i>N) b[i]+=a[i-N]/degrees[i-N];
            if (i<=N*(N-1)) b[i]+=a[i+N]/degrees[i+N];
            for (int j=max(1,i-1);j<=min(i+1,N*N);++j)
                if (neighbor(i,j))
                    b[i]+=a[j]/degrees[j];
        }
        delta=0;
        for (int i=1;i<=N*N;++i)
        {
            delta+=fabsl(b[i]-a[i]);
            a[i]=b[i];
        }
        step++;
        //if (step%10==0)
            cout<<step<<" finished not converge yet, delta="<<setprecision(13)<<delta<<endl;
    }
    long double sum=0,need=0;
    for (int i=1;i<=N*N;++i)
        sum+=b[i];
    for (int i=1;i<=N;++i)
        need+=b[i*i];
    long double ans1=need/sum;
    printf("first part finished\n");
    // second part
    // if starting with equi-probability, it will take hours to converge!
    for (int i=1;i<=N*N;++i)
        a[i]=(degrees[i]-1)*1.0/(total_deg-N*N);
    delta=100,step=0;
    while (delta>1e-14)
    {
        for (int i=1;i<=N*N;++i)
        {
            b[i]=0;
            if (i>N) b[i]+=a[i-N]*0.5/(degrees[i-N]-1);
            if (i<=N*(N-1)) b[i]+=a[i+N]*0.5/(degrees[i+N]-1);
            for (int j=max(1,i-1);j<=min(i+1,N*N);++j)
                if (neighbor(i,j))
                {
                    if (i!=j) b[i]+=a[j]*0.5/(degrees[j]-1);
                    else b[i]+=a[j]*0.5;
                }
        }
        delta=0;
        for (int i=1;i<=N*N;++i)
        {
            delta+=fabsl(b[i]-a[i]);
            a[i]=b[i];
        }
        step++;
        //if (step%10==0)
            cout<<step<<" finished not converge yet, delta="<<setprecision(13)<<delta<<endl;
    }
    sum=0,need=0;
    for (int i=1;i<=N*N;++i)
        sum+=b[i];
    for (int i=1;i<=N;++i)
        need+=b[i*i];
    long double ans2=need/sum;
    cout<<setprecision(13)<<(ans1+ans2)/2<<endl;
    return 0;
}