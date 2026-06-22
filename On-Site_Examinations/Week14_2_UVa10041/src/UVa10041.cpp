#include <iostream>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

class Vito_Family {
	// 位置決定最短距離
	// 絕對值(abs)
public:
	static int SumOfDistance(priority_queue<int>& loc) {
		int sum = 0, sum_e = 0;
		int vito_loc, vito_loc_e = 0;
		vector<int> loc_v;
		
		while(!loc.empty()) {
			loc_v.push_back(loc.top());
			loc.pop();
		}

		if (loc_v.size() % 2 == 0) {
			vito_loc_e = loc_v[loc_v.size() / 2+1];
		}
		vito_loc = loc_v[(loc_v.size() / 2)];

		for (int i = 0; i < loc_v.size(); ++i) {
			sum += abs(loc_v[i] - vito_loc);
			sum_e += abs(loc_v[i] - vito_loc_e);
		}

		if (loc_v.size() % 2 == 0) return min(sum, sum_e);

		return sum;
	}
private:
	static void print(int num) {
		cout << num << endl;
	}
};

int main() {
	int test_case;
	priority_queue<int> family_position;
	int num, position;

	cin >> test_case;
	while (test_case--) {
		cin >> num;
		while (num--) {
			cin >> position;
			family_position.push(position);
		}

		cout << Vito_Family::SumOfDistance(family_position) << endl;
	}

	return 0;
}