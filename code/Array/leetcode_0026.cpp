// 方法一：
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() <= 1)
            return nums.size();
        auto end = nums.end();
        --end;
        while (end > nums.begin())
        {
            --end;
            if (*end == *(end + 1))
                nums.erase(end + 1, end + 2);
        }
        return nums.size();
    }
};

// 方法二：
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int len = nums.size();
        if (len <= 1)
            return len;
        int i = 0;
        int j = 0;
        while (j < len)
        {
            if (nums[i] != nums[j])
            {
                ++i;
                if (i != j)
                    nums[i] = nums[j];
            }
            ++j;
        }
        return i + 1;
    }
};