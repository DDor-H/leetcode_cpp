// 二分法
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        if (n == 1)
            return 0;
        int left = 0, right = n - 1;
        int mid = -1;
        while (left <= right)
        {
            int mid = left + ((right - left) >> 1);
            if (left == mid || mid == right)
                return nums[left] > nums[right] ? left : right;
            if (nums[mid - 1] < nums[mid] && nums[mid] > nums[mid + 1])
                return mid;
            else if (nums[mid - 1] < nums[mid])
                left = mid;
            else
                right = mid;
        }
        return mid;
    }
};

/*
// 循环
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        return max_element(nums.begin(), nums.end()) - nums.begin();
    }
};
*/