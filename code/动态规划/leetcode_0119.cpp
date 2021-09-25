// 方法二：组合数学
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> res(rowIndex + 1);
        res[0] = 1;
        for (int i = 1; i <= rowIndex; ++i)
            res[i] = 1LL * res[i - 1] * (rowIndex - i + 1) / i;
        return res;
    }
};


/*
// 方法一：动态规划（滚动数组）
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> res(rowIndex + 1);
        for (int i = 0; i <= rowIndex; ++i)
        {
            res[0] = res[i] = 1;
            for (int j = i - 1; j > 0; --j)
                res[j] = res[j - 1] + res[j];
        }
        return res;
    }
};
*/