class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int len = nums.size();
        if (len == 1)
            return nums[0];
        
        int curMax = 1;
        int curMin = 1;
        int allMax = INT_MIN;
        for (int i = 0; i < len; ++i)
        {
            if (nums[i] < 0)
            {
                int tmp = curMax;
                curMax = curMin;
                curMin = tmp;
            }
            curMax = max(curMax * nums[i], nums[i]);
            curMin = min(curMin * nums[i], nums[i]);
            allMax = max(allMax, curMax);
        }
        return allMax;
    }
};