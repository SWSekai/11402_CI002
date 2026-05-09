# UVa 10783 - Odd Sum

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 10783
- **Problem Title:** Odd Sum
- **Problem Link:** [UVa 10783](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=19&page=show_problem&problem=1724)
- **Source Code (Correct/Accepted):** [UVa10783.cpp](https://github.com/SWSekai/11402_CI002/blob/main/On-Site_Examinations/Week03_1_UVa10783/UVa10783.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 第一行為測資筆數 T。每筆測資包含兩個整數 a, b。
- **Expected Output:** 對每筆測資輸出 `Case X: sum`，其中 X 為測資編號（從1開始），sum 為 [a, b] 區間內所有奇數的總和。
- **Rules/Constraints:** 輸入範圍未明確給出，但可使用 int 處理。a 與 b 的相對大小不固定（可能 a > b）。
- **Core Task:** 計算兩個整數之間（含端點）所有奇數的和。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 最直觀的方式是遍歷 a 到 b 的每個數，判斷是否為奇數後累加。
- 需注意 a 可能大於 b，要先確保 a <= b。

### Final Strategy
- **逐一檢查法：** 使用 for 迴圈從 a 到 b，若 i % 2 != 0 則加入總和。
- **為什麼可行：** 題目資料量小，O(n) 線性掃描即可。
- **邊界處理：** 若 a > b 則 swap，確保迴圈正確執行。

## 4. Pseudocode

```text
START
1. 讀入 T (測資筆數)
2. FOR case_num = 1 TO T:
    a. 讀入 a, b
    b. IF a > b: SWAP a, b
    c. ans = 0
    d. FOR i = a TO b:
        IF i 是奇數: ans += i
    e. 輸出 "Case case_num: ans"
END
```

## 5. Correct Code

```cpp
class Odd_Sum {
public:
    static int calculate_all_odd_sun(int a, int b) {
        int ans = 0;
        if (a > b) swap(a, b);
        for (int i = a; i <= b; i++)
            (i % 2 != 0) ? ans += i : 0;
        return ans;
    }
};
```
**Why it works:**
- 使用 swap 處理 a > b 的情況，確保區間正確。
- 逐一判斷奇數性並累加，邏輯簡單直觀。

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 線性掃描區間內所有數字，過濾奇數後累加 |
| **Edge Cases** | 主動 swap 處理 a > b，避免迴圈錯誤 |

### Reflection
- **輸入順序陷阱：** 題目沒保證 a <= b，必須自行處理大小交換，否則區間會是空的。
- **三元運算子簡潔寫法：** `(i % 2 != 0) ? ans += i : 0;` 一行完成判斷與累加，但要注意可讀性。
