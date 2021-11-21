// 按行访问
class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) return s;

        string ret;
        int n = s.length();
        int cycleLen = 2 * numRows - 2;

        for (int i = 0; i < numRows; ++i)
        {
            for (int j = 0; i + j < n; j += cycleLen)
            {
                ret += s[i + j];
                if (i != 0 && i != numRows - 1 && j + cycleLen - i < n)
                    ret += s[j + cycleLen - i];
            }
        }
        return ret;
    }
};

/*
// 按行排序
class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) return s;

        vector<string> ans(min(numRows, int(s.length())));
        int curRow = 0;
        bool isDown = false;

        for (auto& ch : s)
        {
            ans[curRow] += ch;
            if (curRow == 0 || curRow == numRows - 1) isDown = !isDown;
            curRow += isDown ? 1 : -1;
        }

        string res = "";
        for (auto& str : ans)
            res += str;
        return res;
    }
};
*/