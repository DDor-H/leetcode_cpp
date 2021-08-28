// 方法一：递归  超时
class Solution {
public:
    int uniquePaths(int m, int n) {
        return 1 + _uniquePaths(1, 1, m, n);
    }
    int _uniquePaths(int curm, int curn, int m, int n)
    {
        if (curm < m && curn < n)
            return 1 + _uniquePaths(curm + 1, curn, m, n) + _uniquePaths(curm, curn + 1, m, n);
        else
            return 0;
    }
};

// 方法二：动态规划
// dp[i][j] = dp[i-1][j] + dp[i][j-1]
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> status(m, vector<int>(n, 1));
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (i == 0 || j == 0)
                    continue;
                status[i][j] = status[i - 1][j] + status[i][j - 1];
            }
        }
        return status[m - 1][n - 1];
    }
};

// 方法三：组合数学
class Solution {
public:
    int uniquePaths(int m, int n) {
        long long res = 1;
        for (int i = m - 2; i >= 0; --i)
            res = res * (m + n - 2 - i) / (m - 1 - i);
        return res;
    }
};