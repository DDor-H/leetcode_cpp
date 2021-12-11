// 优先队列
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> um;
        for (auto& word : words)
            ++um[word];
        auto cmp = [](pair<string, int>& p1, pair<string, int>& p2)->bool {
            return p1.second == p2.second ? p1.first < p2.first : p1.second > p2.second;
        };
        priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)> pq(cmp);
        for (auto& p : um)
        {
            pq.push(p);
            if (pq.size() > k)
                pq.pop();
        }
        vector<string> ans(k);
        for (int i = k - 1; i >= 0; --i)
        {
            ans[i] = pq.top().first;
            pq.pop();
        }
        return ans;
    }
};

/*
// hash表排序
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> um;
        for (auto& word : words)
            ++um[word];
        vector<pair<string, int>> tmp;
        for (auto& e : um)
            tmp.push_back(e);
        sort(tmp.begin(), tmp.end(), [](pair<string, int>& p1, pair<string, int>& p2)->bool {
            if (p1.second == p2.second)
            {
                return p1.first < p2.first;
            }
            return p1.second > p2.second;
        });
        vector<string> ans;
        for (int i = 0; i < k; ++i)
            ans.push_back(tmp[i].first);
        return ans;
    }
};
*/