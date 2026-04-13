# UVa 10170 - The Hotel with Infinite Rooms

## 1. Problem Information

- **Platform:** UVa Online Judge [cite: 1]
- **Problem ID:** 10170 [cite: 2]
- **Problem Title:** The Hotel with Infinite Rooms [cite: 3]
- **Problem Link:** [UVa 10170](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=13&page=show_problem&problem=1111)
- **Source Code (Correct/Accepted):** [UVa10170.cpp](https://github.com/SWSekai/11402_CI002/blob/main/On-Site_Examinations/Week03_2_UVa10170/UVa10170.cpp)

## 2. Problem Statement in My Own Words

描述一個擁有無限房間的奇怪旅館，其入住規則如下：
- **入住規則**：同一時間只有一個團體入住 。每個團體在第一天早上入住，最後一天傍晚離開 。
- **團體遞增**：下一個團體會在前一個團體離開後的隔天早上入住 ，且成員人數比前一團多1人。
- **停留天數**：一個擁有 $n$ 個成員的團體，會在旅館停留 $n$ 天。
- **任務**：給予初始團體的人數 $S$ 以及指定的第 $D$ 天，求出在第 $D$ 天時，旅館內入住團體的人數。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **直覺作法**：使用 `for` 或 `while` 迴圈，從 $S$ 開始逐一累加天數，直到總天數大於或等於 $D$ 為止。
- [cite_start]**觀察限制**：發現 $D$ 的範圍高達 $10^{15}$ [cite: 16, 18][cite_start]。如果使用線性累加，當 $S$ 很小且 $D$ 很大時，迴圈執行次數過多，可能導致逾時（TLE） [cite: 16][cite_start]。此外，天數累加量會超過 `int` 的範圍，必須使用 `long long` [cite: 18]。

### Final Strategy
- **演算法選擇**：採用 **二分搜尋法 (Binary Search)** 搭配 **等差級數公式**。
- **為何有效**：總天數隨著入住人數增加而具有「單調性」，因此可以在 $O(\log n)$ 時間內找到答案。
- **等差級數判定**：計算從 $S$ 到目前人數 $M$ 的總天數公式為：$\text{Total Days} = \frac{(S + M) \times (M - S + 1)}{2}$。
- **邊界考慮**：
    1.  **溢位處理**：在計算等差級數乘法時，先判斷「(首項+末項)」或「項數」何者為偶數並預先除以 2，避免乘法中間值超過 `long long` 最大限制。
    2.  **搜尋區間**：將搜尋上界設定為合理的 $2 \times 10^9$，因為其平方規模已足以涵蓋 $10^{15}$。

## 4. Pseudocode

```text
START
1. Read initial_member (S) and target_room_num (D).
2. IF S >= D, RETURN S.
3. SET low = S, high = 2,000,000,000.
4. WHILE low <= high:
    a. mid = low + (high - low) / 2
    b. Calculate total_days using safe arithmetic (prevent overflow).
    c. IF total_days >= D:
        answer = mid, high = mid - 1
    d. ELSE:
        low = mid + 1
5. PRINT answer.
END
```

## 5. Fail Code vs Correct Code

### Fail Code
```cpp
// 初始版本：線性累加與潛在溢位
long long current_archive_room = 0; // 若此處用 int 必溢位
for (long long i = initial_member; ; i++) {
    current_archive_room += i;
    if (current_archive_room >= target_room) {
        cout << i; // 缺少 endl 導致多筆測資輸出黏連
        break;
    }
}
```

**Why it failed:**
- **效率低下**：面對 $D = 10^{15}$ 時，線性迴圈運算次數過多。
- **型別溢位**：中間累加變數若誤用 `int` 會發生溢位，導致判斷錯誤。
- **輸出格式**：未處理換行，導致多筆測試結果無法被判定正確。

### Correct Code
```cpp
// 最終 Accepted 版本：二分搜尋 + 溢位防護
static bool is_reach_target_room(long long initial_member, long long current_room_member, long long target_room_num) {
    long long total_day = 0;
    // 預先除以 2 以防止 (A+B)*N 在中間過程溢位
    if ((initial_member + current_room_member) % 2 == 0) {
        total_day = ((initial_member + current_room_member) / 2) * (current_room_member - initial_member + 1);
    } else {
        total_day = (initial_member + current_room_member) * ((current_room_member - initial_member + 1) / 2);
    }
    return total_day >= target_room_num;
}
```

**Why it works:**
- **效能優化**：二分搜尋大幅減少檢查次數。
- **安全計算**：透過先除再乘的邏輯，確保 $10^{15}$ 規模的運算不會撞擊 `long long` 的極限。

## 6. Difference and Reflection

### Key Differences

| Item | Fail Code | Correct Code |
|---|---|---|
| Logic | 線性累加 $O(N)$ | 二分搜尋 $O(\log N)$ |
| Edge Cases | 易忽略 $10^{15}$ 帶來的溢位 | 針對乘法中間值進行溢位防護 |
| Output Handling | 缺少換行 | 統一使用 `endl` 處理多筆輸入 |
| Code Quality | 邏輯分散在 main 中 | 封裝於類別，職責分離明確 |

### Reflection
- **嚴格檢查型別**：在處理大數據題目時，第一時間應確認所有涉及計算的變數是否需要 `long long`。
- **數學公式的中間值**：即使最終結果在 `long long` 內，乘法的中間過程極易溢位，必須採取「先除後乘」或使用更大的型別（如 `__int128`）。
- **二分搜尋的威力**：學會將問題轉換為「判定滿足條件的最小值」，是優化 $O(N)$ 到 $O(\log N)$ 的核心思維。