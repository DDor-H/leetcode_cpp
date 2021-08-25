// 方法一：
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int len = nums.size();
        if (len == 1)
            return nums[0];
        int maxSum = INT_MIN;
        for (int i = 0; i < len; ++i)
        {
            int curSum = 0;
            for (int j = i; j < len; ++j)
            {
                curSum += nums[j];
                if (curSum > maxSum)
                    maxSum = curSum;
            }
        }
        return maxSum;
    }
};

// 方法二：
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int len = nums.size();
        if (len == 1)
            return nums[0];
        vector<int> dp(len);
        
        dp[0] = nums[0];
        int maxNum = dp[0];
        for (int i = 1; i < len; ++i)
        {
            dp[i] = max(dp[i - 1] + nums[i], nums[i]);
            maxNum = max(dp[i], maxNum);
        }
        return maxNum;
    }
};

// 方法三：
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int len = nums.size();
        if (len == 1)
            return nums[0];
        
        int maxNum = INT_MIN;
        int curSum = 0;
        for (int i = 0; i < len; ++i)
        {
            curSum = curSum + nums[i];
            maxNum = max(curSum, maxNum);
            curSum = max(curSum, 0);
        }
        return maxNum;
    }
};

// 方法四：
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int len = nums.size();
        if (len == 1)
            return nums[0];
        
        return maxSubArrayHelper(nums, 0, len - 1);
    }

    int maxSubArrayHelper(vector<int>& nums, int left, int right)
    {
        if (left == right)
            return nums[left];
        int mid = (left + right) / 2;
        int leftSum = maxSubArrayHelper(nums, left, mid);
        int rightSum = maxSubArrayHelper(nums, mid + 1, right);
        int midSum = findMaxCrossingSubarray(nums, left, mid, right);
        return max(max(leftSum, rightSum), midSum);
    }

    int findMaxCrossingSubarray(vector<int>& nums, int left, int mid, int right)
    {
        int leftSum = INT_MIN;
        int sum = 0;
        for (int i = mid; i >= left; --i)
        {
            sum = sum + nums[i];
            leftSum = max(sum, leftSum);
        }

        int rightSum = INT_MIN;
        sum = 0;
        for (int i = mid + 1; i <= right; ++i)
        {
            sum = sum + nums[i];
            rightSum = max(sum, rightSum);
        }
        return leftSum + rightSum;
    }
};