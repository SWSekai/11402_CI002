# UVa 10035 - Primary Arithmetic

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 10035
- **Problem Title:** Primary Arithmetic
- **Problem Link:** [UVa 10035](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=12&page=show_problem&problem=976)
- **Source Code (Correct/Accepted):** [UVa10035.cpp](https://github.com/SWSekai/11402_CI002/blob/main/On-Site_Examinations/Week01_2_UVa10035/src/UVa10035.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 每行包含兩個無號整數 $a$ 和 $b$（最多 $10$ 位數），以 `0 0` 作為結束。
- **Expected Output:** 輸出兩個數字相加時產生的進位次數，格式為 "No carry operation."、"1 carry operation." 或 "X carry operations."。
- **Rules/Constraints:** 每次加法最多進位 $1$，需計算每一位的進位總次數。
- **Core Task:** 模擬直式加法，統計進位發生的次數。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 將兩個數字從最低位開始逐位相加，判斷是否產生進位。
- 需要追蹤前一位的進位對當前位的影響。

### Final Strategy
- **逐位模擬法：** 使用 while 迴圈，每次取 $a$ 和 $b$ 的末位數字進行相加，加上前一輪的進位值，若總和大於等於 10 則進位計數加 1。
- **為何可行：** 直式加法的本質就是逐位處理，模擬方式完全符合題意。
- **邊界處理：** 當 $a$ 和 $b$ 位數不同時，較短數字的較高位視為 0。

## 4. Pseudocode

```text
START
1. READ a, b (while a != 0 || b != 0)
2. SET total_carries = 0, carry = 0
3. WHILE a != 0 || b != 0:
    IF (a % 10) + (b % 10) + carry >= 10:
        total_carries++
        carry = 1
    ELSE:
        carry = 0
    a = a / 10
    b = b / 10
4. IF total_carries == 0: PRINT "No carry operation."
   ELSE IF total_carries == 1: PRINT "1 carry operation."
   ELSE: PRINT total_carries + " carry operations."
5. REPEAT from step 1
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
class CarryCalculator {
public:
    static int calculateCarryCount(unsigned int a, unsigned int b, int base=10) {
        int total_carries = 0;
        int carry = 0;
        while (a != 0 || b != 0) {
            if ((a % base) + (b % base) + carry >= base) {
                total_carries++;
                carry = 1;
            } else carry = 0;
            a /= base;
            b /= base;
        }
        return total_carries;
    }
};
```
**Why it works:**
- 精確模擬直式加法，每次取末位相加並判斷進位。
- 用 `carry` 變數追蹤前一輪進位，正確傳遞到下一位。
- 迴圈條件 `a != 0 || b != 0` 確保處理完所有位數。

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 逐位取出數字，加上進位判斷是否 >= 10，統計進位次數 |
| **Edge Cases** | $a=b=0$ 為終止條件；位數不同時較高位自動視為 0；進位後 `carry` 設為 1 而不是加上次數 |

### Reflection
- **進位邏輯：** 每次進位後 `carry` 只需設為 1（而非加上進位次數），因為最大 9+9+1=19 只會進位 1。
- **格式化輸出：** 注意單複數的區別，"carry operation" 與 "carry operations" 的字尾不同，需根據次數調整。
- **模數運算的巧妙：** 利用 `% 10` 和 `/ 10` 可輕鬆從右到左處理每一位，無需先轉換為字串。
