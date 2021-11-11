// 双指针
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        int negtivate = -1;
        for (int i = 0; i < n; ++i)
        {
            if (nums[i] < 0)
                negtivate = i;
            else
                break;
        }
        vector<int> ans;
        for (int i = negtivate, j = negtivate + 1; i >= 0 || j < n;)
        {
            if (i < 0)
            {
                ans.push_back(nums[j] * nums[j]);
                ++j;
            }
            else if (j == n)
            {
                ans.push_back(nums[i] * nums[i]);
                --i;
            }
            else if (nums[i] * nums[i] < nums[j] * nums[j])
            {
                ans.push_back(nums[i] * nums[i]);
                --i;
            }
            else
            {
                ans.push_back(nums[j] * nums[j]);
                ++j;
            }
        }
        return ans;
    }
};


/*
// 双指针
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        int pos = n - 1;
        for (int i = 0, j = n - 1; i <= j;)
        {
            int i2 = nums[i] * nums[i];
            int j2 = nums[j] * nums[j];
            if (i2 > j2)
            {
                ans[pos] = i2;
                ++i;
            }
            else
            {
                ans[pos] = j2;
                --j;
            }
            --pos;
        }
        return ans;
    }
};

/*
// 直接sort
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        vector<int> ans;
        for (auto& e : nums)
            ans.push_back(e * e);
        sort(ans.begin(), ans.end());
        return ans;
    }
};
*/