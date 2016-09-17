//
//  Guess Number Higher or Lower.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/16/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file Guess Number Higher or Lower
///@author  zhao wei
///@date    2016.09.16
///@version 1.0

#include <vector>
#include <algorithm>

using namespace std;

// Forward declaration of guess API.
// @param num, your guess
// @return 1 if the test number is lower, -1 if the test number is higher, otherwise return 0
int guess(int num);

class Solution {
public:
    ///@brief   guess the number given between 1 to n
    ///@param   n   the upper bound of number
    ///@return  the given number
    ///@note    1. binary search
    //          2. take advantage of binary search and the API mentioned in this problem, if the number is lower, then we could change the
    //          searching upper bound, if the number is higher, we could increase our search bottom.
    //          3. pay attention to the overflow of sum of two big integers.
    //          4. the time complexity is O(logn), and the time complexity is O(1)
    int guessNumber(int n) {
        int left = 1, right = n;
        int rslt = left + (right - left) / 2;
        int tmp = guess(rslt);
        while (tmp) {
            if (tmp == -1)   right = rslt - 1;
            else    left = rslt + 1;
            rslt = left + (right - left) / 2;
            tmp = guess(rslt);
        }
        return rslt;
    }
};

int main() {
    
    return 0;
}
