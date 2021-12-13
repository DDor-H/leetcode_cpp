
// 位运算
class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int> tmp;
        vector<vector<int>> ans;
        for (int mask = 0; mask < (1 << 9); ++mask)
            _combinationSum3(ans, tmp, mask, n, k);
        return ans;
    }
    
    void _combinationSum3(vector<vector<int>>& ans, vector<int>& tmp, int mask, int n, int k)
    {
        tmp.clear();
        for (int i = 0; i < 9; ++i)
        {
            if (1 & (mask >> i))
                tmp.push_back(i + 1);
        }
        int sumv = 0;
        for (auto& e : tmp)
            sumv += e;
        if (tmp.size() == k && sumv == n)
            ans.push_back(tmp);
    }
};

/*
// 递归组合
class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int> tmp;
        vector<vector<int>> ans;
        _combinationSum3(ans, tmp, 1, n, k);
        return ans;
    }
    
    void _combinationSum3(vector<vector<int>>& ans, vector<int>& tmp, int idx, int n, int k)
    {
        if (n <= 0)
        {
            if (n == 0 && tmp.size() == k)
                ans.push_back(tmp);
            return;
        }

        if (idx > 9)
		    return;

        tmp.push_back(idx);
        _combinationSum3(ans, tmp, idx + 1, n - idx, k);
        tmp.pop_back();
        _combinationSum3(ans, tmp, idx + 1, n, k);
    }
};
*/
