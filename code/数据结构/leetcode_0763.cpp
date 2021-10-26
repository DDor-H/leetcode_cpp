class Solution {
public:
    vector<int> partitionLabels(string s) {
        int last[26];
        int n = s.length();
        for (int i = 0; i < n; ++i)
            last[s[i] - 'a'] = i;
        
        vector<int> strlens;
        int start = 0, end = 0;
        for (int i = 0; i < n; ++i)
        {
            // 当前字符的last和前面累计的last的最大值
            end = max(end, last[s[i] - 'a']);
            if (i == end)
            {
                strlens.push_back(end - start + 1);
                start = end + 1;
            }
        }
        return strlens;
    }
};