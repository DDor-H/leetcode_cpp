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

 /*
 //递归
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int m = inorder.size();
        int n = postorder.size();
        if (m == 0 || n == 0 || m != n)
            return nullptr;
        return _buildTree(inorder, 0, m, postorder, 0, n);
    }

    TreeNode* _buildTree(vector<int>& inorder, int left1, int right1, vector<int>& postorder, int left2, int right2)
    {
        if (left1 >= right1 || left2 >= right2)
            return nullptr;
        int key = postorder[right2 - 1];
        TreeNode* node = new TreeNode(key);

        int index = left1;
        while (index < right1)
        {
            if (inorder[index] == key)
                break;
            else
                ++index;
        }
        int leftlen = index - left1;
        int rightlen = right1 - index - 1;
        node->left = leftlen == 0 ? nullptr : _buildTree(inorder, left1, left1 + leftlen, postorder, left2, left2 + leftlen);
        node->right = rightlen == 0 ? nullptr : _buildTree(inorder, index + 1, right1, postorder, left2 + leftlen, right2 - 1);

        return node;
    }
};
*/

 //递归
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int m = inorder.size();
        int n = postorder.size();
        if (m == 0 || n == 0 || m != n)
            return nullptr;
        int inorderIndex = m - 1;
        TreeNode* root = new TreeNode(postorder[n - 1]);
        stack<TreeNode*> st;
        st.push(root);

        for (int i = n - 2; i >= 0; --i)
        {
            TreeNode* node = st.top();
            int postOrderVal = postorder[i];
            if (node->val != inorder[inorderIndex])
            {
                node->right = new TreeNode(postOrderVal);
                st.push(node->right);
            }
            else
            {
                while(!st.empty() && st.top()->val == inorder[inorderIndex])
                {
                    node = st.top(); // 先换top，最极端情况，没有右分支
                    st.pop();
                    --inorderIndex;
                }
                node->left = new TreeNode(postOrderVal);
                st.push(node->left);
            }
        }
        return root;
    }
};
