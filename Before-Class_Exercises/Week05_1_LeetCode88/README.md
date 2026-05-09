# LeetCode 88 - Merge Sorted Array

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 88
- **Problem Title:** Merge Sorted Array
- **Problem Link:** https://leetcode.com/problems/merge-sorted-array/
- **Source Code (Correct/Accepted):** [leetcode88.cpp](https://github.com/SWSekai/11402_CI002/blob/main/Before-Class_Exercises/Week05_1_LeetCode88/leetcode88.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 兩個已排序的整數陣列 `nums1` 和 `nums2`，以及它們的實際元素數量 `m` 和 `n`。`nums1` 的總長度為 `m + n`，尾端預留 `n` 個空格（填 0）。
- **Expected Output:** 將 `nums2` 合併到 `nums1` 中，使 `nums1` 成為一個已排序的陣列（in-place）。
- **Rules/Constraints:** 必須原地修改 `nums1`，不可回傳新陣列。
- **Core Task:** 將兩個已排序陣列合併為單一排序陣列。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 從前往後合併需要移動大量元素，效率低。
- 若從後往前填，則不需要額外空間。

### Final Strategy
- 使用**三指標從後往前合併**。
- 設 `i = m - 1`（指向 nums1 有效尾端）、`j = n - 1`（指向 nums2 尾端）、`k = m + n - 1`（指向 nums1 總尾端）。
- 比較 `nums1[i]` 與 `nums2[j]`，將較大者放入 `nums1[k]`，並移動對應指標。
- 若 `nums2` 還有剩餘元素，直接複製到 `nums1` 前端。
- **為什麼可行：** 從後往前填不會覆蓋到尚未處理的 `nums1` 有效元素，因為前方永遠有足夠空間。
- **邊界處理：** `m = 0` 時直接複製 `nums2`；`n = 0` 時不需操作。

## 4. Pseudocode

```text
START
1. i = m - 1, j = n - 1, k = m + n - 1
2. WHILE i >= 0 AND j >= 0
3.     IF nums1[i] > nums2[j]
4.         nums1[k--] = nums1[i--]
5.     ELSE
6.         nums1[k--] = nums2[j--]
7. WHILE j >= 0                    // 處理 nums2 剩餘元素
8.     nums1[k--] = nums2[j--]
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1, j = n - 1, k = m + n - 1;
        while (i >= 0 && j >= 0) {
            if (nums1[i] > nums2[j])
                nums1[k--] = nums1[i--];
            else
                nums1[k--] = nums2[j--];
        }
        while (j >= 0)
            nums1[k--] = nums2[j--];
    }
};
```
**Why it works:**
- 從後往前填入最大值，避免覆蓋尚未處理的 `nums1` 元素，達成 in-place 合併。

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 三指標從後往前合併，每次取兩陣列當前最大元素填入尾端 |
| **Edge Cases** | `m = 0` 直接複製 nums2；`n = 0` 則跳過第二個 while 迴圈 |

### Reflection
- 從後往前操作是解決陣列 in-place 合併問題的經典技巧，避免 O(n) 的搬移開銷。時間 O(m + n)、空間 O(1)。
