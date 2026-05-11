# LeetCode 1022 - Sum of Root To Leaf Binary Numbers

## 1. Problem Information

- **Platform:** LeetCode
- **Problem ID:** 1022
- **Problem Title:** Sum of Root To Leaf Binary Numbers
- **Problem Link:** https://leetcode.com/problems/sum-of-root-to-leaf-binary-numbers/
- **Source Code (Correct/Accepted):** [leetcode1022_Sum_of_Root_To_Leaf_Binary_Numbers.cpp](https://github.com/SWSekai/11402_CI002/blob/main/Before-Class_Exercises/week12_1_Leetcode1022/leetcode1022_Sum_of_Root_To_Leaf_Binary_Numbers.cpp)

## 2. Problem Statement in My Own Words

- **Input:** 一棵二元樹的根節點 `root`，每個節點的值只會是 `0` 或 `1`。
- **Expected Output:** 回傳所有從根節點到葉節點路徑所代表的二進位數字總和。
- **Rules/Constraints:** 每一條 root-to-leaf path 都可以視為一個二進位數字；路徑越往下，新的節點值就接在目前二進位數字的最右邊。
- **Core Task:** 使用樹的遍歷方式，累積每條路徑目前形成的二進位值，並在抵達葉節點時把該值加入總和。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- 這題的核心是「一路往下走時記住目前路徑形成的數字」。
- 因為每個節點值只會是 `0` 或 `1`，當走到下一層時，相當於把目前數字左移一位，再加上目前節點值。
- 每條路徑都必須從 root 走到 leaf 才能形成完整數字，所以可以使用 DFS 遞迴處理。

### Final Strategy

- **Data Structure / Method:** 使用 DFS 遞迴。
- **State Update:** 每到一個節點時，更新目前路徑值：

```cpp
currentSum = (currentSum << 1) + node->val;
```

- **Time Complexity:** `O(N)`，其中 `N` 是節點數，每個節點只會走訪一次。
- **Space Complexity:** `O(H)`，其中 `H` 是樹高，來自遞迴呼叫堆疊。
- **Edge Cases:**
  - `root == nullptr` 時回傳 `0`。
  - 判斷葉節點時，條件必須是 `!node->left && !node->right`。

## 4. Pseudocode

```text
START
FUNCTION dfs(node, currentSum)
    1. IF node IS NULL:
           RETURN 0
    2. currentSum = currentSum * 2 + node.val
    3. IF node IS leaf:
           RETURN currentSum
    4. RETURN dfs(node.left, currentSum) + dfs(node.right, currentSum)

FUNCTION sumRootToLeaf(root)
    1. RETURN dfs(root, 0)
END
```

## 5. Fail Code vs Correct Code

### Fail Code

```cpp
class Solution {
public:
    int sumRootToLeaf(TreeNode* root) {
        int res = 0;
        leafCalculator(root, 0, res);
        return res;
    }

    void leafCalculator(TreeNode* node, int cur, int& res) {
        if (!node) return;

        cur += cur * 2 + node->val;

        if (!node->left && !node->right) res += cur;
        leafCalculator(node->left, cur, res);
        leafCalculator(node->right, cur, res);
    }
};
```

**Why it failed:**

- **Logic Error:** `cur += cur * 2 + node->val` 會把原本的 `cur` 多加一次，實際效果變成 `cur = 3 * cur + node->val`。
- **Correct Formula:** 下一層的二進位值應該只做一次左移，也就是 `cur = cur * 2 + node->val`。
- **State Management:** 使用外部參考 `res` 可以得到答案，但比起直接讓 DFS 回傳子樹總和，狀態較分散，也比較容易出錯。

### Correct Code

```cpp
class Solution {
public:
    int sumRootToLeaf(TreeNode* root) {
        return dfs(root, 0);
    }

private:
    int dfs(TreeNode* node, int currentSum) {
        if (!node) return 0;

        currentSum = (currentSum << 1) + node->val;

        if (!node->left && !node->right) {
            return currentSum;
        }

        return dfs(node->left, currentSum) + dfs(node->right, currentSum);
    }
};
```

**Why it works:**

- **Correct Binary Update:** `(currentSum << 1) + node->val` 等同於 `currentSum * 2 + node->val`，正確表示把目前路徑值接上一個新的 binary digit。
- **Leaf Handling:** 只有在葉節點才回傳完整路徑值，避免把尚未完成的中間路徑加入答案。
- **Cleaner Recursion:** 左子樹與右子樹各自回傳總和，最後直接相加，讓函式的回傳值意義清楚。

## 6. Difference and Reflection

### Key Differences

| Item | Fail Code | Correct Code |
| :--- | :--- | :--- |
| **Logic** | 使用 `cur += cur * 2 + node->val`，導致目前值被重複加上 | 使用 `currentSum = (currentSum << 1) + node->val`，正確更新二進位路徑值 |
| **State Management** | 用 `int& res` 在遞迴外部累加答案 | 讓 `dfs` 回傳每棵子樹的總和 |
| **Readability** | 更新狀態與累加答案混在一起 | 每個遞迴呼叫只負責回傳該節點以下的總和 |
| **Edge Cases** | 若公式錯誤，越深的路徑偏差越大 | 空節點回傳 `0`，葉節點回傳完整路徑值 |

### Reflection

- 這題讓我注意到，路徑狀態更新不能只憑直覺使用 `+=`，必須先確認數學公式是否正確。
- 對於 binary path 類型的題目，可以把「往下一層」想成「目前值乘以 2，再加上新 bit」。
- 使用 DFS 回傳值的方式可以讓程式更簡潔，也能降低外部變數造成的狀態混亂。
