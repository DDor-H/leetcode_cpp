class Solution {
public:
    bool wordPattern(string pattern, string s) {
        unordered_map<string, char> str2ch;
        unordered_map<char, string> ch2str;
        int m = s.length();
        int i = 0;
        for (auto& ch : pattern)
        {
            // 单词数不够字符数
            if (i >= m)
                return false;
            int j = i;
            while (j < m && s[j] != ' ')
                ++j;
            string str = s.substr(i, j - i);
            // 如果之前出现过这个字符串，检查是否等于当前对应字符
            if (str2ch.count(str) && str2ch[str] != ch)
                return false;
            // 如果之前出现过这个字符，检查是否等于当前对应字符串
            if (ch2str.count(ch) && ch2str[ch] != str)
                return false;
            str2ch[str] = ch;
            ch2str[ch] = str;
            i = j + 1;
        }
        return i >= m;  // 最后一个空格符，就会 = ，最后一个非空格符，就会 > 
    }
};