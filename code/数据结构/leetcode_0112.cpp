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

// BFS
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (root == nullptr)
            return false;
        
        queue<TreeNode*> dqNode;
        queue<int> dqVal;
        dqNode.push(root);
        dqVal.push(root->val);

        while (!dqNode.empty())
        {
            TreeNode* node = dqNode.front();
            dqNode.pop();
            int curSum = dqVal.front();
            dqVal.pop();
            if (node->left == nullptr && node->right == nullptr && curSum == targetSum)
                return true;
            
            if (node->left != nullptr)
                dqNode.push(node->left), dqVal.push(curSum + node->left->val);
            if (node->right != nullptr)
                dqNode.push(node->right), dqVal.push(curSum + node->right->val);
        }
        return false;
    }
};

/*
// 递归
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (root == nullptr)
            return false;
        
        if (root->left == nullptr && root->right == nullptr)
            return targetSum - root->val == 0;
        return hasPathSum(root->left, targetSum - root->val) || hasPathSum(root->right, targetSum - root->val);
    }
};
*/