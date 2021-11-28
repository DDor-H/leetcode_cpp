
// 滑动窗口（改进）
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int lens = s.length(), lenp = p.length();
        vector<int> ans;
        if (lens < lenp) return ans;
        
        vector<int> count(26, 0);

        for (int i = 0; i < lenp; ++i)
        {
            --count[p[i] - 'a'];
            ++count[s[i] - 'a'];
        }
        int diff = 0;
        for (int i = 0; i < 26; ++i)
        {
            if (count[i] != 0)
                ++diff;
        }
        if (diff == 0)
            ans.push_back(0);
        
        for (int i = lenp; i < lens; ++i)
        {
            if (count[s[i] - 'a'] == -1)
                --diff;
            else if (count[s[i] - 'a'] == 0)
                ++diff;
            ++count[s[i] - 'a'];

            if (count[s[i - lenp] - 'a'] == 1)
                --diff;
            else if (count[s[i - lenp] - 'a'] == 0)
                ++diff;
            --count[s[i - lenp] - 'a'];

            if (diff == 0)
                ans.push_back(i - lenp + 1);
        }
        return ans;
    }
};

/*
// 滑动窗口（数组统计字母个数）
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int lens = s.length(), lenp = p.length();
        vector<int> ans;
        if (lens < lenp) return ans;
        
        vector<int> s_count(26, 0);
        vector<int> p_count(26, 0);

        for (int i = 0; i < lenp; ++i)
        {
            ++p_count[p[i] - 'a'];
            ++s_count[s[i] - 'a'];
        }
        if (p_count == s_count)
            ans.push_back(0);
        
        for (int i = lenp; i < lens; ++i)
        {
            --s_count[s[i - lenp] - 'a'];
            ++s_count[s[i] - 'a'];

            if (s_count == p_count)
                ans.push_back(i - lenp + 1);
        }
        return ans;
    }
};

/*
// 子字符串排序比较（超时）
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int lens = s.length(), lenp = p.length();
        vector<int> ans;
        sort(p.begin(), p.end());
        for (int i = 0; i <= lens - lenp; ++i)
        {
            string subs = s.substr(i, lenp);
            sort(subs.begin(), subs.end());
            if (subs == p)
                ans.push_back(i);
        }
        return ans;
    }
};
*/