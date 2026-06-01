#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Rotating_Sentences {
public:
	static vector<string> rotate_sentences(const vector<string> &sentences, int max_length) {
		vector<string> result;
		for (int i = 0; i <= max_length - 1; i++) {
			string result_line;
			for (int j = sentences.size() - 1; j >= 0; j--) {
				result_line += (i < sentences[j].length() ? sentences[j][i] : ' '); // 如果當前行的長度不足，則添加空格
			}
			result.push_back(result_line);
		}
		return result;
	}
};

int main()
{
	string input;
	vector<string> sentences;
	int max_length = 0; // 總列數

	while (getline(cin, input)) {
		sentences.push_back(input);
		max_length = max(max_length, (int)input.length());
	}

	vector<string> result = Rotating_Sentences::rotate_sentences(sentences, max_length);

	for (const auto& line : result) cout << line << endl;
}