class Solution {
public:
    bool canJump(vector<int>& nums) {
        int len = nums.size();
        if (len == 0)
            return false;
        if (len == 1)
            return true;
        
        int maxJumpIndex = 0;
        for (int i = 0; i < len; ++i)
        {
            maxJumpIndex = max(i + nums[i], maxJumpIndex);
            if (maxJumpIndex >= len - 1)
                return true;
            if (maxJumpIndex == i)
                return false;
        }
        return false;
    }
};