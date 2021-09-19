# Array

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

​		依次从每一个下表的 i  i  位置和 i  i+1 位置向两边扩散，寻找最长回文

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

当两个子串最后一个字母相同，可以选择删除掉第一个字串最后一个，然后比较前面；

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































