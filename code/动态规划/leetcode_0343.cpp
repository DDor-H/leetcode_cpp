
// 方法三：数学方法
class Solution {
public:
    int integerBreak(int n) {
        if (n < 4)
            return n - 1;
        
        int zheng = n / 3;
        int yu = n % 3;

        if (yu == 0)
            return pow(3, zheng);
        else if (yu == 1)
            return pow(3, zheng - 1) * 4;
        else
            return pow(3, zheng) * 2;
    }
};

/*
// 方法二：动态规划改进
class Solution {
public:
    int integerBreak(int n) {
        if (n < 4)
            return n - 1;
        vector<int> dp(n + 1, 0);
        for (int i = 4; i <= n; ++i)
        {
            dp[i] = max(max(2 * (i - 2), 2 * dp[i - 2]), max(3 * (i - 3), 3 * dp[i - 3]));
        }
        return dp[n];
    }
};

/*
// 方法一：动态规划
class Solution {
public:
    int integerBreak(int n) {
        vector<int> dp(n + 1, 0);
        for (int i = 2; i <= n; ++i)
        {
            int curMax = 0;
            for (int j = 1; j < i; ++j)
                curMax = max(curMax, max(j * (i - j), j * dp[i - j]));
            dp[i] = curMax;
        }
        return dp[n];
    }
};
*/