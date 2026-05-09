# LeetCode 9 - Palindrome Number

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 9
- **Problem Title:** Palindrome Number
- **Problem Link:** https://leetcode.com/problems/palindrome-number/
- **Source Code (Correct/Accepted):** [leetcode9_Palindrome Number.cpp](https://github.com/SWSekai/11402_CI002/blob/main/After-Class_Practices/Week01_1_LeetCode9/leetcode9_Palindrome%20Number.cpp)

## 2. Problem Statement in My Own Words

- **Input:** An integer `x`.
- **Expected Output:** A boolean value (`true` or `false`).
- **Rules/Constraints:**
  - Negative numbers are not palindromes.
  - If the last digit is 0, the number cannot be a palindrome unless the number itself is 0.
- **Core Task:** Determine whether the given integer reads the same forwards and backwards.

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 直觀的解法是將整數轉為字串，再用雙指標比對前後字元是否相同。
- 但題目的進階要求建議不要使用字串轉換，因此需要純數學方式。

### Final Strategy
- 使用「反轉一半數字」的技巧：每次取出原數字的末位數，加到反轉數字的末尾，直到反轉數字 >= 原數字。
- 優點是只需反轉一半，避免整個反轉可能導致的整數溢位。
- 處理奇數位數時，反轉數字會多一位，只要去掉最後一位再比較即可。

## 4. Pseudocode

```text
START
1. IF x < 0 OR (x % 10 == 0 AND x != 0) THEN return false
2. SET reverb_num = 0
3. WHILE x > reverb_num:
     a. reverb_num = reverb_num * 10 + x % 10
     b. x = x / 10
4. RETURN x == reverb_num OR x == reverb_num / 10
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
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
```

**Why it works:**
- 透過反轉一半數字，避免整個反轉造成的溢位問題，同時保有 O(log n) 的時間複雜度。

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 只反轉後半段數字並與前半段比較，而非轉字串或反轉整個整數 |
| **Edge Cases** | 負數直接回傳 false；末位為 0 的數（除 0 本身）也直接回傳 false |

### Reflection
- 學到「反轉一半」的技巧，既能避免溢位又能達到 O(log n) 的時間複雜度，是處理迴文數問題的最佳解。
