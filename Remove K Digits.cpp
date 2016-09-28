//
//  Remove K Digits.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/27/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Remove K Digits
///@author  Wei Zhao
///@date    2016.09.27
///@version 1.0

/*
 Given a non-negative integer num represented as a string, remove k digits from the number so that the new number is the smallest possible.
 
 Note:
 The length of num is less than 10002 and will be ≥ k.
 The given num does not contain any leading zero.
 Example 1:
 
 Input: num = "1432219", k = 3
 Output: "1219"
 Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
 Example 2:
 
 Input: num = "10200", k = 1
 Output: "200"
 Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
 Example 3:
 
 Input: num = "10", k = 2
 Output: "0"
 Explanation: Remove all the digits from the number and it is left with nothing which is 0.
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
    public:
    ///@brief   given a string assembled with numbers, removing k digit makes it became the smallest number in those digits
    ///@note    1. find the descending interval from left to right. If there exists a interval in which the digits are sorted decendantly, we could just remove the first digit of the interval;
    //          2. if there exists a substring whose length is no longer than k and behind it following a sequential zeros, and at the same time it is at the head of the string ,we should remove it first, because these zeros could make the string became more small with the extra zero with limited digits
    string removeKdigits(string num, int k) {
        int len = num.length();
        if (k >= len)   return "0";
        
        int  nz = countLeadingNonZero(num); // the count for the non-zero digits
        while (nz <= k) {
            k -= nz;
            int z = nz; //  the sequential zero digits
            while (z < len && num[z] == '0')   z++;
            
            if (z == len)   return "0";
            
            num = num.substr(z, len - z);
            len = num.length();
            nz = countLeadingNonZero(num);
        }
        
        while (k > 0) {
            for (int i = 0; i < num.length() - 1; i++) {
                if (num[i] > num[i + 1]) {
                    num.erase(i, 1);
                    break;
                }
                //  if the digits are ordered in non-descending order, we just remove the last digit
                if (i == num.length() - 2) {
                    if (num[i] <= num[i + 1])
                        num.pop_back();
                }
            }
            k--;
        }
        return num;
    }
    
    ///@brief   count the leading non-zero digits before the first zero digit in string s
    int countLeadingNonZero(string s) {
        if (s.empty())  return 0;
        int cnt = 0;
        while (cnt < s.length() && s[cnt] != '0') {
            cnt++;
        }
        return cnt;
    }
};

int main() {
    string num = "10010010011222";
    Solution slt;
    string rslt = slt.removeKdigits(num, 8);
    return 0;
}


























