class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.length(), n = text2.length();
        vector<int> dp(n + 1, 0);
        for (int i = 1; i <= m; ++i)
        {
            vector<int> tmpDp(n + 1, 0);
            for (int j = 1; j <= n; ++j)
            {
                if (text1[i - 1] == text2[j - 1])
                    tmpDp[j] = dp[j - 1] + 1;
                else
                    tmpDp[j] = max(dp[j], tmpDp[j - 1]);
            }
            dp = tmpDp;
        }
        return dp[n];
    }
};