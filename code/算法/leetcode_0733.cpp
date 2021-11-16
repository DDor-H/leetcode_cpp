

// 广度优先
class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int srcColor = image[sr][sc];
        if (srcColor == newColor)
            return image;
        int m = image.size();
        int n = image[0].size();
        const int dx[4] = {0, -1, 0, 1};
        const int dy[4] = {-1, 0, 1, 0};

        vector<vector<bool>> vis(m, vector<bool>(n, false));
        queue<pair<int, int>> qu;
        qu.push({sr, sc});
        while (!qu.empty())
        {
            tie(sr, sc) = qu.front();
            qu.pop();
            if (image[sr][sc] != srcColor || image[sr][sc] == newColor || vis[sr][sc])
                continue;
            image[sr][sc] = newColor;
            vis[sr][sc] = true;
            for (int i = 0; i < 4; ++i)
            {
                int nx = sr + dx[i], ny = sc + dy[i];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n)
                    qu.push({nx, ny});
            }
        }
        return image;
    }
};

/*
// 深度优先
class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int m = image.size();
        int n = image[0].size();

        int srcColor = image[sr][sc];
        vector<vector<bool>> vis(m, vector<bool>(n, false));
        _floodFill(image, sr, sc, srcColor, newColor, vis);
        return image;
    }

    void _floodFill(vector<vector<int>>& image, int sr, int sc, int srcColor, int newColor, vector<vector<bool>>& vis)
    {
        if (sr < 0 || sr >= image.size() || sc < 0 || sc >= image[0].size())
            return;
        if (vis[sr][sc])
            return;

        if (image[sr][sc] != srcColor)
            return;
        image[sr][sc] = newColor;
        vis[sr][sc] = true;
            
        _floodFill(image, sr - 1, sc, srcColor, newColor, vis);
        _floodFill(image, sr + 1, sc, srcColor, newColor, vis);
        _floodFill(image, sr, sc - 1, srcColor, newColor, vis);
        _floodFill(image, sr, sc + 1, srcColor, newColor, vis);
    }
};
*/