// 方法四：递推式（组合数学）
class Solution {
public:
    int fib(int n) {
        if (n < 2)
            return n;
        double sqrt5 = sqrt(5);
        double fibn = pow((1 + sqrt5) / 2, n) + pow((1 - sqrt5) / 2, n);
        return round(fibn / sqrt5);
    }
};

/*
// 方法三：矩阵快速幂
class Solution {
public:
    int fib(int n) {
        if (n < 2)
            return n;
        vector<vector<int>> q = {{1, 1}, {1, 0}};
        vector<vector<int>> ret = matrix_pow(q, n - 1);
        return ret[0][0];
    }

    vector<vector<int>> matrix_pow(vector<vector<int>>& a, int n)
    {
        vector<vector<int>> ret = {{1, 0}, {0, 1}};
        while (n > 0)
        {
            if (n & 1)
                ret = matrix_multiply(ret, a);
            n >>= 1;
            a = matrix_multiply(a, a);
        }
        return ret;
    }

    vector<vector<int>> matrix_multiply(vector<vector<int>>& a, vector<vector<int>>& b)
    {
        vector<vector<int>> c = {{0, 0}, {0, 0}};
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                c[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j];
        return c;
    }
};

/*
// 方法二：递归
class Solution {
public:
    int fib(int n) {
        if (n == 0)
            return 0;
        else if (n == 1)
            return 1;
        else 
            return fib(n - 1) + fib(n - 2);
    }
};

/*
// 方法一：循环
class Solution {
public:
    int fib(int n) {
        if (n == 0)
            return 0;
        if (n == 1)
            return 1;
        int a = 0, b = 1;
        int c = 0;
        for (int i = 2; i <= n; ++i)
        {
            c = a + b;
            a = b;
            b = c;
        }
        return c;
    }
};
*/