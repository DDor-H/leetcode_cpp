/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// 一次遍历
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* ancestor = root;
        while (ancestor != NULL)
        {
            if (ancestor->val > p->val && ancestor->val > q->val)
                ancestor = ancestor->left;
            else if (ancestor->val < p->val && ancestor->val < q->val)
                ancestor = ancestor->right;
            else
                break;
        }
        return ancestor;
    }
};

/*
// 两次遍历
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<TreeNode*> path_p = getPath(root, p);
        vector<TreeNode*> path_q = getPath(root, q);

        int i = 0;
        for (; i < path_p.size() && i < path_q.size(); ++i)
        {
            if (path_p[i] != path_q[i])
                break;
        }
        return path_p[i - 1];
    }

    vector<TreeNode*> getPath(TreeNode* root, TreeNode* p)
    {
        vector<TreeNode*> path;
        while (root->val != p->val)
        {
            path.push_back(root);
            if (root->val > p->val)
                root = root->left;
            else
                root = root->right;
        }
        path.push_back(root);
        return path;
    }
};
*/