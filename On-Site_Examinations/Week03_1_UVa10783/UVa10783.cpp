#include<iostream>

using namespace std;

int num;

int main() {
	cin >> num;
	int round = 1;

	while (num) {
		int a, b;
		int ans = 0;
		cin >> a >> b;

		if (a > b) {
			int tmp = a;
			a = b;
			b = tmp;
		}

		for (int i = a; i <= b; i++) {
			if (i % 2 != 0) ans += i;
		}
		cout << "Case " << round << ": " << ans << endl;
		num--;
		round++;
	}
}