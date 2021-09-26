class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        if (n == 1)
            return triangle[0][0];
        
        vector<int> dp;
        dp.resize(1);
        dp[0] = triangle[0][0];

        for (int i = 1; i < n; ++i)
        {
            dp.resize(i + 1);
            for (int j = i; j >= 0; --j)
            {
                if (j == i)
                    dp[j] = triangle[i][j] + dp[j - 1];
                else if (j == 0)
                    dp[j] = triangle[i][j] + dp[0];
                else
                    dp[j] = triangle[i][j] + min(dp[j], dp[j - 1]);
            }
        }
        
        return *min_element(dp.begin(), dp.end());;
    }
};