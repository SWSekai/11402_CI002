#include <iostream>
#include <string>
#include<vector>

using namespace std;

class Solution {
public:
	void Uva10931(int num) {
		int parity = 0;
		vector<int> loss;

		while (num != 0) {
			int los = num % 2;
			num = num / 2;
			loss.push_back(los);
		}
		while (true) {
			vector<int> loss_bp;

			if (loss_bp.back() == 1) parity++;
			loss_bp.pop_back();

			if (loss_bp.empty()) break;
		}

		cout << "The parity of ";
		while (!loss.empty()) {
			cout << loss.back();
			loss.pop_back();
		}
		
		 cout << " is " << parity << " (mod 2)." << endl;
	}
};

int main() {
	int input;
	while (cin >> input && input != 0) {
		Solution sol;
		sol.Uva10931(input);
	}
	return 0;
}