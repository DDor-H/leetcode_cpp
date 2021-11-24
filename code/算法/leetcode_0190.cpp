
// 位运算分治
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        const uint32_t M1 = 0x55555555; // 01010101010101010101010101010101
        const uint32_t M2 = 0x33333333; // 00110011001100110011001100110011
        const uint32_t M4 = 0x0f0f0f0f; // 00001111000011110000111100001111
        const uint32_t M8 = 0x00ff00ff; // 00000000111111110000000011111111
        const uint32_t M16 = 0x0000ffff; // 00000000000000001111111111111111

        n = (n >> 1) & M1 | (n & M1) << 1;
        n = (n >> 2) & M2 | (n & M2) << 2;
        n = (n >> 4) & M4 | (n & M4) << 4;
        n = (n >> 8) & M8 | (n & M8) << 8;
        n = (n >> 16) & M16 | (n & M16) << 16;
        return n;
    }
};

/*
// 逐位逆置
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t ans = 0;
        for (int i = 0; i < 32 && n > 0; ++i)
        {
            ans |= (n & 1) << (31 - i);
            n >>= 1;
        }
        return ans;
    }
};

/*
// 逐位逆置
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t ans = 0;
        for (int i = 0; i < 32 && n > 0; ++i)
        {
            ans |= (n & 1) << (31 - i);
            n >>= 1;
        }
        return ans;
    }
};

/*
// 循环
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        for (int i = 0; i < 16; ++i)
        {
            uint32_t RB = (n >> i) & 0x01;
            uint32_t LB = (n >> (31 - i)) & 0x01;

            if (RB == LB)
                continue;
            if (RB == 0)
            {
                n &= (0xffffffff ^ (1 << (31 - i)));
                n |= (1 << i);
            }
            else
            {
                n |= (1 << (31 - i));
                n &= (0xffffffff ^ (1 << i));
            }
        }
        return n;
    }
};
*/