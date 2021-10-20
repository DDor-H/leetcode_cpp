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