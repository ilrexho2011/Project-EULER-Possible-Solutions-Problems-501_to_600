#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	constexpr unsigned n = 1000000;
	cout.precision(10);

	double result = 1; // n * P(n, n)
	double previous = 1;
	previous = previous * pow(double(n - 1) / double(n), n - 1); // (n - 1) * P(n, n - 1)
	result += previous;
	for (int k = n - 2; k > 0; --k) {
		previous = previous * pow(double(k) / double(k + 1), k) * pow(double(n - k) / double(n - k - 1), n - k - 1);
		result += previous;
	}

	cout << "Answer: " << result << '\n';
}