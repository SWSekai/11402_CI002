# LeetCode 169 - Majority Element

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 169
- **Problem Title:** Majority Element
- **Problem Link:** https://leetcode.com/problems/majority-element/
- **Source Code (Correct/Accepted):** [leetcode169.cpp](https://github.com/SWSekai/11402_CI002/blob/main/Before-Class_Exercises/Week04_1_LeetCode169/leetcode169.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 一個整數陣列 `nums`，長度為 `n`。
- **Expected Output:** 回傳該陣列的**多數元素**（出現次數超過 `⌊n / 2⌋` 的元素）。
- **Rules/Constraints:** 保證陣列中一定存在多數元素。不可使用額外 O(n) 空間（進階要求）。
- **Core Task:** 找出出現次數超過半數的元素。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 可以用 Hash Map 統計每個元素的出現次數，但需要 O(n) 額外空間。
- 排序後取中間元素也可以，但時間複雜度 O(n log n)。

### Final Strategy
- 使用 **Boyer-Moore 投票演算法**（Boyer-Moore Voting Algorithm）。
- **核心概念：** 將不同的數字兩兩抵消，最後留下來的就是多數元素。
- 遍歷陣列，維護一個 `candidate` 和 `count`。遇到相同數字 `count++`，不同則 `count--`；當 `count == 0` 時更換 `candidate`。
- **為什麼可行：** 因為多數元素出現次數超過一半，抵消後必定剩下該元素。
- **邊界處理：** 題目保證一定存在多數元素，因此最後的 `candidate` 即為答案。

## 4. Pseudocode

```text
START
1. candidate = nums[0], count = 1
2. FOR i = 1 TO n-1
3.     IF count == 0 THEN candidate = nums[i], count = 1
4.     ELSE IF nums[i] == candidate THEN count++
5.     ELSE count--
6. RETURN candidate
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int candidate = nums[0], count = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (count == 0) {
                candidate = nums[i];
                count = 1;
            } else if (nums[i] == candidate) {
                count++;
            } else {
                count--;
            }
        }
        return candidate;
    }
};
```
**Why it works:**
- 利用抵消原理，多數元素因為數量過半，必定會留在最後成為 `candidate`。

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | Boyer-Moore 投票法，用 count 抵消不同元素 |
| **Edge Cases** | 陣列長度為 1 時直接回唯一元素；題目保證一定有解 |

### Reflection
- 此演算法時間 O(n)、空間 O(1)，是解決 Majority Element 問題最優雅的方法。關鍵在於理解「多數元素出現次數 > 一半」這個數學保證。
