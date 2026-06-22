# LeetCode 1046 - Last Stone Weight

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 1046
- **Problem Title:** Last Stone Weight
- **Problem Link:** https://leetcode.com/problems/last-stone-weight/
- **Source Code (Correct/Accepted):** [LeetCode1046.cpp](https://github.com/SWSekai/11402_CI002/blob/main/Before-Class_Exercises/Week14_1_LeetCode1046/src/LeetCode1046.cpp)

---

## 2. Problem Statement in My Own Words

給定一組石頭，每顆石頭都有一個正整數重量。每一回合從中選出最重的兩顆石頭互相碰撞，規則如下：

- **Input:** 一個整數陣列 `stones`，長度為 $1 \leq n \leq 30$，每個元素滿足 $1 \leq stones[i] \leq 1000$。
- **Expected Output:** 回傳最後剩下的石頭重量；若所有石頭都相消則回傳 `0`。
- **Rules/Constraints:**
  - 每回合必須取**最重的兩顆**石頭
  - 若兩顆重量相同 → 兩顆都消失
  - 若兩顆重量不同（設為 `x ≤ y`）→ 重量 `x` 的石頭消失，重量 `y` 的石頭變為 `y - x`
  - 重複此過程直到石頭數量 ≤ 1
- **Core Task:** 模擬石頭碰撞過程，每次都能快速取出最大值，最終回傳剩餘重量。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- **初步思路:** 題目要求每回合取最大的兩顆，直覺聯想到需要一個能快速取最大值的資料結構。若用普通陣列每次排序則 Time Complexity 為 $O(N^2 \log N)$，顯然不是最佳解。
- **初期難點:**
  - 如何高效率地反覆取出最大值 → 需要 max-heap（`priority_queue<int>`）
  - `first == second` 時，兩石相消後應該對 heap 做什麼操作？這是最容易犯錯的邏輯點
  - 當所有石頭恰好兩兩相消，heap 為空時，若直接呼叫 `pq.top()` 會產生 undefined behavior

### Final Strategy

- **採用方法:** Max-Heap（`priority_queue<int>`）+ 貪婪模擬
- **可行性分析:**
  - `priority_queue<int>` 預設為 max-heap，每次 `top()` 取最大值時間複雜度為 $O(1)$，`push` / `pop` 為 $O(\log N)$
  - 整體 Time Complexity：$O(N \log N)$，對於 $N \leq 30$ 的規模遠在限制之內
  - 兩石碰撞後若有差值才 push 回 heap，若相等則直接跳過，讓兩石自然消失，邏輯最為精簡
- **邊界處理:**
  - `first == second`：兩石消失，不 push 任何值，用 `continue` 跳過
  - heap 最終為空：在 `return` 前加 `if (pq.empty()) return 0;` 防護

---

## 4. Pseudocode

```text
START
1. 將所有 stones 元素推入 max-heap (priority_queue)

2. WHILE heap 內元素數量 > 1:
   a. 取出最大值 first，pop
   b. 取出次大值 second，pop
   c. IF first == second → continue（兩石相消，不 push）
   d. ELSE → push (first - second) 回 heap

3. IF heap 為空 → return 0
4. ELSE → return heap.top()
END
```

---

## 5. Fail Code vs Correct Code

### Fail Code

```cpp
class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> pq;

        for (int num : stones) {
            pq.push(num);
        }
        
        while (pq.size() > 1) {
            int first = pq.top();
            pq.pop();
            int second = pq.top();
            pq.pop();

            if (first == second) {
                // [BUG] 兩石相消後不應 push 任何值
                // push(0) 讓 heap 永遠不會真正清空，且 0 會污染後續碰撞邏輯
                if(first != 1) pq.push(0);
                // [BUG] heap 為空時強行 push(1) 製造錯誤答案
                if(pq.size() == 0) pq.push(1);
                
                continue;
            }

            pq.push(first - second);
        }
        // [BUG] heap 為空時 pq.top() 造成 undefined behavior
        return pq.top();
    }
};
```

**Why it failed:**
- **邏輯缺陷:** `first == second` 時，不應 push 任何值。錯誤地 push `0` 導致 heap 殘留無效元素，污染後續碰撞運算。
- **型別/邊界:** heap 為空時強行 `push(1)` 完全違反題意，直接製造錯誤答案（如 `stones = [9,3,2,10]` 回傳 `1` 而非 `0`）。
- **邊界缺失:** 最終 `return pq.top()` 未處理 heap 為空的情況，存在 undefined behavior 風險。

---

### Correct Code

```cpp
class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> pq;

        for (int num : stones) {
            pq.push(num);
        }
        
        while (pq.size() > 1) {
            int first = pq.top();
            pq.pop();
            int second = pq.top();
            pq.pop();

            // [FIX] 兩石相消時直接 continue，不 push 任何值
            if (first == second) continue;
            pq.push(first - second);
        }
        
        // [FIX] 補上 heap 為空的邊界防護，回傳 0 符合題意
        if(pq.size() == 0) return 0;
        return pq.top();
    }
};
```

**Why it works:**
- **核心優化:** 移除所有錯誤的 `push` 操作，兩石相消後直接 `continue`，heap 狀態始終乾淨正確。
- **穩健性:** 明確處理 heap 最終為空的情境，確保不會發生 undefined behavior，且回傳值完全符合題目規範。

---

## 6. Difference and Reflection

### Key Differences

| Item | Fail Code | Correct Code |
| :--- | :--- | :--- |
| **相消邏輯** | `first == second` 時錯誤 push `0` 或 `1` 進 heap | `first == second` 時直接 `continue`，兩石真正消失 |
| **Edge Cases** | heap 為空時直接 `pq.top()`，undefined behavior | 補上 `if (pq.empty()) return 0;` 防護 |
| **Heap 純淨性** | 殘留無效的 `0` 元素參與後續碰撞，污染結果 | heap 中只存在有效的石頭重量 |
| **Other** | 兩個 `if` 條件邏輯互相矛盾，難以維護 | 單一 `continue` 路徑，邏輯清晰 |

### Reflection

- **最大的失誤:** 對「相消」的語意理解不夠精確。誤以為兩石相消後需要在 heap 中留下一個佔位符（`0` 或 `1`），沒有意識到直接不 push 才是正確語意。這導致在 heap 內留下了污染元素，並衍生出更多錯誤的補救條件。

- **習得知識:**
  - Max-heap（`priority_queue<int>`）是處理「反覆取最大值」類型問題的標準工具，$O(\log N)$ 的 push/pop 效率遠優於每次重新排序
  - 模擬類題目的邊界條件核心在於：操作結束後資料結構是否可能為空？需要在 `return` 前明確防護
  - 當條件分支越寫越複雜時，應退一步思考「有沒有更統一的邏輯可以涵蓋所有情況」

- **未來規劃:**
  - 遇到「反覆取最值」的模擬題，優先確認是否使用 heap，並在動筆前先列出 heap 為空時的回傳行為
  - 每寫完一個條件分支，立即用至少一個手動測試案例（如 `stones = [2,2]`、`stones = [3,3,3]`）追蹤 heap 狀態變化，確認語意正確再繼續
