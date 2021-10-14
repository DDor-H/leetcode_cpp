class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        if (n < k || k == 0)
            return vector<vector<int>>();
        vector<vector<int>> res;
        vector<int> cur;
        _combine(res, cur, 1, n, k);
        return res;
    }

    void _combine(vector<vector<int>>& res, vector<int>& cur, int idx, int n, int k)
    {
        // 剪枝 ： 当前长度 + [idx, n] 的长度不够 k
        if (cur.size() + (n - idx + 1) < k)
            return;

        if (cur.size() == k)
        {
            res.push_back(cur);
            return;
        }

        // 选用idx
        cur.push_back(idx);
        _combine(res, cur, idx + 1, n, k);
        cur.pop_back();
        // 不用idx
        _combine(res, cur, idx + 1, n, k);
    }
};