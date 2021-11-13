class Solution {
public:
    void reverse(string& s, int start, int end)
    {
        while (start < end)
        {
            char tmp = s[start];
            s[start] = s[end];
            s[end] = tmp;
            ++start;
            --end;
        }
    }
    string reverseWords(string s) {
        if (s.size() <= 1)
            return s;
        int front = 0, back = 0;
        while (front < s.size())
        {
            back = s.find(' ', front);
            if (back != string::npos)
                reverse(s, front, back - 1);
            else
            {
                reverse(s, front, s.size() - 1);
                break;
            }
            front = back + 1;
        }

        return s;
    }
};