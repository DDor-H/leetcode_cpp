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

class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr)
            return nullptr;
        if (root->val > key)
            root->left = deleteNode(root->left, key);
        else if (root->val < key)
            root->right = deleteNode(root->right, key);
        else
        {
            if (!root->left)
                return root->right;
            if (!root->right)
                return root->left;
            TreeNode* node = root->right;
            while (node->left != nullptr)
                node = node->left;
            node->left = root->left;
            root = root->right;
        }
        return root;
    }
};


/*
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr)
            return nullptr;
        if (root->val > key)
            root->left = deleteNode(root->left, key);
        else if (root->val < key)
            root->right = deleteNode(root->right, key);
        else
        {
            if (root->left == nullptr && root->right == nullptr)
                root = nullptr;
            else
            {
                // 这两个条件只能满足一个
                if (root->left != nullptr)
                {
                    root->val = getLeftNextVal(root);
                    root->left = deleteNode(root->left, root->val);
                }
                else if (root->right != nullptr)
                {
                    root->val = getRightNextVal(root);
                    root->right = deleteNode(root->right, root->val);
                }
            }
        }
        return root;
    }

    int getRightNextVal(TreeNode* node)  // successor
    {
        node = node->right;
        while (node->left != nullptr) 
            node = node->left;
        return node->val;
    }

    int getLeftNextVal(TreeNode* node)  // predecessor
    {
        node = node->left;
        while (node->right != nullptr) 
            node = node->right;
        return node->val;
    }
};
*/