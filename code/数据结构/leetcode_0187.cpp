
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        const int L = 10;
        if (s.length() <= L)
            return {};
        vector<string> ans;
        unordered_map<char, int> bin = {{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}};
        unordered_map<int, int> map;
        int x = 0;

        for (int i = 0; i < L - 1; ++i)
            x = (x << 2) | bin[s[i]];

        for (int i = 0; i <= s.size() - L; ++i)
        {
            x = ((x << 2) | bin[s[i + L - 1]]) & ((1 << 2 * L) - 1);
            if (++map[x] == 2)
                ans.push_back(s.substr(i, L));
        }
        return ans;
    }
};

/*
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        const int L = 10;
        vector<string> ans;
        unordered_map<string, int> map;
        for (int i = 0; i < s.size() - L; ++i)
        {
            string subs = s.substr(i, L);
            if (++map[subs] == 2)
                ans.push_back(subs);
        }
        return ans;
    }
};
*/