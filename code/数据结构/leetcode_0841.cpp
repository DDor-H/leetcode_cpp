// 深度优先
class Solution {
public:
    void dfs(vector<vector<int>>& rooms, int idx, vector<bool>& vis, int& num)
    {
        vis[idx] = true;
        ++num;
        for (auto& e : rooms[idx])
        {
            if (!vis[e])
                dfs(rooms, e, vis, num);
        }
    }

    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n = rooms.size();
        vector<bool> vis(n, false);
        int num = 0;
        dfs(rooms, 0, vis, num);
        return num == n;
    }
};

/*
// 广度优先
class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n = rooms.size();
        vector<bool> vis(n, false);
        queue<int> qu;
        vis[0] = true;
        qu.push(0);
        int num = 1;
        while (!qu.empty())
        {
            int room_idx = qu.front();
            qu.pop();
            for (int i = 0; i < rooms[room_idx].size(); ++i)
            {
                if (!vis[rooms[room_idx][i]])
                {
                    vis[rooms[room_idx][i]] = true;
                    qu.push(rooms[room_idx][i]);
                    ++num;
                }
            }
        }
        return num == n;
    }
};
*/