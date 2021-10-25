class Solution {
public:
    int AddItem(int a, int b, int& sign)
    {
        int sum = a + b + sign;
        if (sum > 9)
        {
            sum -= 10;
            sign = 1;
        }
        else
            sign = 0;
        return sum;
    }
    //进位问题，所以反转之后就好解决了
    string addStrings(string num1, string num2) {
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        int i, j, sign, sum;
        i = j = 0;
        sign = 0;
        sum = 0;
        string result;
        while (i < num1.size() && j < num2.size())
        {
            sum = AddItem(num1[i] - '0', num2[j] - '0', sign);
            result += (sum + '0');
            ++i;
            ++j;
        }
        while (i < num1.size())
        {
            sum = AddItem(num1[i] - '0', 0, sign);
            result += (sum + '0');
            ++i;
        }
        while (j < num2.size())
        {
            sum = AddItem(0, num2[j] - '0', sign);
            result += (sum + '0');
            ++j;
        }
        if (sign == 1)
            result += (sign + '0');
        reverse(result.begin(), result.end());
        return result;
    }
};