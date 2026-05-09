# LeetCode 704 - Binary Search

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 704
- **Problem Title:** Binary Search
- **Problem Link:** https://leetcode.com/problems/binary-search/
- **Source Code (Correct/Accepted):** [leetcode704.cpp](https://github.com/SWSekai/11402_CI002/blob/main/Before-Class_Exercises/Week07_1_LeetCode704/leetcode704.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 一個已升序排列的整數陣列 `nums` 以及一個目標值 `target`
- **Expected Output:** `target` 在陣列中的索引；若不存在則回傳 -1
- **Rules/Constraints:** 必須實作 O(log n) 時間複雜度的演算法
- **Core Task:** 在有序陣列中以二分搜尋法快速定位目標值

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 有序陣列中搜尋，最直觀的方法是線性搜尋 O(n)，但題目要求 O(log n)，必須使用二分搜尋
- 二分搜尋的關鍵在於正確處理邊界（left 與 right 的開閉區間）

### Final Strategy
- 使用雙指針 `left` 和 `right` 分別指向陣列頭尾
- 每次取中間位置 `mid = left + (right - left) / 2`（避免溢位）
- 比較 `nums[mid]` 與 `target`：
  - 若相等則直接回傳 `mid`
  - 若 `nums[mid] < target` 則搜尋右半邊
  - 若 `nums[mid] > target` 則搜尋左半邊
- 若迴圈結束仍未找到則回傳 -1

### Edge Cases Handled
- 陣列為空 → 直接回傳 -1
- 目標值不在陣列範圍內 → 迴圈自然結束後回傳 -1
- 只有一個元素 → left == right 仍需進入迴圈判斷

## 4. Pseudocode

```text
START
1. left = 0, right = nums.size() - 1
2. while left <= right:
3.     mid = left + (right - left) / 2
4.     if nums[mid] == target: return mid
5.     if nums[mid] < target: left = mid + 1
6.     else: right = mid - 1
7. return -1
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) return mid;
            else if (nums[mid] < target) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }
};
```
**Why it works:**
- 每次將搜尋範圍縮小一半，確保 O(log n) 時間複雜度；`left + (right-left)/2` 避免 `(left+right)/2` 可能的整數溢位

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 經典二分搜尋模板，使用閉區間 `[left, right]`，條件為 `left <= right` |
| **Edge Cases** | 空陣列時 `right = -1`，迴圈不執行直接回傳 -1 |

### Reflection
- 二分搜尋是演算法基礎中的基礎，核心在於邊界條件的統一；熟練一套模板（如閉區間寫法）後即可套用至各種變形題
