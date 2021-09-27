// 方法二：动态规划(二维前缀数组和)
class Solution {
public:
    int get(vector<vector<int>>& dp, int m, int n, int r, int c)
    {
        r = max(min(r, m), 0);
        c = max(min(c, n), 0);
        return dp[r][c];
    }
    vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        vector<vector<int>> ans(m, vector<int>(n, 0));
        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= n; ++j)
                dp[i][j] = mat[i - 1][j - 1] + dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1];

        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                ans[i][j] = get(dp, m, n, i + k + 1, j + k + 1) - get(dp, m, n, i - k, j + k + 1) - get(dp, m, n, i + k + 1, j - k) + get(dp, m, n, i - k, j - k);
        return ans;
    }
};

/*
// 方法一：暴力解法(时间效率很低)
class Solution {
public:
    vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> ans(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                for (int r = (i - k < 0 ? 0 : i - k); r <= (i + k >= m ? m - 1 : i + k); ++r)
                {
                    for (int c = (j - k < 0 ? 0 : j - k); c <= (j + k >= n ? n - 1 : j + k); ++c)
                    {
                        ans[i][j] += mat[r][c];
                    }
                }
            }
        }
        return ans;
    }
};
*/