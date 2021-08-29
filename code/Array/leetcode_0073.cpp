// 方法一：一个标志位
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        if (matrix.size() == 0 || matrix[0].size() == 0)
            return;
        int m = matrix.size(), n = matrix[0].size();
        bool isFirstColExistZero = false;
        int i = 0, j = 0;

        for (i = 0; i < m; ++i)
        {
            if (matrix[i][0] == 0)
                isFirstColExistZero = true;
            for (j = 1; j < n; ++j)
            {
                if (matrix[i][j] == 0)
                {
                    matrix[i][0] = matrix[0][j] = 0;
                }
            }
        }

        for (i = m - 1; i >= 0; --i)
        {
            for (j = 1; j < n; ++j)
            {
                if (matrix[i][0] == 0 || matrix[0][j] == 0)
                    matrix[i][j] = 0;
            }
            if (isFirstColExistZero)
                matrix[i][0] = 0;
        }
    }
};

// 方法二：两个标志位
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        if (matrix.size() == 0 || matrix[0].size() == 0)
            return;
        int m = matrix.size(), n = matrix[0].size();
        bool isFirstRowExistZero = false, isFirstColExistZero = false;
        int i = 0, j = 0;
        for (j = 0; j < n; ++j)
        {
            if (matrix[0][j] == 0)
            {
                isFirstRowExistZero = true;
                break;
            }
        }

        for (i = 0; i < m; ++i)
        {
            if (matrix[i][0] == 0)
            {
                isFirstColExistZero = true;
                break;
            }
        }

        for (i = 1; i < m; ++i)
        {
            for (j = 1; j < n ; ++j)
            {
                if (matrix[i][j] == 0)
                {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        for (i = 1; i < m; ++i)
        {
            if (matrix[i][0] == 0)
            {
                for (j = 1; j < n; ++j)
                    matrix[i][j] = 0;
            }
        }

        for (j = 1; j < n; ++j)
        {
            if (matrix[0][j] == 0)
            {
                for (i = 1; i < m; ++i)
                    matrix[i][j] = 0;
            }
        }

        if (isFirstColExistZero)
        {
            for (i = 0; i < m; ++i)
                matrix[i][0] = 0;
        }

        if (isFirstRowExistZero)
        {
            for (j = 0; j < n; ++j)
                matrix[0][j] = 0;
        }
    }
};