# UVa 10008 - What's Cryptanalysis?

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 10008
- **Problem Title:** What's Cryptanalysis?
- **Problem Link:** [UVa 10008 - What's Cryptanalysis?](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=949)
- **Source Code (Correct/Accepted):** [UVa10008.cpp](https://github.com/SWSekai/11402_CI002/blob/main/On-Site_Examinations/Week05_2_UVa10008/UVa10008.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 第一行為正整數 $n$，代表接下來有 $n$ 行文字。每行文字包含零個或多個字元（可能包含空白、標點符號、數字等）。
- **Expected Output:** 輸出所有出現過的英文字母（不分大小寫）及其出現次數，按出現次數由高到低排序；次數相同時，按字母順序 (A-Z) 排序。每行一個字母（大寫）和次數，以空格分隔。
- **Rules/Constraints:** 只統計英文字母 (A-Z, a-z)，大小視為相同；非字母字元全部忽略。
- **Core Task:** 統計每行文字中各字母的出現頻率，並依指定規則排序輸出。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 需要一個大小為 26 的整數陣列來統計 A-Z 的出現次數。
- 需要一個自訂排序規則：先按次數降序，次數相同則按字母升序。

### Final Strategy
- **統計階段：** 逐行讀取文字，對每個字元判斷是否為字母，若是則轉為大寫並更新對應的計數陣列。
- **排序階段：** 建立一個結構體陣列（包含字母和次數），僅收錄出現次數大於 0 的字母，再依自訂比較函式排序。
- **比較函式：** `compareLetters` 先比較次數（降序），次數相同則比較字母（升序）。
- **邊界處理：** 使用 `cin.ignore()` 吃掉第一行數字後的換行；使用 `getline` 讀取含空白的整行文字。

## 4. Pseudocode

```text
START
1. READ n (number of lines)
2. cin.ignore() to discard the newline after n
3. CREATE int counts[26] = {0}
4. FOR i = 1 TO n:
5.   READ a whole line (including spaces) into sentence
6.   FOR each character c IN sentence:
7.     IF c IS a letter:
8.       counts[toupper(c) - 'A']++
9. CREATE a list of Letter structs for counts[i] > 0
10.SORT the list by:
11.  primary: count DESC
12.  secondary: alphabet ASC
13.FOR each letter in the sorted list:
14.  PRINT letter and its count
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
struct Letter {
    char alpha;
    int count;
};

static bool compareLetters(const Letter& a, const Letter& b) {
    if (a.count != b.count)
        return a.count > b.count;
    return a.alpha < b.alpha;
}

void analyze(const string& text) {
    for (char c : text) {
        if (isalpha(c))
            counts[toupper(c) - 'A']++;
    }
}

void printResults() {
    vector<Letter> validLetters;
    for (int i = 0; i < 26; ++i) {
        if (counts[i] > 0)
            validLetters.push_back({ (char)('A' + i), counts[i] });
    }
    sort(validLetters.begin(), validLetters.end(), compareLetters);
    for (const auto& leaf : validLetters)
        cout << leaf.alpha << " " << leaf.count << endl;
}
```
**Why it works:**
- `isalpha` + `toupper` 確保非字母字元被忽略，且大小寫合併統計。
- 先過濾 `counts[i] > 0` 再排序，避免輸出未出現的字母。
- 自訂排序函式精準滿足題目要求：次數降序、字母升序。

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 以 26 格陣列統計 → 過濾非零項目 → 排序輸出，流程清晰 |
| **Edge Cases** | 使用 `cin.ignore()` 處理數字後的換行；`getline` 讀取含空白的行 |

### Reflection
- **穩定排序的替代方案：** 自訂比較函式比依賴穩定排序更可靠，因為題目要求的是明確的 lexicographical order 而非 stable sort 的保留原序。
- **輸入處理的細節：** 混合使用 `cin >>` 和 `getline` 時務必注意換行字元的殘留，這是 C++ 輸入常見的陷阱。
