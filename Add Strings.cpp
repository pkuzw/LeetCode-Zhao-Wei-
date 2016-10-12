//
//  Add Strings.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 10/12/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Add Strings
///@author  Wei Zhao
///@date    Oct. 12 2016
///@version 1.0

/*
 Given two non-negative numbers num1 and num2 represented as string, return the sum of num1 and num2.
 
 Note:
 
 The length of both num1 and num2 is < 5100.
 Both num1 and num2 contains only digits 0-9.
 Both num1 and num2 does not contain any leading zero.
 You must not use any built-in BigInteger library or convert the inputs to integer directly.
 
 */

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    string addStrings(string num1, string num2) {
        int len_short = num1.size() < num2.size() ? num1.length() : num2.length();
        
        bool carry = false;
        string rslt;
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        for (int i = 0; i < len_short; i++) {
            int a = num1[i] - '0';
            int b = num2[i] - '0';
            a = carry ? a + b + 1 : a + b;
            carry = a >= 10 ? true : false;
            if (a >= 10)    a -= 10;
            rslt += char('0' + a);
        }
        if (!carry) {
            if (num1.size() < num2.size())
                rslt += num2.substr(len_short, num2.length() - len_short);
            else
                rslt += num1.substr(len_short, num1.length() - len_short);
        }
        else {
            if (num1.size() < num2.size()) {
                num2 = num2.substr(len_short, num2.length() - len_short);
                for (int i = 0; i < num2.length(); i++) {
                    int a = num2[i] - '0';
                    a = carry ? a + 1 : a;
                    carry = a >= 10 ? true : false;
                    if (a >= 10) a -= 10;
                    num2[i] = '0' + a;
                }
                num2 = carry ? num2 + "1" : num2;
                rslt += num2;
            }
            else {
                num1 = num1.substr(len_short, num1.length() - len_short);
                for (int i = 0; i < num1.length(); i++) {
                    int a = num1[i] - '0';
                    a = carry ? a + 1 : a;
                    carry = a >= 10 ? true : false;
                    if (a >= 10) a -= 10;
                    num1[i] = '0' + a;
                }
                num1 = carry ? num1 + "1" : num1;
                rslt += num1;
            }
        }
        reverse(rslt.begin(), rslt.end());
        return rslt;
    }
};

int main() {
    
    string num1 = "408";
    string num2 = "5";
    Solution slt;
    string rslt = slt.addStrings(num1, num2);
    
    return 0;
}
