//
//  Integer Replacement.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/18/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Integer Replacement
///@author  Wei Zhao
///@date    2016.09.18
///@version 1.0

#include <vector>
#include <cmath>
#include <unordered_map>

using namespace std;

/*
 Given a positive integer n and you can do operations as follow:
 
 If n is even, replace n with n/2.
 If n is odd, you can replace n with either n + 1 or n - 1.
 What is the minimum number of replacements needed for n to become 1?
 
 Example 1:
 
 Input:
 8
 
 Output:
 3
 
 Explanation:
 8 -> 4 -> 2 -> 1
 Example 2:
 
 Input:
 7
 
 Output:
 4
 
 Explanation:
 7 -> 8 -> 4 -> 2 -> 1
 or
 7 -> 6 -> 3 -> 2 -> 1
 */

class Solution {
private:
    unordered_map<int, int> ht;
public:
    ///@brief   Caculate the minimum replacements.
    ///@param   n   the number
    ///@return  minimum replacements for down to 1
    ///@note    recurrence with hash table
        int integerReplacement(int n) {
        if (n <= 1)  return 0;
        if (ht[n] == 0) {
            if (n % 2) {
                ht[n] = 2 + min(integerReplacement(n/2), integerReplacement(n/2 + 1));
            }
            else {
                ht[n] = 1 + integerReplacement(n/2);
            }
        }
        return ht[n];
    }
};

class Solution_dp {
public:
    ///@note    1. dynamic programming
    //          2. if we use dp[i] i > 0 presents the min replacements from i to 1. Then
    //          3. dp[1] = 0;
    //          4. dp[i] = dp[i / 2] + 1, if i is even;
    //          5. dp[i] = min(dp[i+1], dp[i-1]) + 1, if i is odd. At the same time, this formula could be transformed into dp[i] = min(dp[i/2], dp[i/2+1]) + 2. So it could be calculated from bottom to top.
    //          6. time complexity is O(n), and the space complexity is O(n).
    int integerReplacement(int n) {
        vector<int> dp(n+1, 0);
        dp[1] = 0;
        for (int i = 2; i < n + 1; i++) {
            if (i % 2) {
                dp[i] = 2 + min(dp[i/2], dp[i/2 + 1]);
            }
            else {
                dp[i] = 1 + dp[i/2];
            }
        }
        return dp[n];
    }
};



int main() {
    int rslt = 0;
    int n = 5;
    Solution slt;
    rslt = slt.integerReplacement(n);
    Solution_dp slt_dp;
    int rslt_dp = slt_dp.integerReplacement(n);
    return 0;
}





























