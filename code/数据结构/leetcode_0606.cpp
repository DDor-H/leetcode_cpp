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
 // 递归
class Solution {
public:
    string tree2str(TreeNode* root) {
        if (root == nullptr)
            return "";
        string strr = tree2str(root->right);
        string strl = tree2str(root->left);
        string strroot = to_string(root->val);

        if (strr != "")
            strroot += "(" + strl + ")" + "(" + strr + ")";
        else if (strl != "" && strr == "")
            strroot += "(" + strl + ")";

        return strroot;
    }
};
*/

// 迭代
class Solution {
public:
    string tree2str(TreeNode* root) {
        if (root == nullptr)
            return "";
        stack<TreeNode*> st;
        st.push(root);
        set<TreeNode*> se;
        string strroot = "";

        while (!st.empty())
        {
            TreeNode* node = st.top();
            if (se.count(node) != 0)
            {
                st.pop();
                strroot += ")";
            }
            else
            {
                se.insert(node);
                strroot += "(" + node->val;
                if (node->left == nullptr && node->right != nullptr)
                    strroot += "()";
                if (node->right != nullptr)
                    st.push(node->right);
                if (node->left != nullptr)
                    st.push(node->left);
            }
        }
        return strroot;
    }
};