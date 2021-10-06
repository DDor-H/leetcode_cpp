
// 方法三：hash表
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        int n = nums.size();
        if (n < 2)
            return false;
        unordered_set<int> us;

        for (auto& x : nums)
        {
            if (us.find(x) != us.end())
                return true;
            us.insert(x);
        }
        return false;
    }
};


/*
// 方法二：排序
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        int n = nums.size();
        if (n < 2)
            return false;
        sort(nums.begin(), nums.end());
        for (int i = 1; i < n; ++i)
        {
            if (nums[i - 1] == nums[i])
                return true;
        }
        return false;
    }
};

/*
// 方法一：暴力解法（超时）
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        int n = nums.size();
        if (n < 2)
            return false;
        
        for (int i = 1; i < n; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (nums[i] == nums[j])
                    return true;
            }
        }
        return false;
    }
};
*/