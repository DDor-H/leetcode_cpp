class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int cnt = 0, ans = 0;
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dis(m, vector<int>(n, -1));
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};
        queue<pair<int, int>> qu;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == 2)
                {
                    qu.push({i, j});
                    dis[i][j] = 0;
                }
                else if (grid[i][j] == 1)
                    cnt += 1;
            }
        }
        while (!qu.empty())
        {
            pair<int, int> x = qu.front();
            qu.pop();
            for (int i = 0; i < 4; ++i)
            {
                int tx = x.first + dx[i];
                int ty = x.second + dy[i];
                // 新坐标不在范围内、坏橘子点、-1点（第一次访问非坏点都是-1，后面再次遇到访问过的 1 点，就会跳过）
                if (tx < 0 || tx >= m || ty < 0 || ty >= n || !grid[tx][ty] || ~dis[tx][ty])
                    continue;
                dis[tx][ty] = dis[x.first][x.second] + 1;
                qu.push({tx, ty});
                if (grid[tx][ty] == 1)
                {
                    cnt -= 1;
                    ans = dis[tx][ty];
                    if (!cnt)
                        break;
                }
            }
        }
        return cnt == 0 ? ans : -1;
    }
};