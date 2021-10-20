// 分治法
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        return majority_element_rec(nums, 0, nums.size() - 1);
    }

    int majority_element_rec(vector<int>& nums, int lo, int hi) 
    {
        if (lo == hi)
            return nums[lo];
        int mid = ((lo + hi) >> 1);
        int left_majority = majority_element_rec(nums, lo, mid);
        int right_majority = majority_element_rec(nums, mid + 1, hi);
        if (count_in_range(nums, left_majority, lo, hi) > (hi - lo + 1) / 2)
            return left_majority;
        if (count_in_range(nums, right_majority, lo, hi) > (hi - lo + 1) / 2)
            return right_majority;
        return -1;
    }

    int count_in_range(vector<int>& nums, int target, int lo, int hi) 
    {
        int count = 0;
        for (int i = lo; i <= hi; ++i)
        {
            if (nums[i] == target)
                ++count;
        }
        return count;
    }
};

/*
// 排序
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return nums[nums.size() / 2];
    }
};

/*
// Boyer-Moore 投票算法
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int max_value = nums[0];
        int max_count = 1;
        for (int i = 1; i < nums.size(); ++i)
        {
            if (nums[i] == max_value)
                ++max_count;
            else
                --max_count;
            
            if (max_count < 0)
            {
                max_count = 1;
                max_value = nums[i];
            }
        }
        return max_value;
    }
};
*/

/*
// hash表
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> m;
        for (auto & e : nums)
        {
            if (m.count(e) == 0)
                m.insert(make_pair(e, 1));
            else
                ++m[e];
        }
        int max_value = INT_MIN;
        int max_count = INT_MIN;
        for (auto it = m.begin(); it != m.end(); ++it)
        {
            if (it->second > max_count)
            {
                max_count = it->second;
                max_value = it->first;
            }
        }
        return max_value;
    }
};
*/