class Solution {
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        vector<int> stk;
        vector<vector<int>> ans;
        stk.push_back(0);
        _dfs(graph, ans, stk, 0);
        return ans;
    }
    void _dfs(vector<vector<int>>& graph, vector<vector<int>>& ans, vector<int>& stk, int x)
    {
        if (x == graph.size() - 1)
        {
            ans.push_back(stk);
            return;
        }

        for (auto& y : graph[x])
        {
            stk.push_back(y);
            _dfs(graph, ans, stk, y);
            stk.pop_back();
        }
    }
};