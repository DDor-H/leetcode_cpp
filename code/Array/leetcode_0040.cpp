class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> res;
        vector<int> combine;
        backtracking(candidates, res, combine, target, 0);
        return res;
    }
    void backtracking(vector<int>& candidates, vector<vector<int>>& res, vector<int>& combine, int target, int idx)
    {
        if (target <= 0)
        {
            if (target == 0)
                res.push_back(combine);
            return;
        }

        for (int i = idx; i < candidates.size(); ++i)
        {
            if (i > idx && candidates[i] == candidates[i - 1])  // 去重
                continue;
            if (candidates[i] > target)  // 剪枝
                return;
            combine.push_back(candidates[i]);
            backtracking(candidates, res, combine, target - candidates[i], i + 1);
            combine.pop_back();
        }
    }
};