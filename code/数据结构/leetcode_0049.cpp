class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> map;
        for (auto& e : strs)
        {
            string tmp = e;
            sort(tmp.begin(), tmp.end());
            map[tmp].push_back(e);
        }
        vector<vector<string>> ans;
        for (auto it = map.begin(); it != map.end(); ++it)
        {
            ans.push_back(it->second);
        }
        return ans;
    }
};