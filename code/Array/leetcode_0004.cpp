// 方法一：合并两数组，再取中值 O(m + n)
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) 
{
    int len = nums1.size() + nums2.size();
    int ban = len / 2;
    bool flag = (len % 2 == 1) ? false : true;
    vector<int>::iterator it1 = nums1.begin();
    vector<int>::iterator it2 = nums2.begin();
    vector<int> v;

    while(it1 != nums1.end() && it2 != nums2.end())
    {
        if (*it1 <= *it2)
        {
            v.push_back(*it1);
            it1++;
        }
        else
        {
            v.push_back(*it2);
            it2++;
        }
    }

    while(it1 != nums1.end())
    {
        v.push_back(*it1);
        it1++;
    }

    while(it2 != nums2.end())
    {
        v.push_back(*it2);
        it2++;
    }

    if (flag)
        return (v[ban] + v[ban - 1]) / 2.f;
    else
        return v[ban] / 1.f;
}
 
 // 方法二：二分查找法 O(log(m + n))
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) 
{
    //方法二：二分法计算中位数
	if (nums1.size() > nums2.size())
		return findMedianSortedArrays(nums2, nums1);
    
    int m = nums1.size();
    int n = nums2.size();

    //分割线左边的所有元素需要满足的个数 m + (n - m + 1) / 2;  + 1是为了让左边的个数 >= 右边的个数
    int totalLeft = (m + n + 1) / 2;

    //在 nums1 的区间 [0, m] 里查找恰当的分割线
    //使得 nums1[i - 1] <= nums2[j] && nums2[j - 1] <= nums1[i]
    int left = 0;
    int right = m;

    while (left < right)
    {
        int i = left + (right - left + 1) / 2;  // + 1 是为了在 i 的左边画线
        int j = totalLeft - i;
        if (nums1[i - 1] > nums2[j])
        {
            //下一轮搜索的区间 [left, i - 1]
            right = i - 1;
        }
        else
        {
            //下一轮搜索的区间 [i, right]
            left = i;
        }
    }

    int i = left;
    int j = totalLeft - i;

    int nums1LeftMax = i == 0 ? INT_MIN : nums1[i - 1];  //INT_MIN
    int nums1RightMin = i == m ? INT_MAX : nums1[i];     //INT_MAX
    int nums2LeftMax = j == 0 ? INT_MIN : nums2[j - 1];  //2
    int nums2RightMin = j == n ? INT_MAX : nums2[j];     //INT_MAX

    if ((m + n) % 2 == 1)
    {
        return (nums1LeftMax > nums2LeftMax ? nums1LeftMax : nums2LeftMax) / 1.f;  //2.0
    }
    else
    {
        return ((nums1LeftMax > nums2LeftMax ? nums1LeftMax : nums2LeftMax) + (nums1RightMin < nums2RightMin ? nums1RightMin : nums2RightMin)) / 2.f;
    }
}