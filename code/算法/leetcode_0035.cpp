class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        return serchFirstGreaterInsert(nums, target);
    }

    int serchFirstGreaterInsert(vector<int>& nums, int target)
    {
        int left = 0, right = nums.size() - 1;
        int mid = -1;
        while (left <= right)
        {
            mid = left + ((right - left) >> 1);
            if (nums[mid] >= target)
            {
                if (mid == 0 || nums[mid - 1] < target)
                    return mid;
                right = mid - 1;
            }
            else
                left = mid + 1;
        }
        return nums.size();
    }
};