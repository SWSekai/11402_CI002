# UVa 10420 - List of Conquests

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 10420
- **Problem Title:** List of Conquests
- **Problem Link:** [UVa 10420 - List of Conquests](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1361)
- **Source Code (Correct/Accepted):** [UVa10420.cpp](https://github.com/SWSekai/11402_CI002/blob/main/On-Site_Examinations/Week05_3_UVa10420/src/UVa10420.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 第一行為整數 $n$，表示征服記錄的筆數。接下來 $n$ 行，每行包含一個國家名稱和一個女性名字（名字可能包含多個單字，例如 "Mary Jane"），以空格分隔。
- **Expected Output:** 按國家名稱的字母順序（lexicographical order）輸出每個國家及被征服的女性人數，以空格分隔。
- **Rules/Constraints:** 國家名稱不含空格；女性名字可能包含空格且對統計無關（只需統計國家出現次數）。
- **Core Task:** 統計每個國家出現的次數，並按國家名稱字母排序輸出。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 需要一個能根據國家名稱快速累加計數的資料結構，`std::map<std::string, int>` 是最直接的選擇。
- 女性名字對結果沒有影響，讀取時可以忽略。

### Final Strategy
- **使用 std::map：** map 會自動按 key（國家名稱）的字母順序排序，遍歷時即為題目要求的輸出順序。
- **輸入處理：** 讀取國家名稱後，使用 `getline` 讀取該行剩下的部分（女性名字）並直接拋棄。
- **輸出：** 遍歷 map，輸出 `country + " " + count`。
- **邊界處理：** 注意混合使用 `cin >>` 與 `getline` 時要用 `cin.ignore()` 或 `getline` 吃掉換行；國家名稱和女性名字之間以空格分隔。

## 4. Pseudocode

```text
START
1. READ n
2. CREATE map<string, int> conquests (key = country, value = count)
3. FOR i = 1 TO n:
4.   READ country (string without spaces)
5.   IGNORE the rest of the line (woman's name)
6.   conquests[country]++
7. FOR each (country, count) IN conquests:
8.   PRINT country + " " + count
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    int n;
    cin >> n;
    cin.ignore();  // discard the newline after n

    map<string, int> conquests;
    while (n--) {
        string country;
        cin >> country;
        string rest;
        getline(cin, rest);  // read and ignore woman's name
        conquests[country]++;
    }

    for (const auto& entry : conquests) {
        cout << entry.first << " " << entry.second << endl;
    }
}
```
**Why it works:**
- `std::map` 自動以字母順序儲存 key，無須額外排序。
- `cin >> country` 讀取到第一個空格為止（即國家名稱），`getline(cin, rest)` 讀取該行剩餘部分（女性名字）並忽略，處理方式簡潔正確。

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 使用 `map<string, int>` 自動計數並排序，無需手動實作排序邏輯 |
| **Edge Cases** | 用 `cin.ignore()` 避免數字後的換行殘留；女性名字可能含多個單字，用 `getline` 一次讀完 |

### Reflection
- **選對資料結構事半功倍：** `std::map` 同時解決了「計數」和「排序」兩個需求，是此題的最佳選擇。
- **輸入處理的連鎖效應：** `cin >>` 讀取字串後游標停在空格前，必須用 `getline` 吃掉該行剩餘內容（包含空格），否則下一次 `cin >>` 會讀到空字串。理解 `cin` 和 `getline` 的交互行為是這類題目的關鍵。
