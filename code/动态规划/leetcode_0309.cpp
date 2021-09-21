class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if (len <= 1)
            return 0;
        
        int sell = 0, buy = -prices[0], cool = 0;
        for (int i = 0; i < len; ++i)
        {
            int newsell = buy + prices[i];
            int newbuy = max(cool - prices[i], buy);
            int newcool = max(sell, cool);
            tie(sell, buy, cool) = {newsell, newbuy, newcool};
        }
        return max(sell, cool);
    }
};