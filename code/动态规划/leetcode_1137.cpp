// 方法三：矩阵快速幂
class Solution {
public:
    int tribonacci(int n) {
        if (n < 2)
            return n;
        else if (n == 2)
            return 1;
        vector<vector<long>> q = {{1, 1, 1}, {1, 0, 0}, {0, 1, 0}};
        vector<vector<long>> ret = matrix_pow(q, n - 2);
        return ret[0][0] + ret[0][1];        
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
    int tribonacci(int n) {
        if (n < 2)
            return n;
        else if (n == 2)
            return 1;
        
        return tribonacci(n - 1) + tribonacci(n - 2) + tribonacci( n - 3);
    }
};


/*
// 方法二：递归(超时)
class Solution {
public:
    int tribonacci(int n) {
        if (n < 2)
            return n;
        else if (n == 2)
            return 1;
        
        return tribonacci(n - 1) + tribonacci(n - 2) + tribonacci( n - 3);
    }
};



/*
// 方法一：循环
class Solution {
public:
    int tribonacci(int n) {
        if (n < 2)
            return n;
        else if (n == 2)
            return 1;
        
        int a = 0, b = 1, c = 1;
        int d = 0;
        for (int i = 3; i <= n; ++i)
        {
            d = a + b + c;
            a = b;
            b = c;
            c = d;
        }
        return d;
    }
};
*/