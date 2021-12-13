
// n & (n - 1)求最大前缀
class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        while (left < right)
            right &= (right - 1);
        return right;
    }
};

/*
// 位运算求最大前缀
class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        int shift = 0;
        while (left < right)
        {
            ++shift;
            left >>= 1;
            right >>= 1;
        }
        return right << shift;
    }
};
*/