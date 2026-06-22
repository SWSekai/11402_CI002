# LeetCode 121 - Best Time to Buy and Sell Stock

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 121
- **Problem Title:** Best Time to Buy and Sell Stock
- **Problem Link:** https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
- **Source Code (Correct/Accepted):** [leetcode121.cpp](https://github.com/SWSekai/11402_CI002/blob/main/After-Class_Practices/Week04_1_LeetCode121/src/leetcode121.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 一個整數陣列 `prices`，其中 `prices[i]` 表示第 i 天的股票價格
- **Expected Output:** 最大利潤（賣出價格減去買入價格），若無法獲利則回傳 0
- **Rules/Constraints:** 只能買賣一次（先買後賣），不可在同一天賣出
- **Core Task:** 找到 `prices[j] - prices[i]` 的最大值，其中 j > i

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 暴力法：兩層迴圈對所有買賣組合計算利潤 O(n²)
- 需要 O(n) 的單次掃描解法

### Final Strategy
- 掃描陣列的同時維護到目前為止的最低買入價格 `minPrice`
- 對每一天計算「如果今天賣出能賺多少」，即 `prices[i] - minPrice`
- 用 `maxProfit` 記錄所有可能利潤中的最大值
- 這樣相當於固定賣出日，往前找最低買入日，保證 j > i

### Edge Cases Handled
- 價格持續下跌：maxProfit 保持 0（不買賣）
- 只有一天價格：直接回傳 0

## 4. Pseudocode

```text
START
1. minPrice = INF, maxProfit = 0
2. For each price p in prices:
     If p < minPrice: minPrice = p
     Else if p - minPrice > maxProfit: maxProfit = p - minPrice
3. Return maxProfit
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minPrice = INT_MAX;
        int maxProfit = 0;
        for (int p : prices) {
            if (p < minPrice) {
                minPrice = p;
            } else if (p - minPrice > maxProfit) {
                maxProfit = p - minPrice;
            }
        }
        return maxProfit;
    }
};
```
**Why it works:**
- 動態維護歷史最低價，保證買入日在賣出日之前
- 一次遍歷同時更新最低價與最大利潤，O(n) 時間、O(1) 空間

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 暴力法 O(n²) 枚舉所有對；Kadane-like 一次遍歷 O(n) 解決 |
| **Edge Cases** | 需處理無法獲利時回傳 0，以及價格持續下跌的場景 |

### Reflection
- 將「買賣」問題轉換為「維護歷史最小值」的思路是股票系列題目的核心
- 理解 Kadane 演算法的變形：將利潤視為「當前價格減去歷史最低價」
