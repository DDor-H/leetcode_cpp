class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> levelOrder;
        if (root == nullptr)
            return levelOrder;
        queue<TreeNode*> Q;
        Q.push(root);
        TreeNode* emptyNode = new TreeNode();
        while (!Q.empty())
        {
            int sz = Q.size();
            vector<int> level;
            for (int i = 0; i < sz; ++i)
            {
                TreeNode* front_node = Q.front();
                Q.pop();
                level.push_back(front_node->val);

                if (front_node->left)
                    Q.push(front_node->left);
                if (front_node->right)
                    Q.push(front_node->right);
            }
            levelOrder.push_back(level);
        }
        reverse(levelOrder.begin(), levelOrder.end());
        return levelOrder;
    }
};