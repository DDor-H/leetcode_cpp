class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        if (trust.size() == 0)
            return n == 1 ? 1 : -1;
        vector<int> in(n + 1, 0);
        vector<int> out(n + 1, 0);
        for (auto& e : trust)
        {
            ++in[e[1]];
            ++out[e[0]];
        }
            
        for (int i = 1; i <= n; ++i)
        {
            if (in[i] == n - 1 && out[i] == 0)
                return i;
        }
        return -1;
    }
};