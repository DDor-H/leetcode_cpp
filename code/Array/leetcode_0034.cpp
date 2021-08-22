class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        return vector<int>({searchFirstEqualElement(nums, target), searchLastEqualElement(nums, target)});
    }

    // 变种1：查找第一个为目标元素的位置
    int searchFirstEqualElement(vector<int>& nums, int target)
    {
        int left = 0, right = nums.size() - 1;
        int mid = -1;
        while (left <= right)
        {
            mid = left + ((right - left) >> 1);
            if (nums[mid] > target)
                right = mid - 1;
            else if (nums[mid] < target)
                left = mid + 1;
            else 
            {
                if (mid == 0 || nums[mid - 1] != target)
                    return mid;
                right = mid - 1;
            }
        }
        return -1;
    }

    // 变种2：查找最后一个为目标元素的位置
    int searchLastEqualElement(vector<int>& nums, int target)
    {
        int left = 0, right = nums.size() - 1;
        int mid = -1;
        while (left <= right)
        {
            mid = left + ((right - left) >> 1);
            if (nums[mid] > target)
                right = mid - 1;
            else if (nums[mid] < target)
                left = mid + 1;
            else 
            {
                if (mid == nums.size() - 1 || nums[mid + 1] != target)
                    return mid;
                left = mid + 1;
            }
        }
        return -1;
    }

    // 变种3：查找第一个大于等于给定值的元素
    int searchFirstGreaterElement(vector<int>& nums, int target)
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
        return -1;
    }

    // 变种4：查找最后一个小于等于 target 的元素
    int searchLastLessElement(vector<int>& nums, int target)
    {
        int left = 0, right = nums.size() - 1;
        int mid = -1;
        while (left <= right)
        {
            mid = left + ((right - left) >> 1);
            if (nums[mid] <= target)
            {
                if (mid == nums.size() - 1 || nums[mid + 1] > target)
                    return mid;
                left = mid + 1;
            }
            else
                right = mid - 1;
        }
        return -1;
    }
};