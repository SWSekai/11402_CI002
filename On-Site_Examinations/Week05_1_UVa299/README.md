# UVa 299 - Train Swapping

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 299
- **Problem Title:** Train Swapping
- **Problem Link:** [UVa 299 - Train Swapping](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=235)
- **Source Code (Correct/Accepted):** [UVa299.cpp](https://github.com/SWSekai/11402_CI002/blob/main/On-Site_Examinations/Week05_1_UVa299/src/UVa299.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 第一行為測資筆數 $T$。每筆測資第一行為火車長度 $L$ ($L \le 50$)，第二行為 $L$ 個整數，代表車廂編號。
- **Expected Output:** 每筆測資輸出一行：`Optimal train swapping takes X swaps.`，$X$ 為最少相鄰交換次數。
- **Rules/Constraints:** 只能交換相鄰的車廂；目標是將車廂排列成遞增順序；$L$ 很小 ($\le 50$)，可直接用 $O(L^2)$ 演算法。
- **Core Task:** 計算將序列排序成遞增順序所需的最少相鄰交換次數，即求序列中的逆序數對 (inversion count)。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 最少相鄰交換次數等於序列中的逆序數對數量（Bubble Sort 的交換次數）。
- 因為 $L \le 50$，直接使用 Bubble Sort 模擬計數即可，無需使用 Merge Sort 優化。

### Final Strategy
- **雙層迴圈模擬 Bubble Sort：** 外層從左到右遍歷每個元素，內層檢查其右側所有比它小的元素，遇到順序錯誤就交換並計數。
- **為什麼有效：** 每一次相鄰交換恰好消除一個逆序對，且 Bubble Sort 總是使用最少交換次數的排序方式之一（針對相鄰交換限制）。
- **邊界處理：** $L$ 最大 50，int 型別足以儲存計數結果。

## 4. Pseudocode

```text
START
1. READ test_case T
2. FOR each test case:
3.   READ L (train length)
4.   READ L carriages into array carr[]
5.   SET count = 0
6.   FOR i = 0 TO L-1:
7.     FOR j = i+1 TO L-1:
8.       IF carr[i] > carr[j]:
9.         SWAP carr[i] AND carr[j]
10.        count++
11.  PRINT "Optimal train swapping takes " + count + " swaps."
12. END FOR
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
static int count_swaps(int train_len, int carriages[]) {
    int count = 0;
    for (int i = 0; i < train_len; i++) {
        for (int j = i + 1; j < train_len; j++) {
            if (carriages[i] > carriages[j]) {
                swap(carriages[i], carriages[j]);
                count++;
            }
        }
    }
    return count;
}
```
**Why it works:**
- 直接模擬 Bubble Sort 的相鄰交換過程，每次交換都對應一個逆序對，計數即為最少交換次數。
- 雙層迴圈 $O(L^2)$ 在 $L \le 50$ 的限制下非常高效，程式碼簡潔易懂。

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 使用 Bubble Sort 模擬交換並計數，本質上就是計算逆序數對的數量 |
| **Edge Cases** | 已排序的序列交換次數為 0；長度為 1 時內層迴圈不執行，直接回傳 0 |

### Reflection
- **相鄰交換 = 逆序數對：** 最少相鄰交換次數永遠等於序列的逆序數對數量，這是排序理論中的基本性質。
- **根據資料規模選擇演算法：** $L \le 50$ 時 Bubble Sort 的 $O(L^2)$ 已足夠，但若 $L$ 很大（如 $10^5$），則需改用 Merge Sort 計算逆序數對。
