// 方法一：
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int len = nums.size();
        if (len == 0)
            return len;
        auto end = nums.end();
        --end;
        while (end >= nums.begin())
        {
            --end;
            if (*(end + 1) == val)
                nums.erase(end + 1, end + 2);
        }
        return nums.size();
    }
};

// 方法二：
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if (nums.size() == 0)
            return 0;
        int i = 0;
        int j = 0;
        while (j < nums.size())
        {
            if (nums[j] != val)
            {
                if (i != j)
                {
                    nums[i] = nums[j];
                    nums[j] = val;
                }
                ++i;
            }
            ++j;
        }
        return i;
    }
};