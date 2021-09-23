class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int len = nums.size();
        if (len < 3)
            return 0;
        
        int res = 0;
        int d = nums[1] - nums[0];
        int l = 2;
        for (int i = 2; i < len; ++i)
        {
            if (nums[i] - nums[i - 1] == d)
                ++l;
            else
            {
                res += (l >= 3 ? (l - 1) * (l - 2) / 2 : 0);
                l = 2;
                d = nums[i] - nums[i - 1];
            }
        }
        res += (l >= 3 ? (l - 1) * (l - 2) / 2 : 0);
        return res;
    }
};