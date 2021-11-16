// 广度遍历
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<bool>> vis(m, vector<bool>(n, false));
        int maxArea = 0;
        const int dx[4] = { 0, -1, 0, 1 };
        const int dy[4] = { -1, 0, 1, 0 };
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] != 1 || vis[i][j])
                    continue;
                int area = 0;
                queue<pair<int, int>> qu;
                qu.push({ i, j });
                vis[i][j] = true;
                ++area;
                while (!qu.empty())
                {
                    int newi = qu.front().first, newj = qu.front().second;
                    qu.pop();
                    for (int k = 0; k < 4; ++k)
                    {
                        int nx = newi + dx[k], ny = newj + dy[k];
                        if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 1 && vis[nx][ny] == false)
                        {
                            vis[nx][ny] = true;
                            ++area;
                            qu.push({ nx, ny });
                        }
                    }
                }
                maxArea = max(maxArea, area);
            }
        }
        return maxArea;
    }
};

/*
// 深度遍历 非递归
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<bool>> vis(m, vector<bool>(n, false));
        int maxArea = 0;
        const int dx[4] = { 0, -1, 0, 1 };
        const int dy[4] = { -1, 0, 1, 0 };
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] != 1 || vis[i][j])
                    continue;
                int area = 0;
                stack<pair<int, int>> stk;
                stk.push({ i, j });
                vis[i][j] = true;
                ++area;
                while (!stk.empty())
                {
                    int newi = stk.top().first, newj = stk.top().second;
                    stk.pop();
                    for (int k = 0; k < 4; ++k)
                    {
                        int nx = newi + dx[k], ny = newj + dy[k];
                        if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 1 && vis[nx][ny] == false)
                        {
                            vis[nx][ny] = true;
                            ++area;
                            stk.push({ nx, ny });
                        }
                    }
                }
                maxArea = max(maxArea, area);
            }
        }
        return maxArea;
    }
};

/*
// 深度遍历 递归
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<bool>> vis(m, vector<bool>(n, false));
        int maxArea = 0;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] != 1 || vis[i][j])
                    continue;
                int area = 0;
                _maxAreaOfIsland(grid, area, i, j, vis);
                maxArea = max(maxArea, area);
            }
        }
        return maxArea;
    }

    void _maxAreaOfIsland(vector<vector<int>>& grid, int& area, int i, int j, vector<vector<bool>>& vis)
    {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size())
            return;
        if (grid[i][j] == 0 || vis[i][j])
            return;
        ++area;
        vis[i][j] = true;
        _maxAreaOfIsland(grid, area, i + 1, j, vis);
        _maxAreaOfIsland(grid, area, i - 1, j, vis);
        _maxAreaOfIsland(grid, area, i, j + 1, vis);
        _maxAreaOfIsland(grid, area, i, j - 1, vis);
    }
};
*/