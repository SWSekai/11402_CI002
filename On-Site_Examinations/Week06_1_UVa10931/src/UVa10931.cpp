#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Parity {
public:
	static vector<int> toBinary(int num) {
		vector<int> res;
		while (num > 0) {
			res.push_back(num % 2);
			num /= 2;
		}

		return res;
	}

	static int parityToModTwo(vector<int> num) {
		int count = 0;
		for (int i = 0; i < num.size(); i++) {
			if (num[i] == 1) {
				count++;
			}
		}

		return count;
	}
};

int main() {
	int num;
	while (cin >> num && num != 0) {
		vector<int> binary = Parity::toBinary(num);
		int parity = Parity::parityToModTwo(binary);

		cout << "The parity of ";
		for (int i = binary.size() - 1; i >= 0; i--) {
			cout << binary[i];
		}
		cout << " is " << parity << " (mod 2)."  << endl;
	}

	return 0;
}