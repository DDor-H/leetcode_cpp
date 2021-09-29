class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int len1 = s1.length();
        int len2 = s2.length();
        int len3 = s3.length();
        if (len1 + len2 != len3)
            return false;

        vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, false));
        dp[0][0] = true;
        for (int i = 0; i <= len1; ++i)
        {
            for (int j = 0; j <= len2; ++j)
            {
                int p = i + j - 1;
                if (i > 0)
                    dp[i][j] |= (dp[i - 1][j] && (s1[i - 1] == s3[p]));
                if (j > 0)
                    dp[i][j] |= (dp[i][j - 1] && (s2[j - 1] == s3[p]));
            }
        }
        return dp[len1][len2];
    }
};

// 滚动数组
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int len1 = s1.length();
        int len2 = s2.length();
        int len3 = s3.length();
        if (len1 + len2 != len3)
            return false;

        vector<int> dp(len2 + 1, false);
        dp[0] = true;
        for (int i = 0; i <= len1; ++i)
        {
            for (int j = 0; j <= len2; ++j)
            {
                int p = i + j - 1;
                if (i > 0)
                    dp[j] &= (s1[i - 1] == s3[p]);
                if (j > 0)
                    dp[j] |= (dp[j - 1] && (s2[j - 1] == s3[p]));
            }
        }
        return dp[len2];
    }
};