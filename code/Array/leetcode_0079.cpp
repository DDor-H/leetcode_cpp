class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (check(board, visited, i, j, word, 0))
                    return true;
            }
        }
        return false;
    }

    bool check(vector<vector<char>>& board, vector<vector<bool>>& visited, int i, int j, string& word, int idx)
    {
        if (word[idx] != board[i][j])
            return false;
        else if (idx == word.length() - 1)
            return true;
        
        visited[i][j] = true;
        vector<pair<int, int>> directions{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        bool result = false;
        for (const auto & dir : directions)
        {
            int newi = i + dir.first;
            int newj = j + dir.second;
            if (newi >= 0 && newi < board.size() && newj >= 0 && newj < board[0].size())
            {
                if (!visited[newi][newj] && check(board, visited, newi, newj, word, idx + 1))
                {
                    /*
                    bool flag = check(board, visited, newi, newj, word, idx + 1);
                    if (flag) {
                        result = true;
                        break;
                    }
                    */
                    result = true;
                    break;
                }
            }
        }
        visited[i][j] = false;
        return result;
    }
};