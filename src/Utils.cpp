#include "Utils.h"

namespace utils {
        // 4轮循环中使用的生成函数 (轮函数)
    u_int F(u_int x, u_int y, u_int z) { return (x & y) | ((~x) & z); }  
    u_int G(u_int x, u_int y, u_int z) { return (x & z) | (y & (~z)); }
    u_int H(u_int x, u_int y, u_int z) { return (x ^ y ^ z); }
    u_int I(u_int x, u_int y, u_int z) { return (y ^ (x | ~z)); }

    // 将32位输入循环左移 (CLS) s 位
    u_int CycleMoveLeft(u_int x, int n) { return (x << n) | (x >> (32 - n)); }

    //各次迭代运算采用的左循环移位的 s 值：
    u_int s[4][16] = { 
        7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,  // 第一轮
        5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,      // 第二轮
        4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,  // 第三轮
        6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21   // 第四轮
    };

    // 每次循环对应的X[k]
    int X_table[4][16] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,   // 第一轮
        1, 6, 11, 0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12,   // 第二轮
        5, 8, 11, 14, 1, 4, 7, 10, 13, 0, 3, 6, 9, 12, 15, 2,   // 第三轮
        0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 4, 11, 2, 9    // 第四轮
    };

    // 获取各次迭代运算采用的 T 值
    // u_int T(int i) { return u_int(long((u_int)1 << 32) * sin(i)); }
    u_int T[64] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
    };

    u_int charToUint(u_char charArray[4]) {
        u_int res = 0;
        for (int i = 3; i >= 0; i--) {
            res = (res << 8) + charArray[i];
        }
        return res;
    }
}