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

// 先序遍历 + 填充NULL + KMP
class Solution {
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        int maxVal = INT_MIN;
        getMaxElement(root, maxVal);
        getMaxElement(subRoot, maxVal);
        int lNULL = maxVal + 1;
        int rNULL = maxVal + 2;

        vector<int> sOrder, tOrder;
        preOrder(root, sOrder, lNULL, rNULL);
        preOrder(subRoot, tOrder, lNULL, rNULL);

        int m = sOrder.size(), n = tOrder.size();
        vector<int> prefix(n, 0);
        prefix_table(tOrder, prefix);

        return kmp(sOrder, tOrder, prefix);
        
    }
    void getMaxElement(TreeNode* root, int& maxVal)
    {
        if (!root)
            return;
        maxVal = max(root->val, maxVal);
        getMaxElement(root->left, maxVal);
        getMaxElement(root->right, maxVal);
    }

    void preOrder(TreeNode* root, vector<int>& order, int lNULL, int rNULL)
    {
        if (!root)
            return;
        order.push_back(root->val);
        if (root->left)
            preOrder(root->left, order, lNULL, rNULL);
        else
            order.push_back(lNULL);
        if (root->right)
            preOrder(root->right, order, lNULL, rNULL);
        else
            order.push_back(rNULL);
    }

    void prefix_table(vector<int>& pattern, vector<int>& prefix)
    {
        int len = 0, n = pattern.size();
        prefix[0] = 0;
        int i = 1;
        while (i < n)
        {
            if (pattern[i] == pattern[len])
            {
                ++len;
                prefix[i] = len;
                ++i;
            }
            else
            {
                if (len > 0)
                    len = prefix[len - 1];
                else
                {
                    prefix[i] = len;
                    ++i;
                }
            }
        }
        // 前后缀表 后移一位 首位填充 -1
        for (int j = n - 1; j > 0; --j)
            prefix[j] = prefix[j - 1];
        prefix[0] = -1;
    }

    bool kmp(vector<int>& sOrder, vector<int>& tOrder, vector<int>& prefix)
    {
        int m = sOrder.size(), n = tOrder.size();
        int i = 0, j = 0;
        while (i < m)
        {
            if (sOrder[i] == tOrder[j])
            {
                if (j == n - 1)
                    return true;
                ++i, ++j;
            }
            else
            {
                j = prefix[j];
                if (j == -1)
                    ++i, ++j;
            }
        } 
        return false;
    }
};

/*
 // dfs
class Solution {
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        return dfs(root, subRoot);
    }

    bool dfs(TreeNode* o, TreeNode* t)
    {
        if (!o)
            return false;
        return check(o, t) || dfs(o->left, t) || dfs(o->right, t);
    }

    bool check(TreeNode* o, TreeNode* t)
    {
        if (!o && !t)
            return true;
        if ((!o && t) || (o && !t) || (o->val != t->val))
            return false;
        return check(o->left, t->left) && check(o->right, t->right);
    }
};
*/