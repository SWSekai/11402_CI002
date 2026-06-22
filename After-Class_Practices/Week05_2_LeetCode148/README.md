# LeetCode 148 - Sort List

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 148
- **Problem Title:** Sort List
- **Problem Link:** https://leetcode.com/problems/sort-list/
- **Source Code (Correct/Accepted):** [leetcode148.cpp](https://github.com/SWSekai/11402_CI002/blob/main/After-Class_Practices/Week05_2_LeetCode148/src/leetcode148.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 一個 singly-linked list 的頭節點 `head`
- **Expected Output:** 將 linked list 排序後回傳新的頭節點
- **Rules/Constraints:** 時間複雜度需 O(n log n)，空間複雜度需 O(1)
- **Core Task:** 對 linked list 進行符合進階要求的排序（不可用陣列轉存後排序）

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 常見排序法：Merge Sort 在 linked list 上可以達到 O(1) 額外空間
- Quick Sort 對 linked list 需要 O(log n) 遞迴空間，且 partition 較麻煩
- Merge Sort 是 linked list 排序的首選

### Final Strategy
- 使用 Merge Sort Top-Down 或 Bottom-Up：
  - Top-Down：用快慢指標找到中點，遞迴分割左右，再 merge
  - Bottom-Up：從長度 1 的 sublist 開始，逐次加倍，迭代合併
- 合併兩個有序 linked list 用 dummy node 技巧

### Edge Cases Handled
- 空 list 或只有一個節點：直接回傳
- list 長度奇數/偶數：快慢指標處理得當

## 4. Pseudocode

```text
START
Function sortList(head):
1. If head == NULL or head->next == NULL: return head
2. Find mid (slow/fast pointer)
3. Split: left = head, right = mid->next, mid->next = NULL
4. left = sortList(left)
5. right = sortList(right)
6. Return merge(left, right)

Function merge(l1, l2):
1. dummy = new ListNode(0), tail = dummy
2. While l1 != NULL and l2 != NULL:
     If l1->val < l2->val: tail->next = l1; l1 = l1->next
     Else: tail->next = l2; l2 = l2->next
     tail = tail->next
3. tail->next = (l1 != NULL) ? l1 : l2
4. Return dummy->next
END
```

## 5. Fail Code vs Correct Code

### Correct Code

```cpp
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode *slow = head, *fast = head, *prev = NULL;
        while (fast && fast->next) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        prev->next = NULL;
        ListNode* left = sortList(head);
        ListNode* right = sortList(slow);
        return merge(left, right);
    }

    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        tail->next = l1 ? l1 : l2;
        return dummy.next;
    }
};
```
**Why it works:**
- Merge Sort 在 linked list 上不需要額外陣列空間，符合 O(1) 空間要求
- 快慢指標找中點、dummy node 合併是 linked list 操作的經典技巧

## 6. Difference and Reflection

### Key Differences

| Item | Description |
|---|---|
| **Logic** | 用陣列排序再重建 list 不符合 O(1) 空間要求；Merge Sort 直接操作 list 節點指標 |
| **Edge Cases** | 需在分割時將中間斷開（`prev->next = NULL`），避免無窮遞迴 |

### Reflection
- Linked list 的 Merge Sort 是面試高頻題，需熟練快慢指標找中點與合併操作
- 對 linked list 操作時，指標的斷開與連接要特別謹慎
