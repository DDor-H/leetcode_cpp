// 方法三：单调栈 + 常数优化
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
};


/*
// 方法二：单调栈
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int len = heights.size();
        if (len == 1)
            return heights[0];
        int maxArea = 0;
        vector<int> left(len, 0), right(len, 0);

        stack<int> dp_stack;
        for (int i = 0; i < len; ++i)
        {
            while (!dp_stack.empty() && heights[dp_stack.top()] >= heights[i])
                dp_stack.pop();
            left[i] = (dp_stack.empty() ? -1 : dp_stack.top());
            dp_stack.push(i);
        }
        dp_stack = stack<int>();
        for (int i = len - 1; i >= 0; --i)
        {
            while (!dp_stack.empty() && heights[i] <= heights[dp_stack.top()])
                dp_stack.pop();
            right[i] = (dp_stack.empty() ? len : dp_stack.top());
            dp_stack.push(i);
        }

        for (int i = 0; i < len; ++i)
            maxArea = max(maxArea, heights[i] * (right[i] - left[i] - 1));

        return maxArea;
    }
};

/*
// 方法一：暴力解法(超时)
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int len = heights.size();
        if (len == 1)
            return heights[0];
        int maxArea = 0;
        int left = 0;
        int right = 0;
        for (int i = 0; i < len; ++i)
        {
            left = right = i;
            while (left >= 0 && heights[left] >= heights[i])
                --left;
            ++left;
            while (right < len && heights[right] >= heights[i])
                ++right;
            --right;

            maxArea = max((right - left + 1) * heights[i], maxArea);
        }
        return maxArea;
    }
};
*/