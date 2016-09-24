//
//  Elimination Game.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/23/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Elimination Game
///@author  Wei Zhao
///@date    2016.09.23
///@version 1.0

/*
 There is a list of sorted integers from 1 to n. Starting from left to right, remove the first number and every other number afterward until you reach the end of the list.
 
 Repeat the previous step again, but this time from right to left, remove the right most number and every other number from the remaining numbers.
 
 We keep repeating the steps again, alternating left to right and right to left, until a single number remains.
 
 Find the last number that remains starting with a list of length n.
 
 Example:
 
 Input:
 n = 9,
 1 2 3 4 5 6 7 8 9
 2 4 6 8
 2 6
 6
 
 Output:
 6
 */

#include <vector>

using namespace std;

class Solution {
public:
    ///@brief   find the last number in the array from 1 to n
    ///@param   n   the end of the array
    ///@return  the last remaining number
    ///@note    1. enumeration
    //          2. the interval will be double after one elimination
    //          3. the time complexity is sum(n / 2^k), k >= 1, the space complexity is O(n). tle
    int lastRemaining(int n) {
        vector<int> arr;
        for (int i = 0; i < n; i++) arr.push_back(i + 1);
        
        int eliminated_num = 0;
        int k = 2;
        while (1) {
            int left_start = 0;
            while (arr[left_start] == -1)   left_start++;
            for (int i = left_start; i < n; i += k) {
                arr[i] = -1;
                eliminated_num++;
            }
            k *= 2;
            if (eliminated_num == n - 1)    break;
            
            int right_start = n - 1;
            while (arr[right_start] == -1)  right_start--;
            for (int i = right_start; i >= 0; i -= k) {
                arr[i] = -1;
                eliminated_num++;
            }
            k *= 2;
            if (eliminated_num == n - 1)    break;
        }
        for (int i = 0; i < n; i++)
            if (arr[i] != -1)
                return arr[i];
        
        return 0;
    }
};

int main() {
    Solution slt;
    int n = INT_MAX - 10;
    int rslt = slt.lastRemaining(n);
    return 0;
}



































