
// 快速选择排序
class Solution {
public:
    void quickSelectSort(vector<vector<int>>& points, int left, int right, int k)
    {
        if (left >= right)
            return;
        int p = rand() % (right - left + 1) + left;
        swap(points[p], points[right]);

        vector<int> x = points[right];
        int x_dis = x[0] * x[0] + x[1] * x[1];
        int i = left - 1;
        for (int j = left; j < right; ++j)
        {
            int dis = points[j][0] * points[j][0] + points[j][1] * points[j][1];
            if (dis <= x_dis)
                swap(points[++i], points[j]);
        }
        ++i;
        swap(points[i], points[right]);

        if (i > k)
            quickSelectSort(points, left, i - 1, k);
        else if (i < k)
            quickSelectSort(points, i + 1, right, k);
    }
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        quickSelectSort(points, 0, points.size() - 1, k);
        return {points.begin(), points.begin() + k};
    }
};

/*
// API priority_queue堆
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        priority_queue<pair<int, int>> q;
        for (int i = 0; i < k; ++i)
            q.push({points[i][0] * points[i][0] + points[i][1] * points[i][1], i});
        for (int i = k; i < points.size(); ++i)
        {
            int dis = points[i][0] * points[i][0] + points[i][1] * points[i][1];
            if (dis < q.top().first)
            {
                q.pop();
                q.push({dis, i});
            }
        }
        vector<vector<int>> ans;
        while (!q.empty())
        {
            ans.push_back(points[q.top().second]);
            q.pop();
        }
            
        return ans;
    }
};

/*
// API sort排序
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        sort(points.begin(), points.end(), [](const vector<int>& d1, const vector<int>& d2){
            return d1[0] * d1[0] + d1[1] * d1[1] < d2[0] * d2[0] + d2[1] * d2[1];
        });
        return {points.begin(), points.begin() + k};
    }
};
*/