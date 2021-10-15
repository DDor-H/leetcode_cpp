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

// 方法三：Morris 遍历
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
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
                    res.push_back(cur1->val);
                    cur2->right = cur1;
                    cur1 = cur1->left;
                    continue;
                }
                else
                    cur2->right = nullptr;
            }
            else
                res.push_back(cur1->val);
            cur1 = cur1->right;
        }
        return res;
    }
};


/*
// 方法二：栈迭代
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        if (root == nullptr)
            return vector<int>();
        vector<int> res;
        stack<TreeNode*> st;
        st.push(root);
        while (!st.empty())
        {
            TreeNode* node = st.top();
            res.push_back(node->val);
            st.pop();
            if (node->right != nullptr)
                st.push(node->right);
            if (node->left != nullptr)
                st.push(node->left);
        }
        return res;
    }
};


/*
 // 方法一：递归
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        if (root == nullptr)
            return vector<int>();
        vector<int> res;
        _preorderTraversal(root, res);
        return res;
    }
    void _preorderTraversal(TreeNode* node, vector<int>& res)
    {
        if (node == nullptr)
            return;
        res.push_back(node->val);
        _preorderTraversal(node->left, res);
        _preorderTraversal(node->right, res);
    }
};
*/