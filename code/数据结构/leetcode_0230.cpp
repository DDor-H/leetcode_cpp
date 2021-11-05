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

// 中序遍历
class MyBst {
private:
    TreeNode* root;
    unordered_map<TreeNode*, int> map;

public:
    MyBst (TreeNode* root)
    {
        this->root = root;
        countNum(this->root);
    }
    int countNum(TreeNode* node)
    {
        if (node == nullptr)
            return 0;
        map[node] = countNum(node->left) + countNum(node->right) + 1;
        return map[node];
    }
    int getNum(TreeNode* node)
    {
        if (node != nullptr && map.count(node))
            return map[node];
        else
            return 0;
    }
    int kthSmallestVal(int k)
    {
        TreeNode* node = root;
        while (node != nullptr)
        {
            int left = getNum(node->left);
            if (left == k - 1)
                break;
            else if (left > k - 1)
                node = node->left;
            else
            {
                node = node->right;
                k -= left + 1;
            }
        }
        return node->val;
    }
};

class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        MyBst bst(root);
        return bst.kthSmallestVal(k);
    }
};
    

/*
 // 中序遍历
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> stk;
        while (root != nullptr || !stk.empty())
        {
            while (root != nullptr)
            {
                stk.push(root);
                root = root->left;
            }
            root = stk.top();
            stk.pop();
            if (--k == 0)
                break;
            root = root->right;
        }
        return root->val;
    }
};
*/