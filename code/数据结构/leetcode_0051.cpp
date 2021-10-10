// 方法二：位运算改进
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<int> queens = vector<int>(n, -1);
        backTrace(res, 0, 0, 0, queens, n, 0);
        return res;
    }
    void backTrace(vector<vector<string>>& res, int col, int diags1, int diags2, vector<int>& queens, int n, int idx)
    {
        if (idx == n)
        {
            res.push_back(generateBoard(queens, n));
            return;
        }
        else
        {
            int availablePosition = ~(col | diags1 | diags2) & ((1 << n) - 1);
            for (; availablePosition > 0; availablePosition &= (availablePosition - 1))
            {
                int pos = availablePosition & (-availablePosition);
                int index = __builtin_ctz(pos);
                queens[idx] = index;
                backTrace(res, col | pos, (diags1 | pos) >> 1, (diags2 | pos) << 1, queens, n, idx + 1);
                queens[idx] = -1;
            }
        }
    }
    vector<string> generateBoard(vector<int>& queens, int n)
    {
        vector<string> res = vector<string>(n, string(n, '.'));
        for (int i = 0; i < n; ++i)
            res[i][queens[i]] = 'Q';
        return res;
    }
};

/*
// 方法一：递归 + 回溯
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<int> queens = vector<int>(n, -1);
        unordered_set<int> col = unordered_set<int>();
        unordered_set<int> diags1 = unordered_set<int>();
        unordered_set<int> diags2 = unordered_set<int>();
        backTrace(res, col, diags1, diags2, queens, n, 0);
        return res;
    }
    void backTrace(vector<vector<string>>& res, unordered_set<int>& col, unordered_set<int>& diags1, unordered_set<int>& diags2, vector<int>& queens, int n, int idx)
    {
        if (idx == n)
        {
            res.push_back(generateBoard(queens, n));
            return;
        }
        else
        {
            for (int i = 0; i < n; ++i)
            {
                if (col.find(i) != col.end())
                    continue;
                int diag1 = idx - i;
                if (diags1.find(diag1) != diags1.end())
                    continue;
                int diag2 = idx + i;
                if (diags2.find(diag2) != diags2.end())
                    continue;
                col.insert(i);
                diags1.insert(diag1);
                diags2.insert(diag2);
                queens[idx] = i;
                backTrace(res, col, diags1, diags2, queens, n, idx + 1);
                queens[idx] = -1;
                col.erase(i);
                diags1.erase(diag1);
                diags2.erase(diag2);
            }
        }
    }
    vector<string> generateBoard(vector<int>& queens, int n)
    {
        vector<string> res = vector<string>(n, string(n, '.'));
        for (int i = 0; i < n; ++i)
            res[i][queens[i]] = 'Q';
        return res;
    }
};
*/