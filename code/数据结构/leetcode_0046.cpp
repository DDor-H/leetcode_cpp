class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> res;
        
        backtrace(res, nums, 0, n);
        return res;
    }

    void backtrace(vector<vector<int>>& res, vector<int>& output, int first, int end)
    {
        if (first == end)
        {
            res.push_back(output);
            return;
        }

        for (int i = first; i < end; ++i)
        {
            swap(output[i], output[first]);
            backtrace(res, output, first + 1, end);
            swap(output[i], output[first]);
        }
    }
};