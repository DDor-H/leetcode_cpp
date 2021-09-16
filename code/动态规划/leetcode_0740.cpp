class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        int maxVal = 0;
        for (auto &e : nums)
            maxVal = max(maxVal, e);
        
        vector<int> dp(maxVal + 1, 0);
        for (auto &e : nums)
            dp[e] += e;
        
        return rob(dp);
    }

    int rob(vector<int>& nums)
    {
        int len = nums.size();
        if (len == 2)
            return max(nums[0], nums[1]);
        int a = nums[0], b = max(nums[0], nums[1]), c = 0;
        for (int i = 2; i < len; ++i)
        {
            c = max(a + nums[i], b);
            a = b;
            b = c;
        }
        return c;
    }
};