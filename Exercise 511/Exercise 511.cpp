#include <iostream>
#include <vector>
#include <ctime>

#define MOD 4321

using namespace std;

int main(int argc, const char * argv[])
{
    vector<uint64_t> d = {1,5,41,205,25343,126715,237631,1039063,1188155,5195315,9742871,48714355,6022282433,30111412165,246913579753,1234567898765};
    
    for (int i = 0; i < d.size(); ++i)
    {
        d[i] = d[i]%MOD;
    }
    
    uint64_t x[41][MOD];
    
    for (int i = 0; i < 41; ++i)
    {
        for (int j = 0; j < MOD; ++j)
        {
            x[i][j] = 0;
        }
    }
    
    for (int i = 0; i < d.size(); ++i)
    {
        ++x[0][d[i]];
    }
    
    for (int i = 1; i < 41; ++i)
    {
        for (int j = 0; j < MOD; ++j)
        {
            for (int k = 0; k < MOD; ++k)
            {
                x[i][j] += (x[i-1][k]*x[i-1][(MOD+(j-k)%MOD)%MOD])%1000000000;
                x[i][j] = x[i][j]%1000000000;
            }
        }
    }
    
    uint64_t ans[MOD];
    uint64_t tmp[MOD];
    
    for (int i = 0; i < MOD; ++i)
    {
        ans[i] = tmp[i] = 0;
    }
    
    ans[0] = 1;
    
    for (int i = 0; i < 41; ++i)
    {
        if ((1234567898765ULL >> i)&1)
        {
            for (int j = 0; j < MOD; ++j)
            {
                tmp[j] = ans[j];
                ans[j] = 0;
            }
            for (int j = 0; j < MOD; ++j)
            {
                for (int k = 0; k < MOD; ++k)
                {
                    ans[j] += (tmp[k]*x[i][(MOD+(j-k)%MOD)%MOD])%1000000000;
                    ans[j] = ans[j]%1000000000;
                }
            }
        }
    }
    
    cout << ans[(MOD+(MOD-1234567898765)%MOD)%MOD] << endl;
    cout << clock()/CLOCKS_PER_SEC << " seconds." << endl;
    return 0;
}