# LeetCode 1845 - Seat Reservation Manager

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 1845
- **Problem Title:** Seat Reservation Manager
- **Problem Link:** https://leetcode.com/problems/seat-reservation-manager/
- **Source Code (Correct/Accepted):** [LeetCode1845.cpp](https://github.com/SWSekai/11402_CI002/blob/main/Before_Class/Week14_2_LeetCode1845/LeetCode1845.cpp)

---

## 2. Problem Statement in My Own Words

設計一個座位管理系統，座位編號從 1 到 n，支援以下兩種操作：

- **Input:**
  - 初始化時給定整數 `n`，代表總座位數量
  - 每次操作為 `reserve()` 或 `unreserve(seatNumber)`
- **Expected Output:**
  - `reserve()`：回傳當前**編號最小**的可用座位號碼，並將其標記為已佔用
  - `unreserve(seatNumber)`：將指定座位釋放回可用狀態，無回傳值
- **Rules/Constraints:**
  - 座位編號從 1 開始，最大為 $n$（$1 \leq n \leq 10^5$）
  - 總操作次數最多 $10^5$ 次
  - `unreserve` 保證只對已被 reserve 的座位呼叫
- **Core Task:** 在動態 reserve / unreserve 的過程中，始終能以 $O(\log n)$ 的效率找到並回傳編號最小的可用座位。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- **初步思路:** 直接將 1 到 n 的所有座位號碼全部推入 min-heap（`priority_queue` with `greater<int>`），`reserve()` 從堆頂取號，`unreserve()` 將號碼推回 heap。
- **初期難點:** 邏輯正確、可以通過所有測資，但 Constructor 的初始化需要 $O(n \log n)$ 時間與 $O(n)$ 空間。當 $n = 10^5$ 但操作次數極少時，大量座位號碼被推入 heap 卻永遠不會被碰觸，屬於無效的空間佔用。

### Final Strategy

- **採用方法:** Min-heap（`priority_queue<int, vector<int>, greater<int>>`）搭配 `nextSeat` 指標。
- **可行性分析:**
  - 觀察關鍵 invariant：`unreserve()` 只對已被 reserve 的座位呼叫，因此 heap 中的號碼**永遠小於 `nextSeat`**，不需要做兩者的大小比較。
  - 尚未被 reserve 過的連續座位（即 `nextSeat` 之後的部分）不需要提前入堆，用一個整數指標追蹤即可。
  - Constructor 降為 $O(1)$，heap 只在有歸還座位時才有元素，整體空間使用大幅改善。
  - `reserve()` 與 `unreserve()` 的 Time Complexity 維持 $O(\log n)$。
- **邊界處理:**
  - heap 為空時，直接回傳 `nextSeat` 並遞增，不需要額外判斷。
  - heap 不為空時，其頂端值保證小於 `nextSeat`，直接取用即可。

---

## 4. Pseudocode

```text
START

CLASS SeatManager:
  min-heap: available_seats  // 只存放被 unreserve 歸還的座位
  int: nextSeat = 1          // 指向下一個從未被 reserve 過的座位

  CONSTRUCTOR(n):
    nextSeat = 1             // O(1) 初始化，不預先填入任何座位

  FUNCTION reserve():
    IF available_seats is empty:
      RETURN nextSeat++      // 直接取用連續段的下一個號碼
    ELSE:
      seat = available_seats.top()
      available_seats.pop()
      RETURN seat            // 取用歸還池中編號最小的座位

  FUNCTION unreserve(seatNumber):
    available_seats.push(seatNumber)  // 歸還至 heap

END
```

---

## 5. Fail Code vs Correct Code

### Fail Code

```cpp
class SeatManager {
    // 問題：一次性將所有座位推入 heap，初始化成本為 O(n log n)
    priority_queue<int, vector<int>, greater<int>> seats;
public:
    SeatManager(int n) {
        // 缺陷：n 極大時，大量座位永遠不會被操作，造成無效記憶體佔用
        for(int i = 1; i <= n; ++i) seats.push(i);
    }
    
    int reserve() {
        int target = seats.top();
        seats.pop();
        return target;
    }
    
    void unreserve(int seatNumber) {
        seats.push(seatNumber);
    }
};
```

**Why it failed:**
- **效率問題:** Constructor 執行 $O(n \log n)$ 的初始化，當 $n = 10^5$ 而操作數極少時，產生大量無效工作。若 $n$ 放大至 $10^9$ 等級，則直接 MLE。
- **邏輯缺陷:** 未區分「從未被 reserve 的連續座位」與「曾被歸還的座位」，導致兩者混用同一個 heap，無法針對前者做 $O(1)$ 的空間優化。

---

### Correct Code

```cpp
class SeatManager {
    // 修正：heap 只存放被 unreserve 歸還的座位
    priority_queue<int, vector<int>, greater<int>> available_seats;
    int nextSeat; // 新增：指向連續未使用段的下一個號碼
public:
    SeatManager(int n) {
        nextSeat = 1; // 修正：O(1) 初始化，不預先填入任何元素
    }
    
    int reserve() {
        // 關鍵 invariant：heap 不為空時，其頂端值必然 < nextSeat
        // 因為 unreserve 只對已 reserved 的座位呼叫，保證 heap 中的號碼都 < nextSeat
        if(available_seats.empty()) return nextSeat++;
        else {
            int seat = available_seats.top();
            available_seats.pop();
            return seat;
        }
    }
    
    void unreserve(int seatNumber) {
        available_seats.push(seatNumber);
    }
};
```

**Why it works:**
- **核心優化:** 引入 `nextSeat` 指標，將「從未被使用的連續座位段」與「被歸還的座位」分開管理。Constructor 降為 $O(1)$，heap 的元素數量與實際操作次數成正比，而非與 $n$ 成正比。
- **穩健性:** 利用題目保證的 invariant（`unreserve` 只對已 reserved 座位呼叫），確保 heap 中的號碼永遠小於 `nextSeat`，因此 `reserve()` 不需要額外的大小比較，邏輯簡潔且正確。

---

## 6. Difference and Reflection

### Key Differences

| Item | Fail Code | Correct Code |
| :--- | :--- | :--- |
| **初始化複雜度** | $O(n \log n)$，預先填入所有座位 | $O(1)$，只設定 `nextSeat = 1` |
| **空間使用** | $O(n)$，heap 永遠持有全部 $n$ 個元素 | $O(k)$，$k$ 為實際歸還次數，與操作數成正比 |
| **Heap 職責** | 混用：存放所有座位（包含從未使用的） | 單一：只存放曾被 `unreserve` 歸還的座位 |
| **連續段管理** | 無，依賴 heap 隱含排序 | 以 `nextSeat` 指標明確追蹤 |
| **擴展性** | $n$ 放大至 $10^9$ 時直接崩潰 | $n$ 的大小不影響初始化，僅操作次數影響效能 |

### Reflection

- **最大的失誤:** 初版未區分「從未被碰觸的連續座位」與「歸還的座位」，直覺地將兩者全部丟入 heap，導致初始化成本與 $n 直接掛鉤，而非與操作次數掛鉤。這是一個典型的「不必要的預先計算」反模式。
- **習得知識:** 設計資料結構時，應先分析操作的 invariant。本題的關鍵洞察是：「未被使用的座位編號具有連續遞增的性質」，這個規律可以用一個簡單的整數指標取代，而無需一個 $O(n)$ 的資料結構。識別並利用 invariant 是將暴力解優化為最佳解的核心思維。
- **未來規劃:** 遇到需要「動態維護最小值」的題目時，第一步先評估初始集合是否可以懶惰初始化（lazy initialization）。若集合具有連續、有序等規律，優先考慮用指標或計數器代替，再用 heap 補充處理「例外情況」（如歸還的元素），避免無謂的全量初始化。
