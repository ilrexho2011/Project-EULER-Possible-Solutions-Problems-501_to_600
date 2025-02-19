#include <cstdio>
#include <cmath>
using namespace std;
const long long N=5000;
const long long MOD=1000000000LL*8;
long long gcd(long long a,long long b)
{
    if (!b) return a;
    return gcd(b,a%b);
}
long long calc(long long a,long long b,long long c,long long d,long long t,long long ggg)
{
    long long bases[3][3];
    bases[0][0]=a*a+b*b-c*c-d*d,bases[1][0]=2*(b*c+d*a),bases[2][0]=2*(b*d-c*a);
    bases[0][1]=2*(b*c-d*a),bases[1][1]=a*a-b*b+c*c-d*d,bases[2][1]=2*(c*d+b*a);
    bases[0][2]=2*(b*d+c*a),bases[1][2]=2*(c*d-b*a),bases[2][2]=a*a-b*b-c*c+d*d;
    for (int i=0;i<3;i++)
        for (int j=0;j<3;j++)
            bases[i][j]=bases[i][j]/ggg*t;
    long long max_val[3]={0},min_val[3]={0};
    for (int i=1;i<8;i++)
    {
        long long point[3]={0};
        for (int j=0;j<3;j++)
            if (i&(1<<j))
                for (int k=0;k<3;k++)
                    point[k]+=bases[j][k];
        for (int k=0;k<3;k++)
        {
            if (point[k]>max_val[k]) max_val[k]=point[k];
            if (point[k]<min_val[k]) min_val[k]=point[k];
        }
    }
    long long ret=1;
    for (int k=0;k<3;k++)
    {
        long long mmin=-min_val[k],mmax=N-max_val[k];
        if (mmin<=mmax) ret=ret*(mmax-mmin+1);
        else return 0;
    }
    return ret;
}
long long abs(long long x)
{
    return x>=0?x:-x;
}
long long mult(long long a,long long b)
{
// calculate (a*b) mod MOD
    a%=MOD,b%=MOD;
    long long ans=0;
    while (b)
    {
        if (b&1) (ans+=a)%=MOD;
        (a<<=1)%=MOD;
        b>>=1;
    }
    return ans%MOD;
}
int main()
{
    long long ans=0;
    for (long long a=-sqrt(N);a<=sqrt(N);a++)
    {
        for (long long b=-sqrt(N-a*a);b<=sqrt(N-a*a);b++)
            for (long long c=-sqrt(N-a*a-b*b);c<=sqrt(N-a*a-b*b);c++)
                for (long long d=-sqrt(N-a*a-b*b-c*c);d<=sqrt(N-a*a-b*b-c*c);d++)
                    if ((a || b || c || d) && abs(gcd(gcd(a,b),gcd(c,d)))==1 && (a*a+b*b+c*c+d*d)%2==1)
                    {
                        long long length=a*a+b*b+c*c+d*d;
                        long long d1=abs(gcd(a*a+b*b-c*c-d*d,2*gcd(b*c-d*a,b*d+c*a)));
                        long long d2=abs(gcd(a*a-b*b+c*c-d*d,2*gcd(b*c+d*a,c*d-b*a)));
                        long long d3=abs(gcd(a*a-b*b-c*c+d*d,2*gcd(b*d-c*a,c*d+b*a)));
                        long long temp=gcd(d1,gcd(d2,d3));
                        length/=temp;d1/=temp;d2/=temp;d3/=temp;
                        for (long long t=1;;t++)
                        {
                            long long count=calc(a,b,c,d,t,temp);
                            if (count<=0) break;
                            long long len=length%MOD,tt=t%MOD;
                            long long p1=mult(len,len),p2=mult(tt,tt),p3=mult(len,tt);
                            long long p4=mult(p1,p2);
                            long long ehrhart=mult((p3+1)%MOD,(p4+mult((d1+d2+d3-len)%MOD,tt)+1)%MOD);
                            ans=(ans+mult(count%MOD,ehrhart))%MOD;
                        }
                    }
        printf("%lld finished\n",a);
    }
    if (ans%8!=0) printf("err!\n");
    printf("%lld\n",ans/8);
    return 0;
}