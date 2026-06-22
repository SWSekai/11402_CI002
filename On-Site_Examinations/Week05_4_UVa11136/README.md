# UVa 11136 - Hoax or what

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 11136
- **Problem Title:** Hoax or what
- **Problem Link:** [https://onlinejudge.org/external/111/11136.pdf](https://onlinejudge.org/external/111/11136.pdf)
- **Source Code (Correct/Accepted):** [UVa11136.cpp](https://github.com/SWSekai/11402_CI002/blob/main/On-Site_Examinations/Week05_4_UVa11136/src/UVa11136.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 多組測資，每組第一行為一個整數 n（n > 0）表示天數，接下來 n 行每行第一個整數 k 表示當天有 k 張獎金收據，後面跟著 k 個整數代表金額。n = 0 時結束。
- **Expected Output:** 輸出所有天數的 (當天最大金額 - 當天最小金額) 的總和。
- **Rules/Constraints:** 每天投入 k 張收據後，會從中抽出最高和最低金額的收據，將其差額作為當天的 cost。金額可能很大，總和需用 long long。
- **Core Task:** 模擬每天投入收據並計算最高與最低金額的差值，累加所有天數的差值輸出。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 需要一個能快速找到最大值和最小值的資料結構，且支援插入和刪除操作。
- 使用陣列或 vector 會導致每次都需要排序或遍歷，效率太差。

### Final Strategy
- 使用 C++ STL 的 `multiset`（基於紅黑樹，自動排序），插入、刪除、取最大最小值皆為 O(log n)。
- 每天先將 k 個數字插入 multiset，然後取出 `begin()`（最小值）和 `rbegin()`（最大值），計算差值並累加，再刪除這兩個元素。
- 注意 total cost 可能很大，必須使用 `long long`。

## 4. Pseudocode

```text
START
WHILE read n AND n != 0:
    multiset<int> urn
    long long total = 0
    FOR i = 1 TO n:
        read k
        FOR j = 1 TO k:
            read num
            urn.insert(num)
        lowest = *urn.begin()
        highest = *urn.rbegin()
        total += highest - lowest
        urn.erase(urn.begin())
        urn.erase(urn.find(highest))  // erase by iterator, not value
    PRINT total
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
multiset<int> urn;
long long ans = 0;
for (int i = 0; i < n; i++) {
    int m; cin >> m;
    for (int j = 0; j < m; j++) {
        int a; cin >> a;
        urn.insert(a);
    }
    ans += *urn.rbegin() - *urn.begin();
    urn.erase(urn.begin());
    urn.erase(urn.find(*urn.rbegin()));
}
```
**Why it works:**
- `multiset` 自動維持排序順序，`begin()` 為最小值，`rbegin()` 為最大值
- 刪除最大值時使用 `find()` 取得 iterator 再刪除，避免刪除所有相同值的元素

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 使用 multiset 而非手動排序，每次插入 O(log n)，取極值 O(1) |
| **Edge Cases** | 總和可能超過 int 範圍，需使用 long long；刪除時用 iterator 避免刪除多個相同值的元素 |

### Reflection
- 學會使用 multiset 處理需要頻繁插入、刪除並取極值的問題
- 注意 STL 容器 erase(value) 會刪除所有等於 value 的元素，erase(iterator) 只刪除一個
