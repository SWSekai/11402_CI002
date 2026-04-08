#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TEX_Quotes {
public:
    static string replace_quotes(string &str) {
	    string result;
        int flag = 0;

        for (size_t i = 0; i <= str.length(); i++) {
            if (str[i] == '"' && flag == 0) {
				result += "``"; //利用 += 延長字串
                flag = 1;
            }
            else if (str[i] == '"' && flag == 1) {
				result += "''";
                flag = 0;
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

    while(getline(cin, str)) {
        result = TEX_Quotes::replace_quotes(str);
		cout << result << endl;
	}
}