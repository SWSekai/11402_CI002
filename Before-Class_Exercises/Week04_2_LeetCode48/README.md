# LeetCode 48 - Rotate Image

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 48
- **Problem Title:** Rotate Image
- **Problem Link:** https://leetcode.com/problems/rotate-image/
- **Source Code (Correct/Accepted):** [leetcode48.cpp](https://github.com/SWSekai/11402_CI002/blob/main/Before-Class_Exercises/Week04_2_LeetCode48/leetcode48.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 一個 `n x n` 的二維矩陣 `matrix`。
- **Expected Output:** 將該矩陣**原地順時針旋轉 90 度**，不回傳新矩陣。
- **Rules/Constraints:** 必須原地修改 (in-place)，不可使用額外的矩陣空間。`1 <= n <= 20`。
- **Core Task:** 將矩陣順時針旋轉 90 度。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 直覺是建立新矩陣填入旋轉後的值，但題目要求 in-place。
- 原地旋轉需要找到元素交換的規律。

### Final Strategy
- 分兩步驟完成：
  1. **轉置矩陣 (Transpose)：** 將 `matrix[i][j]` 與 `matrix[j][i]` 交換（沿主對角線鏡像）。
  2. **水平翻轉 (Reverse each row)：** 將每一行左右反轉。
- **為什麼可行：** 轉置 + 水平翻轉 = 順時針旋轉 90 度。
- **邊界處理：** `n = 1` 時不需任何操作；偶數/奇數矩陣皆適用。

## 4. Pseudocode

```text
START
1. n = matrix.size()
2. FOR i = 0 TO n-1      // Transpose
3.     FOR j = i TO n-1
4.         SWAP matrix[i][j] 與 matrix[j][i]
5. FOR i = 0 TO n-1      // Reverse each row
6.     REVERSE matrix[i]
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        // 轉置
        for (int i = 0; i < n; i++)
            for (int j = i; j < n; j++)
                swap(matrix[i][j], matrix[j][i]);
        // 每行反轉
        for (int i = 0; i < n; i++)
            reverse(matrix[i].begin(), matrix[i].end());
    }
};
```
**Why it works:**
- 轉置將列與行互換，再水平反轉即達成順時針旋轉效果。

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 先轉置再水平翻轉，兩次操作合成旋轉 |
| **Edge Cases** | n = 1 時轉置和反轉皆無影響；不須額外判斷 |

### Reflection
- 將複雜的旋轉分解為兩個熟悉的線性代數操作（轉置 + 反轉），大幅降低思考難度。時間 O(n²)、空間 O(1)。
