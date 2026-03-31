#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int test_case;
    if (!(cin >> test_case)) return 0;

    while (test_case--) {
        int location = 0;
        vector<int> request_log; // 儲存每次移動的位移量（-1 或 1）
        int move_count;

        cin >> move_count;
        cin.ignore(); // 重要：跳過數字後的換行符號

        for (int i = 0; i < move_count; ++i) {
            string request;
            getline(cin, request);

            if (request == "LEFT") {
                location -= 1;
                request_log.push_back(-1);
            }
            else if (request == "RIGHT") {
                location += 1;
                request_log.push_back(1);
            }
            else {
                // 解析 "SAME AS X"
                // 從索引 8 開始擷取到最後 (即 X 的部分)
                int index = stoi(request.substr(8));
                int move = request_log[index - 1];
                location += move;
                request_log.push_back(move);
            }
        }
        cout << location << endl;
    }
    return 0;
}