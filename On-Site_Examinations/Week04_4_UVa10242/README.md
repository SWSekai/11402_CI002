# UVa 10242 - Fourth Point !!

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 10242
- **Problem Title:** Fourth Point !!
- **Problem Link:** [UVa 10242 - Fourth Point !!](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1183)
- **Source Code (Correct/Accepted):** [UVa10242.cpp](https://github.com/SWSekai/11402_CI002/blob/main/On-Site_Examinations/Week04_4_UVa10242/UVa10242.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 每行包含 8 個浮點數，分別表示平行四邊形兩相鄰邊的端點座標（每邊給兩個端點），順序為：第一邊的端點1、第一邊的端點2、第二邊的端點1、第二邊的端點2。座標範圍 −10000 到 +10000，EOF 結束。
- **Expected Output:** 輸出第四個頂點的 (x, y) 座標，精確到小數點後 3 位，以空格分隔。
- **Rules/Constraints:** 兩相鄰邊共用一個頂點（即 4 個端點中有 1 個點出現兩次）。座標輸入至 nearest mm，輸出亦須至 nearest mm。
- **Core Task:** 從給定的 4 個端點中找出重複的共用頂點，再利用平行四邊形對角線互相平分的性質求出第四點。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 平行四邊形的對角線互相平分，因此若已知三個頂點，可透過中點公式求出第四點。
- 題目給出兩相鄰邊的端點，總共 4 個點，但其中一個點是重複的（兩邊的共用頂點），實際只給了 3 個唯一頂點。

### Final Strategy
- **找重複點：** 逐一比對 4 個輸入點，找出哪一個點出現了兩次，即為共用頂點。
- **求第四點：** 設共用頂點為 P，另外兩個頂點為 A 和 B。平行四邊形第四點 Q = A + B − P（向量相加），因為 P 和 Q 的中點 = A 和 B 的中點。
- **輸出格式：** 使用 `printf("%.3lf %.3lf")` 輸出到小數點後 3 位。
- **邊界處理：** 所有座標均為浮點數，需使用 `double` 型別；比對重複點時直接比較浮點數是否相等即可（輸入精確到 mm）。

## 4. Pseudocode

```text
START
1. WHILE (read 8 doubles x1,y1,x2,y2,x3,y3,x4,y4 successfully)
2.   Store points in arrays x[1..4], y[1..4]
3.   Find the index pair (i, j) where x[i]==x[j] AND y[i]==y[j], i != j  → shared vertex
4.   Identify the remaining two indices p, q (not shared)
5.   fourth_x = x[p] + x[q] - x[shared]
6.   fourth_y = y[p] + y[q] - y[shared]
7.   PRINT fourth_x and fourth_y with 3 decimal places
8. END WHILE
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
double x[5], y[5];
while (scanf("%lf %lf %lf %lf %lf %lf %lf %lf",
       &x[1], &y[1], &x[2], &y[2], &x[3], &y[3], &x[4], &y[4]) == 8) {
    int shared1, shared2;
    // Find the duplicate point (shared vertex)
    for (int i = 1; i <= 4; i++) {
        for (int j = i + 1; j <= 4; j++) {
            if (x[i] == x[j] && y[i] == y[j]) {
                shared1 = i; shared2 = j;
            }
        }
    }
    // Find the other two unique points
    int others[2], idx = 0;
    for (int i = 1; i <= 4; i++) {
        if (i != shared1 && i != shared2)
            others[idx++] = i;
    }
    // Fourth point = sum of other two - shared
    double fx = x[others[0]] + x[others[1]] - x[shared1];
    double fy = y[others[0]] + y[others[1]] - y[shared1];
    printf("%.3lf %.3lf\n", fx, fy);
}
```
**Why it works:**
- 利用平行四邊形「對角線互相平分」的性質，透過向量加法直接求出第四點，無需判斷邊的對應關係。
- 雙層迴圈找出重複點，邏輯簡單且能處理任意輸入順序。

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 找重複的共用頂點 → 用向量加法求第四點，不需要考慮邊的順序 |
| **Edge Cases** | 浮點數直接比較相等（輸入精確到 mm）；使用 `double` 避免精度遺失 |

### Reflection
- **幾何性質簡化問題：** 平行四邊形的對角線平分性質可以將求第四點化簡為簡單的向量運算，無須處理繁瑣的條件判斷。
- **輸入順序的陷阱：** 題目沒有保證端點的輸入順序，因此必須先找出重複點才能正確計算，不能假設前兩個點是一條邊。
