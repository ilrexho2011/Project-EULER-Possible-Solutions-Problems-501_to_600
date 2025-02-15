#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>

using namespace std;

constexpr unsigned n = 100;
constexpr double g = 0.00002;

struct Range {
    double start;
    double end;
    double value;

    bool operator<(const Range& r) const {
        return start < r.start;
    }
};

void calc_S(unsigned p, vector<Range>& result) {
    set<Range> unvisited_ranges{{0.0, 1.0 - g, 0.0}};
    double step = sqrt(1.0 / double(p));
    double current = 0.0;
    double n_laps = 0.0;
    while (!unvisited_ranges.empty()) {
        current += step;
        if (current > 1.0) {
            --current;
            ++n_laps;
        }
        double hole_start = current > g ? current - g : 0.0;
        auto it = unvisited_ranges.lower_bound(Range{hole_start, current});
        if (it != unvisited_ranges.end() && it->start <= current) {
            if (it->end <= current) {
                // Remove range;
                result.push_back(Range{it->start, it->end, current + n_laps});
                unvisited_ranges.erase(it);
            } else {
                // Cut range from start
                result.push_back(Range{it->start, current, current + n_laps});
                Range n{current, it->end, 0.0};
                unvisited_ranges.erase(it);
                unvisited_ranges.insert(n);
            }
        } else {
            --it;
            if (it->end >= hole_start) {
                if (it->end >= current) {
                    // Cut in the middle
                    result.push_back(Range{hole_start, current, current + n_laps});
                    Range n1{it->start, hole_start, 0.0};
                    Range n2{current, it->end, 0.0};
                    unvisited_ranges.erase(it);
                    unvisited_ranges.insert(n1);
                    unvisited_ranges.insert(n2);
                } else {
                    // Cut range from the end;
                    result.push_back(Range{hole_start, it->end, current + n_laps});
                    Range n{it->start, hole_start, 0.0};
                    unvisited_ranges.erase(it);
                    unvisited_ranges.insert(n);
                }
            }
        }
    }
    sort(result.begin(), result.end());
}

int main() {
    vector<unsigned> primes;
    for (int i = 2; i <= n; ++i) {
        bool is_prime = true;
        for (auto p: primes) {
            if (i % p == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime) {
            primes.push_back(i);
        }
    }
    vector<vector<Range>> s_values;

    for (auto p: primes) {
        s_values.push_back(vector<Range>());
        calc_S(p, s_values.back());

        cout << "Calculated S for p=" << p << '\n';
    }

    double current_sum = 0.0;
    for (size_t i = 0; i < s_values.size(); ++i) {
        current_sum += s_values[i].back().value;
    }
    double max_sum = current_sum;
    while (!s_values.empty()) {
        double max_start = 0.0;
        size_t max_start_index = 0;
        for (size_t i = 0; i < s_values.size(); ++i) {
            if (s_values[i].back().start > max_start) {
                max_start = s_values[i].back().start;
                max_start_index = i;
            }
        }

        current_sum -= s_values[max_start_index].back().value;
        s_values[max_start_index].pop_back();
        current_sum += s_values[max_start_index].back().value;
        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
        if (s_values[max_start_index].size() == 1) {
            s_values[max_start_index].pop_back();
            s_values[max_start_index].swap(s_values.back());
            s_values.pop_back();
        }
    }

    cout.precision(16);
    cout << "Answer: " << max_sum << '\n';
}