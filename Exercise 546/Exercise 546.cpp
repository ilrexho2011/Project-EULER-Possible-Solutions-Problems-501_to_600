#include <iostream>
using namespace std;

const int K = 3;
const int LAYERS_DEEP = 50;
const long long MOD = 1000000007;

long long coeffs[LAYERS_DEEP][K][LAYERS_DEEP+2];
long long sCache[LAYERS_DEEP][LAYERS_DEEP];

// S(0, N, 0) is just f(N).  cacheDepth just tells us how many /K's we've done.
long long S(int L, long long N, int cacheDepth) {
    if (N < 1) return 1;

    // Check cache:
    if (sCache[L][cacheDepth] != -1) {
        return sCache[L][cacheDepth];
    }

    // Otherwise, recurse!
    // For mod --> K mapping, we want K-1 to map to 0!  K-2 should map to 1, etc...
    int currMod = (-1-N) % K;
    if (currMod < 0) currMod += K;
    long long currSum = 0;
    for (int c = 0; c < L+2; c++) {
        if (coeffs[L][currMod][c] != 0) {
            currSum += (coeffs[L][currMod][c]*S(c, N/K, cacheDepth+1)) % MOD;
            currSum %= MOD;
        }
    }

    sCache[L][cacheDepth] = currSum;
    return currSum;
}

int main() {
    // Prep the s-cache to all -1's
    for (int l = 0; l < LAYERS_DEEP; l++) {
        for (int i = 0; i < LAYERS_DEEP; i++) {
            sCache[l][i] = -1;
        }
    }

    // Now for the coefficients
    for (int l = 0; l < LAYERS_DEEP; l++) {
        for (int k = 0; k < K; k++) {
            for (int c = 0; c < LAYERS_DEEP+2; c++) coeffs[l][k][c] = 0;
        }
    }
    
    // base case L=0: coeffs are <K,0>,<K,-1>,<K,-2>,...
    for (int i = 0; i < K; i++) {
        coeffs[0][i][1] = (long long)K;
        coeffs[0][i][0] = (long long)-i;
    }
    
    for (int L = 1; L < LAYERS_DEEP; L++) {
        // first row is sum of previous rows, all shifted over one to the left
        for (int c = 1; c < L+2; c++) {
            for (int i = 0; i < K; i++) {
                coeffs[L][0][c] += coeffs[L-1][i][c-1];
                coeffs[L][0][c] %= MOD;
            }
        }
        
        // current row = row above - previous+above row (none shifted)
        for (int k = 1; k < K; k++) {
            for (int c = 0; c < L+2; c++) {
                coeffs[L][k][c] += coeffs[L][k-1][c];
                coeffs[L][k][c] %= MOD;

                coeffs[L][k][c] -= coeffs[L-1][k-1][c];
                coeffs[L][k][c] %= MOD;
            }
        }
    }
    
    cout << K << ": " << S(0, 100000000000000, 0) << endl;
    
    return 0;
}
