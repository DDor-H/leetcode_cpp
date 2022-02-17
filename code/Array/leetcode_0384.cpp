
// 使用辅助数组
class Solution {
private:
    vector<int> nums;
    vector<int> original;
public:
    Solution(vector<int>& nums) {
        this->nums = nums;
        this->original.resize(this->nums.size());
        copy(this->nums.begin(), this->nums.end(), this->original.begin());
    }
    
    vector<int> reset() {
        copy(this->original.begin(), this->original.end(), this->nums.begin());
        return this->nums;
    }
    
    vector<int> shuffle() {
        for (int i = 0; i < this->original.size(); ++i)
        {
            // i 和 i - n 之间的一个 j 交换
            // 也就是 j 有机会放前面
            int j = i + rand() % (this->nums.size() - i);
            swap(this->nums[i], this->nums[j]);
        }
        return this->nums;
    }
};

/*
// 使用辅助数组
class Solution {
private:
    vector<int> nums;
    vector<int> original;
public:
    Solution(vector<int>& nums) {
        this->nums = nums;
        this->original.resize(this->nums.size());
        copy(this->nums.begin(), this->nums.end(), this->original.begin());
    }
    
    vector<int> reset() {
        copy(this->original.begin(), this->original.end(), this->nums.begin());
        return this->nums;
    }
    
    vector<int> shuffle() {
        vector<int> tmp = vector<int>(this->nums.size());
        copy(this->original.begin(), this->original.end(), tmp.begin());
        for (int i = 0; i < this->original.size(); ++i)
        {
            int j = rand() % (tmp.size());
            this->nums[i] = tmp[j];
            tmp.erase(tmp.begin() + j);
        }
        return this->nums;
    }
};
*/

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */