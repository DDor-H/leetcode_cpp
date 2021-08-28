// 方法一：动态规划
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        if (obstacleGrid[m - 1][n - 1] == 1 || obstacleGrid[0][0] == 1)
            return 0;
        vector<vector<int>> status(m, vector<int>(n, 1));
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (i == 0 || j == 0)
                {
                    if (obstacleGrid[i][j] == 1)
                        status[i][j] = 0;
                    if ((i != 0 && j == 0 && status[i - 1][j] == 0) || (i == 0 && j != 0 && status[i][j - 1] == 0))
                        status[i][j] = 0;
                    continue;
                }
                    
                if (obstacleGrid[i - 1][j] == 1 && obstacleGrid[i][j - 1] == 0)
                    status[i][j] = status[i][j - 1];
                else if (obstacleGrid[i - 1][j] == 0 && obstacleGrid[i][j - 1] == 1)
                    status[i][j] = status[i - 1][j];
                else if (obstacleGrid[i - 1][j] == 0 && obstacleGrid[i][j - 1] == 0)
                    status[i][j] = status[i - 1][j] + status[i][j - 1];
                else
                    status[i][j] = 0;
            }
        }
        return status[m - 1][n - 1];
    }
};

// 方法二：动态规划 + 滚动数组
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        if (obstacleGrid[m - 1][n - 1] == 1 || obstacleGrid[0][0] == 1)
            return 0;
        
        vector<int> status(n, 0);
        status[0] = (obstacleGrid[0][0] == 0);
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (obstacleGrid[i][j] == 1)
                {
                    status[j] = 0;
                    continue;
                }
                // obstacleGrid[i][j - 1] == 0 剪枝操作:若左边位置是障碍，则当前位置直接就是上面的值，不需要计算
                if (j > 0 && obstacleGrid[i][j - 1] == 0)
                    status[j] += status[j - 1];
            }
        }
        return status[n - 1];
    }
};