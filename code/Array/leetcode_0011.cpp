class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;

        int maxArea = 0;
        int tmpArea = 0;

        while (left < right)
        {
            tmpArea = (right - left) * (height[left] < height[right] ? height[left] : height[right]);
            if (maxArea < tmpArea)
                maxArea = tmpArea;
            if (height[left] < height[right])
                left++;
            else
                right--;
        }
        return maxArea;
    }
};