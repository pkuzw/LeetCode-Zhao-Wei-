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
    //          2. ax + by =? z，但是要满足如下两个条件：
    //          3. 如果x和y均为偶数，则z一定为偶数；
    //          4. z <= x + y. 其中a和b是整数。
    bool canMeasureWater(int x, int y, int z) {
        if (z > x + y)  return false;
        if (x % 2 == 0 && y % 2 == 0 && z % 2 == 1) return false;
        int a = 0, b = 0;
        
        int i = 0;
        while (1) {
            a = i;
            if ((z - a * x) % y  == 0 || (z + a * x) % y == 0)  return true;
            i++;
            if (a * x + b * y)
        }
        
        return false;
    }
};

int main() {
    return 0;
}