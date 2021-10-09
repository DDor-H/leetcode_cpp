class Solution {
private:
    vector<int> vis;
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> perm;
        vis.resize(nums.size());
        sort(nums.begin(), nums.end());
        backtrace(nums, ans, 0, perm);
        return ans;
    }
    void backtrace(vector<int>& nums, vector<vector<int>>& ans, int idx, vector<int>& perm)
    {
        if (idx == nums.size())
        {
            ans.push_back(perm);
            return;
        }

        for (int i = 0; i < nums.size(); ++i)
        {
            // vis[i] : 表示这个位置的数已经被使用
            // i > 0 && nums[i] == nums[i - 1] ： 主要是防止两个连续的数相同
            /*for循环保证了从数组中从前往后一个一个取值，再用if判断条件。所以nums[i - 1]一定比nums[i]先被取值和判断。
            如果nums[i - 1]被取值了，那vis[i - 1]会被置1，只有当递归再回退到这一层时再将它置0。每递归一层都是在寻找数
            组对应于递归深度位置的值，每一层里用for循环来寻找。所以当vis[i - 1] == 1时，说明nums[i - 1]和nums[i]分别
            属于两层递归中，也就是我们要用这两个数分别放在数组的两个位置，这时不需要去重。但是当vis[i - 1] == 0时，
            说明nums[i - 1]和nums[i]属于同一层递归中（只是for循环进入下一层循环），也就是我们要用这两个数放在数组中的
            同一个位置上，这就是我们要去重的情况。*/
            if (vis[i] || (i > 0 && nums[i] == nums[i - 1] && !vis[i - 1]))
                continue;
            
            perm.push_back(nums[i]);
            vis[i] = 1;
            backtrace(nums, ans, idx + 1, perm);
            vis[i] = 0;
            perm.pop_back();
        }
    }
};