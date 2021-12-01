class UnionFindSet {
public:
    UnionFindSet(int lens)
    {
        parent = vector<int>(lens, -1);
        rank = vector<int>(lens, 0);
        set_nums = 0;
    }

    int find(int x)
    {
        int x_root = x;
        while (parent[x_root] != -1)
        {
            x_root = parent[x];
            x = x_root;
        }

        return x_root;
    }

    bool merge(int x, int y)
    {
        int x_root = find(x);
        int y_root = find(y);

        if (x_root == y_root)
            return false;
        
        if (rank[x_root] > rank[y_root])
            parent[y_root] = x_root;
        else if (rank[y_root] > rank[x_root])
            parent[x_root] = y_root;
        else
        {
            parent[y_root] = x_root;
            ++rank[x_root];
        }
        return true;
    }

    int count_set_nums()
    {
        for (int i = 0; i < parent.size(); ++i)
        {
            if (parent[i] == -1)
                ++set_nums;
        }
        return set_nums;
    }

private:
    vector<int> parent;
    vector<int> rank;
    int set_nums;
};

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        UnionFindSet ufs = UnionFindSet(n);
        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                if (isConnected[i][j] == 1)
                    ufs.merge(i, j);
            }
        }
        return ufs.count_set_nums();
    }
};