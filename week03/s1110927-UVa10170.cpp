#include<iostream>

using namespace std;

int initial_member;
long long target_room;

int ans = 0;

int main() {
	while (cin >> initial_member >> target_room) {
		int current_archive_room = 0;
		if (initial_member >= target_room) {
			cout << initial_member;
			continue;
		}

		for (int i = initial_member; i <= target_room; i++) {
			current_archive_room += i;
			if (current_archive_room >= target_room) {
				cout << i << endl;
				break;
			}
		}

		//for (int end = sqrt(target_room)+1; end >= initial_member; end--) {
		//	current_archive_room = ((end + initial_member) * ((end - initial_member)+1)) / 2;
		//	if (current_archive_room < target_room) {
		//		cout << end+1 << endl;
		//		break;
		//	}
		//}
	}
}