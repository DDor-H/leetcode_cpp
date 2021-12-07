class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size();
        if (n == 1)
            return nums[0];
        return _binFind(nums, 0, n - 1);
    }

    int _binFind(vector<int>& nums, int left, int right)
    {
        while (left < right)
        {
            int mid = left + ((right - left) >> 1);
            if (nums[mid] < nums[right])
                right = mid;
            else if (nums[mid] > nums[right])
                left = mid + 1;
            else
                right -= 1;
        }
        return nums[left];
    }
};