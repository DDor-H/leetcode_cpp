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

// 递归
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr)
            return true;
        return check(root, root);
    }

    bool check(TreeNode* l, TreeNode* r)
    {
        if (!l && !r)
            return true;
        if ((!l || !r) || (l->val != r->val))
            return false;
        return check(l->left, r->right) && check(l->right, r->left);
    }
};


 /*
 //迭代
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr)
            return true;
        return check(root, root);
    }

    bool check(TreeNode* LNode, TreeNode* RNode)
    {
        queue<TreeNode*> dq;
        dq.push(LNode);
        dq.push(RNode);
        while (!dq.empty())
        {
            TreeNode* l = dq.front();
            dq.pop();
            TreeNode* r = dq.front();
            dq.pop();

            if (!l && !r)
                continue;
            if ((!l || !r) || (l->val != r->val))
                return false;
            dq.push(l->left);
            dq.push(r->right);

            dq.push(l->right);
            dq.push(r->left);
        }
        return true;
    }
};
*/