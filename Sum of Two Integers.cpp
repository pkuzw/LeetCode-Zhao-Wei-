//
//  Sum of Two Integers.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 16/9/6.
//  Copyright © 2016年 Zhao Wei. All rights reserved.
//

///@brief   Sum of Two Integers
///@author  zhao wei
///@date    2016.09.06
///@version 1.0

#include <vector>
#include <cmath>
using namespace std;

class Solution {
public:
    ///@brief   计算两个整型变量的和，在计算过程中不可以使用'+', '-'算符
    ///@param   a   加数a
    ///@param   b   加数b
    ///@return  返回两个加数的和
    ///@note    1. 通过位操作来实现两个加数的和
    ///         2. 1 ^ 1 = 0, 1 ^ 0 = 1, 0 ^ 0 = 0
    ///         3. 在使用异或操作之外，通过每一位的进位标志来判断是否需要进位
    ///         4. 时间复杂度为O(n)，空间复杂度为O(n)，其中n为整型变量的二进制长度
    int getSum(int a, int b) {
        int rslt = 0;
        bool isSum = true;
        int sign = 1;
        if (a > 0 && b > 0) {
            sign = 1;
            isSum = true;
        }
        else if (a < 0 && b < 0) {
            sign = -1;
            isSum = true;
        }
        else if (a == 0)    return b;
        else if (b == 0)    return a;
        else {
            isSum = false;
            if (a < 0 && b > 0) {
                if (-a > b) sign = -1;
                else    sign = 1;
            }
            else if (a > 0 && b < 0) {
                if (a >= -b) sign = 1;
                else    sign = -1;
            }
        }
        return rslt;
    }
};

int main() {
    
    return 0;
}