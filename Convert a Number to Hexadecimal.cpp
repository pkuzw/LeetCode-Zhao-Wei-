//
//  Convert a Number to Hexadecimal.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 10/9/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//
///@file    Convert a Number to Hexadecimal
///@author  Wei Zhao
///@date    10.09.2016
///@version 1.0

/*
 Given an integer, write an algorithm to convert it to hexadecimal. For negative integer, two’s complement method is used.
 
 Note:
 
 All letters in hexadecimal (a-f) must be in lowercase.
 The hexadecimal string must not contain extra leading 0s. If the number is zero, it is represented by a single zero character '0'; otherwise, the first character in the hexadecimal string will not be the zero character.
 The given number is guaranteed to fit within the range of a 32-bit signed integer.
 You must not use any method provided by the library which converts/formats the number to hex directly.
 Example 1:
 
 Input:
 26
 
 Output:
 "1a"
 Example 2:
 
 Input:
 -1
 
 Output:
 "ffffffff"
 */

#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    /*  @note
        1. for the positive integer, just process it with each 4 bits from most significan bit to least significant bit.
        2. for the negative integer, firstly it should be transfered into the two's complement. the fisrt step is get the absolute value of 
        the number, secondly use the bitwise NOT on the absolute value, lastly add 1 to the end of the number.
     */
    string toHex(int num) {
        string rslt = "";
        if (!num)   return "0";
        else if (num > 0) {
            unsigned msb = 15;
            msb <<= 28;
            msb = ~msb;
            for (int i = 0; i < 8; i++) {
                unsigned head4bits = num | msb;
                head4bits >>= 28;
                if (head4bits < 10) rslt += char('0' + head4bits);
                else if (head4bits == 10) rslt += 'a';
                else if (head4bits == 11) rslt += 'b';
                else if (head4bits == 12) rslt += 'c';
                else if (head4bits == 13) rslt += 'd';
                else if (head4bits == 14) rslt += 'e';
                else if (head4bits == 15) rslt += 'f';
                num <<= 4;
            }
        }
        else if (num < 0) {
            unsigned tmp = -num;
            tmp = ~tmp;
            tmp++;
            unsigned msb = 15;
            msb <<= 28;
            msb = ~msb;
            for (int i = 0; i < 8; i++) {
                unsigned head4bits = tmp | msb;
                head4bits >>= 28;
                if (head4bits < 10) rslt += char('0' + head4bits);
                else if (head4bits == 10) rslt += 'a';
                else if (head4bits == 11) rslt += 'b';
                else if (head4bits == 12) rslt += 'c';
                else if (head4bits == 13) rslt += 'd';
                else if (head4bits == 14) rslt += 'e';
                else if (head4bits == 15) rslt += 'f';
                tmp <<= 4;
            }
        }
        int j = 0;
        while (rslt[j] == '0') {
            j++;
        }
        rslt = rslt.substr(j);
        return rslt;
    }
};

int main() {
    Solution slt;
    string rslt = slt.toHex(INT_MAX);
    rslt = slt.toHex(INT_MIN);
    rslt = slt.toHex(-1);
    return 0;
}





















