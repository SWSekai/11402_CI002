#include <iostream>
#include<vector>

using namespace std;

class Train_swapping {
public:
	static int count_swaps(int train_len, int carriages[]) {
		int count = 0;

		for (int i = 0; i < train_len; i++) {
			for (int j = i + 1; j < train_len; j++) {
				if (carriages[i] > carriages[j]) {
					swap(carriages[i], carriages[j]);
					count++;
				}
			}
		} 
		return count;
	}
};

int main() {
	int test_case;
	cin >> test_case;
	while (test_case--) {
		int train_len;
		cin >> train_len;

		int carriages[50];
		for (int i = 0; i < train_len; i++) {
			cin >> carriages[i];
		}
		
		cout << "Optimal train swapping takes " << Train_swapping::count_swaps(train_len, carriages) << " swaps." << endl;
	}
}