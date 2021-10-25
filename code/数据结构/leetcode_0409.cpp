class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char, int> map;
        for (auto& e : s)
            ++map[e];
        int exist_odd = false;
        int res = 0;
        for (auto& e : map)
        {
            if (e.second % 2 == 0)
                res += e.second;
            else 
            {
                res += e.second / 2 * 2;
                exist_odd = true;
            }
        }
        res += exist_odd ? 1 : 0;
        return res;
    }
};