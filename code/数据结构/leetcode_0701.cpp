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
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (root == nullptr)
            return new TreeNode(val);

        TreeNode* prev = nullptr;
        TreeNode* p = root;
        while (p != nullptr)
        {
            prev = p;
            if (p->val < val)
                p = p->right;
            else
                p = p->left;
        }
        p = new TreeNode(val);
        if (prev->val > val)
            prev->left = p;
        else
            prev->right = p;
        return root;
    }
};