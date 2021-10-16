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

 // BFS
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr)
            return 0;
        queue<TreeNode*> dq;
        dq.push(root);
        int level = 0;
        while (!dq.empty())
        {
            int curLevelSize = dq.size();
            while (curLevelSize-- > 0)
            {
                TreeNode* node = dq.front();
                dq.pop();
                if (node->left != nullptr)
                    dq.push(node->left);
                if (node->right != nullptr)
                    dq.push(node->right);
            }
            ++level;
        }
        return level;
    }
};

/*
 // DFS
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr)
            return 0;
        return root == nullptr ? 0 : max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};
*/