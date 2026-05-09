# UVa 10908 - Largest Square

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 10908
- **Problem Title:** Largest Square
- **Problem Link:** [UVa 10908](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=22&page=show_problem&problem=1849)
- **Source Code (Correct/Accepted):** [UVa10908.cpp](https://github.com/SWSekai/11402_CI002/blob/main/On-Site_Examinations/Week04_3_UVa10908/UVa10908.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 第一行為 T (T < 21)。每筆測資的第一行有三個整數 M、N、Q，代表 M×N 的字元矩陣，接下來 M 行每行 N 個字元。再接下來 Q 行每行包含兩個整數 (r, c)，代表查詢的中心點座標。
- **Expected Output:** 對每筆測資，第一行輸出 M、N、Q，接下來 Q 行每行輸出以 (r, c) 為中心、由相同字元構成之最大正方形的邊長。
- **Rules/Constraints:** 正方形中心固定為 (r, c)，且所有邊上的字元必須與中心字元相同。M、N ≤ 100。左上角為 (0, 0)，右下角為 (M-1, N-1)。
- **Core Task:** 對每個查詢點，從中心向外擴展，找出由相同字元構成的最大正方形邊長。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 從中心點 (r, c) 開始，檢查上下左右四個方向是否都與中心字元相同。
- 每次向外擴大一層（邊長 +2），檢查新的四個邊上的所有字元是否一致。

### Final Strategy
- **中心向外擴展法（Centered Expansion）：** 由半徑 len = 0 開始，每次嘗試將半徑加 1，檢查正方形四邊上的所有字元是否都等於中心字元。若全部符合則繼續擴展，否則停止。
- **為什麼可行：** M, N ≤ 100，最多 21 組測資，Q 未明確給定但暴力檢查即可。
- **邊界處理：** 擴展時需確保正方形不超出矩陣邊界；檢查四邊時需遍歷該邊上的每個字元。

## 4. Pseudocode

```text
START
1. 讀入 T
2. FOR 每筆測資:
    a. 讀入 M, N, Q
    b. 讀入 M×N 字元矩陣 grid
    c. 輸出 M, N, Q
    d. FOR 每筆查詢 (r, c):
        center_char = grid[r][c]
        len = 0
        WHILE 可以繼續擴展:
            len++  (新邊長 = 2*len + 1)
            檢查正方形四邊是否皆在邊界內且等於 center_char
            IF 通過: 繼續
            ELSE: BREAK
        輸出 2*(len-1) + 1
END
```

## 5. Correct Code

```cpp
int largestSquare(const vector<string>& grid, int r, int c) {
    int M = grid.size(), N = grid[0].size();
    char center = grid[r][c];
    int len = 0;
    while (true) {
        len++;
        int top = r - len + 1, bottom = r + len - 1;
        int left = c - len + 1, right = c + len - 1;
        if (top < 0 || left < 0 || bottom >= M || right >= N) break;
        bool ok = true;
        for (int i = left; i <= right; i++)
            if (grid[top][i] != center || grid[bottom][i] != center) { ok = false; break; }
        for (int i = top; i <= bottom; i++)
            if (grid[i][left] != center || grid[i][right] != center) { ok = false; break; }
        if (!ok) break;
    }
    return 2 * (len - 1) + 1;
}
```
**Why it works:**
- 以中心為基準，逐步擴大半徑，確保正方形始終中心對稱。
- 每次檢查新擴展的四邊是否全部由相同字元構成。
- 透過邊界檢查避免陣列越界。

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 從中心向外擴展，逐層檢查正方形邊界的字元一致性 |
| **Edge Cases** | 需檢查上下左右邊界，確保正方形不超出矩陣範圍 |

### Reflection
- **對稱擴展：** 中心固定的正方形問題，最直觀的解法就是從中心逐步向外擴展，確保對稱性。
- **邊界檢查的重要性：** 每次擴展前必須先確認新的邊界未超出矩陣，否則會產生執行期錯誤。
- **暴力法的適用性：** 雖然有更高效的演算法（如 DP），但題目限制小，暴力法已足夠且更容易實作。
