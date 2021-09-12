
// 方法四：左右指针法
class Solution {
public:
    int longestValidParentheses(string s) {
        int len = s.length();
        if (len <= 1)
            return 0;
        int maxlen = 0;
        
        int left = 0, right = 0;
        for (int i = 0; i < len; ++i)
        {
            if (s[i] == '(')
                ++left;
            else if (s[i] == ')')
                ++right;

            if (left == right)
                maxlen = max(maxlen, 2 * right);
            else if (right > left)
                left = right = 0;
        }
        left = 0, right = 0;
        for (int i = len - 1; i >= 0; --i)
        {
            if (s[i] == '(')
                ++left;
            else if (s[i] == ')')
                ++right;

            if (left == right)
                maxlen = max(maxlen, 2 * left);
            else if (left > right)
                left = right = 0;
        }

        return maxlen;
    }
};

/*
// 方法三：动态规划
class Solution {
public:
    int longestValidParentheses(string s) {
        int len = s.length();
        if (len <= 1)
            return 0;
        stack<int> st;
        st.push(-1);
        int maxlen = 0;
        for (int i = 0; i < len; ++i)
        {
            if (s[i] == '(')
                st.push(i);
            else
            {
                st.pop();
                if (st.empty())
                    st.push(i);
                else
                    maxlen = (i - st.top()) > maxlen ? (i - st.top()) : maxlen;
            }
        }
        return maxlen;
    }
};

/*
// 方法二：动态规划
class Solution {
public:
    int longestValidParentheses(string s) {
        int len = s.length();
        if (len <= 1)
            return 0;
        vector<int> dp(len, 0);
        int maxlen = 0;
        for (int i = 1; i < len; ++i)
        {
            if (s[i] == ')')
            {
                if (s[i - 1] == '(')
                    dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
                else if (i - dp[i - 1] - 1 >= 0 && s[i - dp[i - 1] - 1] == '(')
                    dp[i] = dp[i - 1] + ((i - dp[i - 1] - 2) >= 0 ? dp[i - dp[i - 1] - 2] : 0) + 2;

                maxlen = (maxlen > dp[i] ? maxlen : dp[i]);
            }
        }
        return maxlen;
    }
};


/*
// 方法一：暴力解法
class Solution {
public:
    int longestValidParentheses(string s) {
        int len = s.length();
        if (len <= 1)
            return 0;
        int maxLen = 0;
        for (int i = 0; i < len - 1; ++i)
        {
            for (int j = i + 1; j < len; ++j)
            {
                if (isVaild(s, i, j) && (j - i + 1 > maxLen))
                    maxLen = j - i + 1;
            }
        }
        return maxLen;
    }
    
    bool isVaild(string s, int start, int end)
    {
        if ((end - start + 1) % 2 == 1)
            return false;
        if (s[start] == ')' || s[end] == '(')
            return false;

        int balance = 0;
        for (int i = start; i <= end; ++i)
        {
            if (s[i] == '(')
                ++balance;
            else if (s[i] == ')')
                --balance;
            
            if (balance < 0)
                return false;
        }

        return balance == 0;
    }
};
*/