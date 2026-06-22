# LeetCode 8 - String to Integer (atoi)

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 8
- **Problem Title:** String to Integer (atoi)
- **Problem Link:** https://leetcode.com/problems/string-to-integer-atoi/
- **Source Code (Correct/Accepted):** [leetcode8_String _to_Integer.cpp](https://github.com/SWSekai/11402_CI002/blob/main/After-Class_Practices/Week01_2_LeetCode8/src/leetcode8_String%20_to_Integer.cpp)

## 2. Problem Statement in My Own Words

- **Input:** A string `s`.
- **Expected Output:** A 32-bit signed integer.
- **Rules/Constraints:**
  - 忽略前導空白字元。
  - 可選的正負號（+/-）。
  - 讀取連續數字，直到遇到非數字字元停止。
  - 若數值超出 INT_MIN ~ INT_MAX 範圍，則 clamp 到邊界值。
  - 若無有效數字，回傳 0。
- **Core Task:** 實作類似 C++ 的 `atoi` 函式，將字串轉換為整數。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 需要依序處理空白、正負號、數字字元。
- 必須考慮整數溢位問題，因此使用 `long long` 來暫存數字。

### Final Strategy
- 使用一個索引 `i` 依序掃描字串：
  1. 跳過所有前導空白。
  2. 判斷正負號，記錄符號。
  3. 逐字元讀取數字，用 `num = num * 10 + digit` 方式累加。
  4. 每一步都檢查是否溢位，若溢位直接回傳 INT_MAX 或 INT_MIN。

## 4. Pseudocode

```text
START
1. SET sign = 1, num = 0, i = 0
2. WHILE s[i] == ' ': i++
3. IF s[i] == '+' OR s[i] == '-':
     sign = (s[i] == '-') ? -1 : 1
     i++
4. WHILE s[i] IS digit:
     num = num * 10 + (s[i] - '0')
     IF num * sign >= INT_MAX: RETURN INT_MAX
     IF num * sign <= INT_MIN: RETURN INT_MIN
     i++
5. RETURN (int)(num * sign)
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
class Solution {
public:
    int myAtoi(string s) {
        int sign = 1;
        long long num = 0;
        int i = 0, n = s.length();

        while (i < n && s[i] == ' ') i++;

        if (i < n && (s[i] == '+' || s[i] == '-')) {
            sign = (s[i] == '-') ? -1 : 1;
            i++;
        }
        while (i < n && isdigit(s[i])) {
            num = num * 10 + (s[i] - '0');
            if (num * sign >= INT_MAX) return INT_MAX;
            if (num * sign <= INT_MIN) return INT_MIN;
            i++;
        }
        return (int)(num * sign);
    }
};
```

**Why it works:**
- 使用 `long long` 暫存避免中途溢位，且在每一次迭代便檢查是否超出 int 範圍，確保結果正確 clamp。

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 逐字元掃描、累加數字、邊讀邊檢查溢位 |
| **Edge Cases** | 前導空白、正負號、非數字字元截斷、溢位 clamp |

### Reflection
- 實作 atoi 的關鍵在於依序處理空白、正負號、數字，並在累加過程中持續監控溢位，而非等到全部計算完才檢查。
