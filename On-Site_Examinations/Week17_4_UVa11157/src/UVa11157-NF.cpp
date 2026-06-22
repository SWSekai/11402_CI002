/*
# Situation
 	- run time error
	- 猜測輸入的問題
		- 數字輸入應該有更好的處理方式
*/

#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;



int main() {
	int test_case;
	cin >> test_case;
	for (int i = 1; i <= test_case; i++) {
		int n;
		long d, cur_d = 0, max = 0;
		cin >> n >> d;
		vector<long> stones;
		
		while (n--) {
			string input;
			cin >> input;
			if (input[0] == 'S') continue;
			else {
				int num = input[2] - '0';

				for (int j = 3; j < input.length(); j++) {
					num = num * 10 + int(input[j] - '0');
				}
				stones.push_back(num);
			}
		}

		for (auto dt : stones) {
			cur_d = dt - cur_d;
			if (max < cur_d) max = cur_d;
		}

		cur_d = d - stones.back(); // 最後一個間隔
		if (max < cur_d) max = cur_d;

		cout << "Case " << i << ": " << max << endl;
	}
}