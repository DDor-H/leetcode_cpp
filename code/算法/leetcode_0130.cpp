
// 深度优先
class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int m = board.size(), n = board[0].size();

        for (int i = 0; i < m; ++i)
        {
            if (board[i][0] == 'O')
                bfs(board, i, 0);
            if (board[i][n - 1] == 'O')
                bfs(board, i, n - 1);
        }
        for (int i = 0; i < n; ++i)
        {
            if (board[0][i] == 'O')
                bfs(board, 0, i);
            if (board[m - 1][i] == 'O')
                bfs(board, m - 1, i);
        }

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (board[i][j] == 'A')
                    board[i][j] = 'O';
                else if (board[i][j] == 'O')
                    board[i][j] = 'X';
            }
        }
    }
    void bfs(vector<vector<char>>& board, int x, int y)
    {
        board[x][y] = 'A';
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};
        queue<pair<int, int>> q;
        q.push({x, y});
        int m = board.size(), n = board[0].size();

        while (!q.empty())
        {
            pair<int, int> pos = q.front();
            q.pop();
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    int tx = pos.first + dx[i];
                    int ty = pos.second + dy[i];
                    if (tx >= 0 && tx < m && ty >= 0 && ty < n && board[tx][ty] == 'O')
                    {
                        board[tx][ty] = 'A';
                        q.push({tx, ty});
                    }
                }
            }
        }
    }
};

/*
// 深度优先
class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int m = board.size(), n = board[0].size();

        for (int i = 0; i < m; ++i)
        {
            dfs(board, i, 0);
            dfs(board, i, n - 1);
        }
        for (int i = 0; i < n; ++i)
        {
            dfs(board, 0, i);
            dfs(board, m - 1, i);
        }

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (board[i][j] == 'A')
                    board[i][j] = 'O';
                else if (board[i][j] == 'O')
                    board[i][j] = 'X';
            }
        }
    }
    void dfs(vector<vector<char>>& board, int x, int y)
    {
        if (x < 0 || x >= board.size() || y < 0 || y >= board[0].size() || board[x][y] != 'O')
            return;
        board[x][y] = 'A';
        dfs(board, x + 1, y);
        dfs(board, x - 1, y);
        dfs(board, x, y + 1);
        dfs(board, x, y - 1);
    }
};
*/