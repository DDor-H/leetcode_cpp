class Solution {
public:
    string replaceSpace(string s) {
        int s_size = s.length();
        int space_count = 0;
        for (int i = 0; i < s_size; ++i)
        {
            if (s[i] == ' ')
                ++space_count;
        }
        string res;
        int res_size = s_size + 2 * space_count;
        res.resize(res_size);
        for (int i = res_size - 1, j = s_size - 1; i >=0 && j >= 0;)
        {
            if (s[j] != ' ')
                res[i--] = s[j--];
            else
            {
                res[i--] = '0';
                res[i--] = '2';
                res[i--] = '%';
                --j;
            }
        }
        return res;
    }
};