#include "MD5.h"
#include <iostream>
#include <cmath>

using namespace std;

int main() {
    string str = "";
    cout << "请输入要进行加密的字符串：" << endl;
    cin >> str;
    MD5 md5(str);
    cout << "进行MD5加密之后的十六进制串为：" << endl;
    md5.HexOutput();
}