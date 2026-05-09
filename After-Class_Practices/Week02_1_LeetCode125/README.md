# LeetCode 125 - Valid Palindrome

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 125
- **Problem Title:** Valid Palindrome
- **Problem Link:** https://leetcode.com/problems/valid-palindrome/
- **Source Code (Correct/Accepted):** [leetcode125_valid_palindrome.cpp](https://github.com/SWSekai/11402_CI002/blob/main/After-Class_Practices/Week02_1_LeetCode125/leetcode125_valid_palindrome.cpp)

## 2. Problem Statement in My Own Words

- **Input:** A string `s`.
- **Expected Output:** A boolean value (`true` or `false`).
- **Rules/Constraints:**
  - 只考慮字母（a-z, A-Z）和數字（0-9），忽略其他字元（如空格、標點符號）。
  - 字母不分大小寫。
- **Core Task:** 判斷字串是否為迴文（僅考慮 alphanumeric 字元）。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 最直接的方式是先用過濾器取出字母數字，轉小寫後再比對。
- 但這需要額外空間儲存過濾後的字串。

### Final Strategy
- 使用雙指標（left & right）直接在原字串上操作：
  - 左指標從頭向右移動，右指標從尾向左移動。
  - 遇到非字母數字字元則跳過。
  - 比較左右指標指向的字元（轉為小寫後），若不相等則回傳 false。
  - 直到左右指標交錯為止。

## 4. Pseudocode

```text
START
1. SET i = 0, j = s.length() - 1
2. WHILE i < j:
     a. IF s[i] IS NOT alphanumeric: i++, CONTINUE
     b. IF s[j] IS NOT alphanumeric: j--, CONTINUE
     c. IF tolower(s[i]) != tolower(s[j]): RETURN false
     d. i++, j--
3. RETURN true
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
class Solution {
public:
    bool isPalindrome(string s) {
        int i = 0, j = s.length() - 1;
        while (i < j) {
            if (!isalnum(s[i])) { i++; continue; }
            if (!isalnum(s[j])) { j--; continue; }
            if (tolower(s[i]) != tolower(s[j])) return false;
            i++; j--;
        }
        return true;
    }
};
```

**Why it works:**
- 雙指標可在 O(n) 時間內完成，且只使用 O(1) 額外空間，無需過濾後的新字串。

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 雙指標跳過非字母數字，直接比較原字串的前後字元 |
| **Edge Cases** | 空字串、只有非字母數字的字串、大小寫混合、數字與字母混合 |

### Reflection
- 雙指標技巧非常適合處理這種需要忽略特定字元的迴文判斷問題，不需要額外空間就能達到最佳效率。
