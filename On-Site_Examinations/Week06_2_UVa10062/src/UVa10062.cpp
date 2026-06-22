#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TellMeTheFrequencies {
public:
	static void printFrequencies(const string& str) {
		vector<int> res(128, 0); // ASCII character set size
		for (char c : str) {
			res[c]++;
		}
		for (int i = 1; i <= str.length(); ++i) {
			for (int j = res.size() - 1; j >= 0; --j) {
				if (res[j] == i) {
					cout << j << " " << res[j] << endl;
				}
			}
		}
	}
};

int main() {
	string str;
	bool flag_for_first_input = true;
	
	while (getline(cin, str)) {
		if (!flag_for_first_input) cout << endl;
		TellMeTheFrequencies::printFrequencies(str);

		flag_for_first_input = false;
	}
	return 0;
}