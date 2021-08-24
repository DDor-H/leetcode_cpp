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

