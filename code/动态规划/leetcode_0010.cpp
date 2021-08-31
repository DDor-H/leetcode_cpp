class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.length();
        int n = p.length();
        vector<vector<bool>> statusTransTable(m + 1, vector<bool>(n + 1));
        statusTransTable[0][0] = true;

        for (int i = 1; i <= m; ++i)
            statusTransTable[i][0] = false;

        for (int j = 1; j <= n; ++j)
            statusTransTable[0][j] = (p[j - 1] == '*' && statusTransTable[0][j - 2]);
        
        for (int i = 1; i <= m; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (p[j - 1] == s[i - 1] || p[j - 1] == '.')
                    statusTransTable[i][j] = statusTransTable[i - 1][j - 1];
                else if (p[j - 1] == '*')
                {
                    if (statusTransTable[i][j - 2] == true)
                        statusTransTable[i][j] = true;
                    else if (p[j - 2] == s[i - 1] || p[j - 2] == '.')
                        statusTransTable[i][j] = statusTransTable[i - 1][j];
                }
                else
                    statusTransTable[i][j] = false;
            }
        }
        return statusTransTable[m][n];
    }
};