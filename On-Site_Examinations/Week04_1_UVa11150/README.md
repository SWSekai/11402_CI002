# UVa 11150 - Cola

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 11150
- **Problem Title:** Cola
- **Problem Link:** [UVa 11150 - Cola](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=23&page=show_problem&problem=2091)
- **Source Code (Correct/Accepted):** [UVa11150.cpp](https://github.com/SWSekai/11402_CI002/blob/main/On-Site_Examinations/Week04_1_UVa11150/UVa11150.cpp)

## 2. Problem Statement in My Own Words

-**Input:** 每行包含一個整數 $N$ ($1 \le N \le 200$)，代表最初購買的可樂數量。
- **Expected Output:** 輸出在可以向朋友「借空瓶」的前提下，最多能喝到的可樂總數。
- **Rules/Constraints:** 每 3 個空瓶可以換 1 瓶新可樂。可以借空瓶，但最後必須確保有足夠的空瓶還給朋友。
- **Core Task:** 模擬兌換過程，並判斷在剩餘 2 個空瓶時，是否可以透過「借 1 還 1」來多喝一瓶。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 最初的想法是直接進行模擬：喝完 $N$ 瓶產生 $N$ 個空瓶，然後不斷除以 3 來計算換得的新可樂。
- 觀察到題目圖示中的 Method 2 ，發現在剩餘 2 個空瓶時，如果借 1 個湊成 3 個，換到 1 瓶喝完後剛好剩 1 個可以還回去。

### Final Strategy
- **模擬法：** 建立一個循環，每次計算 `換得的可樂 = 目前空瓶 / 3`，並更新 `剩餘空瓶 = (目前空瓶 / 3) + (目前空瓶 % 3)`。
- **邊界處理：** 當模擬結束後，若手上剛好剩下 2 個空瓶，代表可以進行最後一次「借 1 還 1」的動作，總數加 1。
- **數學法（延伸）：** 實際上每換一瓶新可樂淨消耗 2 個空瓶（3 換 1，喝完剩 1），故公式可簡化為 $N + N/2$。

## 4. Pseudocode

```text
START
1. READ initial_bottles (N)
2. SET total_drunk = N
3. SET empty_bottles = N
4. WHILE empty_bottles >= 3:
    NEW_COLA = empty_bottles / 3
    total_drunk += NEW_COLA
    empty_bottles = (empty_bottles % 3) + NEW_COLA
5. IF empty_bottles == 2:
    total_drunk += 1 (Borrow 1, exchange, drink, return 1)
6. PRINT total_drunk
END
```

## 5. Fail Code vs Correct Code

### Fail Code

```cpp
// 原始有問題的邏輯
while (coke_bottle != 1) {
    total_bottle += coke_bottle / 3;
    coke_bottle = coke_bottle / 3 + coke_bottle % 3;

    if (coke_bottle == 2) {
        total_bottle += 1;
        return total_bottle; // 過早結束，且未考慮 N=1, 2 等狀況
    }
}
```

**Why it failed:**
- **邏輯斷點：** 使用 `if (coke_bottle == 2)` 直接 `return` 導致程式無法處理更小的輸入（如 $N=1$）或在某些情況下過早跳出循環。
- **累積誤差：** 雖然在 $N=8$ 時剛好觸發條件得到 12，但並非通用的模擬邏輯。

### Correct Code (修正後的邏輯)

```cpp
static int get_total_bottle(int n) {
    int total = n;
    int empty = n;
    while (empty >= 3) {
        total += empty / 3;
        empty = (empty / 3) + (empty % 3);
    }
    if (empty == 2) total++; // 關鍵：最後剩 2 瓶時借 1 還 1
    return total;
}
```

**Why it works:**
- **完整模擬：** 嚴格遵循「換完再喝、喝完再換」的物理過程。
- **邊界判定：** 最後的 `if (empty == 2)` 準確捕捉了題目「借還機制」的精髓，且不破壞前面的循環邏輯。

## 6. Difference and Reflection

### Key Differences

| Item | Fail Code | Correct Code |
|---|---|---|
| Logic | 使用 `if` 硬湊借瓶時機 | 完整模擬後再處理剩餘瓶數 |
| Edge Cases | $N=1, 2$ 時可能直接回傳錯誤值 | 能正確處理所有 $1 \le N \le 200$  |
| 結構 | 迴圈內有不穩定的 `return` | 邏輯線性流動，結構穩定 |

### Reflection
- **不要過早優化：** 最初想用一個 `if` 解決借瓶問題，反而導致邏輯不通用。應先寫出正確的基礎模擬。
- **理解題意：** 題目中的「借 1 還 1」實際上就是「剩 2 瓶就能多喝 1 瓶」的代名詞 。
- **命名重要性：** 將變數清楚地區分為 `total_drunk` 和 `current_empty` 有助於思考邏輯而不混淆。