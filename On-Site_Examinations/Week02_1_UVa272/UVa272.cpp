#include <iostream>
#include <string>

using namespace std;

class TEX_Quotes {
public:
    static string replace_quotes(string& str, bool& flag) {
        string result;

        for (size_t i = 0; i <= str.length()-1; i++) {
            if (str[i] == '"' && flag == false) {
                result += "``"; //利用 += 延長字串
                flag = true;
            }
            else if (str[i] == '"' && flag == true) {
                result += "''";
                flag = false;
            }
            else result += str[i];
        }
        return result;
    }
};

int main()
{
    string str;
    string result;
    bool flag = false; // flag 的生命週期應該在 main 函式內，因為它需要在多行輸入中保持狀態

    while (getline(cin, str)) {
        result = TEX_Quotes::replace_quotes(str, flag);
        cout << result << endl;
    }
}