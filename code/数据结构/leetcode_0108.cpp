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
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return _sortedArrayToBST(nums, 0, nums.size() - 1);
    }

    TreeNode* _sortedArrayToBST(vector<int>& nums, int left, int right) 
    {
        if (left > right)
            return nullptr;
        // 总是选择中间位置左边的数字作为根节点
        // int mid = ((left + right) >> 1);
        // 总是选择中间位置右边的数字作为根节点
        // int mid = ((left + right + 1) >> 1);
        // 总是选择中间位置左右随机的数字作为根节点
        int mid = ((left + right + rand() % 2) >> 1);
        TreeNode* root = new TreeNode(nums[mid]);

        root->left = _sortedArrayToBST(nums, left, mid - 1);
        root->right = _sortedArrayToBST(nums, mid + 1, right);
        return root;
    }
};
