# LeetCode 33 - Search in Rotated Sorted Array

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 33
- **Problem Title:** Search in Rotated Sorted Array
- **Problem Link:** https://leetcode.com/problems/search-in-rotated-sorted-array/
- **Source Code (Correct/Accepted):** [leetcode33.cpp](https://github.com/SWSekai/11402_CI002/blob/main/After-Class_Practices/Week07_2_LeetCode33/leetcode33.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 一個在某个未知 pivot 上被旋轉過的有序（遞增）整數陣列 `nums`，以及一個目標值 `target`。旋轉後陣列為遞增序列的循環移位。
- **Expected Output:** 回傳 target 在 nums 中的索引位置；若不存在則回傳 -1。
- **Rules/Constraints:** `1 <= nums.length <= 5000`，`-10^4 <= nums[i], target <= 10^4`，陣列中無重複元素，要求時間複雜度 O(log n)。
- **Core Task:** 在旋轉後的排序陣列中使用 O(log n) 時間搜尋目標值。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 直接線性搜尋需要 O(n)，不符合題目要求的 O(log n)。
- 雖然陣列被旋轉了，但可以用一次二分搜尋來解決，關鍵在於判斷 mid 落在哪個有序區間。

### Final Strategy
- 使用修改過的二分搜尋法。每次取 mid 後，先判斷 left 到 mid 是否為有序區段。
- `nums[left] <= nums[mid]` 表示左半邊是有序的：
  - 若 target 在 `[nums[left], nums[mid])` 區間內，則搜尋左半邊。
  - 否則搜尋右半邊。
- 反之（左半邊無序，則右半邊必然有序）：
  - 若 target 在 `(nums[mid], nums[right]]` 區間內，則搜尋右半邊。
  - 否則搜尋左半邊。
- 時間複雜度 O(log n)，空間複雜度 O(1)。

### Edge Cases Handled
- 陣列未旋轉（即正常排序）：二分搜尋仍能正確工作。
- 陣列長度為 1：mid 等於 left 和 right，需要正確判斷。
- target 不存在陣列中：二分搜尋結束回傳 -1。
- 旋轉點在陣列中間或邊界：都能正確處理。

## 4. Pseudocode

```text
START
1. left = 0, right = nums.size() - 1
2. WHILE left <= right:
    a. mid = left + (right - left) / 2
    b. IF nums[mid] == target: 回傳 mid
    c. IF nums[left] <= nums[mid]:  // 左半邊有序
        i. IF nums[left] <= target && target < nums[mid]:
            right = mid - 1
        ii. ELSE: left = mid + 1
    d. ELSE:  // 右半邊有序
        i. IF nums[mid] < target && target <= nums[right]:
            left = mid + 1
        ii. ELSE: right = mid - 1
3. 回傳 -1
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
int search(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return mid;
        if (nums[left] <= nums[mid]) {
            if (nums[left] <= target && target < nums[mid])
                right = mid - 1;
            else
                left = mid + 1;
        } else {
            if (nums[mid] < target && target <= nums[right])
                left = mid + 1;
            else
                right = mid - 1;
        }
    }
    return -1;
}
```

**Why it works:**
- 利用旋轉陣列的性質：不管 mid 落在哪裡，至少有一半（左半或右半）是完全有序的，透過判斷 target 是否在有序區間內來決定搜尋方向。

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 在二分搜尋的基礎上增加有序區間判斷，利用 `nums[left] <= nums[mid]` 來決定哪一半是連續遞增的 |
| **Edge Cases** | 使用 `<=` 判斷有序區間（因為當 mid == left 時左半只有一個元素也算有序） |

### Reflection
- 本題的核心是理解「旋轉排序陣列中至少有一半是有序的」這個性質，透過判斷 target 是否在有序區間內來縮小搜尋範圍，從而保持 O(log n) 的時間複雜度。
- 條件判斷中的邊界處理要特別小心，尤其是 `<=` 和 `<` 的使用，以及當陣列長度為奇數或偶數時的影響。
