#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <iostream>
using namespace std;

namespace utils {

    // 定义相关使用类型
    typedef unsigned int  u_int;
    typedef unsigned char u_char;
    typedef u_int (*RoundFunc[])(u_int, u_int, u_int);

    // 4轮循环中使用的生成函数 (轮函数)
    u_int F(u_int x, u_int y, u_int z); 
    u_int G(u_int x, u_int y, u_int z);
    u_int H(u_int x, u_int y, u_int z);
    u_int I(u_int x, u_int y, u_int z);

    // 将32位输入循环左移 (CLS) s 位
    u_int CycleMoveLeft(u_int x, int n);

    //各次迭代运算采用的左循环移位的 s 值：
    extern u_int s[4][16];

    // 每次循环对应的X[k]
    extern int X_table[4][16];

    // 获取各次迭代运算采用的 T 值
    // u_int T(int i);
    extern u_int T[64];

    u_int charToUint(u_char charArray[4]);
}

#endif
