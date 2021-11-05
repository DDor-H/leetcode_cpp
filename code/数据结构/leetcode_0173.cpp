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


// 迭代
class BSTIterator {
private:
    stack<TreeNode*> stk;
    TreeNode* cur;
public:
    BSTIterator(TreeNode* root)
    {
        cur = root;
    }
    
    int next() {
        while (cur != nullptr)
        {
            stk.push(cur);
            cur = cur->left;
        }
        cur = stk.top();
        stk.pop();
        int res = cur->val;
        cur = cur->right;
        return res;
    }
    
    bool hasNext() {
        return cur != nullptr || !stk.empty();
    }
};


/*
 // 使用数组存储
class BSTIterator {
private:
    void _inorder(vector<int>& arr, TreeNode* node)
    {
        if (node == nullptr)
            return;
        _inorder(arr, node->left);
        arr.push_back(node->val);
        _inorder(arr, node->right);
    }

    vector<int> inorder(TreeNode* node)
    {
        vector<int> arr_tmp;
        _inorder(arr_tmp, node);
        return arr_tmp;
    }

    vector<int> arr;
    int idx;
public:
    BSTIterator(TreeNode* root) : idx(0), arr(inorder(root))
    {}
    
    int next() {
        return arr[idx++];
    }
    
    bool hasNext() {
        return (idx < arr.size());
    }
};
*/
