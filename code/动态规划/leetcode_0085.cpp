
// 方法三：动态规划
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int rows = matrix.size();
        if (rows == 0)
            return 0;
        int cols = matrix[0].size();
        vector<int> heights(cols, 0);
        vector<int> left(cols, -1), right(cols, cols);
        int maxArea = 0;

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (matrix[i][j] == '1')
                    heights[j] += 1;
                else
                    heights[j] = 0;
            }

            int boundary = -1;
            for (int j = 0; j < cols; ++j)
            {
                if (matrix[i][j] == '1')
                    left[j] = max(left[j], boundary);
                else
                {
                    left[j] = -1;
                    boundary = j;
                }
            }

            boundary = cols;
            for (int j = cols - 1; j >= 0; --j)
            {
                if (matrix[i][j] == '1')
                    right[j] = min(right[j], boundary);
                else
                {
                    right[j] = cols;
                    boundary = j;
                }
            }

            for (int j = 0; j < cols; ++j)
                maxArea = max(maxArea, heights[j] * (right[j] - left[j] - 1));
        }

        return maxArea;
    }
};

/*
// 方法二：整合顺序栈
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int rows = matrix.size();
        if (rows == 0)
            return 0;
        int cols = matrix[0].size();
        vector<int> dp(cols, 0);
        int maxArea = 0;

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (matrix[i][j] == '1')
                    dp[j] = (i == 0 ? 0 : dp[j]) + 1;
                else
                    dp[j] = 0;
            }

            vector<int> left(cols, 0), right(cols, cols);
            stack<int> dp_stack;
            for (int j = 0; j < cols; ++j)
            {
                while (!dp_stack.empty() && dp[dp_stack.top()] >= dp[j])
                {
                    right[dp_stack.top()] = j;
                    dp_stack.pop();
                }
                left[j] = (dp_stack.empty() ? -1 : dp_stack.top());
                dp_stack.push(j);
            }
            for (int j = 0; j < cols; ++j)
                maxArea = max(maxArea, dp[j] * (right[j] - left[j] - 1));
        }

        return maxArea;
    }
};

/*
// 方法二：调用顺序栈柱状函数
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int len = heights.size();
        if (len == 1)
            return heights[0];
        int maxArea = 0;
        vector<int> left(len, 0), right(len, len);
        stack<int> dp_stack;
        for (int i = 0; i < len; ++i)
        {
            while (!dp_stack.empty() && heights[dp_stack.top()] >= heights[i])
            {
                right[dp_stack.top()] = i;
                dp_stack.pop();
            }
            left[i] = (dp_stack.empty() ? -1 : dp_stack.top());
            dp_stack.push(i);
        }
        for (int i = 0; i < len; ++i)
            maxArea = max(maxArea, heights[i] * (right[i] - left[i] - 1));
        
        return maxArea;
    }

    int maximalRectangle(vector<vector<char>>& matrix) {
        int rows = matrix.size();
        if (rows == 0)
            return 0;
        int cols = matrix[0].size();
        
        vector<int> dp(cols, 0);
        int maxArea = 0;

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (matrix[i][j] == '1')
                    dp[j] = (i == 0 ? 0 : dp[j]) + 1;
                else
                    dp[j] = 0;
            }

            maxArea = max(maxArea, largestRectangleArea(dp));
        }

        return maxArea;
    }
};

/*
// 方法一：暴力解法
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int rows = matrix.size();
        if (rows == 0)
            return 0;
        int cols = matrix[0].size();
        
        vector<vector<int>> dp(rows, vector<int>(cols, 0));
        int maxArea = 0;

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (matrix[i][j] == '1')
                {
                    if (j == 0)
                        dp[i][j] = 1;
                    else
                        dp[i][j] = dp[i][j - 1] + 1;
                }
                else
                {
                    dp[i][j] = 0;
                }

                int minWidth = dp[i][j];
                for (int up_i = i; up_i >= 0; --up_i)
                {
                    int height = i - up_i + 1;
                    minWidth = min(minWidth, dp[up_i][j]);
                    maxArea = max(maxArea, height * minWidth);
                }
            }
        }
        return maxArea;
    }
};
*/