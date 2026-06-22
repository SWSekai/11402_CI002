# UVa 11559 - Event Planning

使用本模板記錄您針對每個程式設計問題的解題過程與效能回顧。請務必用您自己的語言書寫，並著重於闡述您的思考路徑、設計取捨、以及解決問題的核心邏輯。

## 1. Problem Information

- **Platform:** UVa Online Judge
- **Problem ID:** 11559
- **Problem Title:** Event Planning
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2554
- **Source Code (Correct/Accepted):** [UVa11559.cpp](https://github.com/SWSekai/11402_CI002/blob/main/On-Site_Examinations/Week09_1_UVa11559/src/UVa11559.cpp)

## 2. Problem Statement in My Own Words

你被指派規劃一個社團的週末出遊活動。需要從多間旅館與多個可選週次中，挑出一個「旅館 + 週次」的組合，讓所有人都能住進同一間旅館，且總費用在預算內，目標是找出最低總費用。

- **Input:** 每筆測資第一行為四個整數：參加人數 N（1~200）、預算 B（1~500000）、旅館數 H（1~18）、可選週次數 W（1~13）。接著每間旅館佔兩行：第一行為每人每週末的住宿費 p（1~10000），第二行為 W 個整數，代表各週次可用床位數 a（0~1000）。
- **Expected Output:** 每筆測資輸出一行，為可行方案中的最低總費用；若無任何方案在預算內，輸出 `stay home`。
- **Rules/Constraints:**
  - 所有人必須住同一間旅館
  - 只需選擇 W 週中的**任意一週**舉辦活動，不是住滿所有週
  - 該週次的可用床位數必須 ≥ 參加人數才可行
  - 總費用 = 每人費用 × 參加人數，必須 ≤ 預算
- **Core Task:** 枚舉所有（旅館、週次）組合，篩選出可行者，輸出最低總費用。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- **初步思路:** 對每間旅館，逐週讀取可用房間數，判斷是否有任何一週可容納所有人。若可行則計算該旅館的總費用，與全域最小值比較。
- **初期難點:**
  - 誤解題意：最初以為要選擇「所有週次」都可行才算，導致判斷邏輯完全相反（`is_enough` 設計為「所有週都夠」而非「任意一週夠」）
  - 費用計算錯誤：曾誤用 `sum += cost`（在迴圈內累加）或 `cost * week`，未理解 `cost` 為「每人每週末」的單價，正確公式應為 `cost * participant`
  - 缺少 `#include <climits>`：本地環境透過其他 header 間接引入 `INT_MAX`，OJ 環境則 Compile Error

### Final Strategy

- **採用方法:** 暴力枚舉（Brute Force）— 對每間旅館的每個週次逐一檢查
- **可行性分析:** 資料規模極小（H ≤ 18、W ≤ 13），總組合數最多 234 次，時間複雜度 $O(H \times W)$，暴力枚舉為最直觀且充分的解法，無需任何優化
- **邊界處理:**
  - `is_enough` 初始為 `false`，遇到第一個可行週次才設為 `true`，但**仍需讀完該旅館所有週次資料**，避免 `cin` 輸入位置錯位影響後續旅館的讀取
  - 若所有旅館皆不可行，`min_cost` 維持 `INT_MAX`，輸出 `stay home`
  - 使用 `while (cin >> ...)` 處理多筆測資與 EOF

## 4. Pseudocode

```text
START
1. 初始化：讀入 participant, budget, hotel, week
2. 對每筆測資，設 min_cost = INT_MAX
3. 對每間旅館：
   a. 讀入 cost
   b. 設 is_enough = false
   c. 對每個週次：
      - 讀入 available_room
      - 若 is_enough 尚未成立 且 available_room >= participant：
          設 is_enough = true（繼續讀完剩餘週次，但不做判斷）
   d. 若 is_enough == true：
      - 計算 sum = cost * participant
      - 若 sum < min_cost，更新 min_cost
4. 若 min_cost <= budget，輸出 min_cost；否則輸出 "stay home"
END
```

## 5. Fail Code vs Correct Code

### Fail Code

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <set>
// 缺少 #include <climits>，導致 INT_MAX 在 OJ 環境 Compile Error

using namespace std;

int main() {
    while (true) { // 缺少 EOF 判斷，會導致無窮迴圈
        int participant, budget, hotel, week, min_cost = INT_MAX;
        cin >> participant >> budget >> hotel >> week;
        while (hotel--) {
            int cost, available_room, sum = 0;
            bool is_enough = true; // 初始為 true，邏輯完全相反
            cin >> cost;

            for (int i = 0; i < week; i++) {
                cin >> available_room;
                if (available_room < participant) {
                    is_enough = false; // 要求所有週都夠，而非任意一週
                    continue;
                }
                sum += cost; // 費用計算錯誤：累加 cost 而非乘以 participant
            }
            if (sum < min_cost && is_enough) min_cost = sum;
        }
        cout << (min_cost <= budget ? to_string(min_cost) : "stay home") << endl;
    }
    return 0;
}
```

**Why it failed:**
- **效率問題:** 無，資料規模小，效率非瓶頸
- **型別/邊界:** 缺少 `#include <climits>`，`INT_MAX` 在 OJ 環境未定義，直接 Compile Error；`while (true)` 缺少 EOF 判斷
- **邏輯缺陷:** `is_enough` 語意錯誤——題目要求任意一週可行即可，但程式碼實作為「所有週都必須夠」；費用計算 `sum += cost` 在週次迴圈內累加，既不正確也語意混亂

### Correct Code

```cpp
#include <iostream>
#include <string>
#include <climits> // 修正：加入 INT_MAX 所需的 header

using namespace std;

int main() {
    int participant, budget, hotel, week;
    while (cin >> participant >> budget >> hotel >> week) { // 修正：加入 EOF 判斷
        int min_cost = INT_MAX;
        while (hotel--) {
            int cost, available_room, sum = 0;
            bool is_enough = false; // 修正：初始為 false，任意一週可行才設為 true
            cin >> cost;

            for (int i = 0; i < week; i++) {
                cin >> available_room;
                // 修正：找到可行週才標記，但繼續讀完所有週次避免輸入錯位
                if (!is_enough && available_room >= participant) {
                    is_enough = true;
                }
            }
            if (is_enough) {
                sum = cost * participant; // 修正：正確費用公式
                if (sum < min_cost) min_cost = sum;
            }
        }
        cout << (min_cost <= budget ? to_string(min_cost) : "stay home") << endl;
    }
    return 0;
}
```

**Why it works:**
- **核心優化:** 將 `is_enough` 語意從「所有週都夠」修正為「任意一週夠即可」，並正確初始化為 `false`；費用公式改為 `cost * participant`，符合題目「每人每週末」的單價定義
- **穩健性:** 即使 `is_enough` 已為 `true`，仍繼續讀完該旅館所有週次資料，確保 `cin` 不錯位；`while (cin >> ...)` 正確處理多筆測資與 EOF

## 6. Difference and Reflection

### Key Differences

| Item | Fail Code | Correct Code |
| :--- | :--- | :--- |
| **Header** | 缺少 `<climits>`，`INT_MAX` 未定義 | 加入 `#include <climits>` |
| **EOF 處理** | `while (true)` 無限迴圈 | `while (cin >> ...)` 正確偵測 EOF |
| **Logic** | `is_enough = true` 初始，要求所有週都夠 | `is_enough = false` 初始，任意一週夠即可 |
| **費用計算** | `sum += cost`（迴圈累加，語意錯誤） | `sum = cost * participant`（正確單次計算） |
| **輸入對齊** | 判斷後用 `continue` 跳過，語意混亂 | 繼續讀完所有週次，確保 `cin` 不錯位 |

### Reflection

- **最大的失誤:** 對題意的核心理解錯誤——「W 週中選一週」與「必須所有週都可行」是完全相反的語意，卻在沒有仔細確認的情況下直接實作，導致邏輯從根本上就是錯的
- **習得知識:** `INT_MAX` 依賴 `<climits>`，不應依賴本地編譯器的間接引入；Boolean flag 的初始值設定直接決定邏輯語意，動筆前必須想清楚「預設狀態是什麼」；讀取固定格式輸入時，即使提前確定結果，仍需讀完所有應讀資料，避免輸入指標錯位
- **未來規劃:** 拿到題目後先用自己的話寫下「篩選條件」，明確區分「任意一個滿足」（OR 語意）與「全部都滿足」（AND 語意）；實作前先手動跑 Sample Input，確認費用公式的數字對得上；提交前檢查所有用到的常數是否有對應的 `#include`