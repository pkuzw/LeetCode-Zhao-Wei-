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
///@version 1.1
///@version 1.2

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

class Solution_dont_understand {
public:
    /*@note 
     After first elimination, all the rest numbers are even numbers.
     Divide by 2, we get a continuous new sequence from 1 to n / 2.
     For this sequence we start from right to left as the first elimination.
     Then the original result should be two times the mirroring result of lastRemaining(n / 2).
     https://discuss.leetcode.com/topic/58042/c-1-line-solution-with-explanation/2
    */
    int lastRemaining(int n) {
        return n == 1 ? 1 : 2 * (1 + n / 2 - lastRemaining(n / 2));
    }
};

class Solution {
public:
    /*
     @note
     https://discuss.leetcode.com/topic/59293/java-easiest-solution-o-logn-with-explanation
     My idea is to update and record head in each turn. when the total number becomes 1, head is the only number left.
     
     When will head be updated?
     
     if we move from left
     if we move from right and the total remaining number % 2 == 1
     like 2 4 6 8 10, we move from 10, we will take out 10, 6 and 2, head is deleted and move to 4
     like 2 4 6 8 10 12, we move from 12, we will take out 12, 8, 4, head is still remaining 2
     then we find a rule to update our head.
     
     example:
     1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24
     
     Let us start with head = 1, left = true, step = 1 (times 2 each turn), remaining = n(24)
     
     we first move from left, we definitely need to move head to next position. (head = head + step)
     So after first loop we will have:
     1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 - > 2 4 6 8 10 12 14 16 18 20 22 24
     head = 2, left = false, step = 1 * 2 = 2, remaining = remaining / 2 = 12
     
     second loop, we move from right, in what situation we need to move head?
     only if the remaining % 2 == 1, in this case we have 12 % 2 == 0, we don't touch head.
     so after this second loop we will have:
     2 4 6 8 10 12 14 16 18 20 22 24 - > 2 6 10 14 18 22
     head = 2, left = true, step = 2 * 2 = 4, remaining = remaining / 2 = 6
     
     third loop, we move from left, move head to next position
     after third loop we will have:
     2 6 10 14 18 22 - > 6 14 22
     head = 6, left = false, step = 4 * 2 = 8, remaining = remaining / 2 = 3
     
     fourth loop, we move from right, NOTICE HERE:
     we have remaining(3) % 2 == 1, so we know we need to move head to next position
     after this loop, we will have
     6 14 22 - > 14
     head = 14, left = true, step = 8 * 2 = 16, remaining = remaining / 2 = 1
     
     while loop end, return head
     */
    int lastRemaining(int n) {
        int head = 1;
        int step = 1;
        int remain = n;
        bool left = true;
        while (remain != 1) {
            if (left || (!left && remain % 2 == 1)) {
                head += step;
            }
            remain /= 2;
            step *= 2;
            left = !left;
        }
        return head;
    }
};

class Solution_tle {
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
    int n = 10;
    int rslt = slt.lastRemaining(n);
    return 0;
}



































