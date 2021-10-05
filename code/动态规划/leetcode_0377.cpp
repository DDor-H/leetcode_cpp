class Solution {
public:
    int _combinationSum4(vector<int>& nums, int target) {
        vector<int> dp(target + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= target; ++i)
        {
            for (auto& num : nums)
            {
                // dp[i - num] < INT_MAX - dp[i]
                // dp[i - num] + dp[i] < INT_MAX  // 这种可能会为负，越界
                // 题目要求答案符合 32 位整数范围，所以不能越 size_t 的范围，越界的都是不符合的
                if (i >= num && dp[i - num] < INT_MAX - dp[i])
                    dp[i] += dp[i - num];
            }
        }
        return dp[target];
    }

    int combinationSum4(vector<int>& nums, int target) {
        vector<size_t> dp(target + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= target; ++i)
        {
            for (auto& num : nums)
            {
                if (i >= num)
                    dp[i] += dp[i - num];
            }
        }
        return dp[target];
    }
};