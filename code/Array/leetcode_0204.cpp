// 筛除法
class Solution {
public:
    int countPrimes(int n) {
        if (n <= 2)
            return 0;
        int ans = 0;
        vector<int> isPrime(n, 1);
        for (int i = 2; i < n; ++i)
        {
            ans += isPrime[i];
            if ((long long)i * i < n)
            {
                for (int j = i * i; j < n; j += i)
                    isPrime[j] = 0;
            }
        }
        return ans;
    }
};

/*
// 暴力解法（超时）
class Solution {
public:
    int countPrimes(int n) {
        if (n <= 2)
            return 0;
        int ans = 0;
        for (int i = 2; i < n; ++i)
            ans += isPrime(i);
        return ans;
    }
    int isPrime(int x)
    {
        for (int i = 2; i * i <= x; ++i)
            if (x % i == 0)
                return 0;
        return 1;
    }
};
*/