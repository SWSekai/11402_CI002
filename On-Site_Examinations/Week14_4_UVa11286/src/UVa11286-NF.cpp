#include <iostream>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

class Conformity {
public:
	static int popular_class(priority_queue<int> class_set) {
		int ans = 0, res = 0;
		int current = 0, next = 0;

		while (!class_set.empty()) {
			current = next;
			next = class_set.top();
			class_set.pop();

			if (current == next) res++;
			else {
				ans = max(ans, res);
				res = 0;
			}
		}

		return ans;
	}
};

int main() {
	int man_num, class_num;
	while (cin >> man_num && man_num != 0) {
		int all_class = man_num * 5;
		while (all_class--) {
			priority_queue<int> class_select;
			cin >> class_num;
			class_select.push(class_num);
		}
		cout << Conformity::popular_class << endl;
	}
}