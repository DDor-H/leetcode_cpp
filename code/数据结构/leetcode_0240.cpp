
// 方法三：Z字形查找
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();

        int i = 0, j = n - 1;
        while (i < m && j >= 0)
        {
            if (matrix[i][j] == target)
                return true;
            else if (matrix[i][j] > target)
                --j;
            else
                ++i;
        }
        return false;
    }
};

/*
// 方法二：逐行二分查找
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();

        for (int i = 0; i < m; ++i)
        {
            if (binFind(matrix[i], target))
                return true;
        }
        return false;
    }

    bool binFind(vector<int>& v, int target)
    {
        return _binFind(v, target, 0, v.size() - 1);
    }

    bool _binFind(vector<int>& v, int target, int left, int right)
    {
        if (left > right)
            return false;
        int mid = ((left + right) >> 1);
        if (v[mid] == target)
            return true;
        else if (v[mid] > target)
            return _binFind(v, target, left, mid - 1);
        else
            return _binFind(v, target, mid + 1, right);
    }
};

/*
// 方法一：暴力解法（超时）
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (matrix[i][j] == target)
                    return true;
            }
        }
        return false;
    }
};
*/