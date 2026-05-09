#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
	static int square_number(int& a, int& b) {
		if (a > b) swap(a, b);

		int count = 0;
		for (int i = sqrt(a)-1; i <= sqrt(b)+1; i++) {
			int num = i * i;
			if (num <= b && num >= a) count++;
		}
		return count;
	}
};

int main() {
	int a, b;

	while (cin >> a >> b && !(a==0 && b==0)) {
		cout << Solution::square_number(a, b) << endl;
	}
}