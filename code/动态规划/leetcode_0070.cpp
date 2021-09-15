// 方法三：矩阵快速幂
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2)
            return n;
        
        vector<vector<long>> m = {{1, 1}, {1, 0}};
        vector<vector<long>> ret = matrix_pow(m, n - 2);
                
        return 2 * ret[0][0] + ret[0][1];
    }

    vector<vector<long>> matrix_pow(vector<vector<long>>& a, int n)
    {
        vector<vector<long>> ret = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
        while (n > 0)
        {
            if (n & 1)
                ret = matrix_multiply(ret, a);
            n >>= 1;
            a = matrix_multiply(a, a);
        }
        return ret;
    }

    vector<vector<long>> matrix_multiply(vector<vector<long>>& a, vector<vector<long>>& b)
    {
        vector<vector<long>> c = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                c[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] + a[i][2] * b[2][j];
        return c;
    }
};


/*
// 方法二：递归(超时)
class Solution {
public:
    int climbStairs(int n) {
        int count = 0;
        _climbStairs(n, count);
        return count;
    }

    void _climbStairs(int n, int& count) 
    {
        if (n <= 0)
        {
            if (n == 0)
                ++count;
            return;
        }

        _climbStairs(n - 1, count);
        _climbStairs(n - 2, count);
    }
};



/*
// 方法一：循环
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2)
            return n;
        int a = 1, b = 2, c = 0;
        for (int i = 2; i < n; ++i)
        {
            c = a + b;
            a = b;
            b = c;
        }
                
        return c;
    }
};
*/