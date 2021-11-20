// 动态规划
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> dis(m, vector<int>(n, INT_MAX / 2));
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (mat[i][j] == 0)
                    dis[i][j] = 0;
            }
        }

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (i - 1 >= 0)
                    dis[i][j] = min(dis[i][j], dis[i - 1][j] + 1);
                if (j - 1 >= 0)
                    dis[i][j] = min(dis[i][j], dis[i][j - 1] + 1);
            }
        }
        for (int i = m - 1; i >= 0; --i)
        {
            for (int j = n - 1; j >= 0; --j)
            {
                if (i + 1 < m)
                    dis[i][j] = min(dis[i][j], dis[i + 1][j] + 1);
                if (j + 1 < n)
                    dis[i][j] = min(dis[i][j], dis[i][j + 1] + 1);
            }
        }

        return dis;
    }
};

/*
// 多元广度优先遍历
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> dis(m, vector<int>(n, -1));
        queue<pair<int, int>> Q;
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (mat[i][j] == 0)
                {
                    Q.push({i, j});
                    dis[i][j] = 0;
                }
            }
        }

        while (!Q.empty())
        {
            pair<int, int> x = Q.front(); Q.pop();
            for (int i = 0; i < 4; ++i)
            {
                int tx = x.first + dx[i];
                int ty = x.second + dy[i];
                if (tx < 0 || tx >= m || ty < 0 || ty >= n || !mat[tx][ty] || ~dis[tx][ty])
                    continue;
                dis[tx][ty] = dis[x.first][x.second] + 1;
                Q.push({tx, ty});
            }
        }
        return dis;
    }
};
*/