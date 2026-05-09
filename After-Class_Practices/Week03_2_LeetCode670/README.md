# LeetCode 670 - Maximum Swap

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 670
- **Problem Title:** Maximum Swap
- **Problem Link:** https://leetcode.com/problems/maximum-swap/
- **Source Code (Correct/Accepted):** [leetcode670.cpp](https://github.com/SWSekai/11402_CI002/blob/main/After-Class_Practices/Week03_2_LeetCode670/leetcode670.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 一個非負整數 `num`
- **Expected Output:** 將 `num` 的十進位表示中，最多交換一次任兩個位數後能得到的最大值
- **Rules/Constraints:** 只能交換一次（也可不交換），位數範圍 `[0, 10^8]`
- **Core Task:** 找到交換一次能讓數字變最大的最佳交換組合

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 直覺想到暴力法：嘗試所有兩兩交換組合，取最大值，但時間複雜度 O(n³) 較差
- 需要更有效率的 greedy 策略

### Final Strategy
- 將數字轉成字串，從左到右遍歷每個位置，對每個位置尋找右邊最大的數字來交換
- 如果右邊有多個相同最大值，選擇最靠右的那個（使交換後高位更大）
- 找到第一個能變大的交換即可，因為高位交換的影響力最大
- 時間複雜度 O(n²)，可進一步優化到 O(n)

### Edge Cases Handled
- 數字本身已是最大值（不需交換）
- 有重複數字時選最右邊的（如 1993 → 9913）

## 4. Pseudocode

```text
START
1. Convert num to string s
2. For i = 0 to n-1:
     maxDigit = s[i], maxIdx = i
     For j = i+1 to n-1:
       If s[j] >= maxDigit:
         maxDigit = s[j], maxIdx = j
     If maxIdx != i and s[maxIdx] != s[i]:
       Swap s[i] and s[maxIdx]
       Break
3. Convert s back to integer and return
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
class Solution {
public:
    int maximumSwap(int num) {
        string s = to_string(num);
        int n = s.size();
        for (int i = 0; i < n; i++) {
            int maxIdx = i;
            for (int j = i + 1; j < n; j++) {
                if (s[j] >= s[maxIdx]) {
                    maxIdx = j;
                }
            }
            if (maxIdx != i && s[maxIdx] != s[i]) {
                swap(s[i], s[maxIdx]);
                break;
            }
        }
        return stoi(s);
    }
};
```
**Why it works:**
- Greedy 地從高位往低位檢查，找到第一個可優化的位置就交換
- 選擇右邊最大且最靠右的數字，確保交換後值最大

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 暴力法逐一嘗試所有交換組合；Greedy 只找第一個可優化的高位交換 |
| **Edge Cases** | 需處理數字中有重複最大值的情況，選最右邊的才能最大化 |

### Reflection
- 學會 Greedy 思維：在高位尋找可優化的機會往往能直接得到最優解，不需要完整枚舉
- 將數字轉字串操作可以方便地處理位數交換
