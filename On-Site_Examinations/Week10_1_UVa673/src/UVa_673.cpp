#include <iostream>
#include <stack>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

map<char, char> mymap{
	{']', '['},
	{ ')', '(' }
};

class Parentheses_Balance {
public:
	static bool classifier(string s) {
		stack<char> container;

		for (int i = 0; i < s.length(); i++) {
			if (s[i] == ']' || s[i] == ')') {
				if (container.empty()) return false;
				char tmp = container.top();
				if(!container.empty()) container.pop();

				auto idx = mymap.find(s[i]);
				if (idx->second != tmp) return false;
			}
			else container.push(s[i]);
		}

		if (container.empty()) return true;
		else return false;
	}
};

int main() {
	int round;
	cin >> round;
	cin.ignore();

	while (round--) {
		string input;
		getline(cin, input);

		//cout << "input: " << input << endl;

		if (Parentheses_Balance::classifier(input)) {
			cout << "Yes" << endl;
		}
		else cout << "No" << endl;
	}
}