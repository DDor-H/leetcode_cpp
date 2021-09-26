class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        if (n == 1)
            return matrix[0][0];
        vector<int> dp(n, 0);
        int minLen = INT_MAX;
        for (int i = 0; i <n ; ++i)
            dp[i] = matrix[0][i];
        
        for (int i = 1; i < n; ++i)
        {
            vector<int> tmpdp(n, 0);
            for (int j = 0; j < n; ++j)
            {
                if (j == 0)
                    tmpdp[j] = matrix[i][j] + min(dp[j], dp[j + 1]);
                else if (j == n - 1)
                    tmpdp[j] = matrix[i][j] + min(dp[j], dp[j - 1]);
                else
                    tmpdp[j] = matrix[i][j] + min(dp[j], min(dp[j + 1], dp[j - 1]));
            }
            dp = tmpdp;
        }

        for (int i = 0; i < n; ++i)
            minLen = min(minLen, dp[i]);
        return minLen;
    }
};