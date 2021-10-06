class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<vector<int>> row(9, vector<int>(9, 0));
        vector<vector<int>> col(9, vector<int>(9, 0));
        vector<vector<vector<int>>> subGrid(3, vector<vector<int>>(3, vector<int>(9, 0)));

        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                if (board[i][j] != '.')
                {
                    int index = board[i][j] - '0' - 1;
                    row[i][index]++;
                    col[j][index]++;
                    subGrid[i / 3][j / 3][index]++;
                    if (row[i][index] > 1 || col[j][index] > 1 || subGrid[i / 3][j / 3][index] > 1)
                        return false;
                }
            }
        }
        return true;
    }
};