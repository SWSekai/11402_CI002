# UVa 100 - The 3n + 1 Problem

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 100
- **Problem Title:** The 3n + 1 Problem
- **Problem Link:** [UVa 100](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=36)
- **Source Code (Correct/Accepted):** [Uva100.cpp](https://github.com/SWSekai/11402_CI002/blob/main/On-Site_Examinations/Week01_1_UVa100/Uva100.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 每行包含兩個整數 $i$ 和 $j$，範圍在 $1$ 到 $1,000,000$ 之間。
- **Expected Output:** 對於每組輸入，輸出原始的 $i$、$j$ 以及 $[i, j]$ 區間內所有整數中最大的 cycle length。
- **Rules/Constraints:** 對於任意正整數 $n$，定義 3n+1 演算法：若 $n=1$ 則結束；若 $n$ 為偶數則 $n=n/2$；若 $n$ 為奇數則 $n=3n+1$。cycle length 為從 $n$ 開始到 $1$ 所需的步驟數（含起點與終點）。輸入不保證 $i \le j$。
- **Core Task:** 計算給定範圍內所有整數的 cycle length，並輸出最大值。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 最直觀的方式是直接對範圍內每個整數進行模擬計算 cycle length。
- 需要注意輸入的 $i$ 和 $j$ 大小順序不固定，需要先確保 $i \le j$。

### Final Strategy
- **暴力模擬法：** 對 $[\min(i,j), \max(i,j)]$ 範圍內的每個整數，使用 while 迴圈模擬 Collatz 序列直到 $1$，同時計數 cycle length，並取最大值。
- **為何可行：** 題目範圍有限（約 $10^6$），暴力計算在時間限制內可完成。
- **邊界處理：** 用 `swap` 處理 $a > b$ 的情況。

## 4. Pseudocode

```text
START
1. READ a, b (while cin >> a >> b)
2. IF a > b: SWAP a, b
3. SET max_count = 1
4. FOR i = a TO b:
    a. SET count = 1, tmp = i
    b. WHILE tmp != 1:
        IF tmp % 2 == 0: tmp = tmp / 2
        ELSE: tmp = 3 * tmp + 1
        count++
    c. max_count = MAX(max_count, count)
5. PRINT a, b, max_count
6. REPEAT from step 1 until EOF
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
int Uva100(int a, int b) {
    if (a > b) swap(a, b);
    int max_count = 1;
    for (int i = a; i <= b; i++) {
        int count = 1;
        int tmp = i;
        while (tmp != 1) {
            if (tmp % 2 == 0) tmp /= 2;
            else tmp = 3 * tmp + 1;
            count++;
        }
        max_count = max(count, max_count);
    }
    return max_count;
}
```
**Why it works:**
- 直接模擬 Collatz 序列的計算過程，保證準確性。
- 先處理 $a > b$ 的狀況，確保迴圈區間正確。
- 使用 `while (tmp != 1)` 完整計算到終點，無漏算。

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 暴力模擬範圍內每個數字的 cycle length，取最大值 |
| **Edge Cases** | 處理 $a > b$ 的情況，並確保 i, j 在 $1$ 到 $10^6$ 範圍內 |

### Reflection
- **輸入順序陷阱：** 題目沒有保證 $i \le j$，必須主動處理大小交換，否則會得到錯誤結果。
- **模擬 vs 優化：** 雖然本題可用記憶化搜尋（memoization）加速，但暴力法在給定範圍內已足夠，寫出正確的程式碼比過早優化更重要。
- **輸出格式：** 輸出需包含原始輸入的 $i$ 和 $j$（即使交換過），且順序保持不變。
