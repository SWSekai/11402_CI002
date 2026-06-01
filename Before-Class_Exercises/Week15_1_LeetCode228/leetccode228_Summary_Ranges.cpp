class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        if(nums.empty()) return {};
        vector<string> res;
        int cur = nums[0];
        int first = cur;

        for(size_t i = 0; i< nums.size(); ++i){            
            if(cur != nums[i]){
                int end = nums[i-1];
                string str = rangeBounding(first, end);
                res.push_back(str);

                first = nums[i];
                cur = first;
            }
            if(i == nums.size()-1){
                int end = nums[i];
                string str = rangeBounding(first, end);
                res.push_back(str);
                continue;
            }
            cur++;
        }

        return res;
    }
private:
    string rangeBounding(int first, int end){
        if(first == end) return to_string(first);
        else return to_string(first) + "->" + to_string(end);
    }
};