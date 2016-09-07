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

class Solution_v1 {
public:
    ///@brief   计算两个整型变量的和，在计算过程中不可以使用'+', '-'算符
    ///@param   a   加数a
    ///@param   b   加数b
    ///@return  返回两个加数的和
    ///@note    1. 通过位操作来实现两个加数的和
    ///         2. 1 ^ 1 = 0, 1 ^ 0 = 1, 0 ^ 0 = 0
    ///         3. 在使用异或操作之外，通过每一位的进位标志来判断是否需要进位
    ///         4. 时间复杂度为O(n)，空间复杂度为O(n)，其中n为整型变量的二进制长度
    ///         5. 注意，在此题中结果越上界(> INT_MAX)应该返回INT_MIN + 越过的值，如果越下界(< INT_MIN)应该返回INT_MAX - 越过的值
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
            if ((x == 1 && y == 1 && carry == 1) ||
                (x == 1 && y == 1 && carry == 0) ||
                (x == 1 && y == 0 && carry == 1) ||
                (x == 0 && y == 1 && carry == 1))
                carry = 1;
            else    carry = 0;
        }
        return rslt;
    }
    
    ///@brief   计算两个数的差
    ///@param   a   被减数
    ///@param   b   减数
    ///@return  返回a - b的差
    int difference(int a, int b) {
        int rslt = 0;
        for (int i = 0; i < 31; i++) {
            int x = a & 1;
            a >>= 1;
            int y = b & 1;
            b >>= 1;
            int z = x ^ y;
            z <<= 30;
            rslt = (rslt >> 1) | z;
            z >>= 30;
            if (z == 1 && x == 0) {
                int a_ = a;
                int c = a_ & 1;
                int count = 0;
                while (c == 0) {
                    count++;
                    a_ >>= 1;
                    c = a_ & 1;
                }
                int d = 0;
                for (int j = 0; j != 31 - count; j++) {
                    d |= 1;
                    d <<= 1;
                }
                d <<= 1;
                for (int j = 0; j != count; j++) {
                    d <<= 1;
                    d |= 1;
                }
                a &= d;
                d = 0;
                for (int j = 0; j != count; j++) {
                    d <<= 1;
                    d |= 1;
                }
                a |= d;
            }
        }
        return rslt;
    }
};

class Solution {
public:
    ///@brief   通过位操作计算两个数的加减法
    ///@param   a, b    进行加减法的两个整型变量
    ///@return  返回两个数加减法操作后的值
    ///@note    1. 位操作
    ///         2. 先处理其中一个数为0的情形；
    ///         3. 然后计算最低位的两位数的和，通过XOR运算；
    ///         4. 然后通过与运算计算出进位的情况；
    ///         5. 最后递归调用getSum函数本身，来处理进位和原本的两位之和。
    int getSum(int a, int b) {
        if (b == 0) return a;   //  如果进位为0，直接返回原来的加法之和
        int sum = 0, carry = 0;
        sum = a ^ b;    //  处理原来的两数的加法
        carry = (a & b) << 1;   //  处理进位
        return getSum(sum, carry);  //  递归处理每一位
    }
};

int main() {
    int a = -14, b = 16;
    int rslt = 0;
    Solution slt;
//    
    rslt = slt.getSum(a, b);
    return 0;
}