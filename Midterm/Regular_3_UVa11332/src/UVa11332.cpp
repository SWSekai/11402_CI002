#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Solution {
public:
	static long long summing_digit(long long& input) {
		long long ans = input;

		while (ans >= 10) {
			long long tmp = ans;
			ans = 0;

			while (tmp >= 1) {
				ans += tmp % 10;
				tmp /= 10;
			}
		}
		return ans;
	}
};

int main() {
	long long input;
	while (cin >> input && input != 0) {
		cout << Solution::summing_digit(input) << endl;
	}
}