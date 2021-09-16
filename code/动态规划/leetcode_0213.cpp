class Solution {
public:
    int rob(vector<int>& nums) {
        int len = nums.size();
        if (len == 1)
            return nums[0];
        if (len == 2)
            return max(nums[0], nums[1]);

        return max(rotateRob(nums, 0, len - 2), rotateRob(nums, 1, len - 1));
    }
    int rotateRob(vector<int>& nums, int start, int end)
    {
        int len = end - start + 1;
        if (len == 2)
            return max(nums[start], nums[end]);

        int a = nums[start], b = max(nums[start], nums[start + 1]), c = 0;

        for (int i = 2; i < len; ++i)
        {
            c = max(a + nums[start + i], b);
            a = b;
            b = c;
        }
        return c;
    }
};