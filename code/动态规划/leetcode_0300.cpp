// 动态规划 + 二分查找
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        int len = 1;
        vector<int> dp(n + 1, 0);
        dp[len] = nums[0];
        for (int i = 1; i < n; ++i)
            if (nums[i] > dp[len])
                dp[++len] = nums[i];
            else
            {
                int pos = binaryFind(dp, len, nums[i]);
                dp[pos] = nums[i];
            }
        return len;
    }

    int binaryFind(vector<int>& dp, int len, int data)
    {
        int l = 1, r = len, pos = 0;
        while (l <= r)
        {
            int mid = ((l + r) >> 1);
            if (data > dp[mid])
            {
                pos = mid;
                l = mid + 1;
            }
            else 
                r = mid - 1;
        }
        return pos + 1;
    }
};


/*
// 动态规划
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 1);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < i; ++j)
                if (nums[j] < nums[i])
                    dp[i] = max(dp[i], dp[j] + 1);
        return *max_element(dp.begin(), dp.end());
    }
};
*/