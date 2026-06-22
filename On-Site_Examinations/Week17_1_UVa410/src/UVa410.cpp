#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

class Station_Balance {
public:
	static void balance_stations(int chambers, int specimens, int round) {
		double sum = 0.0;
		int n = 2 * chambers;
		vector<int> spec_w(n, 0);

		for (int i = 0; i < specimens; i++) {
			cin >> spec_w[i];
			sum += spec_w[i];
		}

		double avg = sum / chambers, imbalance = 0.0;

		sort(spec_w.begin(), spec_w.end());

		cout << "Set #" << round << endl;

		for (int i = 0; i < chambers; i++) {
			int low = spec_w[i];
			int high = spec_w[n - 1 - i];

			cout << " " << i << ":";
			if (low) cout << " " << low;
			if (high) cout << " " << high;
			cout << endl;

			imbalance += abs((high + low) - avg);
		}

		cout << "IMBALANCE = " << fixed << setprecision(5) << imbalance << endl;
		cout << endl;
	}
};

int main() {
	int chambers, specimens, round = 1;

	while (cin >> chambers >> specimens) {
		Station_Balance::balance_stations(chambers, specimens, round++);
	}
}