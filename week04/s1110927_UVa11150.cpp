//#include <iostream>
//
//using namespace std;
//
//int initial_bottle;
//
//int main() {
//	while (cin >> initial_bottle) {
//		int total_bottle = initial_bottle;
//		bool borrow_flag = false;
//
//		if (initial_bottle % 3 == 2) {
//			initial_bottle += 1;
//			borrow_flag = true;
//		}
//		while (initial_bottle/3 != 0) {
//			total_bottle += initial_bottle / 3;
//			initial_bottle /= 3;
//			if (initial_bottle % 3 == 2 && borrow_flag == false) {
//				initial_bottle += 1;
//				borrow_flag = true;
//			}
//		}
//		cout << total_bottle << endl;
//	}
//}