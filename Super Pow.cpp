//
//  Super Pow.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/16/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Super Pow
///@author  zhao wei
///@date    2016.09.16
///@version 1.0

#include <vector>
using namespace std;

class Solution {
public:
    ///@brief   caculate the result of a ^ b, b is stored as the vector, could be very large.
    ///@param   a   base number
    ///@param   b   index number
    ///@return  (a ^ b) mod 1337
    ///@note    1. A math problem
    ///         2. As we know, (a * b) mod k = (a mod k) * (b mod k) mod k
    ///         3. So, we only need to process vector b digit by digit.
    ///         4. For example, a^123 mod k = (a^120 mod k) * (a^3 mod k) mod k = ((a^12)^10 mod k) * (a^3 mod k) mod k
    //                                      = (((a^12 mod k) ^ 10) mod k) * (a^3 mod k) mod k
    //                                      = (((((a^10 mod k) * (a^2 mod k)) ^ 10) mod k) * (a^3 mod k) mod k
    //                                      = ((((((a mod k) ^ 10) mod k) * (a^2 mod k)) ^ 10) mod k) * (a^3 mod k) mod k
    //          5. the time complexity is O(n), and the space complexity is O(n).
    int superPow(int a, vector<int>& b) {
        if (b.empty())  return 1;
        const int k = 1337;
        int last_digit = b.back();
        b.pop_back();
        return commPow(superPow(a, b), 10) * commPow(a, last_digit) % k;
    }
    
    ///@brief   The common power function. The index is no more than 9.
    ///@param   a   base number
    ///@param   b   index number
    ///@return  a ^ b
    int commPow(int a, int b) {
        const int k = 1337;
        a %= k;
        int rslt = 1;
        for (int i = 0; i != b; i++) {
            rslt *= a;
            rslt %= k;
        }
        return rslt;
    }
};

int main() {
    vector<int> b;
    b.push_back(1);
    b.push_back(0);
//    b.push_back(3);
    
    int rslt = 0;
    Solution slt;
    rslt = slt.superPow(2, b);
    return 0;
}
