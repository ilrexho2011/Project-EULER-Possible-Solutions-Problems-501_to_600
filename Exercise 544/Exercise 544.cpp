#include <iostream>
#include <map>
#include <vector>
#include <gmpxx.h>

#if 1
#define R 9
#define C 10
#define N 1112131415
#else
#define R 2
#define C 2
#define N 15
#endif

struct state
{
	char color[R];
};

bool operator<(const state& l, const state& r)
{ return memcmp(l.color, r.color, R) < 0; }

struct poly
{
	std::vector<mpz_class> coeffs;
	poly() {}
	poly(const mpz_class& c) : coeffs(1, c) {}
	poly& operator=(const mpz_class& c) {
		coeffs.resize(1);
		coeffs[0] = c;
		return *this;
	}
	void add_x() {
		if (coeffs.size() < 2)
			coeffs.resize(2, 0);
		coeffs[1]++;
	}
	poly& operator+=(const poly& r) {
		if (coeffs.size() < r.coeffs.size())
			coeffs.resize(r.coeffs.size(), 0);
		for (size_t i = 0; i < r.coeffs.size(); i++)
			coeffs[i] += r.coeffs[i];
		return *this;
	}
};

int main()
{
	mpz_class totalResult = 0;
	std::map<state, poly> cur;
	state init;
	memset(init.color, 0, R);
	cur[init] = 1;
	for (int i = 0; i < C; i++)
		for (int j = 0; j < R; j++) {
			std::map<state, poly> next;
			state nextState;
			for (std::map<state, poly>::const_iterator pit = cur.begin(); pit != cur.end(); ++pit) {
				if (i == 0 && j == 0) {
					next[pit->first].add_x();
					continue;
				}
				char maxColor = 0;
				for (int s = 0; s < R; s++)
					maxColor = std::max(maxColor, pit->first.color[s]);
				for (int k = 0; k <= maxColor + 1; k++) {
					if (i && k == pit->first.color[j])
						continue;
					if (j && k == pit->first.color[j - 1])
						continue;
					nextState = pit->first;
					nextState.color[j] = k;
					signed char colormap[R + 1];
					for (int s = 0; s <= R; s++)
						colormap[s] = -1;
					int usedColorsNext = 0;
					for (int s = 0; s < R; s++) {
						if (colormap[nextState.color[s]] == -1) {
							colormap[nextState.color[s]] = usedColorsNext++;
						}
						nextState.color[s] = colormap[nextState.color[s]];
					}
					if (k <= maxColor) {
						next[nextState] += pit->second;
					} else {
						//next[nextState] += (n - maxColor - 1) * pit->second;
						if (next[nextState].coeffs.size() <= pit->second.coeffs.size())
							next[nextState].coeffs.resize(pit->second.coeffs.size() + 1, 0);
						for (int i = 0; i < (int)pit->second.coeffs.size(); i++) {
							next[nextState].coeffs[i] -= (maxColor + 1 - i) * pit->second.coeffs[i];
							next[nextState].coeffs[i + 1] += pit->second.coeffs[i];
						}
					}
				}
			}
			cur.swap(next);
		}
	poly result = mpz_class(0);
	for (std::map<state, poly>::const_iterator it = cur.begin(); it != cur.end(); ++it)
		result += it->second;
	mpz_class s = 0;
	mpz_class prod = 1;
	for (int i = 0; i < (int)result.coeffs.size(); i++) {
		prod *= N + 1 - i;
		s += result.coeffs[i] * prod / (i + 1);
	}
	std::cout << s << "\t" << (s % 1000000007) << "\n";
	return 0;
}