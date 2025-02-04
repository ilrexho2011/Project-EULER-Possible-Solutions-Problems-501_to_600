#include <iostream>
#include <iomanip>
using namespace std;

// return (n choose n/2) / 2^(n-1)
long double getMiddleTerm(long long n) {
    long double answer = 1.0;
    long long currTopFact = n;
    long long currBottomFact = n/2;
    long long numTwosLeft = n - 1;
    while (true) {
        bool canAddTop = false;
        bool canAddBottom = false;
        bool canAddTwo = false;
        if (currTopFact > n - n/2) {
            canAddTop = true;
        }
        if (currBottomFact > 1) {
            canAddBottom = true;
        }
        if (numTwosLeft > 0) {
            canAddTwo = true;
        }
        
        if (!(canAddTop || canAddBottom || canAddTwo)) break;
        if (canAddTop && (answer <= 1.0 || (!canAddBottom && !canAddTwo))) {
            answer *= (long double)currTopFact;
            currTopFact--;
            continue;
        }
        if (canAddBottom && (answer > 1.0 || !canAddTop)) {
            answer /= (long double)currBottomFact;
            currBottomFact--;
            continue;
        }
        if (canAddTwo && (answer > 1.0 || !canAddTop)) {
            answer *= 0.5;
            numTwosLeft--;
            continue;
        }
    }
    return answer;
}

long double JSumB(long long n) {
    long double ans = 1.0;
    long double dn = (long double)n;
    long double currInvertedChoose = 1.0/dn;
    for (long long k = 2; k <= n; k++) {
        long double dk = (long double)k;
        long double nextInvertedChoose = currInvertedChoose * dk/((long double)(n+1)-dk);
        ans += 1.0/(dk-1.0)*(1.0-currInvertedChoose);
        ans += 1.0/dk;
        currInvertedChoose = nextInvertedChoose;
    }
    return ans;
}

long double JSumA(long long n) {
    long double ans = 0.0;

    // Start at largest binomial coefficients and work down.
    long double midChoose = getMiddleTerm(n+1);  // (n+1 choose (n+1)/2 ) / 2^n
    long double coeffSumIncreasing = 1.0;  // 2^(n+1) / 2^n
    long double currChoose = midChoose;
    long double coeffSumDecreasing = coeffSumIncreasing - currChoose;
    long long k = (n + 1) / 2;
    if (n % 2 == 1) {
        // 2^(n+1)/2^n = 2*coeffSum + currChoose
        coeffSumDecreasing = (2.0 - midChoose)*0.5;
        coeffSumIncreasing = coeffSumDecreasing + midChoose;
        currChoose *= (long double)k / (long double)(n + 2 - k);
    }

    for (long long k = n/2; k >= 1; k--) {
        ans += coeffSumIncreasing / (long double)k;
        coeffSumIncreasing += currChoose;
        currChoose *= (long double)k / (long double)(n + 2 - k);
    }
    
    currChoose = midChoose;
    if (n % 2 == 0) currChoose *= (long double)(n + 1 - k) / (long double)(k + 1);
    for (long long k = n/2+1; k <= n; k++) {
        currChoose *= (long double)(n + 1 - k) / (long double)(k + 1);
        ans += coeffSumDecreasing / (long double)k;
        coeffSumDecreasing -= currChoose;
    }
    return ans;
}

int main() {
    cout << setprecision(18);
    long long N = 123456789;
    long double aSum = JSumA(N);
    cout << "A: " << aSum << endl;
    long double bSum = JSumB(N);
    cout << "B: " << bSum << endl;
    cout << "Sum: " << aSum + bSum << endl;
}