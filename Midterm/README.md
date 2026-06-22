# Midterm Examination

## UVa 11332 - Summing Digits

### 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 11332
- **Problem Title:** Summing Digits
- **Problem Link:** [UVa 11332](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2307)
- **Source Code (Correct/Accepted):** [UVa11332.cpp](https://github.com/SWSekai/11402_CI002/blob/main/Midterm/src/UVa11332.cpp)

### 2. Problem Statement in My Own Words

- **Input:** 一個正整數 $N$（多筆測資），以 $0$ 結束輸入。
- **Expected Output:** 輸出 $N$ 的不斷加總 digits 直到剩下一位數的結果。
- **Rules/Constraints:** 不斷將每位數相加，直到結果只剩下一位數。例如 $12345 \rightarrow 1+2+3+4+5=15 \rightarrow 1+5=6$。
- **Core Task:** 實作數位根（Digital Root）的計算。

### 3. Thinking Logic and Solution Strategy

#### Initial Thoughts
- 直覺使用巢狀迴圈重複加總 digits，直到數字小於 10。
- 需要注意輸入可能較大，使用 `long long` 避免溢位。

#### Final Strategy
- **模擬法：** 外層 `while` 控制當結果 $\ge 10$ 時繼續，內層 `while` 分解每位數加總。
- **邊界處理：** 當 $N=0$ 時結束程式；單一位數直接回傳。

### 4. Pseudocode

```text
START
1. READ input (N)
2. IF N == 0, EXIT
3. WHILE N >= 10:
     tmp = N, sum = 0
     WHILE tmp > 0:
         sum += tmp % 10
         tmp /= 10
     N = sum
4. PRINT N
5. GOTO 1
END
```

### 5. Correct Code

```cpp
static long long summing_digit(long long& input) {
    long long ans = input;
    while (ans >= 10) {
        long long tmp = ans;
        ans = 0;
        while (tmp >= 1) {
            ans += tmp % 10;
            tmp /= 10;
        }
    }
    return ans;
}
```
**Why it works:**
- 透過簡單的模擬法重複加總 digits，邏輯直觀且正確。
- 使用 `long long` 確保不會溢位。

### 6. Reflection

- **Key Point:** 數位根問題可暴力模擬，也有數學公式 $1 + (N-1) \bmod 9$。
- **Lesson:** 理解問題後先思考是否有數學捷徑，但模擬法永遠是可靠的基礎。

---

## UVa 12250 - Language Detection

### 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 12250
- **Problem Title:** Language Detection
- **Problem Link:** [UVa 12250](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=3398)
- **Source Code (Correct/Accepted):** [UVa12250.cpp](https://github.com/SWSekai/11402_CI002/blob/main/Midterm/src/UVa12250.cpp)

### 2. Problem Statement in My Own Words

- **Input:** 多行字串，每行代表一種語言的問候語，以 `#` 結束輸入。
- **Expected Output:** 根據輸入的字串判斷對應的語言，輸出 `Case X: LANGUAGE`。
- **Rules/Constraints:** 對照表：HELLO→ENGLISH, HOLA→SPANISH, HALLO→GERMAN, BONJOUR→FRENCH, CIAO→ITALIAN, ZDRAVSTVUJTE→RUSSIAN。若無匹配則輸出 UNKNOWN。
- **Core Task:** 字串比對與多筆測資 Case 編號輸出。

### 3. Thinking Logic and Solution Strategy

#### Initial Thoughts
- 簡單的 if-else 字串比較，配合 counter 輸出 Case 編號。

#### Final Strategy
- **暴力比對：** 使用 if-else if 鏈逐一比對字串。
- **邊界處理：** 遇到 `#` 結束輸入，無匹配時回傳 UNKNOWN。

### 4. Pseudocode

```text
START
1. SET count = 1
2. READ input string S
3. WHILE S != "#":
     a. IF S matches any known greeting, PRINT "Case count: Language"
     b. ELSE PRINT "Case count: UNKNOWN"
     c. count++, READ next S
END
```

### 5. Correct Code

```cpp
static string language_detection(string input) {
    if (input == "HELLO") return "ENGLISH";
    else if (input == "HOLA") return "SPANISH";
    else if (input == "HALLO") return "GERMAN";
    else if (input == "BONJOUR") return "FRENCH";
    else if (input == "CIAO") return "ITALIAN";
    else if (input == "ZDRAVSTVUJTE") return "RUSSIAN";
    else return "UNKNOWN";
}
```
**Why it works:**
- 直接的字串比對，邏輯簡單明確，時間複雜度 $O(1)$。

### 6. Reflection

- **Key Point:** 字串比對基礎題，重點在於 Case 編號的正確遞增與輸出格式。
- **Lesson:** 對於這類對應表問題，也可使用 `map<string, string>` 提升可擴展性。
