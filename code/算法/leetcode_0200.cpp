// 深度优先遍历 递归
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<bool>> vis(m, vector<bool>(n, false));
        int count = 0;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == '1' && !vis[i][j])
                {
                    visGrid(grid, vis, i, j);
                    ++count;
                }
            }
        }
        return count;
    }
    void visGrid(vector<vector<char>>& grid, vector<vector<bool>>& vis, int i, int j)
    {
        vis[i][j] = true;
        if (i - 1 >= 0 && grid[i - 1][j] == '1' && !vis[i - 1][j]) // 上
            visGrid(grid, vis, i - 1, j);
        if (i + 1 < grid.size() && grid[i + 1][j] == '1' && !vis[i + 1][j]) // 下
            visGrid(grid, vis, i + 1, j);
        if (j - 1 >= 0 && grid[i][j - 1] == '1' && !vis[i][j - 1]) // 左
            visGrid(grid, vis, i, j - 1);
        if (j + 1 < grid[0].size() && grid[i][j + 1] == '1' && !vis[i][j + 1]) // 右
            visGrid(grid, vis, i, j + 1);
    }
};

/*
// 深度优先遍历 使用栈
// 把栈换成队列即广度优先遍历
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<bool>> vis(m, vector<bool>(n, false));
        int count = 0;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == '1' && !vis[i][j])
                {
                    visGrid(grid, vis, i, j);
                    ++count;
                }
            }
        }
        return count;
    }
    void visGrid(vector<vector<char>>& grid, vector<vector<bool>>& vis, int i, int j)
    {
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};

        stack<pair<int, int>> stk;
        stk.push({i, j});
        while (!stk.empty())
        {
            pair<int, int> cpos = stk.top();
            stk.pop();
            vis[cpos.first][cpos.second] = true;
            for (int k = 0; k < 4; ++k)
            {
                int tx = cpos.first + dx[k];
                int ty = cpos.second + dy[k];
                if (tx >= 0 && tx < grid.size() && ty >= 0 && ty < grid[0].size() && grid[tx][ty] == '1' && !vis[tx][ty])
                    stk.push({tx, ty});
            }
        }
    }
};
*/