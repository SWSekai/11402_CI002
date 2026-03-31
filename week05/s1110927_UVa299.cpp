#include <iostream>
#include<vector>

using namespace std;

int test_case;

int main() {
	cin >> test_case;
	while (test_case) {
		int train_len;
		int carriages[50];
		int count = 0;
		cin >> train_len;

		for (int i = 0; i < train_len; i++) {
			cin >> carriages[i];
		}

		for (int i = 0; i < train_len; i++) {
			for (int j = i+1; j < train_len; j++) {
				if (carriages[i] > carriages[j]) {
					swap(carriages[i], carriages[j]);
					count++;
				}
			}
		}
		cout << "Optimal train swapping takes " << count << " swaps." << endl;
		test_case--;
	}
}