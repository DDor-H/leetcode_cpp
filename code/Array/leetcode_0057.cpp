class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int len = intervals.size();
        if (len == 0)
            return vector<vector<int>>{newInterval};

        vector<vector<int>> res;
        int i = 0;
        for (; i < len; ++i)
        {
            if (newInterval[0] >= intervals[i][0])
                res.push_back(intervals[i]);
            else 
                break;
        }

        if (res.empty() || res.back()[1] < newInterval[0])   // res.empty()这一句很重要
            res.push_back(newInterval);
        else if (res.back()[1] < newInterval[1])
            res.back()[1] = newInterval[1];
        
        for (; i < len; ++i)
        {
            if (intervals[i][0] <= res.back()[1])
            {
                if (intervals[i][1] > res.back()[1])
                    res.back()[1] = intervals[i][1];
            }
            else
                res.push_back(intervals[i]);
        }
        
        return res;
    }
};