#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

class B2Sequence {
public:
	static bool isB2Sequence(vector<int> sequence) {
		set<int> verify_sequence;

		for (int i = 0; i < sequence.size(); i++) {
			for (int j = i; j < sequence.size(); j++) {
				int sum = sequence[i] + sequence[j];
				if (verify_sequence.count(sum)) return false;

				verify_sequence.insert(sum);
			}
		}
		return true;
	}
};

int main() {
	int test_case, n, count = 1;

	while (cin >> test_case) {
		int size = test_case, current = 0;
		bool isUpper = true;
		vector<int> sequence;

		while (size--) {
			cin >> n;
			if (current > n || n <= 0) isUpper = false;
			sequence.push_back(n);
			current = n;
		}

		cout << "Case #" << count++ << ": ";
		if (isUpper && B2Sequence::isB2Sequence(sequence)) {
			cout << "It is a B2-Sequence." << endl;
		}
		else {
			cout << "It is not a B2-Sequence." << endl;
		}
		cout << endl;
	}

	return 0;
}