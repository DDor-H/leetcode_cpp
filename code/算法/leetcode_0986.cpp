class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        int len1 = firstList.size(), len2 = secondList.size();
        vector<vector<int>> ans;
        for (int i = 0, j = 0; i < len1 && j < len2;)
        {
            int lo = max(firstList[i][0], secondList[j][0]);
            int ho = min(firstList[i][1], secondList[j][1]);
            if (lo <= ho)
                ans.push_back({lo, ho});
            if (firstList[i][1] < secondList[j][1])
                ++i;
            else
                ++j;
        }
        return ans;
    }
};