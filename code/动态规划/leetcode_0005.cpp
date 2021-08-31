// 方法一：暴力解法
class Solution {
public:
    string longestPalindrome(string s) {
        int len = s.length();
        if (len < 2)
            return s;
        
        int maxLen = 1;
        int begin = 0;

        for (int i = 0; i < len - 1; ++i)
        {
            for ( int j = i + 1; j < len; ++j)
            {
                if (isPalindrome(s, i, j) && (j - i + 1) > maxLen)
                {
                    maxLen = j - i + 1;
                    begin = i;
                }
            }
        }
        return s.substr(begin, maxLen);
    }
    bool isPalindrome(string& s, int left, int right)
    {
        while (left < right && s[left] == s[right])
        {
            ++left;
            --right;
        }
        return (left >= right);
    }
};

// 方法二：中间扩散法
class Solution {
public:
    string longestPalindrome(string s) {
        int len = s.length();
        if (len < 2)
            return s;
        
        int begin = 0;
        int end = 0;
        for (int i = 0; i < len - 1; ++i)
        {
            auto [left1, right1] = isPalindrome(s, i, i);
            auto [left2, right2] = isPalindrome(s, i, i + 1);
            if (right1 - left1 > end - begin)
            {
                begin = left1;
                end = right1;
            }
            if (right2 - left2 > end - begin)
            {
                begin = left2;
                end = right2;
            }
        }
        return s.substr(begin, end - begin + 1);
    }
    pair<int, int> isPalindrome(const string& s, int left, int right)
    {
        while (left >= 0 && right < s.size() && s[left] == s[right])
        {
            --left;
            ++right;
        }
        return {left + 1, right - 1};
    }
};

// 方法三：动态规划
class Solution {
public:
    string longestPalindrome(string s) {
        int len = s.length();
        if (len < 2)
            return s;
        
        int maxLen = 1;
        int begin = 0;
        vector<vector<bool>> vv(len, vector<bool>(len, false));
        for (int i = 0; i < len; ++i)
        {
            vv[i][i] = true;
            if (i < len - 1 && s[i] == s[i + 1])
            {
                vv[i][i + 1] = true;
                maxLen = 2;
                begin = i;
            }
        }

        for (int l = 3; l <= len; ++l)
        {
            for (int i = 0; i + l - 1 < len; ++i)
            {
                int j = i + l - 1;
                if (s[i] == s[j] && vv[i + 1][j - 1])
                {
                    vv[i][j] = true;
                    maxLen = l;
                    begin = i;
                }
            }
        }
        
        return s.substr(begin, maxLen);
    }
};
