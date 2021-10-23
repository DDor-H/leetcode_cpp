
// 方法二：贪心
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty())
            return 0;
        sort(intervals.begin(), intervals.end(), [](const auto& u, const auto& v){
            return u[1] < v[1];
        });

        int n = intervals.size();
        int end = INT_MIN;
        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            if (intervals[i][0] >= end)
            {
                end = intervals[i][1];
                ++ans;
            }
        }
        return n - ans;
    }
};

/*
// 方法一：动态规划（超时）
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty())
            return 0;
        sort(intervals.begin(), intervals.end(), [](const auto& u, const auto& v){
            return u[0] < v[0];
        });

        int n = intervals.size();
        vector<int> bp(n, 1);
        for (int i = 1; i < n; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (intervals[j][1] <= intervals[i][0])
                {
                    bp[i] = max(bp[i], bp[j] + 1);
                }
            }
        }
        return n - *max_element(bp.begin(), bp.end());
    }
};
*/