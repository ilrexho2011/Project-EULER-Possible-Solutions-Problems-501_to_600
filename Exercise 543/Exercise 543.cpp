#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 701450733

/*
  MAX_PRIME   PRIME_ARRAY_LENGTH
    100.000                9.592
  1.000.000               78.498
 10.000.000              664.579
100.000.000            5.761.455
*/
#define MAX_PRIME 701452733
#define PRIME_ARRAY_LENGTH 36326000  // Enough for MAX_PRIME <= 701.450.733


unsigned long answer;

int maxPrimesIndex;

// **** begin utility routines ****

int primes[PRIME_ARRAY_LENGTH + 10]; // Oversized
int primePi[MAX_PRIME + 1];
int P2[MAX_PRIME + 1];
char isPrime[MAX_PRIME + 1];

void sieveFillPrimes() {
  int i;
  for (i= 2; i <= MAX_PRIME; i++) {
    isPrime[i]= 1;
  }
  isPrime[0]= 0;
  isPrime[1]= 0;

  int j;
  for(i= 2; (i * i) < MAX_PRIME; i++)
    if ( isPrime[i] )
      for (j= (i * i); j <= MAX_PRIME; j+= i)
        isPrime[j]= 0;

  primes[0]= 2;
  maxPrimesIndex= 0; // Better safe than sorry
  int candidate= 3;
  do {
    if ( isPrime[candidate] ) {
      maxPrimesIndex++;
      primes[maxPrimesIndex]= candidate;
    }
    candidate+= 2;
  } while ( candidate <= MAX_PRIME );
  printf("Number of primes in array: %d\n", maxPrimesIndex + 1);
  printf("Index of primes[]: 0 to %d inclusive\n", maxPrimesIndex);
  printf("Max. prime: %d\n", primes[maxPrimesIndex]);
  printf("\n");
} // sieveFillPrimes()

void fillPrimePi() {
  int i= 0;
  int n= 0;
  while ( i <= MAX_N ) {
    if ( i == primes[n] ) n++;
    primePi[i]= n;
    i++;
  }
} // fillPrimePi()

void fillP2() {
  for (int i= 4; i <= MAX_N; i++) P2[i]= 1;
  for (int i= 11; i <= MAX_N; i+= 2) {
    if ( !isPrime[i -2] ) P2[i]= 0;
  }
} // fillP2()

// **** end utility routines ****

unsigned long S(int n) {
  unsigned long s= primePi[n];
  for (int i= 2; i <= n; i++) {
    s+= P2[i];
    if ( i >= 6 ) s+= (i / 2) -2;
  }
  return s;
} // S(.)

void calcResult() {
  int fk_1= 1;
  int fk= 2;
  int k= 3;
  int t;
  while ( k <= 44 ) {
    printf("Calculating k: %d\n", k);
    answer+= S(fk);
    t= fk;
    fk+= fk_1;
    fk_1= t;
    k++;
  }
}

// **** main ****

int main() {
  clock_t start= clock();

  printf("\nFilling array primes[]\n");
  sieveFillPrimes();
  printf("Array primes[] filled after %f seconds\n", (double)(clock() - start) / CLOCKS_PER_SEC);

  printf("\nFilling array primePi[]\n");
  fillPrimePi();
  printf("Array primePi[] filled after %f seconds\n", (double)(clock() - start) / CLOCKS_PER_SEC);

  printf("\nFilling array P2[]\n");
  fillP2();
  printf("Array P2[] filled after %f seconds\n", (double)(clock() - start) / CLOCKS_PER_SEC);

  calcResult();

  double time_count = (double)(clock() - start) / CLOCKS_PER_SEC;
  printf("\n\ne543: %lu\n\n", answer);
  printf("Elapsed time %f seconds\n", time_count);

  return 0;
}