# LeetCode 35 - Search Insert Position

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 35
- **Problem Title:** Search Insert Position
- **Problem Link:** https://leetcode.com/problems/search-insert-position/
- **Source Code (Correct/Accepted):** [leetcode35.cpp](https://github.com/SWSekai/11402_CI002/blob/main/After-Class_Practices/Week07_1_LeetCode35/leetcode35.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 一個已排序（遞增）的整數陣列 `nums` 和一個目標值 `target`。
- **Expected Output:** 回傳 target 在 nums 中的索引位置；如果 target 不存在，回傳 target 應被插入的位置（保持排序順序）。
- **Rules/Constraints:** `1 <= nums.length <= 10^4`，`-10^4 <= nums[i], target <= 10^4`，nums 為嚴格遞增排序（無重複）。
- **Core Task:** 實作搜尋插入位置的函數，要求時間複雜度 O(log n)。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 因為要求 O(log n) 的時間複雜度，必須使用 Binary Search（二分搜尋）。
- 需要同時處理「找到 target」和「找不到 target 時回傳插入位置」兩種情況。

### Final Strategy
- 使用標準的二分搜尋法，在 left <= right 的條件下進行搜尋。
- 當 nums[mid] == target 時，直接回傳 mid。
- 當 nums[mid] < target 時，left = mid + 1。
- 當 nums[mid] > target 時，right = mid - 1。
- 當迴圈結束仍未找到時，left 就是 target 應該被插入的位置。
- 時間複雜度 O(log n)，空間複雜度 O(1)。

### Edge Cases Handled
- target 小於所有元素：left 保持為 0，直接回傳 0。
- target 大於所有元素：left 最終為 nums.length，即插入在最後。
- target 存在於陣列中：直接回傳對應索引。

## 4. Pseudocode

```text
START
1. left = 0, right = nums.size() - 1
2. WHILE left <= right:
    a. mid = left + (right - left) / 2
    b. IF nums[mid] == target: 回傳 mid
    c. IF nums[mid] < target: left = mid + 1
    d. ELSE: right = mid - 1
3. 回傳 left
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
int searchInsert(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return left;
}
```

**Why it works:**
- 二分搜尋結束時，left 指向第一個大於等於 target 的位置，這正是 target 應該存在（或插入）的位置。這個性質由二分搜尋的不變式保證。

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 標準二分搜尋，搜尋失敗時 left 即為插入位置 |
| **Edge Cases** | left 和 right 的邊界更新保證了搜尋結束後 left 是正確的插入索引 |

### Reflection
- 本題是二分搜尋的經典變形，關鍵在於理解當搜尋失敗時，left 指針指向的就是第一個大於等於 target 的位置，這正是插入位置。
- 使用 `left + (right - left) / 2` 而非 `(left + right) / 2` 可以避免整數溢位。
