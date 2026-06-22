#include <iostream>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

class Add_All {
	//最小兩值互加
public:
	static int MinimumCost(vector<int> num_set) {
		priority_queue<int, vector<int>, greater<int>> pq;
		int cost, tot_cost = 0;

		for(int i = 0; i< num_set.size(); i++)  {
			pq.push(num_set[i]);
		}

		while (pq.size() > 1) {
			int first = pq.top();
			pq.pop();
			int second = pq.top();
			pq.pop();

			cost = first + second;
			tot_cost += cost;
			pq.push(cost);
		}

		return tot_cost;
	}
};

int main() {
	int amount_num, num;
	while (cin >> amount_num && amount_num != 0) {
		vector<int> num_set;
		while (amount_num--) {
			cin >> num;
			num_set.push_back(num);
		}
		cout << Add_All::MinimumCost(num_set) << endl;
	}

	return 0;
}