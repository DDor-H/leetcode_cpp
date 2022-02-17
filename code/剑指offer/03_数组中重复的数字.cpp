// 交换
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        int len = nums.size();
        int i = 0;
        for (; i < len; ++i)
        {
            while (nums[i] != i)  // 如果不在他该在的位置，就交换
            {
                if (nums[i] == nums[nums[i]])  // 交换前若相等，直接停止
                    break;
                swap(nums[i], nums[nums[i]]);
            }
            if (nums[i] != i)
                break;
        }   
        return nums[i];
    }
};

/*
// hash表
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        int len = nums.size();
        set<int> tmp;
        int i = 0;
        for (; i < len; ++i)
        {
            if (tmp.find(nums[i]) != tmp.end())
                break;
            else
                tmp.insert(nums[i]);
        }
        return nums[i];        
    }
};

/*
// 排序
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        int len = nums.size();
        quick_sort(nums, 0, len - 1);
        int i = 0;
        for (; i < len - 1; ++i)
            if (nums[i] == nums[i + 1])
                break;
        return nums[i];        
    }

    void quick_sort(vector<int>& nums, int left, int right)
    {
        if (left >= right)
            return;
        int p = rand() % (right - left + 1) + left;
        swap(nums[right], nums[p]);
        int x = nums[right];
        int i = left - 1;
        for (int j = left; j < right; ++j)
        {
            if (nums[j] <= x)
                swap(nums[++i], nums[j]);
        }
        swap(nums[++i], nums[right]);
        quick_sort(nums, left, i - 1);
        quick_sort(nums, i + 1, right);
    }
};
*/class Solution {
public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if (m == 0)
            return false;
        int n = matrix[0].size();
        if (n == 0)
            return false;
        int i = 0, j = n - 1;
        while (i < m && j >= 0)
        {
            if (matrix[i][j] > target)
                --j;
            else if (matrix[i][j] < target)
                ++i;
            else
                return true;
        }
        return false;
    }
};