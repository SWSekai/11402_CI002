class Solution {
public:
    bool isValid(string s) {
        vector<char> queue;

        map<char, char> parentheses_map = {
            {')', '('},
            {'}', '{'},
            {']', '['}
        };

        for (int i = 0; i <= s.length() - 1; i++) { // length() §Ñ°O -1
            if (s[i] == ')' || s[i] == '}' || s[i] == ']') {
                auto target = parentheses_map.find(s[i]);
                auto key = target->first;
                auto value = target->second;

                for (int j = queue.size() - 1; j >= 0; j--) {
                    char it = queue.at(j);

                    if (it == value) {
                        queue.erase(queue.begin() + j);
                        break;
                    }
                    if (j == 0)return false;
                }
            }
            else queue.push_back(s[i]);
        }
        if (queue.empty()) return true;
        else return false;
    }
};