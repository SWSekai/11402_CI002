# LeetCode 1109 - Corporate Flight Bookings

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 1109
- **Problem Title:** Corporate Flight Bookings
- **Problem Link:** https://leetcode.com/problems/corporate-flight-bookings/
- **Source Code (Correct/Accepted):** [leetcode1109.cpp](https://github.com/SWSekai/11402_CI002/blob/main/Before-Class_Exercises/Week09_2_LeetCode1109/leetcode1109.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 一個二維整數陣列 `bookings`，每個元素為 `[first_i, last_i, seats_i]` 代表一筆預訂（從 `first_i` 到 `last_i` 的每個航班都預訂 `seats_i` 個座位），以及一個整數 `n` 代表航班總數（編號 1 到 n）。
- **Expected Output:** 一個長度為 n 的整數陣列 `answer`，其中 `answer[i]` 代表航班 i+1 的總預訂座位數。
- **Rules/Constraints:** 航班編號從 1 開始。
- **Core Task:** 對多個區間進行範圍增量，最後輸出每個位置的累加值。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 暴力解：對每個 booking，從 first 到 last 逐航班加 seats，時間 O(n * k) 會超時。
- 需要 O(n + k) 的解法。

### Final Strategy
- **演算法：** 差分陣列 (Difference Array)
- **步驟：**
  1. 建立長度為 n+2 的差分陣列 diff（多出邊界避免越界）。
  2. 對每個 booking `[first, last, seats]`：
     - `diff[first] += seats`
     - `diff[last + 1] -= seats`
  3. 對 diff 做前綴和，得到每個航班的座位數。
- **為什麼可行：** 差分陣列能在 O(1) 時間內完成區間增量，最後一次前綴和還原結果。
- **邊界處理：** 陣列大小為 n+2 以避免 `last+1` 越界。

## 4. Pseudocode

```text
START
1. 建立 vector<int> diff(n + 2, 0)
2. 對每個 booking [first, last, seats]：
   a. diff[first] += seats
   b. diff[last + 1] -= seats
3. 建立 vector<int> ans(n)
4. cur = 0
5. 遍歷 i 從 0 到 n-1：
   a. cur += diff[i + 1]
   b. ans[i] = cur
6. 回傳 ans
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        vector<int> diff(n + 2, 0);
        for (auto& b : bookings) {
            int first = b[0], last = b[1], seats = b[2];
            diff[first] += seats;
            diff[last + 1] -= seats;
        }
        vector<int> ans(n);
        int cur = 0;
        for (int i = 1; i <= n; i++) {
            cur += diff[i];
            ans[i - 1] = cur;
        }
        return ans;
    }
};
```
**Why it works:**
- 差分陣列將區間加值的時間從 O(length) 降到 O(1)，最終一次前綴和即可得到所有結果。

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 使用差分陣列技巧，只在區間起點 +seats、終點後一位置 -seats |
| **Edge Cases** | diff 大小設為 n+2 避免 last+1 越界；航班編號與陣列索引相差 1 |

### Reflection
- 差分陣列是處理「多次區間增量、最後查詢」的經典工具。理解這個模式後，類似的題目（如 Range Addition）都能迎刃而解。
