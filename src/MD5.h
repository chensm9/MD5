#ifndef MD5_H
#define MD5_H

#include <iostream>
#include <cstring>
#include "Utils.h"

using namespace std;
using namespace utils;

class MD5 {
    public:
        MD5(const string& str);
        // 初始化MD缓冲区的内容
        void initCV();
        // 对输入的字符串信息进行相关填充
        void Padding(const string& str);
        // MD5压缩函数 H_MD5
        void H_MD5(u_char X[64]);
        // 输出MD5加密之后的128bit串的16进制表示
        void HexOutput();
        // 析构函数
        ~MD5() { delete padding_message; }
    private:
        u_int CV[4];
        u_char* padding_message;
        long block_size;
};


#endif
