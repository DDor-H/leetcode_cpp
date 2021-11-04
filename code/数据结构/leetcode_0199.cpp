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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;
        if (!root)
            return ans;
        queue<TreeNode*> qu;
        qu.push(root);
        while (!qu.empty())
        {
            int lens = qu.size();
            for (int i = 0; i < lens; ++i)
            {
                TreeNode* node = qu.front();
                qu.pop();
                if (i == 0)
                    ans.push_back(node->val);
                if (node->right != nullptr)
                    qu.push(node->right);
                if (node->left != nullptr)
                    qu.push(node->left);
            }
        }
        return ans;
    }
};