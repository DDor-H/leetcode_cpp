
// 双指针
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if (k <= 1) return 0;

        int ans = 0, left = 0, prod = 1;
        for (int right = 0; right < nums.size(); ++right)
        {
            prod *= nums[right];
            while (prod >= k)
                prod /= nums[left++];
            ans += right - left + 1;
        }
        return ans;
    }
};


/*
// 二分法
// 连续相乘 取对数后 转化为 指数相加
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if (k == 0) return 0;

        double logk = log(k);
        int lens = nums.size();
        vector<double> prefix(lens + 1, 0.0);
        for (int i = 0; i < lens; ++i)
            prefix[i + 1] = prefix[i] + log(nums[i]);
        int ans = 0;

        int lenpre = prefix.size();
        for (int i = 0; i < lenpre; ++i)
        {
            int lo = i + 1, hi = lenpre;
            while (lo < hi)
            {
                int mid = lo + (hi - lo) / 2;
                if (prefix[mid] - prefix[i] < + logk - 1e-9)
                    lo = mid + 1;
                else
                    hi = mid;
            }
            ans += lo - i - 1;
        }
        
        return ans;
    }
};
*/
