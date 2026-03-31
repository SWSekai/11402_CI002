#include<iostream>

using namespace std;

int num;

int main() {
	while (cin >> num && num != 0) {
		if (num == 1) {
			cout << 1 << endl;
			continue;
		}

		int ans = 0;
		int inside_square = 1;

		for (int i = 1; i <= num; i++) {
			inside_square = i;
			int row_allow_num = 0;
			for (int j = 1; j <= num - inside_square+1; j++) {
				row_allow_num += 1;
			}
			ans += row_allow_num*row_allow_num;
		}
		cout << ans << endl;
	}
}