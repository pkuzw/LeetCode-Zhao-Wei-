//
//  Lexicographical Numbers.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/23/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Lexicographical Numbers
///@author  Wei Zhao
///@date    2016.09.23
///@version 1.0

/*
 Given an integer n, return 1 - n in lexicographical order.
 
 For example, given 13, return: [1,10,11,12,13,2,3,4,5,6,7,8,9].
 
 Please optimize your algorithm to use less time and space. The input size may be as large as 5,000,000.
 
 */

#include <vector>
#include <algorithm>
#include <cmath>
#include <stdio.h>

using namespace std;

class Solution {
public:
    ///@brief   resort the number from 1 to n in the order of lexicograhpy
    ///@param   n   number of n
    ///@return  the lexicographical order
    ///@note    1. Iteration
    //          2. https://discuss.leetcode.com/topic/55131/ac-240ms-c-solution
    vector<int> lexicalOrder(int n) {
        vector<int> rslt(n);
        int cur = 1;
        
        for (int i = 0; i < n; i++) {
            rslt[i] = cur;
            if (cur * 10 <= n) {
                cur *= 10;
            }
            else {
                if (cur >= n)   cur /= 10;
                cur++;
                while (cur % 10 == 0)   cur /= 10;
            }
        }
        return rslt;
    }
};

int main() {
    int n = 363;
    Solution slt;
    vector<int> rslt = slt.lexicalOrder(n);
    return 0;
}
























