class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        int len = nums.size();
        if (len < 4)
            return res;
        sort(nums.begin(), nums.end());

        for (int i = 0; i < len - 3; ++i)
        {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;
            for (int j = i + 1; j < len - 2; ++j)
            {
                if (j > i + 1 && nums[j] == nums[j - 1])
                    continue;
                int m = len - 1;
                int diff = target - (nums[i] + nums[j]);
                for (int k = j + 1; k < len - 1; ++k)
                {
                    if (k > j + 1 && nums[k] == nums[k - 1])
                        continue;
                    while (k < m && nums[k] + nums[m] > diff)
                        --m;

                    if (k == m)
                        break;
                    if (nums[i] + nums[j] + nums[k] + nums[m] == target)
                        res.push_back({nums[i], nums[j], nums[k], nums[m]});
                }
            }
        }
        return res;
    }
};