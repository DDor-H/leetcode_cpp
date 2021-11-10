// 桶排序
class Solution {
public:
    string frequencySort(string s) {
        if (s.length() <= 1)
            return s;
        unordered_map<char, int> map;
        int maxFreq = 0;
        for (char& e : s)
            maxFreq = max(maxFreq, ++map[e]);
        vector<string> buckets(maxFreq + 1);
        for (auto& e : map)
            buckets[e.second].push_back(e.first);
        string ret;
        for (int i = maxFreq; i > 0; --i)
        {
            string& bucket = buckets[i];
            for (char& e : bucket)
            {
                for (int k = 0; k < i; ++k)
                    ret += e;
            }
        }
        return ret;
    }
};

/*
//按照频率排序
class Solution {
public:
    string frequencySort(string s) {
        if (s.length() <= 1)
            return s;
        unordered_map<char, int> map;
        for (char& e : s)
            ++map[e];
        vector<pair<char, int>> tmp;
        for (auto& e : map)
            tmp.push_back(e);
        sort(tmp.begin(), tmp.end(), [](const pair<char, int>& m1, const pair<char, int>& m2){
            return m1.second > m2.second;
        });
        string ret;
        for (auto& [ch, count] : tmp)
        {
            for (int i = 0; i < count; ++i)
                ret += ch;
        }
        return ret;
    }
};
*/