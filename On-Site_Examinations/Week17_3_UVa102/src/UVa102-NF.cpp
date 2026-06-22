/*
# Solution
- 評斷第一袋的最小移動數，其餘按照案例個別處理

# Pending
- 期望使用 struct 和條件案例處理，但失去通用性，並喪失封裝可能
*/
#include <iostream>
#include <vector>

using namespace std;

struct Glass {
	char glass;
	int glass_num;
};

int main() {
	while (true) {
		int input_num = 9, input;
		vector<int> bin;

		while (input_num--) {
			cin >> input;
			bin.push_back(input);
		}
		Glass{ 'b', bin[1] + bin[2] + bin[3] + bin[6]};
		Glass{ 'g', bin[0] + bin[2] + bin[4] + bin[7]};
		Glass{ 'c', bin[0] + bin[1] + bin[5] + bin[8]};
	}
	
}