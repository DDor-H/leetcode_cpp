# **Array**

## 0001. Two Sum

### 题目：

给定一个整数数组 *nums* 和一个整数目标值 *target*，请你在该数组中找出 **和为目标值** *target*  的那 **两个** 整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。

你可以按任意顺序返回答案。

**示例1：**

```
输入：nums = [2,7,11,15], target = 9
输出：[0,1]
解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。
```

**示例2：**

```
输入：nums = [3,2,4], target = 6
输出：[1,2]
```

**示例2：**

```
输入：nums = [3,3], target = 6
输出：[0,1]
```

**提示：**

- `2 <= nums.length <= 104`
- `-109 <= nums[i] <= 109`
- `-109 <= target <= 109`
- **只会存在一个有效答案**



**解题思路：**

最优的做法时间复杂度是 O(n)

顺序扫描数组，对每一个元素，在 *map* 中找能组合给定值的另一半数字，如果找到了，直接返回 2 个数字的下标即可。如果找不到，就把这个数字存入 *map* 中，等待扫到“另一半”数字的时候，再取出来返回结果。



**方法一：**暴力解法  O(n^2)  O(1)

```c++
vector<int> twoSum(vector<int>& nums, int target) 
{
    int i, j;
    for(i = 0; i < nums.size() - 1; i++)
    {
        for(j = i + 1; j < nums.size(); j++)
        {
            if (nums[i] + nums[j] == target)
            {
                vector<int> v;
                v.push_back(i);
                v.push_back(j);
                return v;
            }
        }
    }
    return {i, j};
}
```

**方法二：**hash表法  时：O(n)  空：O(n)

```c++
vector<int> twoSum(vector<int>& nums, int target) 
{
	int i;
	int another = -1;
	map<int, int> m;
	m.insert(make_pair(nums[0], 0));
    for (i = 1; i < nums.size(); ++i)
    {
        another = target - nums[i];
        if (m.count(another) == 1 && m[another] != i)
            return {m[another], i};
        else
            m.insert(make_pair(nums[i], i));
    }
}
```



## 0004. 寻找两个正序数组的中位数

### 题目：

给定两个大小分别为 `m` 和 `n` 的正序（从小到大）数组 `nums1` 和 `nums2`。请你找出并返回这两个正序数组的 **中位数** 。

**示例1：**

```
输入：nums1 = [1,3], nums2 = [2]
输出：2.00000
解释：合并数组 = [1,2,3] ，中位数 2
```

**示例2：**

```
输入：nums1 = [1,2], nums2 = [3,4]
输出：2.50000
解释：合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5
```

**示例3**

```
输入：nums1 = [0,0], nums2 = [0,0]
输出：0.00000
```

**示例4**

```
输入：nums1 = [], nums2 = [1]
输出：1.00000
```

**示例5**

```
输入：nums1 = [2], nums2 = []
输出：2.00000
```

**提示：**

- `nums1.length == m`
- `nums2.length == n`
- `0 <= m <= 1000`
- `0 <= n <= 1000`
- `1 <= m + n <= 2000`
- `-106 <= nums1[i], nums2[i] <= 106`



**解题思路：**

- 给出两个有序数组，要求找出这两个数组合并以后的有序数组中的中位数。要求时间复杂度为 O(log (m+n))。

- 这一题最容易想到的办法是把两个数组合并，然后取出中位数。但是合并有序数组的操作是 `O(m+n)` 的，不符合题意。看到题目给的 `log` 的时间复杂度，**很容易联想到二分搜索**。

- 由于要找到最终合并以后数组的中位数，两个数组的总大小也知道，所以中间这个位置也是知道的。只需要二分搜索一个数组中切分的位置，另一个数组中切分的位置也能得到。**为了使得时间复杂度最小，所以二分搜索两个数组中长度较小的那个数组**。

- 关键的问题是如何切分数组 1 和数组 2 。其实就是如何切分数组 1 。先随便二分产生一个 `midA`，切分的线何时算满足了中位数的条件呢？即，线左边的数都小于右边的数，即，`nums1[midA-1] ≤ nums2[midB] && nums2[midB-1] ≤ nums1[midA]` 。如果这些条件都不满足，切分线就需要调整。

- 如果 `nums1[midA] < nums2[midB-1]`，说明 `midA` 这条线划分出来左边的数小了，切分线应该右移；

- 如果 `nums1[midA-1] > nums2[midB]`，说明 midA 这条线划分出来左边的数大了，切分线应该左移。经过多次调整以后，切分线总能找到满足条件的解。

- 假设现在找到了切分的两条线了，`数组 1` 在切分线两边的下标分别是 `midA - 1` 和 `midA`。`数组 2` 在切分线两边的下标分别是 `midB - 1` 和 `midB`。

- 最终合并成最终数组，如果数组长度是奇数，那么中位数就是 `max(nums1[midA-1], nums2[midB-1])`。

- 如果数组长度是偶数，那么中间位置的两个数依次是：`max(nums1[midA-1], nums2[midB-1])` 和 `min(nums1[midA], nums2[midB])`，那么中位数就是 `(max(nums1[midA-1], nums2[midB-1]) + min(nums1[midA], nums2[midB])) / 2`。图示见下图：

  ![leetcode_4](F:\C++\刷题\Img\leetcode_4.png)



**方法一：**合并两数组，再取中值 O(m + n)

```c++
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
```

**方法二：**二分查找法 O(log(m + n))

```c++
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
```





## 0011. 盛最多水的容器

### 题目：

给你 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0) 。找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。

![leetcode_11](F:\C++\刷题\Img\leetcode_11.jpg)

**示例1：**

```
输入：[1,8,6,2,5,4,8,3,7]
输出：49 
解释：图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。
```

**示例2：**

```
输入：height = [1,1]
输出：1
```

**示例3：**

```c
输入：height = [4,3,2,1,4]
输出：16
```

**示例4：**

```
输入：height = [1,2,1]
输出：2
```

**提示：**

- `n = height.length`
- `2 <= n <= 3 * 104`
- `0 <= height[i] <= 3 * 104`



**解题思路：**

- 这一题也是对撞指针的思路。首尾分别 2 个指针，每次移动以后都分别判断长宽的乘积是否最大。



**方法一：**暴力解法 O(n^2)

**方法二：**双指针法 时：O(n)  空：O(1)

```c++
class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;

        int maxArea = 0;
        int tmpArea = 0;

        while (left < right)
        {
            tmpArea = (right - left) * (height[left] < height[right] ? height[left] : height[right]);
            if (maxArea < tmpArea)
                maxArea = tmpArea;
            if (height[left] < height[right])
                left++;
            else
                right--;
        }
        return maxArea;
    }
};
```





## 0015. 三数之和

### 题目：

给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？请你找出所有和为 0 且不重复的三元组。

**示例1：**

```
输入：nums = [-1,0,1,2,-1,-4]
输出：[[-1,-1,2],[-1,0,1]]
```

**示例2：**

```
输入：nums = []
输出：[]
```

**示例3：**

```
输入：nums = [0]
输出：[]
```

**提示：**

- `0 <= nums.length <= 3000`
- `-105 <= nums[i] <= 105`



**解题思路：**

- 直接想到的方法就是三层循环暴力解法，时间复杂度为O(n^3)。类似于`0001`题，使用map，可以起到优化的作用。
- 用 map 提前计算好任意 2 个数字之和，保存起来，可以将时间复杂度降到 O(n^2)。这一题比较麻烦的一点在于，最后输出解的时候，要求输出不重复的解。数组中同一个数字可能出现多次，同一个数字也可能使用多次，但是最后输出解的时候，不能重复。例如 [-1，-1，2] 和 [2, -1, -1]、[-1, 2, -1] 这 3 个解是重复的，即使 -1 可能出现 100 次，每次使用的 -1 的数组下标都是不同的。
- 这里就需要去重和排序了。map 记录每个数字出现的次数，然后对 map 的 key 数组进行排序，最后在这个排序以后的数组里面扫，找到另外 2 个数字能和自己组成 0 的组合。



**方法一：**暴力解法 O(n^3)  **超时**

```c++
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int len = nums.size();
        vector<vector<int>> v;

        for (int i = 0; i < len - 2; ++i)
        {
            for (int j = i + 1; j < len - 1; ++j)
            {
                for (int k = j + 1; k < len; ++k)
                {
                    if (nums[i] + nums[j] + nums[k] == 0)
                    {
                        vector<int> tmpV = {nums[i], nums[j], nums[k]};
                        sort(tmpV.begin(), tmpV.end());
                        if (count(v.begin(), v.end(), tmpV) == 0)
                            v.push_back(tmpV);
                    }
                }
            }
        }
        reverse(v.begin(),v.end());
        return v;
    }
};
```



这种方法的时间复杂度仍然为 O(N^3)，毕竟我们还是没有跳出三重循环的大框架。然而它是很容易继续优化的，可以发现，如果我们固定了前两重循环枚举到的元素 a 和 b，那么只有唯一的 c 满足 a+b+c=0。当第二重循环往后枚举一个元素 b' 时，由于 b' > b，那么满足 a+b'+c'=0 的 c' 一定有 c' < c，即 c' 在数组中一定出现在 c 的左侧。也就是说，我们可以从小到大枚举 b，**同时**从大到小枚举 c，**即第二重循环和第三重循环实际上是并列的关系**。

保持第二重循环不变，而将**第三重循环变成一个从数组最右端开始向左移动的指针**。

**方法二：**hash表法  O(n^2)

```c++
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        // 枚举 a
        for (int first = 0; first < n; ++first) {
            // 需要和上一次枚举的数不相同
            if (first > 0 && nums[first] == nums[first - 1]) {
                continue;
            }
            // c 对应的指针初始指向数组的最右端
            int third = n - 1;
            int target = -nums[first];
            // 枚举 b
            for (int second = first + 1; second < n; ++second) {
                // 需要和上一次枚举的数不相同
                if (second > first + 1 && nums[second] == nums[second - 1]) {
                    continue;
                }
                // 需要保证 b 的指针在 c 的指针的左侧
                while (second < third && nums[second] + nums[third] > target) {
                    --third;
                }
                // 如果指针重合，随着 b 后续的增加
                // 就不会有满足 a+b+c=0 并且 b<c 的 c 了，可以退出循环
                if (second == third) {
                    break;
                }
                if (nums[second] + nums[third] == target) {
                    ans.push_back({nums[first], nums[second], nums[third]});
                }
            }
        }
        return ans;
    }
};
```





## 0016. 最接近的三数之和

### 题目：

给定一个包括 n 个整数的数组 nums 和 一个目标值 target。找出 nums 中的三个整数，使得它们的和与 target 最接近。返回这三个数的和。假定每组输入只存在唯一答案。

**示例：**

```
输入：nums = [-1,2,1,-4], target = 1
输出：2
解释：与 target 最接近的和是 2 (-1 + 2 + 1 = 2) 。
```

**提示：**

- `3 <= nums.length <= 10^3`
- `-10^3 <= nums[i] <= 10^3`
- `-10^4 <= target <= 10^4`



**解题思路：**

- 这一题看似和第 15 题和第 18 题很像，都是求 3 或者 4 个数之和的问题，但是这一题的做法和 15，18 题完全不同。
- 这一题的解法是用**两个指针夹逼的方法**。先对数组进行排序，i 从头开始往后面扫。这里同样需要注意数组中存在多个重复数字的问题。具体处理方法很多，可以用 map 计数去重。
- i 在循环的时候和前一个数进行比较，如果相等，i 继续往后移，直到移到下一个和前一个数字不同的位置。
- j，k 两个指针开始一前一后夹逼。j 为 i 的下一个数字，k 为数组最后一个数字，由于经过排序，所以 k 的数字最大。j 往后移动，k 往前移动，逐渐夹逼出最接近 target 的值。



**方法一：**暴力解法 O(n^3)

**方法二：**前后指针法 O(n^2)

```c++
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int res = 0;
        int absDiff = INT_MAX;
        int Sum = 0;
        sort(nums.begin(), nums.end());
        int len = nums.size();

        for (int i = 0; i < len - 2; ++i)
        {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;
            for (int j = i + 1, k = len - 1; j < k;)
            {
                if (j > i + 1 && nums[j] == nums[j - 1])
                {
                    ++j;
                    continue;
                }

                Sum = nums[i] + nums[j] + nums[k];
                if (Sum == target)
                    return Sum;
                    
                res = abs(Sum - target) < absDiff ? Sum : res;
                absDiff = abs(Sum - target) < absDiff ? abs(Sum - target) : absDiff;

                if (Sum - target > 0)
                    --k;
                else
                    ++j;
            }
        }
        return res;
    }
};
```





## 0018.  四数之和

### 题目：

给你一个由 n 个整数组成的数组 nums ，和一个目标值 target 。请你找出并返回满足下述全部条件且不重复的四元组 [nums[a], nums[b], nums[c], nums[d]] ：

- 0 <= a, b, c, d < n
- a、b、c 和 d 互不相同
- nums[a] + nums[b] + nums[c] + nums[d] == target

可以按 **任意顺序** 返回答案 。

**示例1：**

```
输入：nums = [1,0,-1,0,-2,2], target = 0
输出：[[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
```

**示例2：**

```
输入：nums = [2,2,2,2,2], target = 8
输出：[[2,2,2,2]]
```

**提示：**

- `1 <= nums.length <= 200`
- `-109 <= nums[i] <= 109`
- `-109 <= target <= 109`



**解题思路：**

同15题的三数之和，双指针法，不过还是要主要 diff 和 target 的关系，以及排序



方法一：暴力解法 O(n^4)

方法二：前后指针法 O(n^3)

```c++
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        int len = nums.size();
        if (len < 4)
            return res;
        sort(nums.begin(), nums.end());

        for (int i = 0; i < len - 3; ++i)
        {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;
            for (int j = i + 1; j < len - 2; ++j)
            {
                if (j > i + 1 && nums[j] == nums[j - 1])
                    continue;
                int m = len - 1;
                int diff = target - (nums[i] + nums[j]);
                for (int k = j + 1; k < len - 1; ++k)
                {
                    if (k > j + 1 && nums[k] == nums[k - 1])
                        continue;
                    while (k < m && nums[k] + nums[m] > diff)
                        --m;

                    if (k == m)
                        break;
                    if (nums[i] + nums[j] + nums[k] + nums[m] == target)
                        res.push_back({nums[i], nums[j], nums[k], nums[m]});
                }
            }
        }
        return res;
    }
};
```





## 0026. 删除有序数组中的重复项

### 题目：

给一个有序数组 nums ，请 **原地** 删除重复出现的元素，使每个元素 只出现一次 ，返回删除后数组的新长度。

不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。

**说明:**

为什么返回数值是整数，但输出的答案是数组呢?

请注意，输入数组是以**「引用」**方式传递的，这意味着在函数里修改输入数组对于调用者是可见的。

可以想象内部操作如下:

```
// nums 是以“引用”方式传递的。也就是说，不对实参做任何拷贝
int len = removeDuplicates(nums);

// 在函数里修改输入数组对于调用者是可见的。
// 根据你的函数返回的长度, 它会打印出数组中 该长度范围内 的所有元素。
for (int i = 0; i < len; i++) {
    print(nums[i]);
}
```

**示例1：**

```
输入：nums = [1,1,2]
输出：2, nums = [1,2]
解释：函数应该返回新的长度 2 ，并且原数组 nums 的前两个元素被修改为 1, 2 。不需要考虑数组中超出新长度后面的元素。
```

**示例2：**

```
输入：nums = [0,0,1,1,1,2,2,3,3,4]
输出：5, nums = [0,1,2,3,4]
解释：函数应该返回新的长度 5 ， 并且原数组 nums 的前五个元素被修改为 0, 1, 2, 3, 4 。不需要考虑数组中超出新长度后面的元素。
```

**说明：**

- `0 <= nums.length <= 3 * 104`
- `-104 <= nums[i] <= 104`
- `nums` 已按升序排列



**解题思路：**

思路一：逆向循环，移除重复元素；

思路二：正向循环，将重复的数放置最后，不真正删除；



**方法一：**时：O(n)  空：O(1)

```c++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() <= 1)
            return nums.size();
        auto end = nums.end();
        --end;
        while (end > nums.begin())
        {
            --end;
            if (*end == *(end + 1))
                nums.erase(end + 1, end + 2);
        }
        return nums.size();
    }
};
```

**方法二：**时：O(n)  空：O(1)

```c++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int len = nums.size();
        if (len <= 1)
            return len;
        int i = 0;
        int j = 0;
        while (j < len)
        {
            if (nums[i] != nums[j])
            {
                ++i;
                if (i != j)
                    nums[i] = nums[j];
            }
            ++j;
        }
        return i + 1;
    }
};
```





## 0027. 移除元素

### 题目：

给一个数组 nums 和一个值 val，需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。

不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组。

元素的顺序可以改变。不需要考虑数组中超出新长度后面的元素。

**示例1：**

```
输入：nums = [3,2,2,3], val = 3
输出：2, nums = [2,2]
解释：函数应该返回新的长度 2, 并且 nums 中的前两个元素均为 2。你不需要考虑数组中超出新长度后面的元素。例如，函数返回的新长度为 2 ，而 nums = [2,2,3,3] 或 nums = [2,2,0,0]，也会被视作正确答案。
```

**示例2：**

```
输入：nums = [0,1,2,2,3,0,4,2], val = 2
输出：5, nums = [0,1,4,0,3]
解释：函数应该返回新的长度 5, 并且 nums 中的前五个元素为 0, 1, 3, 0, 4。注意这五个元素可为任意顺序。你不需要考虑数组中超出新长度后面的元素。
```

**提示：**

- `0 <= nums.length <= 100`
- `0 <= nums[i] <= 50`
- `0 <= val <= 100`



**解题思路：**

同 26 题

思路一：逆向循环，移除重复元素；

思路二：正向循环，将重复的数放置最后，不真正删除；



**方法一：**时：O(n)  空：O(1)

```c++
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int len = nums.size();
        if (len == 0)
            return len;
        auto end = nums.end();
        --end;
        while (end >= nums.begin())
        {
            --end;
            if (*(end + 1) == val)
                nums.erase(end + 1, end + 2);
        }
        return nums.size();
    }
};
```

**方法二：**时：O(n)  空：O(1)

```c++
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if (nums.size() == 0)
            return 0;
        int i = 0;
        int j = 0;
        while (j < nums.size())
        {
            if (nums[j] != val)
            {
                if (i != j)
                {
                    nums[i] = nums[j];
                    nums[j] = val;
                }
                ++i;
            }
            ++j;
        }
        return i;
    }
};
```





## 0031. 下一个排列

### 题目：

实现获取 下一个排列 的函数，算法需要将给定数字序列重新排列成字典序中下一个更大的排列（即，组合出下一个更大的整数）。

如果不存在下一个更大的排列，则将数字重新排列成最小的排列（即升序排列）。

必须 **原地** 修改，只允许使用额外常数空间。



**示例1：**

```
输入：nums = [1,2,3]
输出：[1,3,2]
```

**示例2：**

```
输入：nums = [3,2,1]
输出：[1,2,3]
```

**示例3：**

```
输入：nums = [1,1,5]
输出：[1,5,1]
```

**示例4：**

```
输入：nums = [1]
输出：[1]
```

**提示：**

- `1 <= nums.length <= 100`
- `0 <= nums[i] <= 100`

**解题思路：**

- 题目有 3 个问题需要解决。如何找到下一个排列。不存在下一个排列的时候如何生成最小的排列。如何原地修改。先解决第一个问题，如何找到下一个排列。下一个排列是找到一个大于当前排序的字典序，且变大的幅度最小。那么只能将较小的数与较大数做一次原地交换。**并且较小数的下标要尽量靠右，较大数也要尽可能小。**原地交换以后，还需要将较大数右边的数按照升序重新排列。这样交换以后，才能生成下一个排列。以排列 [8,9,6,10,7,2] 为例：能找到的符合条件的一对「较小数」与「较大数」的组合为 6 与 7，满足「较小数」尽量靠右，而「较大数」尽可能小。当完成交换后排列变为 [8,9,7,10,6,2]，此时我们可以重排「较小数」右边的序列，序列变为 [8,9,7,2,6,10]。
- 第一步：在 `nums[i]` 中找到 `i` 使得 `nums[i] < nums[i+1]`，此时较小数为 `nums[i]`，并且 `[i+1, n)` 一定为下降区间。第二步：如果找到了这样的 `i` ，则在下降区间 `[i+1, n)` 中**从后往前找到**第一个 `j` ，使得 `nums[i] < nums[j]` ，此时较大数为 `nums[j]`。第三步，交换 `nums[i]` 和 `nums[j]`，此时区间 `[i+1, n)` 一定为降序区间。最后原地交换 `[i+1, n)` 区间内的元素，使其变为升序，无需对该区间进行排序。
- 如果第一步找不到符合条件的下标 `i`，说明当前序列已经是一个最大的排列。那么应该直接执行第三步，生成最小的排列。



**方法：**

```c++
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        //  [8,9,7,10,6,2]
        int len = nums.size();
        if (len == 1)
            return;
        int lpos = 0;
        int bpos = len - 1;
        for (int i = len - 2, j = len - 1; j > 0; --i, --j)
        {
            // 从后向前找第一个 nums[i] < nums[j]
            // i 就是 lpos
            if (nums[i] < nums[j])
            {
                lpos = i;
                break;
            }
        }
        for (int j = bpos; j > lpos; --j)
        {
            // 从后向前找第一个 nums[lpos] < nums[j]
            if (nums[lpos] < nums[j])
            {
                bpos = j;
                break;
            }
        }
        int tmp = nums[lpos];
        nums[lpos] = nums[bpos];
        nums[bpos] = tmp;

        sort(nums.begin() + lpos + 1, nums.end());
    }
};
```





## 0033. 搜索旋转排序数组

### 题目：

整数数组 nums 按升序排列，数组中的值 互不相同 。

在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 旋转，使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标 从 0 开始 计数）。例如， [0,1,2,4,5,6,7] 在下标 3 处经旋转后可能变为 [4,5,6,7,0,1,2] 。

给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则返回 -1 。

**示例 1：**

```
输入：nums = [4,5,6,7,0,1,2], target = 0
输出：4
```

**示例 2：**

```
输入：nums = [4,5,6,7,0,1,2], target = 3
输出：-1
```

**示例 3：**

```
输入：nums = [1], target = 0
输出：-1
```

**提示：**

- 1 <= nums.length <= 5000
- -10^4 <= nums[i] <= 10^4
- nums 中的每个值都 独一无二
- 题目数据保证 nums 在预先未知的某个下标上进行了旋转
- -10^4 <= target <= 10^4



**解题思路：**

思路一：循环判断；

思路二：二分查找；

- 由于数组基本有序，虽然中间有一个“断开点”，还是可以使用二分搜索的算法来实现。现在数组前面一段是数值比较大的数，后面一段是数值偏小的数。
- 如果 mid 落在了前一段数值比较大的区间内了，那么一定有 `nums[mid] > nums[low]`，如果是落在后面一段数值比较小的区间内，`nums[mid] ≤ nums[low]` 。
- 如果 mid 落在了后一段数值比较小的区间内了，那么一定有 `nums[mid] < nums[high]`，如果是落在前面一段数值比较大的区间内，`nums[mid] ≤ nums[high]` 。
- 还有 `nums[low] == nums[mid]` 和 `nums[high] == nums[mid]` 的情况，单独处理即可。最后找到则输出 mid，没有找到则输出 -1 。



**方法一：**循环判断，O(n)

```c++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        for (int i =0 ; i < nums.size(); ++i)
        {
            if (nums[i] == target)
                return i;
        }
        return -1;
    }
};
```

**方法二：**二分法，O(logn)

```c++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        int mid = -1;
        while (left <= right)
        {
            mid = left + (right - left) / 2.f;
            if (nums[mid] == target)
                return mid;
            else if (nums[mid] > nums[left])  // 左半部分有序
            {
                // 是否在有序部分中
                if (nums[left] <= target && nums[mid] > target)
                    right = mid - 1;
                else
                    left = mid + 1;
            }
            else if (nums[mid] < nums[right])  // 右半部分有序
            {
                // 是否在有序部分中
                if (nums[mid] < target && nums[right] >= target)
                    left = mid + 1;
                else
                    right = mid - 1;
            }
            else  // mid == left or mid == right or left == right == mid
            {
                if (left == mid)
                    ++left;
                else if (right == mid)
                    --right;
            }
        }
        return -1;
    }
};
```





## 0034. 在排序数组中查找元素的第一个和最后一个位置

### 题目：

给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。

如果数组中不存在目标值 target，返回 [-1, -1]。

**进阶：**时间复杂度为 O(log n) 

**示例 1：**

```
输入：nums = [5,7,7,8,8,10], target = 8
输出：[3,4]
```

**示例 2：**

```
输入：nums = [5,7,7,8,8,10], target = 6
输出：[-1,-1]
```

**示例 3：**

```
输入：nums = [], target = 0
输出：[-1,-1]
```

**提示：**

- 0 <= nums.length <= 105
- -109 <= nums[i] <= 109
- nums 是一个非递减数组
- -109 <= target <= 109



**解题思路：**

O(logn) -> 二分法

- 这一题是经典的二分搜索变种题。二分搜索有 4 大基础变种题：

  1. 查找第一个值等于给定值的元素
  2. 查找最后一个值等于给定值的元素
  3. 查找第一个大于等于给定值的元素
  4. 查找最后一个小于等于给定值的元素

  这一题的解题思路可以分别利用变种 1 和变种 2 的解法就可以做出此题。或者用一次变种 1 的方法，然后循环往后找到最后一个与给定值相等的元素。不过后者这种方法可能会使时间复杂度下降到 O(n)，因为有可能数组中 n 个元素都和给定元素相同。(4 大基础变种的实现见代码)



**方法：**

```c++
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        return vector<int>({searchFirstEqualElement(nums, target), searchLastEqualElement(nums, target)});
    }

    // 变种1：查找第一个为目标元素的位置
    int searchFirstEqualElement(vector<int>& nums, int target)
    {
        int left = 0, right = nums.size() - 1;
        int mid = -1;
        while (left <= right)
        {
            mid = left + ((right - left) >> 1);
            if (nums[mid] > target)
                right = mid - 1;
            else if (nums[mid] < target)
                left = mid + 1;
            else 
            {
                if (mid == 0 || nums[mid - 1] != target)
                    return mid;
                right = mid - 1;
            }
        }
        return -1;
    }

    // 变种2：查找最后一个为目标元素的位置
    int searchLastEqualElement(vector<int>& nums, int target)
    {
        int left = 0, right = nums.size() - 1;
        int mid = -1;
        while (left <= right)
        {
            mid = left + ((right - left) >> 1);
            if (nums[mid] > target)
                right = mid - 1;
            else if (nums[mid] < target)
                left = mid + 1;
            else 
            {
                if (mid == nums.size() - 1 || nums[mid + 1] != target)
                    return mid;
                left = mid + 1;
            }
        }
        return -1;
    }

    // 变种3：查找第一个大于等于给定值的元素
    int searchFirstGreaterElement(vector<int>& nums, int target)
    {
        int left = 0, right = nums.size() - 1;
        int mid = -1;
        while (left <= right)
        {
            mid = left + ((right - left) >> 1);
            if (nums[mid] >= target)
            {
                if (mid == 0 || nums[mid - 1] < target)
                    return mid;
                right = mid - 1;
            }
            else
                left = mid + 1;
        }
        return -1;
    }

    // 变种4：查找最后一个小于等于 target 的元素
    int searchLastLessElement(vector<int>& nums, int target)
    {
        int left = 0, right = nums.size() - 1;
        int mid = -1;
        while (left <= right)
        {
            mid = left + ((right - left) >> 1);
            if (nums[mid] <= target)
            {
                if (mid == nums.size() - 1 || nums[mid + 1] > target)
                    return mid;
                left = mid + 1;
            }
            else
                right = mid - 1;
        }
        return -1;
    }
};
```





## 0035. 搜索插入位置

### 题目：

给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

请必须使用时间复杂度为 O(log n) 的算法。

**示例 1:**

```
输入: nums = [1,3,5,6], target = 5
输出: 2
```

**示例 2:**

```
输入: nums = [1,3,5,6], target = 2
输出: 1
```

**示例 3:**

```
输入: nums = [1,3,5,6], target = 7
输出: 4
```

**示例 4:**

```
输入: nums = [1,3,5,6], target = 0
输出: 0
```

**示例 5:**

```
输入: nums = [1], target = 0
输出: 0
```

**提示:**

- 1 <= nums.length <= 104
- -104 <= nums[i] <= 104
- nums 为无重复元素的升序排列数组
- -104 <= target <= 104



**解题思路：**

找到第一个大于等于target的元素，类似于35题



**方法：**

```c++
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        return serchFirstGreaterInsert(nums, target);
    }

    int serchFirstGreaterInsert(vector<int>& nums, int target)
    {
        int left = 0, right = nums.size() - 1;
        int mid = -1;
        while (left <= right)
        {
            mid = left + ((right - left) >> 1);
            if (nums[mid] >= target)
            {
                if (mid == 0 || nums[mid - 1] < target)
                    return mid;
                right = mid - 1;
            }
            else
                left = mid + 1;
        }
        return nums.size();
    }
};
```





## 0036. 有效的数独

### 题目：

请你判断一个 `9x9` 的数独是否有效。只需要 **根据以下规则** ，验证已经填入的数字是否有效即可。

1. 数字 `1-9` 在每一行只能出现一次。
2. 数字 `1-9` 在每一列只能出现一次。
3. 数字 `1-9` 在每一个以粗实线分隔的 `3x3` 宫内只能出现一次。（请参考示例图）

数独部分空格内已填入了数字，空白格用 `'.'` 表示。

**注意：**

- 一个有效的数独（部分已被填充）不一定是可解的。
- 只需要根据以上规则，验证已经填入的数字是否有效即可。

**示例 1：**

![leetcode_36](F:\C++\刷题\Img\leetcode_36.png)

```
输入：board = 
[["5","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
输出：true
```

**示例 2：**

```
输入：board = 
[["8","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
输出：false
解释：除了第一行的第一个数字从 5 改为 8 以外，空格内其他数字均与 示例1 相同。 但由于位于左上角的 3x3 宫内有两个 8 存在, 因此这个数独是无效的。
```

**提示：**

- `board.length == 9`
- `board[i].length == 9`
- `board[i][j]` 是一位数字或者 `'.'`



**解题思路：**

有效的数独满足以下三个条件：

- 同一个数字在每一行只能出现一次；


- 同一个数字在每一列只能出现一次；


- 同一个数字在每一个小九宫格只能出现一次。


可以使用哈希表记录每一行、每一列和每一个小九宫格中，每个数字出现的次数。只需要遍历数独一次，在遍历的过程中更新哈希表中的计数，并判断是否满足有效的数独的条件即可。

对于数独的第 $i$ 行第 $j$ 列的单元格，其中 $0 \le i, j < 9$，该单元格所在的行下标和列下标分别为 $i$ 和 $j$，该单元格所在的小九宫格的行数和列数分别为 $\Big\lfloor \dfrac{i}{3} \Big\rfloor$ 和 $\Big\lfloor \dfrac{j}{3} \Big\rfloor$，其中 $0 \le \Big\lfloor \dfrac{i}{3} \Big\rfloor, \Big\lfloor \dfrac{j}{3} \Big\rfloor < 3$。

由于数独中的数字范围是 $1$ 到 $9$，因此可以使用数组代替哈希表进行计数。

具体做法是，创建二维数组 $\textit{rows}$ 和 $\textit{columns}$ 分别记录数独的每一行和每一列中的每个数字的出现次数，创建三维数组 $\textit{subboxes}$ 记录数独的每一个小九宫格中的每个数字的出现次数，其中 $\textit{rows}[i][\textit{index}]$、$\textit{columns}[j][\textit{index}]$ 和 $\textit{subboxes}\Big[\Big\lfloor \dfrac{i}{3} \Big\rfloor\Big]\Big[\Big\lfloor \dfrac{j}{3} \Big\rfloor\Big]\Big[\textit{index}\Big]$ 分别表示数独的第 $i$ 行第 $j$ 列的单元格所在的行、列和小九宫格中，数字 $\textit{index} + 1$ 出现的次数，其中 $0 \le \textit{index} < 9$，对应的数字 $\textit{index} + 1$ 满足 $1 \le \textit{index} + 1 \le 9$。

如果 $\textit{board}[i][j]$ 填入了数字 $n$，则将 $\textit{rows}[i][n - 1]$、$\textit{columns}[j][n - 1]$ 和 $\textit{subboxes}\Big[\Big\lfloor \dfrac{i}{3} \Big\rfloor\Big]\Big[\Big\lfloor \dfrac{j}{3} \Big\rfloor\Big]\Big[n - 1\Big]$ 各加 $1$。如果更新后的计数大于 $1$，则不符合有效的数独的条件，返回 $\text{false}$。

如果遍历结束之后没有出现计数大于 $1$ 的情况，则符合有效的数独的条件，返回 $\text{true}$。



**方法：**

```c++
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<vector<int>> row(9, vector<int>(9, 0));
        vector<vector<int>> col(9, vector<int>(9, 0));
        vector<vector<vector<int>>> subGrid(3, vector<vector<int>>(3, vector<int>(9, 0)));

        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                if (board[i][j] != '.')
                {
                    int index = board[i][j] - '0' - 1;
                    row[i][index]++;
                    col[j][index]++;
                    subGrid[i / 3][j / 3][index]++;
                    if (row[i][index] > 1 || col[j][index] > 1 || subGrid[i / 3][j / 3][index] > 1)
                        return false;
                }
            }
        }
        return true;
    }
};
```





## 0037. 解数独

### 题目：

编写一个程序，通过填充空格来解决数独问题。

数独的解法需 **遵循如下规则**：

1. 数字 `1-9` 在每一行只能出现一次。
2. 数字 `1-9` 在每一列只能出现一次。
3. 数字 `1-9` 在每一个以粗实线分隔的 `3x3` 宫内只能出现一次。（请参考示例图）

数独部分空格内已填入了数字，空白格用 `'.'` 表示。

**示例：**

![leetcode_37_1](F:\C++\刷题\Img\leetcode_37_1.png)

```
输入：board = [["5","3",".",".","7",".",".",".","."],		["6",".",".","1","9","5",".",".","."],
[".","9","8",".",".",".",".","6","."],
["8",".",".",".","6",".",".",".","3"],
["4",".",".","8",".","3",".",".","1"],
["7",".",".",".","2",".",".",".","6"],
[".","6",".",".",".",".","2","8","."],
[".",".",".","4","1","9",".",".","5"],
[".",".",".",".","8",".",".","7","9"]]
输出：[["5","3","4","6","7","8","9","1","2"],
["6","7","2","1","9","5","3","4","8"],
["1","9","8","3","4","2","5","6","7"],
["8","5","9","7","6","1","4","2","3"],
["4","2","6","8","5","3","7","9","1"],
["7","1","3","9","2","4","8","5","6"],
["9","6","1","5","3","7","2","8","4"],
["2","8","7","4","1","9","6","3","5"],
["3","4","5","2","8","6","1","7","9"]]
解释：输入的数独如上图所示，唯一有效的解决方案如下所示：
```

![leetcode_37_2](F:\C++\刷题\Img\leetcode_37_2.png)

**提示：**

- `board.length == 9`
- `board[i].length == 9`
- `board[i][j] 是一位数字或者 '.'`
- 题目数据 **保证** 输入数独仅有一个解



**解题思路：**

我们首先对整个数独数组进行遍历，当我们遍历到第 $i$ 行第 $j$ 列的位置：

如果该位置是一个空白格，那么我们将其加入一个用来存储空白格位置的列表中，方便后续的递归操作；

如果该位置是一个数字 $x$，那么我们需要将 $\textit{line}[i][x-1]$，$\textit{column}[j][x-1]$ 以及 $\textit{block}[\lfloor i/3 \rfloor][\lfloor j/3 \rfloor][x-1]$ 均置为 $\text{True}$。

当我们结束了遍历过程之后，就可以开始递归枚举。当递归到第 $i$ 行第 $j$ 列的位置时，我们枚举填入的数字 $x$。根据题目的要求，数字 $x$ 不能和当前行、列、九宫格中已经填入的数字相同，因此 $\textit{line}[i][x-1]$，$\textit{column}[j][x-1]$ 以及 $\textit{block}[\lfloor i/3 \rfloor][\lfloor j/3 \rfloor][x-1]$ 必须均为 $\text{False}$。

当我们填入了数字 $x$ 之后，我们要将上述的三个值都置为 $\text{True}$，并且继续对下一个空白格位置进行递归。在回溯到当前递归层时，我们还要将上述的三个值重新置为 $\text{False}$。

改进一：是用位运算，减少空间复杂度

改进二：若某一行、某一列、某一小块只剩一个空位，则不需要回溯，直接填值；



**方法一：**

```c++
class Solution {
private:
    vector<vector<bool>> row;
    vector<vector<bool>> col;
    vector<vector<vector<bool>>> subGrid;
    vector<pair<int, int>> space;
    bool valid;


public:
    void solveSudoku(vector<vector<char>>& board) {
        row = vector<vector<bool>>(9, vector<bool>(9, false));
        col = vector<vector<bool>>(9, vector<bool>(9, false));
        subGrid = vector<vector<vector<bool>>>(3, vector<vector<bool>>(3, vector<bool>(9, false)));
        valid = false;

        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                if (board[i][j] == '.')
                    space.push_back(make_pair(i, j));
                else
                {
                    int index = board[i][j] - '0' - 1;
                    row[i][index] = col[j][index] = subGrid[i / 3][j / 3][index] = true;
                }
            }
        }
        dfs(board, 0);
    }

    void dfs(vector<vector<char>>& board, int pos)
    {
        if (pos == space.size())
        {
            valid = true;
            return;
        }

        auto [i, j] = space[pos];
        for (int digit = 0; digit < 9 && !valid; ++digit)
        {
            if (!row[i][digit] && !col[j][digit] && !subGrid[i / 3][j / 3][digit])
            {
                row[i][digit] = col[j][digit] = subGrid[i / 3][j / 3][digit] = true;
                board[i][j] = digit + '0' + 1;
                dfs(board, pos + 1);
                row[i][digit] = col[j][digit] = subGrid[i / 3][j / 3][digit] = false;
            }
        }
    }
};
```

**方法二：**

```c++
class Solution {
private:
    vector<int> row;
    vector<int> col;
    vector<vector<int>> subGrid;
    vector<pair<int, int>> space;
    bool valid;


public:
    void solveSudoku(vector<vector<char>>& board) {
        row = vector<int>(9, 0);
        col = vector<int>(9, 0);
        subGrid = vector<vector<int>>(3, vector<int>(3, 0));
        valid = false;

        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                if (board[i][j] == '.')
                    space.push_back(make_pair(i, j));
                else
                {
                    int index = board[i][j] - '0' - 1;
                    flip(i, j, index);
                }
            }
        }
        dfs(board, 0);
    }

    void dfs(vector<vector<char>>& board, int pos)
    {
        if (pos == space.size())
        {
            valid = true;
            return;
        }

        auto [i, j] = space[pos];
        int mask = ~(row[i] | col[j] | subGrid[i / 3][j / 3]) & 0x1ff;
        for (; mask && !valid; mask &= (mask - 1))
        {
            int digitMask = mask & (-mask);
            int digit = __builtin_ctz(digitMask);
            flip(i, j, digit);
            board[i][j] = digit + '0' + 1;
            dfs(board, pos + 1);
            flip(i, j, digit);
        }
    }

    void flip(int i, int j, int digit)
    {
        row[i] ^= (1 << digit);
        col[j] ^= (1 << digit);
        subGrid[i / 3][j / 3] ^= (1 << digit);
    }
};
```

**方法三：**

```c++
class Solution {
private:
    vector<int> row;
    vector<int> col;
    vector<vector<int>> subGrid;
    vector<pair<int, int>> space;
    bool valid;


public:
    void solveSudoku(vector<vector<char>>& board) {
        row = vector<int>(9, 0);
        col = vector<int>(9, 0);
        subGrid = vector<vector<int>>(3, vector<int>(3, 0));
        valid = false;

        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                if (board[i][j] != '.')
                {
                    int index = board[i][j] - '0' - 1;
                    flip(i, j, index);
                }
            }
        }

        while(true)
        {
            bool modified = false;
            for (int i = 0; i < 9; ++i)
            {
                for (int j = 0; j < 9; ++j)
                {
                    if (board[i][j] == '.')
                    {
                        int mask = ~(row[i] | col[j] | subGrid[i / 3][j / 3]) & 0x1ff;
                        if (!(mask & (mask - 1)))
                        {
                            int digitMask = mask & (-mask);
                            int digit = __builtin_ctz(digitMask);
                            flip(i, j, digit);
                            board[i][j] = digit + '0' + 1;
                            modified = true;
                        }
                    }
                }
            }
            if (!modified)
                break;
        }

        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                if (board[i][j] == '.')
                    space.push_back(make_pair(i, j));
            }
        }
        dfs(board, 0);
    }

    void dfs(vector<vector<char>>& board, int pos)
    {
        if (pos == space.size())
        {
            valid = true;
            return;
        }

        auto [i, j] = space[pos];
        int mask = ~(row[i] | col[j] | subGrid[i / 3][j / 3]) & 0x1ff;
        for (; mask && !valid; mask &= (mask - 1))
        {
            int digitMask = mask & (-mask);
            int digit = __builtin_ctz(digitMask);
            flip(i, j, digit);
            board[i][j] = digit + '0' + 1;
            dfs(board, pos + 1);
            flip(i, j, digit);
        }
    }

    void flip(int i, int j, int digit)
    {
        row[i] ^= (1 << digit);
        col[j] ^= (1 << digit);
        subGrid[i / 3][j / 3] ^= (1 << digit);
    }
};
```





## 0039. 组合总和

### 题目：

给定一个**无重复元素**的正整数数组 candidates 和一个正整数 target ，找出 candidates 中所有可以使数字和为目标数 target 的唯一组合。

candidates 中的数字可以无限制重复被选取。如果至少一个所选数字数量不同，则两种组合是唯一的。 

对于给定的输入，保证和为 target 的唯一组合数少于 150 个。

**示例 1：**

```
输入: candidates = [2,3,6,7], target = 7
输出: [[7],[2,2,3]]
```

**示例 2：**

```
输入: candidates = [2,3,5], target = 8
输出: [[2,2,2,2],[2,3,3],[3,5]]
```

**示例 3：**

```
输入: candidates = [2], target = 1
输出: []
```

**示例 4：**

```
输入: candidates = [1], target = 1
输出: [[1]]
```

**示例 5：**

```
输入: candidates = [1], target = 2
输出: [[1,1]]
```

**提示：**

- 1 <= candidates.length <= 30
- 1 <= candidates[i] <= 200
- candidate 中的每个元素都是独一无二的。
- 1 <= target <= 500



**解题思路：**

对于这类**寻找所有可行解的题**，可以尝试用「**搜索回溯 - 剪枝**」的方法来解决。

定义递归函数 `dfs(target, combine, idx)` 表示当前在 `candidates` 数组的第 `idx` 位，还剩 `target` 要组合，已经组合的列表为 `combine`。递归的终止条件为 `target <= 0` 或者 `candidates` 数组被全部用完。那么在当前的函数中，每次我们可以选择跳过不用第 `idx` 个数，即执行 `dfs(target, combine, idx + 1)`。也可以选择使用第 `idx` 个数，即执行 `dfs(target - candidates[idx], combine, idx)`，注意到每个数字可以被无限制重复选取，因此搜索的下标仍为 `idx`。

更形象化地说，如果我们将整个搜索过程用一个树来表达，即如下图呈现，**每次的搜索都会延伸出两个分叉，直到递归的终止条件**，这样我们就能**不重复**（**前提得有序）**且不遗漏地找到所有可行解：

![leetcode_39](F:\C++\刷题\Img\leetcode_39.png)



**方法：**时：O(nlogn)  空：O(n)

```c++
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());  // 剪枝的前提就是有序
        vector<vector<int>> res;
        vector<int> combine;
        backtracking(candidates, target, res, combine, 0);
        return res;
    }

    void backtracking(vector<int>& candidates, int target, vector<vector<int>>& res, vector<int>& combine, int idx)
    {
        if (target <= 0)
        {
            if (target == 0)
                res.push_back(combine);
            return;
        }
            
        for (int i = idx; i < candidates.size(); ++i)
        {
            // 剪枝
            if (candidates[i] > target)
                return;
            combine.push_back(candidates[i]);
            backtracking(candidates, target - candidates[i], res, combine, i);
            combine.pop_back();  // 回溯
        }
    }
};
```





## 0040. 数组总和Ⅱ

### 题目：

给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的每个数字在每个组合中只能使用一次。

注意：解集不能包含重复的组合。 

**示例 1:**

```
输入: candidates = [10,1,2,7,6,1,5], target = 8,
输出:
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]
```

**示例 2:**

```
输入: candidates = [2,5,2,1,2], target = 5,
输出:
[
[1,2,2],
[5]
]
```

**提示:**

- 1 <= candidates.length <= 100
- 1 <= candidates[i] <= 50
- 1 <= target <= 30



**解题思路：**

类似于39题，但与39题不同的是，每个数字只能使用一次，所以下次递归需要 **i + 1**，并且还需要**排序去重**；



**方法：**搜索回溯 + 剪枝   时：O(nlogn)  空：O(n)

```c++
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> res;
        vector<int> combine;
        backtracking(candidates, res, combine, target, 0);
        return res;
    }
    void backtracking(vector<int>& candidates, vector<vector<int>>& res, vector<int>& combine, int target, int idx)
    {
        if (target <= 0)
        {
            if (target == 0)
                res.push_back(combine);
            return;
        }

        for (int i = idx; i < candidates.size(); ++i)
        {
            if (i > idx && candidates[i] == candidates[i - 1])  // 去重
                continue;
            if (candidates[i] > target)  // 剪枝
                return;
            combine.push_back(candidates[i]);
            backtracking(candidates, res, combine, target - candidates[i], i + 1);
            combine.pop_back();
        }
    }
};
```





## 0041. 缺失的第一个正整数

### 题目：

给你一个未排序的整数数组 nums ，请你找出其中没有出现的最小的正整数。

请你实现时间复杂度为 O(n) 并且**只使用常数级别额外空间**的解决方案。

**示例 1：**

```
输入：nums = [1,2,0]
输出：3
```

**示例 2：**

```
输入：nums = [3,4,-1,1]
输出：2
```

**示例 3：**

```
输入：nums = [7,8,9,11,12]
输出：1
```

**提示：**

- 1 <= nums.length <= 5 * 105
- -231 <= nums[i] <= 231 - 1



**解题思路：**

思路1：对数组进行遍历，对于遍历到的数 x，如果它在 [1, N]的范围内，那么就将数组中的第 x-1 个位置（注意：数组下标从 0 开始）打上「标记」。在遍历结束之后，如果所有的位置都被打上了标记，那么答案是 N+1，否则答案是最小的没有打上标记的位置加 1。

由于我们只在意 [1, N] 中的数，因此我们可以先对数组进行遍历，把不在 [1, N] 范围内的数修改成任意一个大于 N 的数（例如 N+1 ）。这样一来，数组中的所有数就都是正数了，因此我们就可以将「标记」表示为「负号」。算法的流程如下：

- 我们将数组中所有小于等于 0 的数修改为 N+1；


- 遍历数组中的每一个数 x，它可能已经被打了标记，因此原本对应的数为 |x|，其中 ∣∣ 为绝对值符号。如果 ∣x∣∈[1,N]，那么我们给数组中的第 |x| - 1 个位置的数添加一个负号。注意如果它已经有负号，不需要重复添加；


- 在遍历完成之后，如果数组中的每一个数都是负数，那么答案是 N+1，否则答案是第一个正数的位置加 1。

![leetcode_41](F:\C++\刷题\Img\leetcode_41.png)

思路2：如果数组中包含 x∈[1,N]，那么恢复后，数组的第 x−1 个元素为 x。

在恢复后，数组应当有 [1, 2, ..., N] 的形式，但其中有若干个位置上的数是错误的，每一个错误的位置就代表了一个缺失的正数。以题目中的示例二 [3, 4, -1, 1] 为例，恢复后的数组应当为 [1, -1, 3, 4]，我们就可以知道缺失的数为 22。

那么我们如何将数组进行恢复呢？我们可以对数组进行一次遍历，对于遍历到的数 x=nums[i]，如果 x∈[1,N]，我们就知道 x 应当出现在数组中的 x−1 的位置，因此交换 nums[i] 和 nums[x−1]，这样 xx 就出现在了正确的位置。在完成交换后，新的nums[i] 可能还在 [1,N] 的范围内，我们需要继续进行交换操作，直到 x不属于[1,N]。

如果 nums[i] 恰好与 nums[x−1] 相等，那么就会无限交换下去。此时我们有 nums[i] = x = nums[x−1]，说明 x 已经出现在了正确的位置。因此我们可以跳出循环，开始遍历下一个数。

由于每次的交换操作都会使得某一个数交换到正确的位置，因此交换的次数最多为 N，整个方法的时间复杂度为 O(N)。

思路3：空间换时间，hash表法（数组也行）；



**方法一：**直接在原数组上修改标记  时:  O(n)  空：O(1)

```c++
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        // 先检查是否包含 1 ，如果没有 1，则直接返回
        auto idx = find(nums.begin(), nums.end(), 1);
        if (idx == nums.end())
            return 1;
		
        // 将 <= 0 及 > n 的值全置为 1
        for (auto& num : nums)
            if (num <= 0 || num > n)
                num = 1;
		
        // 将每个数字 num 对应的下标为 num - 1 位置的值，置为相反数
        int i = -1;
        int n = nums.size();
        for (i = 0; i < n; ++i)
            nums[abs(nums[i]) - 1] = -abs(nums[abs(nums[i]) - 1]);

        // 查找第一个没有被 没有被置为负数的 位置，返回 i + 1
        for (i = 0; i < n; ++i)
            if (nums[i] > 0)
                return i + 1;

        return n + 1;
    }
};
```

**方法二：**将对应的数字，交换到对应 - 1的位置上  时:  O(n)  空：O(1)

```c++
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        int i = -1;
        for (i = 0; i < n; ++i)
        {
            while (nums[i] > 0 && nums[i] <= n && nums[i] != nums[nums[i] - 1])
                swap(nums[i], nums[nums[i] - 1]);
        }

        for (i = 0; i < n; ++i)
            if (nums[i] != i + 1)
                return i + 1;

        return n + 1;
    }
};
```





## 0042. 接雨水

### 题目：

给定 *n* 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

**示例 1：**

![leetcode_42](F:\C++\刷题\Img\leetcode_42.png)

```
输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
输出：6
解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。 
```

**示例 2：**

```
输入：height = [4,2,0,3,2,5]
输出：9
```

**提示：**

- n == height.length
- 0 <= n <= 3 * 10^4
- 0 <= height[i] <= 10^5



**解题思路：**

思路一：依次遍历每个柱子，找到每个柱子两侧的最大值中的最小值；然后和当前值作比较，大于当前值，则有积水；

​				时：O(n^2)  空：O(1);

思路二：动态规划，先用两个数组记录每个位置两侧的最大最小值，后续如思路一；

​				时：O(n)  空：O(n);

思路三：递减栈，维护一个单调栈，单调栈存储的是下标，满足从栈底到栈顶的下标对应的数组 height 中的元素递减。

从左到右遍历数组，遍历到下标 i 时，如果栈内至少有两个元素，记栈顶元素为 top，top 的下面一个元素是 left，则一定有 height[left]≥height[top]。如果 height[i]>height[top]，则得到一个可以接雨水的区域，该区域的宽度是 i−left−1，高度是 min(height[left],height[i])−height[top]，根据宽度和高度即可计算得到该区域能接的雨水量。

为了得到 left，需要将 top 出栈。在对 top 计算能接的雨水量之后，left 变成新的 top，重复上述操作，直到栈变为空，或者栈顶下标对应的 height 中的元素大于或等于 height[i]。

在对下标 i 处计算能接的雨水量之后，将 i 入栈，继续遍历后面的下标，计算能接的雨水量。遍历结束之后即可得到能接的雨水总量。

思路四：从左到右，从右到左，每次只计算当前柱子，用两个变量，记录左右边界最大值，在于当前变量对比。

​				时：O(n)  空：O(n);

![leetcode_42_1](F:\C++\刷题\Img\leetcode_42_1.png)

思路四：双指针法



**方法一：**暴力解法  超时

```c++
class Solution {
public:
    int trap(vector<int>& height) {
        int len = height.size();
        int count = 0;
        for (int i = 1; i < len - 1; ++i)
        {
            int leftMax = height[0];
            int rightMax = height[len - 1];
            for (int j = 1; j < i; ++j)
            {
                if (height[j] > leftMax)
                    leftMax = height[j];
            }   
            for (int j = len - 2; j > i; --j)
            {
                if (height[j] > rightMax)
                    rightMax = height[j];
            }

            int minMax = (leftMax < rightMax ? leftMax : rightMax);
            if (height[i] < minMax)
                count += (minMax - height[i]);
        }
        return count;
    }
};
```

**方法二：**动态规划

```c++
class Solution {
public:
    int trap(vector<int>& height) {
        int len = height.size();
        if (len <= 2)
            return 0;
        int count = 0;

        vector<int> leftMax(len);
        leftMax[0] = height[0];
        for (int i = 1; i < len; ++i)
            leftMax[i] = max(leftMax[i - 1], height[i]);

        vector<int> rightMax(len);
        rightMax[len - 1] = height[len - 1];
        for (int i = len - 2; i >= 0; --i)
            rightMax[i] = max(rightMax[i + 1], height[i]);

        for (int i = 1; i < len - 1; ++i)
        {
            int minMax = (leftMax[i] < rightMax[i] ? leftMax[i] : rightMax[i]);
            if (minMax > height[i])
                count += minMax - height[i];
        }

        return count;
    }
};
```

**方法三：**递减栈  

```c++
class Solution {
public:
    int trap(vector<int>& height) {
        int len = height.size();
        if (len <= 2)
            return 0;
        int count = 0;

        stack<int> st;
        for (int i = 0;i < len ; ++i)
        {
            while (!st.empty() && height[i] > height[st.top()])
            {
                int top = st.top();
                st.pop();

                // 1 号柱子比 0 号柱子高，所以不会存雨
                if (st.empty())
                    break;
                
                int left = st.top();
                count += (min(height[left], height[i]) - height[top]) * (i - left - 1);
            }
            st.push(i);
        }
        return count;
    }
};
```

**方法四：**双指针法

```c++
class Solution {
public:
    int trap(vector<int>& height) {
        int len = height.size();
        if (len <= 2)
            return 0;
        int count = 0;

        int left = 0, right = len - 1;
        int leftMax = 0, rightMax = 0;
        while (left < right)
        {
            leftMax = max(leftMax, height[left]);
            rightMax = max(rightMax, height[right]);

            if (height[left] < height[right])
            {
                count += leftMax - height[left];
                ++left;
            }
            else
            {
                count += rightMax - height[right];
                --right;
            }
        }
        return count;
    }
};
```





## 0045. 跳跃游戏 Ⅱ

### 题目：

给你一个非负整数数组 nums ，你最初位于数组的第一个位置。数组中的每个元素代表你在该位置可以跳跃的最大长度。

你的目标是使用最少的跳跃次数到达数组的最后一个位置。假设你总是可以到达数组的最后一个位置。

**示例 1:**

```
输入: nums = [2,3,1,1,4]
输出: 2
解释: 跳到最后一个位置的最小跳跃数是 2。
     从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。
```

**示例 2:**

```
输入: nums = [2,3,0,1,4]
输出: 2
```

**提示:**

- 1 <= nums.length <= 10^4
- 0 <= nums[i] <= 1000



**解题思路：**贪心算法的优化

思路一：我们的目标是到达数组的最后一个位置，因此我们可以考虑最后一步跳跃前所在的位置，该位置通过跳跃能够到达最后一个位置。

如果有多个位置通过跳跃都能够到达最后一个位置，那么我们应该如何进行选择呢？直观上来看，我们可以「贪心」地选择距离最后一个位置最远的那个位置，也就是对应下标最小的那个位置。因此，我们可以从左到右遍历数组，选择第一个满足要求的位置。

找到最后一步跳跃前所在的位置之后，我们继续贪心地寻找倒数第二步跳跃前所在的位置，以此类推，直到找到数组的开始位置。

思路二：如果我们「贪心」地进行正向查找，每次找到可到达的最远位置，就可以在线性时间内得到最少的跳跃次数。

例如，对于数组 [2,3,1,2,4,2,3]，初始位置是下标 0，从下标 0 出发，最远可到达下标 2。下标 0 可到达的位置中，下标 1 的值是 3，从下标 1 出发可以达到更远的位置，因此第一步到达下标 1。

从下标 1 出发，最远可到达下标 4。下标 1 可到达的位置中，下标 4 的值是 4 ，从下标 4 出发可以达到更远的位置，因此第二步到达下标 4。

![leetcode_45](F:\C++\刷题\Img\leetcode_45.png)



**方法一：** 时：O(n^2)  空：O(1)

```c++
class Solution {
public:
    int jump(vector<int>& nums) {
        int position = nums.size() - 1;
        int steps = 0;
        while (position > 0)
        {
            for (int i = 0; i < position; ++i)
            {
                if (i + nums[i] >= position)
                {
                    position = i;
                    ++steps;
                    break;
                }
            }
        }
        return steps;
    }
};
```

**方法二：** 时：O(n)  空：O(1)

```c++
class Solution {
public:
    int jump(vector<int>& nums) {
        int len = nums.size();
        int steps = 0;
        int maxPos = 0;
        int end = 0;
        for (int i = 0; i < len - 1; ++i)
        {
            maxPos = max(maxPos, nums[i] + i);
            if (i == end)
            {
                end = maxPos;
                ++steps;
            }
        }
        return steps;
    }
};
```





## 0048. 旋转图像

### 题目：

给定一个 n × n 的二维矩阵 matrix 表示一个图像。请你将图像**顺时针**旋转 90 度。

你必须在 **原地** 旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要 使用另一个矩阵来旋转图像。

**示例 1：**

![leetcode_48_1](F:\C++\刷题\Img\leetcode_48_1.jpg)

```
输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[[7,4,1],[8,5,2],[9,6,3]]
```

**示例 2：**

![leetcode_48_2](F:\C++\刷题\Img\leetcode_48_2.jpg)

```
输入：matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
输出：[[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
```

**示例 3：**

```
输入：matrix = [[1]]
输出：[[1]]
```

**示例 4：**

```
输入：matrix = [[1,2],[3,4]]
输出：[[3,1],[4,2]]
```

**提示：**

- matrix.length == n
- matrix[i].length == n
- 1 <= n <= 20
- -1000 <= matrix[i][j] <= 1000

**解题思路：**

思路一：两层for循环，控制下标，存下当前值，四次值的交换。

思路二：水平轴对称 + 主轴对称  或  主轴对称 + 水平轴对称。

拓展：逆时针、主对角线、副对角线、水平轴、竖直轴；



**方法一：**时：O(n^2)  空O(1)

```c++
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        if (n <= 1)
            return;
        int tmp = -1;
        for (int i = 0; i < n / 2; ++i)
        {
            for (int j = 0; j < (n + 1) / 2; ++j)
            {
                tmp = matrix[i][j];
                matrix[i][j] = matrix[n - j - 1][i];
                matrix[n - j - 1][i] = matrix[n - i - 1][n - j - 1];
                matrix[n - i - 1][n - j - 1] = matrix[j][n - i - 1];
                matrix[j][n - i - 1] = tmp;
            }
        }
    }
};
```

方法二：时：O(n^2)  空O(1)

```c++
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        if (n <= 1)
            return;
        int tmp = -1;
        for (int i = 0; i < n / 2; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                tmp = matrix[i][j];
                matrix[i][j] = matrix[n - i - 1][j];
                matrix[n - i - 1][j] = tmp;
            }
        }

        for (int i = 0; i < n; ++i)
        {
            for (int j = i; j < n; ++j)
            {
                if (i == j)
                    continue;
                tmp = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = tmp;
            }
        }
    }
};
```





## 0053. 最大子序和

### 题目：

给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

**示例 1：**

```
输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
输出：6
解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。
```

**示例 2：**

```
输入：nums = [1]
输出：1
```

**示例 3：**

```
输入：nums = [0]
输出：0
```

**示例 4：**

```
输入：nums = [-1]
输出：-1
```

**示例 5：**

```
输入：nums = [-100000]
输出：-100000
```

**提示：**

- 1 <= nums.length <= 3 * 10^4
- -10^5 <= nums[i] <= 10^5



**解题思路：**

思路一：暴力解法  时：O(n^2)  空O(1)

​				求解每一段子序列的长度，求出最大值

思路二：动态规划  时：O(n)  空O(n)

​				使用一个等长数组，每一个位置所保存的值，都是当前位置之前的最大子序列和

思路三：贪心算法  时：O(n)  空O(1)

​				从头遍历，对每一个位置，保存一个当前和，当前和加上当前位置的值，若大于最大值，则存储，若小于，则不变，若为负数，则curSum = 0；

思路四：分治法  时：O(nlogn)  空O(logn)

​				取数组中心为中心，最大子序要么全在中心左边，要么在右边，要么跨中心。分三种情况，跨中心的情况，再分治成中心点左侧和右侧的最大子序列问题。也就是先分治为最小单位求子序和，合并后求各段的最大子序长。



**方法一：**时：O(n^2)  空O(1)

```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int len = nums.size();
        if (len == 1)
            return nums[0];
        int maxSum = INT_MIN;
        for (int i = 0; i < len; ++i)
        {
            int curSum = 0;
            for (int j = i; j < len; ++j)
            {
                curSum += nums[j];
                if (curSum > maxSum)
                    maxSum = curSum;
            }
        }
        return maxSum;
    }
};
```

**方法二：**时：O(n)  空O(n)

```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int len = nums.size();
        if (len == 1)
            return nums[0];
        vector<int> dp(len);
        
        dp[0] = nums[0];
        int maxNum = dp[0];
        for (int i = 1; i < len; ++i)
        {
            dp[i] = max(dp[i - 1] + nums[i], nums[i]);
            maxNum = max(dp[i], maxNum);
        }
        return maxNum;
    }
};
```

**方法三：**时：O(n)  空O(1)

```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int len = nums.size();
        if (len == 1)
            return nums[0];
        
        int maxNum = INT_MIN;
        int curSum = 0;
        for (int i = 0; i < len; ++i)
        {
            curSum = curSum + nums[i];
            maxNum = max(curSum, maxNum);
            curSum = max(curSum, 0);
        }
        return maxNum;
    }
};
```

**方法四：**分治法  时：O(nlogn)  空O(logn)

```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int len = nums.size();
        if (len == 1)
            return nums[0];
        
        return maxSubArrayHelper(nums, 0, len - 1);
    }

    int maxSubArrayHelper(vector<int>& nums, int left, int right)
    {
        if (left == right)
            return nums[left];
        int mid = (left + right) / 2;
        int leftSum = maxSubArrayHelper(nums, left, mid);
        int rightSum = maxSubArrayHelper(nums, mid + 1, right);
        int midSum = findMaxCrossingSubarray(nums, left, mid, right);
        return max(max(leftSum, rightSum), midSum);
    }

    int findMaxCrossingSubarray(vector<int>& nums, int left, int mid, int right)
    {
        int leftSum = INT_MIN;
        int sum = 0;
        for (int i = mid; i >= left; --i)
        {
            sum = sum + nums[i];
            leftSum = max(sum, leftSum);
        }

        int rightSum = INT_MIN;
        sum = 0;
        for (int i = mid + 1; i <= right; ++i)
        {
            sum = sum + nums[i];
            rightSum = max(sum, rightSum);
        }
        return leftSum + rightSum;
    }
};
```





## 0051. N皇后

### 题目：

**n 皇后问题** 研究的是如何将 `n` 个皇后放置在 `n×n` 的棋盘上，并且使皇后彼此之间不能相互攻击。

给你一个整数 `n` ，返回所有不同的 **n 皇后问题** 的解决方案。

每一种解法包含一个不同的 **n 皇后问题** 的棋子放置方案，该方案中 `'Q'` 和 `'.'` 分别代表了皇后和空位。

**示例1：**

![leetcode_51](F:\C++\刷题\Img\leetcode_51.jpg)

```
输入：n = 4
输出：[[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
解释：如上图所示，4 皇后问题存在两个不同的解法。
```

**示例 2：**

```
输入：n = 1
输出：[["Q"]]
```

**提示：**

- `1 <= n <= 9`
- 皇后彼此不能相互攻击，也就是说：任何两个皇后都不能处于同一条横行、纵行或斜线上。



**解题思路：**

思路一：递归 + 回溯

[递归+回溯](https://leetcode-cn.com/problems/n-queens/solution/nhuang-hou-by-leetcode-solution/)

时间复杂度：O(n!)

空间复杂度：O(n)

思路二：位运算改进

[位运算改进](https://leetcode-cn.com/problems/n-queens/solution/nhuang-hou-by-leetcode-solution/)

时间复杂度：O(n!)

空间复杂度：O(n)



**方法一：**

```c++
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<int> queens = vector<int>(n, -1);
        unordered_set<int> col = unordered_set<int>();
        unordered_set<int> diags1 = unordered_set<int>();
        unordered_set<int> diags2 = unordered_set<int>();
        backTrace(res, col, diags1, diags2, queens, n, 0);
        return res;
    }
    void backTrace(vector<vector<string>>& res, unordered_set<int>& col, unordered_set<int>& diags1, unordered_set<int>& diags2, vector<int>& queens, int n, int idx)
    {
        if (idx == n)
        {
            res.push_back(generateBoard(queens, n));
            return;
        }
        else
        {
            for (int i = 0; i < n; ++i)
            {
                if (col.find(i) != col.end())
                    continue;
                int diag1 = idx - i;
                if (diags1.find(diag1) != diags1.end())
                    continue;
                int diag2 = idx + i;
                if (diags2.find(diag2) != diags2.end())
                    continue;
                col.insert(i);
                diags1.insert(diag1);
                diags2.insert(diag2);
                queens[idx] = i;
                backTrace(res, col, diags1, diags2, queens, n, idx + 1);
                queens[idx] = -1;
                col.erase(i);
                diags1.erase(diag1);
                diags2.erase(diag2);
            }
        }
    }
    vector<string> generateBoard(vector<int>& queens, int n)
    {
        vector<string> res = vector<string>(n, string(n, '.'));
        for (int i = 0; i < n; ++i)
            res[i][queens[i]] = 'Q';
        return res;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<int> queens = vector<int>(n, -1);
        backTrace(res, 0, 0, 0, queens, n, 0);
        return res;
    }
    void backTrace(vector<vector<string>>& res, int col, int diags1, int diags2, vector<int>& queens, int n, int idx)
    {
        if (idx == n)
        {
            res.push_back(generateBoard(queens, n));
            return;
        }
        else
        {
            int availablePosition = ~(col | diags1 | diags2) & ((1 << n) - 1);
            for (; availablePosition > 0; availablePosition &= (availablePosition - 1))
            {
                int pos = availablePosition & (-availablePosition);
                int index = __builtin_ctz(pos);
                queens[idx] = index;
                backTrace(res, col | pos, (diags1 | pos) >> 1, (diags2 | pos) << 1, queens, n, idx + 1);
                queens[idx] = -1;
            }
        }
    }
    vector<string> generateBoard(vector<int>& queens, int n)
    {
        vector<string> res = vector<string>(n, string(n, '.'));
        for (int i = 0; i < n; ++i)
            res[i][queens[i]] = 'Q';
        return res;
    }
};
```





## 0054. 螺旋矩阵

### 题目：

给你一个 m 行 n 列的矩阵 matrix ，请按照 顺时针螺旋顺序 ，返回矩阵中的所有元素。

 

**示例 1：**

```
输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[1,2,3,6,9,8,7,4,5]
```

![leetcode_54_1](F:\C++\刷题\Img\leetcode_54_1.jpg)

**示例 2：**

```
输入：matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
输出：[1,2,3,4,8,12,11,10,9,5,6,7]
```

![leetcode_54_2](F:\C++\刷题\Img\leetcode_54_2.jpg)

**提示：**

- m == matrix.length
- n == matrix[i].length
- 1 <= m, n <= 10
- -100 <= matrix [i][j] <= 100



**解题思路：**

顺着周边一圈一圈往里走，控制好下标，先记录恒，再记录竖，注意最里层只有一行，或者一列的情况；

**方法：**时：O(mn)  空：O(1)  除了输出数组外，其他的都是常数阶

```c++
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int height = matrix.size();
        int width = matrix[0].size();
        int len = min(height, width);
        vector<int> res;
        for (int i = 0; i < (len + 1) / 2; ++i)
        {
            int j = 0;
            for (j = i; j < width - i; ++j)
                res.push_back(matrix[i][j]);
            for (j = i + 1; j < height - i; ++j)
                res.push_back(matrix[j][width - i - 1]);
            for (j = width - i - 2; j >= i && i < height - i - 1; --j)
			    res.push_back(matrix[height - i - 1][j]);
            for (j = height - i - 2; j > i && i < width - i - 1; --j)
                res.push_back(matrix[j][i]);
        }
        return res;
    }
};
```







## 0055. 跳跃游戏

### 题目：

给定一个非负整数数组 `nums` ，你最初位于数组的 第一个下标 。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

判断你是否能够到达最后一个下标。

**示例 1：**

```
输入：nums = [2,3,1,1,4]
输出：true
解释：可以先跳 1 步，从下标 0 到达下标 1, 然后再从下标 1 跳 3 步到达最后一个下标。
```

**示例 2：**

```
输入：nums = [3,2,1,0,4]
输出：false
解释：无论怎样，总会到达下标为 3 的位置。但该下标的最大跳跃长度是 0 ， 所以永远不可能到达最后一个下标。
```

**提示：**

- 1 <= nums.length <= 3 * 10^4
- 0 <= nums[i] <= 10^5



**解题思路：**

存储一个可到达的最大位置，自左向右依次遍历每个数字，记录下当前位置可到达的最远位置，若最远位置已经可到达最后一个，则直接返回，若最远位置是当前位置，则表示走不下去了；



**方法：**时：O(n) 空：O(1)

```c++
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int len = nums.size();
        if (len == 0)
            return false;
        if (len == 1)
            return true;
        
        int maxJumpIndex = 0;
        for (int i = 0; i < len; ++i)
        {
            maxJumpIndex = max(i + nums[i], maxJumpIndex);
            if (maxJumpIndex >= len - 1)
                return true;
            if (maxJumpIndex == i)
                return false;
        }
        return false;
    }
};
```





## 0056. 合并区间

### 题目：

以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。请你合并所有重叠的区间，并返回一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间。

**示例 1：**

```
输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
输出：[[1,6],[8,10],[15,18]]
解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
```

**示例 2：**

```
输入：intervals = [[1,4],[4,5]]
输出：[[1,5]]
解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。
```

**提示：**

- 1 <= intervals.length <= 10^4
- intervals[i].length == 2
- 0 <= starti <= endi <= 10^4



**解题思路：**

![leetcode_56](F:\C++\刷题\Img\leetcode_56.png)

先按每个子集合的左边界排序，则重叠区域就会聚集在一起；

先将第一个子集合存储下来，下一个子集合，若是左边界在当前 res 最后一个之中，则判断右边界是否大于 res 最后一个的右边界；

- 时间复杂度：O(nlogn)，主要的时间开销是排序的 O(nlogn)。


- 空间复杂度：O(logn)，其中 n 为区间的数量。这里计算的是存储答案之外，使用的额外空间。O(logn) 即为排序所需要的空间复杂度。


**方法：**

```c++
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int len = intervals.size();
        if (len <= 0)
            return intervals;
        sort(intervals.begin(), intervals.end());

        vector<vector<int>> res;
        res.push_back(intervals[0]);
        for (int i = 1; i < len; ++i)
        {
            int L = intervals[i][0];
            int R = intervals[i][1];
            if (L <= res.back()[1])
            {
                if (R > res.back()[1])
                    res.back()[1] = R;
            }
            else
                res.push_back(intervals[i]);
        }
        return res;
    }
};
```





## 0057. 插入区间

### 题目：

给你一个 **无重叠的** *，*按照区间起始端点排序的区间列表。

在列表中插入一个新的区间，你需要确保列表中的区间仍然有序且不重叠（如果有必要的话，可以合并区间）。

**示例 1：**

```
输入：intervals = [[1,3],[6,9]], newInterval = [2,5]
输出：[[1,5],[6,9]]
```

**示例 2：**

```
输入：intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
输出：[[1,2],[3,10],[12,16]]
解释：这是因为新的区间 [4,8] 与 [3,5],[6,7],[8,10] 重叠。
```

**示例 3：**

```
输入：intervals = [], newInterval = [5,7]
输出：[[5,7]]
```

**示例 4：**

```
输入：intervals = [[1,5]], newInterval = [2,3]
输出：[[1,5]]
```

**示例 5：**

```
输入：intervals = [[1,5]], newInterval = [2,7]
输出：[[1,7]]
```

**提示：**

- 0 <= intervals.length <= 10^4
- intervals[i].length == 2
- 0 <= intervals[i][0] <= intervals[i][1] <= 10^5
- intervals **根据** intervals[i][0] **按 升序 排列**
- newInterval.length == 2
- 0 <= newInterval[0] <= newInterval[1] <= 10^5



**解题思路：**

依次遍历intervals集合，判断newInterval左右两个数应该放的位置；

时间复杂度：O(n)，其中 n 是数组 intervals 的长度，即给定的区间个数。

空间复杂度：O(1)。除了存储返回答案的空间以外，我们只需要额外的常数空间即可。



**方法：**

```c++
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int len = intervals.size();
        if (len == 0)
            return vector<vector<int>>{newInterval};

        vector<vector<int>> res;
        int i = 0;
        for (; i < len; ++i)
        {
            if (newInterval[0] >= intervals[i][0])
                res.push_back(intervals[i]);
            else 
                break;
        }

        if (res.empty() || res.back()[1] < newInterval[0])   // res.empty()这一句很重要
            res.push_back(newInterval);
        else if (res.back()[1] < newInterval[1])
            res.back()[1] = newInterval[1];
        
        for (; i < len; ++i)
        {
            if (intervals[i][0] <= res.back()[1])
            {
                if (intervals[i][1] > res.back()[1])
                    res.back()[1] = intervals[i][1];
            }
            else
                res.push_back(intervals[i]);
        }
        
        return res;
    }
};
```





## 0059. 螺旋矩阵 Ⅱ

### 题目：

给你一个正整数 `n` ，生成一个包含 `1` 到 `n^2` 所有元素，且元素按顺时针顺序螺旋排列的 `n x n` 正方形矩阵 `matrix` 。

**示例 1：**

![leetcode_59](F:\C++\刷题\Img\leetcode_59.jpg)

```
输入：n = 3
输出：[[1,2,3],[8,9,4],[7,6,5]]
```

**示例 2：**

```
输入：n = 1
输出：[[1]]
```

**提示：**

- 1 <= n <= 20

**解题思路：**

等效于54题

**方法：**

```c++
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n, vector<int>(n));
        int num = 0;
        for (int i = 0; i < (n + 1) / 2; ++i)
        {
            for (int j = i; j < n - i; ++j)
                res[i][j] = ++num;
            for (int j = i + 1; j < n - i; ++j)
                res[j][n - i - 1] = ++num;
            for (int j = n - i - 2; j >= i && i < n - i - 1; --j)
                res[n - i - 1][j] = ++num;
            for (int j = n - i - 2; j > i && i < n - i - 1; --j)
                res[j][i] = ++num;
        }
        return res;
    }
};
```





## 0062. 不同路径

### 题目：

一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。

问总共有多少条不同的路径？

**示例1：**

![leetcode_62](F:\C++\刷题\Img\leetcode_62.png)

```
输入：m = 3, n = 7
输出：28
```

**示例 2：**

```
输入：m = 3, n = 2
输出：3
解释：
从左上角开始，总共有 3 条路径可以到达右下角。

1. 向右 -> 向下 -> 向下
2. 向下 -> 向下 -> 向右
3. 向下 -> 向右 -> 向下
```

**示例 3：**

```
输入：m = 7, n = 3
输出：28
```

**示例 4：**

```
输入：m = 3, n = 3
输出：6
```

**提示：**

- 1 <= m, n <= 100
- 题目数据保证答案小于等于 2 * 10^9



**解题思路：**

思路一：递归求解

思路二：动态规划

状态转移方程：$dp[i][j] = dp[i-1][j] + dp[i][j-1]$

​		需要注意的是，如果 i=0，那么 f(i-1,j) 并不是一个满足要求的状态，我们需要忽略这一项；同理，如果 j=0，那么 f(i,j-1) 并不是一个满足要求的状态，需要忽略这一项。

​		**复杂度分析**

- 时间复杂度：O(mn)。
- 空间复杂度：O(mn)，即为存储所有状态需要的空间。

思路三：组合数学带公式

从左上角到右下角的过程中，我们需要移动 m+n-2m+n−2 次，其中有 m-1m−1 次向下移动，n-1n−1 次向右移动。因此路径的总数，就等于从 m+n-2m+n−2 次移动中选择 m-1m−1 次向下移动的方案数，即组合数：

$${\Large C}_{m+n-2}^{m-1} = \binom{m+n-2}{m-1} = \frac{(m+n-2)(m+n-3)\cdots n}{(m-1)!} = \frac{(m+n-2)!}{(m-1)!(n-1)!}$$

​	**复杂度分析**

- 时间复杂度：O(min(m, n))。
- 空间复杂度：O(1)。

**方法一：**递归（超时）

```c++
class Solution {
public:
    int uniquePaths(int m, int n) {
        return 1 + _uniquePaths(1, 1, m, n);
    }
    int _uniquePaths(int curm, int curn, int m, int n)
    {
        if (curm < m && curn < n)
            return 1 + _uniquePaths(curm + 1, curn, m, n) + _uniquePaths(curm, curn + 1, m, n);
        else
            return 0;
    }
};
```

方法二：动态规划

```c++
// dp[i][j] = dp[i-1][j] + dp[i][j-1]
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> status(m, vector<int>(n, 1));
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (i == 0 || j == 0)
                    continue;
                status[i][j] = status[i - 1][j] + status[i][j - 1];
            }
        }
        return status[m - 1][n - 1];
    }
};
```

**方法三：**组合数学

```c++
class Solution {
public:
    int uniquePaths(int m, int n) {
        long long res = 1;
        for (int i = m - 2; i >= 0; --i)
            res = res * (m + n - 2 - i) / (m - 1 - i);
        return res;
    }
};
```





## 0063. 不同路径 Ⅱ

### 题目：

一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。

现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？

![leetcode_63](F:\C++\刷题\Img\leetcode_63.png)

网格中的障碍物和空位置分别用 `1` 和 `0` 来表示。

**示例1：**

![leetcode_63_1](F:\C++\刷题\Img\leetcode_63_1.jpg)

```
输入：obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
输出：2
解释：
3x3 网格的正中间有一个障碍物。
从左上角到右下角一共有 2 条不同的路径：
1. 向右 -> 向右 -> 向下 -> 向下
2. 向下 -> 向下 -> 向右 -> 向右
```

**示例2：**

![leetcode_63_2](F:\C++\刷题\Img\leetcode_63_2.jpg)

```
输入：obstacleGrid = [[0,1],[0,0]]
输出：1
```

**提示：**

- m == obstacleGrid.length
- n == obstacleGrid[i].length
- 1 <= m, n <= 100
- obstacleGrid [i] [j] 为 0 或 1



**解题思路：**

思路一：动态规划，不过要注意各种边界值

   			1. 若障碍在 i == 0 或 j == 0 的边界上，则障碍下面障碍后面所有的位置都不可达；
   			2. 若障碍在 起点 或 终点，则直接为 0；

思路二：动态规划 + 滚动数组

使用一个一维数组即可；

动态规划的题目分为两大类，**一种是求最优解类**，典型问题是背包问题，**另一种就是计数类**，比如这里的统计方案数的问题，它们都存在一定的递推性质。前者的递推性质还有一个名字，叫做 「**最优子结构**」 ——即当前问题的最优解取决于子问题的最优解，后者类似，当前问题的方案数取决于子问题的方案数。所以在遇到求方案数的问题时，我们可以往动态规划的方向考虑。



**方法一：**时：O(mn)  空：O(mn)

```c++
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        if (obstacleGrid[m - 1][n - 1] == 1 || obstacleGrid[0][0] == 1)
            return 0;
        vector<vector<int>> status(m, vector<int>(n, 1));
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (i == 0 || j == 0)
                {
                    if (obstacleGrid[i][j] == 1)
                        status[i][j] = 0;
                    if ((i != 0 && j == 0 && status[i - 1][j] == 0) || (i == 0 && j != 0 && status[i][j - 1] == 0))
                        status[i][j] = 0;
                    continue;
                }
                    
                if (obstacleGrid[i - 1][j] == 1 && obstacleGrid[i][j - 1] == 0)
                    status[i][j] = status[i][j - 1];
                else if (obstacleGrid[i - 1][j] == 0 && obstacleGrid[i][j - 1] == 1)
                    status[i][j] = status[i - 1][j];
                else if (obstacleGrid[i - 1][j] == 0 && obstacleGrid[i][j - 1] == 0)
                    status[i][j] = status[i - 1][j] + status[i][j - 1];
                else
                    status[i][j] = 0;
            }
        }
        return status[m - 1][n - 1];
    }
};
```

**方法二：**时：O(mn)  空：O(n)

```c++
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        if (obstacleGrid[m - 1][n - 1] == 1 || obstacleGrid[0][0] == 1)
            return 0;
        
        vector<int> status(n, 0);
        status[0] = (obstacleGrid[0][0] == 0);
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (obstacleGrid[i][j] == 1)
                {
                    status[j] = 0;
                    continue;
                }
                // obstacleGrid[i][j - 1] == 0 剪枝操作:若左边位置是障碍，则当前位置直接就是上面的值，不需要计算
                if (j > 0 && obstacleGrid[i][j - 1] == 0)
                    status[j] += status[j - 1];
            }
        }
        return status[n - 1];
    }
};
```





## 0064. 最小路径和

### 题目：

给定一个包含非负整数的 m x n 网格 grid ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。

说明：每次只能向下或者向右移动一步。

 **示例1：**

![leetcode_64](F:\C++\刷题\Img\leetcode_64.jpg)

```
输入：grid = [[1,3,1],[1,5,1],[4,2,1]]
输出：7
解释：因为路径 1→3→1→1→1 的总和最小。
```

**示例 2：**

```
输入：grid = [[1,2,3],[4,5,6]]
输出：12
```

**提示：**

- m == grid.length
- n == grid[i].length
- 1 <= m, n <= 200
- 0 <= grid[i] [j] <= 100



**解题思路：**

方法同样等同于62.63题，使用动态规划，但注意的地方是单独对第一行和第一列处理。

时间复杂度：O(mn)

空间复杂度：O(n)



**方法：**

```c++
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<int> status(n, 0);
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (i == 0 && j == 0)
                    status[j] = grid[i][j];
                else if (i == 0 && j != 0)
                    status[j] = grid[i][j] + status[j - 1];
                else if (i != 0 && j == 0)
                    status[j] = grid[i][j] + status[j];
                else
                    status[j] = grid[i][j] + min(status[j], status[j - 1]);
            }
        }
        return status[n - 1];
    }
};
```





## 0066. 加一

### 题目：

给定一个由 **整数** 组成的 **非空** 数组所表示的非负整数，在该数的基础上加一。

最高位数字存放在数组的首位， 数组中每个元素只存储**单个**数字。

你可以假设除了整数 0 之外，这个整数不会以零开头。

**示例 1：**

```
输入：digits = [1,2,3]
输出：[1,2,4]
解释：输入数组表示数字 123。
```

**示例 2：**

```
输入：digits = [4,3,2,1]
输出：[4,3,2,2]
解释：输入数组表示数字 4321。
```

**示例 3：**

```
输入：digits = [0]
输出：[1]
```

**提示：**

- 1 <= digits.length <= 100
- 0 <= digits[i] <= 9



**解题思路：**

从后向前遍历，没什么方法，但有一个技巧，若当前++之后，还 <= 9的话，就可以直接返回；

若循环结束还没返回，说明最高位进一；



**方法：**

```c++
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int len = digits.size();
        for (int i = len - 1; i >= 0; --i)
        {
            digits[i]++;
            digits[i] %= 10;
            if (digits[i] != 0)
                return digits;
        }
        digits.insert(digits.begin(), 1);
        return digits;
    }
};
```





## 0073. 矩阵置零

### 题目：

给定一个 `m x n` 的矩阵，如果一个元素为 **0** ，则将其所在行和列的所有元素都设为 **0** 。请使用 **原地** 算法。

**进阶：**

- 一个直观的解决方案是使用  O(mn) 的额外空间，但这并不是一个好的解决方案。

- 一个简单的改进方案是使用 O(m + n) 的额外空间，但这仍然不是最好的解决方案。
- 你能想出一个仅使用常量空间的解决方案吗？

**示例1：**

![leetcode_73_1](F:\C++\刷题\Img\leetcode_73_1.jpg)

```
输入：matrix = [[1,1,1],[1,0,1],[1,1,1]]
输出：[[1,0,1],[0,0,0],[1,0,1]]
```

**示例2：**

![leetcode_73_2](F:\C++\刷题\Img\leetcode_73_2.jpg)

```
输入：matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
输出：[[0,0,0,0],[0,4,5,0],[0,3,1,0]]
```

**提示：**

- m == matrix.length
- n == matrix[0].length
- 1 <= m, n <= 200
- -2^31 <= matrix[i][j] <= 2^31 - 1



**解题思路：**

永远的思路：先标记，最后再改 0 ，防止因修改导致更多的0的存在。

时间复杂度：O(mn)

空间复杂度：O(1)

思路一：使用两个标志位。

- 先标记第一行或第一列是否有0的存在；
- 找[1, m）和[1, n）是否有 0 的存在，若有，将对应行首和列首置为0；
- 按照行首和列首是否为0，将对应行列置0；
- 按照首行或首列的0标志位，将首行首列置0；

思路二：使用一个列标志位

- 依次遍历每一行，记录第一列是否有 0 ，以及每一行的[1, n）列是否有 0，若有将对应位置行首或列首置 0；
- 从后向前依次遍历每一行，循环内嵌[1, n）每一列，若当前位置行首或列首有一个为 0，则置0。顺带判断首列是否有0，若存在，顺带将当前行第一个位置置0。

实际运行两个标志位比一个标志为要快一点；



**方法一：**使用一个标志位

```c++
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        if (matrix.size() == 0 || matrix[0].size() == 0)
            return;
        int m = matrix.size(), n = matrix[0].size();
        bool isFirstColExistZero = false;
        int i = 0, j = 0;

        for (i = 0; i < m; ++i)
        {
            if (matrix[i][0] == 0)
                isFirstColExistZero = true;
            for (j = 1; j < n; ++j)
            {
                if (matrix[i][j] == 0)
                {
                    matrix[i][0] = matrix[0][j] = 0;
                }
            }
        }

        for (i = m - 1; i >= 0; --i)
        {
            for (j = 1; j < n; ++j)
            {
                if (matrix[i][0] == 0 || matrix[0][j] == 0)
                    matrix[i][j] = 0;
            }
            if (isFirstColExistZero)
                matrix[i][0] = 0;
        }
    }
};
```

**方法二：**使用两个标志位

```c++
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        if (matrix.size() == 0 || matrix[0].size() == 0)
            return;
        int m = matrix.size(), n = matrix[0].size();
        bool isFirstRowExistZero = false, isFirstColExistZero = false;
        int i = 0, j = 0;
        for (j = 0; j < n; ++j)
        {
            if (matrix[0][j] == 0)
            {
                isFirstRowExistZero = true;
                break;
            }
        }

        for (i = 0; i < m; ++i)
        {
            if (matrix[i][0] == 0)
            {
                isFirstColExistZero = true;
                break;
            }
        }

        for (i = 1; i < m; ++i)
        {
            for (j = 1; j < n ; ++j)
            {
                if (matrix[i][j] == 0)
                {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        for (i = 1; i < m; ++i)
        {
            if (matrix[i][0] == 0)
            {
                for (j = 1; j < n; ++j)
                    matrix[i][j] = 0;
            }
        }

        for (j = 1; j < n; ++j)
        {
            if (matrix[0][j] == 0)
            {
                for (i = 1; i < m; ++i)
                    matrix[i][j] = 0;
            }
        }

        if (isFirstColExistZero)
        {
            for (i = 0; i < m; ++i)
                matrix[i][0] = 0;
        }

        if (isFirstRowExistZero)
        {
            for (j = 0; j < n; ++j)
                matrix[0][j] = 0;
        }
    }
};
```







## 0074. 搜索二维矩阵

### 题目：

编写一个高效的算法来判断 `m x n` 矩阵中，是否存在一个目标值。该矩阵具有如下特性：

- 每行中的整数从左到右按升序排列。
- 每行的第一个整数大于前一行的最后一个整数。

**示例1：**

![leetcode_74_1](F:\C++\刷题\Img\leetcode_74_1.jpg)

```
输入：matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
输出：true
```

**示例2：**

![leetcode_74_2jpg](F:\C++\刷题\Img\leetcode_74_2jpg.jpg)

```
输入：matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
输出：false
```

**提示：**

- m == matrix.length
- n == matrix[i].length
- 1 <= m, n <= 100
- -10^4 <= matrix[i] [j], target <= 10^4



**解题思路：**

不能直接用矩阵特性，即从[0] [n - 1]位置出发，因为那个思想前提是target存在；

可以将二维数组看作是一个整体递增序列的数列，使用二分查找；

时间复杂度：O(logmn)

空间复杂度：O(1)

**方法：**

```c++
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();
        int low = 0, high = m * n - 1;
        int mid = -1;
        while (low <= high)
        {
            mid = low + ((high - low) >> 1);
            int tmp = matrix[mid / n][mid % n];
            if (tmp > target)
                high = mid - 1;
            else if (tmp < target)
                low = mid + 1;
            else
                return true;
        }
        return false;
    }
};
```







## 0075. 颜色分类

### 题目：

给定一个包含红色、白色和蓝色，一共 `n` 个元素的数组，**原地**对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。

此题中，使用整数 0、 1 和 2 分别表示红色、白色和蓝色。

 

**示例 1：**

```
输入：nums = [2,0,2,1,1,0]
输出：[0,0,1,1,2,2]
```

**示例 2：**

```
输入：nums = [2,0,1]
输出：[0,1,2]
```

**示例 3：**

```
输入：nums = [0]
输出：[0]
```

**示例 4：**

```
输入：nums = [1]
输出：[1]
```

**提示：**

- n == nums.length
- 1 <= n <= 300
- nums[i] 为 0、1 或 2

**进阶：**

- 你可以不使用代码库中的排序函数来解决这道题吗？
- 你能想出一个仅使用常数空间的一趟扫描算法吗？



**解题思路：**

思路一：等价于快排；

​			时间复杂度：O(nlogn)

​			空间复杂度：O(1)



思路二：单指针法；

​				使用一个指针，分两次遍历，一次从前往后，将0交换到前面，一次从后往前，将2将换到后面;

​			时间复杂度：O(n)

​			空间复杂度：O(1)



思路三：双指针法（两端向内走）；

​				使用两个指针，一次遍历，两个指针分别从前后向内部走，将0交换到前面，将2换到后面；**注意 i < right**，即2换到后面就不用再换了，并且将2换到后面后，还要继续循环判断换到前面这个值还是不是2，若是，就得继续换;

​			时间复杂度：O(n)

​			空间复杂度：O(1)



思路三：双指针法（都是从前往后走）；

​				使用两个指针，一次遍历，两个指针分别从前后向内部走，将0交换到前面，将1换到前面；若是 1，则直接与p1指针换，若是0，分两种情况，倘若p0 == p1，则直接换并且0、1指针都往后移，若 p0 < p1，则交换0指针后，就会有一个1被换出来，则需要在做一次 p1交换;

​			时间复杂度：O(n)

​			空间复杂度：O(1)



**方法一：**

```c++
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        if (n == 1)
            return;
        _sortColors(nums, 0, n - 1);
    }
    void _sortColors(vector<int>& nums, int left, int right)
    {
        if (left >= right)
            return;
        int tmpVal = nums[left];
        int low = left, high = right;
        while (low < high)
        {
            while (low < high && tmpVal <= nums[high])
                --high;
            nums[low] = nums[high];

            while (low < high && tmpVal >= nums[low])
                ++low;
            nums[high] = nums[low];
        }
        nums[low] = tmpVal;

        _sortColors(nums, left, low - 1);
        _sortColors(nums, low + 1, right);
    }
};
```



**方法二：**

```c++
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        if (n == 1)
            return;
        int ptr = 0;
        int i = 0;
        for (i = 0; i < n; ++i)
        {
            if (nums[i] == 0)
                swap(nums, i, ptr++);
        }
        ptr = n - 1;
        for (i = n - 1; i >= 0; --i)
        {
            if (nums[i] == 2)
                swap(nums, i, ptr--);
        }
    }
    void swap(vector<int>& nums, int i, int j)
    {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
};
```



**方法三：**

```c++
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        if (n == 1)
            return;
        int left = 0, right = n - 1;
        for (int i = 0; i < n; ++i)
        {
            while (nums[i] == 2 && i < right)
                swap(nums, i, right--);
            if (nums[i] == 0)
                swap(nums, i, left++);
        }
    }
    void swap(vector<int>& nums, int i, int j)
    {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
};
```



**方法四：**

```c++
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        if (n == 1)
            return;
        int p0 = 0, p1 = 0;
        for (int i = 0; i < n; ++i)
        {
            if (nums[i] == 1)
                swap(nums, i, p1++);
            else if (nums[i] == 0)
            {
                swap(nums, i, p0);
                if (p0 < p1)
                    swap(nums, i, p1);
                ++p0;
                ++p1;
            }
        }
    }
    void swap(vector<int>& nums, int i, int j)
    {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
};
```





## 0077. 组合

### 题目：

给定两个整数 `n` 和 `k`，返回范围 `[1, n]` 中所有可能的 `k` 个数的组合。

你可以按 **任何顺序** 返回答案。

**示例 1：**

```
输入：n = 4, k = 2
输出：
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
```

**示例 2：**

```
输入：n = 1, k = 1
输出：[[1]]
```

**提示：**

- `1 <= n <= 20`
- `1 <= k <= n`



**解题思路：**

递归 + 剪枝

时间复杂度：$O({n \choose k} \times k)$

空间复杂度：$O(n + k) = O(n)$

**方法：**

```c++
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        if (n < k || k == 0)
            return vector<vector<int>>();
        vector<vector<int>> res;
        vector<int> cur;
        _combine(res, cur, 1, n, k);
        return res;
    }

    void _combine(vector<vector<int>>& res, vector<int>& cur, int idx, int n, int k)
    {
        // 剪枝 ： 当前长度 + [idx, n] 的长度不够 k
        if (cur.size() + (n - idx + 1) < k)
            return;

        if (cur.size() == k)
        {
            res.push_back(cur);
            return;
        }

        // 选用idx
        cur.push_back(idx);
        _combine(res, cur, idx + 1, n, k);
        cur.pop_back();
        // 不用idx
        _combine(res, cur, idx + 1, n, k);
    }
};
```





## 0078. 子集

### 题目：

给你一个整数数组 `nums` ，数组中的元素 **互不相同** 。返回该数组所有可能的子集（幂集）。

解集 **不能** 包含重复的子集。你可以按 **任意顺序** 返回解集。

**示例 1：**

```
输入：nums = [1,2,3]
输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
```

**示例 2：**

```
输入：nums = [0]
输出：[[],[0]]
```

**提示：**

- 1 <= nums.length <= 10
- -10 <= nums[i] <= 10
- nums 中的所有元素 **互不相同**



**解题思路：**

思路一：递归回溯，每轮都选择是否将当前位置的值放入子集中，等到遍历到最后一个值后，再添加到res集合中；

思路二：用一个二进制位的数，代表某个数是否在子集中。这个方法仅限于nums数组较短的情况下；

两种方法的复杂度相同：

时间复杂度：$O(n * 2 ^ n)$

空间复杂度：$O(n)$



**方法一：**

```c++
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        int len = nums.size();
        vector<int> subSet;
        _insertSubSet(nums, subSet, res, 0);
        return res;
    }

    void _insertSubSet(vector<int>& nums, vector<int>& subSet, vector<vector<int>>& res, int i)
    {
        if (i == nums.size())
        {
            res.push_back(subSet);
            return;
        }
            
        subSet.push_back(nums[i]);
        _insertSubSet(nums, subSet, res, i + 1);
        subSet.pop_back();
        _insertSubSet(nums, subSet, res, i + 1);
    }
};
```

**方法二：**

```c++
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        int n = nums.size();
        vector<int> subSet;
        for (int i = 0; i < pow(2, n); ++i)
        {
            subSet.clear();
            for (int j = 0; j < n; ++j)
            {
                if ((i >> j) & 1)
                    subSet.push_back(nums[j]);
            }
            res.push_back(subSet);
        }
        return res;
    }
};
```





## 0079. 单词搜索

### 题目：

给定一个 `m x n` 二维字符网格 `board` 和一个字符串单词 `word` 。如果 `word` 存在于网格中，返回 `true` ；否则，返回 `false` 。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。

**示例 1：**

![leetcode_79_1](F:\C++\刷题\Img\leetcode_79_1.jpg)

```
输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
输出：true
```

**示例 2：**

![leetcode_79_2](F:\C++\刷题\Img\leetcode_79_2.jpg)

```
输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
输出：true
```

**示例 3：**

![leetcode_79_3](F:\C++\刷题\Img\leetcode_79_3.jpg)

```
输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
输出：false
```

**提示：**

- `m == board.length`
- `n = board[i].length`
- `1 <= m, n <= 6`
- `1 <= word.length <= 15`
- `board` 和 `word` 仅由大小写英文字母组成



**解题思路：**

递归 + 回溯

时间复杂度：O(mn *  3 ^ len)

空间复杂度：O(mn)

**方法：**

```c++
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (check(board, visited, i, j, word, 0))
                    return true;
            }
        }
        return false;
    }

    bool check(vector<vector<char>>& board, vector<vector<bool>>& visited, int i, int j, string& word, int idx)
    {
        if (word[idx] != board[i][j])
            return false;
        else if (idx == word.length() - 1)
            return true;
        
        visited[i][j] = true;
        vector<pair<int, int>> directions{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        bool result = false;
        for (const auto & dir : directions)
        {
            int newi = i + dir.first;
            int newj = j + dir.second;
            if (newi >= 0 && newi < board.size() && newj >= 0 && newj < board[0].size())
            {
                if (!visited[newi][newj] && check(board, visited, newi, newj, word, idx + 1))
                {
                    /*
                    bool flag = check(board, visited, newi, newj, word, idx + 1);
                    if (flag) {
                        result = true;
                        break;
                    }
                    */
                    result = true;
                    break;
                }
            }
        }
        visited[i][j] = false;
        return result;
    }
};
```





## 0080. 删除有序数组中的重复项Ⅱ

### 题目：

给你一个有序数组 `nums` ，请你 **原地** 删除重复出现的元素，使每个元素 **最多出现两次** ，返回删除后数组的新长度。

不要使用额外的数组空间，你必须在 **原地 修改输入数组** 并在使用 `O(1)` 额外空间的条件下完成。

**说明：**

为什么返回数值是整数，但输出的答案是数组呢？

请注意，输入数组是以**「引用」**方式传递的，这意味着在函数里修改输入数组对于调用者是可见的。

你可以想象内部操作如下:

```
// nums 是以“引用”方式传递的。也就是说，不对实参做任何拷贝
int len = removeDuplicates(nums);

// 在函数里修改输入数组对于调用者是可见的。
// 根据你的函数返回的长度, 它会打印出数组中 该长度范围内 的所有元素。
for (int i = 0; i < len; i++) {
    print(nums[i]);
}
```

**示例 1：**

```
输入：nums = [1,1,1,2,2,3]
输出：5, nums = [1,1,2,2,3]
解释：函数应返回新长度 length = 5, 并且原数组的前五个元素被修改为 1, 1, 2, 2, 3 。 不需要考虑数组中超出新长度后面的元素。
```

**示例 2：**

```
输入：nums = [0,0,1,1,1,1,2,3,3]
输出：7, nums = [0,0,1,1,2,3,3]
解释：函数应返回新长度 length = 7, 并且原数组的前五个元素被修改为 0, 0, 1, 1, 2, 3, 3 。 不需要考虑数组中超出新长度后面的元素。
```


**提示：**

- `1 <= nums.length <= 3 * 10^4`
- `-10^4 <= nums[i] <= 10^4`
- `nums` 已按升序排列

**解题思路：**

双指针

快慢指针都从下标 2 开始，如果 right != left - 2，则表示还没累计两个相同字符

时间复杂度：O(n)

空间复杂度：O(1)

**方法：**

```c++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if (n < 3)
            return n;
        int left = 2, right = 2;
        while (right < n)
        {
            if (nums[right] != nums[left - 2])
            {
                nums[left] = nums[right];
                ++left;
            }
            ++right;
        }
        return left;
    }
};
```





## 0081. 搜索旋转排序数组Ⅱ

### 题目：

已知存在一个按非降序排列的整数数组 `nums` ，数组中的值不必互不相同。

在传递给函数之前，`nums` 在预先未知的某个下标 `k（0 <= k < nums.length）`上进行了 **旋转** ，使数组变为 `[nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]`（下标 **从 0 开始** 计数）。例如， `[0,1,2,4,4,4,5,6,6,7]` 在下标 `5` 处经旋转后可能变为 `[4,5,6,6,7,0,1,2,4,4]` 。

给你 **旋转后** 的数组 `nums` 和一个整数 `target` ，请你编写一个函数来判断给定的目标值是否存在于数组中。如果 `nums` 中存在这个目标值 `target` ，则返回 `true` ，否则返回 `false` 。

**示例 1：**

```
输入：nums = [2,5,6,0,0,1,2], target = 0
输出：true
```

**示例 2：**

```
输入：nums = [2,5,6,0,0,1,2], target = 3
输出：false
```

**提示：**

- `1 <= nums.length <= 5000`
- `-10^4 <= nums[i] <= 10^4`
- 题目数据保证 `nums` 在预先未知的某个下标上进行了旋转
- `-10^4 <= target <= 10^4`



**解题思路：**

思路一：循环

时间复杂度：O(n)

空间复杂度：O(1)

思路二：二分查找法

时间复杂度：O(logn)

空间复杂度：O(1)



**方法：**

```c++
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int n = nums.size();
        if (n == 0)
            return false;
        if (n == 1)
            return nums[0] == target;
        
        int left = 0, right = n - 1;
        while (left <= right)
        {
            int mid = ((left + right) >> 1);
            if (nums[mid] == target)
                return true;

            if (nums[left] == nums[mid] && nums[mid] == nums[right])
            {
                ++left;
                --right;
            }
            else if (nums[mid] >= nums[left])
            {
                if (target >= nums[left] && target < nums[mid])
                    right = mid - 1;
                else
                    left = mid + 1;
            }
            else
            {
                if (target > nums[mid] && target <= nums[right])
                    left = mid + 1;
                else
                    right = mid - 1;
            }
        }
        return false;
    }
};
```





## 0084. 柱状图中最大的矩形

### 题目：

给定 *n* 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。

求在该柱状图中，能够勾勒出来的矩形的最大面积。

**示例1：**

![leetcode_84_1](F:\C++\刷题\Img\leetcode_84_1.jpg)

```
输入：heights = [2,1,5,6,2,3]
输出：10
解释：最大的矩形为图中红色区域，面积为 10
```

**示例2：**

![leetcode_84_2](F:\C++\刷题\Img\leetcode_84_2.jpg)

```
输入： heights = [2,4]
输出： 4
```

**提示：**

- `1 <= heights.length <=10^5`
- `0 <= heights[i] <= 10^4`



**解题思路：**

思路一：暴力解法

依次遍历每一个柱子，找到左边，右边最近的一个没自己高的柱子，然后计算这个柱子周边最大面积的矩形；

时间复杂度：O(n^2)

空间复杂度：O(1)

思路二：单调栈 + （常数优化）

[**单调栈（继续重点理解**）](https://leetcode-cn.com/problems/largest-rectangle-in-histogram/solution/zhu-zhuang-tu-zhong-zui-da-de-ju-xing-by-leetcode-/)

时间复杂度：O(n)

空间复杂度：O(n)



**方法一：**

```c++
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int len = heights.size();
        if (len == 1)
            return heights[0];
        int maxArea = 0;
        int left = 0;
        int right = 0;
        for (int i = 0; i < len; ++i)
        {
            left = right = i;
            while (left >= 0 && heights[left] >= heights[i])
                --left;
            ++left;
            while (right < len && heights[right] >= heights[i])
                ++right;
            --right;

            maxArea = max((right - left + 1) * heights[i], maxArea);
        }
        return maxArea;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int len = heights.size();
        if (len == 1)
            return heights[0];
        int maxArea = 0;
        vector<int> left(len, 0), right(len, 0);

        stack<int> dp_stack;
        for (int i = 0; i < len; ++i)
        {
            while (!dp_stack.empty() && heights[dp_stack.top()] >= heights[i])
                dp_stack.pop();
            left[i] = (dp_stack.empty() ? -1 : dp_stack.top());
            dp_stack.push(i);
        }
        dp_stack = stack<int>();
        for (int i = len - 1; i >= 0; --i)
        {
            while (!dp_stack.empty() && heights[i] <= heights[dp_stack.top()])
                dp_stack.pop();
            right[i] = (dp_stack.empty() ? len : dp_stack.top());
            dp_stack.push(i);
        }

        for (int i = 0; i < len; ++i)
            maxArea = max(maxArea, heights[i] * (right[i] - left[i] - 1));

        return maxArea;
    }
};
```

**方法三：**

```c++
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int len = heights.size();
        if (len == 1)
            return heights[0];
        int maxArea = 0;
        vector<int> left(len, 0), right(len, len);

        stack<int> dp_stack;
        for (int i = 0; i < len; ++i)
        {
            while (!dp_stack.empty() && heights[dp_stack.top()] >= heights[i])
            {
                right[dp_stack.top()] = i;
                dp_stack.pop();
            }
            left[i] = (dp_stack.empty() ? -1 : dp_stack.top());
            dp_stack.push(i);
        }

        for (int i = 0; i < len; ++i)
            maxArea = max(maxArea, heights[i] * (right[i] - left[i] - 1));

        return maxArea;
    }
};
```





## 0090. 子集Ⅱ

### 题目：

给你一个整数数组 `nums` ，其中可能包含重复元素，请你返回该数组所有可能的子集（幂集）。

解集 **不能** 包含重复的子集。返回的解集中，子集可以按 **任意顺序** 排列。

**示例 1：**

```
输入：nums = [1,2,2]
输出：[[],[1],[1,2],[1,2,2],[2],[2,2]]
```

**示例 2：**

```
输入：nums = [0]
输出：[[],[0]]
```

**提示：**

- `1 <= nums.length <= 10`
- `-10 <= nums[i] <= 10`



**解题思路：**

思路一：递归

时间复杂度：O(n * 2^n)

空间复杂度：O(n)

思路二：迭代 + 位运算

时间复杂度：O(n * 2^n)

空间复杂度：O(n)

**方法一：**

```c++
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> t;
        int n = nums.size();
        if (n < 1)
            return ans;
        sort(nums.begin(), nums.end());
        _subsetsWithDup(ans, t, false, 0, nums);
        return ans;
    }

    void _subsetsWithDup(vector<vector<int>>& ans, vector<int>& t, bool preChoose, int idx, vector<int>& nums)
    {
        if (idx == nums.size())
        {
            ans.push_back(t);
            return;
        }
        _subsetsWithDup(ans, t, false, idx + 1, nums);
        if (!preChoose && idx > 0 && nums[idx] == nums[idx - 1])
            return;
        t.push_back(nums[idx]);
        _subsetsWithDup(ans, t, true, idx + 1, nums);
        t.pop_back();
    }
};
```

**方法二：**

```c++
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> t;
        int n = nums.size();
        if (n < 1)
            return ans;
        sort(nums.begin(), nums.end());
        for (int mask = 0; mask < (1 << n); ++mask)
        {
            // mask表示 1 - n 位的数字分别使用和不使用
            t.clear();
            bool flag = true;
            for (int i = 0; i < n; ++i)
            {
                // 选中 i 位置
                if (mask & (1 << i))
                {
                    // 选中 i ，但没选中 i - 1 且 nums[i] == nums[i - 1]
                    if (i > 0 && ((mask >> (i - 1) & 1) == 0) && nums[i] == nums[i - 1])
                    {
                        flag = false;
                        break;
                    }
                    t.push_back(nums[i]);
                }
            }
            if (flag)
                ans.push_back(t);
        }
        return ans;
    }
};
```























# 动态规划

## 0005. 最长回文子串

### 题目：

给你一个字符串 `s`，找到 `s` 中最长的回文子串。

**示例 1：**

```
输入：s = "babad"
输出："bab"
解释："aba" 同样是符合题意的答案。
```

**示例 2：**

```
输入：s = "cbbd"
输出："bb"
```

**示例 3：**

```
输入：s = "a"
输出："a"
```

**示例 4：**

```
输入：s = "ac"
输出："a"
```

**提示：**

- 1 <= s.length <= 1000
- s 仅由数字和英文字母（大写和/或小写）组成



**解题思路：**

思路一：暴力解法

​		依次遍历每一个字串，判断是否回文，并判断是否大于当前最长记录；

​		时间复杂度：O(n^3)

​		空间复杂度：O(1)

思路二：中间扩散法

​		依次从每一个下标的 i  i  位置和 i  i+1 位置向两边扩散，寻找最长回文

​		时间复杂度：O(n^2)

​		空间复杂度：O(1)

思路三：动态规划

​		dp[i] [j] = dp[i + 1] [j - 1] && s[i] = s[j]

​		使用一个二维数组，可以先将对角线置为回文标记，然后判断每个元素与他后面紧接着的那个元素，即一共两个元素是否构成回文，再按照长度，从 3 到 len 依次判断是否有回文；

​		即，先记录单个位置回文，再记录长度为 2 的是否为回文，然后状态转移方程的边界条件就得到满足了，就可以依次判断 3 -- len长度的子串是否满足回文；

​		时间复杂度：O(n^2)

​		空间复杂度：O(n^2)

思路四：Manacher 算法



**方法一：**暴力解法

```c++
class Solution {
public:
    string longestPalindrome(string s) {
        int len = s.length();
        if (len < 2)
            return s;
        
        int maxLen = 1;
        int begin = 0;

        for (int i = 0; i < len - 1; ++i)
        {
            for ( int j = i + 1; j < len; ++j)
            {
                if (isPalindrome(s, i, j) && (j - i + 1) > maxLen)
                {
                    maxLen = j - i + 1;
                    begin = i;
                }
            }
        }
        return s.substr(begin, maxLen);
    }
    bool isPalindrome(string& s, int left, int right)
    {
        while (left < right && s[left] == s[right])
        {
            ++left;
            --right;
        }
        return (left >= right);
    }
};
```

**方法二：**中间扩散法

```c++
class Solution {
public:
    string longestPalindrome(string s) {
        int len = s.length();
        if (len < 2)
            return s;
        
        int begin = 0;
        int end = 0;
        for (int i = 0; i < len - 1; ++i)
        {
            auto [left1, right1] = isPalindrome(s, i, i);
            auto [left2, right2] = isPalindrome(s, i, i + 1);
            if (right1 - left1 > end - begin)
            {
                begin = left1;
                end = right1;
            }
            if (right2 - left2 > end - begin)
            {
                begin = left2;
                end = right2;
            }
        }
        return s.substr(begin, end - begin + 1);
    }
    pair<int, int> isPalindrome(const string& s, int left, int right)
    {
        while (left >= 0 && right < s.size() && s[left] == s[right])
        {
            --left;
            ++right;
        }
        return {left + 1, right - 1};
    }
};
```

**方法三：**动态规划

```c++
class Solution {
public:
    string longestPalindrome(string s) {
        int len = s.length();
        if (len < 2)
            return s;
        
        int maxLen = 1;
        int begin = 0;
        vector<vector<bool>> vv(len, vector<bool>(len, false));
        for (int i = 0; i < len; ++i)
        {
            vv[i][i] = true;
            if (i < len - 1 && s[i] == s[i + 1])
            {
                vv[i][i + 1] = true;
                maxLen = 2;
                begin = i;
            }
        }

        for (int l = 3; l <= len; ++l)
        {
            for (int i = 0; i + l - 1 < len; ++i)
            {
                int j = i + l - 1;
                if (s[i] == s[j] && vv[i + 1][j - 1])
                {
                    vv[i][j] = true;
                    maxLen = l;
                    begin = i;
                }
            }
        }
        
        return s.substr(begin, maxLen);
    }
};
```

**方法四：**Manacher 算法

```c++

```





## 0010. 正则表达式匹配

### 题目：

给你一个字符串 `s` 和一个字符规律 `p`，请你来实现一个支持 `'.'` 和 `'*'` 的正则表达式匹配。

- `'.'` 匹配任意单个字符
- `'*'` 匹配零个或多个前面的那一个元素
  所谓匹配，是要涵盖 **整个** 字符串 `s`的，而不是部分字符串。

**示例1：**

```
输入：s = "aa" p = "a"
输出：false
解释："a" 无法匹配 "aa" 整个字符串。
```

**示例2：**

```
输入：s = "aa" p = "a*"
输出：true
解释：因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。
```

**示例3：**

```
输入：s = "ab" p = ".*"
输出：true
解释：".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。
```

**示例4：**

```
输入：s = "aab" p = "c*a*b"
输出：true
解释：因为 '*' 表示零个或多个，这里 'c' 为 0 个, 'a' 被重复一次。因此可以匹配字符串 "aab"。
```

**示例5：**

```
输入：s = "mississippi" p = "mis*is*p*."
输出：false
```

**提示：**

- 0 <= s.length <= 20
- 0 <= p.length <= 30
- s 可能为空，且只包含从 a-z 的小写字母。
- p 可能为空，且只包含从 a-z 的小写字母，以及字符 . 和 *。
- 保证每次出现字符 * 时，前面都匹配到有效的字符



**解题思路：**

思路一：动态规划

[正则表达式匹配](https://leetcode-cn.com/problems/regular-expression-matching/solution/shi-pin-tu-jie-dong-tai-gui-hua-zheng-ze-biao-da-s/)

- 时间复杂度：O(mn)O(mn)，其中 mm 和 nn 分别是字符串 ss 和 pp 的长度。我们需要计算出所有的状态，并且每个状态在进行转移时的时间复杂度为 O(1)O(1)。
- 空间复杂度：O(mn)O(mn)，即为存储所有状态使用的空间。



**方法一：**

```c++
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.length();
        int n = p.length();
        vector<vector<bool>> statusTransTable(m + 1, vector<bool>(n + 1));
        statusTransTable[0][0] = true;

        for (int i = 1; i <= m; ++i)
            statusTransTable[i][0] = false;

        for (int j = 1; j <= n; ++j)
            statusTransTable[0][j] = (p[j - 1] == '*' && statusTransTable[0][j - 2]);
        
        for (int i = 1; i <= m; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (p[j - 1] == s[i - 1] || p[j - 1] == '.')
                    statusTransTable[i][j] = statusTransTable[i - 1][j - 1];
                else if (p[j - 1] == '*')
                {
                    if (statusTransTable[i][j - 2] == true)
                        statusTransTable[i][j] = true;
                    else if (p[j - 2] == s[i - 1] || p[j - 2] == '.')
                        statusTransTable[i][j] = statusTransTable[i - 1][j];
                }
                else
                    statusTransTable[i][j] = false;
            }
        }
        return statusTransTable[m][n];
    }
};
```





## 0022. 括号生成

### 题目：

数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。有效括号组合需满足：左括号必须以正确的顺序闭合。

**示例 1：**

```
输入：n = 3
输出：["((()))","(()())","(())()","()(())","()()()"]
```

**示例 2：**

```
输入：n = 1
输出：["()"]
```

**提示：**

- 1 <= n <= 8

**解题思路：**

思路一：暴力解法

​			依次使用递归生成各个序列，然后判断是否为合法的括号对；

- 时间复杂度：$O(2^{2n}n)$，对于 $2^{2n}$ 个序列中的每一个，我们用于建立和验证该序列的复杂度为 $O(n)$。
- 空间复杂度：$O(n)$，除了答案数组之外，我们所需要的空间取决于递归栈的深度，每一层递归函数需要 $O(1)$ 的空间，最多递归 $2n $层，因此空间复杂度为 $O(n)$。



思路二：回溯法

​	方法一还有改进的余地：我们可以只在序列仍然保持有效时才添加 '(' or ')'，而不是像 方法一 那样每次添加。我们可以通过跟踪到目前为止放置的左括号和右括号的数目来做到这一点，如果左括号数量不大于 n，我们可以放一个左括号。如果右括号数量小于左括号的数量，我们可以放一个右括号。

卡特兰数分析时间复杂度：

- 时间复杂度：$O(\dfrac{4^n}{\sqrt{n}})$，在回溯过程中，每个答案需要 $O(n)$ 的时间复制到答案数组中。
- 空间复杂度：$O(n)$，除了答案数组之外，我们所需要的空间取决于递归栈的深度，每一层递归函数需要 $O(1)$ 的空间，最多递归 $2n$ 层，因此空间复杂度为 $O(n)$。



思路三：动态规划

当我们清楚所有 `i<n` 时括号的可能生成排列后，对与 `i=n` 的情况，我们考虑整个括号排列中最左边的括号。

它一定是一个左括号，那么它可以和它对应的右括号组成一组完整的括号 `"( )"`，我们认为这一组是相比 `n-1` 增加进来的括号。

那么，剩下 `n-1` 组括号有可能在哪呢？

**【这里是重点，请着重理解】**

剩下的括号要么在这一组新增的括号内部，要么在这一组新增括号的外部**（右侧）**。

既然知道了 `i<n` 的情况，那我们就可以对所有情况进行遍历：

"(" + 【i=p时所有括号的排列组合】 + ")" + 【i=q时所有括号的排列组合】

其中 `p + q = n-1`，且 `p q` 均为非负整数。

事实上，当上述 `p` 从 `0` 取到 `n-1`，`q` 从 `n-1` 取到 `0` 后，所有情况就遍历完了。

注：上述遍历是没有重复情况出现的，即当 `(p1,q1)≠(p2,q2)` 时，按上述方式取的括号组合一定不同。

**方法一：**暴力解法

```c++
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        string parenthesis;
        _generateParenthesis(res, parenthesis, n * 2, 0);
        return res;
    }

    void _generateParenthesis(vector<string>& res, string& parenthesis, int n, int idx)
    {
        if (idx == n)
        {
            if (check(parenthesis))
                res.push_back(parenthesis);
            return;
        }
        
        parenthesis += '(';
        _generateParenthesis(res, parenthesis, n, idx + 1);
        parenthesis.pop_back();
        parenthesis += ')';
        _generateParenthesis(res, parenthesis, n, idx + 1);
        parenthesis.pop_back();
    }

    bool check(string& parenthesis)
    {
        int len = parenthesis.length();
        int num = 0;
        if (parenthesis[0] == ')' || parenthesis[len - 1] == '(')
            return false;
        for (int i = 0; i < len; ++i)
        {
            if (parenthesis[i] == '(')
                ++num;
            else if (parenthesis[i] == ')')
                --num;
            if (num < 0)
                return false;
        }
        return num == 0;
    }
};
```

**方法二：**回溯法

```c++
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        string parenthesis;
        _generateParenthesis(res, parenthesis, n, 0, 0);
        return res;
    }

    void _generateParenthesis(vector<string>& res, string& parenthesis, int n, int idx, int jdx)
    {
        if (idx == n && jdx == n)
        {
            res.push_back(parenthesis);
            return;
        }
        
        if (idx < n)
        {
            parenthesis += '(';
            _generateParenthesis(res, parenthesis, n, idx + 1, jdx);
            parenthesis.pop_back();
        }

        if (jdx < idx)
        {
            parenthesis += ')';
            _generateParenthesis(res, parenthesis, n, idx, jdx + 1);
            parenthesis.pop_back();
        }
    }
};
```

**方法三：**动态规划

```c++
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        if (n == 0)
            return {};
        if (n == 1)
            return {"()"};

        vector<vector<string>> res(n + 1);
        res[0] = {""};
        res[1] = {"()"};

        for (int i = 2; i <= n; ++i)
            for (int j = 0; j < i; ++j)
                for (auto p : res[j])
                    for (auto q : res[i - j - 1])
                        res[i].push_back(('(' + q + ')' + p));
        
        return res[n];
    }
};
```







## 0032. 最长有效括号

### 题目：

给你一个只包含 `'('` 和 `')'` 的字符串，找出最长有效（格式正确且连续）括号子串的长度。

**示例 1：**

```
输入：s = "(()"
输出：2
解释：最长有效括号子串是 "()"
```

**示例 2：**

```
输入：s = ")()())"
输出：4
解释：最长有效括号子串是 "()()"
```

**示例 3：**

```
输入：s = ""
输出：0
```

**提示：**

- 0 <= s.length <= 3 * 10^4
- s[i] 为 '(' 或 ')'



**解题思路：**

思路一：暴力解法，依次遍历每一个字串，判断是否合法

​		时间复杂度：O(n^3)

​		空间复杂度：O(1)



思路二：动态规划

​	我们定义 `dp[i]` 表示以下标 `i` 字符结尾的最长有效括号的长度。我们将 `dp` 数组全部初始化为 `0` 。显然有效的子串一定以 `‘)’` 结尾，因此我们可以知道以 `‘(’` 结尾的子串对应的 `dp` 值必定为 `0` ，我们只需要求解 `‘)’` 在 `dp` 数组中对应位置的值。

我们从前往后遍历字符串求解 `dp` 值，我们每两个字符检查一次：

- s[i]=‘)’ 且 s[i−1]=‘(’，也就是字符串形如 `“……()”`，我们可以推出：
  $$dp[i]=dp[i−2]+2$$

我们可以进行这样的转移，是因为结束部分的 `"()"` 是一个有效子字符串，并且将之前有效子字符串的长度增加了 `2` 。

- `s[i]=‘)’ 且 s[i−1]=‘)’`，也就是字符串形如 `“……))”`，我们可以推出：
  如果 `s[i−dp[i−1]−1]=‘(’`，那么
  $dp[i]=dp[i−1]+dp[i−dp[i−1]−2]+2$

我们考虑如果倒数第二个 `‘)’` 是一个有效子字符串的一部分（记作 `sub_s`），对于最后一个 `‘)’` ，如果它是一个更长子字符串的一部分，那么它一定有一个对应的 `‘(’` ，且它的位置在倒数第二个 `‘)’` 所在的有效子字符串的前面（也就是 `sub_s` 的前面）。因此，如果子字符串 `sub_s` 的前面恰好是 `‘(’` ，那么我们就用 `2` 加上 `sub_s` 的长度（`dp[i−1]`）去更新 `dp[i]`。同时，我们也会把有效子串 `“(sub_s)”` 之前的有效子串的长度也加上，也就是再加上 `dp[i−dp[i−1]−2]`。

最后的答案即为 `dp` 数组中的最大值。

​		时间复杂度：O(n)

​		空间复杂度：O(n)



思路三：栈

- 对于遇到的每个 ’(’ ，我们将它的下标放入栈中

- 对于遇到的每个 ‘)’ ，我们先弹出栈顶元素表示匹配了当前右括号：

  - 如果栈为空，说明当前的右括号为没有被匹配的右括号，我们将其下标放入栈中来更新我们之前提到的「最后一个没有被匹配的右括号的下标」
  - 如果栈不为空，当前右括号的下标减去栈顶元素即为「以该右括号为结尾的最长有效括号的长度」

  时间复杂度：O(n)

  空间复杂度：O(n)



思路四：左右指针法

​		时间复杂度：O(n)

​		空间复杂度：O(1)



**方法一：**

```c++
class Solution {
public:
    int longestValidParentheses(string s) {
        int len = s.length();
        if (len <= 1)
            return 0;
        int maxLen = 0;
        for (int i = 0; i < len - 1; ++i)
        {
            for (int j = i + 1; j < len; ++j)
            {
                if (isVaild(s, i, j) && (j - i + 1 > maxLen))
                    maxLen = j - i + 1;
            }
        }
        return maxLen;
    }
    
    bool isVaild(string s, int start, int end)
    {
        if ((end - start + 1) % 2 == 1)
            return false;
        if (s[start] == ')' || s[end] == '(')
            return false;

        int balance = 0;
        for (int i = start; i <= end; ++i)
        {
            if (s[i] == '(')
                ++balance;
            else if (s[i] == ')')
                --balance;
            
            if (balance < 0)
                return false;
        }

        return balance == 0;
    }
};
```



**方法二：**

```c++
class Solution {
public:
    int longestValidParentheses(string s) {
        int len = s.length();
        if (len <= 1)
            return 0;
        vector<int> dp(len, 0);
        int maxlen = 0;
        for (int i = 1; i < len; ++i)
        {
            if (s[i] == ')')
            {
                if (s[i - 1] == '(')
                    dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
                else if (i - dp[i - 1] - 1 >= 0 && s[i - dp[i - 1] - 1] == '(')
                    dp[i] = dp[i - 1] + ((i - dp[i - 1] - 2) >= 0 ? dp[i - dp[i - 1] - 2] : 0) + 2;

                maxlen = (maxlen > dp[i] ? maxlen : dp[i]);
            }
        }
        return maxlen;
    }
};
```

**方法三：**

```c++
class Solution {
public:
    int longestValidParentheses(string s) {
        int len = s.length();
        if (len <= 1)
            return 0;
        stack<int> st;
        st.push(-1);
        int maxlen = 0;
        for (int i = 0; i < len; ++i)
        {
            if (s[i] == '(')
                st.push(i);
            else
            {
                st.pop();
                if (st.empty())
                    st.push(i);
                else
                    maxlen = (i - st.top()) > maxlen ? (i - st.top()) : maxlen;
            }
        }
        return maxlen;
    }
};
```

**方法四：**

```c++
class Solution {
public:
    int longestValidParentheses(string s) {
        int len = s.length();
        if (len <= 1)
            return 0;
        int maxlen = 0;
        
        int left = 0, right = 0;
        for (int i = 0; i < len; ++i)
        {
            if (s[i] == '(')
                ++left;
            else if (s[i] == ')')
                ++right;

            if (left == right)
                maxlen = max(maxlen, 2 * right);
            else if (right > left)
                left = right = 0;
        }
        left = 0, right = 0;
        for (int i = len - 1; i >= 0; --i)
        {
            if (s[i] == '(')
                ++left;
            else if (s[i] == ')')
                ++right;

            if (left == right)
                maxlen = max(maxlen, 2 * left);
            else if (left > right)
                left = right = 0;
        }

        return maxlen;
    }
};
```





## 0042. 接雨水

### [同Array模块 0042题](#0042接雨水)



## 0044. 通配符匹配

### 题目：

给定一个字符串 (`s`) 和一个字符模式 (`p`) ，实现一个支持 `'?'` 和 `'*'` 的通配符匹配。

```
'?' 可以匹配任何单个字符。
'*' 可以匹配任意字符串（包括空字符串）。
```

两个字符串**完全匹配**才算匹配成功。

**说明:**

- `s` 可能为空，且只包含从 `a-z` 的小写字母。
- `p` 可能为空，且只包含从 `a-z` 的小写字母，以及字符 `?` 和 `*`。

**示例 1:**

```
输入:
s = "aa"
p = "a"
输出: false
解释: "a" 无法匹配 "aa" 整个字符串。
```

**示例 2:**

```
输入:
s = "aa"
p = "*"
输出: true
解释: '*' 可以匹配任意字符串。
```

**示例 3:**

```
输入:
s = "cb"
p = "?a"
输出: false
解释: '?' 可以匹配 'c', 但第二个 'a' 无法匹配 'b'。
```

**示例 4:**

```
输入:
s = "adceb"
p = "*a*b"
输出: true
解释: 第一个 '*' 可以匹配空字符串, 第二个 '*' 可以匹配字符串 "dce".
```

**示例 5:**

```
输入:
s = "acdcb"
p = "a*c?b"
输出: false
```





**解题思路：**

动态规划，使用二维数组，横坐标代表第 i 个 s，纵坐标代表第 j 个 p；

若当前 p[j] 等于当前 s[i] 或者 p[j] == '?'，则直接与dp[i] [j] = dp[i - 1] [j - 1]相等；

若当前 p[j] == '*'，则等于dp[i] [j] = dp[i] [j - 1] || dp[i - 1] [j]，即 * 匹配或者不匹配；

**方法：**

```c++
class Solution {
public:
    bool isMatch(string s, string p) {
        int ssize = s.length();
        int psize = p.length();

        vector<vector<bool>> dp(ssize + 1, vector<bool>(psize + 1, false));
        dp[0][0] = true;
        for (int i = 1; i <= psize; ++i)
        {
            if (p[i - 1] == '*')
                dp[0][i] = true;
            else
                break;
        }

        for (int i = 1; i <= ssize; ++i)
        {
            for (int j = 1; j <= psize; ++j)
            {
                if (s[i - 1] == p[j - 1] || p[j - 1] == '?')
                    dp[i][j] = dp[i - 1][j - 1];
                else if (p[j - 1] == '*')
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
            }
        }
        return dp[ssize][psize];
    }
};
```







## 0045. 跳跃游戏Ⅱ

### 同 Array 模块下 0045





## 0053. 最大子序和

### 同 Array 模块下 0053





## 0055. 跳跃游戏

### 同 Array 模块下 0055





## 0062. 不同路径

### 同 Array 模块下 0062





## 0063. 不同路径Ⅱ

### 同 Array 模块下 0063





## 0064. 最小路径和

### 同 Array 模块下 0064





## 0070. 爬楼梯

### 题目：

假设你正在爬楼梯。需要 *n* 阶你才能到达楼顶。

每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

注意：给定 *n* 是一个正整数。

**示例 1：**

```
输入： 2
输出： 2
解释： 有两种方法可以爬到楼顶。
1.  1 阶 + 1 阶
2.  2 阶
```

**示例 2：**

```
输入： 3
输出： 3
解释： 有三种方法可以爬到楼顶。
1.  1 阶 + 1 阶 + 1 阶
2.  1 阶 + 2 阶
3.  2 阶 + 1 阶
```

**解题思路：**

爬楼梯的思路类似于斐波那契数列；

前者是自顶向下，后者是自底向上；

做法都一样；

循环、递归、快速幂阵法、公式推导法；

**方法一：**递归

```c++
class Solution {
public:
    int climbStairs(int n) {
        int count = 0;
        _climbStairs(n, count);
        return count;
    }

    void _climbStairs(int n, int& count) 
    {
        if (n <= 0)
        {
            if (n == 0)
                ++count;
            return;
        }

        _climbStairs(n - 1, count);
        _climbStairs(n - 2, count);
    }
};
```

**方法二：**循环

```c++
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2)
            return n;
        int a = 1, b = 2, c = 0;
        for (int i = 2; i < n; ++i)
        {
            c = a + b;
            a = b;
            b = c;
        }
                
        return c;
    }
};
```

**方法三：**快速幂阵法

```c++
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2)
            return n;
        
        vector<vector<long>> m = {{1, 1}, {1, 0}};
        vector<vector<long>> ret = matrix_pow(m, n - 2);
                
        return 2 * ret[0][0] + ret[0][1];
    }

    vector<vector<long>> matrix_pow(vector<vector<long>>& a, int n)
    {
        vector<vector<long>> ret = {{1, 0}, {0, 1}};
        while (n > 0)
        {
            if (n & 1)
                ret = matrix_multiply(ret, a);
            n >>= 1;
            a = matrix_multiply(a, a);
        }
        return ret;
    }

    vector<vector<long>> matrix_multiply(vector<vector<long>>& a, vector<vector<long>>& b)
    {
        vector<vector<long>> ret = {{0, 0}, {0, 0}};
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                ret[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j];
        return ret;
    }
};
```





## 0072. 编辑距离

### 题目：

给你两个单词 `word1` 和 `word2`，请你计算出将 `word1` 转换成 `word2` 所使用的最少操作数 。

你可以对一个单词进行如下三种操作：

- 插入一个字符
- 删除一个字符
- 替换一个字符

**示例 1：**

```
输入：word1 = "horse", word2 = "ros"
输出：3
解释：
horse -> rorse (将 'h' 替换为 'r')
rorse -> rose (删除 'r')
rose -> ros (删除 'e')
```

**示例 2：**

```
输入：word1 = "intention", word2 = "execution"
输出：5
解释：
intention -> inention (删除 't')
inention -> enention (将 'i' 替换为 'e')
enention -> exention (将 'n' 替换为 'x')
exention -> exection (将 'n' 替换为 'c')
exection -> execution (插入 'u')
```

**提示：**

- `0 <= word1.length, word2.length <= 500`
- `word1` 和 `word2` 由小写英文字母组成



**解题思路：**

思路一：自顶向下递归

当任意一个子串长处为 0 ，则只需要再删除另外一个字串长度数即可；

当两个子串最后一个字母相同，则只需要比较前面的即可；

当两个子串最后一个字母不相同，可以选择删除掉第一个字串最后一个，然后比较前面；

​													可以选择在第二个后面添加一个，抵消后再比较前面的；

​													或者替换后抵消，再比较前面的；



思路二：自底向上动态规划

使用一个二维数组dp[len1 + 1] [len2 + 1]，表示子串1第 0-i匹配子串2第0-j需要执行多少步；

初始化：二维矩阵第一行第一列依次初始化为 0-len（表示移除一个子串，匹配一个空串，细品）

状态转移方程：

​			如果当前word[i - 1] == word[j - 1]

​					dp[i] [j] = dp[i - 1] [j - 1];

​			否则  

​					dp[i] [j] = min(dp[i - 1] [j - 1], dp[i - 1] [j], dp[i] [j - 1]);  // 分别表示递归的最后三种子选项





**方法一：**递归

```c++
class Solution {
public:
    int minDistance(string word1, string word2) {
        if (word1.length() == 0 || word2.length() == 0)
            return max(word1.length(), word2.length());
        
        if (word1.back() == word2.back())
        {
            return minDistance(word1.substr(0, word1.length() - 1), word2.substr(0, word2.length() - 1));
        }

        return 1 + min(
            minDistance(word1, word2.substr(0, word2.length() - 1)),
            min(minDistance(word1.substr(0, word1.length() - 1), word2),
            minDistance(word1.substr(0, word1.length() - 1), word2.substr(0, word2.length() - 1)))
        );
    }
};
```

**方法二：**动态规划

```c++
class Solution {
public:
    int minDistance(string word1, string word2) {
        int len1 = word1.length();
        int len2 = word2.length();

        if (len1 * len2 == 0)
            return len1 + len2;
        
        vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
        for (int i = 0; i < len1 + 1; ++i)
            dp[i][0] = i;
        for (int i = 0; i < len2 + 1; ++i)
            dp[0][i] = i;

        for (int i = 1; i < len1 + 1; ++i)
        {
            for (int j = 1; j < len2 + 1; ++j)
            {
                if (word1[i - 1] == word2[j - 1])  // 字符串下标要比dp数组下少 1
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    dp[i][j] = 1 + min(dp[i - 1][j - 1], min(dp[i][j - 1], dp[i - 1][j]));
            }
        }

        return dp[len1][len2];
    }
};
```





## 0085. 最大矩形

### 题目：

给定一个仅包含 `0` 和 `1` 、大小为 `rows x cols` 的二维二进制矩阵，找出只包含 `1` 的最大矩形，并返回其面积。

**示例1：**

![leetcode_85](F:\C++\刷题\Img\leetcode_85.jpg)

```
输入：matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
输出：6
解释：最大矩形如上图所示。
```

**示例 2：**

```
输入：matrix = []
输出：0
```

**示例 3：**

```
输入：matrix = [["0"]]
输出：0
```

**示例 4：**

```
输入：matrix = [["1"]]
输出：1
```

**示例 5：**

```
输入：matrix = [["0","0"]]
输出：0
```

**提示：**

- `rows == matrix.length`
- `cols == matrix[0].length`
- `0 <= row, cols <= 200`
- `matrix[i][j] 为 '0' 或 '1'`



**解题思路：**

思路一：暴力解法

依次遍历每一个位置，并将同行前可累加的连续值累加起来；

在某一个特定位置，以这个位置为右下角（以当前行为底），然后依次向上遍历，向上遍历过程中，宽度只可能比当前行的连续宽窄，高度可以增加，因为底已经决定了宽度；

用一个二维数组，存储下每个位置在当前行前面可以遇到最大宽度；

时间复杂度：O(m^2 * n)

空间复杂度：O(mn)

思路二：84题的单调栈 + 每一列积累

遍历每一行时，每一个元素可以和上面的积累成最大连续高度，就可以组成一个以当前行为底，高度为累加的条形图，然后就可以调用单调栈，计算每次条形图的最大矩形面积；

![leetcode_85_1](F:\C++\刷题\Img\leetcode_85_1.png)

时间复杂度：O(mn)

空间复杂度：O(n)

思路三：动态规划

[还需再理解](https://leetcode-cn.com/problems/maximal-rectangle/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-1-8/)

时间复杂度：O(mn)

空间复杂度：O(n)



**方法一：**

```c++
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int rows = matrix.size();
        if (rows == 0)
            return 0;
        int cols = matrix[0].size();
        
        vector<vector<int>> dp(rows, vector<int>(cols, 0));
        int maxArea = 0;

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (matrix[i][j] == '1')
                {
                    if (j == 0)
                        dp[i][j] = 1;
                    else
                        dp[i][j] = dp[i][j - 1] + 1;
                }
                else
                {
                    dp[i][j] = 0;
                }

                int minWidth = dp[i][j];
                for (int up_i = i; up_i >= 0; --up_i)
                {
                    int height = i - up_i + 1;
                    minWidth = min(minWidth, dp[up_i][j]);
                    maxArea = max(maxArea, height * minWidth);
                }
            }
        }
        return maxArea;
    }
};
```

**方法二：**

```c++
// 整合顺序栈
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int rows = matrix.size();
        if (rows == 0)
            return 0;
        int cols = matrix[0].size();
        vector<int> dp(cols, 0);
        int maxArea = 0;

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (matrix[i][j] == '1')
                    dp[j] = (i == 0 ? 0 : dp[j]) + 1;
                else
                    dp[j] = 0;
            }

            vector<int> left(cols, 0), right(cols, cols);
            stack<int> dp_stack;
            for (int j = 0; j < cols; ++j)
            {
                while (!dp_stack.empty() && dp[dp_stack.top()] >= dp[j])
                {
                    right[dp_stack.top()] = j;
                    dp_stack.pop();
                }
                left[j] = (dp_stack.empty() ? -1 : dp_stack.top());
                dp_stack.push(j);
            }
            for (int j = 0; j < cols; ++j)
                maxArea = max(maxArea, dp[j] * (right[j] - left[j] - 1));
        }

        return maxArea;
    }
};

// 调用顺序栈柱状函数
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int len = heights.size();
        if (len == 1)
            return heights[0];
        int maxArea = 0;
        vector<int> left(len, 0), right(len, len);
        stack<int> dp_stack;
        for (int i = 0; i < len; ++i)
        {
            while (!dp_stack.empty() && heights[dp_stack.top()] >= heights[i])
            {
                right[dp_stack.top()] = i;
                dp_stack.pop();
            }
            left[i] = (dp_stack.empty() ? -1 : dp_stack.top());
            dp_stack.push(i);
        }
        for (int i = 0; i < len; ++i)
            maxArea = max(maxArea, heights[i] * (right[i] - left[i] - 1));
        
        return maxArea;
    }

    int maximalRectangle(vector<vector<char>>& matrix) {
        int rows = matrix.size();
        if (rows == 0)
            return 0;
        int cols = matrix[0].size();
        
        vector<int> dp(cols, 0);
        int maxArea = 0;

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (matrix[i][j] == '1')
                    dp[j] = (i == 0 ? 0 : dp[j]) + 1;
                else
                    dp[j] = 0;
            }

            maxArea = max(maxArea, largestRectangleArea(dp));
        }

        return maxArea;
    }
};
```

**方法三：**

```c++
// 方法三：动态规划
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int rows = matrix.size();
        if (rows == 0)
            return 0;
        int cols = matrix[0].size();
        vector<int> heights(cols, 0);
        vector<int> left(cols, -1), right(cols, cols);
        int maxArea = 0;

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (matrix[i][j] == '1')
                    heights[j] += 1;
                else
                    heights[j] = 0;
            }

            int boundary = -1;
            for (int j = 0; j < cols; ++j)
            {
                if (matrix[i][j] == '1')
                    left[j] = max(left[j], boundary);
                else
                {
                    left[j] = -1;
                    boundary = j;
                }
            }

            boundary = cols;
            for (int j = cols - 1; j >= 0; --j)
            {
                if (matrix[i][j] == '1')
                    right[j] = min(right[j], boundary);
                else
                {
                    right[j] = cols;
                    boundary = j;
                }
            }

            for (int j = 0; j < cols; ++j)
                maxArea = max(maxArea, heights[j] * (right[j] - left[j] - 1));
        }

        return maxArea;
    }
};

```







## 0087. 扰乱字符串

### 题目：

使用下面描述的算法可以扰乱字符串 `s` 得到字符串 `t` ：

1. 如果字符串的长度为 1 ，算法停止
2. 如果字符串的长度 > 1 ，执行下述步骤：
   - 在一个随机下标处将字符串分割成两个非空的子字符串。即，如果已知字符串 `s` ，则可以将其分成两个子字符串 `x` 和 `y` ，且满足 `s = x + y` 。
   - **随机** 决定是要「交换两个子字符串」还是要「保持这两个子字符串的顺序不变」。即，在执行这一步骤之后，`s` 可能是 `s = x + y` 或者 `s = y + x` 。
   - 在 `x` 和 `y` 这两个子字符串上继续从步骤 1 开始递归执行此算法。

给你两个 `长度相等` 的字符串 `s1` 和 `s2`，判断 `s2` 是否是 `s1` 的扰乱字符串。如果是，返回 `true` ；否则，返回 `false` 。

**示例 1：**

```
输入：s1 = "great", s2 = "rgeat"
输出：true
解释：s1 上可能发生的一种情形是：
"great" --> "gr/eat" // 在一个随机下标处分割得到两个子字符串
"gr/eat" --> "gr/eat" // 随机决定：「保持这两个子字符串的顺序不变」
"gr/eat" --> "g/r / e/at" // 在子字符串上递归执行此算法。两个子字符串分别在随机下标处进行一轮分割
"g/r / e/at" --> "r/g / e/at" // 随机决定：第一组「交换两个子字符串」，第二组「保持这两个子字符串的顺序不变」
"r/g / e/at" --> "r/g / e/ a/t" // 继续递归执行此算法，将 "at" 分割得到 "a/t"
"r/g / e/ a/t" --> "r/g / e/ a/t" // 随机决定：「保持这两个子字符串的顺序不变」
算法终止，结果字符串和 s2 相同，都是 "rgeat"
这是一种能够扰乱 s1 得到 s2 的情形，可以认为 s2 是 s1 的扰乱字符串，返回 true
```

**示例 2：**

```
输入：s1 = "abcde", s2 = "caebd"
输出：false
```

**示例 3：**

```
输入：s1 = "a", s2 = "a"
输出：true
```

**提示：**

- `s1.length == s2.length`
- `1 <= s1.length <= 30`
- `s1` 和 `s2` 由小写英文字母组成



**解题思路：**

[扰乱字符串](https://leetcode-cn.com/problems/scramble-string/solution/miao-dong-de-qu-jian-xing-dpsi-lu-by-sha-yu-la-jia/)

时间复杂度：O(n^4)

空间复杂度：O(n^3)

**方法：**

```c++
class Solution {
public:
    bool isScramble(string s1, string s2) {
        int m = s1.length();
        int n = s2.length();
        if (m != n)
            return false;
        
        vector<vector<vector<bool>>> dp(n, vector(n, vector(n + 1, false)));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                dp[i][j][1] = (s1[i] == s2[j]);
            
        for (int len = 2; len <= n; ++len)
            for (int i = 0; i <= n - len; ++i)
                for (int j = 0; j <= n - len; ++j)
                    for (int k = 1; k <= len - 1; ++k)
                        if ((dp[i][j][k] && dp[i + k][j + k][len - k]) || (dp[i][len + j - k][k] && dp[i + k][j][len - k]))
                        {
                            dp[i][j][len] = true;
                            break;
                        }
        return dp[0][0][n];
    }
};
```







## 0091. 解码方法

### 题目：

一条包含字母 `A-Z` 的消息通过以下映射进行了 **编码** ：

```
'A' -> 1
'B' -> 2
...
'Z' -> 26
```

要 `解码` 已编码的消息，所有数字必须基于上述映射的方法，反向映射回字母（可能有多种方法）。例如，`"11106"` 可以映射为：

- `"AAJF"` ，将消息分组为 `(1 1 10 6)`
- `"KJF"` ，将消息分组为 `(11 10 6)`

注意，消息不能分组为  `(1 11 06)` ，因为 `"06"` 不能映射为 `"F"` ，这是由于 `"6"` 和 `"06"` 在映射中并不等价。

给你一个只含数字的 **`非空`** 字符串 `s` ，请计算并返回 **解码** 方法的 **总数** 。

题目数据保证答案肯定是一个 **32 位** 的整数。

**示例 1：**

```
输入：s = "12"
输出：2
解释：它可以解码为 "AB"（1 2）或者 "L"（12）。
```

**示例 2：**

```
输入：s = "226"
输出：3
解释：它可以解码为 "BZ" (2 26), "VF" (22 6), 或者 "BBF" (2 2 6) 。
```

**示例 3：**

```
输入：s = "0"
输出：0
解释：没有字符映射到以 0 开头的数字。
含有 0 的有效映射是 'J' -> "10" 和 'T'-> "20" 。
由于没有字符，因此没有有效的方法对此进行解码，因为所有数字都需要映射。
```

**示例 4：**

```
输入：s = "06"
输出：0
解释："06" 不能映射到 "F" ，因为字符串含有前导 0（"6" 和 "06" 在映射中并不等价）。
```

**提示：**

- `1 <= s.length <= 100`
- `s` 只包含数字，并且可能包含前导零。



**解题思路：**

动态规划：

从第二个字母开始，依次遍历每一个；

当前遍历的字母，前一个可能是单独解码成一个（前提是不为0），也可能是前两个解码为一个（前提是 i > 1 && 第一位不为0 && 两位 <= 26），因此当前位置表示前面可以解码多少种，为这两种之和；

使用滚动数组，注意for循环的右边界，必须遍历至字符串长度+1的位置，才可以计算到整个字符串；

时间复杂度：O(n)

空间复杂度：O(1)



**方法：**

```c++
class Solution {
public:
    int numDecodings(string s) {
        int len = s.length();

        int a = 0, b = 1, c;
        for (int i = 1; i <= len; ++i)
        {
            c = 0;
            if (s[i - 1] != '0')
                c += b;
            if (i > 1 && s[i - 2] != '0' && (10 * (s[i - 2] - '0') + (s[i - 1] - '0')) <= 26)
                c += a;
            tie(a, b) = {b, c};
        }
        return c;
    }
};
```







## 0095. 不同的二叉搜索树Ⅱ

### 题目：

给你一个整数 `n` ，请你生成并返回所有由 `n` 个节点组成且节点值从 `1` 到 `n` 互不相同的不同 **二叉搜索树** 。可以按 **任意顺序** 返回答案。

**示例1：**

![leetcode_95](F:\C++\刷题\Img\leetcode_95.jpg)

```
输入：n = 3
输出：[[1,null,2,null,3],[1,null,3,2],[2,1,3],[3,1,null,null,2],[3,2,null,1]]
```

**示例 2：**

```
输入：n = 1
输出：[[1]]
```

**提示：**

- `1 <= n <= 8`



**解题思路：**

我们定义 `generateTrees(start, end)` 函数表示当前值的集合为 $[\textit{start},\textit{end}]$，返回序列 $[\textit{start},\textit{end}]$生成的所有可行的二叉搜索树。按照上文的思路，我们考虑枚举 $[\textit{start},\textit{end}]$ 中的值 $i$ 为当前二叉搜索树的根，那么序列划分为了 $[\textit{start},i-1]$ 和 $[i+1,\textit{end}]$ 两部分。我们递归调用这两部分，即 `generateTrees(start, i - 1)` 和 `generateTrees(i + 1, end)`，获得所有可行的左子树和可行的右子树，那么最后一步我们只要从可行左子树集合中选一棵，再从可行右子树集合中选一棵拼接到根节点上，并将生成的二叉搜索树放入答案数组即可。

递归的入口即为 `generateTrees(1, n)`，出口为当 $\textit{start}>\textit{end}$ 的时候，当前二叉搜索树为空，返回空节点即可。



**方法：**

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        if (n)
            return generateTrees(1, n);
        else
            return vector<TreeNode*>{};
    }

    vector<TreeNode*> generateTrees(int left, int right) 
    {
        vector<TreeNode*> res;
        if (left > right)
        {
            res.push_back(nullptr);
            return res;
        }

        for (int i = left; i <= right; ++i)
        {
            vector<TreeNode*> leftTrees = generateTrees(left, i - 1);
            vector<TreeNode*> rightTrees = generateTrees(i + 1, right);

            for (TreeNode* leftNode : leftTrees)
            {
                for (TreeNode* rightNode : rightTrees)
                {
                    TreeNode* root = new TreeNode(i);
                    root->left = leftNode;
                    root->right = rightNode;
                    res.push_back(root);
                }
            }
        }
        return res;
    }
};
```









## 0096. 不同的二叉搜索树

### 题目：

给你一个整数 `n` ，求恰由 `n` 个节点组成且节点值从 `1` 到 `n` 互不相同的 **二叉搜索树** 有多少种？返回满足题意的二叉搜索树的种数。

**示例1：**

![leetcode_96_1](F:\C++\刷题\Img\leetcode_96_1.jpg)

```
输入：n = 3
输出：5
```

**示例 2：**

```
输入：n = 1
输出：1
```

**提示：**

- `1 <= n <= 19`



**解题思路：**

思路一：动态规划

假设 $n$ 个节点存在二叉排序树的个数是 $G(n)$，令 $f(i)$ 为以 $i$ 为根的二叉搜索树的个数

即有:$G(n) = f(1) + f(2) + f(3) + f(4) + ... + f(n)$

$n$ 为根节点，当 $i$ 为根节点时，其左子树节点个数为 $[1,2,3,...,i-1]$，右子树节点个数为$[i+1,i+2,...n]$，所以当i为根节点时，其左子树节点个数为 $i-1$ 个，右子树节点为$n-i$，即$f(i) = G(i-1)*G(n-i)$,

上面两式可得:$G(n) = G(0)*G(n-1)+G(1)*(n-2)+...+G(n-1)*G(0)$

时间复杂度：O(n)

空间复杂度：O(n)

思路二：组合数学（卡特兰数）

$C_0=1,C_{n+1}=\frac {2(2n+1)}{n+2}C_n$

时间复杂度：O(n)

空间复杂度：O(1)



**方法一：**

```c++
class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n + 1, 0);
        dp[0] = dp[1] = 1;
        for (int i = 2; i <= n; ++i)
            for (int j = 1; j <= i; ++j)
                dp[i] += dp[j - 1] * dp[i - j];
        return dp[n];
    }
};
```

**方法二：**

```c++
class Solution {
public:
    int numTrees(int n) {
        long long C = 1;
        for (int i = 0; i < n; ++i)
            C = C * 2 * (2 * i + 1) / (i + 2);

        return C;
    }
};
```







## 0097. 交错字符串

### 题目：

给定三个字符串 `s1、s2、s3`，请你帮忙验证 `s3` 是否是由 `s1` 和 `s2` **交错** 组成的。

两个字符串 `s` 和 `t` **交错** 的定义与过程如下，其中每个字符串都会被分割成若干 **非空** 子字符串：

- `s = s1 + s2 + ... + sn`
- `t = t1 + t2 + ... + tm`
- `|n - m| <= 1`
- **交错** 是 `s1 + t1 + s2 + t2 + s3 + t3 + ...` 或者 `t1 + s1 + t2 + s2 + t3 + s3 + ...`
- **提示**：`a + b` 意味着字符串 `a` 和 `b` 连接。

**示例1：**

![leetcode_97](F:\C++\刷题\Img\leetcode_97.jpg)

```
输入：s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
输出：true
```

**示例 2：**

```
输入：s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
输出：false
```

**示例 3：**

```
输入：s1 = "", s2 = "", s3 = ""
输出：true
```

**提示：**

- `0 <= s1.length, s2.length <= 100
- `0 <= s3.length <= 200`
- `s1、s2、和 s3` 都由小写英文字母组成



**解题思路：**

首先如果 $|s_1| + |s_2| \neq |s_3|$∣，那 $s_3$  必然不可能由 $s_1$ 和 $s_2$ 交错组成。在 $|s_1| + |s_2| = |s_3|$ 时，我们可以用动态规划来求解。我们定义 $f(i, j)$ 表示 $s_1$ 的前 $i$ 个元素和 $s_2$ 的前 $j$ 个元素是否能交错组成 $s_3$ 的前 $i + j$ 个元素。如果 $s_1$ 的第 $i$ 个元素和 $s_3$ 的第 $i + j$ 个元素相等，那么 $s_1$ 的前 $i$ 个元素和 $s_2$ 的前 $j$ 个元素是否能交错组成 $s_3$ 的前 $i + j$ 个元素取决于 $s_1$ 的前 i - 1i−1 个元素和 $s_2$ 的前 $j$ 个元素是否能交错组成 $s_3$ 的前 $i + j - 1$ 个元素，即此时 $f(i, j)$ 取决于 $f(i - 1, j)$，在此情况下如果 $f(i - 1, j)$ 为真，则 $f(i, j)$ 也为真。同样的，如果 $s_2$ 的第 $j$ 个元素和 $s_3$ 的第 $i + j$ 个元素相等并且 $f(i, j - 1)$ 为真，则 $f(i, j)$ 也为真。于是我们可以推导出这样的动态规划转移方程：

$f(i, j) = [f(i - 1, j) \, {\rm and} \, s_1(i - 1) = s_3(p)] \, {\rm or} \, [f(i, j - 1) \, {\rm and} \, s_2(j - 1) = s_3(p)]$

其中 $p = i + j - 1$。边界条件为 $f(0, 0) = {\rm True}$。至此，我们很容易可以给出这样一个实现：



时间复杂度：O(mn)

空间复杂度：O(mn)   -> 滚动数组  O(n)



**方法：**

```c++
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int len1 = s1.length();
        int len2 = s2.length();
        int len3 = s3.length();
        if (len1 + len2 != len3)
            return false;

        vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, false));
        dp[0][0] = true;
        for (int i = 0; i <= len1; ++i)
        {
            for (int j = 0; j <= len2; ++j)
            {
                int p = i + j - 1;
                if (i > 0)
                    dp[i][j] |= (dp[i - 1][j] && (s1[i - 1] == s3[p]));
                if (j > 0)
                    dp[i][j] |= (dp[i][j - 1] && (s2[j - 1] == s3[p]));
            }
        }
        return dp[len1][len2];
    }
};

// 滚动数组
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int len1 = s1.length();
        int len2 = s2.length();
        int len3 = s3.length();
        if (len1 + len2 != len3)
            return false;

        vector<int> dp(len2 + 1, false);
        dp[0] = true;
        for (int i = 0; i <= len1; ++i)
        {
            for (int j = 0; j <= len2; ++j)
            {
                int p = i + j - 1;
                if (i > 0)
                    dp[j] &= (s1[i - 1] == s3[p]);
                if (j > 0)
                    dp[j] |= (dp[j - 1] && (s2[j - 1] == s3[p]));
            }
        }
        return dp[len2];
    }
};
```







## 0118. 杨辉三角

### 题目：

给定一个非负整数 *`numRows`，*生成「杨辉三角」的前 *`numRows`* 行。

在「杨辉三角」中，每个数是它左上方和右上方的数的和。

![leetcode_118](F:\C++\刷题\Img\leetcode_118.gif)

**示例 1:**

```
输入: numRows = 5
输出: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
```

**示例 2:**

```
输入: numRows = 1
输出: [[1]]
```

**提示:**

- `1 <= numRows <= 30`



**解题思路：**

常规思路

时间复杂度：O(n^2)

空间复杂度：O(1)  返回数组不算



**方法：**

```c++
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        
        vector<vector<int>> res(numRows);
        for (int i = 0; i < numRows; ++i)
        {
            res[i].resize(i + 1);
            res[i][0] = res[i][i] = 1;
            for (int j = 1; j < i; ++j)
                res[i][j] = res[i - 1][j - 1] + res[i - 1][j];
        }
        return res;
    }
};
```





## 0119. 杨辉三角Ⅱ

### 题目：

给定一个非负索引 `rowIndex`，返回「杨辉三角」的第 `rowIndex` 行。

在「杨辉三角」中，每个数是它左上方和右上方的数的和。

**示例 1:**

```
输入: rowIndex = 3
输出: [1,3,3,1]
```

**示例 2:**

```
输入: rowIndex = 0
输出: [1]
```

**示例 3:**

```
输入: rowIndex = 1
输出: [1,1]
```

**提示:**

- `0 <= rowIndex <= 33`



**解题思路：**

思路一：动态规划

使用一个定长数组（rowIndex + 1），然后按照常规杨辉三角的双层循环依次赋值；

注意：在使用滚动数组时，要注意数组的值会不会被重复使用，重复使用时会不会造成影响

比如$res[j] = res[j - 1] + res[j];$，在遍历每一行时，当前值需要依靠一个，后一个值需要依靠当前值，如果先修改当前值，会对后一个值的修改造成影响，**因此内层循环采用从后往前的顺序来赋值**；

时间复杂度：O(n^2)

空间复杂度：O(1) 

思路二：组合数学

由组合数公式 $\mathcal{C}_n^m=\dfrac{n!}{m!(n-m)!}$ ，可以得到同一行的相邻组合数的关系

$\mathcal{C}_n^m= \mathcal{C}_n^{m-1} \times \dfrac{n-m+1}{m}$

由于 $\mathcal{C}_n^0=1$，利用上述公式我们可以在线性时间计算出第 nn 行的所有组合数。

时间复杂度：O(n)

空间复杂度：O(1) 



**方法一：**动态规划

```c++
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> res(rowIndex + 1);
        for (int i = 0; i <= rowIndex; ++i)
        {
            res[0] = res[i] = 1;
            for (int j = i - 1; j > 0; --j)
                res[j] = res[j - 1] + res[j];
        }
        return res;
    }
};
```

**方法二：**组合数学

```c++
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> res(rowIndex + 1);
        res[0] = 1;
        for (int i = 1; i <= rowIndex; ++i)
            res[i] = 1LL * res[i - 1] * (rowIndex - i + 1) / i;
        return res;
    }
};
```







## 0120. 三角形最小路径和

### 题目：

给定一个三角形 `triangle` ，找出自顶向下的最小路径和。

每一步只能移动到下一行中相邻的结点上。**相邻的结点** 在这里指的是 **下标** 与 **上一层结点下标** 相同或者等于 **上一层结点下标 + 1** 的两个结点。也就是说，如果正位于当前行的下标 `i` ，那么下一步可以移动到下一行的下标 `i` 或 `i + 1` 。

**示例 1：**

```
输入：triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
输出：11
解释：如下面简图所示：
   2
  3 4
 6 5 7
4 1 8 3
自顶向下的最小路径和为 11（即，2 + 3 + 5 + 1 = 11）。
```

**示例 2：**

```
输入：triangle = [[-10]]
输出：-10
```

**提示：**

- `1 <= triangle.length <= 200`
- `triangle[0].length == 1`
- `triangle[i].length == triangle[i - 1].length + 1`
- `-10^4 <= triangle[i][j] <= 10^4`



**解题思路：**

思路类似于931题

时间复杂度：O(n^2)

空间复杂度：O(n) 



**方法：**

```c++
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        if (n == 1)
            return triangle[0][0];
        
        vector<int> dp;
        dp.resize(1);
        dp[0] = triangle[0][0];

        for (int i = 1; i < n; ++i)
        {
            dp.resize(i + 1);
            for (int j = i; j >= 0; --j)
            {
                if (j == i)
                    dp[j] = triangle[i][j] + dp[j - 1];
                else if (j == 0)
                    dp[j] = triangle[i][j] + dp[0];
                else
                    dp[j] = triangle[i][j] + min(dp[j], dp[j - 1]);
            }
        }
        
        return *min_element(dp.begin(), dp.end());;
    }
};
```









## 0121. 买卖股票的最佳时机

### 题目：

给定一个数组 `prices` ，它的第 `i` 个元素 `prices[i]` 表示一支给定股票第 `i` 天的价格。

你只能选择 **某一天** 买入这只股票，并选择在 **未来的某一个不同的日子** 卖出该股票。设计一个算法来计算你所能获取的最大利润。

返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 `0` 。

**示例 1：**

```
输入：[7,1,5,3,6,4]
输出：5
解释：在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。
```

**示例 2：**

```
输入：prices = [7,6,4,3,1]
输出：0
解释：在这种情况下, 没有交易完成, 所以最大利润为 0。
```

**提示：**

- `1 <= prices.length <= 10^5`
- `0 <= prices[i] <= 10^4`



**解题思路：**

思路一：自后往前

方法等同于 1014 题，记录当前右边最大值，依次向前遍历，找到差值最大的一组，并记录；

思路二：自前往后

时间复杂度：O(n)

空间复杂度：O(1)



**方法一：**自后往前

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if (len == 1)
            return 0;
        int mx = prices[len - 1];
        int ans = 0;
        for (int i = len - 2; i >= 0; --i)
        {
            ans = max(ans, mx - prices[i]);
            mx = max(mx, prices[i]);
        }
        return ans;
    }
};
```

**方法二：**自前往后

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if (len == 1)
            return 0;
        int mn = prices[0];
        int ans = 0;
        for (int i = 1; i < len; ++i)
        {
            ans = max(ans, prices[i] - mn);
            mn = min(mn, prices[i]);
        }
        return ans;
    }
};
```





## 0122. 买卖股票的最佳时机Ⅱ

### 题目：

给定一个数组 `prices` ，其中 `prices[i]` 是一支给定股票第 `i` 天的价格。

设计一个算法来计算你所能获取的最大利润。你可以尽可能地完成更多的交易（多次买卖一支股票）。

**注意**：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

**示例 1:**

```
输入: prices = [7,1,5,3,6,4]
输出: 7
解释: 在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。
     随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6-3 = 3 。
```

**示例 2:**

```
输入: prices = [1,2,3,4,5]
输出: 4
解释: 在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。
     注意你不能在第 1 天和第 2 天接连购买股票，之后再将它们卖出。因为这样属于同时参与了多笔交易，你必须在再次购买前出售掉之前的股票。
```

**示例 3:**

```
输入: prices = [7,6,4,3,1]
输出: 0
解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。
```

**提示：**

- `1 <= prices.length <= 3 * 10^4`
- `0 <= prices[i] <= 10^4`



**解题思路：**

思路一：贪心算法

只要今天比昨天有得赚，就卖

思路二：动态规划

**每天交易结束后只可能存在手里有一支股票或者没有股票的状态**。

定义状态 $\textit{dp}[i][0]$ 表示第 $i$ 天交易完后手里没有股票的最大利润，$\textit{dp}[i][1]$ 表示第 $i$天交易完后手里持有一支股票的最大利润（$i$从 $0$ 开始）。

考虑 $\textit{dp}[i][0]$ 的转移方程，如果这一天交易完后手里没有股票，那么可能的转移状态为前一天已经没有股票，即 $\textit{dp}[i-1][0]$，或者前一天结束的时候手里持有一支股票，即 $\textit{dp}[i-1][1]$，这时候我们要将其卖出，并获得 $\textit{prices}[i]$ 的收益。因此为了收益最大化，我们列出如下的转移方程：

$$\textit{dp}[i][0]=\max\{\textit{dp}[i-1][0],\textit{dp}[i-1][1]+\textit{prices}[i]\}$$

再来考虑 $\textit{dp}[i][1]$，按照同样的方式考虑转移状态，那么可能的转移状态为前一天已经持有一支股票，即 $\textit{dp}[i-1][1]$，或者前一天结束时还没有股票，即 $\textit{dp}[i-1][0]$，这时候我们要将其买入，并减少 $\textit{prices}[i]$ 的收益。可以列出如下的转移方程：

$\textit{dp}[i][1]=\max\{\textit{dp}[i-1][1],\textit{dp}[i-1][0]-\textit{prices}[i]\}$

对于初始状态，根据状态定义我们可以知道第 $0$ 天交易结束的时候 $\textit{dp}[0][0]=0$，$\textit{dp}[0][1]=-\textit{prices}[0]$。

因此，我们只要从前往后依次计算状态即可。由于全部交易结束后，持有股票的收益一定低于不持有股票的收益，因此这时候 $\textit{dp}[n-1][0]$ 的收益必然是大于 $\textit{dp}[n-1][1]$ 的，最后的答案即为 $\textit{dp}[n-1][0]$。



**方法一：**

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if (len == 1)
            return 0;
        int ans = 0;
        for (int i = 1; i < len; ++i)
        {
            if (prices[i] > prices[i - 1])
                ans += (prices[i] - prices[i - 1]);
        }
        
        return ans;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if (len == 1)
            return 0;
        int dp0 = 0, dp1 = -prices[0];
        for (int i = 1; i < len; ++i)
        {
            int newdp0 = max(dp0, dp1 + prices[i]);
            int newdp1 = max(dp1, dp0 - prices[i]);
            tie(dp0, dp1) = {newdp0, newdp1};
        }
        return dp0;
    }
};
```







## 0139. 单词拆分

### 题目：

给定一个**非空**字符串 s 和一个包含**非空**单词的列表 wordDict，判定 s 是否可以被空格拆分为一个或多个在字典中出现的单词。

**说明：**

- 拆分时可以重复使用字典中的单词。
- 你可以假设字典中没有重复的单词。

**示例 1：**

```
输入: s = "leetcode", wordDict = ["leet", "code"]
输出: true
解释: 返回 true 因为 "leetcode" 可以被拆分成 "leet code"。
```

**示例 2：**

```
输入: s = "applepenapple", wordDict = ["apple", "pen"]
输出: true
解释: 返回 true 因为 "applepenapple" 可以被拆分成 "apple pen apple"。
     注意你可以重复使用字典中的单词。
```

**示例 3：**

```
输入: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
输出: false
```



**解题思路：**

![leetcode_139](F:\C++\刷题\Img\leetcode_139.png)

- 初始化 $dp=[False,\cdots,False]$，长度为 $n+1$。$n$ 为字符串长度。$dp[i]$ 表示 $s$ 的前 $i$ 位是否可以用 $wordDict$ 中的单词表示。


- 初始化 $dp[0]=True$，空字符可以被表示。


- 遍历字符串的所有子串，遍历开始索引 $i$，遍历区间 $[0,n)$：
  - 遍历结束索引 $j$，遍历区间 $[i+1,n+1)$：
    - 若 $dp[i]=True$ 且 $s[i,\cdots,j)$ 在 $wordlist$ 中：$dp[j]=True$。解释：$dp[i]=True$ 说明 $s$ 的前 $i$ 位可以用 $wordDict$ 表示，则 $s[i,\cdots,j)$ 出现在 $wordDict$ 中，说明 $s$ 的前 $j$ 位可以表示。
- 返回 $dp[n]$


时间复杂度：$O(n^{2})$
空间复杂度：$O(n)$



**方法：**

```c++
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int len = s.length();
        set<string> wordDictSet(wordDict.begin(), wordDict.end());

        vector<bool> dp(len + 1, false);
        dp[0] = true;
        /*
        for (int i = 1; i <= len; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (dp[j] && wordDictSet.find(s.substr(j, i - j)) != wordDictSet.end())
                {
                    dp[i] = true;
                    break;
                }
            }
        }
        */
        for (int i = 0; i < len; ++i)
        {
            for (int j = i + 1; j <= len; ++j)
            {
                if (dp[i] && wordDictSet.find(s.substr(i, j - i)) != wordDictSet.end())
                    dp[j] = true;
            }
        }
        return dp[len];
    }
};
```







## 0152. 乘积最大子数组

### 题目：

给你一个整数数组 `nums` ，请你找出数组中乘积最大的连续子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。

**示例 1:**

```
输入: [2,3,-2,4]
输出: 6
解释: 子数组 [2,3] 有最大乘积 6。
```

**示例 2:**

```
输入: [-2,0,-1]
输出: 0
解释: 结果不能为 2, 因为 [-2,-1] 不是子数组。
```



**解题思路：**

- 标签：动态规划
- 遍历数组时计算当前最大值，不断更新
- 令imax为当前最大值，则当前最大值为 imax = max(imax * nums[i], nums[i])
- **由于存在负数，那么会导致最大的变最小的，最小的变最大的**。因此还需要维护当前最小值imin，imin = min(imin * nums[i], nums[i])
- 当负数出现时则imax与imin进行交换再进行下一步计算
- 时间复杂度：O(n)
- 空间复杂度：O(1)



**方法：**

```c++
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int len = nums.size();
        if (len == 1)
            return nums[0];
        
        int curMax = 1;
        int curMin = 1;
        int allMax = INT_MIN;
        for (int i = 0; i < len; ++i)
        {
            if (nums[i] < 0)
            {
                int tmp = curMax;
                curMax = curMin;
                curMin = tmp;
            }
            curMax = max(curMax * nums[i], nums[i]);
            curMin = min(curMin * nums[i], nums[i]);
            allMax = max(allMax, curMax);
        }
        return allMax;
    }
};
```







## 0198. 打家劫舍

### 题目：

每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，**如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警**。

给定一个代表每个房屋存放金额的非负整数数组，计算你 **不触动警报装置的情况下** ，一夜之内能够偷窃到的最高金额。

**示例 1：**

```
输入：[1,2,3,1]
输出：4
解释：偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。
     偷窃到的最高金额 = 1 + 3 = 4 。
```

**示例 2：**

```
输入：[2,7,9,3,1]
输出：12
解释：偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)。
     偷窃到的最高金额 = 2 + 9 + 1 = 12 。
```

**提示：**

- `1 <= nums.length <= 100`
- `0 <= nums[i] <= 400`



**解题思路**

数组跳跃组合求极值的问题

如果房屋数量大于两间，应该如何计算能够偷窃到的最高总金额呢？对于第 $k~(k>2)$ 间房屋，有两个选项：

偷窃第 $k$ 间房屋，那么就不能偷窃第 $k-1$ 间房屋，偷窃总金额为前 $k-2$ 间房屋的最高总金额与第 $k$ 间房屋的金额之和。

不偷窃第 $k$ 间房屋，偷窃总金额为前 $k-1$ 间房屋的最高总金额。

在两个选项中选择偷窃总金额较大的选项，该选项对应的偷窃总金额即为前 kk 间房屋能偷窃到的最高总金额。

用 $\textit{dp}[i]$ 表示前 $i$ 间房屋能偷窃到的最高总金额，那么就有如下的状态转移方程：

$\textit{dp}[i] = \max(\textit{dp}[i-2]+\textit{nums}[i], \textit{dp}[i-1])$

边界条件为：

$\begin{cases} \textit{dp}[0] = \textit{nums}[0] & 只有一间房屋，则偷窃该房屋 \\ \textit{dp}[1] = \max(\textit{nums}[0], \textit{nums}[1]) & 只有两间房屋，选择其中金额较高的房屋进行偷窃 \end{cases}$

最终的答案即为 $\textit{dp}[n-1]$，其中 $n$ 是数组的长度。

时间复杂度：O(n)

空间复杂度：O(1)  (滚动数组)





**方法：**

```c++
class Solution {
public:
    int rob(vector<int>& nums) {
        int len = nums.size();
        if (len == 1)
            return nums[0];
        
        if (len == 2)
            return max(nums[0], nums[1]);

        int a = nums[0], b = max(nums[0], nums[1]), c = 0;

        for (int i = 2; i < len; ++i)
        {
            c = max(a + nums[i], b);
            a = b;
            b = c;
        }

        return c;
    }
};

/*
class Solution {
public:
    int rob(vector<int>& nums) {
        int len = nums.size();
        if (len == 1)
            return nums[0];
        
        vector<int> dp(len, 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);

        for (int i = 2; i < len; ++i)
            dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);

        return dp[len - 1];
    }
};


/*
class Solution {
public:
    int rob(vector<int>& nums) {
        int len = nums.size();
        if (len == 1)
            return nums[0];
        
        vector<int> dp(len + 1, 0);
        dp[1] = nums[0];
        dp[2] = nums[1];

        for (int i = 3; i <= len; ++i)
        {
            dp[i] = max(dp[i - 2], dp[i - 3]) + nums[i - 1];
        }

        return max(dp[len - 1], dp[len]);
    }
};
*/
```





## 0213. 打家劫舍Ⅱ

### 题目：

每间房内都藏有一定的现金。这个地方所有的房屋都 **围成一圈** ，这意味着第一个房屋和最后一个房屋是紧挨着的。同时，相邻的房屋装有相互连通的防盗系统，**如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警** 。

给定一个代表每个房屋存放金额的非负整数数组，计算你 **在不触动警报装置的情况下** ，今晚能够偷窃到的最高金额。

**示例 1：**

```
输入：nums = [2,3,2]
输出：3
解释：你不能先偷窃 1 号房屋（金额 = 2），然后偷窃 3 号房屋（金额 = 2）, 因为他们是相邻的。
```

**示例 2：**

```
输入：nums = [1,2,3,1]
输出：4
解释：你可以先偷窃 1 号房屋（金额 = 1），然后偷窃 3 号房屋（金额 = 3）。
     偷窃到的最高金额 = 1 + 3 = 4 。
```

**示例 3：**

```
输入：nums = [0]
输出：0
```

**提示：**

- `1 <= nums.length <= 100`
- `0 <= nums[i] <= 1000`



**解题思路：**

思路等同于0198题，但这个数组是一个循环数组，所以需要计算 0 ~ len - 2 以及 1 ~ len - 1范围内的最大值；

时间复杂度：O(n)

空间复杂度：O(1)  (滚动数组)



**方法：**

```c++
class Solution {
public:
    int rob(vector<int>& nums) {
        int len = nums.size();
        if (len == 1)
            return nums[0];
        if (len == 2)
            return max(nums[0], nums[1]);

        return max(rotateRob(nums, 0, len - 2), rotateRob(nums, 1, len - 1));
    }
    int rotateRob(vector<int>& nums, int start, int end)
    {
        int len = end - start + 1;
        if (len == 2)
            return max(nums[start], nums[end]);

        int a = nums[start], b = max(nums[start], nums[start + 1]), c = 0;

        for (int i = 2; i < len; ++i)
        {
            c = max(a + nums[start + i], b);
            a = b;
            b = c;
        }
        return c;
    }
};
```







## 0221. 最大正方形

### 题目：

在一个由 `'0'` 和 `'1'` 组成的二维矩阵内，找到只包含 `'1'` 的最大正方形，并返回其面积。

**示例1：**

![leetcode_221](F:\C++\刷题\Img\leetcode_221.jpg)

```
输入：matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
输出：4
```

**示例2：**

![leetcode_221_1](F:\C++\刷题\Img\leetcode_221_1.jpg)

```
输入：matrix = [["0","1"],["1","0"]]
输出：1
```

**示例 3：**

```
输入：matrix = [["0"]]
输出：0
```

**提示：**

- `m == matrix.length`
- `n == matrix[i].length`
- `1 <= m, n <= 300`
- `matrix[i][j] 为 '0' 或 '1'`



**解题思路：**

用 $\textit{dp}(i, j)$ 表示以 $(i, j)$ 为右下角，且只包含 $1$ 的正方形的边长最大值。如果我们能计算出所有 $\textit{dp}(i, j)$ 的值，那么其中的最大值即为矩阵中只包含 $1$ 的正方形的边长最大值，其平方即为最大正方形的面积。

那么如何计算 $\textit{dp}$ 中的每个元素值呢？对于每个位置 $(i, j)$，检查在矩阵中该位置的值：

- 如果该位置的值是 $0$，则 $\textit{dp}(i, j) = 0$，因为当前位置不可能在由 $1$ 组成的正方形中；

- 如果该位置的值是 $1$，则 $\textit{dp}(i, j)$ 的值由其上方、左方和左上方的三个相邻位置的 $\textit{dp}$ 值决定。**具体而言，当前位置的元素值等于三个相邻位置的元素中的最小值加 $1$**，状态转移方程如下：


$$
dp(i, j)=min(dp(i−1, j), dp(i−1, j−1), dp(i, j−1))+1
$$



**方法：**

```c++
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        vector<int> dp(n, 0);
        int maxArea = INT_MIN;
        for (int i = 0; i < m; ++i)
        {
            vector<int> dpTmp(n, 0);
            for (int j = 0; j < n; ++j)
                if (matrix[i][j] == '1')
                    if (i == 0 || j == 0)
                        dpTmp[j] = 1;
                    else
                        dpTmp[j] = min(dp[j - 1], min(dp[j], dpTmp[j - 1])) + 1;
            dp = dpTmp;
            maxArea = max(maxArea, *max_element(dp.begin(), dp.end()));
        }
        return maxArea * maxArea;
    }
};
```







## 0264. 丑数Ⅱ

### 题目：

给你一个整数 `n` ，请你找出并返回第 `n` 个 **丑数** 。

**丑数** 就是只包含质因数 `2`、`3` 和/或 `5` 的正整数。

**示例 1：**

```
输入：n = 10
输出：12
解释：[1, 2, 3, 4, 5, 6, 8, 9, 10, 12] 是由前 10 个丑数组成的序列。
```

**示例 2：**

```
输入：n = 1
输出：1
解释：1 通常被视为丑数。
```

**提示：**

- `1 <= n <= 1690`



**解题思路：**

思路一：最小堆

要得到从小到大的第 n 个丑数，可以使用**最小堆**实现。

初始时堆为空。首先将最小的丑数 $1$ 加入堆。

每次取出堆顶元素 $x$，则 $x$ 是堆中最小的丑数，由于 $2x, 3x, 5x$ 也是丑数，因此将 $2x, 3x, 5x$ 加入堆。

上述做法会导致堆中出现重复元素的情况。为了避免重复元素，可以使用哈希集合去重，避免相同元素多次加入堆。

在排除重复元素的情况下，第 $n$ 次从最小堆中取出的元素即为第 $n$ 个丑数。

时间复杂度：O(nlogn)

空间复杂度：O(n) 

思路二：暴力解法（个别示例会超时）

时间复杂度：O(n)

空间复杂度：O(1)

思路三 ：动态规划

使用一个数组记录所有丑数，在使用三个数p2、p3、p5记录当前最小丑数的下标，即

`int num2 = dp[p2] * 2, num3 = dp[p3] * 3, num5 = dp[p5] * 5;`

`dp[i] = min(num2, min(num3, num5));`

因此每次找到的三个数肯定都是丑数，只需要依次记录下最小的一个就行，记录下当前丑数后，再把对应标记后移一位；

时间复杂度：O(n)

空间复杂度：O(n)



**方法一：**

```c++
class Solution {
public:
    int nthUglyNumber(int n) {
        if (n == 1)
            return 1;
        
        vector<int> factors = {2, 3, 5};
        unordered_set<long> seen;
        priority_queue<long, vector<long>, greater<long>> heap;
        heap.push(1L);
        seen.insert(1L);
        int ugly = 0;

        for (int i = 0; i < n; ++i)
        {
            long curr = heap.top();
            heap.pop();
            ugly = (int)curr;

            for (auto & facotr : factors)
            {
                long next = facotr * curr;
                if (!seen.count(next))
                {
                    seen.insert(next);
                    heap.push(next);
                }
            }
        }
        return ugly;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    bool isUgly(int n) {
        while( n > 0 )
        {
            if(n==1)
                return true;
            if(n%2==0)
                n /= 2;
            else if(n%3==0)
                n /= 3;
            else if(n%5==0)
                n /= 5;
            else
                break;
        }
        return false;
    }

    int nthUglyNumber(int n) {
        int count=0,num=1;
        while(count!=n)
        {
            if(isUgly(num))
                count++;
            num++;
        }
        return num-1;
    }
};
```

**方法三：**

```c++
class Solution {
public:
    int nthUglyNumber(int n) 
    {
        if (n == 1)
            return 1;
        
        vector<int> dp(n + 1, 0);
        dp[1] = 1;
        int p2 = 1, p3 = 1, p5 = 1;
        for (int i = 2; i <= n; ++i)
        {
            int num2 = dp[p2] * 2, num3 = dp[p3] * 3, num5 = dp[p5] * 5;
            dp[i] = min(num2, min(num3, num5));
            if (dp[i] == num2) ++p2;
            if (dp[i] == num3) ++p3;
            if (dp[i] == num5) ++p5;
        }
        return dp[n];
    }
};
```





## 0279. 完全平方数

### 题目：

给定正整数 `n`，找到若干个完全平方数（`比如 1, 4, 9, 16, ...`）使得它们的和等于 `n`。你需要让组成和的完全平方数的个数最少。

给你一个整数 n ，返回和为 n 的完全平方数的 **最少数量** 。

**完全平方数** 是一个整数，其值等于另一个整数的平方；换句话说，其值等于一个整数自乘的积。例如，`1、4、9 和 16` 都是完全平方数，而 `3` 和 `11` 不是。

**示例 1：**

```
输入：n = 12
输出：3 
解释：12 = 4 + 4 + 4
```

**示例 2：**

```
输入：n = 13
输出：2
解释：13 = 4 + 9
```

**提示：**

- `1 <= n <= 10^4`



**解题思路：**

$f[i]$ 表示最少需要多少个数的平方来表示整数 $i$。

这些数必然落在区间 $[1,\sqrt{n}]$。我们可以枚举这些数，假设当前枚举到 $j$，那么我们还需要取若干数的平方，构成 $i-j^2$。此时我们发现该子问题和原问题类似，只是规模变小了。这符合了动态规划的要求，于是我们可以写出状态转移方程。

$f[i]=1+\min_{j=1}^{\lfloor\sqrt{i}\rfloor}{f[i-j^2]}$

其中 $f[0]=0$ 为边界条件，实际上我们无法表示数字 $0$，只是为了保证状态转移过程中遇到 $j$ 恰为 $\sqrt{i} $
的情况合法。

同时因为计算 $f[i]$ 时所需要用到的状态仅有 $f[i-j^2]$，必然小于 $i$，因此我们只需要从小到大地枚举 $i$ 来计算 $f[i]$ 即可。



时间复杂度：$O(n\sqrt{n})$

空间复杂度：$O(n)$

**方法：**

```c++
class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, 0);
        for (int i = 1; i <= n; ++i)
        {
            int minn = INT_MAX;
            for (int j = 1; j * j <= i; ++j)
                minn = min(minn, dp[i - j * j]);
            dp[i] = minn + 1;
        }
        return dp[n];
    }
};
```







## 0300. 最长递增子序列

### 题目：

给你一个整数数组 `nums` ，找到其中最长严格递增子序列的长度。

子序列是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，`[3,6,2,7]` 是数组 `[0,3,1,6,2,2,7]` 的子序列。

**示例 1：**

```
输入：nums = [10,9,2,5,3,7,101,18]
输出：4
解释：最长递增子序列是 [2,3,7,101]，因此长度为 4 。
```

**示例 2：**

```
输入：nums = [0,1,0,3,2,3]
输出：4
```

**示例 3：**

```
输入：nums = [7,7,7,7,7,7,7]
输出：1
```

**提示：**

- `1 <= nums.length <= 2500`
- `-10^4 <= nums[i] <= 10^4`



**解题思路：**

思路一：动态规划

定义 $\textit{dp}[i]$ 为考虑前 $i$ 个元素，以第 $i$ 个数字结尾的最长上升子序列的长度，注意 $\textit{nums}[i]$ 必须被选取。

我们从小到大计算 $\textit{dp}$ 数组的值，在计算 $\textit{dp}[i]$ 之前，我们已经计算出 $\textit{dp}[0 \ldots i-1]$ 的值，则状态转移方程为：

$$
\textit{dp}[i] = \max(\textit{dp}[j]) + 1, \text{其中} \, 0 \leq j < i \, \text{且} \, \textit{num}[j]<\textit{num}[i]
$$
即考虑往 $\textit{dp}[0 \ldots i-1]$ 中最长的上升子序列后面再加一个 $\textit{nums}[i]$。由于 $\textit{dp}[j]$ 代表 $\textit{nums}[0 \ldots j]$ 中以 $\textit{nums}[j]$ 结尾的最长上升子序列，所以如果能从 $\textit{dp}[j]$这个状态转移过来，那么 $\textit{nums}[i]$ 必然要大于 $\textit{nums}[j]$，才能将 $\textit{nums}[i]$ 放在 $\textit{nums}[j]$ 后面以形成更长的上升子序列。

最后，整个数组的最长上升子序列即所有 $\textit{dp}[i]$ 中的最大值。

时间复杂度：O(n^2)

空间复杂度：O(n)

思路二：动态规划 + 二分查找

使用一个数组，存储当前已经遍历过的最长递增子序列，若遍历当前元素大于数组最后一个，说明最长递增子序列还能增长，就添加到数组中，否则在当前数组中找位置并插入（可能是中间的某个数）

以输入序列 [0,8,4,12,2] 为例：

- 第一步插入 0，d = [0]；


- 第二步插入 8，d = [0, 8]；


- 第三步插入 4，d = [0, 4]；


- 第四步插入 12，d = [0, 4, 12]；


- 第五步插入 2，d = [0, 2, 12]。


最终得到最大递增子序列长度为 3。

时间复杂度：O(nlogn)

空间复杂度：O(n)



**方法一：**

```c++
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 1);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < i; ++j)
                if (nums[j] < nums[i])
                    dp[i] = max(dp[i], dp[j] + 1);
        return *max_element(dp.begin(), dp.end());
    }
};
```

**方法二：**

```c++
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        int len = 1;
        vector<int> dp(n + 1, 0);
        dp[len] = nums[0];
        for (int i = 1; i < n; ++i)
            if (nums[i] > dp[len])
                dp[++len] = nums[i];
            else
            {
                int pos = binaryFind(dp, len, nums[i]);
                dp[pos] = nums[i];
            }
        return len;
    }

    int binaryFind(vector<int>& dp, int len, int data)
    {
        int l = 1, r = len, pos = 0;
        while (l <= r)
        {
            int mid = ((l + r) >> 1);
            if (data > dp[mid])
            {
                pos = mid;
                l = mid + 1;
            }
            else 
                r = mid - 1;
        }
        return pos + 1;
    }
};
```







## 0304. 二维区域和检索-矩阵不可变

### 题目：

给定一个二维矩阵 `matrix`，以下类型的多个请求：

- 计算其子矩形范围内元素的总和，该子矩阵的 **左上角** 为 `(row1, col1)` ，**右下角** 为 `(row2, col2)` 。

实现 `NumMatrix` 类：

- `NumMatrix(int[][] matrix)` 给定整数矩阵 `matrix` 进行初始化
- `int sumRegion(int row1, int col1, int row2, int col2)` 返回 **左上角** `(row1, col1)` 、**右下角** `(row2, col2)` 所描述的子矩阵的元素 **总和** 。

**示例1：**

```
输入: 
["NumMatrix","sumRegion","sumRegion","sumRegion"]
[[[[3,0,1,4,2],[5,6,3,2,1],[1,2,0,1,5],[4,1,0,1,7],[1,0,3,0,5]]],[2,1,4,3],[1,1,2,2],[1,2,2,4]]
输出: 
[null, 8, 11, 12]

解释:
NumMatrix numMatrix = new NumMatrix([[3,0,1,4,2],[5,6,3,2,1],[1,2,0,1,5],[4,1,0,1,7],[1,0,3,0,5]]]);
numMatrix.sumRegion(2, 1, 4, 3); // return 8 (红色矩形框的元素总和)
numMatrix.sumRegion(1, 1, 2, 2); // return 11 (绿色矩形框的元素总和)
numMatrix.sumRegion(1, 2, 2, 4); // return 12 (蓝色矩形框的元素总和)
```

**提示：**

- `m == matrix.length`
- `n == matrix[i].length`
- `1 <= m, n <= 200`
- `-10^5 <= matrix[i][j] <= 10^5`
- `0 <= row1 <= row2 < m`
- `0 <= col1 <= col2 < n`
- `最多调用 10^4 次 sumRegion 方法`



**解题思路：**

二位前缀和，方法等同于1314题

时间复杂度：O(mn)

空间复杂度：O(mn)

**方法：**

```c++
class NumMatrix {
private:
    vector<vector<int>> dp, mat;
public:
    NumMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        dp.resize(m + 1, vector<int>(n + 1));
        mat.resize(m, vector<int>(n));
        mat = matrix;

        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= n; ++j)
                dp[i][j] = mat[i - 1][j - 1] + dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1];
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return dp[row2 + 1][col2 + 1] - dp[row2 + 1][col1] - dp[row1][col2 + 1] + dp[row1][col1];
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */
```









## 0309. 最佳买卖股票时机含冷冻期

### 题目：

给定一个整数数组，其中第 `i` 个元素代表了第 `i` 天的股票价格 。

设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:

- 你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
- 卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。



**示例:**

```
输入: [1,2,3,0,2]
输出: 3 
解释: 对应的交易状态为: [买入, 卖出, 冷冻期, 买入, 卖出]
```



**解题思路：**

我们用 $f[i]$ 表示**第 $i$ 天结束之后的「累计最大收益」**。根据题目描述，由于我们最多只能同时买入（持有）一支股票，并且卖出股票后有冷冻期的限制，因此我们会有三种不同的状态：

- 我们目前持有一支股票，对应的「累计最大收益」记为 $f[i][0]$；
  - 这只股票有可能是前一天已经拥有的，也有可能是当天买的，说明前一天是冷冻期
  - $f[i][0]=max(f[i−1][0],f[i−1][2]−prices[i])$

- 我们目前不持有任何股票，并且处于冷冻期中，对应的「累计最大收益」记为 $f[i][1]$；
  - 不持有，且冷冻期，说明今天卖了（状态都说得是今天结束时）
  - $f[i][1]=f[i−1][0]+prices[i]$

- 我们目前不持有任何股票，并且不处于冷冻期中，对应的「累计最大收益」记为 $f[i][2]$。
  - 不持有，且不冷冻期，说明今天是冷冻期，或者昨天是
  - $f[i][2]=max(f[i−1][1],f[i−1][2])$



**方法：**

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if (len <= 1)
            return 0;
        
        int sell = 0, buy = -prices[0], cool = 0;
        for (int i = 1; i < len; ++i)
        {
            int newsell = buy + prices[i];
            int newbuy = max(cool - prices[i], buy);
            int newcool = max(sell, cool);
            tie(sell, buy, cool) = {newsell, newbuy, newcool};
        }
        return max(sell, cool);
    }
};
```





## 0322. 零钱兑换

### 题目：

给你一个整数数组 `coins` ，表示不同面额的硬币；以及一个整数 `amount` ，表示总金额。

计算并返回可以凑成总金额所需的 **最少的硬币个数** 。如果没有任何一种硬币组合能组成总金额，返回 `-1` 。

你可以认为每种硬币的数量是无限的。

 

**示例 1：**

```
输入：coins = [1, 2, 5], amount = 11
输出：3 
解释：11 = 5 + 5 + 1
```

**示例 2：**

```
输入：coins = [2], amount = 3
输出：-1
```

**示例 3：**

```
输入：coins = [1], amount = 0
输出：0
```

**示例 4：**

```
输入：coins = [1], amount = 1
输出：1
```

**示例 5：**

```
输入：coins = [1], amount = 2
输出：2
```

**提示：**

- `1 <= coins.length <= 12`
- `1 <= coins[i] <= 2^31 - 1`
- `0 <= amount <= 10^4`



**解题思路：**

思路一：动态规划

依次遍历钱数 1 ~ amount，判断当前余额，可以使用最少的硬币组合

时间复杂度：O(Sn)

空间复杂度：O(S)

思路二：贪心 + dfs

![leetcode_322](F:\C++\刷题\Img\leetcode_322.png)



**方法一：**

```c++
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int len = coins.size();
        int Max = amount + 1;
        vector<int> dp(amount + 1, Max);
        dp[0] = 0;
        for (int i = 1; i <= amount; ++i)
        {
            for (int j = 0; j < len; ++j)
            {
                if (coins[j] <= i)
                    dp[i] = min(dp[i], dp[i - coins[j]] + 1);
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }
};
```

**方法二：**

```c++
class Solution {
public:
    void _coinChange(vector<int>& coins, int amount, int c_index, int curCount, int& ans)
    {
        if (amount == 0)
        {
            ans = min(curCount, ans);
            return;
        }
        if (c_index == coins.size()) return;

        // k + curCount < ans 为剪枝操作
        for (int k = amount / coins[c_index]; k >= 0 && k + curCount < ans; --k)
            _coinChange(coins, amount - k * coins[c_index], c_index + 1, curCount + k, ans);
    }
    int coinChange(vector<int>& coins, int amount) {
        if (amount == 0)
            return 0;
        sort(coins.rbegin(), coins.rend());
        int ans = INT_MAX;
        _coinChange(coins, amount, 0, 0, ans);
        return ans == INT_MAX ? -1 : ans;
    }
};
```





## 0343. 整数拆分

### 题目：

给定一个正整数 `n`，将其拆分为**至少**两个正整数的和，并使这些整数的乘积最大化。 返回你可以获得的最大乘积。

**示例 1:**

```
输入: 2
输出: 1
解释: 2 = 1 + 1, 1 × 1 = 1。
```

**示例 2:**

```
输入: 10
输出: 36
解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36。
```

**说明**: 你可以假设 n 不小于 2 且不大于 58。



**解题思路：**

思路一：动态规划

创建数组 $\textit{dp}$，其中 $\textit{dp}[i]$ 表示将正整数 $i$ 拆分成至少两个正整数的和之后，这些正整数的最大乘积。特别地，$0$ 不是正整数，$1$ 是最小的正整数，$0$ 和 $1$ 都不能拆分，因此 $\textit{dp}[0]=\textit{dp}[1]=0$。

当 $i \ge 2$ 时，假设对正整数 $i$ 拆分出的第一个正整数是 $j$（$1 \le j < i$），则有以下两种方案：

将 $i$ 拆分成 $j$ 和 $i-j$ 的和，且 $i-j$ 不再拆分成多个正整数，此时的乘积是 $j \times (i-j)$；

将 $i$ 拆分成 $j$ 和 $i-j$ 的和，且 $i-j$ 继续拆分成多个正整数，此时的乘积是 $j \times \textit{dp}[i-j]$。

因此，当 $j$ 固定时，有 $\textit{dp}[i]=\max(j \times (i-j), j \times \textit{dp}[i-j])$。由于 $j$ 的取值范围是 $1$ 到 $i-1$，需要遍历所有的 $j$ 得到 $\textit{dp}[i]$ 的最大值，因此可以得到状态转移方程如下：

$\textit{dp}[i]=\mathop{\max}\limits_{1 \le j < i}\{\max(j \times (i-j), j \times \textit{dp}[i-j])\}$

最终得到 $\textit{dp}[n]$ 的值即为将正整数 $n$ 拆分成至少两个正整数的和之后，这些正整数的最大乘积。

时间复杂度：O(n^2)

空间复杂度：O(n)

思路二：动态规划改进

[动态规划改进](https://leetcode-cn.com/problems/integer-break/solution/zheng-shu-chai-fen-by-leetcode-solution/)

时间复杂度：O(n)

空间复杂度：O(n)

思路三：数学方法

[数学方法](https://leetcode-cn.com/problems/integer-break/solution/zheng-shu-chai-fen-by-leetcode-solution/)

时间复杂度：O(1)

空间复杂度：O(1)



**方法一：**

```c++
class Solution {
public:
    int integerBreak(int n) {
        vector<int> dp(n + 1, 0);
        for (int i = 2; i <= n; ++i)
        {
            int curMax = 0;
            for (int j = 1; j < i; ++j)
                curMax = max(curMax, max(j * (i - j), j * dp[i - j]));
            dp[i] = curMax;
        }
        return dp[n];
    }
};
```

**方法二：**

```c++
class Solution {
public:
    int integerBreak(int n) {
        if (n < 4)
            return n - 1;
        vector<int> dp(n + 1, 0);
        for (int i = 4; i <= n; ++i)
        {
            dp[i] = max(max(2 * (i - 2), 2 * dp[i - 2]), max(3 * (i - 3), 3 * dp[i - 3]));
        }
        return dp[n];
    }
};
```

**方法三：**

```c++
class Solution {
public:
    int integerBreak(int n) {
        if (n < 4)
            return n - 1;
        
        int zheng = n / 3;
        int yu = n % 3;

        if (yu == 0)
            return pow(3, zheng);
        else if (yu == 1)
            return pow(3, zheng - 1) * 4;
        else
            return pow(3, zheng) * 2;
    }
};
```





## 0376. 摆动序列

### 题目：

如果连续数字之间的差严格地在正数和负数之间交替，则数字序列称为 `摆动序列` 。第一个差（如果存在的话）可能是正数或负数。仅有一个元素或者含两个不等元素的序列也视作摆动序列。

- 例如， `[1, 7, 4, 9, 2, 5]` 是一个 摆动序列 ，因为差值 `(6, -3, 5, -7, 3)` 是正负交替出现的。

- 相反，`[1, 4, 7, 2, 5] 和 [1, 7, 4, 5, 5]` 不是摆动序列，第一个序列是因为它的前两个差值都是正数，第二个序列是因为它的最后一个差值为零。

**子序列** 可以通过从原始序列中删除一些（也可以不删除）元素来获得，剩下的元素保持其原始顺序。

给你一个整数数组 `nums` ，返回 `nums` 中作为 **摆动序列** 的 **最长子序列的长度** 。

 

**示例 1：**

```
输入：nums = [1,7,4,9,2,5]
输出：6
解释：整个序列均为摆动序列，各元素之间的差值为 (6, -3, 5, -7, 3) 。
```

**示例 2：**

```
输入：nums = [1,17,5,10,13,15,10,5,16,8]
输出：7
解释：这个序列包含几个长度为 7 摆动序列。
其中一个是 [1, 17, 10, 13, 10, 16, 8] ，各元素之间的差值为 (16, -7, 3, -3, 6, -8) 。
```

**示例 3：**

```
输入：nums = [1,2,3,4,5,6,7,8,9]
输出：2
```

**提示：**

- `1 <= nums.length <= 1000`
- `0 <= nums[i] <= 1000`



**解题思路：**

思路一：动态规划

[动态规划思路](https://leetcode-cn.com/problems/wiggle-subsequence/solution/bai-dong-xu-lie-by-leetcode-solution-yh2m/)

- 时间复杂度：O(n)
- 空间复杂度：O(1)

思路二：贪心算法

[贪心算法思路](https://leetcode-cn.com/problems/wiggle-subsequence/solution/bai-dong-xu-lie-by-leetcode-solution-yh2m/)

- 时间复杂度：O(n)
- 空间复杂度：O(1)

**方法一：**

```c++
class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        int n = nums.size();
        if (n < 2)
            return n;
        
        int up = 1, down = 1;
        for (int i = 1; i < n; ++i)
            if (nums[i] > nums[i - 1])
                up = down + 1;
            else if (nums[i] < nums[i - 1])
                down = up + 1;
        return max(up, down);
    }
};
```

**方法二：**

```c++
class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        int n = nums.size();
        if (n < 2)
            return n;
        
        int prevdiff = nums[1] - nums[0];
        int ret = prevdiff != 0 ? 2 : 1;
        for (int i = 2; i < n; ++i)
        {
            int diff = nums[i] - nums[i - 1];
            if ((diff > 0 && prevdiff <= 0) || (diff < 0 && prevdiff >= 0))
            {
                ++ret;
                prevdiff = diff;
            }
        }
        return ret;
    }
};
```





## 0377. 组合总和Ⅳ

### 题目：

给你一个由 **不同** 整数组成的数组 `nums` ，和一个目标整数 `target` 。请你从 `nums` 中找出并返回总和为 `target` 的元素组合的个数。

题目数据保证答案符合 32 位整数范围。

**示例 1：**

```
输入：nums = [1,2,3], target = 4
输出：7
解释：
所有可能的组合为：
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)
请注意，顺序不同的序列被视作不同的组合。
```

**示例 2：**

```
输入：nums = [9], target = 3
输出：0
```

**提示：**

- `1 <= nums.length <= 200`
- `1 <= nums[i] <= 1000`
- `nums 中的所有元素 互不相同`
- `1 <= target <= 1000`



**解题思路：**

思路等同于0518题，一个是需要组合，一个不需要，另外还要保证答案在32位整数范围内

时间复杂度：$O(\textit{target} \times n)$

空间复杂度：$O(\textit{target})$

**方法：**

```c++
class Solution {
public:
    int _combinationSum4(vector<int>& nums, int target) {
        vector<int> dp(target + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= target; ++i)
        {
            for (auto& num : nums)
            {
                // dp[i - num] < INT_MAX - dp[i]
                // dp[i - num] + dp[i] < INT_MAX  // 这种可能会为负，越界
                // 题目要求答案符合 32 位整数范围，所以不能越 size_t 的范围，越界的都是不符合的
                if (i >= num && dp[i - num] < INT_MAX - dp[i])
                    dp[i] += dp[i - num];
            }
        }
        return dp[target];
    }

    int combinationSum4(vector<int>& nums, int target) {
        vector<size_t> dp(target + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= target; ++i)
        {
            for (auto& num : nums)
            {
                if (i >= num)
                    dp[i] += dp[i - num];
            }
        }
        return dp[target];
    }
};
```





## 0392. 判断子序列

### 题目：

给定字符串 **s** 和 **t** ，判断 **s** 是否为 **t** 的子序列。

字符串的一个子序列是原始字符串删除一些（也可以不删除）字符而不改变剩余字符相对位置形成的新字符串。（例如，`"ace"`是`"abcde"`的一个子序列，而`"aec"`不是）。

**进阶：**

如果有大量输入的 `S`，称作 `S1, S2, ... , Sk` 其中 `k >= 10亿`，你需要依次检查它们是否为 `T` 的子序列。在这种情况下，你会怎样改变代码？

**示例 1：**

```
输入：s = "abc", t = "ahbgdc"
输出：true
```

**示例 2：**

```
输入：s = "axc", t = "ahbgdc"
输出：false
```

**提示：**

- `0 <= s.length <= 100`
- `0 <= t.length <= 10^4`
- 两个字符串都只由小写字符组成。



**解题思路：**

思路一：双指针法

挨个比较，若不相等，母串后移一位，若相等，母串子串都后移一位；

时间复杂度：O(m + n)

空间复杂度：O(1)

思路二：动态规划（？？？）





**方法一：**

```c++
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int len1 = s.length();
        int len2 = t.length();

        int i = 0, j = 0;
        while (i < len1 && j < len2)
        {
            if (s[i] == t[j])
                ++i;
            ++j;
        }

        return i == len1;
    }
};
```









## 0413. 等差数列划分

### 题目：

如果一个数列 **至少有三个元素** ，并且任意两个相邻元素之差相同，则称该数列为等差数列。

- 例如，`[1,3,5,7,9]`、`[7,7,7,7]` 和 `[3,-1,-5,-9]` 都是等差数列。

给你一个整数数组 `nums` ，返回数组 `nums` 中所有为等差数组的 **子数组** 个数。

**子数组** 是数组中的一个连续序列。

**示例 1：**

```
输入：nums = [1,2,3,4]
输出：3
解释：nums 中有三个子等差数组：[1, 2, 3]、[2, 3, 4] 和 [1,2,3,4] 自身。
```

**示例 2：**

```
输入：nums = [1]
输出：0
```

**提示：**

- `1 <= nums.length <= 5000`
- `-1000 <= nums[i] <= 1000`



**解题思路：**

依次遍历每一个元素，从第三个开始，查看是否和前面的复合等差，若符合，等差长度+1，若不符合，说明前面等差的范围在这里断了，计算前面那一段等差可以有多少个子等差，继续初始化条件，往后遍历并判断；

时间复杂度：O(n)

空间复杂度：O(1)



**方法：**

```c++
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int len = nums.size();
        if (len < 3)
            return 0;
        
        int res = 0;
        int d = nums[1] - nums[0];
        int l = 2;
        for (int i = 2; i < len; ++i)
        {
            if (nums[i] - nums[i - 1] == d)
                ++l;
            else
            {
                res += (l >= 3 ? (l - 1) * (l - 2) / 2 : 0);
                l = 2;
                d = nums[i] - nums[i - 1];
            }
        }
        res += (l >= 3 ? (l - 1) * (l - 2) / 2 : 0);
        return res;
    }
};
```







## 0509. 斐波那契数列

### 题目：

**斐波那契数**，通常用 `F(n)` 表示，形成的序列称为 **斐波那契数列** 。该数列由 `0` 和 `1` 开始，后面的每一项数字都是前面两项数字的和。也就是：

```
F(0) = 0，F(1) = 1
F(n) = F(n - 1) + F(n - 2)，其中 n > 1
```

给你 `n` ，请计算 `F(n)` 。



**示例 1：**

```
输入：2
输出：1
解释：F(2) = F(1) + F(0) = 1 + 0 = 1
```

**示例 2：**

```
输入：3
输出：2
解释：F(3) = F(2) + F(1) = 1 + 1 = 2
```

**示例 3：**

```
输入：4
输出：3
解释：F(4) = F(3) + F(2) = 2 + 1 = 3
```

**提示：**

- `0 <= n <= 30`



**解题思路：**

思路一：循环

​		时间复杂度：O(n)

​		空间复杂度：O(1)

思路二：递归

思路三：**矩阵快速幂**

​	首先我们可以构建这样一个递推关系：

$$\left[ \begin{matrix} 1 & 1 \\ 1 & 0 \end{matrix} \right] \left[ \begin{matrix} F(n)\\ F(n - 1) \end{matrix} \right] = \left[ \begin{matrix} F(n) + F(n - 1)\\ F(n) \end{matrix} \right] = \left[ \begin{matrix} F(n + 1)\\ F(n) \end{matrix} \right]$$

因此：

$$\left[ \begin{matrix} F(n + 1)\\ F(n) \end{matrix} \right] = \left[ \begin{matrix} 1 & 1 \\ 1 & 0 \end{matrix} \right] ^n \left[ \begin{matrix} F(1)\\ F(0) \end{matrix} \right]$$


令：

$$M = \left[ \begin{matrix} 1 & 1 \\ 1 & 0 \end{matrix} \right]$$

因此只要我们能快速计算矩阵 $M$ 的 $n$ 次幂，就可以得到 $F(n)$ 的值。如果直接求取 $M^n$
 ，时间复杂度是 $O(n)$，可以定义矩阵乘法，然后用快速幂算法来加速这里 $M^n$
  的求取。

​		时间复杂度：O(logn)

​		空间复杂度：O(1)

思路四：组合数学递推式

$F(n)=\frac{1}{\sqrt{5}}\left[ \left(\frac{1+\sqrt{5}}{2}\right)^{n} - \left(\frac{1-\sqrt{5}}{2}\right)^{n} \right]$


**方法一：**循环

```c++
class Solution {
public:
    int fib(int n) {
        if (n == 0)
            return 0;
        if (n == 1)
            return 1;
        int a = 0, b = 1;
        int c = 0;
        for (int i = 2; i <= n; ++i)
        {
            c = a + b;
            a = b;
            b = c;
        }
        return c;
    }
};
```

**方法二：**递归

```c++
class Solution {
public:
    int fib(int n) {
        if (n == 0)
            return 0;
        else if (n == 1)
            return 1;
        else 
            return fib(n - 1) + fib(n - 2);
    }
};
```

**方法三：**矩阵快速幂

```c++
class Solution {
public:
    int fib(int n) {
        if (n < 2)
            return n;
        vector<vector<int>> q = {{1, 1}, {1, 0}};
        vector<vector<int>> ret = matrix_pow(q, n - 1);
        return ret[0][0];
    }

    vector<vector<int>> matrix_pow(vector<vector<int>>& a, int n)
    {
        // 重点
        vector<vector<int>> ret = {{1, 0}, {0, 1}};
        while (n > 0)
        {
            if (n & 1)
                ret = matrix_multiply(ret, a);
            n >>= 1;
            a = matrix_multiply(a, a);
        }
        return ret;
    }

    vector<vector<int>> matrix_multiply(vector<vector<int>>& a, vector<vector<int>>& b)
    {
        vector<vector<int>> c = {{0, 0}, {0, 0}};
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                c[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j];
        return c;
    }
};
```

**方法四：**递推式（组合数学）

```c++
class Solution {
public:
    int fib(int n) {
        if (n < 2)
            return n;
        double sqrt5 = sqrt(5);
        double fibn = pow((1 + sqrt5) / 2, n) + pow((1 - sqrt5) / 2, n);
        return round(fibn / sqrt5);
    }
};
```





## 0516. 最长回文子序列

### 题目：

给你一个字符串 `s` ，找出其中最长的回文子序列，并返回该序列的长度。

子序列定义为：不改变剩余字符顺序的情况下，删除某些字符或者不删除任何字符形成的一个序列。

**示例 1：**

```
输入：s = "bbbab"
输出：4
解释：一个可能的最长回文子序列为 "bbbb" 。
```

**示例 2：**

```
输入：s = "cbbd"
输出：2
解释：一个可能的最长回文子序列为 "bb" 。
```

**提示：**

- `1 <= s.length <= 1000`
- `s 仅由小写英文字母组成`



**解题思路：**

用 $\textit{dp}[i][j]$ 表示字符串 $s$ 的下标范围 $[i, j]$ 内的最长回文子序列的长度。假设字符串 $s$ 的长度为 $n$，则只有当 $0 \le i \le j < n$ 时，才会有 $\textit{dp}[i][j] > 0$，否则 $\textit{dp}[i][j] = 0$。

由于任何长度为 $1$ 的子序列都是回文子序列，因此动态规划的边界情况是，对任意 $0 \le i < n$，都有 $\textit{dp}[i][i] = 1$。

当 $i < j$ 时，计算 $\textit{dp}[i][j]$ 需要分别考虑 $s[i]$ 和 $s[j]$ 相等和不相等的情况：

如果 $s[i] = s[j]$，则首先得到 ss 的下标范围 $[i+1, j-1]$ 内的最长回文子序列，然后在该子序列的首尾分别添加 $s[i]$ 和 $s[j]$，即可得到 $s$ 的下标范围 $[i, j]$ 内的最长回文子序列，因此 $\textit{dp}[i][j] = \textit{dp}[i+1][j-1] + 2$；

如果 $s[i] \ne s[j]$，则 $s[i]$ 和 $s[j]$ 不可能同时作为同一个回文子序列的首尾，因此 $\textit{dp}[i][j] = \max(\textit{dp}[i+1][j], \textit{dp}[i][j-1])$。

由于状态转移方程都是从长度较短的子序列向长度较长的子序列转移，因此需要注意动态规划的循环顺序。然后注意遍历顺序，`i` 从最后一个字符开始往前遍历，`j` 从 `i + 1` 开始往后遍历，这样可以保证每个子问题都已经算好了。

最终得到 $\textit{dp}[0][n-1]$ 即为字符串 $s$ 的最长回文子序列的长度。

时间复杂度：O(n^2)

空间复杂度：O(n^2)



**方法：**

```c++
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int len = s.length();
        vector<vector<int>> dp(len, vector<int>(len, 0));
        for (int i = len - 1; i >= 0; --i)
        {
            dp[i][i] = 1;
            for (int j = i + 1; j < len; ++j)
            {
                if (s[i] == s[j])
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                else
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
        return dp[0][len - 1];
    }
};
```







## 0518. 零钱兑换Ⅱ

### 题目：

给你一个整数数组 `coins` 表示不同面额的硬币，另给一个整数 `amount` 表示总金额。

请你计算并返回可以凑成总金额的硬币组合数。如果任何硬币组合都无法凑出总金额，返回 `0` 。

假设每一种面额的硬币有无限个。 

题目数据保证结果符合 32 位带符号整数。

**示例 1：**

```
输入：amount = 5, coins = [1, 2, 5]
输出：4
解释：有四种方式可以凑成总金额：
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1
```

**示例 2：**

```
输入：amount = 3, coins = [2]
输出：0
解释：只用面额 2 的硬币不能凑成总金额 3 。
```

**示例 3：**

```
输入：amount = 10, coins = [10] 
输出：1
```

**提示：**

- `1 <= coins.length <= 300`
- `1 <= coins[i] <= 5000`
- `coins 中的所有值 互不相同`
- `0 <= amount <= 5000`



**解题思路：**

依次遍历coins，判断从 i = coin  ---- > amount 这些总余额依次可以用coin凑出几个整来，然后就是coins[0]、coins[1]的参与，再从 i = coins[1]  ---- > amount 这些总余额依次可以用coin凑出几个整来，依次遍历结束coins，每次状态转移方程是 dp[i] += dp[i - coin]，dp[i]表示 i 余额可以使用多少种搭配方式找零。

用 $\textit{dp}[x]$ 表示金额之和等于 $x$ 的硬币组合数，目标是求 $\textit{dp}[\textit{amount}]$。

动态规划的边界是 $\textit{dp}[0]=1$。只有当不选取任何硬币时，金额之和才为 $0$，因此只有 $1$ 种硬币组合。

对于面额为 $\textit{coin}$ 的硬币，当 $\textit{coin} \le i \le \textit{amount}$ 时，如果存在一种硬币组合的金额之和等于 $i - \textit{coin}$，则在该硬币组合中增加一个面额为 $\textit{coin}$ 的硬币，即可得到一种金额之和等于 $i$ 的硬币组合。因此需要遍历 $\textit{coins}$，对于其中的每一种面额的硬币，更新数组 $\textit{dp}$ 中的每个大于或等于该面额的元素的值。

**方法：**

```c++
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        vector<int> dp(amount + 1, 0);
        dp[0] = 1;
        for (auto& coin : coins)
            for (int i = coin; i <= amount; ++i)
                dp[i] += dp[i - coin];
        return dp[amount];
    }
};
```





## 0714. 买卖股票的最佳时机含手续费

### 题目：

给定一个整数数组 `prices`，其中第 `i` 个元素代表了第 `i` 天的股票价格 ；整数 `fee` 代表了交易股票的手续费用。

你可以无限次地完成交易，但是你每笔交易都需要付手续费。如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。

返回获得利润的最大值。

**注意**：这里的一笔交易指买入持有并卖出股票的整个过程，每笔交易你只需要为支付一次手续费。

**示例 1：**

```
输入：prices = [1, 3, 2, 8, 4, 9], fee = 2
输出：8
解释：能够达到的最大利润:  
在此处买入 prices[0] = 1
在此处卖出 prices[3] = 8
在此处买入 prices[4] = 4
在此处卖出 prices[5] = 9
总利润: ((8 - 1) - 2) + ((9 - 4) - 2) = 8
```

**示例 2：**

```
输入：prices = [1,3,7,5,10,3], fee = 3
输出：6
```

**提示：**

- `1 <= prices.length <= 5 * 10^4`
- `1 <= prices[i] < 5 * 10^4`
- `0 <= fee < 5 * 10^4`



**解题思路：**

思路类似于0122题，只是一个普通的多次买卖股票求最大收益问题，只是在卖的时候，会减掉手续费后，再对比是否划算卖出；



**方法：**

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int len = prices.size();
        if (len == 1)
            return 0;
        
        int buy = -prices[0];
        int sell = 0;
        for (int i = 1; i < len; ++i)
        {
            int newbuy = max(sell - prices[i], buy);
            int newsell = max(buy + prices[i] - fee, sell);
            tie(buy, sell) = {newbuy, newsell};
        }
        return sell;
    }
};
```







## 0740. 删除并获得点数

### 题目：

给你一个整数数组 nums ，你可以对它进行一些操作。

每次操作中，选择任意一个 nums[i] ，删除它并获得 nums[i] 的点数。之后，你必须删除 **所有** 等于 nums[i] - 1 和 nums[i] + 1 的元素。

开始你拥有 0 个点数。返回你能通过这些操作获得的最大点数。

**示例 1：**

```
输入：nums = [3,4,2]
输出：6
解释：
删除 4 获得 4 个点数，因此 3 也被删除。
之后，删除 2 获得 2 个点数。总共获得 6 个点数。
```

**示例 2：**

```
输入：nums = [2,2,3,3,3,4]
输出：9
解释：
删除 3 获得 3 个点数，接着要删除两个 2 和 4 。
之后，再次删除 3 获得 3 个点数，再次删除 3 获得 3 个点数。
总共获得 9 个点数。
```

**提示：**

- 1 <= nums.length <= 2 * 10^4
- 1 <= nums[i] <= 10^4



**解题思路：**

选择一个数，需要删除掉nums[i] - 1 和 nums[i] + 1 的元素，并且获得nums[i]个点数，nums[i] - 1 、nums[i] 和 nums[i] + 1 都可能重复出现，所以可以先将相同的元素，累加和统计起来,得到一个dp数组，最后将这个数组的每段可以获得的最大点数求和；

求每段可获得最大点数之和的情况，就是拿到一个点数，就不能再拿和他相邻的点数，也就是打家劫舍的问题，不能同时拿相邻的点数，直至数组为空；

时间复杂度：O(n)

空间复杂度：O(1)  (滚动数组)



**方法：**

```c++
class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        int maxVal = 0;
        for (auto &e : nums)
            maxVal = max(maxVal, e);
        
        vector<int> dp(maxVal + 1, 0);
        for (auto &e : nums)
            dp[e] += e;
        
        return rob(dp);
    }

    int rob(vector<int>& nums)
    {
        int len = nums.size();
        if (len == 2)
            return max(nums[0], nums[1]);
        int a = nums[0], b = max(nums[0], nums[1]), c = 0;
        for (int i = 2; i < len; ++i)
        {
            c = max(a + nums[i], b);
            a = b;
            b = c;
        }
        return c;
    }
};
```







## 0746. 使用最小花费爬楼梯

### 题目：

数组的每个下标作为一个阶梯，第 i 个阶梯对应着一个非负数的体力花费值 cost[i]（下标从 0 开始）。

每当你爬上一个阶梯你都要花费对应的体力值，一旦支付了相应的体力值，你就可以选择向上爬一个阶梯或者爬两个阶梯。

请你找出达到楼层顶部的最低花费。在开始时，你可以选择从下标为 0 或 1 的元素作为初始阶梯。

**示例 1：**

```
输入：cost = [10, 15, 20]
输出：15
解释：最低花费是从 cost[1] 开始，然后走两步即可到阶梯顶，一共花费 15 。
```

**示例 2：**

```
输入：cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
输出：6
解释：最低花费方式是从 cost[0] 开始，逐个经过那些 1 ，跳过 cost[3] ，一共花费 6 。
```

**提示：**

- `cost` 的长度范围是 `[2, 1000]`。
- `cost[i]` 将会是一个整型数据，范围为 `[0, 999]` 。



**解题思路：**

题目要求：可以从 0 或 1 下标出发；

使用一个 len + 1 长度的数组，dp[0] == dp[1] == 0;

$2≤i≤n$，每次到达当前位置所需要的花费为：min(到达前一个位置的花费 + 前一个位置的花费，到达前两个位置的花费 + 前两个位置的花费 )，即：

$dp[i]=min(dp[i−1]+cost[i−1],dp[i−2]+cost[i−2])$



时间复杂度：O(n)

空间复杂度：O(n)，使用滚动数组，可以达到O(1)



**方法：**

```c++
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int len = cost.size();
        vector<int> dp(len + 1, 0);

        for (int i = 2; i <= len; ++i)
            dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
        return dp[len];
    }
};

// 改进
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int len = cost.size();
        int prepreval = 0, preval = 0, curval = 0;

        for (int i = 2; i <= len; ++i)
        {
            curval = min(preval + cost[i - 1], prepreval + cost[i - 2]);
            prepreval = preval;
            preval = curval;
        }
            
        return curval;
    }
};
```







## 0918. 环形子数组的最大和

### 题目：

给定一个由整数数组 `A` 表示的**环形数组 `C`**，求 `C` 的非空子数组的最大可能和。

在此处，环形数组意味着数组的末端将会与开头相连呈环状。（形式上，当`0 <= i < A.length` 时 `C[i] = A[i]`，且当 `i >= 0` 时 `C[i+A.length] = C[i]`）

此外，子数组最多只能包含固定缓冲区 `A` 中的每个元素一次。（形式上，对于子数组 `C[i], C[i+1], ..., C[j]`，不存在 `i <= k1, k2 <= j` 其中 `k1 % A.length = k2 % A.length`）

**示例 1：**

```
输入：[1,-2,3,-2]
输出：3
解释：从子数组 [3] 得到最大和 3
```

**示例 2：**

```
输入：[5,-3,5]
输出：10
解释：从子数组 [5,5] 得到最大和 5 + 5 = 10
```

**示例 3：**

```
输入：[3,-1,2,-1]
输出：4
解释：从子数组 [2,-1,3] 得到最大和 2 + (-1) + 3 = 4
```

**示例 4：**

```
输入：[3,-2,2,-3]
输出：3
解释：从子数组 [3] 和 [3,-2,2] 都可以得到最大和 3
```

**示例 5：**

```
输入：[-2,-3,-1]
输出：-1
解释：从子数组 [-1] 得到最大和 -1
```

**提示：**

1. `-30000 <= A[i] <= 30000`
2. `1 <= A.length <= 30000`



**解题思路：**

会了最大子序和，这题也就明白了。
对于环形数组，分两种情况。
	(1)答案在数组中间，就是最大子序和。例如[1,-2,3,-2]；
	(2)答案在数组两边，例如[5,-3,5]最大的子序和就等于数组的总和SUM-最小的子序和。(一种特殊情况是数组全为负数，也就是SUM-最小子序和==0，最大子序和等于数组中最小的那个)。

时间复杂度：O(n)

空间复杂度：O(1)



**方法：**

```c++
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int len = nums.size();
        if (len == 1)
            return nums[0];

        int maxCurSum = nums[0];
        int maxSum = nums[0];
        int minCurSum = nums[0];
        int minSum = nums[0];
        int Sum = nums[0];

        for (int i = 1; i < len; ++i)
        {
            Sum += nums[i];
            maxCurSum = max(maxCurSum + nums[i], nums[i]);
            maxSum = max(maxCurSum, maxSum);
            minCurSum = min(minCurSum + nums[i], nums[i]);
            minSum = min(minCurSum, minSum);
        }

        // 防止全是负数的情况
        return max(maxSum, Sum - minSum == 0 ? maxSum : (Sum - minSum));
    }
};
```







## 0931. 下降路径最小和

### 题目：

给你一个 `n x n` 的 方形 整数数组 `matrix` ，请你找出并返回通过 `matrix` 的**下降路径** 的 **最小和** 。

**下降路径** 可以从第一行中的任何元素开始，并从每一行中选择一个元素。在下一行选择的元素和当前行所选元素最多相隔一列（即位于正下方或者沿对角线向左或者向右的第一个元素）。具体来说，位置 `(row, col)` 的下一个元素应当是 `(row + 1, col - 1)、(row + 1, col)` 或者 `(row + 1, col + 1)` 。

**示例 1：**

```
输入：matrix = [[2,1,3],[6,5,4],[7,8,9]]
输出：13
解释：下面是两条和最小的下降路径，用加粗+斜体标注：
[[2,1,3],      [[2,1,3],
 [6,5,4],       [6,5,4],
 [7,8,9]]       [7,8,9]]
```

**示例 2：**

```
输入：matrix = [[-19,57],[-40,-5]]
输出：-59
解释：下面是一条和最小的下降路径，用加粗+斜体标注：
[[-19,57],
 [-40,-5]]
```

**示例 3：**

```
输入：matrix = [[-48]]
输出：-48
```

**提示：**

- `n == matrix.length`
- `n == matrix[i].length`
- `1 <= n <= 100`
- `-100 <= matrix[i] [j] <= 100`



**解题思路：**

常规dp思路：创建一个n长的数组，记录第一行的值，依次循环1-n行matrix的每一个元素，判断头顶的元素哪个小，就走哪条路；

时间复杂度：O(n^2)

空间复杂度：O(n)  严格来讲是O(2n)，如果选择二维dp数组，就是O(n^2)，如果直接在原数组上修改，就是O(1)，但直接用修改有点不太合适；



**方法：**

```c++
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        if (n == 1)
            return matrix[0][0];
        vector<int> dp(n, 0);
        int minLen = INT_MAX;
        for (int i = 0; i <n ; ++i)
            dp[i] = matrix[0][i];
        
        for (int i = 1; i < n; ++i)
        {
            vector<int> tmpdp(n, 0);
            for (int j = 0; j < n; ++j)
            {
                if (j == 0)
                    tmpdp[j] = matrix[i][j] + min(dp[j], dp[j + 1]);
                else if (j == n - 1)
                    tmpdp[j] = matrix[i][j] + min(dp[j], dp[j - 1]);
                else
                    tmpdp[j] = matrix[i][j] + min(dp[j], min(dp[j + 1], dp[j - 1]));
            }
            dp = tmpdp;
        }

        for (int i = 0; i < n; ++i)
            minLen = min(minLen, dp[i]);
        return minLen;
    }
};
```







## 1014. 最佳观光组合

### 题目：

给你一个正整数数组 `values`，其中 `values[i]` 表示第 `i` 个观光景点的评分，并且两个景点 `i` 和 `j` 之间的 **距离** 为 `j - i`。

一对景点（`i < j`）组成的观光组合的得分为 `values[i] + values[j] + i - j` ，也就是景点的评分之和 **减去** 它们两者之间的距离。

返回一对观光景点能取得的最高分。

**示例 1：**

```
输入：values = [8,1,5,2,6]
输出：11
解释：i = 0, j = 2, values[i] + values[j] + i - j = 8 + 5 + 0 - 2 = 11
```

**示例 2：**

```
输入：values = [1,2]
输出：2
```

**提示：**

- `2 <= values.length <= 5 * 10^4`
- `1 <= values[i] <= 1000`



**解题思路：**

动态规划：`values[i] + values[j] + i - j`   --->  `values[i] + i + values[j] - j` 

所以只需要保存下遍历到 j 时，前面最大的 mx = values[i] + i；

另外，更新答案时，要先更新ans，后更新mx，因为  i < j；



**方法：**

```c++
class Solution {
public:
    int maxScoreSightseeingPair(vector<int>& values) {
        int mx = values[0];
        int ans = INT_MIN;
        for (int i = 1; i < values.size(); ++i)
        {
            ans = max(ans, mx + values[i] - i);
            mx = max(mx, values[i] + i);
        }
        return ans;
    }
};
```







## 1137. 第N个泰波那契数

### 题目：

泰波那契序列 Tn 定义如下： 

T0 = 0, T1 = 1, T2 = 1, 且在 n >= 0 的条件下 Tn+3 = Tn + Tn+1 + Tn+2

给你整数 n，请返回第 n 个泰波那契数 Tn 的值。

**示例 1：**

```
输入：n = 4
输出：4
解释：
T_3 = 0 + 1 + 1 = 2
T_4 = 1 + 1 + 2 = 4
```

**示例 2：**

```
输入：n = 25
输出：1389537
```

**提示：**

- `0 <= n <= 37`
- 答案保证是一个 32 位整数，即 `answer <= 2^31 - 1`。

**解题思路：**

同0509题：

思路一：循环   O(n)  O(1)

思路二：递归

**思路三：快速矩阵法(注意M矩阵的构建方法)**

首先我们可以构建这样一个递推关系：

$\left[ \begin{matrix} 1 & 1 & 1 \\ 1 & 0 & 0 \\ 0 & 1 & 0 \end{matrix} \right] \left[ \begin{matrix} T(n) \\ T(n - 1) \\ T(n - 2) \end{matrix} \right] = \left[ \begin{matrix} T(n) + T(n - 1) + T(n - 2) \\ T(n) \\ T(n - 1) \end{matrix} \right] = \left[ \begin{matrix} T(n + 1) \\ T(n) \\ T(n - 1) \end{matrix} \right]$

因此：

$\left[ \begin{matrix} T(n + 2) \\ T(n + 1) \\ T(n) \end{matrix} \right] = \left[ \begin{matrix} 1 & 1 & 1 \\ 1 & 0 & 0 \\ 0 & 1 & 0 \end{matrix} \right]^n \left[ \begin{matrix} T(2) \\ T(1) \\ T(0) \end{matrix} \right]$

令：

$M = \left[ \begin{matrix} 1 & 1 & 1 \\ 1 & 0 & 0 \\ 0 & 1 & 0 \end{matrix} \right]$

因此只要我们能快速计算矩阵 $M$ 的 $n$ 次幂，就可以得到 $T(n)$ 的值。如果直接求取 $M^n$ ，时间复杂度是 $O(n)$，可以定义矩阵乘法，然后用快速幂算法来加速这里 $M^n$  的求取。

**方法一：**循环

```c++
class Solution {
public:
    int tribonacci(int n) {
        if (n < 2)
            return n;
        else if (n == 2)
            return 1;
        
        int a = 0, b = 1, c = 1;
        int d = 0;
        for (int i = 3; i <= n; ++i)
        {
            d = a + b + c;
            a = b;
            b = c;
            c = d;
        }
        return d;
    }
};
```

**方法二：**递归

```c++
class Solution {
public:
    int tribonacci(int n) {
        if (n < 2)
            return n;
        else if (n == 2)
            return 1;
        
        return tribonacci(n - 1) + tribonacci(n - 2) + tribonacci( n - 3);
    }
};
```

**方法三：**快速矩阵法

```c++
class Solution {
public:
    int tribonacci(int n) {
        if (n < 2)
            return n;
        else if (n == 2)
            return 1;
        vector<vector<long>> q = {{1, 1, 1}, {1, 0, 0}, {0, 1, 0}};
        vector<vector<long>> ret = matrix_pow(q, n - 2);
        return ret[0][0] + ret[0][1];        
    }

    vector<vector<long>> matrix_pow(vector<vector<long>>& a, int n)
    {
        vector<vector<long>> ret = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
        while (n > 0)
        {
            if (n & 1)
                ret = matrix_multiply(ret, a);
            n >>= 1;
            a = matrix_multiply(a, a);
        }
        return ret;
    }

    vector<vector<long>> matrix_multiply(vector<vector<long>>& a, vector<vector<long>>& b)
    {
        vector<vector<long>> c = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                c[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] + a[i][2] * b[2][j];
        return c;
    }
};
```







## 1143. 最长公共子序列

### 题目：

给定两个字符串 `text1` 和 `text2`，返回这两个字符串的最长 **公共子序列** 的长度。如果不存在 **公共子序列** ，返回 `0` 。

一个字符串的 **子序列** 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。

- 例如，`"ace"` 是 `"abcde"` 的子序列，但 `"aec"` 不是 `"abcde"` 的子序列。

两个字符串的 **公共子序列** 是这两个字符串所共同拥有的子序列。

**示例 1：**

```
输入：text1 = "abcde", text2 = "ace" 
输出：3  
解释：最长公共子序列是 "ace" ，它的长度为 3 。
```

**示例 2：**

```
输入：text1 = "abc", text2 = "abc"
输出：3
解释：最长公共子序列是 "abc" ，它的长度为 3 。
```

**示例 3：**

```
输入：text1 = "abc", text2 = "def"
输出：0
解释：两个字符串没有公共子序列，返回 0 。
```

**提示：**

- `1 <= text1.length, text2.length <= 1000`
- `text1 和 text2 仅由小写英文字符组成。`



**解题思路：**

假设字符串 $\textit{text}_1$ 和 $\textit{text}_2$ 的长度分别为 $m$ 和 $n$，创建 $m+1$ 行 $n+1$ 列的二维数组 $\textit{dp}$，其中 $\textit{dp}[i][j]$ 表示 $\textit{text}_1[0:i]$ 和 $\textit{text}_2[0:j]$ 的最长公共子序列的长度。

- 上述表示中，$\textit{text}_1[0:i]$ 表示 $\textit{text}_1$ 的长度为 $i$ 的前缀，$\textit{text}_2[0:j]$ 表示 $\textit{text}_2$ 的长度为 $j$ 的前缀。

考虑动态规划的边界情况：

- 当 $i=0$ 时，$\textit{text}_1[0:i]$ 为空，空字符串和任何字符串的最长公共子序列的长度都是 00，因此对任意 $0 \le j \le n$，有 $\textit{dp}[0][j]=0$；

- 当 $j=0$ 时，$\textit{text}_2[0:j]$ 为空，同理可得，对任意 $0 \le i \le m$，有 $\textit{dp}[i][0]=0$。

因此动态规划的边界情况是：当 $i=0$ 或 $j=0$ 时，$\textit{dp}[i][j]=0$。

当 $i>0$ 且 $j>0$ 时，考虑 $\textit{dp}[i][j]$ 的计算：

- 当 $\textit{text}_1[i-1]=\textit{text}_2[j-1]$ 时，将这两个相同的字符称为公共字符，考虑 $\textit{text}_1[0:i-1]$ 和 $\textit{text}_2[0:j-1]$ 的最长公共子序列，再增加一个字符（即公共字符）即可得到 $\textit{text}_1[0:i]$ 和 $\textit{text}_2[0:j]$ 的最长公共子序列，因此 $\textit{dp}[i][j]=\textit{dp}[i-1][j-1]+1$。

- 当 $\textit{text}_1[i-1] \ne \textit{text}_2[j-1]$ 时，考虑以下两项：
  - $\textit{text}_1[0:i-1]$ 和 $\textit{text}_2[0:j]$ 的最长公共子序列；
  - $\textit{text}_1[0:i]$ 和 $\textit{text}_2[0:j-1]$ 的最长公共子序列。

要得到 $\textit{text}_1[0:i]$ 和 $\textit{text}_2[0:j]$ 的最长公共子序列，应取两项中的长度较大的一项，因此 $\textit{dp}[i][j]=\max(\textit{dp}[i-1][j],\textit{dp}[i][j-1])$。

由此可以得到如下状态转移方程：

$$
\textit{dp}[i][j] = \begin{cases} \textit{dp}[i-1][j-1]+1, & \textit{text}_1[i-1]=\textit{text}_2[j-1] \\ \max(\textit{dp}[i-1][j],\textit{dp}[i][j-1]), & \textit{text}_1[i-1] \ne \textit{text}_2[j-1] \end{cases}
$$
最终计算得到 $\textit{dp}[m][n]$ 即为 $\textit{text}_1$ 和 $\textit{text}_2$ 的最长公共子序列的长度。



**方法：**

```c++
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.length(), n = text2.length();
        vector<int> dp(n + 1, 0);
        for (int i = 1; i <= m; ++i)
        {
            vector<int> tmpDp(n + 1, 0);
            for (int j = 1; j <= n; ++j)
            {
                if (text1[i - 1] == text2[j - 1])
                    tmpDp[j] = dp[j - 1] + 1;
                else
                    tmpDp[j] = max(dp[j], tmpDp[j - 1]);
            }
            dp = tmpDp;
        }
        return dp[n];
    }
};
```







## 1314. 矩阵区域和

### 题目：

给你一个 `m x n` 的矩阵 `mat` 和一个整数 `k` ，请你返回一个矩阵 `answer` ，其中每个 `answer[i][j]` 是所有满足下述条件的元素 `mat[r][c]` 的和： 

- `i - k <= r <= i + k,`
- `j - k <= c <= j + k` 且
- `(r, c)` 在矩阵内。

**示例 1：**

```
输入：mat = [[1,2,3],[4,5,6],[7,8,9]], k = 1
输出：[[12,21,16],[27,45,33],[24,39,28]]
```

**示例 2：**

```
输入：mat = [[1,2,3],[4,5,6],[7,8,9]], k = 2
输出：[[45,45,45],[45,45,45],[45,45,45]]
```

**提示：**

- `m == mat.length`
- `n == mat[i].length`
- `1 <= m, n, k <= 100`
- `1 <= mat[i] [j] <= 100`



**解题思路：**

思路一：暴力解法

时间复杂度：O(m^2 * n^2)

空间复杂度：O(1)

思路二：动态规划

我们用数组 `P` 表示数组 `mat` 的二维前缀和，`P` 的维数为 `(m + 1) * (n + 1)`，其中 `P[i][j]` 表示数组 `mat` 中以 `(0, 0)` 为左上角，`(i - 1, j - 1)` 为右下角的矩形子数组的元素之和。

题目需要对数组 `mat` 中的每个位置，计算以 `(i - K, j - K)` 为左上角，`(i + K, j + K)` 为右下角的矩形子数组的元素之和，我们可以在前缀和数组的帮助下，通过：

```
sum = P[i + K + 1][j + K + 1] - P[i - K][j + K + 1] - P[i + K + 1][j - K] + P[i - K][j - K]
```


得到元素之和。注意到 `i + K + 1、j + K - 1、i - K` 和 `j - K` 这些下标有可能不在矩阵内，因此对于所有的横坐标，我们需要将其规范在 `[0, m]` 的区间内；对于所有的纵坐标，我们需要将其规范在 `[0, n]` 的区间内。具体地：

`i + K + 1 和 j + K - 1` 分别可能超过 `m` 和 `n`，因此我们需要对这两个坐标与 `m` 和 `n` 取较小值，忽略不在矩阵内的部分；

`i - K 和 j - K` 可能小于 `0`，因此我们需要对这两个坐标与 `0` 取较大值，忽略不在矩阵内的部分。

时间复杂度：O(mn)

空间复杂度：O(mn)



**方法一：**

```c++
class Solution {
public:
    vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> ans(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                for (int r = (i - k < 0 ? 0 : i - k); r <= (i + k >= m ? m - 1 : i + k); ++r)
                {
                    for (int c = (j - k < 0 ? 0 : j - k); c <= (j + k >= n ? n - 1 : j + k); ++c)
                    {
                        ans[i][j] += mat[r][c];
                    }
                }
            }
        }
        return ans;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    int get(vector<vector<int>>& dp, int m, int n, int r, int c)
    {
        r = max(min(r, m), 0);
        c = max(min(c, n), 0);
        return dp[r][c];
    }
    vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        vector<vector<int>> ans(m, vector<int>(n, 0));
        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= n; ++j)
                dp[i][j] = mat[i - 1][j - 1] + dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1];

        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                ans[i][j] = get(dp, m, n, i + k + 1, j + k + 1) - get(dp, m, n, i - k, j + k + 1) - get(dp, m, n, i + k + 1, j - k) + get(dp, m, n, i - k, j - k);
        return ans;
    }
};
```







## 1567. 乘积为正数的最长子数组长度

### 题目：

给你一个整数数组 `nums` ，请你求出乘积为正数的最长子数组的长度。

一个数组的子数组是由原数组中零个或者更多个连续数字组成的数组。

请你返回乘积为正数的最长子数组长度。

**示例 1：**

```
输入：nums = [1,-2,-3,4]
输出：4
解释：数组本身乘积就是正数，值为 24 。
```

**示例 2：**

```
输入：nums = [0,1,-2,-3,-4]
输出：3
解释：最长乘积为正数的子数组为 [1,-2,-3] ，乘积为 6 。
注意，我们不能把 0 也包括到子数组中，因为这样乘积为 0 ，不是正数。
```

**示例 3：**

```
输入：nums = [-1,-2,-3,0,1]
输出：2
解释：乘积为正数的最长子数组是 [-1,-2] 或者 [-2,-3] 。
```

**示例 4：**

```
输入：nums = [-1,2]
输出：1
```

**示例 5：**

```
输入：nums = [1,2,3,5,-6,4,0,10]
输出：4
```

**提示：**

- `1 <= nums.length <= 10^5`
- `-10^9 <= nums[i] <= 10^9`



**解题思路：**

[我是fw](https://leetcode-cn.com/problems/maximum-length-of-subarray-with-positive-product/solution/cheng-ji-wei-zheng-shu-de-zui-chang-zi-shu-zu-ch-3/)



**方法：**

```c++
class Solution {
public:
    int getMaxLen(vector<int>& nums) {
        int len = nums.size();
        int curPositive = (nums[0] > 0);
        int curNegative = (nums[0] < 0);
        int maxLength = curPositive;
        
        for (int i = 1; i < len; ++i)
        {
            if (nums[i] > 0)
            {
                ++curPositive;
                curNegative = curNegative ? curNegative + 1 : 0;
            }
            else if (nums[i] < 0)
            {
                // 负数会改变正负号
                int newPositive = curNegative ? curNegative + 1 : 0;
                int newNegative = curPositive + 1;
                curPositive = newPositive;
                curNegative = newNegative;
            }
            else
            {
                curPositive = curNegative = 0;
            }
            maxLength = max(curPositive, maxLength);
        }
        return maxLength;
    }
};
```





















# 数据结构







## 0001. 两数之和

### 题目：

同Array模块的1题





## 0002. 两数相加

### 题目：

给你两个 **非空** 的链表，表示两个非负的整数。它们每位数字都是按照 **逆序** 的方式存储的，并且每个节点只能存储 **一位** 数字。

请你将两个数相加，并以相同形式返回一个表示和的链表。

你可以假设除了数字 0 之外，这两个数都不会以 0 开头。

**示例1：**

![leetcode_2](F:\C++\刷题\Img\leetcode_2.jpg)

```
输入：l1 = [2,4,3], l2 = [5,6,4]
输出：[7,0,8]
解释：342 + 465 = 807.
```

**示例 2：**

```
输入：l1 = [0], l2 = [0]
输出：[0]
```

**示例 3：**

```
输入：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
输出：[8,9,9,9,0,0,0,1]
```

**提示：**

- 每个链表中的节点数在范围 [1, 100] 内
- 0 <= Node.val <= 9
- 题目数据保证列表表示的数字不含前导零



**解题思路：**

挨个加，进位

时间复杂度：O(max(m,n))

空间复杂度：O(1）

**方法：**

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* ret;
        ListNode* l;
        ret = new ListNode(0);
        l = ret;
        int temp = 0;
        bool flag = false;
        while(l1 != nullptr && l2 != nullptr)
        {
            l->next = new ListNode(l1->val + l2->val);
            l = l->next;
            l1 = l1->next;
            l2 = l2->next;
        }

        while(l1)
        {
            l->next = new ListNode(l1->val);
            l = l->next;
            l1 = l1->next;
        }

        while(l2)
        {
            l->next = new ListNode(l2->val);
            l = l->next;
            l2 = l2->next;
        }

        l = ret->next;

        while(l)
        {
            if (l->val > 9)
            {
                l->val -= 10;
                if(l->next == nullptr)
                {
                    l->next = new ListNode(0);
                }
                l->next->val += 1;
            }
            l = l->next;
        }

        return ret->next;
    }
};
```





## 0005. 最长回文子串

### 题目：

同动态规划模块的5题





## 0015. 三数之和

### 题目：

同Array模块的15题





## 0020. 有效的括号

### 题目：

给定一个只包括 `'('，')'，'{'，'}'，'['，']'` 的字符串 `s` ，判断字符串是否有效。

有效字符串需满足：

1. 左括号必须用相同类型的右括号闭合。
2. 左括号必须以正确的顺序闭合。

**示例 1：**

```
输入：s = "()"
输出：true
```

**示例 2：**

```
输入：s = "()[]{}"
输出：true
```

**示例 3：**

```
输入：s = "(]"
输出：false
```

**示例 4：**

```
输入：s = "([)]"
输出：false
```

**示例 5：**

```
输入：s = "{[]}"
输出：true
```

**提示：**

- `1 <= s.length <= 104`
- `s` 仅由括号 `'()[]{}'` 组成



**解题思路：**

使用栈

时间复杂度：O(n)

空间复杂度：O(n+∣Σ∣)，其中 Σ 表示字符集，本题中字符串只包含 6 种括号，∣Σ∣=6。栈中的字符数量为 O(n)，而哈希表使用的空间为 O(∣Σ∣)，相加即可得到总空间复杂度。



**方法：**

```c++
class Solution {
public:
    bool isValid(string s) {
        int n = s.length();
        if (n % 2 == 1)
            return false;
        stack<char> st;
        for (int i = 0; i < n; ++i)
        {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{')
                st.push(s[i]);
            else if ( (s[i] == ')' && !st.empty() && st.top() == '(') || 
                        (s[i] == '}' && !st.empty() && st.top() == '{') || 
                        (s[i] == ']' && !st.empty() && st.top() == '['))
                st.pop();
            else
                return false;        
        }
        return st.empty();
    }
};
```





## 0021. 合并两个有序链表

### 题目：

将两个升序链表合并为一个新的 **升序** 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 

**示例 1：**

![leetcode_0021](F:\C++\刷题\Img\leetcode_0021.jpg)

```
输入：l1 = [1,2,4], l2 = [1,3,4]
输出：[1,1,2,3,4,4]
```

**示例 2：**

```
输入：l1 = [], l2 = []
输出：[]
```

**示例 3：**

```
输入：l1 = [], l2 = [0]
输出：[0]
```

**提示：**

- 两个链表的节点数目范围是 `[0, 50]`
- `-100 <= Node.val <= 100`
- `l1` 和 `l2` 均按 **非递减顺序** 排列



**解题思路：**

思路一：常规思路

思路二：递归



**方法一：**

```c++
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr)
            return l2;
        if (l2 == nullptr)
            return l1;
        ListNode* lhead = new ListNode(-1);
        ListNode* l = lhead;
        while (l1 != nullptr && l2 != nullptr)
        {
            if (l1->val < l2->val)
            {
                l->next = l1;
                l1 = l1->next;
            }
            else
            {
                l->next = l2;
                l2 = l2->next;
            }
            l = l->next;
        }
        l->next = l1 == nullptr ? l2 : l1;

        return lhead->next;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr)
            return l2;
        if (l2 == nullptr)
            return l1;
        if (l1->val < l2->val)
        {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }
        else
        {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }
};
```





## 0024. 两两交换链表中的节点

### 题目：

给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。

**你不能只是单纯的改变节点内部的值**，而是需要实际的进行节点交换。

**示例 1：**

![leetcode_0024](F:\C++\刷题\Img\leetcode_0024.jpg)

```
输入：head = [1,2,3,4]
输出：[2,1,4,3]
```

**示例 2：**

```
输入：head = []
输出：[]
```

**示例 3：**

```
输入：head = [1]
输出：[1]
```

**提示：**

- 链表中节点的数目在范围 `[0, 100]` 内
- `0 <= Node.val <= 100`

**解题思路：**

思路一：递归

时间复杂度：O(n)

空间复杂度：O(n)

思路二：迭代

使用一个**哑结点**

时间复杂度：O(n)

空间复杂度：O(1)



**方法一：**

```c++
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode* back = swapPairs(head->next->next);
        ListNode* tmp = head->next;
        tmp->next = head;
        head->next = back;
        return tmp;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode* res = new ListNode(0, head);
        ListNode* temp = res;
        while (temp->next != nullptr && temp->next->next != nullptr)
        {
            ListNode* p = temp->next;
            ListNode* q = temp->next->next;
            temp->next = q;
            p->next = q->next;
            q->next = p;
            temp = temp->next->next;
        }

        return res->next;
    }
};
```





## 0025. K个一组翻转链表

### 题目：

给你一个链表，每 `k` 个节点一组进行翻转，请你返回翻转后的链表。

`k` 是一个正整数，它的值小于或等于链表的长度。

如果节点总数不是 `k` 的整数倍，那么请将最后剩余的节点保持原有顺序。

**进阶：**

- 你可以设计一个只使用常数额外空间的算法来解决此问题吗？
- **你不能只是单纯的改变节点内部的值**，而是需要实际进行节点交换。

**示例 1：**

![leetcode_25_1](F:\C++\刷题\Img\leetcode_25_1.jpg)

```
输入：head = [1,2,3,4,5], k = 2
输出：[2,1,4,3,5]
```

**示例 2：**

![leetcode_25_2](F:\C++\刷题\Img\leetcode_25_2.jpg)

```
输入：head = [1,2,3,4,5], k = 3
输出：[3,2,1,4,5]
```

**示例 3：**

```
输入：head = [1,2,3,4,5], k = 1
输出：[1,2,3,4,5]
```

**示例 4：**

```
输入：head = [1], k = 1
输出：[1]
```

**提示：**

- 列表中节点的数量在范围 `sz` 内
- `1 <= sz <= 5000`
- `0 <= Node.val <= 1000`
- `1 <= k <= sz`



**解题思路：**

常规思路

**方法：**

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */


class Solution {
public:
    pair<ListNode*, ListNode*> myReverse(ListNode* head, ListNode* tail)
    {
        ListNode* prev = tail->next;
        ListNode* p = head;
        while (prev != tail)
        {
            ListNode* nex = p->next;
            p->next = prev;
            prev = p;
            p = nex;
        }
        return {tail, head};
    }


    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == nullptr || head->next == nullptr || k == 1)
            return head;
        ListNode* dummy = new ListNode(0, head);
        ListNode* p = dummy;
        while (p->next != nullptr)
        {
            ListNode* start = p->next;
            ListNode* end = start;
            for (int i = 0; i < k - 1; ++i)
            {
                end = end->next;
                if (!end)
                    return dummy->next;
            }

            ListNode* nex = end->next;
            tie(start, end) = myReverse(start, end);
            p->next = start;
            end->next = nex;
            p = end;
        }
        return dummy->next;
    }
};
```





## 0036. 有效的数独

### 题目：

同Array模块的36题





## 0043. 字符串相乘

### 题目：

给定两个以字符串形式表示的非负整数 `num1` 和 `num2`，返回 `num1` 和 `num2` 的乘积，它们的乘积也表示为字符串形式。

**示例 1:**

```
输入: num1 = "2", num2 = "3"
输出: "6"
```

**示例 2:**

```
输入: num1 = "123", num2 = "456"
输出: "56088"
```

**说明：**

1. `num1 和 num2 的长度小于110。`
2. num1 和 num2 只包含数字 0-9。
3. `num1 和 num2 均不以零开头，除非是数字 0 本身。`
4. 不能使用任何标准库的大数类型（比如 BigInteger）或直接将输入转换为整数来处理。

**解题思路：**

思路一：常规字符挨个相乘相加

时间复杂度：O(mn+n^2)

空间复杂度：O(m+n)

**思路二：常见一个 m + n 数组，利用卷积知识**

时间复杂度：O(mn)

空间复杂度：O(m+n)



**方法一：**

```c++
class Solution {
public:
    string MultString(string& str, char c)
    {
        string tmp;
        int sign = 0;
        for (int i = 0; i < str.size(); ++i)
        {
            int mul = (str[i] - '0') * (c - '0') + sign;
            if (mul >= 10)
            {
                sign = mul / 10;
                mul %= 10;
            }
            else
                sign = 0;
            tmp += (mul + '0');
        }
        if (sign != 0)
            tmp += (sign + '0');
        return tmp;
    }
    char AddItem(char& c1, char& c2, int& sign)
    {
        int tmp = (c1 - '0') + (c2 - '0') + sign;
        if (tmp >= 10)
        {
            sign = tmp / 10;
            tmp %= 10;
        }
        else
            sign = 0;
        return tmp + '0';
    }
    string MoveAdd(string& res, string& str2, int k)
    {
        int sign = 0;
        int i = k;
        int j = 0;
        while (i < res.size())
        {
            res[i] = AddItem(res[i], str2[j], sign);
            ++i;
            ++j;
        }
        char zero = '0';
        while (j < str2.size())
        {
            res += AddItem(zero, str2[j], sign);
            ++j;
        }
        if (sign != 0)
            res += (sign + '0');
        return res;
    }
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0")
            return string("0");
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());

        string sum("0");
        string tmp;
        for (int i = 0; i < num2.size(); ++i)
        {
            tmp = MultString(num1, num2[i]);
            MoveAdd(sum, tmp, i);
            tmp.clear();
        }

        reverse(sum.begin(), sum.end());
        return sum;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0")
            return "0";
        int m = num1.size(), n = num2.size();
        vector<int> arr(m + n, 0);
        for (int i = m - 1; i >= 0; --i)
        {
            int x = num1[i] - '0';
            for (int j = n - 1; j >= 0; --j)
            {
                int y = num2[j] - '0';
                arr[i + j + 1] += x * y;
            }
        }

        for (int i = m + n - 1; i > 0; --i)
        {
            arr[i - 1] += arr[i] / 10;
            arr[i] %= 10;
        }

        int i = 0;
        while (arr[i] == 0 && i < m + n)
            ++i;
        string ans;
        while (i < m + n)
            ans += (arr[i++] + '0');
        return ans;
    }
};
```





## 0046. 全排列

### 题目：

给定一个不含重复数字的数组 `nums` ，返回其 **所有可能的全排列** 。你可以 **按任意顺序** 返回答案。

 

**示例 1：**

```
输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
```

**示例 2：**

```
输入：nums = [0,1]
输出：[[0,1],[1,0]]
```

**示例 3：**

```
输入：nums = [1]
输出：[[1]]
```

**提示：**

- `1 <= nums.length <= 6`
- `-10 <= nums[i] <= 10`
- `nums` 中的所有整数 **互不相同**



**解题思路：**

这个问题可以看作有 $n$ 个排列成一行的空格，我们需要从左往右依此填入题目给定的 $n$ 个数，每个数只能使用一次。那么很直接的可以想到一种穷举的算法，即从左往右每一个位置都依此尝试填入一个数，看能不能填完这 $n$ 个空格，在程序中我们可以用「回溯法」来模拟这个过程。

我们定义递归函数 $backtrack(first, output)$ 表示从左往右填到第 $\textit{first}$ 个位置，当前排列为 $\textit{output}$。 那么整个递归函数分为两个情况：

如果 $\textit{first}==n$，说明我们已经填完了 $n$ 个位置（注意下标从 $0$ 开始），找到了一个可行的解，我们将 $\textit{output}$ 放入答案数组中，递归结束。
如果 $\textit{first}<n$，我们要考虑这第 $\textit{first}$ 个位置我们要填哪个数。根据题目要求我们肯定不能填已经填过的数，因此很容易想到的一个处理手段是我们定义一个标记数组 $\textit{vis}[]$ 来标记已经填过的数，那么在填第 $\textit{first}$ 个数的时候我们遍历题目给定的 $n$ 个数，如果这个数没有被标记过，我们就尝试填入，并将其标记，继续尝试填下一个位置，即调用函数 $backtrack(first + 1, output)$。回溯的时候要撤销这一个位置填的数以及标记，并继续尝试其他没被标记过的数。



**方法：**

```c++
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> res;
        
        backtrace(res, nums, 0, n);
        return res;
    }

    void backtrace(vector<vector<int>>& res, vector<int>& output, int first, int end)
    {
        if (first == end)
        {
            res.push_back(output);
            return;
        }

        for (int i = first; i < end; ++i)
        {
            swap(output[i], output[first]);
            backtrace(res, output, first + 1, end);
            swap(output[i], output[first]);
        }
    }
};
```





## 0047. 全排列Ⅱ

### 题目：

给定一个可包含重复数字的序列 `nums` ，**按任意顺序** 返回所有不重复的全排列。

**示例 1：**

```
输入：nums = [1,1,2]
输出：
[[1,1,2],
 [1,2,1],
 [2,1,1]]
```

**示例 2：**

```
输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
```

**提示：**

- `1 <= nums.length <= 8`
- `-10 <= nums[i] <= 10`

**解题思路：**

方法等同于46题的全排列，但不同的是需要去重

在去重时，使用vis数组来标记数组nums某个值是否被使用，每一层递归使用for循环遍历，并判断vis[i]是否被使用，具体去重条件：

- vis[i] : 表示这个位置的数已经被使用；
- i > 0 && nums[i] == nums[i - 1] ： 主要是防止两个连续的数相同
- for循环保证了从数组中从前往后一个一个取值，再用if判断条件。所以nums[i - 1]一定比nums[i]先被取值和判断。如果nums[i - 1]被取值了，那vis[i - 1]会被置1，只有当递归再回退到这一层时再将它置0。每递归一层都是在寻找数组对应于递归深度位置的值，每一层里用for循环来寻找。所以当vis[i - 1] == 1时，说明nums[i - 1]和nums[i]分别属于两层递归中，也就是我们要用这两个数分别放在数组的两个位置，这时不需要去重。但是当vis[i - 1] == 0时，说明nums[i - 1]和nums[i]属于同一层递归中（只是for循环进入下一层循环），也就是我们要用这两个数放在数组中的同一个位置上，这就是我们要去重的情况。



**方法：**

```c++
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
```





## 0048. 旋转图像

### 题目：

同Array模块的48题





## 0049. 字母异位词分组

### 题目：

给你一个字符串数组，请你将 **字母异位词** 组合在一起。可以按任意顺序返回结果列表。

**字母异位词** 是由重新排列源单词的字母得到的一个新单词，所有源单词中的字母都恰好只用一次。

**示例 1:**

```
输入: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
输出: [["bat"],["nat","tan"],["ate","eat","tea"]]
```

**示例 2:**

```
输入: strs = [""]
输出: [[""]]
```

**示例 3:**

```
输入: strs = ["a"]
输出: [["a"]]
```

**提示：**

- `1 <= strs.length <= 10^4`
- `0 <= strs[i].length <= 100`
- `strs[i]` 仅包含小写字母



**解题思路：**

使用hash表，unordered_map<string, vector<string>> map;

时间复杂度：O(nklogk)

空间复杂度：O(nk)



**方法：**

```c++
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
```





## 0053. 最大子序和

### 题目：

同Array模块的53题





## 0056. 合并区间

### 题目：

同Array模块的56题





## 0059. 螺旋矩阵Ⅱ

### 题目：

同Array模块的59题





## 0073. 矩阵置零

### 题目：

同Array模块的73题





## 0075. 颜色分类

### 题目：

同Array模块的75题





## 0082. 删除排序链表中的重复元素Ⅱ

### 题目：

存在一个按升序排列的链表，给你这个链表的头节点 `head` ，请你删除链表中所有存在数字重复情况的节点，只保留原始链表中 **没有重复出现** 的数字。

返回同样按升序排列的结果链表。

**示例 1：**

![leetcode_82_1](F:\C++\刷题\Img\leetcode_82_1.jpg)

```
输入：head = [1,2,3,3,4,4,5]
输出：[1,2,5]
```

**示例 2：**

![leetcode_82_2](F:\C++\刷题\Img\leetcode_82_2.jpg)

```
输入：head = [1,1,1,2,3]
输出：[2,3]
```

**提示：**

- 链表中节点数目在范围 `[0, 300]` 内
- `-100 <= Node.val <= 100`
- 题目数据保证链表已经按升序排列

**解题思路：**

技巧：ListNode* dummy = new ListNode(0, head);

时间复杂度：O(n)

空间复杂度：O(1)

**方法：**

```c++
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;
        ListNode* dummy = new ListNode(0, head);
        ListNode* cur = dummy;

        while (cur->next && cur->next->next)
        {
            if (cur->next->val == cur->next->next->val)
            {
                int x = cur->next->val;
                while (cur->next && cur->next->val == x)
                    cur->next = cur->next->next;
            }
            else
                cur = cur->next;
        }
        
        return dummy->next;
    }
};
```





## 0083. 删除排序链表中的重复元素

### 题目：

存在一个按升序排列的链表，给你这个链表的头节点 `head` ，请你删除所有重复的元素，使每个元素 **只出现一次** 。

返回同样按升序排列的结果链表。

 

**示例 1：**

![leetcode_83_1](F:\C++\刷题\Img\leetcode_83_1.jpg)

```
输入：head = [1,1,2]
输出：[1,2]
```

**示例 2：**

![leetcode_83_2](F:\C++\刷题\Img\leetcode_83_2.jpg)

```
输入：head = [1,1,2,3,3]
输出：[1,2,3]
```

**提示：**

- 链表中节点数目在范围 `[0, 300]` 内
- `-100 <= Node.val <= 100`
- 题目数据保证链表已经按升序排列



**解题思路：**

思路一：迭代法

时间复杂度：O(n)

空间复杂度：O(1)

思路二：递归

时间复杂度：O(n)

空间复杂度：O(1)



**方法一：**

```c++
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;
        
        ListNode* prev = head;
        ListNode* cur = head->next;
        while (cur != nullptr)
        {
            if (prev->val == cur->val)
            {
                ListNode* tmp = cur;
                prev->next = cur->next;
                delete tmp;  // 这里不能用free
                cur = prev->next;
            }
            else
            {
                prev = cur;
                cur = cur->next;
            }
        }
        return head;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;
        
        ListNode* newHead = deleteDuplicates(head->next);
        if (head->val == head->next->val)
        {
            ListNode* del = head->next;
            head->next = head->next->next;
            delete del;
        }
        return head;
    }
};
```





## 0088. 合并两个有序数组

### 题目：

给你两个按 **非递减顺序** 排列的整数数组 `nums1` 和 `nums2`，另有两个整数 `m` 和 `n` ，分别表示 `nums1` 和 `nums2` 中的元素数目。

请你 **合并** `nums2` 到 `nums1` 中，使合并后的数组同样按 **非递减顺序** 排列。

**注意**：最终，合并后数组不应由函数返回，而是存储在数组 `nums1` 中。为了应对这种情况，`nums1` 的初始长度为 `m + n`，其中前 `m` 个元素表示应合并的元素，后 `n` 个元素为 `0` ，应忽略。`nums2` 的长度为 `n` 。

**示例 1：**

```
输入：nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
输出：[1,2,2,3,5,6]
解释：需要合并 [1,2,3] 和 [2,5,6] 。
合并结果是 [1,2,2,3,5,6] ，其中斜体加粗标注的为 nums1 中的元素。
```

**示例 2：**

```
输入：nums1 = [1], m = 1, nums2 = [], n = 0
输出：[1]
解释：需要合并 [1] 和 [] 。
合并结果是 [1] 。
```

**示例 3：**

```
输入：nums1 = [0], m = 0, nums2 = [1], n = 1
输出：[1]
解释：需要合并的数组是 [] 和 [1] 。
合并结果是 [1] 。
注意，因为 m = 0 ，所以 nums1 中没有元素。nums1 中仅存的 0 仅仅是为了确保合并结果可以顺利存放到 nums1 中。
```

**提示：**

- `nums1.length == m + n`
- `nums2.length == n`
- `0 <= m, n <= 200`
- `1 <= m + n <= 200`
- `-10^9 <= nums1[i], nums2[j] <= 10^9`



**解题思路：**

思路一：排序

把nums2的值先放到nums1后面，然后排序

时间复杂度：$O((m+n)\log(m+n))$

空间复杂度：$O(\log(m+n))$

思路二：借助中间变量

时间复杂度：$O(m+n)$

空间复杂度：$O(m+n)$

思路三：逆向插入

时间复杂度：$O(m+n)$

空间复杂度：$O(1)$



**方法：**

```c++
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1, j = n - 1, k = m + n - 1;
        while (i >= 0 && j >= 0)
        {
            if (nums1[i] > nums2[j])
                nums1[k--] = nums1[i--];
            else
                nums1[k--] = nums2[j--];
        }

        while (i >= 0)
            nums1[k--] = nums1[i--];
        while (j >= 0)
            nums1[k--] = nums2[j--];
    }
};
```





## 0094. 二叉树的中序遍历

### 题目：

给定一个二叉树的根节点 `root` ，返回它的 **中序** 遍历。

**示例 1：**

![leetcode_94_1](F:\C++\刷题\Img\leetcode_94_1.jpg)

```
输入：root = [1,null,2,3]
输出：[1,3,2]
```

**示例 2：**

```
输入：root = []
输出：[]
```

**示例 3：**

```
输入：root = [1]
输出：[1]
```

**示例 4：**

![leetcode_94_2](F:\C++\刷题\Img\leetcode_94_2.jpg)

```
输入：root = [1,2]
输出：[2,1]
```

**示例 5：**

![leetcode_94_3](F:\C++\刷题\Img\leetcode_94_3.jpg)

```
输入：root = [1,null,2]
输出：[1,2]
```

**提示：**

- 树中节点数目在范围 `[0, 100]` 内
- `-100 <= Node.val <= 100`



**解题思路：**

思路一：递归

时间复杂度：O(n)

空间复杂度：O(n)

思路二：迭代

时间复杂度：O(n)

空间复杂度：O(n)

思路三：Morris遍历

[Morris遍历](https://leetcode-cn.com/problems/binary-tree-preorder-traversal/solution/leetcodesuan-fa-xiu-lian-dong-hua-yan-shi-xbian-2/)

时间复杂度：O(n)

空间复杂度：O(1)

**方法一：**

```c++
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        if (root == nullptr)
            return vector<int>();
        vector<int> res;
        _inorderTraversal(root, res);
        return res;
    }
    void _inorderTraversal(TreeNode* node, vector<int>& res)
    {
        if (node == nullptr)
            return;
        _inorderTraversal(node->left, res);
        res.push_back(node->val);
        _inorderTraversal(node->right, res);
    }
};
```

**方法二：**

```c++
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        if (root == nullptr)
            return vector<int>();
        vector<int> res;
        
        stack<TreeNode*> st;
        while (!st.empty() || root != nullptr)
        {
            while (root != nullptr)
            {
                st.push(root);
                root = root->left;
            }

            TreeNode* node = st.top();
            st.pop();
            res.push_back(node->val);

            if (node->right != nullptr)
                root = node->right;
        }
        return res;
    }
};
```

**方法三：**

```c++
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        if (root == nullptr)
            return vector<int>();
        vector<int> res;
        
        TreeNode* cur1 = root;
        TreeNode* cur2 = nullptr;
        while (cur1 != nullptr)
        {
            cur2 = cur1->left;
            if (cur2 != nullptr)
            {
                while (cur2->right != nullptr && cur2->right != cur1)
                    cur2 = cur2->right;
                if (cur2->right == nullptr)
                {
                    cur2->right = cur1;
                    cur1 = cur1->left;
                    continue;
                }
                else
                    cur2->right = nullptr;
            }
            res.push_back(cur1->val);
            cur1 = cur1->right;
        }
        return res;
    }
};
```





## 0098. 验证二叉搜索树

### 题目：

给你一个二叉树的根节点 `root` ，判断其是否是一个有效的二叉搜索树。

**有效** 二叉搜索树定义如下：

- 节点的左子树只包含 **小于** 当前节点的数。
- 节点的右子树只包含 **大于** 当前节点的数。
- 所有左子树和右子树自身必须也是二叉搜索树。

**示例 1：**

![leetcode_98_1](F:\C++\刷题\Img\leetcode_98_1.jpg)

```
输入：root = [2,1,3]
输出：true
```

**示例 2：**

![leetcode_98_2](F:\C++\刷题\Img\leetcode_98_2.jpg)

```
输入：root = [5,1,4,null,null,3,6]
输出：false
解释：根节点的值是 5 ，但是右子节点的值是 4 。
```

**提示：**

- 树中节点数目范围在`[1, 10^4]` 内
- `-2^31 <= Node.val <= 2^31 - 1`



**解题思路：**

思路一：递归

时间复杂度：O(n)

空间复杂度：O(n)

思路二：中序遍历

时间复杂度：O(n)

空间复杂度：O(n)

**方法一：**

```c++
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return helper(root, LONG_MIN, LONG_MAX);
    }
    bool helper(TreeNode* node, long long lower, long long upper)
    {
        if (node == nullptr)
            return true;
        if (node->val <= lower || node->val >= upper)
            return false;
        return helper(node->left, lower, node->val) && helper(node->right, node->val, upper);
    }
};
```

**思路二：**

```c++
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        stack<TreeNode*> st;
        long long flag = (long long)INT_MIN - 1;
        while (!st.empty() || root != nullptr)
        {
            while (root != nullptr)
            {
                st.push(root);
                root = root->left;
            }

            root = st.top(), st.pop();
            if (root->val <= flag)
                return false;

            flag = root->val;
            root = root->right;
        }
        return true;
    }
};
```





## 0101. 对称二叉树

### 题目：

给定一个二叉树，检查它是否是镜像对称的。

例如，二叉树 `[1,2,2,3,4,4,3]` 是对称的。

```
	1
   / \
  2   2
 / \ / \
3  4 4  3
```


但是下面这个 `[1,2,2,null,3,null,3]` 则不是镜像对称的:

```
	1
   / \
  2   2
   \   \
   3    3
```

**解题思路：**

思路一：迭代

时间复杂度：O(n)

空间复杂度：O(n)

思路二：递归

时间复杂度：O(n)

空间复杂度：O(n)



**方法一：**

```c++
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr)
            return true;
        return check(root, root);
    }

    bool check(TreeNode* LNode, TreeNode* RNode)
    {
        queue<TreeNode*> dq;
        dq.push(LNode);
        dq.push(RNode);
        while (!dq.empty())
        {
            TreeNode* l = dq.front();
            dq.pop();
            TreeNode* r = dq.front();
            dq.pop();

            if (!l && !r)
                continue;
            if ((!l || !r) || (l->val != r->val))
                return false;
            dq.push(l->left);
            dq.push(r->right);

            dq.push(l->right);
            dq.push(r->left);
        }
        return true;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr)
            return true;
        return check(root, root);
    }

    bool check(TreeNode* l, TreeNode* r)
    {
        if (!l && !r)
            return true;
        if ((!l || !r) || (l->val != r->val))
            return false;
        return check(l->left, r->right) && check(l->right, r->left);
    }
};
```





## 0102. 二叉树的层序遍历

### 题目：

给你一个二叉树，请你返回其按 **层序遍历** 得到的节点值。 （即逐层地，从左到右访问所有节点）。

**示例：**
二叉树：`[3,9,20,null,null,15,7]`,

```
    3
   / \
  9  20
    /  \
   15   7
```

返回其层序遍历结果：

```
[
  [3],
  [9,20],
  [15,7]
]
```



**解题思路：**

使用队列，每次进入while循环，记录当前队列的大小，即为当前层的数量，再用一个内部for循环；

时间复杂度：O(n)

空间复杂度：O(n)

**方法：**

```c++
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (root == nullptr)
            return vector<vector<int>>();
        
        queue<TreeNode*> dq;
        vector<vector<int>> res;
        dq.push(root);
        while (!dq.empty())
        {
            int curLevelSize = dq.size();
            vector<int> tmp;
            for (int i = 0; i < curLevelSize; ++i)
            {
                TreeNode* node = dq.front();
                dq.pop();
                tmp.push_back(node->val);
                if (node->left != nullptr)
                    dq.push(node->left);
                if (node->right != nullptr)
                    dq.push(node->right);
            }
            res.push_back(tmp);
        }
        return res;
    }
};
```





## 0103. 二叉树的锯齿形层序遍历

### 题目：

给定一个二叉树，返回其节点值的锯齿形层序遍历。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。

例如：
给定二叉树 `[3,9,20,null,null,15,7]`,

```
	3
   / \
  9  20
    /  \
   15   7
```

返回锯齿形层序遍历如下：

```
[
  [3],
  [20,9],
  [15,7]
]
```



**解题思路：**

基本层序遍历，奇数层顺序，偶数层逆序，使用双端队列

时间复杂度：O(n)

空间复杂度：O(n)

**方法：**

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (!root)
            return res;
        
        int level = 0;
        deque<TreeNode*> dq;
        dq.push_back(root);

        while (!dq.empty())
        {
            ++level;
            int level_size = dq.size();
            vector<int> tmp;
            if (level % 2 == 1)
            {
                while (level_size-- > 0)
                {
                    TreeNode* node = dq.front();
                    dq.pop_front();
                    tmp.push_back(node->val);
                    if (node->left)
                        dq.push_back(node->left);
                    if (node->right)
                        dq.push_back(node->right);
                }
            }
            else
            {
                while (level_size-- > 0)
                {
                    TreeNode* node = dq.back();
                    dq.pop_back();
                    tmp.push_back(node->val);
                    if (node->right)
                        dq.push_front(node->right);
                    if (node->left)
                        dq.push_front(node->left);
                }
            }
            res.push_back(tmp);
            tmp.clear();
        }
        return res;
    }
};
```





## 0104. 二叉树的最大深度

### 题目：

给定一个二叉树，找出其最大深度。

二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。

**说明**: 叶子节点是指没有子节点的节点。

**示例：**
给定二叉树 `[3,9,20,null,null,15,7]`，

```
	3
   / \
  9  20
    /  \
   15   7
```

返回它的最大深度 3 。

**解题思路：**

思路一：DFS

时间复杂度：O(n)

空间复杂度：O(height)

思路二：BFS

时间复杂度：O(n)

空间复杂度：O(n)

**方法一：**

```c++
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr)
            return 0;
        return root == nullptr ? 0 : max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr)
            return 0;
        queue<TreeNode*> dq;
        dq.push(root);
        int level = 0;
        while (!dq.empty())
        {
            int curLevelSize = dq.size();
            while (curLevelSize-- > 0)
            {
                TreeNode* node = dq.front();
                dq.pop();
                if (node->left != nullptr)
                    dq.push(node->left);
                if (node->right != nullptr)
                    dq.push(node->right);
            }
            ++level;
        }
        return level;
    }
};
```





## 0105. 从前序与中序遍历序列构造二叉树

### 题目：

给定一棵树的前序遍历 `preorder` 与中序遍历 `inorder`。请构造二叉树并返回其根节点。

**示例 1:**

![leetcode_105](F:\C++\刷题\Img\leetcode_105.jpg)

```
Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]
```

**示例 2:**

```
Input: preorder = [-1], inorder = [-1]
Output: [-1]
```

**提示:**

- `1 <= preorder.length <= 3000`
- `inorder.length == preorder.length`
- `-3000 <= preorder[i], inorder[i] <= 3000`
- `preorder` 和 `inorder` 均无重复元素
- `inorder` 均出现在 `preorder`
- `preorder` 保证为二叉树的前序遍历序列
- `inorder` 保证为二叉树的中序遍历序列



**解题思路：**

思路一：递归

时间复杂度：O(n)

空间复杂度：O(n)

思路二：迭代

时间复杂度：O(n)

空间复杂度：O(n)

**方法一：**

```c++
class Solution {
private:
    unordered_map<int, int> map;
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        for (int i = 0; i < inorder.size(); ++i)
            map[inorder[i]] = i;
        return _buildTree(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
    }

    TreeNode* _buildTree(vector<int>& preorder, vector<int>& inorder, int pre_left, int pre_right, int in_left, int in_right) {
        if (pre_left > pre_right)
            return nullptr;
        
        int i = map[preorder[pre_left]];
        int left_size = i - in_left;

        TreeNode* root = new TreeNode(preorder[pre_left]);
        root->left = _buildTree(preorder, inorder, pre_left + 1, pre_left + left_size, in_left, i - 1);
        root->right = _buildTree(preorder, inorder, pre_left + left_size + 1, pre_right, i + 1, in_right);

        return root;
    }
};
```

**方法二：**

```c++
class Solution {
private:
    unordered_map<int, int> map;
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (!preorder.size())
            return nullptr;
        TreeNode* root = new TreeNode(preorder[0]);
        stack<TreeNode*> stk;
        stk.push(root);
        int inorderIndex = 0;
        for (int i = 1; i < preorder.size(); ++i)
        {
            int preorderVal = preorder[i];
            TreeNode* node = stk.top();
            if (node->val != inorder[inorderIndex])
            {
                node->left = new TreeNode(preorderVal);
                stk.push(node->left);
            }
            else
            {
                while (!stk.empty() && stk.top()->val == inorder[inorderIndex])
                {
                    node = stk.top();
                    stk.pop();
                    ++inorderIndex;
                }
                node->right = new TreeNode(preorderVal);
                stk.push(node->right);
            }
        }
        return root;
    }
};
```





## 0108. 将有序数组转换为二叉搜索树

### 题目：

给你一个整数数组 `nums` ，其中元素已经按 **升序** 排列，请你将其转换为一棵 **高度平衡** 二叉搜索树。

**高度平衡** 二叉树是一棵满足「每个节点的左右两个子树的高度差的绝对值不超过 1 」的二叉树。

**示例 1：**

![leetcode_108_1](F:\C++\刷题\Img\leetcode_108_1.jpg)

```
输入：nums = [-10,-3,0,5,9]
输出：[0,-3,9,-10,null,5]
解释：[0,-10,5,null,-3,null,9] 也将被视为正确答案：
```

![leetcode_108_2](F:\C++\刷题\Img\leetcode_108_2.jpg)

**示例2：**

![leetcode_108_3](F:\C++\刷题\Img\leetcode_108_3.jpg)

```
输入：nums = [1,3]
输出：[3,1]
解释：[1,3] 和 [3,1] 都是高度平衡二叉搜索树。
```

**提示：**

- `1 <= nums.length <= 10^4`
- `-10^4 <= nums[i] <= 10^4`
- `nums` 按 **严格递增** 顺序排列



**解题思路：**

​		// 总是选择中间位置左边的数字作为根节点
​        // int mid = ((left + right) >> 1);
​        // 总是选择中间位置右边的数字作为根节点
​        // int mid = ((left + right + 1) >> 1);
​        // 总是选择中间位置左右随机的数字作为根节点
​        int mid = ((left + right + rand() % 2) >> 1);

时间复杂度：O(n)

空间复杂度：O(logn)  不考虑返回值的空间，只考虑递归栈的使用

**方法：**

```c++
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return _sortedArrayToBST(nums, 0, nums.size() - 1);
    }

    TreeNode* _sortedArrayToBST(vector<int>& nums, int left, int right) 
    {
        if (left > right)
            return nullptr;
        // 总是选择中间位置左边的数字作为根节点
        // int mid = ((left + right) >> 1);
        // 总是选择中间位置右边的数字作为根节点
        // int mid = ((left + right + 1) >> 1);
        // 总是选择中间位置左右随机的数字作为根节点
        int mid = ((left + right + rand() % 2) >> 1);
        TreeNode* root = new TreeNode(nums[mid]);

        root->left = _sortedArrayToBST(nums, left, mid - 1);
        root->right = _sortedArrayToBST(nums, mid + 1, right);
        return root;
    }
};
```





## 0112. 路经总和

### 题目：

给你二叉树的根节点 `root` 和一个表示目标和的整数 `targetSum` ，判断该树中是否存在 **根节点到叶子节点** 的路径，这条路径上所有节点值相加等于目标和 `targetSum` 。

**叶子节点** 是指没有子节点的节点。

**示例 1：**

![leetcode_112_1](F:\C++\刷题\Img\leetcode_112_1.jpg)

```
输入：root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
输出：true
```

**示例 2：**

![leetcode_112_2](F:\C++\刷题\Img\leetcode_112_2.jpg)

```
输入：root = [1,2,3], targetSum = 5
输出：false
```

**示例 3：**

```
输入：root = [1,2], targetSum = 0
输出：false
```

**提示：**

- 树中节点的数目在范围 `[0, 5000]` 内
- `-1000 <= Node.val <= 1000`
- `-1000 <= targetSum <= 1000`

**解题思路：**

思路一：BFS

使用两个队列，一个记录广度遍历到当前节点的节点，另一个记录遍历到当前节点的路径和

时间复杂度：O(n)

空间复杂度：O(n)

思路二：递归

时间复杂度：O(n)

空间复杂度：O(height)



**方法一：**

```c++
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (root == nullptr)
            return false;
        
        queue<TreeNode*> dqNode;
        queue<int> dqVal;
        dqNode.push(root);
        dqVal.push(root->val);

        while (!dqNode.empty())
        {
            TreeNode* node = dqNode.front();
            dqNode.pop();
            int curSum = dqVal.front();
            dqVal.pop();
            if (node->left == nullptr && node->right == nullptr && curSum == targetSum)
                return true;
            
            if (node->left != nullptr)
                dqNode.push(node->left), dqVal.push(curSum + node->left->val);
            if (node->right != nullptr)
                dqNode.push(node->right), dqVal.push(curSum + node->right->val);
        }
        return false;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (root == nullptr)
            return false;
        
        if (root->left == nullptr && root->right == nullptr)
            return targetSum - root->val == 0;
        return hasPathSum(root->left, targetSum - root->val) || hasPathSum(root->right, targetSum - root->val);
    }
};
```





## 0113. 路径总和Ⅱ

### 题目：

给你二叉树的根节点 `root` 和一个整数目标和 `targetSum` ，找出所有 **从根节点到叶子节点** 路径总和等于给定目标和的路径。

**叶子节点** 是指没有子节点的节点。

**示例 1：**

![leetcode_113_2](F:\C++\刷题\Img\leetcode_113_2.jpg)

```
输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
输出：[[5,4,11,2],[5,8,4,5]]
```

**示例 2：**

![leetcode_113_2](F:\C++\刷题\Img\leetcode_113_2.jpg)

```
输入：root = [1,2,3], targetSum = 5
输出：[]
```

**示例 3：**

```
输入：root = [1,2], targetSum = 0
输出：[]
```

**提示：**

- 树中节点总数在范围 `[0, 5000]` 内
- `-1000 <= Node.val <= 1000`
- `-1000 <= targetSum <= 1000`



**解题思路：**

思路一：深度遍历

时间复杂度：O(n^2)

空间复杂度：O(n)

思路二：广度遍历

使用unordered_map<TreeNode*, TreeNode*> parent;记录路径

时间复杂度：O(n^2)

空间复杂度：O(n)

**方法一：**

```c++
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> ans;
        vector<int> path;
        _pathSum(root, targetSum, ans, path);
        return ans;
    }

    void _pathSum(TreeNode* node, int targetSum, vector<vector<int>>& ans, vector<int>& path) 
    {
        if (node == nullptr)
            return;

        path.push_back(node->val);
        targetSum -= node->val;
        if (targetSum == 0 && node->left == nullptr && node->right == nullptr)
            ans.push_back(path);

        _pathSum(node->left, targetSum, ans, path);
        _pathSum(node->right, targetSum, ans, path);
        path.pop_back();
    }
};
```

**方法二：**

```c++
class Solution {
private:
    vector<vector<int>> ans;
    unordered_map<TreeNode*, TreeNode*> parent;
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        if (root == nullptr)
            return ans;

        queue<TreeNode*> qu;
        queue<int> qu_sum;
        qu.push(root);
        qu_sum.push(0);

        while (!qu.empty())
        {
            TreeNode* node = qu.front();
            qu.pop();
            int rec = qu_sum.front() + node->val;
            qu_sum.pop();

            if (node->left == nullptr && node->right == nullptr)
            {
                if (rec == targetSum)
                    getPath(node);
            }
            else
            {
                if (node->left != nullptr)
                {
                    parent[node->left] = node;
                    qu.push(node->left);
                    qu_sum.push(rec);
                }
                if (node->right != nullptr)
                {
                    parent[node->right] = node;
                    qu.push(node->right);
                    qu_sum.push(rec);
                }
            }
        }
        return ans;
    }

    void getPath(TreeNode* node) 
    {
        vector<int> path;
        while (node != nullptr)
        {
            path.push_back(node->val);
            node = parent[node];
        }
        reverse(path.begin(), path.end());
        ans.push_back(path);
    }
};
```





## 0118. 杨辉三角

### 题目：

同动态规划模块118题





## 0119. 杨辉三角Ⅱ

### 题目：

同动态规划模块119题





## 0121. 买卖股票的最佳时机

### 题目：

同动态规划模块121题





## 0136. 只出现一次的数字

### 题目：

给定一个**非空**整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。

说明：

你的算法应该具有线性时间复杂度。 你可以不使用额外空间来实现吗？

**示例 1:**

```
输入: [2,2,1]
输出: 1
```

**示例 2:**

```
输入: [4,1,2,1,2]
输出: 4
```

**解题思路：**

所有数都异或在一起

时间复杂度：O(n)

空间复杂度：O(1）

**方法：**

```c++
class Solution {
public:
//异或方式
    int singleNumber(vector<int>& nums) {
        int tmp = 0;
        for (const auto& e : nums)
            tmp ^= e;
        return tmp;
    }
};
```





## 0141. 环形链表

### 题目：

给定一个链表，判断链表中是否有环。

如果链表中有某个节点，可以通过连续跟踪 `next` 指针再次到达，则链表中存在环。 为了表示给定链表中的环，我们使用整数 ~来表示链表尾连接到链表中的位置（索引从 `0` 开始）。 如果 `pos` 是 `-1`，则在该链表中没有环。**注意：pos 不作为参数进行传递**，仅仅是为了标识链表的实际情况。

如果链表中存在环，则返回 `true` 。 否则，返回 `false` 。

**进阶：**

你能用 `O(1)`（即，常量）内存解决此问题吗？

**示例 1：**

![leetcode_141_1](F:\C++\刷题\Img\leetcode_141_1.png)

```
输入：head = [3,2,0,-4], pos = 1
输出：true
解释：链表中有一个环，其尾部连接到第二个节点。
```

**示例 2：**

![leetcode_141_2](F:\C++\刷题\Img\leetcode_141_2.png)

```
输入：head = [1,2], pos = 0
输出：true
解释：链表中有一个环，其尾部连接到第一个节点。
```

**示例 3：**

![leetcode_141_3](F:\C++\刷题\Img\leetcode_141_3.png)

```
输入：head = [1], pos = -1
输出：false
解释：链表中没有环。
```

**提示：**

- 链表中节点的数目范围是 `[0, 10^4]`
- `-10^5 <= Node.val <= 10^5`
- `pos` 为 `-1` 或者链表中的一个 **有效索引** 。



**解题思路：**

思路一：前后指针法

快指针一次走两步，慢指针走一步，若有环，迟早会相遇

时间复杂度：O(N)

空间复杂度：O(1）

思路二：hash表法

时间复杂度：O(N)

空间复杂度：O(N）



**方法一：**

```c++
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (head == NULL || head->next == NULL)
            return false;
        ListNode *slow = head;
        ListNode *fast = head->next;

        while (slow != fast)
        {
            if (fast == NULL || fast->next == NULL)
                return false;
            slow = slow->next;
            fast = fast->next->next;
        }
        return true;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (head == NULL || head->next == NULL)
            return false;
        unordered_map<ListNode*, int> um;
        while (head != NULL)
        {
            if (um.count(head) > 0)
                return true;
            um.insert(make_pair(head, 1));
            head = head->next;
        }
        return false;
    }
};
```





## 0142. 环形链表Ⅱ

### 题目：

给定一个链表，返回链表开始入环的第一个节点。 如果链表无环，则返回 `null`。

为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 如果 pos 是 -1，则在该链表中没有环。**注意，pos 仅仅是用于标识环的情况，并不会作为参数传递到函数中。**

**说明**：不允许修改给定的链表。

**进阶**：

- 你是否可以使用 O(1) 空间解决此题？



**示例 1：**

![leetcode_142_1](F:\C++\刷题\Img\leetcode_142_1.png)

```
输入：head = [3,2,0,-4], pos = 1
输出：返回索引为 1 的链表节点
解释：链表中有一个环，其尾部连接到第二个节点。
```

**示例 2：**

![leetcode_142_2](F:\C++\刷题\Img\leetcode_142_2.png)

```
输入：head = [1,2], pos = 0
输出：返回索引为 0 的链表节点
解释：链表中有一个环，其尾部连接到第一个节点。
```

**示例 3：**

![leetcode_142_3](F:\C++\刷题\Img\leetcode_142_3.png)

```
输入：head = [1], pos = -1
输出：返回 null
解释：链表中没有环。
```

**提示：**

- 链表中节点的数目范围在范围 `[0, 10^4]` 内
- `-10^5 <= Node.val <= 10^5`
- pos 的值为 -1 或者链表中的一个有效索引



**解题思路：**

思路一：hash表

时间复杂度：O(N)

空间复杂度：O(N）

思路二：快慢指针

时间复杂度：O(N)

空间复杂度：O(1）

**方法一：**

```c++
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (head == NULL || head->next == NULL)
            return NULL;
        unordered_set<ListNode*> set;
        ListNode* p = head;
        while (p != NULL)
        {
            if (set.count(p) == 1)
                return p;
            else
                set.insert(p);
            p = p->next;
        }
        return NULL;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (head == NULL || head->next == NULL)
            return NULL;
        
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast != NULL)
        {
            slow = slow->next;
            if (fast->next == NULL)
                return NULL;
            fast = fast->next->next;
            if (fast == slow)
            {
                ListNode* ptr = head;
                while (ptr != slow)
                {
                    ptr = ptr->next;
                    slow = slow->next;
                }
                return ptr;
            }
        }
        return NULL;
    }
};
```





## 0143. 重排链表

### 题目：

给定一个单链表 `L` 的头节点 `head` ，单链表 `L` 表示为：

 `L0 → L1 → … → Ln-1 → Ln` 
请将其重新排列后变为：

`L0 → Ln → L1 → Ln-1 → L2 → Ln-2 → …`

不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

**示例 1:**

![leetcode_0143_1](F:\C++\刷题\Img\leetcode_0143_1.png)

```
输入: head = [1,2,3,4]
输出: [1,4,2,3]
```

**示例 2:**

![leetcode_0143_2](F:\C++\刷题\Img\leetcode_0143_2.png)

```
输入: head = [1,2,3,4,5]
输出: [1,5,2,4,3]
```

**提示：**

- 链表的长度范围为 `[1, 5 * 10^4]`
- `1 <= node.val <= 1000`



**解题思路：**

思路一：使用临时数组记录存储节点

时间复杂度：O(N)

空间复杂度：O(N）

思路二：先找中点，再反转后半段，再合并两个

时间复杂度：O(N)

空间复杂度：O(1）



**方法一：**

```c++
class Solution {
public:
    void reorderList(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return;
        vector<ListNode*> v;
        ListNode* node = head;
        while (node != nullptr)
        {
            v.push_back(node);
            node = node->next;
        }
        ListNode* dummy = new ListNode(0);
        ListNode* tmp = dummy;
        for (int i = 0; i < (v.size() + 1) / 2; ++i)
        {
            tmp->next = v[i];
            tmp = tmp->next;
            if (i == v.size() - i - 1)
                continue;
            tmp->next = v[v.size() - i - 1];
            tmp = tmp->next;
        }
        tmp->next = nullptr;
        head = dummy->next;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    void reorderList(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return;

        ListNode* mid = findMiddle(head);
        ListNode* l1 = head;
        ListNode* l2 = mid->next;
        mid->next = nullptr;
        l2 = reverseList(l2);
        mergeList(l1, l2);
    }

    ListNode* findMiddle(ListNode* node)
    {
        ListNode* slow = node;
        ListNode* fast = node;
        while (fast->next != nullptr && fast->next->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
    ListNode* reverseList(ListNode* node)
    {
        ListNode* prev = nullptr;
        ListNode* p = node;
        while (p != nullptr)
        {
            ListNode* tmp = p->next;
            p->next = prev;
            prev = p;
            p = tmp;
        }
        return prev;
    }
    void mergeList(ListNode* p1, ListNode* p2)
    {
        ListNode* l1;
        ListNode* l2;
        while (p1 != nullptr && p2 != nullptr)
        {
            l1 = p1->next;
            l2 = p2->next;

            p1->next = p2;
            p2->next = l1;

            p1 = l1;
            p2 = l2;
        }
    }
};
```



## 0144. 二叉树的前序遍历

### 题目：

给你二叉树的根节点 `root` ，返回它节点值的 **前序** 遍历。

**示例 1：**

![leetcode_144](F:\C++\刷题\Img\leetcode_144.jpg)

```
输入：root = [1,null,2,3]
输出：[1,2,3]
```

**示例 2：**

```
输入：root = []
输出：[]
```

**示例 3：**

```
输入：root = [1]
输出：[1]
```

**示例 4：**

![leetcode_144_1](F:\C++\刷题\Img\leetcode_144_1.jpg)

```
输入：root = [1,2]
输出：[1,2]
```

**示例 5：**

![leetcode_144_2](F:\C++\刷题\Img\leetcode_144_2.jpg)

```
输入：root = [1,null,2]
输出：[1,2]
```

**提示：**

- 树中节点数目在范围 `[0, 100]` 内
- `-100 <= Node.val <= 100`



**解题思路：**

思路一：递归

时间复杂度：O(n)

空间复杂度：O(n)

思路二：迭代

压栈，先压右分支

时间复杂度：O(n)

空间复杂度：O(n)

思路三：Morris遍历

[Morris遍历](https://leetcode-cn.com/problems/binary-tree-preorder-traversal/solution/leetcodesuan-fa-xiu-lian-dong-hua-yan-shi-xbian-2/)

时间复杂度：O(n)

空间复杂度：O(1)

**方法一：**

```c++
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        if (root == nullptr)
            return vector<int>();
        vector<int> res;
        _preorderTraversal(root, res);
        return res;
    }
    void _preorderTraversal(TreeNode* node, vector<int>& res)
    {
        if (node == nullptr)
            return;
        res.push_back(node->val);
        _preorderTraversal(node->left, res);
        _preorderTraversal(node->right, res);
    }
};
```

**方法二：**

```c++
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        if (root == nullptr)
            return vector<int>();
        vector<int> res;
        stack<TreeNode*> st;
        st.push(root);
        while (!st.empty())
        {
            TreeNode* node = st.top();
            res.push_back(node->val);
            st.pop();
            if (node->right != nullptr)
                st.push(node->right);
            if (node->left != nullptr)
                st.push(node->left);
        }
        return res;
    }
};
```

**方法三：**

```c++
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        if (root == nullptr)
            return vector<int>();
        vector<int> res;
        
        TreeNode* cur1 = root;
        TreeNode* cur2 = nullptr;
        while (cur1 != nullptr)
        {
            cur2 = cur1->left;
            if (cur2 != nullptr)
            {
                while (cur2->right != nullptr && cur2->right != cur1)
                    cur2 = cur2->right;
                if (cur2->right == nullptr)
                {
                    res.push_back(cur1->val);
                    cur2->right = cur1;
                    cur1 = cur1->left;
                    continue;
                }
                else
                    cur2->right = nullptr;
            }
            else
                res.push_back(cur1->val);
            cur1 = cur1->right;
        }
        return res;
    }
};
```





## 0145. 二叉树的后序遍历

### 题目：

给定一个二叉树，返回它的 **后序** 遍历。

**示例:**

```
输入: [1,null,2,3]  
   1
    \
     2
    /
   3 

输出: [3,2,1]
```

思路一：递归

时间复杂度：O(n)

空间复杂度：O(n)

思路二：迭代

压栈，先压所有的左，然后取出栈顶，若右为空 或 已访问过右，再访问当前，若没访问过右，再把当前压栈，继续访问右；

时间复杂度：O(n)

空间复杂度：O(n)



**方法一：**

```c++
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        if (root == nullptr)
            return vector<int>();
        vector<int> res;
        _postorderTraversal(root, res);
        return res;
    }
    void _postorderTraversal(TreeNode* node, vector<int>& res)
    {
        if (node == nullptr)
            return;
        _postorderTraversal(node->left, res);
        _postorderTraversal(node->right, res);
        res.push_back(node->val);
    }
};
```

**方法二：**

```c++
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        if (root == nullptr)
            return vector<int>();
        vector<int> res;
        
        stack<TreeNode*> st;
        TreeNode* prev = nullptr;
        while (root != nullptr || !st.empty())
        {
            while (root != nullptr)
            {
                st.push(root);
                root = root->left;
            }

            root = st.top();
            st.pop();

            if (root->right == nullptr || root->right == prev)
            {
                res.push_back(root->val);
                prev = root;
                root = nullptr;
            }
            else
            {
                // 还有右节点，暂时不能访问，再压回去
                st.push(root);
                root = root->right;
            }
        }
        return res;
    }
};
```





## 0155. 最小栈

### 题目：

设计一个支持 `push` ，`pop` ，`top` 操作，并能在常数时间内检索到最小元素的栈。

- `push(x)` —— 将元素 x 推入栈中。
- `pop()` —— 删除栈顶的元素。
- `top()` —— 获取栈顶元素。
- `getMin()` —— 检索栈中的最小元素。

**示例:**

```
输入：
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

输出：
[null,null,null,null,-3,null,0,-2]

解释：
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> 返回 -3.
minStack.pop();
minStack.top();      --> 返回 0.
minStack.getMin();   --> 返回 -2.
```


提示：

`pop`、`top` 和 `getMin` 操作总是在 **非空栈** 上调用。

**解题思路：**

使用一个栈存数据，再使用一个栈存当前最小值

时间复杂度：O(1)

空间复杂度：O(n)

**方法：**

```c++
class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {

    }
    
    void push(int val) {
        if (st.empty() || val <= min_st.top())
        {
            min_st.push(val);
        }
        st.push(val);
    }
    
    void pop() {
        if (st.top() == min_st.top())
        {
            min_st.pop();
        }
        st.pop();
    }
    
    int top() {
        return st.top();
    }
    
    int getMin() {
        return min_st.top();
    }
private:
    stack<int> st;
    stack<int> min_st;
};
```





## 0160. 相交链表

### 题目：

给你两个单链表的头节点 `headA` 和 `headB` ，请你找出并返回两个单链表相交的起始节点。如果两个链表没有交点，返回 `null` 。

图示两个链表在节点 `c1` 开始相交：

![leetcode_160_1](F:\C++\刷题\Img\leetcode_160_1.png)

题目数据 **保证** 整个链式结构中不存在环。

**注意**，函数返回结果后，链表必须 **保持其原始结构** 。

**示例 1：**

![leetcode_160_2](F:\C++\刷题\Img\leetcode_160_2.png)

```
输入：intersectVal = 8, listA = [4,1,8,4,5], listB = [5,0,1,8,4,5], skipA = 2, skipB = 3
输出：Intersected at '8'
解释：相交节点的值为 8 （注意，如果两个链表相交则不能为 0）。
从各自的表头开始算起，链表 A 为 [4,1,8,4,5]，链表 B 为 [5,0,1,8,4,5]。
在 A 中，相交节点前有 2 个节点；在 B 中，相交节点前有 3 个节点。
```

**示例 2：**

![leetcode_160_3](F:\C++\刷题\Img\leetcode_160_3.png)

```
输入：intersectVal = 2, listA = [0,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1
输出：Intersected at '2'
解释：相交节点的值为 2 （注意，如果两个链表相交则不能为 0）。
从各自的表头开始算起，链表 A 为 [0,9,1,2,4]，链表 B 为 [3,2,4]。
在 A 中，相交节点前有 3 个节点；在 B 中，相交节点前有 1 个节点。
```

**示例 3：**

![leetcode_160_4](F:\C++\刷题\Img\leetcode_160_4.png)

```
输入：intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
输出：null
解释：从各自的表头开始算起，链表 A 为 [2,6,4]，链表 B 为 [1,5]。
由于这两个链表不相交，所以 intersectVal 必须为 0，而 skipA 和 skipB 可以是任意值。
这两个链表不相交，因此返回 null 。
```

**提示：**

- `listA` 中节点数目为 `m`
- `listB` 中节点数目为 `n`
- `0 <= m, n <= 3 * 10^4`
- `1 <= Node.val <= 105`
- `0 <= skipA <= m`
- `0 <= skipB <= n`
- 如果 `listA` 和 `listB` 没有交点，`intersectVal` 为 `0`
- 如果 `listA` 和 `listB` 有交点，`intersectVal == listA[skipA + 1] == listB[skipB + 1]`

**进阶**：你能否设计一个时间复杂度 `O(n)` 、仅用 `O(1)` 内存的解决方案？

**解题思路：**

思路一：hash表

时间复杂度：O(m+n)

空间复杂度：O(m+n)

思路二：双指针

时间复杂度：O(max(m, n))

空间复杂度：O(1)

思路三：双指针2

思路类似于是否存在循环链表Ⅱ

时间复杂度：O(m+n)

空间复杂度：O(1)

**方法一：**

```c++
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (headA == NULL || headB == NULL)
            return NULL;
        unordered_set<ListNode*> set;
        ListNode* pA = headA;
        ListNode* pB = headB;
        while (pA != NULL || pB != NULL)
        {
            if (pA != NULL)
            {
                if (set.count(pA) == 0)
                {
                    set.insert(pA);
                    pA = pA->next;
                }
                else
                    return pA;
            }
            if (pB != NULL)
            {
                if (set.count(pB) == 0)
                {
                    set.insert(pB);
                    pB = pB->next;
                }
                else
                    return pB;
            }
        }
        return NULL;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (headA == NULL || headB == NULL)
            return NULL;
        
        ListNode* pA = headA;
        ListNode* pB = headB;
        int lenA = 0;
        int lenB = 0;
        while (pA != NULL)
        {
            ++lenA;
            pA = pA->next;
        }
        while (pB != NULL)
        {
            ++lenB;
            pB = pB->next;
        }
        if (lenA < lenB)
        {
            pA = headB;
            pB = headA;
        }

        for (int i = 0; i < abs(lenA - lenB); ++i)
            pA = pA->next;

        while (pA != NULL && pB != NULL)
        {
            if (pA == pB)
                return pA;
            pA = pA->next;
            pB = pB->next;
        }
        return NULL;
    }
};
```

**方法三：**

```c++
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (headA == NULL || headB == NULL)
            return NULL;
        
        ListNode* pA = headA;
        ListNode* pB = headB;
        while (pA != pB)
        {
            pA = pA == NULL ? headB : pA->next;
            pB = pB == NULL ? headA : pB->next;
        }
        return pA;
    }
};
```





## 0169. 多数元素

### 题目：

给定一个大小为 n 的数组，找到其中的多数元素。多数元素是指在数组中出现次数 **大于 ⌊ n/2 ⌋** 的元素。

你可以假设数组是非空的，并且给定的数组总是存在多数元素。

**示例 1：**

```
输入：[3,2,3]
输出：3
```

**示例 2：**

```
输入：[2,2,1,1,1,2,2]
输出：2
```

**进阶：**

- 尝试设计时间复杂度为 O(n)、空间复杂度为 O(1) 的算法解决此问题。

**解题思路：**

思路一：hash表

时间复杂度：O(n)

空间复杂度：O(n)

思路二：Boyer-Moore 投票算法

时间复杂度：O(n)

空间复杂度：O(1)

思路三：排序

时间复杂度：O(nlogn)

空间复杂度：O(logn)

思路四：分治法

时间复杂度：O(nlogn)

空间复杂度：O(logn)



**方法一：**

```c++
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> m;
        for (auto & e : nums)
        {
            if (m.count(e) == 0)
                m.insert(make_pair(e, 1));
            else
                ++m[e];
        }
        int max_value = INT_MIN;
        int max_count = INT_MIN;
        for (auto it = m.begin(); it != m.end(); ++it)
        {
            if (it->second > max_count)
            {
                max_count = it->second;
                max_value = it->first;
            }
        }
        return max_value;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int max_value = nums[0];
        int max_count = 1;
        for (int i = 1; i < nums.size(); ++i)
        {
            if (nums[i] == max_value)
                ++max_count;
            else
                --max_count;
            
            if (max_count < 0)
            {
                max_count = 1;
                max_value = nums[i];
            }
        }
        return max_value;
    }
};
```

**方法三：**

```c++
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return nums[nums.size() / 2];
    }
};
```

**方法四：**

```c++
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        return majority_element_rec(nums, 0, nums.size() - 1);
    }

    int majority_element_rec(vector<int>& nums, int lo, int hi) 
    {
        if (lo == hi)
            return nums[lo];
        int mid = ((lo + hi) >> 1);
        int left_majority = majority_element_rec(nums, lo, mid);
        int right_majority = majority_element_rec(nums, mid + 1, hi);
        if (count_in_range(nums, left_majority, lo, hi) > (hi - lo + 1) / 2)
            return left_majority;
        if (count_in_range(nums, right_majority, lo, hi) > (hi - lo + 1) / 2)
            return right_majority;
        return -1;
    }

    int count_in_range(vector<int>& nums, int target, int lo, int hi) 
    {
        int count = 0;
        for (int i = lo; i <= hi; ++i)
        {
            if (nums[i] == target)
                ++count;
        }
        return count;
    }
};
```





## 0173. 二叉搜索树迭代器

### 题目：

实现一个二叉搜索树迭代器类`BSTIterator` ，表示一个按中序遍历二叉搜索树（BST）的迭代器：

- `BSTIterator(TreeNode root)` 初始化 `BSTIterator` 类的一个对象。`BST` 的根节点 `root` 会作为构造函数的一部分给出。指针应初始化为一个不存在于 `BST` 中的数字，且该数字小于 `BST` 中的任何元素。

- `boolean hasNext()` 如果向指针右侧遍历存在数字，则返回 `true` ；否则返回 `false` 。
- `int next()`将指针向右移动，然后返回指针处的数字。

注意，指针初始化为一个不存在于 BST 中的数字，所以对 `next()` 的首次调用将返回 `BST` 中的最小元素。

你可以假设 `next()` 调用总是有效的，也就是说，当调用 `next()` 时，`BST` 的中序遍历中至少存在一个下一个数字。

**示例：**

![leetcode_173](F:\C++\刷题\Img\leetcode_173.png)

```
输入
["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"]
[[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]
输出
[null, 3, 7, true, 9, true, 15, true, 20, false]

解释
BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]);
bSTIterator.next();    // 返回 3
bSTIterator.next();    // 返回 7
bSTIterator.hasNext(); // 返回 True
bSTIterator.next();    // 返回 9
bSTIterator.hasNext(); // 返回 True
bSTIterator.next();    // 返回 15
bSTIterator.hasNext(); // 返回 True
bSTIterator.next();    // 返回 20
bSTIterator.hasNext(); // 返回 False
```

**提示：**

- 树中节点的数目在范围 `[1, 10^5]` 内
- `0 <= Node.val <= 10^6`
- 最多调用 `10^5` 次 `hasNext` 和 `next` 操作

**进阶：**

- 你可以设计一个满足下述条件的解决方案吗？`next()` 和 `hasNext()` 操作均摊时间复杂度为 `O(1)` ，并使用 `O(h)` 内存。其中 `h` 是树的高度。


**解题思路：**

思路一：使用一个数组，先存下来

时间复杂度：O(n)

空间复杂度：O(n)

思路二：使用栈迭代

时间复杂度：O(1)

空间复杂度：O(n)

**方法一：**

```c++
class BSTIterator {
private:
    void _inorder(vector<int>& arr, TreeNode* node)
    {
        if (node == nullptr)
            return;
        _inorder(arr, node->left);
        arr.push_back(node->val);
        _inorder(arr, node->right);
    }

    vector<int> inorder(TreeNode* node)
    {
        vector<int> arr_tmp;
        _inorder(arr_tmp, node);
        return arr_tmp;
    }

    vector<int> arr;
    int idx;
public:
    BSTIterator(TreeNode* root) : idx(0), arr(inorder(root))
    {}
    
    int next() {
        return arr[idx++];
    }
    
    bool hasNext() {
        return (idx < arr.size());
    }
};
```

**方法二：**

```c++
class BSTIterator {
private:
    stack<TreeNode*> stk;
    TreeNode* cur;
public:
    BSTIterator(TreeNode* root)
    {
        cur = root;
    }
    
    int next() {
        while (cur != nullptr)
        {
            stk.push(cur);
            cur = cur->left;
        }
        cur = stk.top();
        stk.pop();
        int res = cur->val;
        cur = cur->right;
        return res;
    }
    
    bool hasNext() {
        return cur != nullptr || !stk.empty();
    }
};
```





## 0187. 重复的DNA序列

### 题目：

所有 DNA 都由一系列缩写为 'A'，'C'，'G' 和 'T' 的核苷酸组成，例如："ACGAATTCCG"。在研究 DNA 时，识别 DNA 中的重复序列有时会对研究非常有帮助。

编写一个函数来找出所有目标子串，目标子串的长度为 10，且在 DNA 字符串 s 中出现次数超过一次。

**示例 1：**

```
输入：s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
输出：["AAAAACCCCC","CCCCCAAAAA"]
```

**示例 2：**

```
输入：s = "AAAAAAAAAAAAA"
输出：["AAAAAAAAAA"]
```

**提示：**

- `0 <= s.length <= 10^5`
- `s[i] 为 'A'、'C'、'G' 或 'T'`



**解题思路：**

思路一：滑动窗口 + hash表

unordered_map<string, int>

时间复杂度：O(nL)

空间复杂度：O(nL)

思路二：滑动窗口 + hash表 + 位运算

时间复杂度：O(n)

空间复杂度：O(n)

**方法一：**

```c++
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        const int L = 10;
        vector<string> ans;
        unordered_map<string, int> map;
        for (int i = 0; i < s.size() - L; ++i)
        {
            string subs = s.substr(i, L);
            if (++map[subs] == 2)
                ans.push_back(subs);
        }
        return ans;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        const int L = 10;
        if (s.length() <= L)
            return {};
        vector<string> ans;
        unordered_map<char, int> bin = {{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}};
        unordered_map<int, int> map;
        int x = 0;

        for (int i = 0; i < L - 1; ++i)
            x = (x << 2) | bin[s[i]];

        for (int i = 0; i <= s.size() - L; ++i)
        {
            x = ((x << 2) | bin[s[i + L - 1]]) & ((1 << 2 * L) - 1);
            if (++map[x] == 2)
                ans.push_back(s.substr(i, L));
        }
        return ans;
    }
};
```





## 0199. 二叉树的右视图

### 题目：

给定一个二叉树的 **根节点** `root`，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。

**示例 1:**

![leetcode_199](F:\C++\刷题\Img\leetcode_199.jpg)

```
输入: [1,2,3,null,5,null,4]
输出: [1,3,4]
```

**示例 2:**

```
输入: [1,null,3]
输出: [1,3]
```

**示例 3:**

```
输入: []
输出: []
```

**提示:**

- 二叉树的节点个数的范围是 `[0,100]`
- `-100 <= Node.val <= 100` 

**解题思路：**

层序遍历，从右向左只记录第一个

时间复杂度：O(n)

空间复杂度：O(n)

**方法：**

```c++
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;
        if (!root)
            return ans;
        queue<TreeNode*> qu;
        qu.push(root);
        while (!qu.empty())
        {
            int lens = qu.size();
            for (int i = 0; i < lens; ++i)
            {
                TreeNode* node = qu.front();
                qu.pop();
                if (i == 0)
                    ans.push_back(node->val);
                if (node->right != nullptr)
                    qu.push(node->right);
                if (node->left != nullptr)
                    qu.push(node->left);
            }
        }
        return ans;
    }
};
```





## 0203. 移除链表元素

### 题目：

给你一个链表的头节点 `head` 和一个整数 `val` ，请你删除链表中所有满足 `Node.val == val` 的节点，并返回 **新的头节点** 。

**示例 1：**

![leetcode_203](F:\C++\刷题\Img\leetcode_203.jpg)

```
输入：head = [1,2,6,3,4,5,6], val = 6
输出：[1,2,3,4,5]
```

**示例 2：**

```
输入：head = [], val = 1
输出：[]
```

**示例 3：**

```
输入：head = [7,7,7,7], val = 7
输出：[]
```

**提示：**

- 列表中的节点数目在范围 `[0, 10^4]` 内
- `1 <= Node.val <= 50`
- `0 <= val <= 50`



**解题思路：**

思路一：常规方法

注意：不能释放源节点

时间复杂度：O(n)

空间复杂度：O(1)

思路二：递归

时间复杂度：O(n)

空间复杂度：O(n)

**方法一：**

```c++
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        if (head == nullptr)
            return head;
        
        ListNode* dynHead = new ListNode(-1);
        dynHead->next = head;
        ListNode* p = head;
        ListNode* prev = dynHead;
        while (p != nullptr)
        {
            if (p->val == val)
            {
                prev->next = p->next;
                //free(p);
                p = prev->next;
            }
            else
            {
                prev = p;
                p = p->next;
            }
        }

        return dynHead->next;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        if (head == nullptr)
            return head;
        
        head->next = removeElements(head->next, val);
        return head->val == val ? head->next : head;
    }
};
```





## 0206. 反转链表

### 题目：

给你单链表的头节点 `head` ，请你反转链表，并返回反转后的链表。

**示例1：**

![leetcode_206_1](F:\C++\刷题\Img\leetcode_206_1.jpg)

```
输入：head = [1,2,3,4,5]
输出：[5,4,3,2,1]
```

**示例 2：**

![leetcode_206_2](F:\C++\刷题\Img\leetcode_206_2.jpg)

```
输入：head = [1,2]
输出：[2,1]
```

**示例 3：**

```
输入：head = []
输出：[]
```

**提示：**

链表中节点的数目范围是 `[0, 5000]`
`-5000 <= Node.val <= 5000`



**解题思路：**

思路一：迭代一

时间复杂度：O(n)

空间复杂度：O(1)

思路二：迭代二：

时间复杂度：O(n)

空间复杂度：O(1)

思路三：递归

时间复杂度：O(n)

空间复杂度：O(n)



**方法一：**

```c++
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;
        ListNode* res = new ListNode(-1);
        ListNode* p = head;
        ListNode* q = head->next;

        while (q != nullptr)
        {
            p->next = res->next;
            res->next = p;
            p = q;
            q = q->next;
        }
        p->next = res->next;
        res->next = p;

        return res->next;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;
            
        ListNode* prev = nullptr;
        ListNode* cur = head;

        while (cur != nullptr)
        {
            ListNode* curNext = cur->next;
            cur->next = prev;
            prev = cur;
            cur = curNext;
        }
        return prev;
    }
};
```

**方法三：**

```c++
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;
            
        ListNode* newHead = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return newHead;
    }
};
```





## 0217. 存在重复元素

### 题目：

给定一个整数数组，判断是否存在重复元素。

如果存在一值在数组中出现至少两次，函数返回 `true` 。如果数组中每个元素都不相同，则返回 `false` 。

**示例 1:**

```
输入: [1,2,3,1]
输出: true
```

**示例 2:**

```
输入: [1,2,3,4]
输出: false
```

**示例 3:**

```
输入: [1,1,1,3,3,4,3,2,4,2]
输出: true
```



**解题思路：**

思路一：暴力解法

时间复杂度：O(n^2)

空间复杂度：O(1)

思路二：排序

时间复杂度：O(nlogn)

空间复杂度：O(1)

思路三：hash表

时间复杂度：O(n)

空间复杂度：O(n)



**方法一：**

```c++
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        int n = nums.size();
        if (n < 2)
            return false;
        
        for (int i = 1; i < n; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (nums[i] == nums[j])
                    return true;
            }
        }
        return false;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        int n = nums.size();
        if (n < 2)
            return false;
        sort(nums.begin(), nums.end());
        for (int i = 1; i < n; ++i)
        {
            if (nums[i - 1] == nums[i])
                return true;
        }
        return false;
    }
};
```

**方法三：**

```c++
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        int n = nums.size();
        if (n < 2)
            return false;
        unordered_set<int> us;

        for (auto& x : nums)
        {
            if (us.find(x) != us.end())
                return true;
            us.insert(x);
        }
        return false;
    }
};
```





## 0226. 翻转二叉树

### 题目：

翻转一棵二叉树。

**示例：**

输入：

```
	 4
   /   \
  2     7
 / \   / \
1   3 6   9
```

输出：

```
	 4
   /   \
  7     2
 / \   / \
9   6 3   1
```

**解题思路：**

递归：

时间复杂度：O(n)

空间复杂度：O(n)

**方法：**

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr)
            return root;
        
        TreeNode* L = invertTree(root->left);
        TreeNode* R = invertTree(root->right);

        root->left = R;
        root->right = L;

        return root;
    }
};
```





## 0230. 二叉搜索树中第K小的元素

### 题目：

给定一个二叉搜索树的根节点 `root` ，和一个整数 `k` ，请你设计一个算法查找其中第 `k` 个最小元素（从 1 开始计数）。

**示例 1：**

![leetcode_230_1](F:\C++\刷题\Img\leetcode_230_1.jpg)

```
输入：root = [3,1,4,null,2], k = 1
输出：1
```

**示例 2：**

![leetcode_230_2](F:\C++\刷题\Img\leetcode_230_2.jpg)

```
输入：root = [5,3,6,2,4,null,null,1], k = 3
输出：3
```

**提示：**

- 树中的节点数为 `n` 。
- `1 <= k <= n <= 10^4`
- `0 <= Node.val <= 10^4`

**解题思路：**

思路一：中序遍历

时间复杂度：O(H + K)

空间复杂度：O(H)

思路二：map记录每个子树的节点数

时间复杂度：O(n)

空间复杂度：O(n)

**方法一：**

```c++
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> stk;
        while (root != nullptr || !stk.empty())
        {
            while (root != nullptr)
            {
                stk.push(root);
                root = root->left;
            }
            root = stk.top();
            stk.pop();
            if (--k == 0)
                break;
            root = root->right;
        }
        return root->val;
    }
};
```

**方法二：**

```c++
class MyBst {
private:
    TreeNode* root;
    unordered_map<TreeNode*, int> map;

public:
    MyBst (TreeNode* root)
    {
        this->root = root;
        countNum(this->root);
    }
    int countNum(TreeNode* node)
    {
        if (node == nullptr)
            return 0;
        map[node] = countNum(node->left) + countNum(node->right) + 1;
        return map[node];
    }
    int getNum(TreeNode* node)
    {
        if (node != nullptr && map.count(node))
            return map[node];
        else
            return 0;
    }
    int kthSmallestVal(int k)
    {
        TreeNode* node = root;
        while (node != nullptr)
        {
            int left = getNum(node->left);
            if (left == k - 1)
                break;
            else if (left > k - 1)
                node = node->left;
            else
            {
                node = node->right;
                k -= left + 1;
            }
        }
        return node->val;
    }
};

class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        MyBst bst(root);
        return bst.kthSmallestVal(k);
    }
};
```





## 0232. 用栈实现队列

### 题目：

请你仅使用两个栈实现先入先出队列。队列应当支持一般队列支持的所有操作（`push`、`pop`、`peek`、`empty`）：

实现 `MyQueue` 类：

- `void push(int x)` 将元素 x 推到队列的末尾

- `int pop()` 从队列的开头移除并返回元素

- `int peek()` 返回队列开头的元素

- `boolean empty()` 如果队列为空，返回 `true` ；否则，返回 `false`

  

**说明：**

你只能使用标准的栈操作 —— 也就是只有 `push to top, peek/pop from top, size`, 和 `is empty` 操作是合法的。
你所使用的语言也许不支持栈。你可以使用 `list` 或者 `deque`（双端队列）来模拟一个栈，只要是标准的栈操作即可。

**进阶：**

- 你能否实现每个操作均摊时间复杂度为 `O(1)` 的队列？换句话说，执行 `n` 个操作的总时间复杂度为 `O(n)` ，即使其中一个操作可能花费较长时间。


**示例：**

```
输入：
["MyQueue", "push", "push", "peek", "pop", "empty"]
[[], [1], [2], [], [], []]
输出：
[null, null, null, 1, 1, false]

解释：
MyQueue myQueue = new MyQueue();
myQueue.push(1); // queue is: [1]
myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
myQueue.peek(); // return 1
myQueue.pop(); // return 1, queue is [2]
myQueue.empty(); // return false
```

**提示：**

- `1 <= x <= 9`
- 最多调用 `100` 次 `push`、`pop`、`peek` 和 `empty`
- 假设所有操作都是有效的 （例如，一个空的队列不会调用 `pop` 或者 `peek` 操作）



**解题思路：**

两个栈，一个倒进一个

**方法：**

```c++
class MyQueue {
private:
    stack<int> st1;
    stack<int> st2;
public:
    MyQueue() {
        st1 = stack<int>();
        st2 = stack<int>();
    }
    
    void push(int x) {
        st1.push(x);
    }
    
    int pop() {
        int tmp = -1;
        if (st2.empty())
        {
            while (!st1.empty())
            {
                tmp = st1.top();
                st1.pop();
                st2.push(tmp);
            }
        }

        tmp = st2.top();
        st2.pop();
        return tmp;
    }
    
    int peek() {
        if (st2.empty())
        {
            int tmp = -1;
            while (!st1.empty())
            {
                tmp = st1.top();
                st1.pop();
                st2.push(tmp);
            }
        }
        return st2.top();
    }
    
    bool empty() {
        return st2.empty() && st1.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
```





## 0235. 二叉搜索树的最近公共祖先

### 题目：

给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。

**百度百科**中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（**一个节点也可以是它自己的祖先**）。”

例如，给定如下二叉搜索树:  root = [6,2,8,0,4,7,9,null,null,3,5]

![leetcode_235](F:\C++\刷题\Img\leetcode_235.png)

**示例 1:**

```
输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
输出: 6 
解释: 节点 2 和节点 8 的最近公共祖先是 6。
```

**示例 2:**

```
输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
输出: 2
解释: 节点 2 和节点 4 的最近公共祖先是 2, 因为根据定义最近公共祖先节点可以为节点本身。
```

**说明:**

- 所有节点的值都是唯一的。
- `p、q` 为不同节点且均存在于给定的二叉搜索树中。

**解题思路：**

思路一：两次遍历

获得两个结点的路径，从头至尾找到第一个不相同的节点的前一个

时间复杂度：O(n)

空间复杂度：O(n)

思路二：一次遍历

从根节点出发，若两个节点都在左分支，往左走，若都在右分支，往右走，其他的，返回当前节点

时间复杂度：O(n)

空间复杂度：O(1)

**方法一：**

```c++
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<TreeNode*> path_p = getPath(root, p);
        vector<TreeNode*> path_q = getPath(root, q);

        int i = 0;
        for (; i < path_p.size() && i < path_q.size(); ++i)
        {
            if (path_p[i] != path_q[i])
                break;
        }
        return path_p[i - 1];
    }

    vector<TreeNode*> getPath(TreeNode* root, TreeNode* p)
    {
        vector<TreeNode*> path;
        while (root->val != p->val)
        {
            path.push_back(root);
            if (root->val > p->val)
                root = root->left;
            else
                root = root->right;
        }
        path.push_back(root);
        return path;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* ancestor = root;
        while (ancestor != NULL)
        {
            if (ancestor->val > p->val && ancestor->val > q->val)
                ancestor = ancestor->left;
            else if (ancestor->val < p->val && ancestor->val < q->val)
                ancestor = ancestor->right;
            else
                break;
        }
        return ancestor;
    }
};
```





## 0238. 除自身以外数组的乘积

### 题目：

给你一个长度为 `n` 的整数数组 `nums`，其中 `n > 1`，返回输出数组 `output` ，其中 `output[i]` 等于 `nums` 中除 `nums[i]` 之外其余各元素的乘积。

**示例:**

```
输入: [1,2,3,4]
输出: [24,12,8,6]
```


**提示**：题目数据保证数组之中任意元素的全部前缀元素和后缀（甚至是整个数组）的乘积都在 32 位整数范围内。

说明: 请不要使用除法，且在 O(n) 时间复杂度内完成此题。

**解题思路：**

[左右前后缀之积](https://leetcode-cn.com/problems/product-of-array-except-self/solution/chu-zi-shen-yi-wai-shu-zu-de-cheng-ji-by-leetcode-/)

时间复杂度：O(n)

空间复杂度：O(1)

```c++
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, 1);
        int left = 1, right = 1;
        for (int i = 1; i < n; ++i)
        {
            left *= nums[i - 1];
            ans[i] *= left;
            right *= nums[n - i];
            ans[n - i - 1] *= right;
        }
        return ans;
    }
};
```





## 0240. 搜索二维矩阵Ⅱ

### 题目：

编写一个高效的算法来搜索 `m x n` 矩阵 `matrix` 中的一个目标值 `target` 。该矩阵具有以下特性：

- 每行的元素从左到右升序排列。
- 每列的元素从上到下升序排列。

**示例 1：**

![leetcode_240](F:\C++\刷题\Img\leetcode_240.jpg)

```
输入：matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
输出：true
```

**示例 2：**

![leetcode_240_1](F:\C++\刷题\Img\leetcode_240_1.jpg)

```
输入：matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
输出：false
```

**提示：**

- `m == matrix.length`
- `n == matrix[i].length`
- `1 <= n, m <= 300`
- `-10^9 <= matrix[i][j] <= 10^9`
- 每行的所有元素从左到右升序排列
- 每列的所有元素从上到下升序排列
- `-10^9 <= target <= 10^9`



**解题思路：**

思路一：暴力解法

时间复杂度：O(mn)

空间复杂度：O(1)

思路二：二分查找法

时间复杂度：O(mlogn)

空间复杂度：O(1)

思路三：Z字形查找法

越界就表示未查到

时间复杂度：O(n + m)

空间复杂度：O(1)

**方法一：**

```c++
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (matrix[i][j] == target)
                    return true;
            }
        }
        return false;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();

        for (int i = 0; i < m; ++i)
        {
            if (binFind(matrix[i], target))
                return true;
        }
        return false;
    }

    bool binFind(vector<int>& v, int target)
    {
        return _binFind(v, target, 0, v.size() - 1);
    }

    bool _binFind(vector<int>& v, int target, int left, int right)
    {
        if (left > right)
            return false;
        int mid = ((left + right) >> 1);
        if (v[mid] == target)
            return true;
        else if (v[mid] > target)
            return _binFind(v, target, left, mid - 1);
        else
            return _binFind(v, target, mid + 1, right);
    }
};
```

**方法三：**

```c++
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();

        int i = 0, j = n - 1;
        while (i < m && j >= 0)
        {
            if (matrix[i][j] == target)
                return true;
            else if (matrix[i][j] > target)
                --j;
            else
                ++i;
        }
        return false;
    }
};
```





## 0242. 有效的字母异位词

### 题目：

给定两个字符串 `s` 和 `t` ，编写一个函数来判断 `t` 是否是 `s` 的字母异位词。

**注意**：若 `s` 和 t 中每个字符出现的次数都相同，则称 `s` 和 `t` 互为字母异位词。

 

**示例 1:**

```
输入: s = "anagram", t = "nagaram"
输出: true
```

**示例 2:**

```
输入: s = "rat", t = "car"
输出: false
```

**提示:**

`1 <= s.length, t.length <= 5 * 10^4`
`s` 和 `t` 仅包含小写字母



**解题思路：**

思路一：排序

时间复杂度：O(nlogn)

空间复杂度：O(logn)  排序所需的额外空间

思路二：hash表法

时间复杂度：O(n)

空间复杂度：O(S)  S = 26

**方法一：**

```c++
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length())
            return false;
        
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s == t;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length())
            return false;
        
        unordered_map<char, int> um;
        for (auto& x : s)
        {
            if (um.count(x) > 0)
                ++um[x];
            else
                um.insert(make_pair(x, 1));
        }
        for (auto& x : t)
        {
            if (um.count(x) < 1)
                return false;
            if (--um[x] < 0)
                return false;
        }

        return true;
    }
};
```





## 0290. 单词规律

### 题目：

给定一种规律 pattern 和一个字符串 str ，判断 str 是否遵循相同的规律。

这里的 遵循 指完全匹配，例如， pattern 里的每个字母和字符串 str 中的每个非空单词之间存在着双向连接的对应规律。

示例1:

输入: pattern = "abba", str = "dog cat cat dog"
输出: true
示例 2:

输入:pattern = "abba", str = "dog cat cat fish"
输出: false
示例 3:

输入: pattern = "aaaa", str = "dog cat cat dog"
输出: false
示例 4:

输入: pattern = "abba", str = "dog dog dog dog"
输出: false
说明:
你可以假设 pattern 只包含小写字母， str 包含了由单个空格分隔的小写字母。    

**解题思路：**

使用两个hash表，一个存<string, char>，一个存<char, string>

如果之前出现过这个字符串，检查是否等于当前对应字符

如果之前出现过这个字符，检查是否等于当前对应字符串

时间复杂度：O(n + m)

空间复杂度：O(n + m)

**方法：**

```c++
class Solution {
public:
    bool wordPattern(string pattern, string s) {
        unordered_map<string, char> str2ch;
        unordered_map<char, string> ch2str;
        int m = s.length();
        int i = 0;
        for (auto& ch : pattern)
        {
            // 单词数不够字符数
            if (i >= m)
                return false;
            int j = i;
            while (j < m && s[j] != ' ')
                ++j;
            string str = s.substr(i, j - i);
            // 如果之前出现过这个字符串，检查是否等于当前对应字符
            if (str2ch.count(str) && str2ch[str] != ch)
                return false;
            // 如果之前出现过这个字符，检查是否等于当前对应字符串
            if (ch2str.count(ch) && ch2str[ch] != str)
                return false;
            str2ch[str] = ch;
            ch2str[ch] = str;
            i = j + 1;
        }
        return i >= m;  // 最后一个空格符，就会 = ，最后一个非空格符，就会 > 
    }
};
```





## 0334. 递增的三元子序列

### 题目：

给你一个整数数组 `nums` ，判断这个数组中是否存在长度为 `3` 的递增子序列。

如果存在这样的三元组下标 `(i, j, k)` 且满足 `i < j < k` ，使得 `nums[i] < nums[j] < nums[k]` ，返回 `true` ；否则，返回 `false` 。

 

**示例 1：**

```
输入：nums = [1,2,3,4,5]
输出：true
解释：任何 i < j < k 的三元组都满足题意
```

**示例 2：**

```
输入：nums = [5,4,3,2,1]
输出：false
解释：不存在满足题意的三元组
```

**示例 3：**

```
输入：nums = [2,1,5,0,4,6]
输出：true
解释：三元组 (3, 4, 5) 满足题意，因为 nums[3] == 0 < nums[4] == 4 < nums[5] == 6
```

**提示：**

- `1 <= nums.length <= 10^5`
- `-2^31 <= nums[i] <= 2^31 - 1`

**解题思路：**

思路一：双指针

首先，新建两个变量 `small` 和 `mid` ，分别用来保存题目要我们求的长度为 3 的递增子序列的**最小值**和**中间值**。

接着，我们遍历数组，每遇到一个数字，我们将它和 `small` 和 `mid` 相比：

- 若小于等于 `small` ，则替换 `small`；

- 若小于等于 `mid`，则替换 `mid`；

- 若大于 `mid`，则说明我们找到了长度为 3 的递增数组！

上面的求解过程中有个问题：当已经找到了长度为 2 的递增序列，这时又来了一个比 `small` 还小的数字，为什么可以直接替换 `small` 呢，这样 `small` 和 `mid` 在原数组中并不是按照索引递增的关系呀？

Trick 就在这里了！假如当前的 `small` 和 `mid` 为 [3, 5]，这时又来了个 1。假如我们不将 `small` 替换为 1，那么，当下一个数字是 2，后面再接上一个 3 的时候，我们就没有办法发现这个 [1,2,3] 的递增数组了！也就是说，我们替换最小值，是为了后续能够更好地更新中间值！

另外，即使我们更新了 `small` ，这个 `small` 在 `mid` 后面，没有严格遵守递增顺序，但它隐含着的真相是，`有一个比 small 大比 mid 小的前·最小值出现在 mid 之前`。因此，当后续出现比 mid 大的值的时候，我们一样可以通过当前 `small` 和 `mid` 推断的确存在着长度为 3 的递增序列。 所以，这样的替换并不会干扰我们后续的计算！

时间复杂度：O(n)

空间复杂度：O(1)

思路二：双指针 + 可以返回是哪三个

时间复杂度：O(n)

空间复杂度：O(1)

思路三：动态规划（超时）

时间复杂度：O(n^2)

空间复杂度：O(n)

**方法一：**

```c++
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int n = nums.size();
        if (n < 3)
            return false;
        int small = INT_MAX, mid = INT_MAX;
        for (auto& e : nums)
        {
            if (e <= small)
                small = e;
            else if (e <= mid)
                mid = e;
            else
                return true;
        }
        return false;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int n = nums.size();
        if (n < 3)
            return false;
        int small = nums[0], mid = nums[0];
        int length = 1;
        for (int i = 1; i < n; ++i)
        {
            if (mid < nums[i])
            {
                // small、mid、*
                if (++length == 3)
                    return true;
                mid = nums[i];
            }
            else if (small < nums[i])
                // small、*、mid
                mid = nums[i];
            else if (i + 1 < n && nums[i] < nums[i + 1] && nums[i + 1] <= mid)
            {
                // 前提是 *、small、mid
                // 条件 *、* + 1 整体小于 small、mid
                small = mid = nums[i];
                length = 1;
            }
        }
        return false;
    }
};
```

**方法三：**

```c++
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int n = nums.size();
        if (n < 3)
            return false;
        vector<int> dp(n, 1);
        for (int i = 1; i < n; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (nums[j] < nums[i])
                {
                    dp[i] = max(dp[i], dp[j] + 1);
                    if (dp[i] >= 3)
                        return true;
                }                    
            }
        }
        return false;
    }
};
```





## 0350. 两个数组的交集Ⅱ

### 题目：

给定两个数组，编写一个函数来计算它们的交集。

**示例 1：**

```
输入：nums1 = [1,2,2,1], nums2 = [2,2]
输出：[2,2]
```

**示例 2:**

```
输入：nums1 = [4,9,5], nums2 = [9,4,9,8,4]
输出：[4,9]
```

**说明：**

- 输出结果中每个元素出现的次数，应与元素在两个数组中出现次数的最小值一致。
- 我们可以不考虑输出结果的顺序。



**解题思路：**

思路一：hash表法

将短的数组存在hash表中，并计数

![leetcode_350_1](F:\C++\刷题\Img\leetcode_350_1.gif)

时间复杂度：O(m+n)

空间复杂度：O(min(m,n))

思路二：排序 + 双指针

如果两个数组是有序的，则可以使用双指针的方法得到两个数组的交集。

首先对两个数组进行排序，然后使用两个指针遍历两个数组。

初始时，两个指针分别指向两个数组的头部。每次比较两个指针指向的两个数组中的数字，如果两个数字不相等，则将指向较小数字的指针右移一位，如果两个数字相等，将该数字添加到答案，并将两个指针都右移一位。当至少有一个指针超出数组范围时，遍历结束。



时间复杂度：$O(m \log m+n \log n)$

空间复杂度：$O(\min(m,n))$



**方法一：**

```c++
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
```

**方法二：**

```c++
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
```





## 0383. 赎金信

### 题目：

给定一个赎金信 (`ransom`) 字符串和一个杂志(`magazine`)字符串，判断第一个字符串 `ransom` 能不能由第二个字符串 `magazines` 里面的字符构成。如果可以构成，返回 `true` ；否则返回 `false`。

(题目说明：为了不暴露赎金信字迹，要从杂志上搜索各个需要的字母，组成单词来表达意思。杂志字符串中的每个字符只能在赎金信字符串中使用一次。)

**示例 1：**

```
输入：ransomNote = "a", magazine = "b"
输出：false
```

**示例 2：**

```
输入：ransomNote = "aa", magazine = "ab"
输出：false
```

**示例 3：**

```
输入：ransomNote = "aa", magazine = "aab"
输出：true
```

**提示：**

- 你可以假设两个字符串均只含有小写字母。




**解题思路：**

思路一：hash表法

时间复杂度：O(max(m, n))

空间复杂度：O(m)

思路二：直接在原字符串上find + 做标记

时间复杂度：O(m)

空间复杂度：O(1)



**方法一：**

```c++
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        int m = ransomNote.length();
        int n = magazine.length();

        if (m > n)
            return false;
        
        unordered_map<char, int> um;
        for (auto& x : magazine)
        {
            if (um.count(x) > 0)
                ++um[x];
            else
                um.insert(make_pair(x, 1));
        }

        for (auto& x : ransomNote)
        {
            if (um.count(x) == 0)
                return false;
            if (--um[x] < 0)
                return false;
        }
        return true;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        int m = ransomNote.length();
        int n = magazine.length();
        
        for (auto& x : ransomNote)
        {
            int idx = magazine.find(x);
            if (idx != -1)
                magazine[idx] = '0';
            else
                return false;
        }
        return true;
    }
};
```





## 0387. 字符串中的第一个唯一字符

### 题目：

给定一个字符串，找到它的第一个不重复的字符，并返回它的索引。如果不存在，则返回 `-1`。

 

**示例：**

```
s = "leetcode"
返回 0

s = "loveleetcode"
返回 2
```

**解题思路：**

思路一：空间换时间

使用一个数组，来存储字符对应ascii码的存储次数，再遍历一遍数组

时间复杂度：O(n)

空间复杂度：O(1)  ：字符种类是确定的前提下

思路二：正反双指针find



**方法一：**

```c++
class Solution {
public:
    int firstUniqChar(string s) {
        int Count[256] = {0};
        for (int i = 0; i < s.size(); ++i)
        {
            ++Count[s[i]];
        }
        for (int i = 0; i < s.size(); ++i)
        {
            if (Count[s[i]] == 1)
                return i;
        }
        return -1;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    int firstUniqChar(string s) {
        for (int i = 0; i < s.size(); ++i)
        {
            if (s.find(s[i]) == s.rfind(s[i]))
                return i;
        }
        return -1;
    }
};
```





## 0409. 最长回文串

### 题目：

给定一个包含大写字母和小写字母的字符串，找到通过这些字母构造成的最长的回文串。

在构造过程中，请注意区分大小写。比如 "Aa" 不能当做一个回文字符串。

**注意:**
假设字符串的长度不会超过 1010。

**示例 1:**

```
输入:
"abccccdd"

输出:
7

解释:
我们可以构造的最长的回文串是"dccaccd", 它的长度是 7。
```

**解题思路：**

累加所有偶数数量，再加上奇数 - 1 的数量，若存在奇数，再加 1；

时间复杂度：O(n)

空间复杂度：O(n) 

**方法：**

```c++
class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char, int> map;
        for (auto& e : s)
            ++map[e];
        int exist_odd = false;
        int res = 0;
        for (auto& e : map)
        {
            if (e.second % 2 == 0)
                res += e.second;
            else 
            {
                res += e.second / 2 * 2;
                exist_odd = true;
            }
        }
        res += exist_odd ? 1 : 0;
        return res;
    }
};
```





## 0415. 字符串相加

### 题目：

给定两个字符串形式的非负整数 `num1` 和`num2` ，计算它们的和并同样以字符串形式返回。

你不能使用任何內建的用于处理大整数的库（比如 `BigInteger`）， 也不能直接将输入的字符串转换为整数形式。

**示例 1：**

```
输入：num1 = "11", num2 = "123"
输出："134"
```

**示例 2：**

```
输入：num1 = "456", num2 = "77"
输出："533"
```

**示例 3：**

```
输入：num1 = "0", num2 = "0"
输出："0"
```

**提示：**

- `1 <= num1.length, num2.length <= 10^4`
- `num1` 和`num2` 都只包含数字 `0-9`
- `num1` 和`num2` 都不包含任何前导零

**解题思路：**

将两个字符串反转，就不用考虑进位错位问题

时间复杂度：O(max(m, n))

空间复杂度：O(1)  

**方法：**

```c++
class Solution {
public:
    int AddItem(int a, int b, int& sign)
    {
        int sum = a + b + sign;
        if (sum > 9)
        {
            sum -= 10;
            sign = 1;
        }
        else
            sign = 0;
        return sum;
    }
    //进位问题，所以反转之后就好解决了
    string addStrings(string num1, string num2) {
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        int i, j, sign, sum;
        i = j = 0;
        sign = 0;
        sum = 0;
        string result;
        while (i < num1.size() && j < num2.size())
        {
            sum = AddItem(num1[i] - '0', num2[j] - '0', sign);
            result += (sum + '0');
            ++i;
            ++j;
        }
        while (i < num1.size())
        {
            sum = AddItem(num1[i] - '0', 0, sign);
            result += (sum + '0');
            ++i;
        }
        while (j < num2.size())
        {
            sum = AddItem(0, num2[j] - '0', sign);
            result += (sum + '0');
            ++j;
        }
        if (sign == 1)
            result += (sign + '0');
        reverse(result.begin(), result.end());
        return result;
    }
};
```





## 0435. 无重叠区间

### 题目：

给定一个区间的集合，找到需要移除区间的最小数量，使剩余区间互不重叠。

**注意:**

1. 可以认为区间的终点总是大于它的起点。
2. 区间 [1,2] 和 [2,3] 的边界相互“接触”，但没有相互重叠。

**示例 1:**

```
输入: [ [1,2], [2,3], [3,4], [1,3] ]

输出: 1

解释: 移除 [1,3] 后，剩下的区间没有重叠。
```

**示例 2:**

```
输入: [ [1,2], [1,2], [1,2] ]

输出: 2

解释: 你需要移除两个 [1,2] 来使剩下的区间没有重叠。
```

**示例 3:**

```
输入: [ [1,2], [2,3] ]

输出: 0

解释: 你不需要移除任何区间，因为它们已经是无重叠的了。
```

**解题思路：**

思路一：

[动态规划](https://leetcode-cn.com/problems/non-overlapping-intervals/solution/wu-zhong-die-qu-jian-by-leetcode-solutio-cpsb/)

时间复杂度：O(n^2)

空间复杂度：O(n)

思路二：

[贪心算法](https://leetcode-cn.com/problems/non-overlapping-intervals/solution/wu-zhong-die-qu-jian-by-leetcode-solutio-cpsb/)

时间复杂度：O(nlogn)  排序的

空间复杂度：O(logn)  排序的

**方法一：**

```c++
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty())
            return 0;
        sort(intervals.begin(), intervals.end(), [](const auto& u, const auto& v){
            return u[0] < v[0];
        });

        int n = intervals.size();
        vector<int> bp(n, 1);
        for (int i = 1; i < n; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (intervals[j][1] <= intervals[i][0])
                {
                    bp[i] = max(bp[i], bp[j] + 1);
                }
            }
        }
        return n - *max_element(bp.begin(), bp.end());
    }
};
```

**方法二：**

```c++
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty())
            return 0;
        sort(intervals.begin(), intervals.end(), [](const auto& u, const auto& v){
            return u[1] < v[1];
        });

        int n = intervals.size();
        int end = INT_MIN;
        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            if (intervals[i][0] >= end)
            {
                end = intervals[i][1];
                ++ans;
            }
        }
        return n - ans;
    }
};
```





## 0450. 删除二叉搜索树中的节点

### 题目：

给定一个二叉搜索树的根节点 `root` 和一个值 `key`，删除二叉搜索树中的 `key` 对应的节点，并保证二叉搜索树的性质不变。返回二叉搜索树（有可能被更新）的根节点的引用。

一般来说，删除节点可分为两个步骤：

- 首先找到需要删除的节点；
- 如果找到了，删除它。

**示例 1:**

![leetcode_450_1](F:\C++\刷题\Img\leetcode_450_1.jpg)

```
输入：root = [5,3,6,2,4,null,7], key = 3
输出：[5,4,6,2,null,null,7]
解释：给定需要删除的节点值是 3，所以我们首先找到 3 这个节点，然后删除它。
一个正确的答案是 [5,4,6,2,null,null,7], 如下图所示。
另一个正确答案是 [5,2,6,null,4,null,7]。
```

![leetcode_450_2](F:\C++\刷题\Img\leetcode_450_2.jpg)

**示例 2:**

```
输入: root = [5,3,6,2,4,null,7], key = 0
输出: [5,3,6,2,4,null,7]
解释: 二叉树不包含值为 0 的节点
```

**示例 3:**

```
输入: root = [], key = 0
输出: []
```

**提示:**

- 节点数的范围 `[0, 10^4]`.
- `-10^5 <= Node.val <= 10^5`
- 节点值唯一
- `root` 是合法的二叉搜索树
- `-10^5 <= key <= 10^5`



**解题思路：**

思路一：找到要删的节点，若为叶子节点，直接删，否则找到左或者右节点的next点，并复制当前节点，然后递归删除那个next节点；

时间复杂度：O(logN)  

空间复杂度：O(H)  

思路二：找到要删的节点，若为叶子节点，直接删，若左子树为空，返回右子树，若右为空，返回左，若都不为空，随便找一个next节点，并调整结点指向；

![leetcode_450_3](F:\C++\刷题\Img\leetcode_450_3.jpg)

时间复杂度：O(H)  

空间复杂度：O(H)  

**方法一：**

```c++
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr)
            return nullptr;
        if (root->val > key)
            root->left = deleteNode(root->left, key);
        else if (root->val < key)
            root->right = deleteNode(root->right, key);
        else
        {
            if (root->left == nullptr && root->right == nullptr)
                root = nullptr;
            else
            {
                // 这两个条件只能满足一个
                if (root->left != nullptr)
                {
                    root->val = getLeftNextVal(root);
                    root->left = deleteNode(root->left, root->val);
                }
                else if (root->right != nullptr)
                {
                    root->val = getRightNextVal(root);
                    root->right = deleteNode(root->right, root->val);
                }
            }
        }
        return root;
    }

    int getRightNextVal(TreeNode* node)  // successor
    {
        node = node->right;
        while (node->left != nullptr) 
            node = node->left;
        return node->val;
    }

    int getLeftNextVal(TreeNode* node)  // predecessor
    {
        node = node->left;
        while (node->right != nullptr) 
            node = node->right;
        return node->val;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr)
            return nullptr;
        if (root->val > key)
            root->left = deleteNode(root->left, key);
        else if (root->val < key)
            root->right = deleteNode(root->right, key);
        else
        {
            if (!root->left)
                return root->right;
            if (!root->right)
                return root->left;
            TreeNode* node = root->right;
            while (node->left != nullptr)
                node = node->left;
            node->left = root->left;
            root = root->right;
        }
        return root;
    }
};
```





## 0560. 和为K的子数组

### 题目：

给你一个整数数组 `nums` 和一个整数 `k` ，请你统计并返回该数组中和为 `k` 的连续子数组的个数。

**示例 1：**

```
输入：nums = [1,1,1], k = 2
输出：2
```

**示例 2：**

```
输入：nums = [1,2,3], k = 3
输出：2
```

**提示：**

- `1 <= nums.length <= 2 * 10^4`
- `-1000 <= nums[i] <= 1000`
- `-10^7 <= k <= 10^7`



**解题思路：**

思路一：暴力解法

找到所有的连续子序列的和

时间复杂度：O(n^2)

空间复杂度：O(1)

思路二：前缀和

求一个前缀和数组，判断任意两个位置的前缀和是否相差为k

时间复杂度：O(n^2)

空间复杂度：O(n)

思路三：hash表 优化 前缀和

时间复杂度：O(n)

空间复杂度：O(n)

**方法一：**

```c++
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        int count = 0;
        for (int i = 0; i < n; ++i)
        {
            int sum = 0;
            for (int j = i; j < n; ++j)
            {
                sum += nums[j];
                if (sum == k)
                    ++count;
            }
        }
        return count;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 1)
            return (k == nums[0] ? 1 : 0);
        vector<int> preSum(nums);
        int count = 0;
        // 计算前缀和
        for (int i = 1; i < n; ++i)
            preSum[i] += preSum[i - 1];

        for (int i = 0; i < n; ++i)
        {
            if (preSum[i] == k)
                ++count;
            for (int j = 0; j < i; ++j)
            {
                if (preSum[i] - preSum[j] == k)
                    ++count;
            }
        }
        return count;
    }
};
```

**方法三：**

```c++
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> map;
        map[0] = 1;
        int count = 0, preSum = 0;
        for (auto& e : nums)
        {
            // 边计算前缀和，边查找是否包含preSum - k的数量
            preSum += e;
            if (map.find(preSum - k) != map.end())
                count += map[preSum - k];
            ++map[preSum];  // 有负数，可能前缀和会变小
        }
        return count;
    }
};
```





## 0566. 重塑矩阵

### 题目：

在 `MATLAB` 中，有一个非常有用的函数 `reshape` ，它可以将一个 `m x n` 矩阵重塑为另一个大小不同`（r x c）`的新矩阵，但保留其原始数据。

给你一个由二维数组 `mat` 表示的 `m x n` 矩阵，以及两个正整数 `r` 和 `c` ，分别表示想要的重构的矩阵的行数和列数。

重构后的矩阵需要将原始矩阵的所有元素以相同的 行遍历顺序 填充。

如果具有给定参数的 `reshape` 操作是可行且合理的，则输出新的重塑矩阵；否则，输出原始矩阵。

**示例1：**

![leetcode_566_1](F:\C++\刷题\Img\leetcode_566_1.jpg)

```
输入：mat = [[1,2],[3,4]], r = 1, c = 4
输出：[[1,2,3,4]]
```

**示例2：**

![leetcode_566_2](F:\C++\刷题\Img\leetcode_566_2.jpg)

```
输入：mat = [[1,2],[3,4]], r = 2, c = 4
输出：[[1,2],[3,4]]
```

**提示：**

- `m == mat.length`
- `n == mat[i].length`
- `1 <= m, n <= 100`
- `-1000 <= mat[i][j] <= 1000`
- `1 <= r, c <= 300`



**解题思路：**

直接使用一个一维数组进行过渡，但我们也可以直接从二维数组 $\textit{nums}$ 得到 $r$ 行 $c$ 列的重塑矩阵：

设 $\textit{nums}$ 本身为 $m$ 行 $n$ 列，如果 $mn \neq rc$，那么二者包含的元素个数不相同，因此无法进行重塑；

否则，对于 $x \in [0, mn)$，第 $x$ 个元素在 $\textit{nums}$ 中对应的下标为 $(x ~/~ n, x~\%~ n)$，而在新的重塑矩阵中对应的下标为 $(x ~/~ c, x~\%~ c)$。我们直接进行赋值即可。

时间复杂度：O(mn)

空间复杂度：O(1)

**方法：**

```c++
class Solution {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c) {
        int m = mat.size(), n = mat[0].size();
        if (m * n != r * c)
            return mat;
        
        vector<vector<int>> res(r, vector<int>(c, 0));
        for (int x = 0; x < m * n; ++x)
            res[x / c][x % c] = mat[x / n][x % n];
        return res;
    }
};
```





## 0653. 两数之和 IV - 输入 BST

### 题目：

给定一个二叉搜索树 `root` 和一个目标结果 `k`，如果 BST 中存在两个元素且它们的和等于给定的目标结果，则返回 `true`。

**示例 1：**

![leetcode_653_1](F:\C++\刷题\Img\leetcode_653_1.jpg)

```
输入: root = [5,3,6,2,4,null,7], k = 9
输出: true
```

**示例 2：**

![leetcode_653_2](F:\C++\刷题\Img\leetcode_653_2.jpg)

```
输入: root = [5,3,6,2,4,null,7], k = 28
输出: false
```

**示例 3：**

```
输入: root = [2,1,3], k = 4
输出: true
```

**示例 4：**

```
输入: root = [2,1,3], k = 1
输出: false
```

**示例 5：**

```
输入: root = [2,1,3], k = 3
输出: true
```

**提示:**

- 二叉树的节点个数的范围是  `[1, 10^4]`.
- `-10^4 <= Node.val <= 10^4`
- `root` 为二叉搜索树
- `-10^5 <= k <= 10^5`



**解题思路：**

思路一：BFS + 数组

时间复杂度：O(n)

空间复杂度：O(n)

思路二：任意一种遍历 + hash表

时间复杂度：O(n)

空间复杂度：O(n)

**方法一：**

```c++
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        vector<int> v;
        inorder(root, v);
        int l = 0, r = v.size() - 1;
        while (l < r)
        {
            if (v[l] + v[r] == k)
                return true;
            else if (v[l] + v[r] < k)
                ++l;
            else
                --r;
        }
        return false;
    }

    void inorder(TreeNode* root, vector<int>& res) {
        if (root == nullptr)
            return;
        inorder(root->left, res);
        res.push_back(root->val);
        inorder(root->right, res);
    }

	// 非递归的超时
    void inorderTraversal(TreeNode* node, vector<int>& res)
    {
        stack<TreeNode*> st;
        while (!st.empty() || node != nullptr)
        {
            while (node != nullptr)
            {
                st.push(node);
                node = node->left;
            }
            node = st.top(), st.pop();
            res.push_back(node->val);
            if (node->right != nullptr)
                node = node->right;
        }
    }
};
```

**方法二：**

```c++
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        unordered_map<int, TreeNode*> m;
        stack<TreeNode*> st;
        st.push(root);
        while (!st.empty())
        {
            TreeNode* node = st.top();
            st.pop();
            if (m.count(k - node->val) != 0 && node != m[k - node->val])
                return true;
            m.insert(make_pair(node->val, node));

            if (node->left != nullptr) st.push(node->left);
            if (node->right != nullptr) st.push(node->right);
        }
        return false;
    }
};
```





## 0700. 二叉搜索树中的搜索

### 题目：

给定二叉搜索树（BST）的根节点和一个值。 你需要在BST中找到节点值等于给定值的节点。 返回以该节点为根的子树。 如果节点不存在，则返回 NULL。

例如，

```
给定二叉搜索树:

	4
   / \
  2   7
 / \
1   3

和值: 2
```

你应该返回如下子树:

      2     
     / \   
    1   3
在上述示例中，如果要找的值是 `5`，但因为没有节点值为 `5`，我们应该返回 `NULL`。



**解题思路：**

思路一：迭代

时间复杂度：O(n)

空间复杂度：O(1)

思路二：递归

时间复杂度：O(n)

空间复杂度：O(n)

**方法一：**

```c++
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        while (root != nullptr)
        {
            if (root->val == val)
                return root;
            if (root->val > val)
                root = root->left;
            else
                root = root->right;
        }
        return nullptr;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if (root == nullptr || root->val == val)
            return root;
        return root->val > val ? searchBST(root->left, val) : searchBST(root->right, val);
    }
};
```





## 0701. 二叉搜索树中的插入操作

### 题目：

给定二叉搜索树（BST）的根节点和要插入树中的值，将值插入二叉搜索树。 返回插入后二叉搜索树的根节点。 输入数据 **保证** ，新值和原始二叉搜索树中的任意节点值都不同。

注意，可能存在多种有效的插入方式，只要树在插入后仍保持为二叉搜索树即可。 你可以返回 **任意有效的结果** 。

**示例 1：**

![leetcode_701_1](F:\C++\刷题\Img\leetcode_701_1.jpg)

```
输入：root = [4,2,7,1,3], val = 5
输出：[4,2,7,1,3,5]
解释：另一个满足题目要求可以通过的树是：
```

![leetcode_701_2](F:\C++\刷题\Img\leetcode_701_2.jpg)

**示例 2：**

```
输入：root = [40,20,60,10,30,50,70], val = 25
输出：[40,20,60,10,30,50,70,null,null,25]
```

**示例 3：**

```
输入：root = [4,2,7,1,3,null,null,null,null,null,null], val = 5
输出：[4,2,7,1,3,5]
```

**提示：**

- 给定的树上的节点数介于 `0` 和 `10^4` 之间
- 每个节点都有一个唯一整数值，取值范围从 `0` 到 `10^8`
- `-10^8 <= val <= 10^8`
- 新值和原始二叉搜索树中的任意节点值都不同



**解题思路：**

迭代：

时间复杂度：O(n)

空间复杂度：O(1)

**方法：**

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

 // 迭代
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (root == nullptr)
            return new TreeNode(val);

        TreeNode* prev = nullptr;
        TreeNode* p = root;
        while (p != nullptr)
        {
            prev = p;
            if (p->val < val)
                p = p->right;
            else
                p = p->left;
        }
        p = new TreeNode(val);
        if (prev->val > val)
            prev->left = p;
        else
            prev->right = p;
        return root;
    }
};
```





## 0706. 设计哈希映射

### 题目：

不使用任何内建的哈希表库设计一个哈希映射（HashMap）。

实现 `MyHashMap` 类：

- `MyHashMap()` 用空映射初始化对象
- `void put(int key, int value)` 向 `HashMap` 插入一个键值对 `(key, value)` 。如果 key `已经`存在于映射中，则更新其对应的值 `value` 。
- `int get(int key)` 返回特定的 key 所映射的 `value` ；如果映射中不包含 `key` 的映射，返回 `-1` 。
- `void remove(key)` 如果映射中存在 `key` 的映射，则移除 `key` 和它所对应的 `value` 。

**示例：**

```
输入：
["MyHashMap", "put", "put", "get", "get", "put", "get", "remove", "get"]
[[], [1, 1], [2, 2], [1], [3], [2, 1], [2], [2], [2]]
输出：
[null, null, null, 1, -1, null, 1, null, -1]

解释：
MyHashMap myHashMap = new MyHashMap();
myHashMap.put(1, 1); // myHashMap 现在为 [[1,1]]
myHashMap.put(2, 2); // myHashMap 现在为 [[1,1], [2,2]]
myHashMap.get(1);    // 返回 1 ，myHashMap 现在为 [[1,1], [2,2]]
myHashMap.get(3);    // 返回 -1（未找到），myHashMap 现在为 [[1,1], [2,2]]
myHashMap.put(2, 1); // myHashMap 现在为 [[1,1], [2,1]]（更新已有的值）
myHashMap.get(2);    // 返回 1 ，myHashMap 现在为 [[1,1], [2,1]]
myHashMap.remove(2); // 删除键为 2 的数据，myHashMap 现在为 [[1,1]]
myHashMap.get(2);    // 返回 -1（未找到），myHashMap 现在为 [[1,1]]
```

**提示：**

- `0 <= key, value <= 10^6`
- 最多调用 `10^4` 次 `put`、`get` 和 `remove` 方法

**解题思路：**

思路一：

使用vector填充  很慢

思路二：链地址法

自定义hash函数



**方法一：**

```c++
class MyHashMap {
private:
    vector<vector<int>> vm;
public:
    MyHashMap() {
        vm = vector<vector<int>>();
    }
    
    void put(int key, int value) {
        int i = 0;
        for (; i < vm.size(); ++i)
        {
            if (vm[i][0] == key)
            {
                vm[i][1] = value;
                return;
            }
        }
        vm.push_back({key, value});
    }
    
    int get(int key) {
        for (int i = 0; i < vm.size(); ++i)
        {
            if (vm[i][0] == key)
                return vm[i][1];
        }
        return -1;
    }
    
    void remove(int key) {
        for (auto it = vm.begin(); it != vm.end(); ++it)
        {
            if ((*it)[0] == key)
            {
                vm.erase(it);
                return;
            }
        }
    }
};
```

**方法二：**

```c++
class MyHashMap {
private:
    vector<list<pair<int, int>>> vm;
    static const int base = 769;
    static int hash(int key)
    {
        return key % base;
    }

public:
    MyHashMap(): vm(base) {}
    
    void put(int key, int value) {
        int h = hash(key);
        for (auto it = vm[h].begin(); it != vm[h].end(); ++it)
        {
            if (it->first == key)
            {
                it->second = value;
                return;
            }
        }
        vm[h].push_back(make_pair(key, value));
    }
    
    int get(int key) {
        int h = hash(key);
        for (auto it = vm[h].begin(); it != vm[h].end(); ++it)
        {
            if (it->first == key)
                return it->second;
        }
        return -1;
    }
    
    void remove(int key) {
        int h = hash(key);
        for (auto it = vm[h].begin(); it != vm[h].end(); ++it)
        {
            if (it->first == key)
            {
                vm[h].erase(it);
                return;
            }
        }
    }
};
```





## 0707. 设计链表

### 题目：

设计链表的实现。您可以选择使用单链表或双链表。单链表中的节点应该具有两个属性：`val` 和 `next`。`val` 是当前节点的值，`next` 是指向下一个节点的指针/引用。如果要使用双向链表，则还需要一个属性 `prev` 以指示链表中的上一个节点。假设链表中的所有节点都是 `0-index` 的。

在链表类中实现这些功能：

- `get(index)`：获取链表中第 `index` 个节点的值。如果索引无效，则返回`-1`。
- `addAtHead(val)`：在链表的第一个元素之前添加一个值为 `val` 的节点。插入后，新节点将成为链表的第一个节点。
- `addAtTail(val)`：将值为 `val` 的节点追加到链表的最后一个元素。
- `addAtIndex(index,val)`：在链表中的第 `index` 个节点之前添加值为 `val`  的节点。如果 `index` 等于链表的长度，则该节点将附加到链表的末尾。如果 `index` 大于链表长度，则不会插入节点。如果`index`小于`0`，则在头部插入节点。
- `deleteAtIndex(index)`：如果索引 `index` 有效，则删除链表中的第 `index` 个节点。

**示例：**

```
MyLinkedList linkedList = new MyLinkedList();
linkedList.addAtHead(1);
linkedList.addAtTail(3);
linkedList.addAtIndex(1,2);   //链表变为1-> 2-> 3
linkedList.get(1);            //返回2
linkedList.deleteAtIndex(1);  //现在链表是1-> 3
linkedList.get(1);            //返回3
```

**提示：**

- 所有`val`值都在 `[1, 1000]` 之内。
- 操作次数将在  `[1, 1000]` 之内。
- 请不要使用内置的 `LinkedList` 库。

**解题思路：**

注意空节点和只剩一个节点的情况

**方法一：**双向链表

```c++
class ListNode1 {
public:
    int val = 0;
    ListNode1* next;
    ListNode1* prev;
    ListNode1(int v, ListNode1* n = nullptr, ListNode1* p = nullptr) : val(v), next(n), prev(p)
    {}
};


class MyLinkedList {
public:
    ListNode1* root;
    ListNode1* tail;
    int size;
public:
    MyLinkedList() {
        root = nullptr;
        tail = nullptr;
        size = 0;
    }
    
    int get(int index) {
        int i = 0;
        ListNode1* p = root;
        while (p != nullptr)
        {
            if (i++ == index)
                return p->val;
            p = p->next;
        }
        return -1;
    }
    
    void addAtHead(int val) {
        ListNode1* head = new ListNode1(val);
        if (root == nullptr)
            root = tail = head;
        else
        {
            head->next = root;
            root->prev = head;
            root = head;
        }
        ++size;
    }
    
    void addAtTail(int val) {
        ListNode1* rhead = new ListNode1(val);
        if (tail == nullptr)
            root = tail = rhead;
        else
        {
            tail->next = rhead;
            rhead->prev = tail;
            tail = rhead;
        }
        ++size;
    }
    
    void addAtIndex(int index, int val) {
        if (index > size)
            return;
        if (index <= 0)
        {
            addAtHead(val);
            return;
        }
        if (index == size)
        {
            addAtTail(val);
            return;
        }

        ListNode1* p = root;
        while (index-- > 0)
            p = p->next;
        ListNode1* q = new ListNode1(val);
        q->next = p;
        q->prev = p->prev;
        q->next->prev = q;
        q->prev->next = q;
        ++size;
    }
    
    void deleteAtIndex(int index) {
        if (index >= size || index < 0)
            return;
        if (size == 1)
        {
            delete root;
            root = tail = nullptr;
            --size;
            return;
        }
        if (index == 0)
        {
            ListNode1* p = root;
            root = p->next;
            root->prev = nullptr;
            delete p;
            --size;
            return;
        }
        if (index == size - 1)
        {
            ListNode1* p = tail;
            tail = p->prev;
            tail->next = nullptr;
            delete p;
            --size;
            return;
        }
        ListNode1* p = root;
        while (index-- > 0)
            p = p->next;
        p->next->prev = p->prev;
        p->prev->next = p->next;
        delete p;
        --size;
    }
};
```

**方法二：**单向列表

```c++
// 单链表
class ListNode1 {
public:
    int val = 0;
    ListNode1* next;
    ListNode1(int v, ListNode1* n = nullptr) : val(v), next(n)
    {}
};


class MyLinkedList {
public:
    ListNode1* root;
    int size;
public:
    MyLinkedList() {
        root = nullptr;
        size = 0;
    }
    
    int get(int index) {
        int i = 0;
        ListNode1* p = root;
        while (p != nullptr)
        {
            if (i++ == index)
                return p->val;
            p = p->next;
        }
        return -1;
    }
    
    void addAtHead(int val) {
        ListNode1* head = new ListNode1(val);
        if (root == nullptr)
            root  = head;
        else
        {
            head->next = root;
            root = head;
        }
        ++size;
    }
    
    void addAtTail(int val) {
        ListNode1* tail = new ListNode1(val);
        if (root == nullptr)
            root  = tail;
        else
        {
            ListNode1* p = root;
            while (p->next != nullptr)
                p = p->next;
            p->next = tail;
        }
        ++size;
    }
    
    void addAtIndex(int index, int val) {
        if (index > size)
            return;
        if (index <= 0)
        {
            addAtHead(val);
            return;
        }
        if (index == size)
        {
            addAtTail(val);
            return;
        }

        ListNode1* p = root;
        while (index-- > 1)
            p = p->next;
        ListNode1* q = new ListNode1(val);
        q->next = p->next;
        p->next = q;
        ++size;
    }
    
    void deleteAtIndex(int index) {
        if (index >= size || index < 0)
            return;
        if (size == 1)
        {
            delete root;
            root = nullptr;
            --size;
            return;
        }
        if (index == 0)
        {
            ListNode1* p = root;
            root = p->next;
            delete p;
            --size;
            return;
        }
        ListNode1* p = root;
        ListNode1* prev = nullptr;
        while (p != nullptr && index-- > 0)
        {
            prev = p;
            p = p->next;
        }
        if (p != nullptr)
        {
            prev->next = p->next;
            delete p;
            --size;
        }
    }
};
```





## 0763. 划分字母区间

### 题目：

字符串 S 由小写字母组成。我们要把这个字符串划分为尽可能多的片段，同一字母最多出现在一个片段中。返回一个表示每个字符串片段的长度的列表。

**示例：**

```
输入：S = "ababcbacadefegdehijhklij"
输出：[9,7,8]
解释：
划分结果为 "ababcbaca", "defegde", "hijhklij"。
每个字母最多出现在一个片段中。
像 "ababcbacadefegde", "hijhklij" 的划分是错误的，因为划分的片段数较少。
```

**提示：**

- `S`的长度在`[1, 500]`之间。
- `S`只包含小写字母 `'a'` 到 `'z'` 。



**解题思路：**

先用一个数组last[26]更新每个字符在最后一次出现的下标；

再次遍历字符串，记录当前字符的last和前面累计的last的最大值，使用end标记；

**方法：**

```c++
class Solution {
public:
    vector<int> partitionLabels(string s) {
        int last[26];
        int n = s.length();
        for (int i = 0; i < n; ++i)
            last[s[i] - 'a'] = i;
        
        vector<int> strlens;
        int start = 0, end = 0;
        for (int i = 0; i < n; ++i)
        {
            // 当前字符的last和前面累计的last的最大值
            end = max(end, last[s[i] - 'a']);
            if (i == end)
            {
                strlens.push_back(end - start + 1);
                start = end + 1;
            }
        }
        return strlens;
    }
};
```





## 1249. 移除无效的括号

### 题目：

给你一个由 `'('、')'` 和小写字母组成的字符串 `s`。

你需要从字符串中删除最少数目的 `'('` 或者 `')'` （可以删除任意位置的括号)，使得剩下的「括号字符串」有效。

请返回任意一个合法字符串。

有效「括号字符串」应当符合以下 **任意一条** 要求：

- 空字符串或只包含小写字母的字符串
- 可以被写作 `AB`（`A` 连接 `B`）的字符串，其中 `A` 和 `B` 都是有效「括号字符串」
- 可以被写作 `(A)` 的字符串，其中 `A` 是一个有效的「括号字符串」

**示例 1：**

```
输入：s = "lee(t(c)o)de)"
输出："lee(t(c)o)de"
解释："lee(t(co)de)" , "lee(t(c)ode)" 也是一个可行答案。
```

**示例 2：**

```
输入：s = "a)b(c)d"
输出："ab(c)d"
```

**示例 3：**

```
输入：s = "))(("
输出：""
解释：空字符串也是有效的
```

**示例 4：**

```
输入：s = "(a(b(c)d)"
输出："a(b(c)d)"
```

**提示：**

- `1 <= s.length <= 10^5`
- `s[i]` 可能是 `'('、')'` 或英文小写字母



**解题思路：**

使用三次循环，第一次从前往后，剔除右括号不符合的，第二次从后往前，剔除左括号不符合的，第三次重新组织字符串；

时间复杂度：O(n)

空间复杂度：O(n)

**方法：**

```c++
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        string ans;
        stack<int> st;
        for (int i = 0; i < s.length(); ++i)
        {
            if (s[i] == '(')
                st.push(s[i]);
            else if (s[i] == ')')
            {
                if (st.empty())
                    s[i] = '.';
                else
                    st.pop();
            }
        }

        stack<int> st1;
        for (int i = s.length() - 1; i >= 0; --i)
        {
            if (s[i] == ')')
                st1.push(s[i]);
            else if (s[i] == '(')
            {
                if (st1.empty())
                    s[i] = '.';
                else
                    st1.pop();
            }
        }

        for (int i = 0; i < s.length(); ++i)
        {
            if (s[i] != '.')
                ans += s[i];
        }
        return ans;
    }
};
```





## 1823. 找出游戏的获胜者

### 题目：

共有 `n` 名小伙伴一起做游戏。小伙伴们围成一圈，按 **顺时针顺序** 从 `1` 到 `n` 编号。确切地说，从第 `i` 名小伙伴顺时针移动一位会到达第 `(i+1)` 名小伙伴的位置，其中 `1 <= i < n` ，从第 `n` 名小伙伴顺时针移动一位会回到第 `1` 名小伙伴的位置。

游戏遵循如下规则：

1. 从第 `1` 名小伙伴所在位置 **开始** 。
2. 沿着顺时针方向数 `k` 名小伙伴，计数时需要 **包含** 起始时的那位小伙伴。逐个绕圈进行计数，一些小伙伴可能会被数过不止一次。
3. 你数到的最后一名小伙伴需要离开圈子，并视作输掉游戏。
4. 如果圈子中仍然有不止一名小伙伴，从刚刚输掉的小伙伴的 **顺时针下一位** 小伙伴 **开始**，回到步骤 `2` 继续执行。
5. 否则，圈子中最后一名小伙伴赢得游戏。

给你参与游戏的小伙伴总数 `n` ，和一个整数 `k` ，返回游戏的获胜者。

**示例 1：**

![leetcode_1823](F:\C++\刷题\Img\leetcode_1823.png)

```
输入：n = 5, k = 2
输出：3
解释：游戏运行步骤如下：

1. 从小伙伴 1 开始。
2. 顺时针数 2 名小伙伴，也就是小伙伴 1 和 2 。
3. 小伙伴 2 离开圈子。下一次从小伙伴 3 开始。
4. 顺时针数 2 名小伙伴，也就是小伙伴 3 和 4 。
5. 小伙伴 4 离开圈子。下一次从小伙伴 5 开始。
6. 顺时针数 2 名小伙伴，也就是小伙伴 5 和 1 。
7. 小伙伴 1 离开圈子。下一次从小伙伴 3 开始。
8. 顺时针数 2 名小伙伴，也就是小伙伴 3 和 5 。
9. 小伙伴 5 离开圈子。只剩下小伙伴 3 。所以小伙伴 3 是游戏的获胜者。
```

**示例 2：**

```
输入：n = 6, k = 5
输出：1
解释：小伙伴离开圈子的顺序：5、4、6、2、3 。小伙伴 1 是游戏的获胜者。
```

**提示：**

`1 <= k <= n <= 500`



**解题思路：**

思路一：暴力解法

思路二：动态规划

时间复杂度：O(n)

空间复杂度：O(n)

思路三：约瑟夫环

时间复杂度：O(n)

空间复杂度：O(1)

**方法一：**

```c++
class Solution {
public:
    int findTheWinner(int n, int k) {
        int i = -1;
        int remain = n;
        vector<int> v(n, 1);
        while (remain-- > 1)
        {
            int c = 0;
            while (c < k)
            {
                i = (i + 1) % n;
                if (v[i] == 1)
                    ++c;
            }
            v[i] = 0;
        }

        for (i = 0; i < n; ++i)
            if (v[i] == 1)
                break;
            
        return i + 1;
    }
};
```

**方法二：**

```c++
class Solution {
public:
    int findTheWinner(int n, int k) {
        vector<int> v(n + 1, 0);
        v[1] = 1;
        for (int i = 2; i <= n; ++i)
        {
            // f[i-1] + k即为偏移量，为防止刚好整除的情形导致取模为0，对原值-1后再对模+1.
            v[i] = ((v[i - 1] + k - 1) % i) + 1;
        }
        return v[n];
    }
};
```

**方法三：**

```c++
class Solution {
public:
    int findTheWinner(int n, int k) {
        int p = 0;
        for (int i = 2; i <= n; ++i)
        {
            p = (p + k) % i;
        }
        return p + 1;
    }
};
```

