#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Solution {
public:
	static string language_detection(string input) {
		if (input == "HELLO") return "ENGLISH";
		else if (input == "HOLA") return "SPANISH";
		else if (input == "HALLO") return "GERMAN";
		else if (input == "BONJOUR") return "FRENCH";
		else if (input == "CIAO") return "ITALIAN";
		else if (input == "ZDRAVSTVUJTE") return "RUSSIAN";
		else return "UNKNOWN";
	}
};

int main() {
	int count = 1;
	string input;

	while (getline(cin, input) && input != "#") {
		cout << "Case " << count << ": " << Solution::language_detection(input) << endl;
		count++;
	}
}