#include <iostream>
#include <algorithm>
#include <string>
#include<vector>

using namespace std;

class DragonOfLoowater {
public:
	static int classier(vector<int> dragon, vector<int> loowater) {
		int pointer = 0;
		int res = 0;

		for (int i = 0; i < dragon.size(); i++) {
			for (int j = pointer; j < loowater.size(); j++) {
				if (j >= loowater.size() - 1 && i < dragon.size() - 1) return 0;
				if (loowater[j] >= dragon[i]) {
					pointer = j + 1;
					res += loowater[j];

					break;
				}
				if(j >= loowater.size() - 1 && i <= dragon.size() - 1) return 0;
			}
			
		}

		return res;
	}
};

int main() {
	while (true) {
		int dragon_num, loowater_num;
		cin >> dragon_num >> loowater_num;
		if (dragon_num == 0 && loowater_num == 0) break;

		vector<int> dragon;
		vector<int> loowater;
		int input;

		while (dragon_num-- && cin >> input) dragon.push_back(input);
		while (loowater_num-- && cin >> input) loowater.push_back(input);

		sort(dragon.begin(), dragon.end());
		sort(loowater.begin(), loowater.end());

		int cost = DragonOfLoowater::classier(dragon, loowater);

		if (dragon.size() > loowater.size() || cost == 0) cout << "Loowater is doomed!" << endl;
		else cout << cost << endl;
	}
}