//
//  Decode String.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/25/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Decode String
///@author  Wei Zhao
///@date    2016.09.25
///@version 1.0

/*
 Given an encoded string, return it's decoded string.
 
 The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.
 
 You may assume that the input string is always valid; No extra white spaces, square brackets are well-formed, etc.
 
 Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there won't be input like 3a or 2[4].
 
 Examples:
 
 s = "3[a]2[bc]", return "aaabcbc".
 s = "3[a2[c]]", return "accaccacc".
 s = "2[abc]3[cd]ef", return "abcabccdcdcdef".
 */

#include <stack>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    ///@brief   decode string
    ///@note    1. stack
    ///         2. use two stacks, one is used to store the number, the other one stores the string in the bracket
    //          3. when meet the left bracket, just pass by; when meet the right bracket, pop the string stack and the number stack and calculate the new string stack top
    //          4. if in front of the characters without number and brackets, just add them to the current substring.
    string decodeString(string s) {
        string rslt = "";
        if (s.empty())  return rslt;
        stack<int> stk_num;
        stack<string> stk_str;
  
        int left_bracket_cnt = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '[')
                left_bracket_cnt++;
            
            else if (s[i] <= 'z' && s[i] >= 'a') {
                int j = i;
                while (s[j] <= 'z' && s[j] >= 'a') {
                    j++;
                }
                string sub_string = s.substr(i, j - i);
                i = j - 1;
                if (left_bracket_cnt) {
                    stk_str.push(sub_string);
                }
                else {
                    rslt += sub_string;
                }
            }
            
            else if (s[i] <= '9' && s[i] >= '0') {
                int j = i;
                while (s[j] <= '9' && s[j] >= '0') {
                    j++;
                }
                string sub_str = s.substr(i, j - i);
                i = j - 1;  // update index i
                int rep_time = stoi(sub_str);
                stk_num.push(rep_time);
            }
            
            else if (s[i] == ']') {
                left_bracket_cnt--;
                string str_tmp = stk_str.top(); stk_str.pop();
                int rep_time = stk_num.top(); stk_num.pop();
                string new_top = "";
                for (int j = 0; j < rep_time; j++) {
                    new_top += str_tmp;
                }
                if (!stk_str.empty()) {
                    new_top = stk_str.top() + new_top;
                    stk_str.pop();
                }
                
                //  add the string at the same layer to new_top
                int j = i + 1;
                while (s[j] <= 'z' && s[j] >= 'a') {
                    j++;
                }
                str_tmp = s.substr(i + 1, j - i - 1);
                new_top += str_tmp;
                stk_str.push(new_top);
                i = j - 1;  // update i
                
                if (!left_bracket_cnt) {
                    rslt += stk_str.top();stk_str.pop();
                }
            }
        }
        return rslt;
    }
};

int main() {
    Solution slt;
    string s = "y2[a2[c2[e2[f]d]u]v]z";
    string rslt = slt.decodeString(s);
    return 0;
}





























