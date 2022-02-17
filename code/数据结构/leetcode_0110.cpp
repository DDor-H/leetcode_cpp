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

/*
 // 自顶向下递归
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if (root == nullptr)
            return true;
        else
            return (abs(height(root->left) - height(root->right)) <= 1) && isBalanced(root->left) && isBalanced(root->right);
    }
    int height(TreeNode* node)
    {
        if (node == nullptr)
            return 0;
        else
            return max(height(node->left), height(node->right)) + 1;
    }
};
*/

 // 自底向上递归
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        return height(root) >= 0;
    }
    int height(TreeNode* node)
    {
        if (node == nullptr)
            return 0;
        int height1 = height(node->left);
        int height2 = height(node->right);
        if (height1 == -1 || height2 == -1 || abs(height1 - height2) > 1)
            return -1;
        return max(height1, height2) + 1;
    }
};



