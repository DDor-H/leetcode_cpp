class Solution {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c) {
        int m = mat.size(), n = mat[0].size();
        if (m * n != r * c)
            return mat;
        
        vector<vector<int>> res(r, vector<int>(c, 0));
        for (int x = 0; x < m * n; ++x)
            res[x / c][x % c] = mat[x / n][x % n];
        return res;
    }
};