
// 贪心 + dfs(超时)
class Solution {
public:
    void _coinChange(vector<int>& coins, int amount, int c_index, int curCount, int& ans)
    {
        if (amount == 0)
        {
            ans = min(curCount, ans);
            return;
        }
        if (c_index == coins.size()) return;

        // k + curCount < ans 为剪枝操作
        for (int k = amount / coins[c_index]; k >= 0 && k + curCount < ans; --k)
            _coinChange(coins, amount - k * coins[c_index], c_index + 1, curCount + k, ans);
    }
    int coinChange(vector<int>& coins, int amount) {
        if (amount == 0)
            return 0;
        sort(coins.rbegin(), coins.rend());
        int ans = INT_MAX;
        _coinChange(coins, amount, 0, 0, ans);
        return ans == INT_MAX ? -1 : ans;
    }
};


/*
// 动态规划
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int len = coins.size();
        int Max = amount + 1;
        vector<int> dp(amount + 1, Max);
        dp[0] = 0;
        for (int i = 1; i <= amount; ++i)
        {
            for (int j = 0; j < len; ++j)
            {
                if (coins[j] <= i)
                    dp[i] = min(dp[i], dp[i - coins[j]] + 1);
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }
};
*/