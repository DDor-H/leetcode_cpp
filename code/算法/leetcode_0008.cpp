class Solution {
public:
    int myAtoi(string s) {
        int len = s.length();
        if (len == 0) return 0;

        int i = 0;
        for (; i < len; ++i)
        {
            if (s[i] != ' ')
                break;
        }
        if (i == len) return 0;
        bool flag = true;
        if (s[i] == '-' || s[i] == '+')
        {
            if (s[i] == '-')
                flag = false;
            ++i;
        }
        string ans_s = "";
        for (; i < len; ++i)
        {
            if (s[i] >= '0' && s[i] <= '9')
                ans_s += s[i];
            else
                break;
        }
        long long ans = 0;
        for (int j = 0; j < ans_s.length(); ++j)
        {
            ans = ans * 10 + ans_s[j] - '0';
            ans = flag ? min(ans, (long long)INT_MAX) : min(ans, -(long long)INT_MIN); // 防止越界操作
        }
            
        ans *= flag ? 1 : -1;

        const int S = pow(-2, 31);
        const int B = pow(2, 31) - 1;
        if (ans < S)
            return S;
        if (ans > B)
            return B;
        return (int)ans;
    }
};