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


// 方法二：迭代
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        if (root == nullptr)
            return vector<int>();
        vector<int> res;
        
        stack<TreeNode*> st;
        TreeNode* prev = nullptr;
        while (root != nullptr || !st.empty())
        {
            while (root != nullptr)
            {
                st.push(root);
                root = root->left;
            }

            root = st.top();
            st.pop();

            if (root->right == nullptr || root->right == prev)
            {
                res.push_back(root->val);
                prev = root;
                root = nullptr;
            }
            else
            {
                // 还有右节点，暂时不能访问，再压回去
                st.push(root);
                root = root->right;
            }
        }
        return res;
    }
};

/*
 // 方法一：递归
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        if (root == nullptr)
            return vector<int>();
        vector<int> res;
        _postorderTraversal(root, res);
        return res;
    }
    void _postorderTraversal(TreeNode* node, vector<int>& res)
    {
        if (node == nullptr)
            return;
        _postorderTraversal(node->left, res);
        _postorderTraversal(node->right, res);
        res.push_back(node->val);
    }
};
*/