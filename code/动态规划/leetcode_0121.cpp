// 自前往后
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if (len == 1)
            return 0;
        int mn = prices[0];
        int ans = 0;
        for (int i = 1; i < len; ++i)
        {
            ans = max(ans, prices[i] - mn);
            mn = min(mn, prices[i]);
        }
        return ans;
    }
};

/*
// 自后往前
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if (len == 1)
            return 0;
        int mx = prices[len - 1];
        int ans = 0;
        for (int i = len - 2; i >= 0; --i)
        {
            ans = max(ans, mx - prices[i]);
            mx = max(mx, prices[i]);
        }
        return ans;
    }
};
*/