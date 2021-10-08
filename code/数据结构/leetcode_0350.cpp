
// 方法二：排序 + 双指针
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        if (m == 0 || n == 0)
            return vector<int>();
        
        vector<int> res;
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        int i = 0, j = 0;
        while (i < m && j < n)
        {
            if (nums1[i] == nums2[j])
            {
                res.push_back(nums1[i]);
                ++i, ++j;
            }
            else if (nums1[i] > nums2[j])
                ++j;
            else
                ++i;
        }

        return res;
    }
};

/*
// 方法一：hash表法
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        if (m == 0 || n == 0)
            return vector<int>();
        if (m > n)
            return intersect(nums2, nums1);
        
        vector<int> res;
        unordered_map<int, int> mm;
        for (auto& x : nums1)
            ++mm[x];
        
        for (int i = 0; i < n; ++i)
        {
            if (mm[nums2[i]] > 0)
            {
                res.push_back(nums2[i]);
                --mm[nums2[i]];
            }
        }
        return res;
    }
};
*/