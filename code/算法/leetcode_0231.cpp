
// 最大数的约数
class Solution {
private:
    static constexpr int BIG = 1 << 30;
public:
    bool isPowerOfTwo(int n) {
        return n > 0 && BIG % n == 0;
    }
};

/*
// 位运算
class Solution {
public:
    bool isPowerOfTwo(int n) {
        return n > 0 && (n & (n - 1)) == 0;
        // return n > 0 && (n & (-n)) == n;
    }
};

/*
// 递归
class Solution {
public:
    bool isPowerOfTwo(int n) {
        if (n == 1) return true;
        if (n <= 0) return false;
        
        if (n % 2 == 1) return false;
        return isPowerOfTwo(n / 2);
    }
};

/*
// 循环
class Solution {
public:
    bool isPowerOfTwo(int n) {
        if (n == 1) return true;
        if (n <= 0) return false;
        
        while (n % 2 != 1)
        {
            n /= 2;
            if (n == 1)
                return true;
        }
        return false;
    }
};
*/