#include <iostream>
#include <algorithm>
#include <cstring>
#include <chrono>
#include <cmath>

bool composite[50000001];
int smf[50000001];

// Computes the number of positive integers
// in [a, b] that are relatively prime to x.
int rel_prime(int x, int a, int b) {
    if (a < 1) a = 1;
    if (x == 1) return b - a + 1;

    int p[9];
    int size = 0;
    while (x != 1) {
        p[size] = smf[x];
        while (x % p[size] == 0) {
            x /= p[size];
        }
        size++;
    }

    int total0 = 0;
    int total1 = 0;
    for (int i = 0; i < (1 << size); ++i) {
        int sign = 1;
        int product = 1;
        for (int j = 0; j < size; ++j) {
            if (i & (1 << j)) {
                sign = -sign;
                product *= p[j];
            }
        }
        total0 += sign*(b/product);
        total1 += sign*((a-1)/product);
    }
    return total0 - total1;
}

// Computes the number of primitive Pythagorean triplets
// with hypotenuse less than or equal to N.
int64_t f(int64_t N) {
    static double root2 = std::sqrt(2.0);
    static double delta = 1 + root2;
    static double gamma = 1 + delta*delta;
    int64_t result = 0;
    int a, b;
    int limit = std::sqrt(2*N / gamma);
    for (int64_t i = 1; i <= limit; i += 2) {
        a = int(i / root2) + 1;
        b = (std::sqrt(2.0*N - i*i) - i)/2.0;
        result += rel_prime(i, a, b);
    }
    limit = std::sqrt(N / gamma);
    for (int64_t i = 1; i <= limit; ++i) {
        a = int(i*root2) + 1;
        b = std::sqrt(N - i*i) - i;
        result += rel_prime(2*i, a, b);
    }
    return result;
}

int main() {
    auto t0 = std::chrono::high_resolution_clock::now();
    std::memset(smf, -1, sizeof(smf));
    composite[0] = composite[1] = true;
    smf[0] = smf[1] = 1; smf[2] = 2;
    for (int i = 4; i <= 50000000; i += 2) {
        composite[i] = true;
        smf[i] = 2;
    }
    for (int64_t i = 3; i <= 50000000; i += 2) {
        if (!composite[i]) {
            smf[i] = i;
            for (int64_t j = i*i; j <= 50000000; j += 2*i) {
                composite[j] = true;
                if (smf[j] == -1) {
                    smf[j] = i;
                }
            }
        }
    }
    std::cout << f(3141592653589793ll) << '\n';
    auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << "Finished in " << std::chrono::duration_cast<std::chrono::seconds>(t1 - t0).count() << "s.\n";
    return 0;
}