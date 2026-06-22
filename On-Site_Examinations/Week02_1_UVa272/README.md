# UVa 272 - TEX Quotes

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 272
- **Problem Title:** TEX Quotes
- **Problem Link:** [UVa 272](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=4&page=show_problem&problem=208)
- **Source Code (Correct/Accepted):** [UVa272.cpp](https://github.com/SWSekai/11402_CI002/blob/main/On-Site_Examinations/Week02_1_UVa272/src/UVa272.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 包含多行文字的輸入，每行可能包含雙引號 `"`。
- **Expected Output:** 將所有雙引號替換為 TEX 風格的左右引號：左引號用 `\`\`` （兩個反引號），右引號用 `''` （兩個單引號）。
- **Rules/Constraints:** 雙引號的出現順序必定是成對的：左、右、左、右……第一個 `"` 視為左引號，第二個視為右引號，依此類推。
- **Core Task:** 逐字元讀取輸入，遇到 `"` 時根據目前是左還是右來替換為對應的 TEX 引號。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 需要一個 flag 來記錄當前的引號狀態（左或右）。
- 逐字元處理，遇到 `"` 時切換狀態並輸出對應的替代字串。

### Final Strategy
- **狀態機法：** 使用一個 `bool flag` 標記當前是否應該輸出左引號（`false` = 左引號，`true` = 右引號）。遇到 `"` 時輸出對應字串並翻轉 flag。
- **為何可行：** 題目保證引號成對出現，只需交替替換即可。
- **多行處理：** flag 的生命週期必須跨越多行輸入，因此宣告在 main 中而非每次 getline 時重新設定。

## 4. Pseudocode

```text
START
1. SET flag = false
2. FOR each line (getline):
    a. FOR each character in line:
        IF char == '"' AND flag == false:
            PRINT "``"
            flag = true
        ELSE IF char == '"' AND flag == true:
            PRINT "''"
            flag = false
        ELSE:
            PRINT char
    b. PRINT newline
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
class TEX_Quotes {
public:
    static string replace_quotes(string& str, bool& flag) {
        string result;
        for (size_t i = 0; i <= str.length()-1; i++) {
            if (str[i] == '"' && flag == false) {
                result += "``";
                flag = true;
            }
            else if (str[i] == '"' && flag == true) {
                result += "''";
                flag = false;
            }
            else result += str[i];
        }
        return result;
    }
};
```
**Why it works:**
- 使用 `flag` 追蹤下一個引號的類型（左/右），保證交替輸出。
- flag 以 reference 傳遞，狀態可跨行保持。
- 非引號字元原封不動保留，不影響其他內容。

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 利用 bool flag 交替判斷左引號與右引號 |
| **Edge Cases** | flag 需跨行保持狀態，不能設為局部變數；引號可能出現在字串中任何位置 |

### Reflection
- **狀態設計：** 將一個簡單的布林變數作為狀態機的核心，是處理「交替模式」問題的經典做法。
- **跨行狀態：** 在處理多行輸入時，判斷 flag 應該在迴圈內還是迴圈外重置至關重要。本題的 flag 必須跨行，因此宣告在 main 中傳入函數。
- **+= 字串拼接：** 使用 `result += str[i]` 可以動態擴展結果字串，比預先分配空間更加靈活。
