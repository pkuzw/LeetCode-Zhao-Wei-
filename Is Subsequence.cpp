//
//  Is Subsequence.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/25/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Is Subsequence
///@author  Wei Zhao
///@date    2016.09.25
///@version 1.0

/*
 Given a string s and a string t, check if s is subsequence of t.
 
 You may assume that there is only lower case English letters in both s and t. t is potentially a very long (length ~= 500,000) string, and s is a short string (<=100).
 
 A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ace" is a subsequence of "abcde" while "aec" is not).
 
 Example 1:
 s = "abc", t = "ahbgdc"
 
 Return true.
 
 Example 2:
 s = "axc", t = "ahbgdc"
 
 Return false.
 
 Follow up:
 If there are lots of incoming S, say S1, S2, ... , Sk where k >= 1B, and you want to check one by one to see if T has its subsequence. In this scenario, how would you change your code?
 */

#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class Solution {
    public:
    ///@brief   judge whether string s is a substring of string t
    ///@note    1. iteration
    //          2. use an index to record the start of t currently, and eumerate every letter in the t.
    //          3. if there is a letter matches the char in s, then update the index in t and move the char to the next one in string s
    bool isSubsequence(string s, string t) {
        if (s.empty())  return true;
        if (!s.empty() && t.empty())    return false;
        
        int ti = 0;
        int i = 0, j = 0;
        for (i = 0; i < s.size(); i++) {
            for (j = ti; j < t.size(); j++) {
                if (s[i] == t[j]) {
                    ti = j + 1;
                    break;
                }
            }
            if (j == t.size())  return false;
        }
        return true;
    }
};

int main() {
    string s = "abc", t = "ahbdgc";
    string s1 = "axc", t1 = "xaaaacaxc";
    Solution slt;
    bool rslt = slt.isSubsequence(s1, t1);
    return 0;
}




































