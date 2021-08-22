// 方法一：
class Solution {
public:
    int search(vector<int>& nums, int target) {
        for (int i =0 ; i < nums.size(); ++i)
        {
            if (nums[i] == target)
                return i;
        }
        return -1;
    }
};

// 方法二：
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        int mid = -1;
        while (left <= right)
        {
            mid = left + (right - left) / 2.f;
            if (nums[mid] == target)
                return mid;
            else if (nums[mid] > nums[left])  // 左半部分有序
            {
                // 是否在有序部分中
                if (nums[left] <= target && nums[mid] > target)
                    right = mid - 1;
                else
                    left = mid + 1;
            }
            else if (nums[mid] < nums[right])  // 右半部分有序
            {
                // 是否在有序部分中
                if (nums[mid] < target && nums[right] >= target)
                    left = mid + 1;
                else
                    right = mid - 1;
            }
            else  // mid == left or mid == right or left == right == mid
            {
                if (left == mid)
                    ++left;
                else if (right == mid)
                    --right;
            }
        }
        return -1;
    }
};