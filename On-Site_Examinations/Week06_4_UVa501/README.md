# UVa 501 - Black Box

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 501
- **Problem Title:** Black Box
- **Problem Link:** [https://onlinejudge.org/external/5/501.pdf](https://onlinejudge.org/external/5/501.pdf)
- **Source Code (Correct/Accepted):** [UVa501.cpp](https://github.com/SWSekai/11402_CI002/blob/main/On-Site_Examinations/Week06_4_UVa501/UVa501.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 第一行為測資數 K，每組測資包含 M、N、長度為 M 的陣列 A（ADD 的數字序列）以及長度為 N 的遞增序列 u（表示第幾次 ADD 後要執行 GET）。數字以空格或換行分隔，組間有空行。
- **Expected Output:** 對每個 GET 操作，輸出目前 Black Box 中第 i 小的元素（i 從 1 開始，每次 GET 後 i 遞增 1）。每組測資的輸出間空一行。
- **Rules/Constraints:** M, N ≤ 30000，|A[i]| ≤ 2×10^9。u 序列遞增且 1 ≤ u[p] ≤ M，且 p ≤ u[p]。
- **Core Task:** 模擬 ADD 和 GET 操作，每次 GET 時輸出當前的第 i 小元素。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 每次 GET 都需要第 i 小的值，若每次都排序會太慢（O(M log M × N)）。
- 需要一個能動態維護排序並快速取得第 k 小元素的資料結構。

### Final Strategy
- 使用 `multiset` 搭配 iterator：在 multiset 中插入元素後，iterator 會保持在正確的排序位置。
- 初始化時插入一個極小值（如 -1e9）作為哨兵，iterator 指向 begin()。
- 對每個 ADD：若插入的值比目前 iterator 指向的值小，則將 iterator 前移一格（--it），以維持 iterator 指向第 cnt 小的元素。
- 對每個 GET：輸出 iterator 目前指向的值，然後 iterator 後移一格（++it）到下一位置，同時 cnt++ 以追蹤目前已輸出的元素個數。

## 4. Pseudocode

```text
START
FOR each dataset:
    multiset<int> mst
    mst.insert(-INF)
    it = mst.begin()
    cnt = 0
    idx = 1  // 指向 A 陣列的下一個 ADD 位置
    FOR k = 1 TO N:   // k 為第幾次 GET
        read u[k]
        WHILE idx <= u[k]:
            mst.insert(A[idx])
            IF A[idx] < *it: --it
            idx++
        WHILE cnt < k:
            ++it; ++cnt
        PRINT *it
    IF not last dataset: PRINT blank line
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
multiset<int> mst;
mst.insert(-1e9);
auto it = mst.begin();
int cnt = 0, lst = 1;
for (int k = 1; m--; k++) {
    int u; cin >> u;
    for (int i = lst; i <= u; i++) {
        mst.insert(A[i]);
        if (A[i] < *it) --it;
    }
    lst = u + 1;
    while (cnt < k) { ++it; ++cnt; }
    cout << *it << endl;
}
```
**Why it works:**
- multiset 維持排序，iterator 指向當前第 cnt 小的元素
- 插入比 `*it` 小的數時，第 cnt 小元素的位置會往右移一格，故 `--it` 修正
- 每次 GET 後 iterator 前進一格，cnt 加 1，準備指向下一個第 k 小元素

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 用 multiset + iterator 追蹤第 k 小元素，避免每次 GET 都重新遍歷 |
| **Edge Cases** | 哨兵值確保 iterator 不會越界；多筆測資間的 blank line 需處理 |

### Reflection
- 這是一道經典的「動態第 k 小元素」問題，multiset + iterator 是高效的解法
- 若每次 GET 都從頭遍歷會導致 TLE，必須利用 iterator 的持續性來保持位置
