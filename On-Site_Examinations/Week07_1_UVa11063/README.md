# UVa 11063 - B2-Sequence

## 1. Problem Information

- **Platform:** UVa Online Judge
- **Problem ID:** 11063
- **Problem Title:** B2-Sequence
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2004
- **Source Code (Correct/Accepted):** [UVa11063.cpp](https://github.com/SWSekai/11402_CI002/blob/main/On-Site_Examinations/Week07_1_UVa11063/src/UVa11063.cpp)

---

## 2. Problem Statement in My Own Words

給定一個整數序列，判斷它是否為合法的 B2-Sequence。

- **Input:** 多筆測資，以 EOF 終止。每筆測資第一行為整數 $N$（$2 \leq N \leq 100$），代表序列元素個數；第二行為 $N$ 個整數，每個元素 $b_i \leq 10000$。每筆測資後有一個空行。
- **Expected Output:** 每筆測資輸出一行 `Case #X: It is a B2-Sequence.` 或 `Case #X: It is not a B2-Sequence.`，X 從 1 開始計數。每筆測資輸出後接一個空行。
- **Rules/Constraints:**
  - 序列所有元素必須為正整數（$b_i \geq 1$）
  - 序列必須嚴格遞增（$b_1 < b_2 < b_3 \ldots$）
  - 所有 pairwise sum $b_i + b_j$（其中 $i \leq j$，包含 $i = j$）必須兩兩不同
- **Core Task:** 驗證輸入序列是否同時滿足嚴格遞增、全為正整數、以及所有 pairwise sum 唯一三個條件。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- **初步思路:** 用雙層迴圈枚舉所有 pairwise sum，記錄已出現的 sum，若有重複則判為非 B2-Sequence。
- **初期難點:**
  - 最初忽略了 $i = j$ 的情況（即 $b_i + b_i = 2b_i$ 也必須納入驗證）
  - 最初用 `vector<int> sequence(test_case)` 初始化，再用 `push_back` 新增元素，導致 vector 前段充滿 0，函式永遠回傳 `false`
  - 忽略了輸入終止條件是 EOF 而非哨兵值 `0`，以及輸出需要附上 Case 編號

### Final Strategy

- **採用方法:** 前置驗證（嚴格遞增 + 正整數）+ 雙層迴圈枚舉 pairwise sum，使用 `set<int>` 進行 $O(\log N)$ 查詢與插入。
- **可行性分析:** $N \leq 100$，pairwise sum 最多 $\frac{N(N+1)}{2} \approx 5050$ 組，整體時間複雜度為 $O(N^2 \log N)$，遠低於 TLE 門檻。`set` 比 `vector` 線性搜尋更有效率，且語意清晰。
- **邊界處理:**
  - $i = j$ 的情況（$2b_i$）須納入 pairwise sum 驗證
  - 序列元素非嚴格遞增時（包含相等）須判為 false
  - 序列含非正整數（$\leq 0$）須判為 false
  - 跨 test case 的狀態變數（`current`、`isUpper`）必須在每筆測資開始時重置

---

## 4. Pseudocode

```text
START
1. 初始化 case 計數器 count = 1

2. WHILE 成功讀入 N（EOF 終止）:
   a. 初始化 current = 0, isUpper = true, sequence = 空 vector
   b. 讀入 N 個整數:
      - 若 n <= 0 或 n <= current，設 isUpper = false
      - 將 n push 進 sequence
      - 更新 current = n

3. 印出 "Case #count: "

4. IF isUpper 為 false:
      印出 "It is not a B2-Sequence."
   ELSE:
      呼叫 isB2Sequence(sequence):
         初始化空 set verify_sequence
         FOR i = 0 to N-1:
            FOR j = i to N-1:  // 包含 i == j
               sum = sequence[i] + sequence[j]
               IF sum 已在 verify_sequence 中: RETURN false
               將 sum 插入 verify_sequence
         RETURN true
      依回傳值印出對應訊息

5. 印出空行，count++
END
```

---

## 5. Fail Code vs Correct Code

### Fail Code

```cpp
int main() {
    int test_case, n;
    bool is_first_case = true;

    // BUG 1: 終止條件錯誤，題目應以 EOF 終止，不是讀到 0 停止
    while (cin >> test_case && test_case != 0) {
        // BUG 2: vector(test_case) 預先填充 test_case 個 0
        // 再用 push_back 新增，導致序列前段全是 0
        vector<int> sequence(test_case);
        while (test_case--) {
            cin >> n;
            sequence.push_back(n);
        }

        if (!is_first_case) cout << endl;
        is_first_case = false;

        // BUG 3: 缺少 Case 編號，輸出格式不符
        // BUG 4: 未驗證序列嚴格遞增與正整數條件
        if (B2Sequence::isB2Sequence(sequence)) {
            cout << "It is a B2-Sequence." << endl;
        } else {
            cout << "It is not a B2-Sequence." << endl;
        }
    }
}
```

**Why it failed:**
- **邏輯缺陷:** `vector<int> sequence(test_case)` 與 `push_back` 混用，序列前段塞滿 0，pairwise sum 必然大量重複，`isB2Sequence` 永遠回傳 `false`。
- **型別/邊界:** 未驗證序列嚴格遞增與元素為正整數，對非法序列無法正確攔截。
- **輸出格式:** 缺少 `Case #X:` 編號；空行邏輯為「每筆之前印」而非「每筆之後印」，最後一筆缺少空行；輸入終止條件為哨兵值 `0` 而非 EOF。

### Correct Code

```cpp
#include <iostream>
#include <vector>
#include <set>
using namespace std;

class B2Sequence {
public:
    static bool isB2Sequence(vector<int> sequence) {
        set<int> verify_sequence;
        for (int i = 0; i < sequence.size(); i++) {
            // 修正：j 從 i 開始，涵蓋 i == j（即 2*b_i）的情況
            for (int j = i; j < sequence.size(); j++) {
                int sum = sequence[i] + sequence[j];
                if (verify_sequence.count(sum)) return false;
                verify_sequence.insert(sum);
            }
        }
        return true;
    }
};

int main() {
    int test_case, n, count = 1; // 修正：count 初始化為 1

    // 修正：以 EOF 作為終止條件
    while (cin >> test_case) {
        int size = test_case, current = 0;
        bool isUpper = true; // 修正：每筆測資重置狀態
        vector<int> sequence;

        while (size--) {
            cin >> n;
            // 前置驗證：嚴格遞增 + 正整數
            if (current >= n || n <= 0) isUpper = false;
            sequence.push_back(n);
            current = n;
        }

        // 修正：輸出 Case 編號，結果接在同一行
        cout << "Case #" << count++ << ": ";
        if (isUpper && B2Sequence::isB2Sequence(sequence)) {
            cout << "It is a B2-Sequence." << endl;
        } else {
            cout << "It is not a B2-Sequence." << endl;
        }
        // 修正：每筆測資後無條件印空行
        cout << endl;
    }
    return 0;
}
```

**Why it works:**
- **核心優化:** 將序列驗證拆為兩階段：前置檢查（嚴格遞增 + 正整數）與 pairwise sum 唯一性驗證，邏輯清晰且互不干擾。
- **穩健性:** 跨 test case 的狀態變數（`current`、`isUpper`）皆在迴圈內重置，避免污染；`set` 查詢取代線性搜尋，效率更佳；EOF 終止確保所有合法輸入均被處理。

---

## 6. Difference and Reflection

### Key Differences

| Item | Fail Code | Correct Code |
| :--- | :--- | :--- |
| **Input 終止** | 哨兵值 `test_case != 0` | EOF `while (cin >> test_case)` |
| **Vector 初始化** | `vector<int>(N)` + `push_back` 混用，前段塞 0 | `vector<int>` 空初始化 + 純 `push_back` |
| **序列合法性驗證** | 無前置驗證 | 讀入時即檢查嚴格遞增與正整數 |
| **Pairwise sum 範圍** | `j` 從 `i+1` 開始，遺漏 $i = j$ | `j` 從 `i` 開始，涵蓋 $2b_i$ |
| **輸出格式** | 缺 Case 編號，空行位置錯誤 | `Case #X:` 編號正確，每筆後無條件空行 |
| **跨 test case 狀態** | `isUpper`、`current` 未重置，污染後續測資 | 每筆測資開始時重置所有狀態變數 |

### Reflection

- **最大的失誤:** 在尚未完整閱讀題目輸入輸出規格的情況下就開始撰寫程式，導致輸入終止條件、輸出格式與 B2-Sequence 定義（$i \leq j$）三處同時出錯。這些都是讀題不夠仔細造成的問題，與演算法能力無關。
- **習得知識:**
  - `vector<int> v(n)` 與 `vector<int> v` 的語意差異：前者預先填充 n 個預設值，後者為空容器，不可混用 `push_back`。
  - `set` 適合用於查詢唯一性（`verify_sequence`），但不適合用於儲存需要保留重複元素語意的原始輸入序列。
  - 跨 test case 的狀態變數應在迴圈內宣告或明確重置，避免污染。
- **未來規劃:**
  1. 拿到題目後，先確認輸入終止條件（EOF / 哨兵值 / 固定筆數）再動筆。
  2. 對照 Sample Output 確認輸出格式（有無編號、空行位置）後再實作輸出邏輯。
  3. 仔細閱讀數學定義中的不等號方向（$i < j$ vs $i \leq j$），避免遺漏邊界情況。