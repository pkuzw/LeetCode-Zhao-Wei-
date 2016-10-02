//
//  Longest Palindrome.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 10/1/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Longest Palindrome
///@author  Wei Zhao
///@date    10.01.2016
///@version 1.0

/*
 Given a string which consists of lowercase or uppercase letters, find the length of the longest palindromes that can be built with those letters.
 
 This is case sensitive, for example "Aa" is not considered a palindrome here.
 
 Note:
 Assume the length of given string will not exceed 1,010.
 
 Example:
 
 Input:
 "abccccdd"
 
 Output:
 7
 
 Explanation:
 One longest palindrome that can be built is "dccaccd", whose length is 7.
 */
#include <stdio.h>
#include <string>
using namespace std;

class Solution {
public:
    ///@note    hash table
    //          1. use an array to store all the letters' appearance time. For the even times, they should be added into the result; for the odd times, it should be minus 1 then add into the result. But for the maximum odd time, we should add it into the result originally.
    int longestPalindrome(string s) {
        int ht[52] = {0};
        for (int i = 0; i < s.length(); i++) {
            if (s[i] <= 'z' && s[i] >= 'a')
                ht[26 + s[i] - 'a']++;
            else
                ht[s[i] - 'A']++;
        }
        int rslt = 0;
        int existOdd = 0;
        for (int i = 0; i < 52; i++) {
            if (ht[i] % 2) {
                rslt += ht[i] - 1;
                existOdd = 1;
            }
            else
                rslt += ht[i];
        }
        return rslt + existOdd;
    }
};

int main() {
    string s = "abccADFSDVaerasdfSDFWRFSSDFasdhaecxzzDFSawebdf";
    Solution slt;
    int rslt = slt.longestPalindrome(s);
    return 0;
}
