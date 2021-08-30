class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();
        int low = 0, high = m * n - 1;
        int mid = -1;
        while (low <= high)
        {
            mid = low + ((high - low) >> 1);
            int tmp = matrix[mid / n][mid % n];
            if (tmp > target)
                high = mid - 1;
            else if (tmp < target)
                low = mid + 1;
            else
                return true;
        }
        return false;
    }
};