#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
	static int parity(int input) {
		int num = input;
		int parity = 0;
		int count = 0;

		if (num == 1) {
			return input, 1;
		}

		while (num > 1) {
			parity = parity + (num % 2)*10^count;
			if (num % 2) count++;
			num /= 2;
		}
		return parity, count;
	}
};

int main() {
	int input;
	int parity_num = 0, count = 0;

	while (cin >> input && input != 0) {
		parity_num, count = Solution::parity(input);
		cout << "The parity of " << input <<  parity_num << " is " << count << " (mod2)." << endl;
	}
}