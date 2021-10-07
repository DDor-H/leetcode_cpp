
// 方法三：
class Solution {
private:
    vector<int> row;
    vector<int> col;
    vector<vector<int>> subGrid;
    vector<pair<int, int>> space;
    bool valid;


public:
    void solveSudoku(vector<vector<char>>& board) {
        row = vector<int>(9, 0);
        col = vector<int>(9, 0);
        subGrid = vector<vector<int>>(3, vector<int>(3, 0));
        valid = false;

        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                if (board[i][j] != '.')
                {
                    int index = board[i][j] - '0' - 1;
                    flip(i, j, index);
                }
            }
        }

        while(true)
        {
            bool modified = false;
            for (int i = 0; i < 9; ++i)
            {
                for (int j = 0; j < 9; ++j)
                {
                    if (board[i][j] == '.')
                    {
                        int mask = ~(row[i] | col[j] | subGrid[i / 3][j / 3]) & 0x1ff;
                        if (!(mask & (mask - 1)))
                        {
                            int digitMask = mask & (-mask);
                            int digit = __builtin_ctz(digitMask);
                            flip(i, j, digit);
                            board[i][j] = digit + '0' + 1;
                            modified = true;
                        }
                    }
                }
            }
            if (!modified)
                break;
        }

        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                if (board[i][j] == '.')
                    space.push_back(make_pair(i, j));
            }
        }
        dfs(board, 0);
    }

    void dfs(vector<vector<char>>& board, int pos)
    {
        if (pos == space.size())
        {
            valid = true;
            return;
        }

        auto [i, j] = space[pos];
        int mask = ~(row[i] | col[j] | subGrid[i / 3][j / 3]) & 0x1ff;
        for (; mask && !valid; mask &= (mask - 1))
        {
            int digitMask = mask & (-mask);
            int digit = __builtin_ctz(digitMask);
            flip(i, j, digit);
            board[i][j] = digit + '0' + 1;
            dfs(board, pos + 1);
            flip(i, j, digit);
        }
    }

    void flip(int i, int j, int digit)
    {
        row[i] ^= (1 << digit);
        col[j] ^= (1 << digit);
        subGrid[i / 3][j / 3] ^= (1 << digit);
    }
};

/*
// 方法二：位运算优化
class Solution {
private:
    vector<int> row;
    vector<int> col;
    vector<vector<int>> subGrid;
    vector<pair<int, int>> space;
    bool valid;


public:
    void solveSudoku(vector<vector<char>>& board) {
        row = vector<int>(9, 0);
        col = vector<int>(9, 0);
        subGrid = vector<vector<int>>(3, vector<int>(3, 0));
        valid = false;

        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                if (board[i][j] == '.')
                    space.push_back(make_pair(i, j));
                else
                {
                    int index = board[i][j] - '0' - 1;
                    flip(i, j, index);
                }
            }
        }
        dfs(board, 0);
    }

    void dfs(vector<vector<char>>& board, int pos)
    {
        if (pos == space.size())
        {
            valid = true;
            return;
        }

        auto [i, j] = space[pos];
        int mask = ~(row[i] | col[j] | subGrid[i / 3][j / 3]) & 0x1ff;
        for (; mask && !valid; mask &= (mask - 1))
        {
            int digitMask = mask & (-mask);
            int digit = __builtin_ctz(digitMask);
            flip(i, j, digit);
            board[i][j] = digit + '0' + 1;
            dfs(board, pos + 1);
            flip(i, j, digit);
        }
    }

    void flip(int i, int j, int digit)
    {
        row[i] ^= (1 << digit);
        col[j] ^= (1 << digit);
        subGrid[i / 3][j / 3] ^= (1 << digit);
    }
};

/*
// 方法一：递归
class Solution {
private:
    vector<vector<bool>> row;
    vector<vector<bool>> col;
    vector<vector<vector<bool>>> subGrid;
    vector<pair<int, int>> space;
    bool valid;


public:
    void solveSudoku(vector<vector<char>>& board) {
        row = vector<vector<bool>>(9, vector<bool>(9, false));
        col = vector<vector<bool>>(9, vector<bool>(9, false));
        subGrid = vector<vector<vector<bool>>>(3, vector<vector<bool>>(3, vector<bool>(9, false)));
        valid = false;

        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                if (board[i][j] == '.')
                    space.push_back(make_pair(i, j));
                else
                {
                    int index = board[i][j] - '0' - 1;
                    row[i][index] = col[j][index] = subGrid[i / 3][j / 3][index] = true;
                }
            }
        }
        dfs(board, 0);
    }

    void dfs(vector<vector<char>>& board, int pos)
    {
        if (pos == space.size())
        {
            valid = true;
            return;
        }

        auto [i, j] = space[pos];
        for (int digit = 0; digit < 9 && !valid; ++digit)
        {
            if (!row[i][digit] && !col[j][digit] && !subGrid[i / 3][j / 3][digit])
            {
                row[i][digit] = col[j][digit] = subGrid[i / 3][j / 3][digit] = true;
                board[i][j] = digit + '0' + 1;
                dfs(board, pos + 1);
                row[i][digit] = col[j][digit] = subGrid[i / 3][j / 3][digit] = false;
            }
        }
    }
};
*/


