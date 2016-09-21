//
//  Nth Digit.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/20/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Nth Digit
///@author  Wei Zhao
///@date    2016.09.20
///@version 1.0

/*
 Find the nth digit of the infinite integer sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...
 
 Note:
 n is positive and will fit within the range of a 32-bit signed integer (n < 231).
 
 Example 1:
 
 Input:
 3
 
 Output:
 3
 Example 2:
 
 Input:
 11
 
 Output:
 0
 
 Explanation:
 The 11th digit of the sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... is a 0, which is part of the number 10.
 Show Company Tags
 Show Tags
 */

#include <string>
#include <cstdlib>

using namespace std;

class Solution {
public:
    ///@brief   find the Nth digit of the natural numbers sequence
    ///@param   n   the Nth digit
    ///@return  the digit
    ///@note    1. confirm the length of the number
    //          2. find the actual number
    //          3. find the digit
    //          4. https://discuss.leetcode.com/topic/59314/java-solution
    int findNthDigit(int n) {
        long long lln = n;  // int type will overflow.
        long long count = 9;
        long long start = 1;
        int len = 1;
        while (lln > len * count) {
            lln -= len * count;
            start *= 10;
            count *= 10;
            len++;
        }
        start += (lln - 1) / len; //  because the array index start with 0
        string s = to_string(start);
        int rslt = s[(lln - 1) % len] - '0';
        return rslt;
    }
};

int main() {
    int n = 1000000000;
    Solution slt;
    int rslt = slt.findNthDigit(n);
    return 0;
}




































