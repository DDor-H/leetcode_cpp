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
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (root == nullptr)
            return vector<vector<int>>();
        
        queue<TreeNode*> dq;
        vector<vector<int>> res;
        dq.push(root);
        while (!dq.empty())
        {
            int curLevelSize = dq.size();
            vector<int> tmp;
            for (int i = 0; i < curLevelSize; ++i)
            {
                TreeNode* node = dq.front();
                dq.pop();
                tmp.push_back(node->val);
                if (node->left != nullptr)
                    dq.push(node->left);
                if (node->right != nullptr)
                    dq.push(node->right);
            }
            res.push_back(tmp);
        }
        return res;
    }
};