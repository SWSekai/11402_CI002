# UVa 12149 - Feynman

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 12149
- **Problem Title:** Feynman
- **Problem Link:** [UVa 12149](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=25&page=show_problem&problem=3301)
- **Source Code (Correct/Accepted):** [UVa12149.cpp](https://github.com/SWSekai/11402_CI002/blob/main/On-Site_Examinations/Week03_3_UVa12149/UVa12149.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 多筆測資，每行一個整數 N (1 <= N <= 100)，以 0 結束。
- **Expected Output:** 對每個 N，輸出 N×N 方格中可以數出多少個正方形（包含所有尺寸的子正方形）。
- **Rules/Constraints:** N 最大到 100。輸入以 0 終止。
- **Core Task:** 計算 N×N 網格中所有可能大小的正方形總數。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 1×1 的正方形有 N² 個，2×2 的有 (N-1)² 個，依此類推。
- 總數為 1² + 2² + ... + N² = N(N+1)(2N+1)/6。
- 可用公式直接計算，也可用迴圈累加。

### Final Strategy
- **逐尺寸計算：** 對每個可能的正方形邊長 i（從1到N），計算可放置的數量為 (N - i + 1)²，全部加總。
- **為什麼可行：** N ≤ 100，O(N²) 或 O(N) 皆可接受。程式使用了雙層迴圈但實質仍是 O(N)（內層迴圈只是算出 row_allow_num = N - i + 1）。
- **邊界處理：** N = 1 時回傳 1。

## 4. Pseudocode

```text
START
1. 重複讀入 N，直到 N = 0
2. IF N == 1: 輸出 1，繼續下一筆
3. ans = 0
4. FOR i = 1 TO N:
    a. 邊長 i 的正方形數量 = (N - i + 1)²
    b. ans += 該數量
5. 輸出 ans
END
```

## 5. Correct Code

```cpp
class Feynman {
public:
    static int count(int num) {
        if (num == 1) return 1;
        int ans = 0;
        for (int i = 1; i <= num; i++) {
            int row_allow_num = num - i + 1;
            ans += row_allow_num * row_allow_num;
        }
        return ans;
    }
};
```
**Why it works:**
- 對每個邊長 i，計算在 N×N 網格中有多少個位置可以放置該正方形。
- 公式 (N - i + 1)² 精確計算了每個尺寸的數量。

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 依正方形尺寸逐項計算，累加所有可能數量 |
| **Edge Cases** | N = 1 時直接回傳 1，避免進入迴圈 |

### Reflection
- **數學公式的力量：** 本題可用公式 O(1) 求解，但迴圈累加已是足夠有效率的解法。
- **問題轉化：** 從「數正方形」到「計算每個尺寸的排列數」，是典型的組合數學思維。
- **雙層迴圈誤區：** 程式的雙層迴圈中內層只是計算數量，實際上可簡化為單層。
