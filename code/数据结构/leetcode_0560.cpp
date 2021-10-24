/*
// hash表 + 前缀和
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> map;
        map[0] = 1;
        int count = 0, preSum = 0;
        for (auto& e : nums)
        {
            // 边计算前缀和，边查找是否包含preSum - k的数量
            preSum += e;
            if (map.find(preSum - k) != map.end())
                count += map[preSum - k];
            ++map[preSum];  // 有负数，可能前缀和会变小
        }
        return count;
    }
};
*/

// 前缀和 （超时）
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 1)
            return (k == nums[0] ? 1 : 0);
        vector<int> preSum(nums);
        int count = 0;
        // 计算前缀和
        for (int i = 1; i < n; ++i)
            preSum[i] += preSum[i - 1];

        for (int i = 0; i < n; ++i)
        {
            if (preSum[i] == k)
                ++count;
            for (int j = 0; j < i; ++j)
            {
                if (preSum[i] - preSum[j] == k)
                    ++count;
            }
        }
        return count;
    }
};

/*
// 暴力解法（超时）
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        int count = 0;
        for (int i = 0; i < n; ++i)
        {
            int sum = 0;
            for (int j = i; j < n; ++j)
            {
                sum += nums[j];
                if (sum == k)
                    ++count;
            }
        }
        return count;
    }
};
*/