class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size(), n = dungeon[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));
        // dp[m - 1][n - 1]为终点，但到达终点并扣完血量后必须活着
        // 即至少还需要 1 点血
        // 所以 这两个无效值需初始化为 1
        // 且到达终点前至少需要有dp[m - 1][n - 1] = min(dp[m][n - 1], dp[m - 1][n]) - dungeon[m - 1][n - 1];
        dp[m][n - 1] = 1, dp[m - 1][n] = 1;
        for (int i = m - 1; i >= 0; --i)
        {
            for (int j = n - 1; j >= 0; --j)
            {
                int minn = min(dp[i + 1][j], dp[i][j + 1]);
                dp[i][j] = max(minn - dungeon[i][j], 1);
            }
        }
        return dp[0][0];
    }
};