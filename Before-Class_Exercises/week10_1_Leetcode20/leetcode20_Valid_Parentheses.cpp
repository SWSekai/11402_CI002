class Solution {
public:
    bool isValid(string s) {
        vector<char> queue;

        map<char, char> parentheses_map = {
            {')', '('},
            {'}', '{'},
            {']', '['}
        };

        for (int i = 0; i < s.length(); i++) { // length()邊界條件錯誤（已修正）
            if (s[i] == ')' || s[i] == '}' || s[i] == ']') {
                if (queue.size() == 0) return false;

				char last = queue.back();

                auto idx = parentheses_map.find(s[i]);
				auto key = idx->first;
                auto value = idx->second;

                if (last == value) queue.pop_back();
				else return false;
            }
            else queue.push_back(s[i]);
        }

        if (queue.empty()) return true;
        else return false;
    }
};