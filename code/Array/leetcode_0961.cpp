/*
// 方法一：计数法
class Solution {
public:
    int repeatedNTimes(vector<int>& nums) {
        map<int, int> m;
        for (auto& e : nums)
            ++m[e];
        auto it = m.begin();
        for (; it != m.end(); ++it)
        {
            if (it->second > 1)
                break;
        }
        return it->first;
    }
};
*/

// 方法二：比较
class Solution {
public:
    int repeatedNTimes(vector<int>& nums) {
        int sz = nums.size();
        for (int i = 1; i <= 3; ++i)
        {
            for (int j = 0; j < sz - i; ++j)
            {
                if (nums[j] == nums[i + j])
                    return nums[j];
            }
        }
        return -1;
    }
};