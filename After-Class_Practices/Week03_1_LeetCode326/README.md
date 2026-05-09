# LeetCode 326 - Power of Three

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 326
- **Problem Title:** Power of Three
- **Problem Link:** https://leetcode.com/problems/power-of-three/
- **Source Code (Correct/Accepted):** [leetcode326.cpp](https://github.com/SWSekai/11402_CI002/blob/main/After-Class_Practices/Week03_1_LeetCode326/leetcode326.cpp)

## 2. Problem Statement in My Own Words

- **Input:** An integer `n`.
- **Expected Output:** A boolean value (`true` or `false`).
- **Rules/Constraints:**
  - 判斷 `n` 是否為 3 的冪次（3^k）。
  - `n` 可能為負數或零，這些情況皆回傳 `false`。
- **Core Task:** 判斷給定的整數是否為 3 的某個正整數次方。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 使用迴圈不斷除以 3，若最後得到 1 則為 true，否則 false。
- 需先排除 n <= 0 的情況。

### Final Strategy
- 迭代法：若 n <= 0 直接回傳 false；否則持續將 n 除以 3，直到 n 無法被 3 整除。
- 最後檢查 n 是否等於 1，若等於 1 則表示原數為 3 的冪次。

## 4. Pseudocode

```text
START
1. IF n <= 0: RETURN false
2. WHILE n % 3 == 0:
     n = n / 3
3. RETURN n == 1
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
class Solution {
public:
    bool isPowerOfThree(int n) {
        if (n <= 0) return false;
        while (n % 3 == 0) n /= 3;
        return n == 1;
    }
};
```

**Why it works:**
- 所有 3 的冪次都能被 3 連續整除直到剩下 1，非 3 的冪次則會在中途被除盡或得到非 1 的結果。

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 透過迭代除以 3 的方式逐步縮小問題規模 |
| **Edge Cases** | n <= 0 直接回傳 false；n = 1 時迴圈不執行，直接回傳 true |

### Reflection
- Power of Three 問題看似簡單，但可以延伸出多種解法（迭代、遞迴、數學公式），迭代法是最直觀且效率良好的做法。
