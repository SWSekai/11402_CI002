#include<iostream>

using namespace std;

class Feynman {
public:
	static int count(int num) {
		if (num == 1) {
			return 1;
		}

		int ans = 0;
		int inside_square = 1;

		for (int i = 1; i <= num; i++) {
			inside_square = i;
			int row_allow_num = 0;
			for (int j = 1; j <= num - inside_square + 1; j++) {
				row_allow_num += 1;
			}
			ans += row_allow_num * row_allow_num;
		}
		return ans;
	}
};

int main() {
	int num;
	while (cin >> num && num != 0) {
		cout << Feynman::count(num) << endl;
	}
}