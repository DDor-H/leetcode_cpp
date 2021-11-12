class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size();
        if (n <= 0)
            return;
        int prev = -1;
        int i = 0;
        while (i < n)
        {
            if (nums[i] != 0)
                swap(nums[++prev], nums[i]);
            ++i;
        }
    }
};