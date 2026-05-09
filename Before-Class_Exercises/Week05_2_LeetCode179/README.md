# LeetCode 179 - Largest Number

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 179
- **Problem Title:** Largest Number
- **Problem Link:** https://leetcode.com/problems/largest-number/
- **Source Code (Correct/Accepted):** [leetcode179.cpp](https://github.com/SWSekai/11402_CI002/blob/main/Before-Class_Exercises/Week05_2_LeetCode179/leetcode179.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 一個整數陣列 `nums`（非負整數）
- **Expected Output:** 一個字串，代表將所有數字拼接後所能得到的最大數值
- **Rules/Constraints:** 結果可能非常大，必須以字串形式回傳；不能有前導零（除非結果本身就是 0）
- **Core Task:** 重新排列陣列中的數字順序，使得拼接後的字串在字典序意義下最大

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 直覺想到直接將數字轉成字串後排序，但單純按字典序排序（如 "9" > "80"）無法得到正確結果，例如 [3, 30] 排序後 "303" 並非最大，"330" 才是正確答案
- 需要自定義比較規則

### Final Strategy
- 使用自定義排序，比較兩個字串 `a+b` 與 `b+a` 的大小；若 `a+b > b+a` 則 a 應排在 b 前面
- 利用 `std::sort` 搭配 lambda 表達式實作比較函數
- 最後處理 corner case：若排序後第一個字元是 '0'，則直接回傳 "0"

### Edge Cases Handled
- 全為 0 時應回傳 "0" 而非 "000..."

## 4. Pseudocode

```text
START
1. 將所有數字轉為字串存入 vector<string>
2. 對字串陣列排序，比較規則為 s1+s2 > s2+s1
3. 若排序後第一個字元為 '0'，回傳 "0"
4. 否則將所有字串拼接並回傳
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        vector<string> strs;
        for (int n : nums) strs.push_back(to_string(n));
        sort(strs.begin(), strs.end(), [](string &a, string &b) {
            return a + b > b + a;
        });
        if (strs[0] == "0") return "0";
        string ans;
        for (string &s : strs) ans += s;
        return ans;
    }
};
```
**Why it works:**
- 自定義排序保證了區域最優的拼接順序，傳遞性使得整體拼接結果最大

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 透過自定義 comparator 決定數字順序，而非單純字典序或數值排序 |
| **Edge Cases** | 處理全零情況，避免回傳 "000...0" 而改為 "0" |

### Reflection
- 排序問題中，comparator 的設計至關重要，關鍵在於找到一個有傳遞性的比較規則，使得局部最優能保證全域最優
