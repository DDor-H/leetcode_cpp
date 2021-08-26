class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int len = intervals.size();
        if (len <= 0)
            return intervals;
        sort(intervals.begin(), intervals.end());

        vector<vector<int>> res;
        res.push_back(intervals[0]);
        for (int i = 1; i < len; ++i)
        {
            int L = intervals[i][0];
            int R = intervals[i][1];
            if (L <= res.back()[1])
            {
                if (R > res.back()[1])
                    res.back()[1] = R;
            }
            else
                res.push_back(intervals[i]);
        }
        return res;
    }
};