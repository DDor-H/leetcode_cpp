class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<int> status(n, 0);
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (i == 0 && j == 0)
                    status[j] = grid[i][j];
                else if (i == 0 && j != 0)
                    status[j] = grid[i][j] + status[j - 1];
                else if (i != 0 && j == 0)
                    status[j] = grid[i][j] + status[j];
                else
                    status[j] = grid[i][j] + min(status[j], status[j - 1]);
            }
        }
        return status[n - 1];
    }
};