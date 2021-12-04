class Solution {
public:
    vector<string> letterCombinations(string digits) {
        int lens = digits.length();
        if (lens == 0)
            return vector<string>();
        vector<string> letters = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        vector<string> ans;
        string subs = "";
        _letterCombinations(digits, letters, ans, subs, 0);
        return ans;
    }

    void _letterCombinations(string& digits, vector<string>& letters, vector<string>& ans, string& subs, int i)
    {
        if (i == digits.length())
        {
            ans.push_back(subs);
            return;
        }
        int posi = digits[i] - '0' - 2;
        int lens = letters[posi].length();
        for (int j = 0; j < lens; ++j)
        {
            subs += letters[posi][j];
            _letterCombinations(digits, letters, ans, subs, i + 1);
            subs.pop_back();
        }
    }
};