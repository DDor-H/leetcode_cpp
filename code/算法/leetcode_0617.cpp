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

  // 广度优先
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if (root1 == nullptr)
            return root2;
        if (root2 == nullptr)
            return root1;
        TreeNode* root = new TreeNode(root1->val + root2->val);
        queue<TreeNode*> q;
        queue<TreeNode*> q1;
        queue<TreeNode*> q2;
        q.push(root);
        q1.push(root1);
        q2.push(root2);
        while (!q1.empty() && !q2.empty())
        {
            TreeNode* node = q.front(), *nodel = q1.front(), *noder = q2.front();
            q.pop(), q1.pop(), q2.pop();
            TreeNode* left1 = nodel->left, *left2 = noder->left, *right1 = nodel->right, *right2 = noder->right;
            if (left1 != nullptr && left2 != nullptr)
            {
                TreeNode* left = new TreeNode(left1->val + left2->val);
                node->left = left;
                q.push(left);
                q1.push(left1);
                q2.push(left2);
            }
            else if (left1 != nullptr)
                node->left = left1;
            else if (left2 != nullptr)
                node->left = left2;

            if (right1 != nullptr && right2 != nullptr)
            {
                TreeNode* right = new TreeNode(right1->val + right2->val);
                node->right = right;
                q.push(right);
                q1.push(right1);
                q2.push(right2);
            }
            else if (right1 != nullptr)
                node->right = right1;
            else if (right2 != nullptr)
                node->right = right2;
        }
        return root;
    }
};


/*
 // 深度优先
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if (root1 == nullptr)
            return root2;
        if (root2 == nullptr)
            return root1;
        TreeNode* node = new TreeNode(root1->val + root2->val);
        node->left = mergeTrees(root1->left, root2->left);
        node->right = mergeTrees(root1->right, root2->right);
        return node;
    }
};
*/