#include <iostream>
#include<string>
#include<map>

using namespace std;

int main() {
	int line;
	cin >> line;
	cin.ignore();

	map<string, int> word;

	while (line) {
		string sentence;
		getline(cin, sentence);

		for (int i = 0; i < sentence.length(); i++) {
			if (!isdigit) {
				sentence[i] = toupper(sentence[i]);
				word[to_string((sentence[i]))]++;
			}
		}
		line--;
	}
	for (char i = 'A'; i <= 'Z'; i++) {
		cout << i << " " << word[to_string(i)] << endl;
	}
}