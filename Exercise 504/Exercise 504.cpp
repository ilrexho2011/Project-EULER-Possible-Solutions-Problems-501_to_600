#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <inttypes.h>
#include <limits.h>
#include <math.h>

#define MAX_N 100

uint64_t answer;

int isPerfectSquare(int64_t n) {
  int64_t sqrtN= (int64_t)sqrt((double)n);
  return (sqrtN * sqrtN) == n;
}

int64_t gcdEuclid(int64_t a, int64_t b) {
  int64_t x= a;
  int64_t y= b;
  int64_t t;
  while ( y != 0 ) {
    t= x % y;
    x= y;
    y= t;
  }
  return x;
}

int64_t latOnSeg(int64_t x0, int64_t y0, int64_t x1, int64_t y1) {
  int64_t dx= (x0 > x1) ? x0 - x1 : x1 - x0;
  int64_t dy= (y0 > y1) ? y0 - y1 : y1 - y0;
  return 1 + gcdEuclid(dx, dy);
}

int main() {
  clock_t start;
  start = clock();

  int64_t los;
  int64_t area2;
  int64_t inside;

  for (int64_t a= 1; a <= MAX_N; a++) {
    for (int64_t b= 1; b <= MAX_N; b++) {
      for (int64_t c= 1; c <= MAX_N; c++) {
        for (int64_t d= 1; d <= MAX_N; d++) {
          los= latOnSeg(a, 0, 0, b);
          los+= latOnSeg(0, b, c, 0);
          los+= latOnSeg(c, 0, 0, d);
          los+= latOnSeg(0, d, a, 0);
          los-= 4;
          area2= (a + c) * (b + d);
          if ( ((area2 - los) % 2) == 0) {
            inside= 1 + ((area2 - los) / 2);
            if ( isPerfectSquare(inside) ) {
              answer++;
            }
          }
        }
      }
    }
  }

  double time_count = (double)(clock() - start) / CLOCKS_PER_SEC;
  printf("\nE504: %"PRIu64"\n", answer);
  printf("Elapsed time %f seconds\n", time_count);

  return 0;
}