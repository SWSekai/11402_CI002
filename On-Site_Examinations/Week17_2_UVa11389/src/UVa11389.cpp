#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Bus_Scheduling {
public:
	static int claculate_minimum_cost(vector<int> morning, vector<int> evening, int d, int r){
		int cost = 0;
		sort(morning.begin(), morning.end());
		sort(evening.begin(), evening.end(), greater<int>());

		for (size_t i = 0; i < morning.size(); i++) {
			int total = morning[i] + evening[i];
			if (total > d) cost += (total - d) * r;
		}

		return cost;
	}
};

int main() {
	int n, d, r;
	while (cin >> n >> d >> r) {
		if (n == 0 && d == 0 && r == 0) break;
		vector<int> morning(n), evening(n);

		for (int i = 0; i < n; i++) cin >> morning[i];
		for (int i = 0; i < n; i++) cin >> evening[i];

		cout << Bus_Scheduling::claculate_minimum_cost(morning, evening, d, r) << endl;
	}
}