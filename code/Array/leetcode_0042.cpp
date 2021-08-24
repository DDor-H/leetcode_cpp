// 方法一：
class Solution {
public:
    int trap(vector<int>& height) {
        int len = height.size();
        int count = 0;
        for (int i = 1; i < len - 1; ++i)
        {
            int leftMax = height[0];
            int rightMax = height[len - 1];
            for (int j = 1; j < i; ++j)
            {
                if (height[j] > leftMax)
                    leftMax = height[j];
            }   
            for (int j = len - 2; j > i; --j)
            {
                if (height[j] > rightMax)
                    rightMax = height[j];
            }

            int minMax = (leftMax < rightMax ? leftMax : rightMax);
            if (height[i] < minMax)
                count += (minMax - height[i]);
        }
        return count;
    }
};

// 方法二：
class Solution {
public:
    int trap(vector<int>& height) {
        int len = height.size();
        if (len <= 2)
            return 0;
        int count = 0;

        vector<int> leftMax(len);
        leftMax[0] = height[0];
        for (int i = 1; i < len; ++i)
            leftMax[i] = max(leftMax[i - 1], height[i]);

        vector<int> rightMax(len);
        rightMax[len - 1] = height[len - 1];
        for (int i = len - 2; i >= 0; --i)
            rightMax[i] = max(rightMax[i + 1], height[i]);

        for (int i = 1; i < len - 1; ++i)
        {
            int minMax = (leftMax[i] < rightMax[i] ? leftMax[i] : rightMax[i]);
            if (minMax > height[i])
                count += minMax - height[i];
        }

        return count;
    }
};

// 方法三：
class Solution {
public:
    int trap(vector<int>& height) {
        int len = height.size();
        if (len <= 2)
            return 0;
        int count = 0;

        stack<int> st;
        for (int i = 0;i < len ; ++i)
        {
            while (!st.empty() && height[i] > height[st.top()])
            {
                int top = st.top();
                st.pop();

                // 1 号柱子比 0 号柱子高，所以不会存雨
                if (st.empty())
                    break;
                
                int left = st.top();
                count += (min(height[left], height[i]) - height[top]) * (i - left - 1);
            }
            st.push(i);
        }
        return count;
    }
};

// 方法四：
class Solution {
public:
    int trap(vector<int>& height) {
        int len = height.size();
        if (len <= 2)
            return 0;
        int count = 0;

        int left = 0, right = len - 1;
        int leftMax = 0, rightMax = 0;
        while (left < right)
        {
            leftMax = max(leftMax, height[left]);
            rightMax = max(rightMax, height[right]);

            if (height[left] < height[right])
            {
                count += leftMax - height[left];
                ++left;
            }
            else
            {
                count += rightMax - height[right];
                --right;
            }
        }
        return count;
    }
};