# LeetCode 378 - Kth Smallest Element in a Sorted Matrix

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 378
- **Problem Title:** Kth Smallest Element in a Sorted Matrix
- **Problem Link:** https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/
- **Source Code (Correct/Accepted):** [leetcode378.cpp](https://github.com/SWSekai/11402_CI002/blob/main/After-Class_Practices/Week06_2_LeetCode378/leetcode378.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 一個 n x n 的整數矩陣 `matrix`，其中每一行和每一列都按照遞增順序排序，以及一個整數 `k`。
- **Expected Output:** 回傳矩陣中第 k 小的元素（1-indexed）。
- **Rules/Constraints:** `n == matrix.length == matrix[i].length`，`1 <= n <= 300`，`-10^9 <= matrix[i][j] <= 10^9`，保證 `1 <= k <= n^2`。
- **Core Task:** 在行和列都排序的矩陣中找到第 k 小的元素。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 最簡單的方法是將所有元素放入一個陣列後排序，但時間複雜度 O(n² log n) 不是最優。
- 可以利用矩陣行與列都已排序的性質來做更高效的搜尋。

### Final Strategy
- 使用 Binary Search（二分搜尋）配合 Counting 函數來找出第 k 小的元素。
- 在矩陣的最小值 `matrix[0][0]` 和最大值 `matrix[n-1][n-1]` 之間進行二分搜尋。
- 對於每個猜測的 mid 值，計算矩陣中小於等於 mid 的元素個數，如果個數 >= k，則縮小右邊界，否則縮小左邊界。
- 計算個數時，可以利用矩陣排序的特性，從左下角開始向右上遍歷，時間複雜度 O(n)。
- 整體時間複雜度 O(n log(max - min))，空間複雜度 O(1)。

### Edge Cases Handled
- k = 1：回傳最小值。
- k = n²：回傳最大值。
- 矩陣中有重複元素：二分搜尋可以正確處理。

## 4. Pseudocode

```text
START
1. n = matrix.size()
2. left = matrix[0][0], right = matrix[n-1][n-1]
3. WHILE left < right:
    a. mid = left + (right - left) / 2
    b. count = 計算矩陣中 <= mid 的元素個數
       - 從左下角 (n-1, 0) 開始
       - 若 matrix[i][j] <= mid，則該行 i 以上都 <= mid，count += i+1，j++
       - 否則 i--
    c. IF count >= k: right = mid
       ELSE: left = mid + 1
4. 回傳 left
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
int kthSmallest(vector<vector<int>>& matrix, int k) {
    int n = matrix.size();
    int left = matrix[0][0], right = matrix[n-1][n-1];
    while (left < right) {
        int mid = left + (right - left) / 2;
        int count = 0, i = n - 1, j = 0;
        while (i >= 0 && j < n) {
            if (matrix[i][j] <= mid) {
                count += i + 1;
                j++;
            } else {
                i--;
            }
        }
        if (count >= k) right = mid;
        else left = mid + 1;
    }
    return left;
}
```

**Why it works:**
- 二分搜尋在「值域」而非「索引」上進行，配合矩陣的行列排序性質，可以在 O(n) 時間內統計小於等於某值的元素個數，從而在 O(n log range) 時間內找到第 k 小的元素。

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 在值域上進行二分搜尋而非在索引上，利用矩陣排序性質加速計數 |
| **Edge Cases** | 二分邊界 left/right 的更新方式確保不會陷入無窮迴圈 |

### Reflection
- 本題的核心技巧是「在值域上二分搜尋」，當直接尋找第 k 個元素困難時，可以轉換為「給定一個值，判斷有多少元素 ≤ 它」，這是一個典型的「通過驗證來搜尋」的策略。
- 從左下角開始遍歷是利用了矩陣行列都排序的特性，每次可以跳過一整行或一整列，將計數的時間複雜度降到 O(n)。
