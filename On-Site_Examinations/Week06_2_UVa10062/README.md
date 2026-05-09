# UVa 10062 - Tell me the frequencies!

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 10062
- **Problem Title:** Tell me the frequencies!
- **Problem Link:** [https://onlinejudge.org/external/100/10062.pdf](https://onlinejudge.org/external/100/10062.pdf)
- **Source Code (Correct/Accepted):** [UVa10062.cpp](https://github.com/SWSekai/11402_CI002/blob/main/On-Site_Examinations/Week06_2_UVa10062/UVa10062.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 多行文字（每行視為一筆測資），每行最大長度 1000，僅包含 ASCII 碼 32 之後及 128 之前的字元（即 ASCII 33~127）。以 EOF 結束。
- **Expected Output:** 對每行輸入，輸出出現過的 ASCII 字元之 ASCII 值及其頻率。輸出順序依頻率由小到大，若頻率相同則 ASCII 值大者優先輸出。每筆測資輸出後須空一行，但最後一筆後不要多空行。
- **Rules/Constraints:** 每行最長 1000 字元。忽略換行字元 \n 和 \r。
- **Core Task:** 統計每行中每個 ASCII 字元出現的次數，並按照指定排序規則輸出。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 使用大小為 128 的陣列來統計 ASCII 字元出現次數。
- 排序時需要將 (ASCII 值, 頻率) 作為 pair 存入 vector，再自訂排序規則。

### Final Strategy
- 每次讀取一整行（使用 `getline`），用大小為 128 的 int 陣列計數。
- 遍歷 ASCII 33~127，將頻率 > 0 的 (ascii, freq) 加入 vector。
- 使用自訂 comparator 排序：先依 freq 升序，若 freq 相同則依 ascii 降序。
- 注意輸出格式：兩筆測資之間空一行，最後一筆不空行。

## 4. Pseudocode

```text
START
bool first = true
WHILE read line:
    IF !first: PRINT blank line
    first = false
    int count[128] = {0}
    FOR each char c IN line:
        count[c]++
    vector<pair<int,int>> result
    FOR i = 33 TO 127:
        IF count[i] > 0:
            result.push_back({i, count[i]})
    SORT result:
        IF freq1 != freq2: freq1 < freq2
        ELSE: ascii1 > ascii2
    FOR each (ascii, freq) IN result:
        PRINT ascii << " " << freq
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
int freq[128] = {0};
for (char c : line) freq[c]++;
vector<pair<int,int>> v;
for (int i = 33; i <= 127; i++)
    if (freq[i] > 0)
        v.push_back({i, freq[i]});
sort(v.begin(), v.end(), [](auto &a, auto &b) {
    if (a.second != b.second) return a.second < b.second;
    return a.first > b.first;
});
```
**Why it works:**
- 陣列計數 O(n)，排序 O(m log m)（m ≤ 95 種字元），效率足夠
- 排序規則完全符合題目要求：頻率小優先，同頻率則 ASCII 大優先

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 用 int[128] 計數後篩選非零項目排序，避免不必要的處理 |
| **Edge Cases** | 輸出格式：每筆測資間空一行但最後一筆後不空行；忽略 \n, \r |

### Reflection
- 輸出格式控制是本題最容易出錯的地方，必須仔細處理 blank line 的時機
- 自訂排序 lambda 時注意 comparator 需滿足 strict weak ordering
