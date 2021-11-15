#include <algorithm>
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int len = s.length();
        if (len <= 1)
            return len;
        unordered_set<char> set;
        int maxLen = 0, left = 0;
        for (int i = 0; i < len; ++i)
        {
            while (set.find(s[i]) != set.end())
                set.erase(s[left++]);
            maxLen = max(maxLen, i - left + 1);
            set.insert(s[i]);
        }
        return maxLen;
    }
/*
    int lengthOfLongestSubstring(string s) {
        if(s.size() == 0)
        {
            return 0;
        }
        int maxLength = 1;

        deque<char> d;  //（时多，空少）或者用map（时少，空多）
        d.push_back(s[0]);

        for(int i = 1; i < s.size(); ++i)
        {
            while (count(d.begin(), d.end(), s[i]) != 0)
            {
                d.pop_front();
            }

            d.push_back(s[i]);

            if(d.size() > maxLength)
            {
                maxLength = d.size();
            }
            
        }
        
        return maxLength;
    }*/
};