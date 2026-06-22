# LeetCode 6 - Zigzag Conversion

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 6
- **Problem Title:** Zigzag Conversion
- **Problem Link:** https://leetcode.com/problems/zigzag-conversion/
- **Source Code (Correct/Accepted):** [leetcode6_zigzag_conversion.cpp](https://github.com/SWSekai/11402_CI002/blob/main/After-Class_Practices/Week02_2_LeetCode6/src/leetcode6_zigzag_conversion.cpp)

## 2. Problem Statement in My Own Words

- **Input:** A string `s` and an integer `numRows`.
- **Expected Output:** A string read row by row after writing in a zigzag pattern.
- **Rules/Constraints:**
  - 將字串以鋸齒形（zigzag）方式排列，再依橫列讀取。
  - 若 numRows = 1，直接回傳原字串。
- **Core Task:** 模擬鋸齒形排列後，按照列順序重新組合字串。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 直觀做法是建立一個二維陣列模擬 zigzag 填入，再逐列讀取。
- 但空間複雜度較高。

### Final Strategy
- 數學規律法：觀察 zigzag 排列後，每一列兩相鄰字元之間的間隔存在數學規律。
  - 第一列和最後一列：間隔固定為 `diff = 2 * numRows - 2`。
  - 中間列：交替出現兩種間隔 `row * 2` 和 `diff - row * 2`。
- 用一個 flag 切換兩種間隔，依序跳躍讀取字元。

## 4. Pseudocode

```text
START
1. IF numRows == 1: RETURN s
2. SET diff = numRows * 2 - 2
3. SET ans = ""
4. FOR row = 0 TO numRows - 1:
     SET flag = false
     FOR j = row; j < s.length(); flag = !flag:
       ans += s[j]
       IF row == 0 OR row == numRows - 1:
         j += diff
       ELSE IF flag:
         j += row * 2
       ELSE:
         j += diff - row * 2
5. RETURN ans
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) return s;
        int diff = numRows * 2 - 2;
        string ans = "";
        for (int row = 0; row < numRows; row++) {
            bool flag = false;
            for (int j = row; j < s.length(); flag = !flag) {
                ans += s[j];
                if (row == 0 || row == numRows - 1)
                    j += diff;
                else if (flag)
                    j += row * 2;
                else
                    j += diff - row * 2;
            }
        }
        return ans;
    }
};
```

**Why it works:**
- 透過數學規律直接計算每一列的下一個字元位置，無需額外的二維陣列，空間複雜度 O(1)。

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 根據數學間隔公式直接跳躍取值，而非模擬填入二維陣列 |
| **Edge Cases** | numRows = 1 時直接回傳；字串長度不足一行時的處理 |

### Reflection
- zigzag 轉換的關鍵在於發現列與列之間的間隔規律，將模擬問題轉化為數學計算，大幅降低空間複雜度。
