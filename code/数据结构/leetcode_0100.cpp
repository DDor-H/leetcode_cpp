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
 // 深度优先
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == nullptr && q == nullptr)
            return true;
        else if ((p == nullptr && q != nullptr) || (p != nullptr && q == nullptr))
            return false;
        else
            return (p->val == q->val) && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};
*/

//广度优先
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == nullptr && q == nullptr)
            return true;
        else if (p == nullptr || q == nullptr)
            return false;
        
        queue<TreeNode*> queue1, queue2;
        queue1.push(p);
        queue2.push(q);
        while (!queue1.empty() && !queue2.empty())
        {
            TreeNode* pt = queue1.front();
            queue1.pop();
            TreeNode* qt = queue2.front();
            queue2.pop();
            if (pt->val != qt->val)
                return false;
            TreeNode* pl = pt->left, *pr = pt->right, *ql = qt->left, *qr = qt->right;
            if ((pl == nullptr ^ ql == nullptr) || (pr == nullptr ^ qr == nullptr))
                return false;
            if (pl != nullptr && ql != nullptr)
            {
                queue1.push(pl);
                queue2.push(ql);
            }
            if (pr != nullptr && qr != nullptr)
            {
                queue1.push(pr);
                queue2.push(qr);
            }
        }
        return queue1.empty() && queue2.empty();
    }
};


