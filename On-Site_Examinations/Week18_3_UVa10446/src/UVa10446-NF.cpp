/*
* 暫無想法，或許使用 static 存值是比較可行的方式
 */
#include <iostream>

using namespace std;

class Marriage_Interview {
public:
	static long long trib(int n, unsigned int back, long long count) {
		if (n <= 0) return 1;
		if (n == 1) return 1;
		count++;

		for (unsigned int i = 1; i <= back; i++) {
			count += trib(n - i, back, count);
		}

		return count;
	}
};

int main() {
	int input_n, input_back;
	int round = 0;
	long long count = 0;

	while (cin >> input_n >> input_back) {
		if (input_n >= 60) break;
		round++;

		cout << "Case " << round << ": " << Marriage_Interview::trib(input_n, input_back, count) << endl;
	}
}