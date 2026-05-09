# LeetCode 414 - Third Maximum Number

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 414
- **Problem Title:** Third Maximum Number
- **Problem Link:** https://leetcode.com/problems/third-maximum-number/
- **Source Code (Correct/Accepted):** [leetcode414.cpp](https://github.com/SWSekai/11402_CI002/blob/main/Before-Class_Exercises/Week06_1_LeetCode414/leetcode414.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 一個整數陣列 `nums`（可能包含重複值）
- **Expected Output:** 陣列中第三大的不相同數字；若第三大的不存在，則回傳最大的數字
- **Rules/Constraints:** 必須考慮 distinct 值；時間複雜度 O(n)
- **Core Task:** 在一次遍歷中找出前三大的不重複元素

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 最直覺的做法是先排序再去重取第三個，但排序的時間複雜度為 O(n log n)，不符合題目對 O(n) 的要求
- 使用 set 或 priority queue 也可以，但空間開銷較大

### Final Strategy
- 使用三個 `long` 變數 `first`、`second`、`third` 初始化為 `LONG_MIN`，分別代表第一大、第二大、第三大的值
- 遍歷陣列，根據當前 `num` 與三個變數的大小關係逐一更新
- 因為陣列元素可能包含 `INT_MIN`，所以使用 `LONG_MIN` 作為初始值來避免混淆
- 最後檢查 `third` 是否仍為 `LONG_MIN`（或 `second` 為 `LONG_MIN`），若是則表示不存在第三大，回傳 `first`

### Edge Cases Handled
- 陣列中只有一個或兩個不重複數字 → 回傳最大值
- 陣列元素包含 `INT_MIN` → 用 `LONG_MIN` 區分有效值
- 重複元素不影響計算（透過嚴格的大小判斷 `num > first`、`num < first && num > second` 等）

## 4. Pseudocode

```text
START
1. first = second = third = LONG_MIN
2. for each num in nums:
     if num > first:
         third = second, second = first, first = num
     else if num < first && num > second:
         third = second, second = num
     else if num > third && num < second:
         third = num
3. if third == LONG_MIN or second == LONG_MIN:
       return first
   else
       return third
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        long first = LONG_MIN, second = LONG_MIN, third = LONG_MIN;
        for(int num : nums) {
            if(num > first) {
                third = second;
                second = first;
                first = num;
            }
            else if(num < first && num > second) {
                third = second;
                second = num;
            }
            else if(num > third && num < second) {
                third = num;
            }
        }
        return (third == LONG_MIN || second == LONG_MIN) ? first : third;
    }
};
```
**Why it works:**
- 只用 O(1) 額外空間，在一次線性掃描中動態維護前三大的值，並用 `LONG_MIN` 避開 `INT_MIN` 的干擾

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 用三個變數模擬有序鏈表，每次插入新值時將後面的值向後移位 |
| **Edge Cases** | 使用 `LONG_MIN` 而非 `INT_MIN` 作為初始值，避免元素恰為 `INT_MIN` 時誤判為未賦值 |

### Reflection
- 處理 Top-k 問題時，若 k 很小（如 k=3），用變數維護比用 heap 或排序更高效且簡潔；關鍵在於初始值的選取要避開所有合法輸入值
