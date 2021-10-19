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

// 迭代
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        stack<TreeNode*> st;
        long long flag = (long long)INT_MIN - 1;
        while (!st.empty() || root != nullptr)
        {
            while (root != nullptr)
            {
                st.push(root);
                root = root->left;
            }

            root = st.top(), st.pop();
            if (root->val <= flag)
                return false;

            flag = root->val;
            root = root->right;
        }
        return true;
    }
};

/*
 // 递归
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return helper(root, LONG_MIN, LONG_MAX);
    }
    bool helper(TreeNode* node, long long lower, long long upper)
    {
        if (node == nullptr)
            return true;
        if (node->val <= lower || node->val >= upper)
            return false;
        return helper(node->left, lower, node->val) && helper(node->right, node->val, upper);
    }
};
*/