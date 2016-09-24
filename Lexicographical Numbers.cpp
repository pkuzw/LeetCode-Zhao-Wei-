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
    ///@note    1. at first, find the largest 10^k which is no more than n
    //          2. then insert the numbers start with 1, 2, ..., 9 in order.
    vector<int> lexicalOrder(int n) {
        int bound = n;
        int div = 1;
        int bcnt = 1;
        vector<int> rslt;
        while (n /= div) {
            div *= 10;
            bcnt++;
        }
        div /= 10;
        for (int i = 1; i <= 9 && i <= bound; i++) {
            for (int j = 1; j <= bcnt; j++) {
                int a = 1;
                for (int k = 0; k < j - 1; k++) {
                    a *= 10;
                }
                for (int l = i * a; l < (i + 1) * a && l <= bound; l++) {
                    rslt.push_back(l);
                }
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
























