#include <iostream>
using namespace std;
#include <math.h>
int main(int argc, const char * argv[]) {
    long long sum=0;
    int limite=10000;
    long d;
    long A;
    long small_sum;
    long bc;
    long a2_bc;
    long a2pbc;
    for (long b=1; b<limite/2; b++) {
        for (long c=b; c<limite-b; c++) {
            bc=b*c;
            A=sqrt(bc)+1;
            a2_bc=A*A-b*c;
            a2pbc=bc*(2*A+b+c);
            for (long a=A; a<limite-b-c and a<=sqrt(bc*(b+1)*(c+1))+bc; a++) {
                if (a2pbc%a2_bc==0) {
                    d=a2pbc/a2_bc;
                    small_sum=a+b+c+d;
                    if (small_sum<=limite) {
                        cout<<a<<' '<<b<<' '<<c<<' '<<d<<' '<<small_sum<<endl;
                        sum+=small_sum;
                    }
                }
                a2_bc+=(2*a+1);
                a2pbc+=2*bc;
            }
        }
    }
    cout<<sum<<endl;
    return 0;
}