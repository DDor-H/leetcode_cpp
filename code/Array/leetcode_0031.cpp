class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        //  [8,9,7,10,6,2]
        int len = nums.size();
        if (len == 1)
            return;
        int lpos = 0;
        int bpos = len - 1;
        for (int i = len - 2, j = len - 1; j > 0; --i, --j)
        {
            // 从后向前找第一个 nums[i] < nums[j]
            // i 就是 lpos
            if (nums[i] < nums[j])
            {
                lpos = i;
                break;
            }
        }
        for (int j = bpos; j > lpos; --j)
        {
            // 从后向前找第一个 nums[lpos] < nums[j]
            if (nums[lpos] < nums[j])
            {
                bpos = j;
                break;
            }
        }
        int tmp = nums[lpos];
        nums[lpos] = nums[bpos];
        nums[bpos] = tmp;

        sort(nums.begin() + lpos + 1, nums.end());
    }
};