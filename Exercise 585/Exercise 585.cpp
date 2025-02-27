#include <stdio.h>
#include <math.h>
#include <string.h>

//#define N 5000
#define N 5000000

int gcd(int a, int b)
{ return b ? gcd(b, a%b) : a; }

int main()
{
	int k1, k2, k3, k4;
	int result = 0;
	long long result1 = 0, result2 = 0;
	static int sum1[N+1], sum2[N+1];
	printf("calculating sum1\n");fflush(stdout);
	for (k1 = 1; k1 <= N; k1++)
		sum1[k1] = (k1-1)/2;
	for (k1 = 1; 2*k1*k1 <= N; k1++)
		for (k2 = k1+1; k1*k1+k2*k2 <= N; k2++)
			if (gcd(k1, k2) == 1) {
				int s = k1*k1+k2*k2;
				int m = s;
				for (k3 = 1; m <= N; k3++, m += s)
					sum1[m]--;
			}
	for (k1 = 1; k1 <= N; k1++)
		result1 += sum1[k1];
	printf("calculating sum2\n");fflush(stdout);
	memcpy(sum2, sum1, sizeof(sum1));
	static char mu[N+1], primes[N+1];
	for (k1 = 1; k1 <= N; k1++) {
		mu[k1] = 1;
		primes[k1] = 1;
	}
	for (k1 = 2; k1*k1 <= N; k1++) if (primes[k1]) {
		for (k2 = k1; k2 <= N; k2 += k1) {
			mu[k2] = -mu[k2];
			primes[k2] = 0;
		}
		primes[k1] = 1;
		for (k2 = k1*k1; k2 <= N; k2 += k1*k1)
			mu[k2] = 0;
	}
	for (; k1 <= N; k1++) if (primes[k1])
		for (k2 = k1; k2 <= N; k2 += k1)
			mu[k2] = -mu[k2];
	for (k1 = 2; k1 <= N; k1++) if (mu[k1])
		for (k2 = 1; k1*k2 <= N; k2++)
			sum2[k1*k2] += sum1[k2] * mu[k1];
	printf("calculating first part of result2\n");fflush(stdout);
	for (k1 = 1; k1 <= N; k1++)
		for (k2 = 1; k1*k2 <= N; k2++) {
			result2 += (long long)sum1[k1] * sum2[k2];
		}
	printf("calculating exceptions of result2\n");fflush(stdout);
	int s1, s4, t1, t4;
	for (s1 = 1; s1*s1 <= N; s1++) if (mu[s1])
		for (s4 = 1; s1*s4*(s1+s4) <= N; s4++) if (mu[s4] && gcd(s1, s4) == 1)
			for (t1 = 1; (s1*t1+s4)*(s1*s4+t1) <= N; t1++) if (mu[t1] && gcd(t1, s1*s4) == 1)
				for (t4 = 1; (s1*t1+s4*t4)*(s1*s4+t1*t4) <= N; t4++) if (mu[t4] && gcd(t4, t1*s1*s4) == 1) {
					if (s1 == 1 && t1 == 1 && s4 == 1 && t4 == 1)
						continue;
					// k1 = s1*t1*r*x^2
					// k2 = s1*s4*y^2
					// k3 = t1*t4*z^2
					// k4 = s4*t4*r*w^2
					// gcd(k2, k3) == 1
					// gcd(x, w) == 1
					int x, y, z, w, r;
					for (r = 1; (s1*t1+s4*t4)*(s1*s4+t1*t4)*r <= N; r++) if (mu[r] && gcd(r, s1*t1*s4*t4) == 1) {
						for (y = 1; ; y++) {
							k2 = s1*s4*y*y;
							if ((k2+t1*t4)*(s1*t1+s4*t4)*r > N)
								break;
							for (z = 1; ; z++) {
								k3 = t1*t4*z*z;
								if ((k2+k3)*(s1*t1+s4*t4)*r > N)
									break;
								if (k2 >= k3)
									continue;
								if (gcd(k2, k3) != 1)
									continue;
								for (x = 1; ; x++) {
									k1 = s1*t1*r*x*x;
									if ((k2+k3)*(k1+s4*t4*r) > N)
										break;
									for (w = 1; ; w++) {
										k4 = s4*t4*r*w*w;
										if ((k2+k3)*(k1+k4) > N)
											break;
										if (k1 > k4) {
											result2--;
										}
									}
								}
							}
						}
					}
				}
	printf("%lld\n", result1 + result2/2);
	return 0;
}