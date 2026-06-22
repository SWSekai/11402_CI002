# UVa 10062 - Tell Me the Frequencies!

## 1. Problem Information

- **Platform:** UVa Online Judge
- **Problem ID:** 10062
- **Problem Title:** Tell Me the Frequencies!
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1003
- **Source Code (Correct/Accepted):** [UVa10062.cpp](https://github.com/SWSekai/11402_CI002/blob/main/On-Site_Examinations/Week06_2_UVa10062/src/UVa10062.cpp)

---

## 2. Problem Statement in My Own Words

給定若干行字串，統計每行中各 ASCII 字元出現的頻率，並依照特定排序規則輸出。

- **Input:** 多行字串，每行為一筆測資，直到 EOF 為止。字元範圍涵蓋完整 ASCII（包含空白等可見與不可見字元）。
- **Expected Output:** 針對每行，輸出「字元的 ASCII 碼 + 該字元的出現頻率」，每筆輸出佔一行；每兩筆測資的輸出之間以一個空行分隔，最後一筆後面不加空行。
- **Rules/Constraints:**
  - 排序優先順序：先依**頻率升冪**排序；頻率相同時，依**ASCII 碼降冪**排序。
  - 頻率為 0 的字元不輸出。
  - 多筆測資之間有空行，但最後一筆之後無空行（Presentation Error 的關鍵點）。
- **Core Task:** 統計字元頻率後，依雙重排序規則輸出，並精確控制多筆測資間的空行格式。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- **初步思路:** 建立一個大小為 128 的 `vector<int>` 對應 ASCII 字元集，遍歷字串逐一計數，接著用雙層迴圈掃描輸出：外層跑頻率值 `i`，內層跑字元索引 `j`，符合條件就輸出。
- **初期難點:**
  - 排序規則為雙條件：頻率升冪 + ASCII 碼降冪，用暴力雙層迴圈能模擬排序，但內層 `j` 的遍歷方向必須正確（從大到小才能模擬 ASCII 降冪）。
  - 頻率迴圈上界若用 `< str.length()`，會漏掉「整行只有一種字元」的情況（頻率恰好等於字串長度）。
  - 多筆測資的空行格式需精確控制，不能在最後一筆後多加空行，否則會產生 Presentation Error。

### Final Strategy

- **採用方法:** 大小為 128 的頻率陣列 + 雙層暴力掃描模擬排序（外層頻率升冪、內層 ASCII 降冪）。
- **可行性分析:** ASCII 字元集固定為 128，字串長度最多也不過數百，雙層迴圈的時間複雜度為 $O(N \times 128)$，其中 $N$ 為字串長度，在此題規模下完全可行，不需要額外的排序資料結構。
- **邊界處理:**
  - 頻率迴圈上界改為 `<= str.length()`，確保最大頻率值不被跳過。
  - 內層 `j` 從 `res.size() - 1` 往 `0` 遍歷，正確實現 ASCII 降冪。
  - 使用 `flag_for_first_input` 旗標，確保空行只出現在兩筆測資之間，而非每筆後面都加。

---

## 4. Pseudocode

```text
START
1. 初始化 flag_for_first_input = true

2. WHILE 能從標準輸入讀取一行 str：
   a. 若 flag_for_first_input 為 false，先輸出一個空行
   b. 建立大小 128 的頻率陣列 res，全部初始化為 0
   c. 遍歷 str 中每個字元 c，執行 res[c]++
   d. FOR i 從 1 到 str.length()（含）：
        FOR j 從 127 到 0（含）：
          IF res[j] == i：
            輸出 j 與 res[j]
   e. 將 flag_for_first_input 設為 false

END
```

---

## 5. Fail Code vs Correct Code

### Fail Code

```cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TellMeTheFrequencies {
public:
    static void processInput() {
        string str;
        while (getline(cin, str)) {
            vector<int> res(128, 0);

            for (char c : str) {
                res[c]++;
            }

            // 缺陷一：上界用 < str.length()，漏掉最大頻率值
            for (int i = 1; i < str.length(); i++) {
                // 缺陷二：j 從小到大，ASCII 碼應為降冪，方向錯誤
                for (int j = 0; j < res.size(); j++) {
                    if (res[j] == i) {
                        cout << j << " " << res[j] << endl;
                    }
                }
            }
            // 缺陷三：每筆後面無條件加空行，最後一筆會多出空行
            cout << endl;
        }
    }
};

int main() {
    TellMeTheFrequencies::processInput();
    return 0;
}
```

**Why it failed:**
- **型別／邊界:** 頻率迴圈上界為 `< str.length()`，當字串只包含單一字元時（頻率 = 字串長度），該字元永遠不會被輸出，產生 Wrong Answer。
- **邏輯缺陷:** 內層 `j` 從 0 往上跑，輸出順序為 ASCII 升冪，與題目要求的降冪完全相反，Wrong Answer。
- **輸出格式:** 每筆測資後無條件輸出空行，最後一筆後多一個空行，產生 Presentation Error。

### Correct Code

```cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TellMeTheFrequencies {
public:
    static void printFrequencies(const string& str) {
        vector<int> res(128, 0);
        for (char c : str) {
            res[c]++;
        }
        // 修正一：上界改為 <= str.length()，涵蓋最大頻率
        for (int i = 1; i <= str.length(); ++i) {
            // 修正二：j 從大到小，正確實現 ASCII 降冪
            for (int j = res.size() - 1; j >= 0; --j) {
                if (res[j] == i) {
                    cout << j << " " << res[j] << endl;
                }
            }
        }
    }
};

int main() {
    string str;
    bool flag_for_first_input = true;

    while (getline(cin, str)) {
        // 修正三：空行在「第二筆起」的前面輸出，避免最後一筆後多空行
        if (!flag_for_first_input) cout << endl;
        TellMeTheFrequencies::printFrequencies(str);
        flag_for_first_input = false;
    }
    return 0;
}
```

**Why it works:**
- **核心優化:** 三個缺陷逐一修正：頻率上界補齊、ASCII 遍歷方向反轉、空行改為「前置輸出」策略，三者缺一不可。
- **穩健性:** `flag_for_first_input` 旗標精確控制空行位置，無論輸入有幾筆，格式都符合題目要求；`<= str.length()` 確保極端情況（單一字元重複填滿整行）不被漏掉。

---

## 6. Difference and Reflection

### Key Differences

| Item | Fail Code | Correct Code |
| :--- | :--- | :--- |
| **頻率迴圈上界** | `i < str.length()`，漏掉最大頻率值 | `i <= str.length()`，完整涵蓋所有頻率 |
| **ASCII 輸出順序** | `j` 從 0 到 127（升冪），方向錯誤 | `j` 從 127 到 0（降冪），符合題意 |
| **空行控制** | 每筆後面無條件 `cout << endl`，末尾多空行 | 旗標判斷，空行只出現在兩筆之間 |
| **封裝結構** | 流程控制與輸出邏輯混在同一個 method | `main` 負責流程，class method 只處理單筆，職責分離 |

### Reflection

- **最大的失誤:** 沒有在動筆前仔細確認排序規則的方向性。「ASCII 降冪」這個細節在題目中明確標示，卻在實作時直接寫成升冪，屬於審題不夠仔細的問題。
- **習得知識:**
  - 輸出格式的空行控制有兩種策略：「後置空行」容易在最後一筆產生多餘空行；「前置空行 + 旗標」是更穩健的標準做法，應優先採用。
  - 頻率迴圈上界的 Off-by-one 錯誤是此類計數題的常見陷阱，需養成習慣：先問自己「最大值能被涵蓋嗎？」。
- **未來規劃:**
  - 拿到題目後，先列出輸出格式的所有細節（包含空行規則），再動手寫程式。
  - 排序規則涉及多個欄位時，在偽代碼中明確寫出每個欄位的升／降冪方向，避免實作時憑感覺寫反。
  - 完成初版後，先用「極端測資」手動驗證：單一字元填滿整行、只有一筆輸入、末筆輸出後是否多空行。