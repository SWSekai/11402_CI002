//inclass01
#include <iostream>

using namespace std;

	int Uva100(int a, int b) {
		int minimum = min(a, b);
		int maximum = max(a, b);
		int max_count = 1;

		for (int i = a; i <= b; i++) {
			int count = 1;
			int tmp = i;

			while (tmp != 1) {
				if (tmp % 2 == 0) tmp /= 2;
				else tmp = 3 * tmp + 1;
				count++;
			}
			max_count = max(count, max_count);
		}
		return max_count;
	}

int main() {
	int a, b;
	cin >> a >> b;
	cout << a << " " << b << " ";
	cout << Uva100(a, b) << endl;

	return 0;
}