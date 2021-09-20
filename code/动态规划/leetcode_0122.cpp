// 方法二：贪心算法
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if (len == 1)
            return 0;
        int ans = 0;
        for (int i = 1; i < len; ++i)
        {
            if (prices[i] > prices[i - 1])
                ans += (prices[i] - prices[i - 1]);
        }
        
        return ans;
    }
};

/*
// 方法一：动态规划
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if (len == 1)
            return 0;
        int dp0 = 0, dp1 = -prices[0];
        for (int i = 1; i < len; ++i)
        {
            int newdp0 = max(dp0, dp1 + prices[i]);
            int newdp1 = max(dp1, dp0 - prices[i]);
            tie(dp0, dp1) = {newdp0, newdp1};
        }
        return dp0;
    }
};
*/