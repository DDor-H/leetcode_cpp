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

// 方法三：Morris遍历
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        if (root == nullptr)
            return vector<int>();
        vector<int> res;
        
        TreeNode* cur1 = root;
        TreeNode* cur2 = nullptr;
        while (cur1 != nullptr)
        {
            cur2 = cur1->left;
            if (cur2 != nullptr)
            {
                while (cur2->right != nullptr && cur2->right != cur1)
                    cur2 = cur2->right;
                if (cur2->right == nullptr)
                {
                    cur2->right = cur1;
                    cur1 = cur1->left;
                    continue;
                }
                else
                    cur2->right = nullptr;
            }
            res.push_back(cur1->val);
            cur1 = cur1->right;
        }
        return res;
    }
};


/*
// 方法二：迭代
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        if (root == nullptr)
            return vector<int>();
        vector<int> res;
        
        stack<TreeNode*> st;
        while (!st.empty() || root != nullptr)
        {
            while (root != nullptr)
            {
                st.push(root);
                root = root->left;
            }

            TreeNode* node = st.top();
            st.pop();
            res.push_back(node->val);

            if (node->right != nullptr)
                root = node->right;
        }
        return res;
    }
};

 /*
 // 方法一：递归
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        if (root == nullptr)
            return vector<int>();
        vector<int> res;
        _inorderTraversal(root, res);
        return res;
    }
    void _inorderTraversal(TreeNode* node, vector<int>& res)
    {
        if (node == nullptr)
            return;
        _inorderTraversal(node->left, res);
        res.push_back(node->val);
        _inorderTraversal(node->right, res);
    }
};
*/