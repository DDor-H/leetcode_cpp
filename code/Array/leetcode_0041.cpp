// 方法一：
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        // 先检查是否包含 1 ，如果没有 1，则直接返回
        auto idx = find(nums.begin(), nums.end(), 1);
        if (idx == nums.end())
            return 1;
		
        // 将 <= 0 及 > n 的值全置为 1
        for (auto& num : nums)
            if (num <= 0 || num > n)
                num = 1;
		
        // 将每个数字 num 对应的下标为 num - 1 位置的值，置为相反数
        int i = -1;
        int n = nums.size();
        for (i = 0; i < n; ++i)
            nums[abs(nums[i]) - 1] = -abs(nums[abs(nums[i]) - 1]);

        // 查找第一个没有被 没有被置为负数的 位置，返回 i + 1
        for (i = 0; i < n; ++i)
            if (nums[i] > 0)
                return i + 1;

        return n + 1;
    }
};

// 方法二：
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        int i = -1;
        for (i = 0; i < n; ++i)
        {
            while (nums[i] > 0 && nums[i] <= n && nums[i] != nums[nums[i] - 1])
                swap(nums[i], nums[nums[i] - 1]);
        }

        for (i = 0; i < n; ++i)
            if (nums[i] != i + 1)
                return i + 1;

        return n + 1;
    }
};