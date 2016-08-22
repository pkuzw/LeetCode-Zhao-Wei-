//
//  Count Numbers with Unique Digits.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 16/8/22.
//  Copyright © 2016年 Zhao Wei. All rights reserved.
//

///@file    Count Numbers with Unique Digits
///@author  zhaowei
///@date    2016.08.22
///@version 1.0

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    ///@brief   计算给定位数的每位不重复的整型数字数目
    ///@param   n   位数
    ///@return  返回n位的每位皆不同的整数数目
    ///@note    1. 排列组合问题;
    //          2. 首先，如果只有一位，则是10种;
    //          3. 如果位数大于1，则第一位不能为0，那么第一位有9种情况，第二位之后的位数可以含0，有9, 8, 7, ...种情况;
    //          4. 将所有小于等于n的情况累加即可;
    //          5. 时间复杂度为O(n^2)，空间复杂度为O(1)。
    int countNumbersWithUniqueDigits(int n) {
        if (!n) return 1;
        int rslt = 0;
        for (int i = 1; i <= n; i++)
            rslt += helper(i);
        return rslt;
    }
    
    ///@brief   计算n位正整数，其中每一位都不相同的数字数目
    ///@param   n   位数
    ///@return  返回满足条件的正数数目
    int helper(int n) {
        int cnt = 1;
        if (n == 0) return cnt;
        else if (n == 1)    cnt = 10;
        else {
            int tmp = 9;
            cnt = tmp;
            for (int i = 1; i < n; i++) {
                cnt *= 10 - i;
            }
        }
        return cnt;
    }
};

int main() {
    Solution slt;
    int rslt = slt.countNumbersWithUniqueDigits(0);
    return 0;
}