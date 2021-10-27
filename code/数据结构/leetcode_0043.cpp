
class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0")
            return "0";
        int m = num1.size(), n = num2.size();
        vector<int> arr(m + n, 0);
        for (int i = m - 1; i >= 0; --i)
        {
            int x = num1[i] - '0';
            for (int j = n - 1; j >= 0; --j)
            {
                int y = num2[j] - '0';
                arr[i + j + 1] += x * y;
            }
        }

        for (int i = m + n - 1; i > 0; --i)
        {
            arr[i - 1] += arr[i] / 10;
            arr[i] %= 10;
        }

        int i = 0;
        while (arr[i] == 0 && i < m + n)
            ++i;
        string ans;
        while (i < m + n)
            ans += (arr[i++] + '0');
        return ans;
    }
};


/*
class Solution {
public:
    string MultString(string& str, char c)
    {
        string tmp;
        int sign = 0;
        for (int i = 0; i < str.size(); ++i)
        {
            int mul = (str[i] - '0') * (c - '0') + sign;
            if (mul >= 10)
            {
                sign = mul / 10;
                mul %= 10;
            }
            else
                sign = 0;
            tmp += (mul + '0');
        }
        if (sign != 0)
            tmp += (sign + '0');
        return tmp;
    }
    char AddItem(char& c1, char& c2, int& sign)
    {
        int tmp = (c1 - '0') + (c2 - '0') + sign;
        if (tmp >= 10)
        {
            sign = tmp / 10;
            tmp %= 10;
        }
        else
            sign = 0;
        return tmp + '0';
    }
    string MoveAdd(string& res, string& str2, int k)
    {
        int sign = 0;
        int i = k;
        int j = 0;
        while (i < res.size())
        {
            res[i] = AddItem(res[i], str2[j], sign);
            ++i;
            ++j;
        }
        char zero = '0';
        while (j < str2.size())
        {
            res += AddItem(zero, str2[j], sign);
            ++j;
        }
        if (sign != 0)
            res += (sign + '0');
        return res;
    }
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0")
            return string("0");
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());

        string sum("0");
        string tmp;
        for (int i = 0; i < num2.size(); ++i)
        {
            tmp = MultString(num1, num2[i]);
            MoveAdd(sum, tmp, i);
            tmp.clear();
        }

        reverse(sum.begin(), sum.end());
        return sum;
    }
};
*/