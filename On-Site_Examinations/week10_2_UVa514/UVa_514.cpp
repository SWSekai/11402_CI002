#include <iostream>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <vector>

using namespace std;

class Rail {
public:
	static bool classifier(int len, vector<int> target) {
		stack<int> tmp;
		vector<int> start;

		for (int i = 0; i < len; i++) {
			start.push_back(i);
		}

		int a_station_pointer = 0;
		for (int i = 0; i < target.size(); i++) {
			// when a_station_pointer == start.size(), IDE will return error
			// why a_station_pointer can equal start.size() ?

			if (target[i] != start[a_station_pointer]) {
				//tmp to target
				if (target[i] == tmp.top()) {
					tmp.pop();
					continue;
				}
				else return false;

				//start to tmp
				tmp.push(start[a_station_pointer]);
				a_station_pointer++;
			}
			else a_station_pointer++; // start to target
		}
		return true;
	}
};

int main() {
	int train_length;
	cin >> train_length;
	
	while (train_length != 0) {
		int input;
		vector<int> target;
		bool flag = false;

		int input_length = train_length;
		while (input_length--) {
			cin >> input;
			if (input == 0) {
				flag = true;
				break;
			}
			target.push_back(input);
		}
		if (flag) {
			cout << endl;
			break;
		}

		if (Rail::classifier(input_length, target)) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
}