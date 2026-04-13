#include<iostream>

using namespace std;

class Infinite_room {
public:
	static long long get_room_group_size(long long initial_member, long long target_room_num) {

		if (initial_member >= target_room_num) return initial_member;

		long long low = initial_member;
		long long high = 2000000000LL; // 根據題目限制，最大成員數不會超過2*10^9
		long long answer = 0;

		while (low <= high) {
			long long mid = low + (high - low) / 2; // 避免(low + high)導致溢出
			if (is_reach_target_room(initial_member, mid, target_room_num)) {
				answer = mid;
				high = mid - 1;
			}
			else {
				low = mid + 1;
			}
		}
		return answer;
	}

private:
	static bool is_reach_target_room(long long initial_member, long long current_room_member, long long target_room_num) {
		long long total_day = 0;
		
		if ((initial_member + current_room_member) % 2 == 0) {
			total_day = ((initial_member + current_room_member) / 2) * (current_room_member - initial_member + 1);
			return total_day >= target_room_num;
		}
		else {
			total_day = (initial_member + current_room_member) * ((current_room_member - initial_member + 1) / 2);
			return total_day >= target_room_num;
		}
	}
};

int main() {
	long long initial_member;
	long long target_room;

	while (cin >> initial_member >> target_room) {
		cout << Infinite_room::get_room_group_size(initial_member, target_room) << endl;
	}
}