// 快速选择排序
class Solution {
public:
    int randomPartition(vector<pair<int, int>>& tmp, int left, int right)
    {
        int p = rand() & (right - left + 1) + left;
        swap(tmp[p], tmp[right]);

        int x = tmp[right].second, i = left - 1;
        for (int j = left; j < right; ++j)
        {
            if (tmp[j].second <= x)
                swap(tmp[++i], tmp[j]);
        }
        swap(tmp[i + 1], tmp[right]);
        return i + 1;
    }

    void mysort(vector<pair<int, int>>& tmp, int left, int right, int k)
    {
        int q = randomPartition(tmp, left, right);
        if (q > k)
            mysort(tmp, left, q - 1, k);
        else if (q < k)
            mysort(tmp, q + 1, right, k);
    }
    
    vector<int> topKFrequent(vector<int>& nums, int k) {
        srand(time(0));
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); ++i)
            ++map[nums[i]];
        vector<int> v;
        vector<pair<int, int>> tmp;
        for (auto& e : map)
            tmp.push_back(e);
        mysort(tmp, 0, tmp.size() - 1, tmp.size() - k);
        for (int i = 0; i < k; ++i)
            v.push_back(tmp[tmp.size() - i - 1].first);
        return v;
    }
};
    

/*
// 基于优先级队列（堆）
class Solution {
public:
    static bool function(pair<int, int> x, pair<int, int> y)
    {
        return (x.second > y.second);
    }
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); ++i)
            ++map[nums[i]];
        // 有序优先级队列定义方式
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(&function)> q(function);
        for (auto& [num, count] : map)
        {
            if (q.size() == k)
            {
                if (q.top().second < count)
                {
                    q.pop();
                    q.push({num, count});
                }
            }
            else
                q.push({num, count});
        }
        vector<int> v;
        while (!q.empty())
        {
            v.push_back(q.top().first);
            q.pop();
        }
            
        return v;
    }
};


/*
// map映射
class Solution {
public:
    static bool function(pair<int, int> x, pair<int, int> y)
    {
        return (x.second > y.second);
    }
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); ++i)
            ++map[nums[i]];
        vector<int> v;
        vector<pair<int, int>> tmp;
        for (auto& e : map)
            tmp.push_back(e);
        sort(tmp.begin(), tmp.end(), function);
        for (auto e = tmp.begin(); e != tmp.end(); ++e)
        {
            if (k-- == 0)
                break;
            v.push_back(e->first);
        }
            
        return v;
    }
};
*/