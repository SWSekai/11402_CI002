#include<iostream>

using namespace std;

class Odd_Sum {
public:
	static int calculate_all_odd_sun(int a, int b) {
		int ans = 0;
		if (a > b) swap(a, b);
		for (int i = a; i <= b; i++) (i % 2 != 0) ? ans += i : 0;

		return ans;
	}
};

int main() {
	int round, case_num = 1;
	cin >> round;

	while (round--){
		int num1, num2;
		cin >> num1 >> num2;
		cout << "Case " << case_num << ": " << Odd_Sum::calculate_all_odd_sun(num1, num2) << endl;
		case_num++;
	}
}