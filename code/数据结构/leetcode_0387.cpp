class Solution {
public:
    //方法一：空间换时间
    /*int firstUniqChar(string s) {
        int Count[256] = {0};
        for (int i = 0; i < s.size(); ++i)
        {
            ++Count[s[i]];
        }
        for (int i = 0; i < s.size(); ++i)
        {
            if (Count[s[i]] == 1)
                return i;
        }
        return -1;
    }*/
    //方法二：正反查
    int firstUniqChar(string s) {
        for (int i = 0; i < s.size(); ++i)
        {
            if (s.find(s[i]) == s.rfind(s[i]))
                return i;
        }
        return -1;
    }
};