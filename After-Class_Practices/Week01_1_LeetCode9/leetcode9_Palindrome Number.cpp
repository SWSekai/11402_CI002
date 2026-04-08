#include<iostream>

using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0 || (x % 10 == 0 && x != 0)) return false;
        int reverb_num = 0;
        while (x > reverb_num) {
            reverb_num = reverb_num * 10 + x % 10;
            x /= 10;
        }
        return x == reverb_num || x == reverb_num / 10;
    }
};

int main() {
    int num;
    while (cin >> num) {
		bool result = Solution().isPalindrome(num);
		cout << (result ? "true" : "false") << endl;
    }
}