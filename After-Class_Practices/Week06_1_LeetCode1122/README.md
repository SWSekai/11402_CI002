# LeetCode 1122 - Relative Sort Array

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 1122
- **Problem Title:** Relative Sort Array
- **Problem Link:** https://leetcode.com/problems/relative-sort-array/
- **Source Code (Correct/Accepted):** [leetcode1122.cpp](https://github.com/SWSekai/11402_CI002/blob/main/After-Class_Practices/Week06_1_LeetCode1122/src/leetcode1122.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 兩個整數陣列 `arr1` 和 `arr2`，其中 `arr2` 的元素彼此不重複，且 `arr2` 中的每個元素都存在於 `arr1` 中。
- **Expected Output:** 回傳一個排序後的 `arr1`，使得 `arr1` 中出現在 `arr2` 的元素按照 `arr2` 的順序排列，未出現在 `arr2` 中的元素則以遞增順序排在最後。
- **Rules/Constraints:** `1 <= arr1.length, arr2.length <= 1000`，`0 <= arr1[i], arr2[i] <= 1000`，arr2 中的元素在 arr1 中必定出現。
- **Core Task:** 按照 arr2 的相對順序對 arr1 進行排序，其餘元素升序排列。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 最直觀的想法是遍歷 arr2，對於每個元素，將 arr1 中所有相同元素依序放到結果陣列中。
- 需要處理 arr2 中沒有的元素，這些元素需要單獨收集並升序排列。

### Final Strategy
- 使用 Counting Sort（計數排序）的思想，因為題目給定的數值範圍很小（0 ~ 1000），非常適合用計數陣列來統計頻率。
- 先統計 arr1 中每個數字出現的次數，然後先按照 arr2 的順序輸出，再按照升序輸出其餘數字。
- 時間複雜度 O(n + m + 1001) = O(n + m)，空間複雜度 O(1001) = O(1)。

### Edge Cases Handled
- arr2 為空：直接對 arr1 進行排序即可。
- arr1 中所有元素都不在 arr2 中：按照升序輸出整個 arr1。
- 元素重複出現多次：計數陣列可以正確處理頻率。

## 4. Pseudocode

```text
START
1. 建立計數陣列 freq[1001]，初始化為 0
2. 遍歷 arr1，對每個元素 num，freq[num]++
3. 初始化結果陣列 idx = 0
4. 遍歷 arr2：
    a. 當 freq[num] > 0 時：
       - 將 num 放入結果陣列
       - freq[num]--
5. 遍歷 i = 0...1000：
    a. 當 freq[i] > 0 時：
       - 將 i 放入結果陣列
       - freq[i]--
6. 回傳結果陣列
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
    int freq[1001] = {0};
    for (int num : arr1) freq[num]++;

    vector<int> res;
    for (int num : arr2) {
        while (freq[num]-- > 0) res.push_back(num);
    }
    for (int i = 0; i <= 1000; i++) {
        while (freq[i]-- > 0) res.push_back(i);
    }
    return res;
}
```

**Why it works:**
- 利用 Counting Sort 的特性，先按 arr2 順序輸出，再按數值大小輸出剩餘元素，完全符合題目要求。

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 使用計數排序而非比較排序，將時間複雜度從 O(n log n) 降低到 O(n + m) |
| **Edge Cases** | 計數陣列能自動處理重複元素，且範圍有限保證空間效率 |

### Reflection
- 當題目給定的數值範圍很小時，計數排序是非常高效的選擇，比基於比較的排序更適合這類問題。
- 理解題目的「相對順序」本質上是一種自定義排序規則，可以透過映射或計數來實現。
