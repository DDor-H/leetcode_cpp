// 动态规划(超时)
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int n = nums.size();
        if (n < 3)
            return false;
        vector<int> dp(n, 1);
        for (int i = 1; i < n; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (nums[j] < nums[i])
                {
                    dp[i] = max(dp[i], dp[j] + 1);
                    if (dp[i] >= 3)
                        return true;
                }                    
            }
        }
        return false;
    }
};

/*
// 双指针（也可返回是哪三个序列）
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int n = nums.size();
        if (n < 3)
            return false;
        int small = nums[0], mid = nums[0];
        int length = 1;
        for (int i = 1; i < n; ++i)
        {
            if (mid < nums[i])
            {
                // small、mid、*
                if (++length == 3)
                    return true;
                mid = nums[i];
            }
            else if (small < nums[i])
                // small、*、mid
                mid = nums[i];
            else if (i + 1 < n && nums[i] < nums[i + 1] && nums[i + 1] <= mid)
            {
                // 前提是 *、small、mid
                // 条件 *、* + 1 整体小于 small、mid
                small = mid = nums[i];
                length = 1;
            }
        }
        return false;
    }
};

/*
// 双指针
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int n = nums.size();
        if (n < 3)
            return false;
        int small = INT_MAX, mid = INT_MAX;
        for (auto& e : nums)
        {
            if (e <= small)
                small = e;
            else if (e <= mid)
                mid = e;
            else
                return true;
        }
        return false;
    }
};
*/