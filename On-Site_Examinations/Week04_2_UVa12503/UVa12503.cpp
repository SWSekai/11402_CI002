#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Robot_instruction {
public:
    static int parseInstruction(string cmd, const vector<int>& history) {
		if (cmd == "LEFT") {
            return -1;
        }
        else if (cmd == "RIGHT") {
            return 1;
        }
        else {
            stringstream ss(cmd);
            string last, temp;
            while (ss >> temp) {
                last = temp; // Get the last word
            }
            return history[stoi(last)-1];
        }
    }
};

int main() {
    int test_case;
    if (!(cin >> test_case)) return 0;

    while (test_case--) {
        int location = 0;
        vector<int> request_log = {};
        int move_count = 0;

        cin >> move_count;
        cin.ignore();

        for (int i = 1; i <= move_count; ++i) {
            string request;
            getline(cin, request);

			int current_move = Robot_instruction::parseInstruction(request, request_log);
			location += current_move;
			request_log.push_back(current_move);
        }
        cout << location << endl;
    }
    return 0;
}