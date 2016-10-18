//
//  Longest Repeating Character Replacement.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 10/17/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Longest Repeating Character Replacement
///@author  Wei Zhao
///@date    Oct. 17, 2016
///@version 1.0

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

class Solution {
public:
    ///@note    https://discuss.leetcode.com/topic/63416/sliding-window-similar-to-finding-longest-substring-with-k-distinct-characters
    int characterReplacement(string s, int k) {
        vector<int> counts(26, 0);
        int start = 0;
        int maxCharCount = 0;
        int n = s.length();
        int result = 0;
        for(int end = 0; end < n; end++){
            counts[s[end]-'A']++;
            if(maxCharCount < counts[s[end]-'A']){
                maxCharCount = counts[s[end]-'A'];
            }
            while(end-start-maxCharCount+1 > k){
                counts[s[start]-'A']--;
                start++;
                for(int i = 0; i < 26; i++){
                    if(maxCharCount < counts[i]){
                        maxCharCount = counts[i];
                    }
                }
            }
            result = max(result, end-start+1);
        }
        return result;
    }
};

int main() {

}

/*
 Given a string that consists of only uppercase English letters, you can replace any letter in the string with another letter at most k times. Find the length of a longest substring containing all repeating letters you can get after performing the above operations.
 
 Note:
 Both the string's length and k will not exceed 104.
 
 Example 1:
 
 Input:
 s = "ABAB", k = 2
 
 Output:
 4
 
 Explanation:
 Replace the two 'A's with two 'B's or vice versa.
 Example 2:
 
 Input:
 s = "AABABBA", k = 1
 
 Output:
 4
 
 Explanation:
 Replace the one 'A' in the middle with 'B' and form "AABBBBA".
 The substring "BBBB" has the longest repeating letters, which is 4.
 */
