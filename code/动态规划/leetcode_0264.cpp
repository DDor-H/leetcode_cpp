
// 方法三：动态规划
class Solution {
public:
    int nthUglyNumber(int n) 
    {
        if (n == 1)
            return 1;
        
        vector<int> dp(n + 1, 0);
        dp[1] = 1;
        int p2 = 1, p3 = 1, p5 = 1;
        for (int i = 2; i <= n; ++i)
        {
            int num2 = dp[p2] * 2, num3 = dp[p3] * 3, num5 = dp[p5] * 5;
            dp[i] = min(num2, min(num3, num5));
            if (dp[i] == num2) ++p2;
            if (dp[i] == num3) ++p3;
            if (dp[i] == num5) ++p5;
        }
        return dp[n];
    }
};

/*
// 方法二：暴力解法(超时)
class Solution {
public:
    bool isUgly(int n) {
        while( n > 0 )
        {
            if(n==1)
                return true;
            if(n%2==0)
                n /= 2;
            else if(n%3==0)
                n /= 3;
            else if(n%5==0)
                n /= 5;
            else
                break;
        }
        return false;
    }

    int nthUglyNumber(int n) {
        int count=0,num=1;
        while(count!=n)
        {
            if(isUgly(num))
                count++;
            num++;
        }
        return num-1;
    }
};

/*
// 方法一：大顶堆
class Solution {
public:
    int nthUglyNumber(int n) {
        if (n == 1)
            return 1;
        
        vector<int> factors = {2, 3, 5};
        unordered_set<long> seen;
        priority_queue<long, vector<long>, greater<long>> heap;
        heap.push(1L);
        seen.insert(1L);
        int ugly = 0;

        for (int i = 0; i < n; ++i)
        {
            long curr = heap.top();
            heap.pop();
            ugly = (int)curr;

            for (auto & facotr : factors)
            {
                long next = facotr * curr;
                if (!seen.count(next))
                {
                    seen.insert(next);
                    heap.push(next);
                }
            }
        }
        return ugly;
    }
};
*/