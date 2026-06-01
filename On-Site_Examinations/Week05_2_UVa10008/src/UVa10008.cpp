#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Letter {
	char alpha;
	int count;
};

class Cryptanalysis {
private:
	int counts[26] = {0};
	
	static bool compareLetters(const Letter& a, const Letter& b) {
		if (a.count != b.count) {
			return a.count > b.count;
		}
		return a.alpha < b.alpha;
	}

public:
	void analyze(const string& text) {
		for (char c : text) {
			if (isalpha(c)) {
				counts[toupper(c) - 'A']++;
			}
		}
	}

	void printResults(){
		vector<Letter> validLetters;

		for (int i = 0; i < 26; ++i) {
			if (counts[i] > 0) {
				validLetters.push_back({ (char)('A' + i), counts[i] });
			}
		}

		sort(validLetters.begin(), validLetters.end(), compareLetters);

		for (const auto& leaf : validLetters) {
			cout << leaf.alpha << " " << leaf.count << endl;
		}
	}
};

int main() {
	int line_num;
	cin >> line_num;
	cin.ignore();

	Cryptanalysis analyzer;

	while (line_num--) {
		string sentence;
		getline(cin, sentence);
		analyzer.analyze(sentence);
	}
	analyzer.printResults();
}