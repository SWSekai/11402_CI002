#include <iostream>

using namespace std;

class Cola {
public:
	static int get_total_bottle(int initial_bottle) {
		if (initial_bottle <= 1) {
			return initial_bottle;
		}

		int total_bottle = initial_bottle;
		//bool borrow_flag = false;
		int coke_bottle = initial_bottle;
		//int empty_bottle = 0;

		while (coke_bottle != 1) {
			total_bottle += coke_bottle / 3;
			coke_bottle = coke_bottle / 3 + coke_bottle % 3;

			if (coke_bottle == 2) {
				total_bottle += 1;
				//borrow_flag = true;
				return total_bottle;
			}
		}
		return total_bottle;
	}
};

int main() {
	int initial_bottle;

	while (cin >> initial_bottle) {
		cout << Cola::get_total_bottle(initial_bottle) << endl;
	}
}