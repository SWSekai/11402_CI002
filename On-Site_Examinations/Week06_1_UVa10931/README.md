# UVa 10931 - Parity

## 1. Problem Information

- **Platform:** UVa Online Judge
- **Problem ID:** 10931
- **Problem Title:** Parity
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1872
- **Source Code (Correct/Accepted):** [UVa10931.cpp](https://github.com/SWSekai/11402_CI002/blob/main/On-Site_Examinations/Week06_1_UVa10931/src/UVa10931.cpp)

---

## 2. Problem Statement in My Own Words

給定一個正整數，將其轉換為二進位表示，並計算其中 `1` 的個數（即奇偶校驗位，parity）。

- **Input:** 每行一個正整數 `num`（`num > 0`），以 `0` 作為終止輸入的信號。
- **Expected Output:** 每筆輸入對應一行輸出，格式固定為：
  `The parity of [二進位字串] is [1的個數] (mod 2).`
- **Rules/Constraints:**
  - 輸入以 `0` 結尾，`0` 本身不處理也不輸出。
  - 二進位字串不需補前置零，從最高有效位開始輸出。
  - 輸出字串中 `(mod 2)` 前後格式必須完全符合，包含空格。
- **Core Task:** 將整數轉二進位，統計 `1` 的個數，依照指定格式輸出。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- **初步思路:** 直覺上用除以 2 取餘數的方式逐位提取二進位各位元，存入 `vector`，再反向輸出即可重組原本的二進位字串。統計 `1` 的個數就是 parity。
- **初期難點:**
  - 除 2 取餘的順序是從 LSB（最低有效位）到 MSB（最高有效位），輸出時必須反向。
  - 輸出格式完全固定，需逐字元比對題目 sample output，空格錯一個即為 Presentation Error。

### Final Strategy

- **採用方法:** 迭代除法提取二進位位元，存入 `vector<int>`，輸出時反向遍歷；以線性掃描統計 `1` 的個數。
- **可行性分析:** 輸入為正整數（`int` 範圍），二進位位數最多 31 位，時間複雜度為 $O(\log N)$，空間複雜度 $O(\log N)$，完全不存在 TLE 或 Overflow 風險。
- **邊界處理:**
  - `num = 0`：直接作為終止條件，不進入處理流程。
  - `num = 1`：二進位為 `1`，parity 為 1，邊界最小正整數，正常處理。

---

## 4. Pseudocode

```text
START
1. 讀入 num
2. WHILE num != 0:
   a. 呼叫 toBinary(num)：
      - 初始化空 vector res
      - WHILE num > 0:
          res.push_back(num % 2)
          num /= 2
      - RETURN res
   b. 呼叫 parityToModTwo(binary)：
      - 初始化 count = 0
      - FOR each bit in binary:
          IF bit == 1: count++
      - RETURN count
   c. 輸出 "The parity of "
   d. 反向輸出 binary 各位元（從 MSB 到 LSB）
   e. 輸出 " is [parity] (mod 2)."
   f. 讀入下一個 num
END
```

---

## 5. Fail Code vs Correct Code

### Fail Code

```cpp
// 輸出格式錯誤版本
cout << " is " << parity << " (mod2)." << endl;
//                                ^ 缺少空格，應為 "(mod 2)"
```

**Why it failed:**
- **效率問題:** 無效率問題，邏輯本身正確。
- **型別/邊界:** 無型別或邊界問題。
- **邏輯缺陷:** 輸出字串 `(mod2)` 與題目要求的 `(mod 2)` 差了一個空格，導致 Online Judge 判定 Presentation Error。本地執行因肉眼難以察覺空格差異，表現上無異常。

### Correct Code

```cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Parity {
public:
    static vector<int> toBinary(int num) {
        vector<int> res;
        while (num > 0) {
            res.push_back(num % 2);
            num /= 2;
        }
        return res;
    }

    static int parityToModTwo(vector<int> num) {
        int count = 0;
        for (int i = 0; i < num.size(); i++) {
            if (num[i] == 1) count++;
        }
        return count;
    }
};

int main() {
    int num;
    while (cin >> num && num != 0) {
        vector<int> binary = Parity::toBinary(num);
        int parity = Parity::parityToModTwo(binary);

        cout << "The parity of ";
        for (int i = binary.size() - 1; i >= 0; i--) {
            cout << binary[i];
        }
        // 修正點：(mod 2) 中間補上空格
        cout << " is " << parity << " (mod 2)." << endl;
    }
    return 0;
}
```

**Why it works:**
- **核心優化:** 將 `(mod2)` 修正為 `(mod 2)`，與題目 sample output 完全吻合，消除 Presentation Error。
- **穩健性:** `while (cin >> num && num != 0)` 確保 `0` 作為正確終止條件，不產生多餘輸出；`vector` 反向輸出正確重組 MSB-first 的二進位字串。

---

## 6. Difference and Reflection

### Key Differences

| Item | Fail Code | Correct Code |
| :--- | :--- | :--- |
| **Logic** | 邏輯完全正確 | 邏輯完全正確 |
| **Edge Cases** | 正常處理 | 正常處理 |
| **Output Handling** | `(mod2)` 缺少空格，Presentation Error | `(mod 2)` 與題目格式完全一致 |
| **Other** | 本地測試無法察覺格式差異 | 需逐字元比對 sample output 才能發現 |

### Reflection

- **最大的失誤:** 沒有在提交前逐字元比對題目 sample output 的每一個字元，包含空格與標點，導致格式錯誤卻在本地毫無警訊。
- **習得知識:** Presentation Error 與 Wrong Answer 的本質差異——前者是「答案對但格式錯」，後者是「答案本身錯誤」。Online Judge 對輸出格式的要求是逐字元嚴格比對，任何多餘或缺漏的空格都會被判 PE，而本地終端機輸出完全無法反映這個差異。
- **未來規劃:** 每次提交前建立一個固定的 Output Format Checklist：(1) 將自己的輸出與題目 sample output 並排逐行逐字元核對；(2) 特別留意括號內的空格、句點、大小寫；(3) 確認每行結尾的換行方式一致。