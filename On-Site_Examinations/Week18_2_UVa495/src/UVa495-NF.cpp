/*
	需要尋找更好的分配方法與存值方式，5000 有機會超越 long long 型別範圍
*/
#include <iostream>
#include <vector>

using namespace std;

class Fibonacci_Freeze {
public:
	static long long countFiboncci(int input) {
		if (!initialized) {
			fn.resize(5000);
			fn[0] = 0;
			fn[1] = 1;

			for (int i = 2; i <= fn.size(); ++i) {
				fn[i] = fn[i - 1] + fn[i - 2];
			}
		}

		return fn[input];
	}
private:
	static vector<long long> fn;
	static bool initialized;
};

//static vector<long long> fn;
//static bool initialized = false;

int main() {
	int input, min;
	vector<long long> fn(5000);
	fn[0] = 0;
	fn[1] = 1;

	/*for (int i = 2; i <= fn.size(); ++i) {
		fn[i] = fn[i - 1] + fn[i - 2];
	}*/

	while (cin >> input) {
		//if (input == 0) break;
		//cout << "The Fibonacci number for " << input << " is " << Fibonacci_Freeze::countFiboncci(input) << endl;
		for (int i = 2; i <= input; ++i) {
			fn[i] = fn[i - 1] + fn[i - 2];
		}

		cout << "The Fibonacci number for " << input << " is " << fn[input] << endl;
	}
}