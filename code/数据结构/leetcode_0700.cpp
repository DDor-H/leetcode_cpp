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

 // 方法二：递归
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if (root == nullptr || root->val == val)
            return root;
        return root->val > val ? searchBST(root->left, val) : searchBST(root->right, val);
    }
};

 /*
 // 方法一：迭代
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        while (root != nullptr)
        {
            if (root->val == val)
                return root;
            if (root->val > val)
                root = root->left;
            else
                root = root->right;
        }
        return nullptr;
    }
};
*/