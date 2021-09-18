class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int len = nums.size();
        if (len == 1)
            return nums[0];

        int maxCurSum = nums[0];
        int maxSum = nums[0];
        int minCurSum = nums[0];
        int minSum = nums[0];
        int Sum = nums[0];

        for (int i = 1; i < len; ++i)
        {
            Sum += nums[i];
            maxCurSum = max(maxCurSum + nums[i], nums[i]);
            maxSum = max(maxCurSum, maxSum);
            minCurSum = min(minCurSum + nums[i], nums[i]);
            minSum = min(minCurSum, minSum);
        }

        // 防止全是负数的情况
        return max(maxSum, Sum - minSum == 0 ? maxSum : (Sum - minSum));
    }
};