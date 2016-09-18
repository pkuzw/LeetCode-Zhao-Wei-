//
//  Guess Number Higher or Lower II.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/17/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Guess Number Higher or Lower II
///@author  Wei Zhao
///@date    2016.09.17
///@version 1.0

/*
 We are playing the Guess Game. The game is as follows:
 
 I pick a number from 1 to n. You have to guess which number I picked.
 
 Every time you guess wrong, I'll tell you whether the number I picked is higher or lower.
 
 However, when you guess a particular number x, and you guess wrong, you pay $x. You win the game when you guess the number I picked.
 
 Example:
 
 n = 10, I pick 8.
 
 First round:  You guess 5, I tell you that it's higher. You pay $5.
 Second round: You guess 7, I tell you that it's higher. You pay $7.
 Third round:  You guess 9, I tell you that it's lower. You pay $9.
 
 Game over. 8 is the number I picked.
 
 You end up paying $5 + $7 + $9 = $21.
 Given a particular n ≥ 1, find out how much money you need to have to guarantee a win.
 */

#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    ///@brief   caculate the money we need to ganrantee the winning
    ///@param   n   the upper bound of arrays
    ///@return  the money we need to win
    ///@note    1. Wrong Answer.
    //          2. It couldn't be done by naive binary search. For instance, if n = 5, as a naive binary search, we pick {3, 4} in order as the worst case, however, we could actually pick 4 at first, and if higher, 5 is the number. Otherwise it's between 1 to 3. Then we choose 2. So the total expense is 4 + 2 = 6, not $7.
    int getMoneyAmount(int n) {
        int rslt = 0;
        int left = 1, right = n;
        int mid = left + (right - left) / 2;
        while (mid != n) {
            rslt += mid;
            left = mid + 1;
            mid = left + (right - left) / 2;
        }
        return rslt;
    }
};

int main() {
    Solution slt;
    int rslt = 0;
    int n = 5;
    rslt = slt.getMoneyAmount(n);
    return 0;
}
