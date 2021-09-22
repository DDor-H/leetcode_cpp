class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int len = s.length();
        set<string> wordDictSet(wordDict.begin(), wordDict.end());

        vector<bool> dp(len + 1, false);
        dp[0] = true;
        /*
        for (int i = 1; i <= len; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (dp[j] && wordDictSet.find(s.substr(j, i - j)) != wordDictSet.end())
                {
                    dp[i] = true;
                    break;
                }
            }
        }
        */
        for (int i = 0; i < len; ++i)
        {
            for (int j = i + 1; j <= len; ++j)
            {
                if (dp[i] && wordDictSet.find(s.substr(i, j - i)) != wordDictSet.end())
                    dp[j] = true;
            }
        }
        return dp[len];
    }
};