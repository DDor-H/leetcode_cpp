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
    vector<TreeNode*> generateTrees(int n) {
        if (n)
            return generateTrees(1, n);
        else
            return vector<TreeNode*>{};
    }

    vector<TreeNode*> generateTrees(int left, int right) 
    {
        vector<TreeNode*> res;
        if (left > right)
        {
            res.push_back(nullptr);
            return res;
        }

        for (int i = left; i <= right; ++i)
        {
            vector<TreeNode*> leftTrees = generateTrees(left, i - 1);
            vector<TreeNode*> rightTrees = generateTrees(i + 1, right);

            for (TreeNode* leftNode : leftTrees)
            {
                for (TreeNode* rightNode : rightTrees)
                {
                    TreeNode* root = new TreeNode(i);
                    root->left = leftNode;
                    root->right = rightNode;
                    res.push_back(root);
                }
            }
        }
        return res;
    }
};