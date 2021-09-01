
// 方法三：动态规划
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        if (n == 0)
            return {};
        if (n == 1)
            return {"()"};

        vector<vector<string>> res(n + 1);
        res[0] = {""};
        res[1] = {"()"};

        for (int i = 2; i <= n; ++i)
            for (int j = 0; j < i; ++j)
                for (auto p : res[j])
                    for (auto q : res[i - j - 1])
                        res[i].push_back(('(' + q + ')' + p));
        
        return res[n];
    }
};


// 方法二：回溯法
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        string parenthesis;
        _generateParenthesis(res, parenthesis, n, 0, 0);
        return res;
    }

    void _generateParenthesis(vector<string>& res, string& parenthesis, int n, int idx, int jdx)
    {
        if (idx == n && jdx == n)
        {
            res.push_back(parenthesis);
            return;
        }
        
        if (idx < n)
        {
            parenthesis += '(';
            _generateParenthesis(res, parenthesis, n, idx + 1, jdx);
            parenthesis.pop_back();
        }

        if (jdx < idx)
        {
            parenthesis += ')';
            _generateParenthesis(res, parenthesis, n, idx, jdx + 1);
            parenthesis.pop_back();
        }
    }
};


// 方法一：递归暴力方法
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        string parenthesis;
        _generateParenthesis(res, parenthesis, n * 2, 0);
        return res;
    }

    void _generateParenthesis(vector<string>& res, string& parenthesis, int n, int idx)
    {
        if (idx == n)
        {
            if (check(parenthesis))
                res.push_back(parenthesis);
            return;
        }
        
        parenthesis += '(';
        _generateParenthesis(res, parenthesis, n, idx + 1);
        parenthesis.pop_back();
        parenthesis += ')';
        _generateParenthesis(res, parenthesis, n, idx + 1);
        parenthesis.pop_back();
    }

    bool check(string& parenthesis)
    {
        int len = parenthesis.length();
        int num = 0;
        if (parenthesis[0] == ')' || parenthesis[len - 1] == '(')
            return false;
        for (int i = 0; i < len; ++i)
        {
            if (parenthesis[i] == '(')
                ++num;
            else if (parenthesis[i] == ')')
                --num;
            if (num < 0)
                return false;
        }
        return num == 0;
    }
};
