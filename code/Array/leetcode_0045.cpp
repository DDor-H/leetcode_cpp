// 方法一：
class Solution {
public:
    int jump(vector<int>& nums) {
        int position = nums.size() - 1;
        int steps = 0;
        while (position > 0)
        {
            for (int i = 0; i < position; ++i)
            {
                if (i + nums[i] >= position)
                {
                    position = i;
                    ++steps;
                    break;
                }
            }
        }
        return steps;
    }
};

// 方法二：
class Solution {
public:
    int jump(vector<int>& nums) {
        int len = nums.size();
        int steps = 0;
        int maxPos = 0;
        int end = 0;
        for (int i = 0; i < len - 1; ++i)
        {
            maxPos = max(maxPos, nums[i] + i);
            if (i == end)
            {
                end = maxPos;
                ++steps;
            }
        }
        return steps;
    }
};