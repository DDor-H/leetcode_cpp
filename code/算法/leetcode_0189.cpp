
// 环状旋转
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;
        int count = gcd(k, n);
        for (int start = 0; start < count; ++start)
        {
            int curr = start;
            int prev = nums[start];
            do
            {
                int next = (curr + k) % n;
                swap(prev, nums[next]);
                curr = next;
            }while (curr != start);
        }
    }
};

/*
// 额外数组
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;
        vector<int> tmpArr(n);
        for (int i = 0; i < n; ++i)
            tmpArr[i] = nums[(i + (n - k)) % n];
        nums.assign(tmpArr.begin(), tmpArr.end());
    }
};

/*
// 翻转
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;
        reverse(nums, 0, n - k - 1);
        reverse(nums, n - k, n - 1);
        reverse(nums, 0, n - 1);
    }
    void reverse(vector<int>& nums, int left, int right)
    {
        while (left < right)
        {
            swap(nums[left], nums[right]);
            ++left, --right;
        }
    }
};
*/