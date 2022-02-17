/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

 // 递归法
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int pre_size = preorder.size();
        int in_size = inorder.size();
        if (pre_size == 0 || in_size == 0 || pre_size != in_size)
            return NULL;
        
        TreeNode* root = new TreeNode(preorder[0]);
        int inorderIndex = 0;
        stack<TreeNode*> stk;
        stk.push(root);
        for (int i = 1; i < pre_size; ++i)
        {
            int preorderVal = preorder[i];
            TreeNode* node = stk.top();
            if (node->val != inorder[inorderIndex])
            {
                TreeNode* leftNode = new TreeNode(preorderVal);
                node->left = leftNode;
                stk.push(leftNode);
            }
            else
            {
                while (!stk.empty() && stk.top()->val == inorder[inorderIndex])
                {
                    node = stk.top();
                    stk.pop();
                    ++inorderIndex;
                }
                node->right = new TreeNode(preorderVal);
                stk.push(node->right);
            }
        }
        return root;
    }
};


/*
 // 递归法
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int pre_size = preorder.size();
        int in_size = inorder.size();
        if (pre_size == 0 || in_size == 0 || pre_size != in_size)
            return NULL;
        return _buildTree(preorder, 0, pre_size - 1, inorder, 0, in_size - 1);
    }
    TreeNode* _buildTree(vector<int>& preorder, int left1, int right1, vector<int>& inorder, int left2, int right2)
    {
        int x = preorder[left1];
        int pos = left2;
        while (inorder[pos] != x && pos <= right2)
            ++pos;
        if (pos > right2)
            return NULL; // 异常处理
        int l_size = pos - left2;
        int r_size = right2 - pos;
        TreeNode* node = new TreeNode(x);
        if (l_size > 0)
            node->left = _buildTree(preorder, left1 + 1, left1 + l_size, inorder, left2, pos - 1);
        if (r_size > 0)
            node->right = _buildTree(preorder, left1 + 1 + l_size, right1 , inorder, pos + 1, right2);
        return node;
    }
};
*/