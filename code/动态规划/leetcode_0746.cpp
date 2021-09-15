class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int len = cost.size();
        vector<int> dp(len + 1, 0);

        for (int i = 2; i <= len; ++i)
            dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
        return dp[len];
    }
};

// 改进
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int len = cost.size();
        int prepreval = 0, preval = 0, curval = 0;

        for (int i = 2; i <= len; ++i)
        {
            curval = min(preval + cost[i - 1], prepreval + cost[i - 2]);
            prepreval = preval;
            preval = curval;
        }
            
        return curval;
    }
};