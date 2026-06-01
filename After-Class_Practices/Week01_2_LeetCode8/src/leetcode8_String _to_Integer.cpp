class Solution {
public:
    int myAtoi(string s) {
        int sign = 1;
        long long num = 0; //使用 long long 儲存數字，避免溢出
        int i = 0;
        int n = s.length();

        while(i<n && s[i] == ' ') i++;

        if(i<n && s[i] == '+' || s[i] == '-'){
            sign = (s[i] == '-') ? -1:1;
            i++;
        }
        while(i<n && isdigit(s[i])){
            num = num*10 + (s[i] - '0'); //-'0' 將字符轉換為數字

            // 檢查是否溢出
            if(num*sign >= INT_MAX) return INT_MAX;
            if(num*sign <= INT_MIN) return INT_MIN;
            i++;
        }
        return (int)(num*sign); // 因為已經在前面檢查過溢出，所以轉換是安全的(符合返回類型)
    }
};