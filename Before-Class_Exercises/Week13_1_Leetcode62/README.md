# LeetCode 62 - Unique Paths

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 62
- **Problem Title:** Unique Paths
- **Problem Link:** https://leetcode.com/problems/unique-paths/
- **Source Code (Correct/Accepted):** [leetcode62_Unique_Paths.cpp](leetcode62_Unique_Paths.cpp)

---

## 2. Problem Statement in My Own Words

一個機器人從左上角出發，目標抵達右下角，每次只能向右或向下移動一格。求所有可能的移動路徑總數。

- **Input:** 兩個整數 `m`、`n`，代表網格的列數與行數，範圍 $1 \le m, n \le 100$。
- **Expected Output:** 一個整數，代表從左上角到右下角的不重複路徑總數。
- **Rules/Constraints:**
  - 每次移動只能向右或向下，不可向左或向上
  - 抵達邊界後只剩一種移動方向
  - 題目保證答案在 `int` 範圍內
- **Core Task:** 計算在 $m \times n$ 網格中，從起點到終點的所有合法路徑數量。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- **初步思路:** 觀察到機器人總共需要 $(m-1)$ 步向下、$(n-1)$ 步向右，共 $(m+n-2)$ 步。路徑總數等同於在總步數中，選擇哪幾步向下（或向右）的組合數，即 $C(m+n-2,\ m-1)$。
- **初期難點:**
  - 直接計算階乘 $(m+n-2)!$ 數值極大，即使使用 `long long` 也會在中間過程溢位
  - 若先乘完分子再除分母，整數截斷誤差無法避免
  - 除法時機點不當：對單一分子項直接除以 $i$，不保證整除，造成截斷誤差

### Final Strategy

- **採用方法:** 數學組合公式 $C(n, k)$ 搭配**逐步乘除（邊乘邊除）**的迭代計算方式。
- **可行性分析:**
  - 利用遞推關係 $C(n, i) = C(n, i-1) \times \dfrac{n-i+1}{i}$，每一步結果都是組合數，**整除性由數學保證**，不會產生截斷誤差
  - 取 $k = \min(\text{down\_step},\ \text{right\_step})$ 縮小迭代次數，最多只需迭代 $\min(m-1, n-1)$ 次，Time Complexity 為 $O(\min(m, n))$，Space Complexity 為 $O(1)$
- **邊界處理:**
  - $m = 1$ 或 $n = 1$ 時，`min_num = 0`，迴圈不執行，直接回傳 `res = 1`，正確
  - 中間值使用 `long long` 避免乘法過程溢位，最終以 `static_cast<int>` 明確轉型回傳

---

## 4. Pseudocode

```text
START
1. 計算 down_step = m-1, right_step = n-1, tot_step = down_step + right_step
2. 取 min_num = min(down_step, right_step)
3. 初始化 res = 1（long long）
4. FOR i = 1 TO min_num:
       res = res * (tot_step - min_num + i) / i
       // 先對 res 乘，再除以 i，整除性由 C(n,i) 的遞推關係保證
5. 回傳 static_cast<int>(res)
END
```

---

## 5. Fail Code vs Correct Code

### Fail Code

```cpp
for(int i = 1; i <= min_num; i++){
    res *= (tot - min_num + i) / i; // 錯誤：先對單一分子項做整數除法，不保證整除
}
```

**Why it failed:**
- **效率問題:** 無 TLE 問題，演算法本身為 $O(\min(m,n))$。
- **型別/邊界:** `res` 為 `int`，中間乘法可能溢位。
- **邏輯缺陷:** `(tot - min_num + i) / i` 單獨計算時不保證整除，整數截斷導致累積誤差，例如 $m=3, n=7$ 時第二步 $9/2=4$（截斷），正確應為 $8 \times 9 / 2 = 36$，但得到 $8 \times 4 = 32$。

### Correct Code

```cpp
class Solution {
public:
    int uniquePaths(int m, int n) {
        int down_step = m-1;
        int right_step = n-1;
        int tot_step = down_step + right_step;

        return combination_calculator(tot_step, down_step, right_step);
    }
private:
    int combination_calculator(int tot, int a, int b){
        int min_num = min(a, b);
        long long res = 1; // 避免中間值溢位

        for(int i = 1; i <= min_num; i++){
            res = res * (tot - min_num + i) / i; // 修正：先乘 res 再除 i，整除性有數學保證
        }

        return static_cast<int>(res); // 明確型別轉換意圖
    }
};
```

**Why it works:**
- **核心優化:** 將除法對象從「單一分子項」改為「累積的 `res`」，利用 $C(n,i) = C(n,i-1) \times \frac{n-i+1}{i}$ 的遞推性質，每步結果皆為整數，完全消除截斷誤差。
- **穩健性:** `long long` 確保中間乘法不溢位；`static_cast<int>` 明確表達型別轉換意圖而非依賴隱式轉型；`min_num = 0` 的邊界情況迴圈自然跳過，回傳 1，符合預期。

---

## 6. Difference and Reflection

### Key Differences

| Item | Fail Code | Correct Code |
| :--- | :--- | :--- |
| **除法時機** | 對單一分子項 `(tot - min_num + i)` 先除以 `i` | 對累積結果 `res` 先乘後除，整除性有數學保證 |
| **型別** | `int res`，中間值可能溢位 | `long long res`，避免中間乘法溢位 |
| **型別轉換** | 隱式轉型，意圖不明確 | `static_cast<int>(res)`，明確表達轉換意圖 |
| **死碼** | 宣告 `max_num` 但未使用 | 移除 `max_num`，程式碼整潔 |

### Reflection

- **最大的失誤:** 誤以為對每個分子項單獨除以 $i$ 等同於對累積結果除以 $i$，忽略了整除性的前提條件——整除性需建立在**組合數遞推的整體結構**上，而非單一項上。
- **習得知識:** 組合數的逐步遞推關係 $C(n, i) = C(n, i-1) \times \frac{n-i+1}{i}$ 不僅是數學等式，更是實作中保證整除、避免截斷的核心依據。乘除順序的微小差異，在整數運算中會導致完全不同的結果。
- **未來規劃:**
  - 遇到含有階乘或組合數的計算，優先思考是否能以遞推方式逐步計算，避免直接計算大數階乘
  - 實作前先手算小測資（如 $m=3, n=7$）逐步驗證每一迭代步驟的中間值，確認整除性假設成立
  - 凡涉及型別轉換，一律使用 `static_cast` 明確表達，避免依賴隱式轉型

(文件結束)
