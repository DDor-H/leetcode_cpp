class Solution {
public:
    string minRemoveToMakeValid(string s) {
        string ans;
        stack<int> st;
        for (int i = 0; i < s.length(); ++i)
        {
            if (s[i] == '(')
                st.push(s[i]);
            else if (s[i] == ')')
            {
                if (st.empty())
                    s[i] = '.';
                else
                    st.pop();
            }
        }

        stack<int> st1;
        for (int i = s.length() - 1; i >= 0; --i)
        {
            if (s[i] == ')')
                st1.push(s[i]);
            else if (s[i] == '(')
            {
                if (st1.empty())
                    s[i] = '.';
                else
                    st1.pop();
            }
        }

        for (int i = 0; i < s.length(); ++i)
        {
            if (s[i] != '.')
                ans += s[i];
        }
        return ans;
    }
};