#include <iostream>
#include <string>
#include <climits>

using namespace std;

class EventPlanning {
public:

};

int main() {
	int participant, budget, hotel, week;
	while (cin >> participant >> budget >> hotel >> week) {
		int min_cost = INT_MAX;
		while (hotel--) {
			int cost, available_room, sum = 0;
			bool is_enough = false;
			cin >> cost;

			for (int i = 0; i < week; i++) {
				cin >> available_room;
				if (!is_enough && available_room >= participant) {
					is_enough = true;
				}
			}
			if (is_enough) {
				sum = cost * participant;
				if (sum < min_cost) min_cost = sum;
			}
		}
		cout << (min_cost <= budget ? to_string(min_cost) : "stay home") << endl;
	}

	return 0;
}