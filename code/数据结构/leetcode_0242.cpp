
// 方法二：hash表
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length())
            return false;
        
        unordered_map<char, int> um;
        for (auto& x : s)
        {
            if (um.count(x) > 0)
                ++um[x];
            else
                um.insert(make_pair(x, 1));
        }
        for (auto& x : t)
        {
            if (um.count(x) < 1)
                return false;
            if (--um[x] < 0)
                return false;
        }

        return true;
    }
};

/*
// 方法一：排序
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length())
            return false;
        
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s == t;
    }
};
*/