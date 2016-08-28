//
//  Water and Jug Problem.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 16/8/26.
//  Copyright © 2016年 Zhao Wei. All rights reserved.
//

///@file    Water and Jug Problem
///@author  zhaowei
///@date    2016.08.28
///@version 1.0

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    ///@brief   判断x和y容量的桶能否称量出z容量多的水
    ///@param   x, y, z 桶的容量
    ///@return  如果可以，返回true；否则返回false
    ///@note    1. 将此问题转换为代数问题；
    //          2. ax + by =? z，但是要满足如下条件：
    //          3. 如果x和y均为偶数，则z一定为偶数；
    //          4. z <= x + y. 其中a和b是整数；
    //          5. 如果x与y存在公约数，那么z必须要整除二者的最小公约数；
    //          6. 此外，需要对有0的情况进行额外处理。
    bool canMeasureWater(int x, int y, int z) {
        //  z不能够超过x与y之和
        if (z > x + y)  return false;
        //  如果x和y是偶数，则z一定是偶数
        if (x % 2 == 0 && y % 2 == 0 && z % 2 == 1) return false;
        //  判断x, y, z中有为0的情况
        if (x == 0) {
            if (y == 0) {
                if (z != 0) return false;
                else    return true;
            }
            if (z % y)  return false;
        }
        if (y == 0)
            if (z % x)  return false;
        //  如果x与y有最小公约数
        int cd = haveSameCommonDivisor(x, y);
        if (cd != -1 && z % cd) return false;
        return true;
    }
    
    ///@brief   找出a和b的最小公约数
    ///@param   a, b    输入参数
    ///@return  如果a和b存在最小公约数，返回之；否则返回-1
    int haveSameCommonDivisor(int a, int b) {
        if (a  > b) swap(a, b);
        for (int i = 2; i <= a; i++)
            if (a % i == 0 && b % i == 0)   return i;
        return -1;
    }
};

int main() {
    Solution slt;
    int x = 23, y = 46, z = 12;
    bool rslt = slt.canMeasureWater(x, y, z);
    return 0;
}