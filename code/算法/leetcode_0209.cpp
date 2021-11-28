class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int lens = nums.size();
        vector<int> prefix(lens + 1, 0);
        for (int i = 0; i < lens; ++i)
            prefix[i + 1] = prefix[i] + nums[i];
        int min_idx = -1, max_len = INT_MAX;
        for (int i = 1; i < prefix.size(); ++i)
        {
            for (int j = i; j < prefix.size(); ++j)
            {
                if (prefix[j] - prefix[j - i] >= target)
                    return i;
            }
        }
        return 0;
    }
};