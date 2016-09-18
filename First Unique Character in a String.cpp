
//
//  First Unique Character in a String.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/18/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    First Unique Character in a String
///@author  Wei Zhao
///@date    2016.09.18
///@version 1.0

#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    ///@brief   Find the first unique character in the string.
    ///@param   s   the string
    ///@return  the index of the first unique character
    ///@note    1. enumeration
    //          2. use an array to store the appearing times of the letters in the first loop, then the second loop find the first uqique character.
    int firstUniqChar(string s) {
        if (s.empty())  return -1;
        int ht[26] = {0};
        for (int i = 0; i != s.size(); i++) {
            ht[s[i] - 'a']++;
        }
        for (int i = 0; i != s.size(); i++) {
            if (ht[s[i] - 'a'] ==  1)   return i;
        }
        return -1;
    }
};

int main() {
    string s = "hh";
    Solution slt;
    int rslt = 0;
    rslt = slt.firstUniqChar(s);
    return 0;
}
