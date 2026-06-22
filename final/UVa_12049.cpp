//#include <iostream>
//#include <climits>
//#include <algorithm>
//#include <string>
//#include <set>
//#include <vector>
//#include <cmath>
//#include <sstream>
//#include <array>
//
//using namespace std;
//
//int main() {
//	int test_case;
//	cin >> test_case;
//	while (test_case--) {
//		int m, n, input, count = 0;
//		cin >> m >> n;
//		vector<int> first, second;
//		set<int> num_set;
//		
//		for (int i = 0; i <= 10000; i++) {
//			first.push_back(0);
//			second.push_back(0);
//		}
//
//		while (m--) {
//			cin >> input;
//			first[input]++;
//			num_set.insert(input);
//		}
//		while (n--) {
//			cin >> input;
//			second[input]++;
//			num_set.insert(input);
//		}
//
//		for (auto i : num_set) {
//			if (first[i] != second[i]) {
//				if (first[i] > second[i]) count += first[i] - second[i];
//				else count += second[i] - first[i];
//			}
//		}
//
//		cout << count << endl;
//	}
//}