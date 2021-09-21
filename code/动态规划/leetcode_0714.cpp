class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int len = prices.size();
        if (len == 1)
            return 0;
        
        int buy = -prices[0];
        int sell = 0;
        for (int i = 1; i < len; ++i)
        {
            int newbuy = max(sell - prices[i], buy);
            int newsell = max(buy + prices[i] - fee, sell);
            tie(buy, sell) = {newbuy, newsell};
        }
        return sell;
    }
};