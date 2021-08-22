class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());  // 剪枝的前提就是有序
        vector<vector<int>> res;
        vector<int> combine;
        backtracking(candidates, target, res, combine, 0);
        return res;
    }

    void backtracking(vector<int>& candidates, int target, vector<vector<int>>& res, vector<int>& combine, int idx)
    {
        if (target <= 0)
        {
            if (target == 0)
                res.push_back(combine);
            return;
        }
            
        for (int i = idx; i < candidates.size(); ++i)
        {
            // 剪枝
            if (candidates[i] > target)
                return;
            combine.push_back(candidates[i]);
            backtracking(candidates, target - candidates[i], res, combine, i);
            combine.pop_back();  // 回溯
        }
    }
};