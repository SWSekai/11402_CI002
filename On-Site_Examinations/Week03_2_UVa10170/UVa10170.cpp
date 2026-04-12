#include<iostream>

using namespace std;

class Infinite_room {
public:
	static long long get_room_group_size(int initial_member, long long target_room_number) {
		long long current_archive_room = 0;
		for(long long i = initial_member; i <= target_room_number; i++) {
			current_archive_room += i;
			if (current_archive_room >= target_room_number) {
				return i;
			}
		}
		return -1; // Should not reach here
	}
};

int main() {
	int initial_member;
	long long target_room;

	while (cin >> initial_member >> target_room) {
		int current_archive_room = 0;
		if (initial_member >= target_room) {
			cout << initial_member;
			continue;
		}

		cout << Infinite_room::get_room_group_size(initial_member, target_room) << endl;

		//for (int end = sqrt(target_room)+1; end >= initial_member; end--) {
		//	current_archive_room = ((end + initial_member) * ((end - initial_member)+1)) / 2;
		//	if (current_archive_room < target_room) {
		//		cout << end+1 << endl;
		//		break;
		//	}
		//}
	}
}