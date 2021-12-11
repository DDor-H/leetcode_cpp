
// 计数排序(超时)
class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1)
            return 0;
        countSort(nums);
        int maxSpan = INT_MIN;
        for (int i = 1; i < n; ++i)
            maxSpan = max(maxSpan, nums[i] - nums[i - 1]);
        return maxSpan;
    }

    void countSort(vector<int>& nums)
    {
        int minV = *min_element(nums.begin(), nums.end());
        int maxV = *max_element(nums.begin(), nums.end());
        int n = nums.size();
        int k = maxV - minV + 1;
        vector<int> count = vector<int>(k, 0);
        vector<int> tmp = vector<int>(nums.begin(), nums.end());
        for (int i = 0; i < n; ++i)
            ++count[nums[i] - minV];
        for (int i = 1; i < k; ++i)
            count[i] = count[i] + count[i - 1];
        for (int i = 0; i < n; ++i)
            nums[--count[tmp[i] - minV]] = tmp[i];
    }
};

/*
// 桶排序
class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1)
            return 0;
        BucketSort(nums);
        int maxSpan = INT_MIN;
        for (int i = 1; i < n; ++i)
            maxSpan = max(maxSpan, nums[i] - nums[i - 1]);
        return maxSpan;
    }

    void BucketSort(vector<int>& nums)
    {
        int d = getMaxBit(nums);
        int n = nums.size();
        vector<list<int>> bucket = vector<list<int>>(10, list<int>());
        int radix = 1;
        int i, j, k;
        for (i = 0; i < d; ++i)
        {
            for (j = 0; j < 10; ++j)
                bucket[j].clear();
            for (j = 0; j < n; ++j)
            {
                k = (nums[j] / radix) % 10;
                bucket[k].push_back(nums[j]);
            }
            int m = 0;
            for (j = 0; j < 10; ++j)
            {
                while (!bucket[j].empty())
                {
                    nums[m++] = bucket[j].front();
                    bucket[j].pop_front();
                }
            }
            
            radix *= 10;
        }
    }

    int getMaxBit(vector<int>& nums)
    {
        int maxData = INT_MIN;
        for (auto& e : nums)
            maxData = max(maxData, e);
        int count = 0;
        while (maxData > 0)
        {
            ++count;
            maxData /= 10;
        }
        return count;
    }
};

/*
// 基数排序
class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1)
            return 0;
        radixsort(nums);
        int maxSpan = INT_MIN;
        for (int i = 1; i < n; ++i)
            maxSpan = max(maxSpan, nums[i] - nums[i - 1]);
        return maxSpan;
    }

    void radixsort(vector<int>& nums)
    {
        int d = getMaxBit(nums);
        int n = nums.size();
        vector<int> tmp = vector<int>(n, 0);
        vector<int> count = vector<int>(10, 0);
        int radix = 1;
        int i, j, k;
        for (i = 0; i < d; ++i)
        {
            for (j = 0; j < 10; ++j)
                count[j] = 0;
            for (j = 0; j < n; ++j)
            {
                k = (nums[j] / radix) % 10;
                ++count[k];
            }
            for (j = 1; j < 10; ++j)
                count[j] = count[j] + count[j - 1];
            for (j = n - 1; j >= 0; --j)
            {
                k = (nums[j] / radix) % 10;
                tmp[count[k] - 1] = nums[j];
                --count[k];
            }
            for (j = 0; j < n; ++j)
                nums[j] = tmp[j];
            radix *= 10;
        }
    }

    int getMaxBit(vector<int>& nums)
    {
        int maxData = INT_MIN;
        for (auto& e : nums)
            maxData = max(maxData, e);
        int count = 0;
        while (maxData > 0)
        {
            ++count;
            maxData /= 10;
        }
        return count;
    }
};
*/