// 方法一：快排
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        if (n == 1)
            return;
        _sortColors(nums, 0, n - 1);
    }
    void _sortColors(vector<int>& nums, int left, int right)
    {
        if (left >= right)
            return;
        int tmpVal = nums[left];
        int low = left, high = right;
        while (low < high)
        {
            while (low < high && tmpVal <= nums[high])
                --high;
            nums[low] = nums[high];

            while (low < high && tmpVal >= nums[low])
                ++low;
            nums[high] = nums[low];
        }
        nums[low] = tmpVal;

        _sortColors(nums, left, low - 1);
        _sortColors(nums, low + 1, right);
    }
};

// 方法二：单指针，两轮循环
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        if (n == 1)
            return;
        int ptr = 0;
        int i = 0;
        for (i = 0; i < n; ++i)
        {
            if (nums[i] == 0)
                swap(nums, i, ptr++);
        }
        ptr = n - 1;
        for (i = n - 1; i >= 0; --i)
        {
            if (nums[i] == 2)
                swap(nums, i, ptr--);
        }
    }
    void swap(vector<int>& nums, int i, int j)
    {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
};

// 方法三：双指针，双向向内
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        if (n == 1)
            return;
        int left = 0, right = n - 1;
        for (int i = 0; i < n; ++i)
        {
            while (nums[i] == 2 && i < right)
                swap(nums, i, right--);
            if (nums[i] == 0)
                swap(nums, i, left++);
        }
    }
    void swap(vector<int>& nums, int i, int j)
    {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
};

// 方法四：双指针，都是从前向后
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        if (n == 1)
            return;
        int p0 = 0, p1 = 0;
        for (int i = 0; i < n; ++i)
        {
            if (nums[i] == 1)
                swap(nums, i, p1++);
            else if (nums[i] == 0)
            {
                swap(nums, i, p0);
                if (p0 < p1)
                    swap(nums, i, p1);
                ++p0;
                ++p1;
            }
        }
    }
    void swap(vector<int>& nums, int i, int j)
    {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
};