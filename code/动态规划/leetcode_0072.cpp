
// 方法二：动态规划
class Solution {
public:
    int minDistance(string word1, string word2) {
        int len1 = word1.length();
        int len2 = word2.length();

        if (len1 * len2 == 0)
            return len1 + len2;
        
        vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
        for (int i = 0; i < len1 + 1; ++i)
            dp[i][0] = i;
        for (int i = 0; i < len2 + 1; ++i)
            dp[0][i] = i;

        for (int i = 1; i < len1 + 1; ++i)
        {
            for (int j = 1; j < len2 + 1; ++j)
            {
                if (word1[i - 1] == word2[j - 1])  // 字符串下标要比dp数组下少 1
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    dp[i][j] = 1 + min(dp[i - 1][j - 1], min(dp[i][j - 1], dp[i - 1][j]));
            }
        }

        return dp[len1][len2];
    }
};

/*
// 方法一：递归(超时)
class Solution {
public:
    int minDistance(string word1, string word2) {
        if (word1.length() == 0 || word2.length() == 0)
            return max(word1.length(), word2.length());
        
        if (word1.back() == word2.back())
        {
            return minDistance(word1.substr(0, word1.length() - 1), word2.substr(0, word2.length() - 1));
        }

        return 1 + min(
            minDistance(word1, word2.substr(0, word2.length() - 1)),
            min(minDistance(word1.substr(0, word1.length() - 1), word2),
            minDistance(word1.substr(0, word1.length() - 1), word2.substr(0, word2.length() - 1)))
        );
    }
};
*/