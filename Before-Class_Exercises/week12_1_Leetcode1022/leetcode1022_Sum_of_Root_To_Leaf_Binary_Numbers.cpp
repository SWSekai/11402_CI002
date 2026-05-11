/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int sumRootToLeaf(TreeNode* root) {
        return dfs(root, 0);
    }

private:
    int dfs(TreeNode* node, int currentSum) {
        if (!node) return 0;
        
        // 左移一位 (x2) 並加上當前節點值
        currentSum = (currentSum << 1) + node->val;
        
        // leaf，回傳當前路徑的總和
        if (!node->left && !node->right) {
            return currentSum;
        }
        
        //非leaf, 回傳左右子樹的總和
        return dfs(node->left, currentSum) + dfs(node->right, currentSum);
    }
};