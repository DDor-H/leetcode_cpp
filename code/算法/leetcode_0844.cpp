
// 双指针
class Solution {
public:
    bool backspaceCompare(string s, string t) {
        int i = s.length() - 1, j = t.length() - 1;
        int count_i = 0, count_j = 0;
        while (i >= 0 || j >= 0)
        {
            while (i >= 0)
            {
                if (s[i] == '#')
                    --i, ++count_i;
                else if (count_i > 0)
                    --i, --count_i;
                else
                    break;
            }
            while (j >= 0)
            {
                if (t[j] == '#')
                    --j, ++count_j;
                else if (count_j > 0)
                    --j, --count_j;
                else
                    break;
            }
            
            if (i >= 0 && j >= 0)
            {
                if (s[i] != t[j])
                    return false;
            }
            else
            {
                if (i >= 0 || j >= 0)
                    return false;
            }
            --i, --j;
        }
        return true;
    }
};

/*
// 使用栈
class Solution {
public:
    bool backspaceCompare(string s, string t) {
        return build(s) == build(t);
    }

    stack<char> build(string s)
    {
        stack<char> stk;
        for (int i = 0; i < s.length(); ++i)
        {
            if (s[i] != '#')
                stk.push(s[i]);
            else
            {
                if (!stk.empty())
                    stk.pop();
            }
        }
        return stk;
    }
};
*/