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
        if (a > 0 && b > 0) rslt = sum(a, b);
        else if (a < 0 && b < 0)    rslt = -1 * sum(-a, -b);
        else if (a == 0)    return b;
        else if (b == 0)    return a;
        else {
            if (a < 0 && b > 0) {
                if (-a > b) rslt = -1 * difference(-a, b);
                else    rslt = difference(b, -a);
            }
            else if (a > 0 && b < 0) {
                if (a >= -b) rslt = difference(a, -b);
                else    rslt = -1 * difference(-b, a);
            }
        }
        return rslt;
    }
    
    ///@brief   计算两个正整数的和
    ///@param   a, b    两个加数
    ///@return  返回a + b
    int sum(int a, int b) {
        int rslt = 0;
        int carry = 0;
        for (int i = 0; i < 31; i++) {
            int x = a & 1;
            a >>= 1;
            int y = b & 1;
            b >>= 1;
            int z = x ^ y;
            z ^= carry;
            z <<= 30;
            rslt = (rslt >> 1) | z;
            z >>= 30;
            carry = z == 0 && x == 1 ? 1 : 0;
        }
        return rslt;
    }
    
    ///@brief   计算两个数的差
    ///@param   a   被减数
    ///@param   b   减数
    ///@return  返回a - b的差
    int difference(int a, int b) {
        int rslt = 0;
        int carry = 0;
        for (int i = 0; i < 31; i++) {
            int x = a & 1;
            a >>= 1;
            x ^= carry;
            if (x == 1 && carry == 1)   carry = 1;
            int y = b & 1;
            b >>= 1;
            int z = x ^ y;
            z <<= 30;
            rslt = (rslt >> 1) | z;
            z >>= 30;
            if (z == 1 && x == 0)   carry = 1;
        }
        return rslt;
    }
};

int main() {
    int a = 2, b = -1;
    int rslt = 0;
    Solution slt;
//    
    rslt = slt.getSum(a, b);
    return 0;
}