# UVa 490 - Rotating Sentences

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 490
- **Problem Title:** Rotating Sentences
- **Problem Link:** [UVa 490](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=6&page=show_problem&problem=431)
- **Source Code (Correct/Accepted):** [UVa490.cpp](https://github.com/SWSekai/11402_CI002/blob/main/On-Site_Examinations/Week02_2_UVa490/src/UVa490.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 多行文字（最多 100 行，每行最多 100 個字元）。
- **Expected Output:** 將輸入的文字順時針旋轉 90 度後輸出。原第一行變成最右一列，原最後一行變成最左一列。
- **Rules/Constraints:** 旋轉後每一列的長度需對齊最長輸入行的長度，不足的部分以空格填充。
- **Core Task:** 將輸入文字視為字元矩陣，進行矩陣轉置並反轉行序後輸出。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 需要先讀取所有行，記錄最大長度以確定旋轉後的列數。
- 旋轉後新矩陣的每個位置 `[i][j]` 對應到原矩陣的哪個位置需要推導。

### Final Strategy
- **矩陣旋轉法：** 原行數為 $R$，最大行長為 $C$。旋轉後新行數為 $C$，新列數為 $R$。新矩陣第 $i$ 行第 $j$ 列對應原矩陣第 $(R-1-j)$ 行第 $i$ 列。若原位置超出該行長度則輸出空格。
- **為何可行：** 字元矩陣的旋轉本質上就是座標變換，與二維陣列的轉置加反轉相同。
- **邊界處理：** 從最後一行開始取字元，空位補空格。

## 4. Pseudocode

```text
START
1. INIT vector<string> sentences, max_length = 0
2. FOR each input line (getline):
    sentences.push_back(line)
    max_length = MAX(max_length, line.length())
3. FOR i = 0 TO max_length - 1:
    a. INIT result_line = ""
    b. FOR j = sentences.size() - 1 DOWNTO 0:
        IF i < sentences[j].length():
            result_line += sentences[j][i]
        ELSE:
            result_line += ' '
    c. PRINT result_line
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
class Rotating_Sentences {
public:
    static vector<string> rotate_sentences(const vector<string> &sentences, int max_length) {
        vector<string> result;
        for (int i = 0; i <= max_length - 1; i++) {
            string result_line;
            for (int j = sentences.size() - 1; j >= 0; j--) {
                result_line += (i < sentences[j].length() ? sentences[j][i] : ' ');
            }
            result.push_back(result_line);
        }
        return result;
    }
};
```
**Why it works:**
- 外層迴圈 $i$ 遍歷行內字元（0 到 max_length-1），內層迴圈 $j$ 從最後一行往前取字元，實現順時針旋轉。
- 使用三元運算子判斷是否超出該行長度，超出的部分補空格。
- 以 `vector<string>` 儲存結果，便於後續逐行輸出。

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 將輸入儲存為字串陣列後，從下到上遍歷行的每個字元位置，形成旋轉效果 |
| **Edge Cases** | 不同行長度不同，需補空格；使用 `max_length` 確保旋轉後無遺漏字元 |

### Reflection
- **座標轉換思維：** 處理矩陣旋轉問題時，先畫圖推導座標映射關係，能避免索引錯誤。
- **補空格策略：** 旋轉後短行對應的位置需要補空格，且補空格不會改變輸出外觀，是處理不對等長度行的重要技巧。
- **容器選擇：** 使用 `vector<string>` 儲存多行字串，既方便讀取又便於動態擴展，比固定大小的二維陣列更靈活。
