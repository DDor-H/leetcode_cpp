/*
// 方法一：使用map统计词频
class Solution {
public:
    vector<string> uncommonFromSentences(string s1, string s2) {
        unordered_map<string, int> um;
        findStringMap(s1, um);
        findStringMap(s2, um);

        vector<string> ret;
        for (auto it = um.begin(); it != um.end(); ++it)
        {
            if (it->second == 1)
                ret.push_back(it->first);
        }
        return ret;
    }

    void findStringMap(string s, unordered_map<string, int>& um)
    {
        int sz = s.length();
        int i = 0, j = 0;
        while (i < sz)
        {
            while (j < sz)
            {
                if (s[j] == ' ')
                    break;
                ++j;
            }
            if (i != j)
            {
                ++um[s.substr(i, j - i)];
            }
            ++j;
            i = j;
        }
    }
};
*/

// 方法二：字符串匹配
class Solution {
public:
    vector<string> uncommonFromSentences(string s1, string s2) {
        
        vector<string> ret;
        findStringMatch(s1, s2, ret);
        findStringMatch(s2, s1, ret);
        return ret;
    }

    bool stringMatch(const string& s, const string& subs)
    {
        int sz = s.length(), sub_sz = subs.size();
        for (int i = 0; i < sz - sub_sz; ++i)
        {
            int idx = i;
            int j = 0;
            for (; j < sub_sz; ++j)
            {
                if (s[idx] == subs[j])
                    ++idx;
                else
                    break;
            }

            if (j == sub_sz)
                return true;
        }
        return false;
    }

    void findStringMatch(const string& s1, const string& s2, vector<string>& ret)
    {
        int sz = s1.size();
        int i = 0, j = 0;
        while (i < sz)
        {
            while (j < sz)
            {
                if (s1[j] == ' ')
                    break;
                ++j;
            }
            if (i != j)
            {
                string sub_s = s1.substr(i, j - i);
                if (!stringMatch(s2, sub_s))
                    ret.push_back(sub_s);
            }
            ++j;
            i = j;
        }
    }
};