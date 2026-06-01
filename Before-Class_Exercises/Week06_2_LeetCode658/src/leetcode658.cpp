class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        while(arr.size()>k){
            if(x - arr.front() <= arr.back() - x) arr.pop_back();
            else arr.erase(arr.begin());
        }
        return arr;
    }
};