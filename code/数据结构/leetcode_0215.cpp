
    
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int heapSize = nums.size();
        buildHeapify(nums, heapSize);
        for (int i = 0; i < k - 1; ++i)
        {
            swap(nums[0], nums[heapSize - 1]);
            maxHeapify(nums, 0, --heapSize);
        }
        return nums[0];
    }

    void buildHeapify(vector<int>& nums, int heapSize)
    {
        for (int i = heapSize / 2; i >= 0; --i)
            maxHeapify(nums, i, heapSize);
    }
    void maxHeapify(vector<int>& nums, int idx, int heapSize)
    {
        int left = 2 * idx + 1, right = 2 * idx + 2, largest = idx;
        if (left < heapSize && nums[left] > nums[largest])
            largest = left;
        if (right < heapSize && nums[right] > nums[largest])
            largest = right;
        if (largest != idx)
        {
            swap(nums[idx], nums[largest]);
            maxHeapify(nums, largest, heapSize);
        }
    }
};

/*
// 快速选择算法
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        srand(time(0));
        return quicklySelect(nums, 0, nums.size() - 1, nums.size() - k);
    }

    int quicklySelect(vector<int>& nums, int left, int right, int kth)
    {
        int q = randomPartition(nums, left, right);
        if (q == kth)
            return nums[q];
        return q > kth ? quicklySelect(nums, left, q - 1, kth) : quicklySelect(nums, q + 1, right, kth);
    }

    int randomPartition(vector<int>& nums, int left, int right)
    {
        int p = rand() % (right - left + 1) + left;
        swap(nums[p], nums[right]);

        int x = nums[right], i = left - 1;
        for (int j = left; j < right; ++j)
        {
            if (nums[j] <= x)
                swap(nums[++i], nums[j]);
        }
        swap(nums[i + 1], nums[right]);
        return i + 1;
    }
};

/*
// API选手
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> pq(nums.begin(), nums.end());
        while (--k)
            pq.pop();
        return pq.top();
    }
};
*/