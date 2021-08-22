class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int res = 0;
        int absDiff = INT_MAX;
        int Sum = 0;
        sort(nums.begin(), nums.end());
        int len = nums.size();

        for (int i = 0; i < len - 2; ++i)
        {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;
            for (int j = i + 1, k = len - 1; j < k;)
            {
                if (j > i + 1 && nums[j] == nums[j - 1])
                {
                    ++j;
                    continue;
                }

                Sum = nums[i] + nums[j] + nums[k];
                if (Sum == target)
                    return Sum;
                    
                res = abs(Sum - target) < absDiff ? Sum : res;
                absDiff = abs(Sum - target) < absDiff ? abs(Sum - target) : absDiff;

                if (Sum - target > 0)
                    --k;
                else
                    ++j;
            }
        }
        return res;
    }
};