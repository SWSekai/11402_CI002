# LeetCode 231 - Power of Two

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 231
- **Problem Title:** Power of Two
- **Problem Link:** https://leetcode.com/problems/power-of-two/
- **Source Code (Correct/Accepted):** [leetcode231.cpp](https://github.com/SWSekai/11402_CI002/blob/main/Before-Class_Exercises/Week03_1_LeetCode231/src/leetcode231.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 一個整數 `n`（可能為負數或零）。
- **Expected Output:** 若 `n` 是 2 的冪次方則回傳 `true`，否則回傳 `false`。
- **Rules/Constraints:** `-2^31 <= n <= 2^31 - 1`。不可以使用內建函式。
- **Core Task:** 判斷給定整數是否為 2 的某次方 (即 `n = 2^k`，其中 `k >= 0`)。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 直覺想到用迴圈不斷除以 2，檢查是否能被 2 整除直到 1。

### Final Strategy
- 在 `n >= 1` 的條件下反覆除以 2；若中途遇到奇數（且不等於 1）則直接回傳 `false`；若最終能降到 `1` 則回傳 `true`。
- **為什麼可行：** 2 的冪次方的質因數只有 2，因此不斷除以 2 最後必定得到 1。
- **邊界處理：** `n <= 0` 時不進入迴圈，直接回傳 `false`；`n = 1` 是特殊情況（2^0），直接回傳 `true`。

## 4. Pseudocode

```text
START
1. WHILE n >= 1
2.     IF n == 1 THEN RETURN true
3.     IF n % 2 == 1 THEN RETURN false (奇數且非 1)
4.     n = n / 2
5. RETURN false (n <= 0)
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
class Solution {
public:
    bool isPowerOfTwo(int n) {
        while(n >= 1){
            if(n == 1) return true;
            if(n%2 == 1) return false;
            n /= 2;
        }
        return false;
    }
};
```
**Why it works:**
- 反覆除以 2，利用 2 的冪次方必定能被 2 整除的特性，最終收斂至 1。

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 使用 while 迴圈重複整除 2，檢查餘數 |
| **Edge Cases** | 負數與 0 不進入迴圈直接 false；n = 1 為 true |

### Reflection
- 此解法時間複雜度 O(log n)，空間 O(1)。另有位元運算解法 (`n > 0 && (n & (n-1)) == 0`) 可達 O(1)，但迴圈法更直觀易懂。
