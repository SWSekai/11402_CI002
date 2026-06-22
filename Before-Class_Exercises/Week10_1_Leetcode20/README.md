# LeetCode 20 - Valid Parentheses

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 20
- **Problem Title:** Valid Parentheses
- **Problem Link:** https://leetcode.com/problems/valid-parentheses/
- **Source Code (Correct/Accepted):** [leetcode20_Valid_Parentheses.cpp](https://github.com/SWSekai/11402_CI002/blob/main/Before-Class_Exercises/Week10_1_LeetCode20/src/leetcode20_Valid_Parentheses.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 一個僅包含 `'('`、`')'`、`'{'`、`'}'`、`'['`、`']'` 的字串 `s`。
- **Expected Output:** `true` 如果括號的配對順序是合法的，否則 `false`。
- **Rules/Constraints:** 左括號必須被相同類型的右括號以正確順序關閉；每個右括號都有一個對應的同類型左括號。
- **Core Task:** 使用棧 (Stack) 資料結構來匹配括號。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 括號匹配是典型的 Stack 應用題。
- 需要注意邊界情況：只有左括號、只有右括號、交錯的括號等。

### Final Strategy
- **演算法：** 使用 `vector<char>` 模擬 Stack，並搭配 `map` 儲存括號對應關係。
- **步驟：**
  1. 遍歷字串每個字元。
  2. 若是左括號 `( { [`，直接 push 進 stack。
  3. 若是右括號 `) } ]`：
     - 若 stack 為空，則不合法，回傳 false。
     - 取 stack 頂部元素，與 map 中對應的左括號比對。若匹配則 pop，否則 false。
  4. 遍歷結束後，檢查 stack 是否為空（不允許遺留未匹配的左括號）。
- **為什麼可行：** Stack 的 LIFO 特性天然符合括號巢狀匹配的順序。
- **邊界處理：** 空字串回傳 true；只有右括號時 stack 為空立即回 false。

## 4. Pseudocode

```text
START
1. 建立 map：')' -> '(', '}' -> '{', ']' -> '['
2. 建立 stack (vector<char>)
3. 遍歷 s 中每個字元 c：
   a. 若 c 是左括號，push 進 stack
   b. 若 c 是右括號：
      i.   若 stack 為空，回傳 false
      ii.  取 stack.back() 與 map[c] 比對
      iii. 若匹配則 pop，否則回傳 false
4. 回傳 stack.empty()
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
class Solution {
public:
    bool isValid(string s) {
        vector<char> stack;
        map<char, char> paren_map = {
            {')', '('},
            {'}', '{'},
            {']', '['}
        };
        for (char c : s) {
            if (c == ')' || c == '}' || c == ']') {
                if (stack.empty()) return false;
                char top = stack.back();
                if (top == paren_map[c]) stack.pop_back();
                else return false;
            } else {
                stack.push_back(c);
            }
        }
        return stack.empty();
    }
};
```
**Why it works:**
- 用 `map` 簡化右括號與左括號的比對邏輯；用 `vector` 模擬 stack 的 push/pop 行為。

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | Stack + Hash Map 儲存括號對應，避免多層 if-else |
| **Edge Cases** | 先檢查 stack 是否為空再取 top；遍歷結束後檢查 stack 是否為空 |

### Reflection
- 括號匹配是 Stack 最經典的應用。使用 map 儲存對應關係可以讓程式碼更具可讀性與可擴展性，新增括號類型時只需修改 map 即可。
