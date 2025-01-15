#include "stdafx.h"
#include <iostream>
__int64 g(__int64 n) {
	__int64 r = 0;
	while (n > 0) {
		r += n % 10;
		n /= 10;
	}
	return r;
}
__int64 a[16][164][181];
__int64 b[16][164][181];
int main()
{
	int i, j, k, l;
	int x;
	for (j = 0; j < 164; ++j)
		for (k = 0; k < 181; ++k)
		if (j!=0 || k!=0) {
			b[0][j][k] = 0;
			a[0][j][k] = k;
			while (a[0][j][k] < 1000) {
				++b[0][j][k];
				a[0][j][k] += g(a[0][j][k]) + j;
			}
		}
	__int64 y = 1000;
	for (i = 1; i < 16; ++i) {
		for (j = 0; j < 164 - 9 * i; ++j)
			for (k = 0; k < 181; ++k)
				if (j != 0 || k != 0) {
					b[i][j][k] = 0;
					x = k;
					for (l = 0; l <= 9; ++l) {
						b[i][j][k] += b[i - 1][j + l][x];
						x = a[i - 1][j + l][x] - y;
					}
					a[i][j][k] = x + y * 10;
				}
		y *= 10;
	}
	i = 0;
	y = 1000;
	__int64 z = 0;
	__int64 n = 1000000000000000;
	while (b[i + 1][0][1] < n) {
		++i;
		y *= 10;
	}
	j = 0;
	x = 1;
	n -= 1;
	l = 1;
	z = 1;
	while (i > 0) {
		k = 0;
		while (b[i][j+k][x] < n) {
			n -= b[i][j+k][x];
			z += a[i][j+k][x] - x;
			x = a[i][j+k][x] - y;
			++k;
		}
		j += k;
		--i;
		y /= 10;
	}
	while (n > 0) {
		z += g(z);
		--n;
	}
	std::cout << z;
	std::cin >> i;
	return 0;
}