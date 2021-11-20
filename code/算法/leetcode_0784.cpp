
class Solution {
public:
    vector<string> letterCasePermutation(string s) {
        vector<string> ans;
        if (s.length() == 0)
            return ans;
        ans.push_back("");
        for (int i = 0; i < s.length(); ++i)
        {
            int n = ans.size();
            if (s[i] >= 48 && s[i] <= 57)
            {
                for (int j = 0; j < n; ++j)
                    ans[j] += s[i];
            }
            if (s[i] >= 65 && s[i] <= 90)
            {
                for (int j = 0; j < n; ++j)
                {
                    ans.push_back(ans[j] + (char)(s[i] + 32));
                    ans[j] += s[i];
                }
            }
            if (s[i] >= 97 && s[i] <= 122)
            {
                for (int j = 0; j < n; ++j)
                {
                    ans.push_back(ans[j] + (char)(s[i] - 32));
                    ans[j] += s[i];
                }
            }
        }
        return ans;
    }
};

/*
// 递归
class Solution {
public:
    vector<string> letterCasePermutation(string s) {
        vector<string> ans;
        if (s.length() == 0)
            return ans;
        _letterCasePermutation(s, ans, 0);
        return ans;
    }

    void _letterCasePermutation(string s, vector<string>& ans, int idx) {
        if (idx == s.length())
        {
            ans.push_back(s);
            return;
        }
        if (s[idx] >= 65 && s[idx] <= 90)
        {
            s[idx] += 32;
            _letterCasePermutation(s, ans, idx + 1);
            s[idx] -= 32;
        }
        if (s[idx] >= 97 && s[idx] <= 122)
        {
            s[idx] -= 32;
            _letterCasePermutation(s, ans, idx + 1);
            s[idx] += 32;
        }
        _letterCasePermutation(s, ans, idx + 1);
    }
};
*/