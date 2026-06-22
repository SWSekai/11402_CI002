# UVa 12503 - Robot Instructions

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 12503
- **Problem Title:** Robot Instructions
- **Problem Link:** [UVa 12503](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=3947)
- **Source Code (Correct/Accepted):** [UVa12503.cpp](https://github.com/SWSekai/11402_CI002/blob/main/On-Site_Examinations/Week04_2_UVa12503/src/UVa12503.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 第一行為測資筆數 T。每筆測資先給一個整數 n (1 ≤ n ≤ 100)，接下來 n 行每行為一個指令：「LEFT」（左移一格）、「RIGHT」（右移一格）、或「SAME AS i」（與第 i 個指令相同）。
- **Expected Output:** 對每筆測資，輸出機器人執行完所有指令後的最終位置。
- **Rules/Constraints:** 機器人起始位置為 0。指令 i 保證不會大於當前指令編號。每筆測資結束後機器人重置為原點。
- **Core Task:** 模擬機器人根據指令在 x 軸上移動，計算最終座標。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 直接根據指令模擬移動即可。
- 需要記錄每個指令的移動值（+1 或 -1），以處理 SAME AS 指令。

### Final Strategy
- **模擬法：** 用一個 vector 記錄每個指令對應的移動值，遇到 LEFT 存 -1、RIGHT 存 +1、SAME AS i 則查詢歷史記錄的對應值。
- **為什麼可行：** n ≤ 100，O(n) 即可完成。直接模擬即可，無需複雜演算法。
- **邊界處理：** 使用 `getline` 讀取含空格的指令行。使用 `stringstream` 解析 SAME AS i 中的最後一個數字。

## 4. Pseudocode

```text
START
1. 讀入 T
2. FOR 每筆測資:
    a. 讀入 n
    b. location = 0
    c. request_log = [] (空陣列)
    d. FOR i = 1 TO n:
        讀入一行指令
        IF "LEFT": move = -1
        ELSE IF "RIGHT": move = 1
        ELSE: 解析出數字 idx, move = request_log[idx-1]
        location += move
        request_log 加入 move
    e. 輸出 location
END
```

## 5. Correct Code

```cpp
class Robot_instruction {
public:
    static int parseInstruction(string cmd, const vector<int>& history) {
        if (cmd == "LEFT") return -1;
        else if (cmd == "RIGHT") return 1;
        else {
            stringstream ss(cmd);
            string temp, last;
            while (ss >> temp) last = temp;
            return history[stoi(last) - 1];
        }
    }
};
```
**Why it works:**
- LEFT/RIGHT 直接對應 -1/+1，直觀易懂。
- SAME AS i 透過 stringstream 取出最後的數字 i，查詢 history[i-1] 即可。
- 將指令解析封裝在類別中，邏輯清晰。

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 模擬機器人移動，記錄歷史指令以便查詢 |
| **Edge Cases** | 使用 getline 處理含空格字串，使用 stringstream 解析數字 |

### Reflection
- **字串解析技巧：** SAME AS i 的格式需要擷取最後的數字，利用 stringstream 逐字讀取並保留最後一個 token 是簡潔的做法。
- **歷史記錄的必要性：** 因為後續指令可能參考前面的指令，必須用陣列儲存每個指令的實際移動值。
- **模擬題的特性：** 直接按照題目規則執行即可，關鍵在於正確處理輸入格式。
