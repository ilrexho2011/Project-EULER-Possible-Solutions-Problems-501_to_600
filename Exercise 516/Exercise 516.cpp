#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <inttypes.h>
#include <limits.h>
#include <math.h>

#define MAX_N 1000000000000

uint64_t answer;

uint64_t hPrimes[543];
int hPrimesIndex; // After filling hPrimesIndex = 543

int isPrime(uint64_t n) {
  if (n < 2)
    return 0;
  if (n == 2 || n == 3)
    return 1;
  if (n % 2 == 0 || n % 3 == 0)
    return 0;
  uint64_t sqrtN= (uint64_t)sqrt((double)n) + 1;
  uint64_t i;
  for (i= 6; i <= sqrtN; i+= 6) {
    if (n % (i - 1) == 0 || n % (i + 1) == 0)
      return 0;
  }
  return 1;
}

void fillHPrimes() {
  uint64_t n2,n3,n5;
  uint64_t p;

  n2= 1;
  while ( (n2 + 1) <= MAX_N ) {
    n3= 1;
    while ( ((n2 * n3) + 1) <= MAX_N ) {
      n5= 1;
      while ( ((n2 * n3 * n5) + 1) <= MAX_N ) {
        p= (n2 * n3 * n5) + 1;
        if ( (p >= 7) && isPrime(p) ) {
          hPrimes[hPrimesIndex]= p;
          hPrimesIndex++;
        }
        n5*= 5;
      }
      n3*= 3;
    }
    n2*= 2;
  }
  // Sort array hPrimes
  for (int i= 0; i < (hPrimesIndex - 1); i++) {
    for (int j= (i + 1); j < hPrimesIndex; j++) {
      if ( hPrimes[j] < hPrimes[i] ) {
        p= hPrimes[i];
        hPrimes[i]= hPrimes[j];
        hPrimes[j]= p;
      }
    }
  }
}

void nextStep(uint64_t p, uint64_t qPrev, int startIndex) {
  uint64_t q;
  for (int i= startIndex; i < hPrimesIndex; i++) {
    q= qPrev * hPrimes[i];
    if ( (p * q) <= MAX_N ) {
      answer= (answer + (p * q)) % 4294967296;
      nextStep(p, q, i + 1);
    } else {
      break; // I don't like this but it works ...
    }
  }
}

int main() {
  clock_t start;
  start = clock();

  printf("\nFilling array with hPrimes\n");
  fillHPrimes();
  printf("Array hPrimes filled after %f seconds\n", (double)(clock() - start) / CLOCKS_PER_SEC);

  uint64_t n2, n3, n5;
  uint64_t p;

  n2= 1;
  while ( n2 <= MAX_N ) {
    n3= 1;
    while ( (n2 * n3) <= MAX_N ) {
      n5= 1;
      while ( (n2 * n3 * n5) <= MAX_N ) {
        p= n2 * n3 * n5;
        answer= (answer + p) % 4294967296;
        nextStep(p, 1, 0);
        n5*= 5;
      }
      n3*= 3;
    }
    n2*= 2;
  }

  double time_count = (double)(clock() - start) / CLOCKS_PER_SEC;
  printf("\nE516: %"PRIu64"\n", answer);
  printf("Elapsed time %f seconds\n", time_count);

  return 0;
}