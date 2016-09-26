//
//  UTF-8 Validation.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/25/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    UTF-8 Validation
///@author  Wei Zhao
///@date    2016.09.25
///@version 1.0
/*
 A character in UTF8 can be from 1 to 4 bytes long, subjected to the following rules:
 
 For 1-byte character, the first bit is a 0, followed by its unicode code.
 For n-bytes character, the first n-bits are all one's, the n+1 bit is 0, followed by n-1 bytes with most significant 2 bits being 10.
 This is how the UTF-8 encoding would work:
 
 Char. number range  |        UTF-8 octet sequence
 (hexadecimal)    |              (binary)
 --------------------+---------------------------------------------
 0000 0000-0000 007F | 0xxxxxxx
 0000 0080-0000 07FF | 110xxxxx 10xxxxxx
 0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
 0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
 Given an array of integers representing the data, return whether it is a valid utf-8 encoding.
 
 Note:
 The input is an array of integers. Only the least significant 8 bits of each integer is used to store the data. This means each integer represents only 1 byte of data.
 
 Example 1:
 
 data = [197, 130, 1], which represents the octet sequence: 11000101 10000010 00000001.
 
 Return true.
 It is a valid utf-8 encoding for a 2-bytes character followed by a 1-byte character.
 Example 2:
 
 data = [235, 140, 4], which represented the octet sequence: 11101011 10001100 00000100.
 
 Return false.
 The first 3 bits are all one's and the 4th bit is 0 means it is a 3-bytes character.
 The next byte is a continuation byte which starts with 10 and that's correct.
 But the second continuation byte does not start with 10, so it is invalid.
 */
#include <stdio.h>
#include <vector>

using namespace std;

class Solution {
    public:
    ///@brief   verify the input data is a valid UTF-8 character
    ///@note    1. iteration
    //          2. check every number in the array of data, if in the representation of binary, its first bit is 1, then count the number of 1 continuous, if there isn't enough number in the array starts with 10, return false; there should be more than one 1 at head, otherwise it's false
    //          3. if a number starts with 0, it's also valid.
    bool validUtf8(vector<int>& data) {
        if (data.empty())   return false;
        int mask = 0xff;
        int count[8] = {0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1};
        for (int i = 0; i < data.size(); i++) {
            int cur = data[i] & mask;
            int seq_one = 0;
            if ((cur >> 7) == 0)    continue;
            else {
                for (int i = 0; i < 8; i++) {
                    if (cur & count[i]) seq_one++;
                    else    break;
                }
                if (seq_one == 1)   return false;
                for (int j = i + 1; j < i + seq_one; j++) {
                    int start_with_one = (data[j] & mask) >> 6;
                    if (start_with_one != 2)    return false;
                }
                i += seq_one - 1;
            }
        }
        return true;
    }
};

int main() {
    Solution slt;
    vector<int> data = {197,130,1};
    bool rslt = slt.validUtf8(data);
    return 0;
}




























