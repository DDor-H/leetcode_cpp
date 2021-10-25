class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if (n < 3)
            return n;
        int left = 2, right = 2;
        while (right < n)
        {
            if (nums[right] != nums[left - 2])
            {
                nums[left] = nums[right];
                ++left;
            }
            ++right;
        }
        return left;
    }
};