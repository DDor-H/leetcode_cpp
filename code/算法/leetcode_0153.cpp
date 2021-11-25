class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size();
        if (n == 1)
            return nums[0];
        int left = 0, right = nums.size() - 1;
        int mid = -1;
        while (left < right)
        {
            int mid = left + ((right - left) >> 1);
            if (nums[mid] < nums[right])  // 右半部分有序
                right = mid;
            else
                left = mid + 1;
        }
        return nums[left];
    }
};

/*
class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size();
        if (n == 1)
            return nums[0];
        int left = 0, right = nums.size() - 1;
        int mid = -1;
        while (left <= right)
        {
            if (nums[left] <= nums[right])
                break;
            int mid = left + ((right - left) >> 1);
            if (nums[left] <= nums[mid])  // 左半部分有序
            {
                if (nums[mid] < nums[mid + 1])
                    left = mid + 1;
                else
                    return nums[mid + 1];
            }
            else if (nums[mid] <= nums[right])  // 右半部分有序
            {
                if (nums[mid] > nums[mid - 1])
                    right = mid - 1;
                else
                    return nums[mid];
            }
        }
        return nums[left];
    }
};
*/