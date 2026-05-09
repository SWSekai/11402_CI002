# LeetCode 349 - Intersection of Two Arrays

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 349
- **Problem Title:** Intersection of Two Arrays
- **Problem Link:** https://leetcode.com/problems/intersection-of-two-arrays/
- **Source Code (Correct/Accepted):** [leetcode349.cpp](https://github.com/SWSekai/11402_CI002/blob/main/After-Class_Practices/Week05_1_LeetCode349/leetcode349.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 兩個整數陣列 `nums1` 和 `nums2`
- **Expected Output:** 兩陣列的交集（所有共同出現的元素），每個元素只能出現一次
- **Rules/Constraints:** 輸出結果中每個元素必須是唯一的（不重複），順序不限
- **Core Task:** 找出兩個陣列中都出現的數字集合（去重）

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 直覺：用雙重迴圈找共同元素，再用 set 去重，但效率較差 O(n*m)
- 更好的做法：先用 set 去重 + 快速查詢

### Final Strategy
- 將 `nums1` 放入 `unordered_set` 中（O(1) 查詢）
- 遍歷 `nums2`，對每個元素檢查是否在 set 中
- 若存在則加入結果集，並從 set 中移除（避免重複加入）
- 時間複雜度 O(n + m)，空間複雜度 O(n)

### Edge Cases Handled
- 陣列為空：回傳空陣列
- 陣列中有重複元素：用 set 確保輸出唯一
- 兩陣列無交集：回傳空陣列

## 4. Pseudocode

```text
START
1. Insert all nums1 elements into unordered_set s
2. For each num in nums2:
     If num is in s:
       Add num to result
       Remove num from s (prevent duplicates)
3. Return result
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> s(nums1.begin(), nums1.end());
        vector<int> ans;
        for (int num : nums2) {
            if (s.count(num)) {
                ans.push_back(num);
                s.erase(num);
            }
        }
        return ans;
    }
};
```
**Why it works:**
- 利用 `unordered_set` 的 O(1) 平均查詢時間
- 找到匹配後立即從 set 中刪除，確保結果不重複

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 暴力法使用雙重迴圈 O(n*m)；Set 法用 hash 查詢將複雜度降為 O(n+m) |
| **Edge Cases** | 需處理重複元素，用 set 去重並在匹配後刪除避免重複輸出 |

### Reflection
- 學會利用 `unordered_set` 進行高效的集合操作
- 當需要去重或快速查詢時，hash-based 容器是最佳選擇
