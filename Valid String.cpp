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
///@date    November 3, 2018
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
        trim(s);
        if (s.empty())  return false;
        vector<int> strDigitPos, strExpoPos, strPointPos, strSignPos;
        if (!checkLegal(s, strDigitPos, strExpoPos, strPointPos, strSignPos)) return false;
        if (strExpoPos.empty()) {
            if  (strSignPos.size() > 1 || (strSignPos.size() == 1 && strSignPos[0] != 0))    return false;
        }
        else if (strExpoPos.size() == 1) {
            string left = s.substr(0, strExpoPos[0]);
            string right = s.substr(strExpoPos[0]+1, s.length() - strExpoPos[0] - 1);
            vector<int> leftDigitPos, leftExpoPos, leftPointPos, leftSignPos;
            vector<int> rightDigitPos, rightExpoPos, rightPointPos, rightSignPos;
            if ((!strPointPos.empty() && strPointPos[0] > strExpoPos[0]) ||
                (left.empty() || right.empty()) ||
                !checkLegal(left, leftDigitPos, leftExpoPos, leftPointPos, leftSignPos) ||
                !checkLegal(right, rightDigitPos, rightExpoPos, rightPointPos, rightSignPos) ||
                (strSignPos.size() == 2 && (strSignPos[0] != 0 || strSignPos[1] != strExpoPos[0] + 1)) ||
                (strSignPos.size() == 1 && (strSignPos[0] != 0 && strSignPos[0] != strExpoPos[0] + 1)))
                return false;
        }
        return true;
    }
    
    ///@brief   去掉前缀空白符和后缀空白符
    ///@param   str     字符串
    ///@return  无
    void trim(string& str) {
        int i = 0;
        for (; i < str.length(); i++)
            if (str[i] != ' ')  break;
        str = str.substr(i);
        i = str.length() - 1;
        for(; i >= 0; i--)
            if (str[i] != ' ')  break;
        str = str.substr(0, i+1);
    }
    
    ///@brief   字符串中是否含有非法字符
    ///@param   str     字符串
    ///@param   digitPos    字符串中数字字符的下标数组
    ///@param   expoPos     字符串中幂指数符号的下标数组
    ///@param   pointPos    字符串中小数点的下标数组
    ///@param   signPos     字符串中正负号的下标数组
    ///@return  如果字符串中不含有非法字符，返回true，否则返回false。
    bool checkLegal(string str, vector<int>& digitPos, vector<int>& expoPos, vector<int>& pointPos, vector<int>& signPos) {
        for (int i = 0; i < str.length(); i++) {
            if (str[i] <= '9' && str[i] >= '0')     digitPos.push_back(i);
            else if (str[i] == 'e' || str[i] == 'E')     expoPos.push_back(i);
            else if (str[i] == '.')     pointPos.push_back(i);
            else if (str[i] == '+' || str[i] == '-')    signPos.push_back(i);
            else
                return false;
        }
        if (pointPos.size() > 1 ||
            expoPos.size() > 1 ||
            signPos.size() > 2 ||
            ((!pointPos.empty() || !expoPos.empty() || !signPos.empty()) && digitPos.empty()))
            return false;
        return true;
    }
};

int main() {
    Solution slt;
    string input;
    while (getline(cin, input)) {
        cout << slt.isNumber(input) << endl;
    }
    return 0;
}
