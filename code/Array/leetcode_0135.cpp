
/*
// 一次遍历
class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        int ans = 1;
        int inc = 1, dec = 0, pre = 1;
        for (int i = 1; i < n; ++i)
        {
            if (ratings[i - 1] <= ratings[i])
            {
                dec = 0;
                pre = ratings[i] == ratings[i - 1] ? 1 : pre + 1;
                ans += pre;
                inc = pre;
            }
            else
            {
                ++dec;
                // 注意当当前的递减序列长度和上一个递增序列等长时，
                // 需要把最近的递增序列的最后一个同学也并进递减序列中。
                if (inc == dec)
                    ++dec;
                ans += dec;
                pre = 1;
            }
        }
        return ans;
    }
};
*/

// 两次遍历
class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        vector<int> v(n, 0);
        
        for (int i = 0; i < n; ++i)
        {
            if (i > 0 && ratings[i] > ratings[i - 1])
                v[i] = v[i - 1] + 1;
            else
                v[i] = 1;
        }
        int ans = 0, right = 1;
        for (int i = n - 1; i >= 0; --i)
        {
            if (i < n - 1 && ratings[i] > ratings[i + 1])
                ++right;
            else
                right = 1;
            ans += max(v[i], right);
        }
        return ans;
    }
};