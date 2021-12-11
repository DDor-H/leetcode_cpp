// 动态规划
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size(), maxLen = 0, ans = 0;
        // dp[i]：表示nums前 i 个序列的最长递增子序列长度
        // cnt[i]：表示前 i 个序列最长递增子序列的个数
        // 最长递增子序列的长度变化后，只是前面那些长度的序列长度多了一个，个数没变
        // 但当新增的一个数字后，最长长度没变，说明前面有一个maxLen - 1的多个序列，则cnt需要累加
        vector<int> dp(n), cnt(n);
        for (int i = 0; i < n; ++i)
        {
            dp[i] = 1, cnt[i] = 1;
            for (int j = 0; j < i; ++j)
            {
                if (nums[j] < nums[i])
                {
                    if (dp[j] + 1 > dp[i])
                    {
                        dp[i] = dp[j] + 1;
                        cnt[i] = cnt[j];
                    }
                    else if (dp[j] + 1 == dp[i])
                        cnt[i] += cnt[j];
                }
            }

            if (dp[i] > maxLen)
            {
                maxLen = dp[i];
                ans = cnt[i];
            }
            else if (dp[i] == maxLen)
                ans += cnt[i];
        }
        return ans;
    }
};