/*
// 方法一：集合
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> set1, set2;
        for (auto& e : nums1)
            set1.insert(e);
        for (auto& e : nums2)
            set2.insert(e);

        vector<int> intersec;
        for (auto& e : set1)
        {
            if (set2.count(e) != 0)
                intersec.push_back(e);
        }
        return intersec;
    }
};
*/

// 方法二：排序+ 双指针
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        vector<int> intersec;
        int i = 0, j = 0, sz1 = nums1.size(), sz2 = nums2.size();
        while (i < sz1 && j < sz2)
        {
            if (nums1[i] < nums2[j])
                ++i;
            else if (nums1[i] > nums2[j])
                ++j;
            else
            {
                if (intersec.size() == 0 || intersec.back() != nums1[i])
                    intersec.push_back(nums1[i]);
                ++i, ++j;
            }
        }

        return intersec;
    }
};