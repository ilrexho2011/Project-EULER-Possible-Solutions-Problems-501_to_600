#include <iostream>
#include <cmath>
#include "primes.hpp"

using namespace std;

#define N 10000000000000LL
#define M 1000000LL

typedef long long ll;
ll *primes;


int binSearchPrimes(ll n, int low) {
	int high = primes[0];
	while (low < high) {
		int mid = (low + high) / 2;
		ll test = primes[mid];
		
		if (test <= n) {
			low = mid + 1;
		} else {
			high = mid;
		}
	}
	return low;
}

ll countMults(ll n, int index) {
  ll count = 0;
	
  for (int newIndex = index; newIndex <= primes[0]; newIndex++) {
    int prime = primes[newIndex];

    if (prime > n) {
      return count;
		}

    if (prime * prime > n) {
      int tfinalPrimes = newIndex;
			while (primes[tfinalPrimes] <= n) {
				tfinalPrimes++;
			}
			int finalPrimes = binSearchPrimes(n, newIndex);
		  return count + finalPrimes - newIndex;
		}

    ll newN = n;
    while (newN >= prime) {
      newN /= prime;
      count += 1;
      count += countMults(newN, newIndex+1);
		}
	}
  return count;
}


 // how many numbers 1 <= i <= n don't have any of the small primes
ll countNoSmallPrimes(ll n, int index, int maxIndex) {
  ll count = n;
  for (int nextIndex = index; nextIndex <= maxIndex; nextIndex++) {
    int prime = primes[nextIndex];
    if (prime > n) {
      return count;
		}

    ll newN = n / prime;
    if (newN > prime) {
      count -= countNoSmallPrimes(n / prime, nextIndex + 1, maxIndex);
		} else {
      count -= newN;
		}
	}
  return count;
}      

ll countDec(ll n, int index, int minToInc) {
  ll count = 0;
  for (int newIndex = index; newIndex <= primes[0]; newIndex++) {
    ll prime = primes[newIndex];
    ll prime2 = prime * prime;

    // prime then next_primes ** 2
    if (pow(prime, min(3, minToInc + 1)) > n) {
      break;
		}

    ll primePower = 0;
    ll newN = n;
    while (newN >= prime) {
      primePower += 1;
      newN /= prime;

      if (primePower > minToInc) {
        count += 1;
        if (newN > prime) {
          if (newN >= N / M) {
            count += countNoSmallPrimes(newN, 1, newIndex) - 1;
          } else {
						count += countMults(newN, newIndex + 1);
					}
				}
      } else if (newN > prime2) {
        count += countDec(newN, newIndex + 1, primePower);
			}
		}
	}
  return count;
}


// 6, 71, 759, 7758, 77948, 780216, 7803437?, 78033303?, 780315757?, 7803070411?,
// 2   3    4     5      6       7        8          9          10           11


int main(void) {
	primes = sieveOfErat(N / M);
	
	ll count = N - countDec(N, 1, 100);
	cout << "Answer 578: " << count << endl;
};