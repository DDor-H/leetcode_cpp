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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (!root)
            return res;
        
        int level = 0;
        deque<TreeNode*> dq;
        dq.push_back(root);

        while (!dq.empty())
        {
            ++level;
            int level_size = dq.size();
            vector<int> tmp;
            if (level % 2 == 1)
            {
                while (level_size-- > 0)
                {
                    TreeNode* node = dq.front();
                    dq.pop_front();
                    tmp.push_back(node->val);
                    if (node->left)
                        dq.push_back(node->left);
                    if (node->right)
                        dq.push_back(node->right);
                }
            }
            else
            {
                while (level_size-- > 0)
                {
                    TreeNode* node = dq.back();
                    dq.pop_back();
                    tmp.push_back(node->val);
                    if (node->right)
                        dq.push_front(node->right);
                    if (node->left)
                        dq.push_front(node->left);
                }
            }
            res.push_back(tmp);
            tmp.clear();
        }
        return res;
    }
};