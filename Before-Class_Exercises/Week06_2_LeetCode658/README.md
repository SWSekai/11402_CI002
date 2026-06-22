# LeetCode 658 - Find K Closest Elements

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 658
- **Problem Title:** Find K Closest Elements
- **Problem Link:** https://leetcode.com/problems/find-k-closest-elements/
- **Source Code (Correct/Accepted):** [leetcode658.cpp](https://github.com/SWSekai/11402_CI002/blob/main/Before-Class_Exercises/Week06_2_LeetCode658/src/leetcode658.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 一個已排序的整數陣列 `arr`、整數 `k`、目標值 `x`
- **Expected Output:** 陣列中與 `x` 最接近的 `k` 個元素（按升序排列）
- **Rules/Constraints:** 若兩個元素距離相同，選擇較小的值；結果必須保持原有排序
- **Core Task:** 從已排序陣列中找出距離 `x` 最近的 `k` 個元素

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 直覺想到可以用雙指針或 binary search 找出 x 的插入位置後向兩側擴展
- 但實作上需要處理邊界情況，程式碼較長

### Final Strategy
- 利用 while 迴圈在陣列長度大於 k 時，每次比較頭尾元素與 x 的距離，較遠的那一側縮減一格
- 若頭尾距離相等（`x - front == back - x`），根據題意取較小值，所以移除尾端（因為尾端元素較大）
- 當陣列長度縮減到 k 時，剩下的即為答案

### Edge Cases Handled
- `x` 不在陣列範圍內 → 持續移除較遠的一端即可正確縮小範圍
- 距離相等時優先保留較小值
- `k` 等於陣列長度時不需任何操作

## 4. Pseudocode

```text
START
1. while arr.size() > k:
2.   if x - arr.front() <= arr.back() - x:
3.      移除最後一個元素 (arr.pop_back())
4.   else
5.      移除第一個元素 (arr.erase(arr.begin()))
6. return arr
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        while(arr.size() > k) {
            if(x - arr.front() <= arr.back() - x)
                arr.pop_back();
            else
                arr.erase(arr.begin());
        }
        return arr;
    }
};
```
**Why it works:**
- 每次比較兩端距離遠近，移除較遠者，保證剩下的 k 個元素就是全域最接近的 k 個值

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 用雙端逐步縮減的方式取代複雜的 binary search，邏輯簡潔且不易出錯 |
| **Edge Cases** | 距離相等時選擇移除尾端（保留較小值）符合題目要求 |

### Reflection
- 對於已排序陣列的區間問題，雙指針或雙端縮減法往往比二分搜尋更直觀且易於實作；關鍵是理解何時縮減哪一端
