/*
 Validate if a given string can be interpreted as a decimal number.
 
 Some examples:
 "0" => true
 " 0.1 " => true
 "abc" => false
 "1 a" => false
 "2e10" => true
 " -90e3   " => true
 " 1e" => false
 "e3" => false
 " 6e-1" => true
 " 99e2.5 " => false
 "53.5e93" => true
 " --6 " => false
 "-+3" => false
 "95a54e53" => false
 
 Note: It is intended for the problem statement to be ambiguous. You should gather all requirements up front before implementing one. However, here is a list of characters that can be in a valid decimal number:
 
 Numbers 0-9
 Exponent - "e"
 Positive/negative sign - "+"/"-"
 Decimal point - "."
 Of course, the context of these characters also matters in the input.
 
 Update (2015-02-10):
 The signature of the C++ function had been updated. If you still see your function signature accepts a const char * argument, please click the reload button to reset your code definition.
 */

///@author  Zhao Wei
///@date    November 2, 2018
///@version 1.0

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    ///@brief   判断一个字符串是否是数字。
    ///@param   s   字符串
    ///@return  如果一个字符串是数字，那么返回true；否则返回false。
    ///@note    1. 枚举法；
    //          2. 一个字符串的开头可以是数字，+/-，空格符，中间可以有一个字母e，e的两侧可以各有一个'.'和+/-号。
    //          3. 时间复杂度为O(n)，空间复杂度为O(1)，其中n为字符串长度。
    bool isNumber(string s) {
        if (s.empty())  return false;
        
    }
};

int main() {
    Solution slt;
    string input;
    while (cin >> input) {
        cout << slt.isNumber(input) << endl;
    }
    return 0;
}
