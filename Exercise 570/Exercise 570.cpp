#include <iostream>
#include <algorithm>

using namespace std;

struct GCalcer {
    vector<unsigned> factorization_sieve;

    size_t start_pow3;
    size_t start_pow4;
    size_t start_k;
    size_t initial_result;

    GCalcer(size_t start_k, size_t start_pow3, size_t start_pow4, size_t initial_result);

    unsigned calc_g(vector<unsigned>& fast_divisors, unsigned n) const;

    size_t calc_g_sum(unsigned n) const;
};

GCalcer::GCalcer(size_t start_k, size_t start_pow3, size_t start_pow4, size_t initial_result)
    : factorization_sieve(100000000)
    , start_pow3(start_pow3)
    , start_pow4(start_pow4)
    , start_k(start_k)
    , initial_result(initial_result)
{
    for (size_t i = 2; i < factorization_sieve.size(); ++i) {
        if (factorization_sieve[i] == 0) {
            for (size_t j = i + i; j < factorization_sieve.size(); j += i) {
                factorization_sieve[j] = i;
            }
        }
    }
}

inline size_t fast_mul(size_t initial, size_t base, size_t power, size_t modulo) {
    size_t current_power = base;
    size_t mul = 1;
    while (power > 0) {
        if (power & 1) {
            mul = (mul * current_power) % modulo;
        }
        power >>= 1;
        current_power = (current_power * current_power) % modulo;
    }
    return (initial * mul) % modulo;
}

unsigned GCalcer::calc_g(vector<unsigned>& fast_divisors, unsigned n) const {
    unsigned mul = 7 * n + 3;
    unsigned result = 6;
    fast_divisors.clear();
    while (factorization_sieve[mul] > 0) {
        fast_divisors.push_back(factorization_sieve[mul]);
        mul /= factorization_sieve[mul];
    }
    fast_divisors.push_back(mul);

    while (!fast_divisors.empty() && fast_divisors.back() < 5) {
        fast_divisors.pop_back();
    }

    for (size_t i = 0; i < fast_divisors.size(); ++i) {
        unsigned d = fast_divisors[i];
        if (i > 0 && fast_divisors[i - 1] == fast_divisors[i]) {
            d *= fast_divisors[i];
            size_t j = i - 1;
            while (j > 0 && fast_divisors[j - 1] == fast_divisors[i]) {
                d *= fast_divisors[i];
                --j;
            }
        }

        size_t p3 = fast_mul(start_pow3, 3, n - start_k, d);
        size_t p4 = fast_mul(start_pow4, 4, n - start_k, d);

        if ((d + 2 * p4 - p3) % d == 0) {
            result *= fast_divisors[i];
        }
    }

    return result;
}

size_t GCalcer::calc_g_sum(unsigned n) const {
    size_t result = initial_result;
    vector<unsigned> fast_divisors;
    for (size_t k = start_k; k <= n; ++k) {
        result += calc_g(fast_divisors, k);
    }
    return result;
}

size_t simple_gcd(size_t a, size_t b) {
    while (b > 0) {
        if (a > b) {
            swap(a, b);
        }
        b -= a * (b / a);
    }
    return a;
}

int main() {
    size_t sum_of_g = 6;
    size_t four_power = 4;
    size_t three_power = 3;
    for (size_t i = 4; i < 20; ++i) {
        four_power *= 4;
        three_power *= 3;
        size_t a = 2 * four_power - 1 * three_power;
        size_t b = (3 * i - 23) * four_power + (2 * i + 13) * three_power;
        size_t gcd = 6 * simple_gcd(a, b);
        sum_of_g += gcd;
    }


    // G(n) = 6 * gcd(2 * 4^(k - 2) - 3^(k - 2), (3k - 23) * 4^(k - 2) + (2k + 13) * 3 ^ k - 2)
    // Two and three can't be divisor of 2 * 4^(k - 2) - 3^(k - 2)
    // as the first argument % 2 != 0 we can multiply the second argument by 2
    // G(n) = 6 * gcd(2 * 4^(k - 2) - 3^(k - 2), (7k + 3) * 3 ^ (k - 2))

    GCalcer g_calcer(20, three_power * 3, four_power * 4, sum_of_g);
    cout << "Answer: " << g_calcer.calc_g_sum(10000000) << '\n';
};
