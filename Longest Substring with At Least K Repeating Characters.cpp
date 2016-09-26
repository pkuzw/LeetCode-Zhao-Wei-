//
//  Longest Substring with At Least K Repeating Characters.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/26/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Longest Substring with At Least K Repeating Characters
///@author  Wei Zhao
///@date    2016.09.26
///@version 1.0


/*
 Find the length of the longest substring T of a given string (consists of lowercase letters only) such that every character in T appears no less than k times.
 
 Example 1:
 
 Input:
 s = "aaabb", k = 3
 
 Output:
 3
 
 The longest substring is "aaa", as 'a' is repeated 3 times.
 Example 2:
 
 Input:
 s = "ababbc", k = 2
 
 Output:
 5
 
 The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
    public:
    ///@brief   find the longest substring in which the letters appear no less than k times
    ///@note    1. iteration
    //          2. use an array to record the appear times in the substring
    //          3. take advantage of bit operation to judge whether the letters qualify the conditions
    int longestSubstring(string s, int k) {
        int max_len = 0;
        
        int first = 0;
        while (first + k <= s.size()) {
            int count[26] = {0};
            int mask = 0;   //  the mask to judge the substring is legal or not
            
            int max_last = first;
            for (int last = first; last < s.size(); last++) {
                int i = s[last] - 'a';
                count[i]++;
                if (count[i] < k)   mask |= (1 << i);   //  mark the letter less than k as 1
                else    mask &= (~(1 << i));            // mark the letter no less than k as 0
                
                if (mask == 0) {
                    max_len = max(max_len, last - first + 1);
                    max_last = last;
                }
            }
            first = max_last + 1;
        }
        return max_len;
    }
};

int main() {
    string s = "ababbc";
    Solution slt;
    int k = 2;
    int rslt = slt.longestSubstring(s, k);
    return 0;
}






















