class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, 1);
        int left = 1, right = 1;
        for (int i = 1; i < n; ++i)
        {
            left *= nums[i - 1];
            ans[i] *= left;
            right *= nums[n - i];
            ans[n - i - 1] *= right;
        }
        return ans;
    }
};