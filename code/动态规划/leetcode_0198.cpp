class Solution {
public:
    int rob(vector<int>& nums) {
        int len = nums.size();
        if (len == 1)
            return nums[0];
        
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

/*
class Solution {
public:
    int rob(vector<int>& nums) {
        int len = nums.size();
        if (len == 1)
            return nums[0];
        
        vector<int> dp(len, 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);

        for (int i = 2; i < len; ++i)
            dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);

        return dp[len - 1];
    }
};


/*
class Solution {
public:
    int rob(vector<int>& nums) {
        int len = nums.size();
        if (len == 1)
            return nums[0];
        
        vector<int> dp(len + 1, 0);
        dp[1] = nums[0];
        dp[2] = nums[1];

        for (int i = 3; i <= len; ++i)
        {
            dp[i] = max(dp[i - 2], dp[i - 3]) + nums[i - 1];
        }

        return max(dp[len - 1], dp[len]);
    }
};
*/