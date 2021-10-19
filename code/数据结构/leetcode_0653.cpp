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

 // 中序遍历
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        unordered_map<int, TreeNode*> m;
        stack<TreeNode*> st;
        st.push(root);
        while (!st.empty())
        {
            TreeNode* node = st.top();
            st.pop();
            if (m.count(k - node->val) != 0 && node != m[k - node->val])
                return true;
            m.insert(make_pair(node->val, node));

            if (node->left != nullptr) st.push(node->left);
            if (node->right != nullptr) st.push(node->right);
        }
        return false;
    }
};

 /*
// 中序遍历
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        vector<int> v;
        inorder(root, v);
        int l = 0, r = v.size() - 1;
        while (l < r)
        {
            if (v[l] + v[r] == k)
                return true;
            else if (v[l] + v[r] < k)
                ++l;
            else
                --r;
        }
        return false;
    }

    void inorder(TreeNode* root, vector<int>& res) {
        if (root == nullptr)
            return;
        inorder(root->left, res);
        res.push_back(root->val);
        inorder(root->right, res);
    }

    void inorderTraversal(TreeNode* node, vector<int>& res)
    {
        stack<TreeNode*> st;
        while (!st.empty() || node != nullptr)
        {
            while (node != nullptr)
            {
                st.push(node);
                node = node->left;
            }
            node = st.top(), st.pop();
            res.push_back(node->val);
            if (node->right != nullptr)
                node = node->right;
        }
    }
};
*/