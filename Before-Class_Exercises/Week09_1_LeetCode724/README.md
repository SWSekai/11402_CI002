# LeetCode 724 - Find Pivot Index

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 724
- **Problem Title:** Find Pivot Index
- **Problem Link:** https://leetcode.com/problems/find-pivot-index/
- **Source Code (Correct/Accepted):** [leetcode724.cpp](https://github.com/SWSekai/11402_CI002/blob/main/Before-Class_Exercises/Week09_1_LeetCode724/leetcode724.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 一個整數陣列 `nums`。
- **Expected Output:** 傳回「樞紐索引」(pivot index)，該索引左側所有元素總和等於右側所有元素總和。若不存在則回傳 -1。
- **Rules/Constraints:** 樞紐索引本身不計入左右兩側總和；若索引為 0，左側總和視為 0；若索引為最後一個，右側總和視為 0。
- **Core Task:** 找出一個位置使得 `sum(nums[0..i-1]) == sum(nums[i+1..n-1])`。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 暴力解：對每個 i 分別計算左右總和，時間 O(n²) 太慢。
- 需要 O(n) 時間、O(1) 額外空間的方法。

### Final Strategy
- **演算法：** 前綴和 (Prefix Sum)
- **步驟：**
  1. 先計算整個陣列的總和 `totalSum`。
  2. 從左到右遍歷，維護 `leftSum`。
  3. 對每個 i，右側總和 = `totalSum - leftSum - nums[i]`。
  4. 若 `leftSum == rightSum` 則回傳 i。
- **為什麼可行：** 只需一次遍歷即可比對左右總和，不需額外陣列。
- **邊界處理：** i = 0 時 leftSum = 0；i = n-1 時 rightSum = 0。

## 4. Pseudocode

```text
START
1. 計算 totalSum = sum(nums)
2. leftSum = 0
3. 遍歷 i 從 0 到 n-1：
   a. rightSum = totalSum - leftSum - nums[i]
   b. 若 leftSum == rightSum，回傳 i
   c. leftSum += nums[i]
4. 回傳 -1
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int totalSum = 0;
        for (int num : nums) totalSum += num;
        int leftSum = 0;
        for (int i = 0; i < nums.size(); i++) {
            int rightSum = totalSum - leftSum - nums[i];
            if (leftSum == rightSum) return i;
            leftSum += nums[i];
        }
        return -1;
    }
};
```
**Why it works:**
- 利用 `totalSum - leftSum - nums[i]` 即時計算右側總和，避免雙重迴圈。

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 先算總和，再以 leftSum 動態推算 rightSum，O(n) 一次走訪 |
| **Edge Cases** | leftSum 初始為 0 處理了 pivot 在 index 0 的情況 |

### Reflection
- 此題是典型的前綴和應用。關鍵在於「右側總和 = 總和 - 左側總和 - 當前元素」這個轉換，將雙指針問題化簡為單次遍歷。
