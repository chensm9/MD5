#include "MD5.h"

MD5::MD5(const string& str) {
    // 字符串填充
    Padding(str);
    // 初始化MD缓冲区
    initCV();
    // 进行MD5压缩
    for(int i = 0; i < block_size; i++) {
        H_MD5(padding_message+64*i);
    }
}


// 初始化MD缓冲区，也即向量IV，采用little-endian的存储结构
void MD5::initCV() {
    CV[0] = 0x67452301;
    CV[1] = 0xefcdab89;
    CV[2] = 0x98badcfe;
    CV[3] = 0x10325476;
}

// 对字符串进行扩充，得到一个长度位数为 K + P + 64 = 0 (mod 512) 的消息。
// 然后再进行分组，每个分组64个char（512字节）
void MD5::Padding(const string& str) {
    long length = str.length(), total_length = 0, zero_num;
    // 一个char为8个bit，所以512个bit为64个char
    if (length % 64 < 56) {
        zero_num = 56 - length%64 - 1;      // 第一个是从1开始的
        total_length = (length/64+1) * 64;
    } else {
        zero_num = 64 - length%64 + 56 - 1; // 第一个是从1开始的
        total_length = (length/64+2) * 64;   
    }

    padding_message = new u_char[total_length];
    memcpy(padding_message, str.c_str(), length);
    // 下一块是以1开头的
    padding_message[length] = 0b10000000;
    for (int i = 1; i <= zero_num; i++) {
        padding_message[i+length] = 0;
    }

    // 最后64位是长度，小端放
    long bit_length = length * 8;
    for (int j = 0; j < 8; j++) {
        padding_message[total_length - 1 - j] =  ((bit_length << 8*j) >> 56);  
    }
    block_size = total_length / 64;
}

// MD5 压缩，进行4轮循环
void MD5::H_MD5(u_char X[64]) {
    u_int a = CV[0], b = CV[1], c = CV[2], d = CV[3];
    RoundFunc ArrFunc = { F, G, H, I};  // 四轮循环使用到的轮函数
    for (int i = 0; i < 4; i ++) {    // 四轮循环
        for (int j = 0; j < 16; j++) {
            // a = b + ((a + g(b, c, d) + X[k] + T[i]) <<<s)
            int k = X_table[i][j];
            u_int t  = b + CycleMoveLeft(a + ArrFunc[i](b, c, d) + charToUint(X+k*4) + T[16*i+j], s[i][j]);
            // 缓冲区 (A, B, C, D) 作循环轮换
            a = d; d = c; c = b; b = t;
        }
    }
    CV[0] += a; CV[1] += b; CV[2] += c; CV[3] += d;
}

// 输出MD5加密之后的128bit串的16进制表示
void MD5::HexOutput() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << hex <<  ((CV[i] << (3-j)*8) >> 24);   //逆序处理每个字节
        }
    }
    cout << endl;
}
