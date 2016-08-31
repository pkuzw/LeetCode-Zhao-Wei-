//
//  Valid Perfect Square.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 16/8/31.
//  Copyright © 2016年 Zhao Wei. All rights reserved.
//

///@file    Valid Perfect Square
///@author  zhaowei
///@date    2016.08.31
///@version 1.0


#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    ///@brief   判断一个正整数是否是平方数
    ///@param   num 正整数
    ///@return  如果num是平方数，则返回true，否则返回false
    ///@note    1. 二分查找
    //          2. 在区间[1, num]中查找其平方等于num的整数，如果存在则返回true；否则在最后检查退出二分查找时的边界的平方是否为num，如果不是则返回false
    //          3. 时间复杂度为O(logn)，其中n为num的大小
    bool isPerfectSquare(int num) {
        if (num == 0)   return false;
        if (num == 1)   return true;
        long long l = 1, r = num;
        
        while (l < r) {
            long long mid = (l + r) / 2;
            if (mid * mid == num)   return true;
            else if (mid * mid < num)   l = mid + 1;
            else    r = mid - 1;
        }
        return l * l == num;
    }
};

int main() {
    int num = 5;
    Solution slt;
    bool rslt = slt.isPerfectSquare(num);
    return 0;
}