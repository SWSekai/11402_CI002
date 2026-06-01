# LeetCode 228 - Summary Ranges

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 228
- **Problem Title:** Summary Ranges
- **Problem Link:** https://leetcode.com/problems/summary-ranges/
- **Source Code (Correct/Accepted):** [LeetCode228.cpp](https://github.com/SWSekai/11402_CI002/blob/main/Before_Class/Week15_1_LeetCode228/LeetCode228.cpp)

---

## 2. Problem Statement in My Own Words

給定一個已排序且不含重複元素的整數陣列，將其中所有連續的數字段落合併為範圍字串輸出。

- **Input:** 一個已排序、無重複元素的 `int` 陣列 `nums`，長度範圍為 `[0, 20]`，元素值域為 `[-2^31, 2^31-1]`。
- **Expected Output:** 一個 `vector<string>`，每個元素代表一段連續範圍。單一數字輸出 `"a"`，連續範圍輸出 `"a->b"`。
- **Rules/Constraints:**
  - 陣列可能為空，需回傳空結果
  - 元素值可達 `INT_MAX`（$2^{31}-1$），對追蹤變數執行 `++` 時需注意溢位
  - 陣列保證已排序且無重複，因此只需線性掃描
- **Core Task:** 線性掃描陣列，識別連續區間的起點與終點，並格式化輸出。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- **初步思路:** 使用 `first` 記錄當前區間起點，`cur` 追蹤預期的下一個連續值。每當 `cur != nums[i]` 時，代表連續性中斷，關閉當前區間並重新開始追蹤。走到陣列末尾時強制收尾。
- **初期難點:**
  - 最後一個元素的收尾時機：若單獨在 `i == size-1` 的分支中處理，會隱含「最後一個元素一定屬於當前區間」的錯誤假設，導致不連續的最後元素被錯誤合併
  - `cur++` 在 `nums[i] == INT_MAX` 時會發生整數溢位
  - 空陣列未防護時，`nums[0]` 直接存取會造成 Runtime Error

### Final Strategy

- **採用方法:** 線性掃描（Single Pass），輔以 `first` 與 `cur` 雙變數追蹤區間狀態
- **可行性分析:** 陣列已排序，連續性判斷只需比對相鄰值，時間複雜度為 $O(N)$，空間複雜度為 $O(1)$（不計輸出）。無需排序或額外資料結構。
- **邊界處理:**
  - 函式入口加上 `if(nums.empty()) return {}` 防護空陣列
  - 將「不連續關閉區間」與「最後元素收尾」拆為兩個獨立的 `if`，確保當兩者同時觸發時，先關閉上一段、再收尾最後元素，順序語義正確
  - 在 `i == nums.size()-1` 的分支末尾加上 `continue`，跳過 `cur++`，從根本避免 `INT_MAX` 溢位

---

## 4. Pseudocode

```text
START
1. 若 nums 為空，回傳空結果

2. 初始化：
   - first = nums[0]（當前區間起點）
   - cur = nums[0]（預期的下一個連續值）

3. 對 i 從 0 到 nums.size()-1 迭代：

   3a. 若 cur != nums[i]：
       - 關閉上一段區間：end = nums[i-1]
       - 將 rangeBounding(first, end) 推入結果
       - 重設 first = nums[i]，cur = first

   3b. 若 i == nums.size()-1：
       - 收尾當前區間：end = nums[i]
       - 將 rangeBounding(first, end) 推入結果
       - continue（跳過 cur++，避免 INT_MAX 溢位）

   3c. cur++

4. 回傳結果
END
```

---

## 5. Fail Code vs Correct Code

### Fail Code

```cpp
class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> res;
        int cur = nums[0]; // ❌ 未防護空陣列，nums 為空時直接崩潰
        int first = cur;

        for(int i = 0; i < nums.size(); ++i){ // ⚠️ signed/unsigned mismatch
            int end;
            string str;
            
            // ❌ 優先處理最後元素，但未先判斷連續性
            // 隱含假設：最後元素一定屬於當前區間
            if(i == nums.size()-1){
                end = nums[i];
                str = rangeBounding(first, end);
                res.push_back(str);
                continue;
            }
            if(cur != nums[i]){
                end = nums[i-1];
                str = rangeBounding(first, end);
                res.push_back(str);
                first = nums[i];
                cur = first;
            }
            cur++;
        }
        return res;
    }
private:
    string rangeBounding(int first, int end){
        if(first == end) return to_string(first);
        else return to_string(first) + "->" + to_string(end);
    }
};
```

**Why it failed:**
- **邏輯缺陷:** `i == size-1` 的分支優先於 `cur != nums[i]` 執行，導致最後一個「不連續元素」在未關閉上一段區間的情況下直接以錯誤的 `first` 收尾，產生如 `"1->3"` 的錯誤輸出
- **型別/邊界:** 未防護空陣列，`nums[0]` 在 `nums` 為空時造成 Runtime Error
- **型別/邊界:** `cur++` 未處理 `INT_MAX` 溢位情境

---

### Correct Code

```cpp
class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        if(nums.empty()) return {}; // ✅ 空陣列防護

        vector<string> res;
        int cur = nums[0];
        int first = cur;

        for(size_t i = 0; i < nums.size(); ++i){ // ✅ size_t 消除 signed/unsigned mismatch
            
            // ✅ 先判斷連續性中斷，關閉上一段區間
            if(cur != nums[i]){
                int end = nums[i-1];
                string str = rangeBounding(first, end);
                res.push_back(str);
                first = nums[i];
                cur = first;
            }

            // ✅ 再判斷是否為最後元素，收尾當前區間
            if(i == nums.size()-1){
                int end = nums[i];
                string str = rangeBounding(first, end);
                res.push_back(str);
                continue; // ✅ 跳過 cur++，避免 INT_MAX 溢位
            }

            cur++;
        }
        return res;
    }
private:
    string rangeBounding(int first, int end){
        if(first == end) return to_string(first);
        else return to_string(first) + "->" + to_string(end);
    }
};
```

**Why it works:**
- **核心優化:** 將兩個 `if` 的執行順序對調，確保「不連續時先關閉上一段」的動作發生在「收尾最後元素」之前，使兩者同時觸發時語義正確
- **穩健性:** 入口防護空陣列；`continue` 跳過 `cur++` 從根本迴避 `INT_MAX + 1` 的溢位；`end`、`str` 改為 local 宣告縮小 scope；`size_t` 消除索引型別警告

---

## 6. Difference and Reflection

### Key Differences

| Item | Fail Code | Correct Code |
| :--- | :--- | :--- |
| **邏輯順序** | `i == size-1` 優先執行，跳過連續性判斷 | 先判斷 `cur != nums[i]`，再收尾最後元素 |
| **空陣列** | 未防護，`nums[0]` 直接崩潰 | 入口加上 `if(nums.empty()) return {}` |
| **INT_MAX 溢位** | `cur++` 無條件執行，可能溢位 | `continue` 跳過最後一次 `cur++` |
| **變數 Scope** | `end`、`str` 宣告於迴圈頂部，scope 過寬 | 改為在使用處 local 宣告 |
| **索引型別** | `int i` 與 `size_t` 比較產生警告 | 改用 `size_t i` 統一型別 |

### Reflection

- **最大的失誤:** 對「最後一個元素」的處理過度特殊化，沒有意識到它與「不連續元素」的處理邏輯存在交集，導致兩個分支的執行順序產生語義衝突。
- **習得知識:**
  - 兩個獨立 `if`（非 `if-else`）同時觸發時，執行順序決定語義，必須明確分析哪個先執行
  - `cur++` 這類看似無害的操作在值域邊界（`INT_MAX`）下會產生 Undefined Behavior，應在設計階段就考慮跳脫路徑
  - 變數的 scope 應盡量縮小至實際使用處，避免在函式頂部預先宣告所有變數
- **未來規劃:** 遇到「最後一個元素需要特殊處理」的情境時，先列出「最後元素同時也滿足其他條件」的 Edge Case，確認兩個分支的執行順序不會產生衝突後再動筆。
