class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1)
            return -1;
        vector<vector<bool>> vis(n, vector<bool>(n, false));
        queue<pair<int, int>> q;
        q.push({ 0, 0 });
        vis[0][0] = true;
        int dx[8] = { 0, 1, 0, -1, 1, 1, -1, -1 };
        int dy[8] = { 1, 0, -1, 0, 1, -1, -1, 1 };
        int ans = 0;

        int zero_nums = 0;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == 0)
                    ++zero_nums;
            }
        }

        while (!q.empty())
        {
            ++ans;
            int level_count = q.size();
            while (level_count-- > 0)
            {
                pair<int, int> pos = q.front();
                q.pop();
                if (pos.first == n - 1 && pos.second == n - 1)
                    return ans;
                --zero_nums;
                for (int i = 0; i < 8; ++i)
                {
                    int tx = pos.first + dx[i];
                    int ty = pos.second + dy[i];
                    if (tx >= 0 && tx < n && ty >= 0 && ty < n && grid[tx][ty] == 0 && !vis[tx][ty])
                    {
                        vis[tx][ty] = true;
                        q.push({ tx, ty });
                    }
                }
            }
        }
        return zero_nums > 0 ? -1 : ans;
    }
};