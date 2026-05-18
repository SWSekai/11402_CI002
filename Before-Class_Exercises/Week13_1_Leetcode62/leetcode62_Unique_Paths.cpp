class Solution {
public:
    int uniquePaths(int m, int n) {
        int down_step = m-1;
        int right_step = n-1;
        int tot_step = down_step + right_step;

        return combination_calculator(tot_step, down_step, right_step);
    }
private:
    int combination_calculator(int tot, int a, int b){
        // 方法組合
        int min_num = min(a, b);
        long long res = 1; // 避免溢位



        for(int i = 1; i <= min_num; i++){
            res = res * (tot - min_num + i) / i; // 原有res *= (tot - min_num + i) /i; 會造成整數截斷
        }

        return static_cast<int>(res); //明確型別轉換意圖
    }
};