# LeetCode 74 - Search a 2D Matrix

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 74
- **Problem Title:** Search a 2D Matrix
- **Problem Link:** https://leetcode.com/problems/search-a-2d-matrix/
- **Source Code (Correct/Accepted):** [leetcode74.cpp](https://github.com/SWSekai/11402_CI002/blob/main/Before-Class_Exercises/Week07_2_LeetCode74/leetcode74.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 一個 m x n 的二維整數矩陣 `matrix`，以及一個整數 `target`。矩陣每行由左至右遞增排序，且每行第一個元素大於前一行最後一個元素。
- **Expected Output:** `true` 如果 `target` 存在於矩陣中，否則 `false`。
- **Rules/Constraints:** 必須在 O(log(m * n)) 時間內完成。
- **Core Task:** 將二維矩陣視為一個已排序的一維陣列，進行二分搜尋。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 直觀做法是用兩層 for 迴圈暴力搜尋，但不符合 O(log(m*n)) 的要求。
- 需要利用矩陣「由左至右、由上至下皆排序」的特性。

### Final Strategy
- **演算法：** 將二維矩陣攤平成邏輯上的一維陣列，使用標準的 Binary Search。
- **為什麼可行：** 由於矩陣嚴格滿足「每一行遞增，且下一行第一個 > 上一行最後一個」，所以可以用 `mid / n` 得到列索引、`mid % n` 得到行索引。
- **邊界處理：** 空矩陣、target 小於最小值或大於最大值。

## 4. Pseudocode

```text
START
1. 令 m = matrix.size(), n = matrix[0].size()
2. 若 m == 0，回傳 false
3. 令 left = 0, right = m * n - 1
4. 當 left <= right 時：
   a. mid = left + (right - left) / 2
   b. row = mid / n, col = mid % n
   c. 若 matrix[row][col] == target，回傳 true
   d. 若 matrix[row][col] < target，left = mid + 1
   e. 否則 right = mid - 1
5. 回傳 false
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if (m == 0) return false;
        int n = matrix[0].size();
        int left = 0, right = m * n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int row = mid / n;
            int col = mid % n;
            if (matrix[row][col] == target) return true;
            else if (matrix[row][col] < target) left = mid + 1;
            else right = mid - 1;
        }
        return false;
    }
};
```
**Why it works:**
- 利用 `mid / n` 和 `mid % n` 將一維索引映射回二維座標，一次 Binary Search 即可完成搜尋。

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 將二維矩陣視為一維排序陣列，用 Binary Search 取代暴力走訪 |
| **Edge Cases** | 先檢查空矩陣；使用 `left + (right-left)/2` 避免整數溢位 |

### Reflection
- 題目的關鍵在於發現矩陣的排序性質足以支援直接的二元搜尋，而不需要先找行再找列。
