class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int len = digits.size();
        for (int i = len - 1; i >= 0; --i)
        {
            digits[i]++;
            digits[i] %= 10;
            if (digits[i] != 0)
                return digits;
        }
        digits.insert(digits.begin(), 1);
        return digits;
    }
};