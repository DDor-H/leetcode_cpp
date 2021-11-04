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

// 广度遍历算法
class Solution {
private:
    vector<vector<int>> ans;
    unordered_map<TreeNode*, TreeNode*> parent;
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        if (root == nullptr)
            return ans;

        queue<TreeNode*> qu;
        queue<int> qu_sum;
        qu.push(root);
        qu_sum.push(0);

        while (!qu.empty())
        {
            TreeNode* node = qu.front();
            qu.pop();
            int rec = qu_sum.front() + node->val;
            qu_sum.pop();

            if (node->left == nullptr && node->right == nullptr)
            {
                if (rec == targetSum)
                    getPath(node);
            }
            else
            {
                if (node->left != nullptr)
                {
                    parent[node->left] = node;
                    qu.push(node->left);
                    qu_sum.push(rec);
                }
                if (node->right != nullptr)
                {
                    parent[node->right] = node;
                    qu.push(node->right);
                    qu_sum.push(rec);
                }
            }
        }
        return ans;
    }

    void getPath(TreeNode* node) 
    {
        vector<int> path;
        while (node != nullptr)
        {
            path.push_back(node->val);
            node = parent[node];
        }
        reverse(path.begin(), path.end());
        ans.push_back(path);
    }
};

/*
 // 深度遍历算法
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> ans;
        vector<int> path;
        _pathSum(root, targetSum, ans, path);
        return ans;
    }

    void _pathSum(TreeNode* node, int targetSum, vector<vector<int>>& ans, vector<int>& path) 
    {
        if (node == nullptr)
            return;

        path.push_back(node->val);
        targetSum -= node->val;
        if (targetSum == 0 && node->left == nullptr && node->right == nullptr)
            ans.push_back(path);

        _pathSum(node->left, targetSum, ans, path);
        _pathSum(node->right, targetSum, ans, path);
        path.pop_back();
    }
};
*/
