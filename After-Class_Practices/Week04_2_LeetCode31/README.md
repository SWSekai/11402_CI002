# LeetCode 31 - Next Permutation

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 31
- **Problem Title:** Next Permutation
- **Problem Link:** https://leetcode.com/problems/next-permutation/
- **Source Code (Correct/Accepted):** [leetcode31.cpp](https://github.com/SWSekai/11402_CI002/blob/main/After-Class_Practices/Week04_2_LeetCode31/src/leetcode31.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 一個整數陣列 `nums`，代表一個排列
- **Expected Output:** 將 `nums` 修改為下一個字典序更大的排列，若已是最後一個則改為最小的排列（升序）
- **Rules/Constraints:** 必須 in-place 修改，不能使用額外陣列
- **Core Task:** 實作字典序的下一個排列演算法

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 字典序排列的規律：從右往左找第一個遞增的位置
- 跟「下一個更大的數字」概念相似

### Final Strategy
- 從右往左找到第一個 `nums[i] < nums[i+1]` 的位置 i（從 i 右側的序列是降序的）
- 再從右往左找到第一個大於 `nums[i]` 的 `nums[j]`，交換兩者
- 將 i 右側的序列反轉（降序變升序，即最小排列）
- 若找不到 i（整個序列降序），直接反轉整個陣列

### Edge Cases Handled
- 陣列長度為 1：直接回傳
- 已是最大排列：反轉整個陣列回到最小排列

## 4. Pseudocode

```text
START
1. i = n - 2
2. While i >= 0 and nums[i] >= nums[i+1]: i--
3. If i >= 0:
     j = n - 1
     While nums[j] <= nums[i]: j--
     Swap nums[i], nums[j]
4. Reverse nums[i+1...n-1]
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int i = n - 2;
        while (i >= 0 && nums[i] >= nums[i + 1]) i--;
        if (i >= 0) {
            int j = n - 1;
            while (nums[j] <= nums[i]) j--;
            swap(nums[i], nums[j]);
        }
        reverse(nums.begin() + i + 1, nums.end());
    }
};
```
**Why it works:**
- 找到第一個破壞降序的位置 i，其右側是降序（已是最大排列）
- 交換 i 與右側最小的大數，然後將右側反轉為升序（最小排列）

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 暴力法用 next_permutation 或遞迴；標準演算法分三步：找 i、交換、反轉 |
| **Edge Cases** | 需處理整個陣列降序（已是最大排列）的情況，直接反轉 |

### Reflection
- 理解字典序排列的數學規律是關鍵，避免使用暴力遞迴
- 這種「從右往左」的掃描模式在許多排列問題中都會用到
