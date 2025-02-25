#include <stdio.h>
#include <vector>
#include <algorithm>
//#define N 10000
#define N 10000000

int gcd(int a, int b)
{ return b ? gcd(b, a%b) : a; }

int isqrt(long long x) {
	long long x1, g0, g1;
	int s;

	if (x <= 1) return x;
	s = 1;
	x1 = x - 1;
	if (x1 > 0xFFFFFFFF) {s = s + 16; x1 = x1 >> 32;}
	if (x1 > 0xFFFF)     {s = s + 8; x1 = x1 >> 16;}
	if (x1 > 0xFF)       {s = s + 4; x1 = x1 >> 8;}
	if (x1 > 0xF)        {s = s + 2; x1 = x1 >> 4;}
	if (x1 > 3)          {s = s + 1;}

	g0 = 1 << s;                // g0 = 2**s.
	g1 = (g0 + (x >> s)) >> 1;  // g1 = (g0 + x/g0)/2.

	while (g1 < g0) {           // Do while approximations
		g0 = g1;                 // strictly decrease.
		g1 = (g0 + (x/g0)) >> 1;
	}
	return g0;
}

int main()
{
	std::vector<std::pair<int, int>> pyth;
	int m, n, d;
	for (m = 1; m*m < N; m++)
		for (n = 1; n < m; n++) if ((m+n)%2 && gcd(n, m) == 1) {
			int k = m*m + n*n;
			for (d = 1; k*d <= N; d++) {
				if (d % 2 == 0)
					pyth.push_back(std::make_pair((m*m-n*n)*d, 2*m*n*d));
				pyth.push_back(std::make_pair(2*m*n*d, (m*m-n*n)*d));
			}
		}
	//printf("[number of triangles: %d]\n", pyth.size());fflush(stdout);
	std::sort(pyth.begin(), pyth.end());
	long long result = 0;
	for (auto it = pyth.begin(); it != pyth.end(); ) {
		auto jt = it;
		for (; jt != pyth.end() && jt->first == it->first; ++jt)
			;
		// a^2+b^2=k^2
		// a^2+m^2=4c^2
		// a^2+(2b+m)^2=4n^2
		for (auto kt = it; kt != jt; ++kt)
			if (kt->second % 2 == 0) {
				// 2b+m == kt->second
				for (auto mt = it; mt != kt; ++mt) {
					if (mt->second % 2 == 0 && std::binary_search(it, kt, std::make_pair(it->first, (kt->second - mt->second) / 2))) {
						int a = it->first;
						int b = (kt->second - mt->second) / 2;
						int c = isqrt((long long)a*a/4 + (long long)mt->second*mt->second/4);
						if (b > mt->second / 2 && a+2*b+2*c <= N)
							result += a+2*b+2*c;
					}
				}
			}
		it = jt;
	}
	printf("%lld\n", result);
	return 0;
}