/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// 记录父节点
class Solution {
private:
    unordered_map<int, TreeNode*> parent;
    unordered_map<int, bool> vis;
public:
    void dfs(TreeNode* root)
    {
        if (root->left != NULL)
        {
            parent[root->left->val] = root;
            dfs(root->left);
        }
        if (root->right != NULL)
        {
            parent[root->right->val] = root;
            dfs(root->right);
        }
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == NULL || root == p || root == q)
            return root;
        dfs(root);
        while (p != NULL)
        {
            vis[p->val] = true;
            p = parent[p->val];
        }
        while (q != NULL)
        {
            if (vis[q->val]) return q;
            q = parent[q->val];
        }
        return NULL;
    }
};

/*
 // 递归
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == NULL || root == p || root == q)
            return root;
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        if (left != NULL && right != NULL)
            return root;
        return left != NULL ? left : right;
    }
};
*/