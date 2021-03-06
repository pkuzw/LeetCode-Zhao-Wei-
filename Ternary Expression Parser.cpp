//
//  Ternary Expression Parser.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 10/22/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Ternary Expression Parser
///@author  Wei Zhao
///@date    Oct. 22, 2016
///@version 1.0
#include <string>
#include <vector>
#include <stdio.h>
#include <stack>
using namespace std;

class Solution {
public:
    ///@note    1. string::find_last_of(string) returns the last character's place in the string
    string parseTernary(string expression) {
        unsigned pos = 0;
        while (expression.length() > 5) {
            pos = expression.find_last_of('?');
            string tmp = expression.substr(0, pos-1);
            if (expression[pos-1] == 'T')   tmp += expression[pos+1];
            else    tmp += expression[pos+3];
            tmp += expression.substr(pos+4);
            expression = tmp;
        }
        return expression[0] == 'T' ? expression.substr(2, 1) : expression.substr(4, 1);
    }
};

int main() {
    Solution slt;
    string expression = "F?1:T?4:5";
    string rslt = slt.parseTernary(expression);
    return 0;
}

/*
 Given a string representing arbitrarily nested ternary expressions, calculate the result of the expression. You can always assume that the given expression is valid and only consists of digits 0-9, ?, :, T and F (T and F represent True and False respectively).
 
 Note:
 
 The length of the given string is ≤ 10000.
 Each number will contain only one digit.
 The conditional expressions group right-to-left (as usual in most languages).
 The condition will always be either T or F. That is, the condition will never be a digit.
 The result of the expression will always evaluate to either a digit 0-9, T or F.
 Example 1:
 
 Input: "T?2:3"
 
 Output: "2"
 
 Explanation: If true, then result is 2; otherwise result is 3.
 Example 2:
 
 Input: "F?1:T?4:5"
 
 Output: "4"
 
 Explanation: The conditional expressions group right-to-left. Using parenthesis, it is read/evaluated as:
 
 "(F ? 1 : (T ? 4 : 5))"                   "(F ? 1 : (T ? 4 : 5))"
 -> "(F ? 1 : 4)"                 or       -> "(T ? 4 : 5)"
 -> "4"                                    -> "4"
 Example 3:
 
 Input: "T?T?F:5:3"
 
 Output: "F"
 
 Explanation: The conditional expressions group right-to-left. Using parenthesis, it is read/evaluated as:
 
 "(T ? (T ? F : 5) : 3)"                   "(T ? (T ? F : 5) : 3)"
 -> "(T ? F : 3)"                 or       -> "(T ? F : 5)"
 -> "F"                                    -> "F"
*/
