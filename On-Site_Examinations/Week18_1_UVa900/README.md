# UVa Online Judge 900 - Brick Wall Patterns

## 1. Problem Information

- **Platform:** UVa Online Judge
- **Problem ID:** 900
- **Problem Title:** Brick Wall Patterns
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=841
- **Source Code (Correct/Accepted):** [UVa900.cpp](https://github.com/SWSekai/11402_CI002/blob/main/On-Site_Examinations/Week18_1_UVa900/src/UVa900.cpp)

## 2. Problem Statement in My Own Words

用長度為高度兩倍的標準磚塊，砌一道高度固定為 2 單位的牆。每塊磚可以「直立」（佔 1 單位寬）或「平放」（佔 2 單位寬，需上下兩塊配對填滿整個高度）。給定牆的寬度（長度），求出有幾種不同的排列方式。

- **Input:** 一連串正整數，每行一個，代表牆的長度。最大長度為 50。輸入以 `0` 作為終止訊號。
- **Expected Output:** 對每一筆輸入，各自輸出一行，代表該長度的牆有幾種排列方式。
- **Rules/Constraints:**
  - 牆高固定為 2 單位。
  - 長度範圍：1 ≤ length ≤ 50。
  - 結果數值會隨長度成長快速膨脹，需注意型別容量。
  - 多筆查詢、以 `0` 終止。
- **Core Task:** 對給定的牆長，計算合法排列總數。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- **初步思路:** 觀察樣本（長度 1→1 種、2→2 種、3→3 種），發現數列符合遞推關係 `f(n) = f(n-1) + f(n-2)`，本質上是 Fibonacci 數列。直覺上想用遞迴直接表達這個遞推式。
- **初期難點:**
  - 遞迴若不做任何優化，時間複雜度會是 $O(2^n)$，在 `input = 50` 時必然 TLE。
  - 第 50 項數值約 $2 \times 10^{10}$，超出 `int` 範圍，必須使用 `long long`。
  - 遞推式的基底（base case）設定：本題 `f(1) = 1`、`f(2) = 2`，與標準 Fibonacci 起始值不同，需自行確認。

### Final Strategy

- **採用方法:** 動態規劃（Dynamic Programming）的 bottom-up 填表，再結合 lazy initialization（延遲初始化）與快取，使用 `static` 類別成員保存 dp 表。
- **可行性分析:**
  - 將 $O(2^n)$ 的重複遞迴改為 $O(n)$ 的單層迴圈填表，徹底消除重算。
  - 題目上限固定為 50，因此第一次呼叫時即一次填滿 `dp[1..50]`，並透過 `static` 成員讓表跨呼叫存活；後續所有查詢退化為 $O(1)$ 查表。
  - 旗標 `initialized` 確保填表邏輯整個程式生命週期只執行一次，避免每筆查詢重建表所造成的記憶體配置 overhead。
- **邊界處理:**
  - 基底值 `dp[1] = 1`、`dp[2] = 2` 在迴圈前先設定，迴圈自 `i = 3` 起。
  - 填表一律填到固定上限 50，不依賴當次 `input`，避免「先查小值再查大值時表不夠大」的越界風險。
  - `input = 0` 在 `main` 攔截作為終止條件，不進入計算。
  - 已驗算 `dp[50]` 量級在 `long long` 容納範圍內，無溢位。

## 4. Pseudocode

```text
START
1. 宣告 static 快取表 dp 與 static 旗標 initialized (= false)
2. countPatterns(input):
   2.1 IF initialized == false:
         resize dp 至 51
         dp[1] = 1, dp[2] = 2
         FOR i = 3 TO 50:
             dp[i] = dp[i-1] + dp[i-2]
         initialized = true
   2.2 RETURN dp[input]
3. main:
   WHILE 讀入 input:
       IF input == 0: BREAK
       輸出 countPatterns(input)
END
```

## 5. Fail Code vs Correct Code

### Fail Code

```cpp
class Brick_Wall_Patterns {
public:
    static long long countPatterns(int input) {
        if (input == 1) return 1;
        if (input == 2) return 2;

        long long res = 0;
        for (int i = 3; i <= input; ++i) {
            // 缺陷：迴圈內又呼叫遞迴，迴圈與遞迴語意衝突
            // 每次迭代都觸發一棵完整的指數級遞迴樹
            res = countPatterns(i - 1) + countPatterns(i - 2);
        }
        return res;
    }
};
```
**Why it failed:**
- **效率問題:** 迴圈內呼叫 `countPatterns(i-1) + countPatterns(i-2)`，兩個遞迴呼叫各自往下展開成指數級的遞迴樹，時間複雜度約 $O(2^n)$，`input = 50` 必然 TLE。
- **邏輯缺陷:** 迴圈與遞迴混用導致迴圈變數 `i` 形同虛設，`res` 每次被覆寫，前面迭代全屬浪費，僅最後一次 `i = input` 的結果有效——這是披著迴圈外皮的指數遞迴。
- **無狀態保存:** 每筆查詢從零重算，多筆輸入重複勞動。

### Correct Code

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Brick_Wall_Patterns {
public:
    static long long countPatterns(int input) {
        // 修正關鍵 1：lazy init，旗標確保填表只跑一次
        if (!initialized) {
            dp.resize(51);
            dp[1] = 1;
            dp[2] = 2;
            // 修正關鍵 2：填到固定上限 50，不依賴 input，供後續快取重用
            for (int i = 3; i <= 50; ++i) {
                dp[i] = dp[i - 1] + dp[i - 2];
            }
            initialized = true;
        }
        // 修正關鍵 3：所有回傳統一查表，single source of truth
        return dp[input];
    }
private:
    static vector<long long> dp;
    static bool initialized;
};

// 修正關鍵 4：static 成員必須在 class 外定義，否則 linker error
vector<long long> Brick_Wall_Patterns::dp;
bool Brick_Wall_Patterns::initialized = false;

int main() {
    int input;
    while (cin >> input) {
        if (input == 0) break;
        cout << Brick_Wall_Patterns::countPatterns(input) << endl;
    }
}
```
**Why it works:**
- **核心優化:** 把指數級遞迴改為 $O(n)$ 的 bottom-up 填表，並用 `static` 成員 + 旗標讓表跨呼叫只建一次，查詢退化為 $O(1)$。
- **穩健性:** 填表上限固定為 50 而非當次 `input`，杜絕「先小後大」的越界；`long long` 容納第 50 項，無溢位；`input = 0` 在 `main` 攔截終止。

## 6. Difference and Reflection

### Key Differences

| Item | Fail Code | Correct Code |
| :--- | :--- | :--- |
| **Logic** | 迴圈內遞迴展開，$O(2^n)$ | bottom-up 填表，建表 $O(n)$、查詢 $O(1)$ |
| **State Handling** | 無快取，每筆查詢重算 | static 成員跨呼叫快取，lazy init 只建一次 |
| **Edge Cases** | 迴圈變數失效、`res` 被覆寫 | 填表至固定上限 50，避免越界 |
| **Code Cleanliness** | 殘留死變數 `res`、基底特判冗餘 | 邏輯收斂於單一 dp 表（single source of truth） |

### Reflection

- **最大的失誤:** 最初把「迴圈累加」與「遞迴展開」兩種思維混用，誤以為加了 `for` 迴圈就是優化，實際上迴圈內的遞迴呼叫才是 TLE 真正根源。沒看清「DP 的關鍵是查表取代重算」，而非單純套個迴圈外殼。
- **習得知識:**
  - DP 的 bottom-up 填表如何將指數級遞迴降為線性。
  - lazy initialization 設計模式：用 `static` 成員 + 旗標讓快取跨呼叫存活，第一次呼叫才建表。
  - C++ `static` 類別成員必須在 class 外定義一次，否則產生 `undefined reference` linker error。
  - single source of truth：基底值既已入表，就不該再保留 `input == 1/2` 的特判。
- **未來規劃:** 遇到遞推型問題，先寫出遞推式並判斷是否有重疊子問題；若有，直接走 memoization 或 bottom-up，而非裸遞迴。對於上限固定的題目，優先考慮 precompute / lazy init 快取。重構後務必逐行檢視，清除死變數與冗餘特判再收尾。
