// 双指针
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int m = s1.length(), n = s2.length();
        if (m > n)
            return false;

        vector<int> cnt(26);
        for (int i = 0; i < m; ++i)
            --cnt[s1[i] - 'a'];
        int left = 0;
        for (int right = 0; right < n; ++right)
        {
            int x = s2[right] - 'a';
            ++cnt[x];
            while (cnt[x] > 0)
            {
                --cnt[s2[left] - 'a'];
                ++left;
            }
            if (right - left + 1 == m)
                return true;
        }
        return false;
    }
};


/*
// 滑动窗口
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int m = s1.length(), n = s2.length();
        if (m > n)
            return false;
        vector<int> cnt(26);
        for (int i = 0; i < m; ++i)
        {
            --cnt[s1[i] - 'a'];
            ++cnt[s2[i] - 'a'];
        }
        int diff = 0;
        for (auto& ch : cnt)
        {
            if (ch != 0)
                ++diff;
        }
        if (diff == 0)
            return true;
        
        for (int i = m; i < n; ++i)
        {
            int x = s2[i - m] - 'a', y = s2[i] - 'a';
            if (x == y)
                continue;
            if (cnt[y] == 0) // 添加前若为0，则说明加入后就不同了
                ++diff;
            ++cnt[y];  
            if (cnt[y] == 0) // 添加后为0，则说明加入后相同
                --diff;
            if (cnt[x] == 0)
                ++diff;
            --cnt[x];
            if (cnt[x] == 0)
                --diff;

            if (diff == 0)
                return true;
        }
        return false;
    }

    /*
    bool checkInclusion(string s1, string s2) {
        int m = s1.length(), n = s2.length();
        if (m > n)
            return false;
        vector<int> cnt1(26), cnt2(26);
        for (int i = 0; i < m; ++i)
        {
            ++cnt1[s1[i] - 'a'];
            ++cnt2[s2[i] - 'a'];
        }
        if (cnt1 == cnt2)
            return true;
        for (int i = m; i < n; ++i)
        {
            ++cnt2[s2[i] - 'a'];
            --cnt2[s2[i - m] - 'a'];

            if (cnt1 == cnt2)
                return true;
        }
        return false;
    }
};
*/