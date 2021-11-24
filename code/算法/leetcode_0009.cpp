
// 反转一半数字
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0 || (x / 10 != 0 && x % 10 == 0))
            return false;

        int num = 0;
        while (x > num)
        {
            num = num * 10 + x % 10;
            x /= 10;
        }
        return x == num || x == num / 10;
    }
};

/*
// 使用list存储
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0)
            return false;

        list<int> v;
        while (x)
        {
            v.push_back(x % 10);
            x /= 10;
        }

        while (v.size() != 0)
        {
            if (v.size() == 1)
                return true;
            if (v.back() != v.front())
                return false;
            v.pop_back();
            v.pop_front();
        }
        return true;
    }
};
*/