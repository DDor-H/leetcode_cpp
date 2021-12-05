class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> nums_set;
        for (auto& e : nums)
            nums_set.insert(e);
        
        int ans = 0;
        for (auto& e : nums_set)
        {
            if (nums_set.count(e - 1) != 0)
                continue;
            int curnum = e;
            int curlen = 1;
            while (nums_set.count(curnum + 1) != 0)
            {
                ++curlen;
                ++curnum;
            }

            ans = max(curlen, ans);
        }
        return ans;
    }
};