class Solution {
public:
    int getMaxLen(vector<int>& nums) {
        int len = nums.size();
        int curPositive = (nums[0] > 0);
        int curNegative = (nums[0] < 0);
        int maxLength = curPositive;
        
        for (int i = 1; i < len; ++i)
        {
            if (nums[i] > 0)
            {
                ++curPositive;
                curNegative = curNegative ? curNegative + 1 : 0;
            }
            else if (nums[i] < 0)
            {
                // 负数会改变正负号
                int newPositive = curNegative ? curNegative + 1 : 0;
                int newNegative = curPositive + 1;
                curPositive = newPositive;
                curNegative = newNegative;
            }
            else
            {
                curPositive = curNegative = 0;
            }
            maxLength = max(curPositive, maxLength);
        }
        return maxLength;
    }
};