# UVa 10931 - Parity

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 10931
- **Problem Title:** Parity
- **Problem Link:** [https://onlinejudge.org/external/109/10931.pdf](https://onlinejudge.org/external/109/10931.pdf)
- **Source Code (Correct/Accepted):** [UVa10931.cpp](https://github.com/SWSekai/11402_CI002/blob/main/On-Site_Examinations/Week06_1_UVa10931/UVa10931.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 多個整數 I（1 ≤ I ≤ 2147483647），每行一個，以 0 結束。
- **Expected Output:** 對每個非零輸入，輸出 "The parity of B is P (mod 2)."，其中 B 是 I 的二進位表示（不含前導零），P 是 B 中 1 的個數（即 parity）。
- **Rules/Constraints:** I 為正整數，最大值為 2^31-1。輸入以 0 結束。
- **Core Task:** 將整數轉換為二進位字串，計算其中的 1 的個數（偶數個為 even parity，奇數個為 odd parity）。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 使用短除法反覆除以 2，記錄餘數即可得到二進位表示。
- 在轉換的同時可以順便計算 1 的個數。

### Final Strategy
- 用 while 迴圈不斷對數字 `num % 2` 取得最低位，`num / 2` 縮小數字，將餘數存入 vector。
- 轉換完成後 vector 中儲存的是從低位到高位的二進位，需反向輸出。
- 統計 `num % 2 == 1` 的次數即為 parity。

## 4. Pseudocode

```text
START
WHILE read I AND I != 0:
    vector<int> bits
    int count = 0
    WHILE I > 0:
        bits.push_back(I % 2)
        IF I % 2 == 1: count++
        I = I / 2
    PRINT "The parity of "
    FOR i FROM bits.size()-1 DOWN TO 0:
        PRINT bits[i]
    PRINT " is " << count << " (mod 2)."
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
void Uva10931(int num) {
    int parity = 0;
    vector<int> bits;
    while (num != 0) {
        bits.push_back(num % 2);
        if (num % 2 == 1) parity++;
        num /= 2;
    }
    cout << "The parity of ";
    for (int i = bits.size() - 1; i >= 0; i--)
        cout << bits[i];
    cout << " is " << parity << " (mod 2)." << endl;
}
```
**Why it works:**
- 標準的十進位轉二進位：每次取 mod 2 得到最低位，除以 2 去掉最低位
- 統計 1 的個數即為 parity（mod 2 下的值）

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 使用短除法轉二進位，同時統計 parity，簡單直觀 |
| **Edge Cases** | I = 1 時二進位為 "1"，parity = 1；輸入以 0 結束 |

### Reflection
- 這是一道基礎題，重點在於熟悉二進位轉換的實作及 parity 的定義
- 注意 while 迴圈條件為 `num != 0`，避免輸出前導零
