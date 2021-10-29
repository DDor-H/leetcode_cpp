// 迭代法 + 位运算
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> t;
        int n = nums.size();
        if (n < 1)
            return ans;
        sort(nums.begin(), nums.end());
        for (int mask = 0; mask < (1 << n); ++mask)
        {
            // mask表示 1 - n 位的数字分别使用和不使用
            t.clear();
            bool flag = true;
            for (int i = 0; i < n; ++i)
            {
                // 选中 i 位置
                if (mask & (1 << i))
                {
                    // 选中 i ，但没选中 i - 1 且 nums[i] == nums[i - 1]
                    if (i > 0 && ((mask >> (i - 1) & 1) == 0) && nums[i] == nums[i - 1])
                    {
                        flag = false;
                        break;
                    }
                    t.push_back(nums[i]);
                }
            }
            if (flag)
                ans.push_back(t);
        }
        return ans;
    }
};

/*
// 递归法
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> t;
        int n = nums.size();
        if (n < 1)
            return ans;
        sort(nums.begin(), nums.end());
        _subsetsWithDup(ans, t, false, 0, nums);
        return ans;
    }

    void _subsetsWithDup(vector<vector<int>>& ans, vector<int>& t, bool preChoose, int idx, vector<int>& nums)
    {
        if (idx == nums.size())
        {
            ans.push_back(t);
            return;
        }
        _subsetsWithDup(ans, t, false, idx + 1, nums);
        if (!preChoose && idx > 0 && nums[idx] == nums[idx - 1])
            return;
        t.push_back(nums[idx]);
        _subsetsWithDup(ans, t, true, idx + 1, nums);
        t.pop_back();
    }
};
*/