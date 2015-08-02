///@file	Fraction to Recurring Decimal
/*
Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.

If the fractional part is repeating, enclose the repeating part in parentheses.

For example,

Given numerator = 1, denominator = 2, return "0.5".
Given numerator = 2, denominator = 1, return "2".
Given numerator = 2, denominator = 3, return "0.(6)".
*/
///@author	zhaowei
///@date	2015.08.02
///@version	1.0

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
	///@brief	将分数转换成小数
	///@param	numerator	分子
	///@param	denominator	分母
	///@return	返回字符串表示的小数，如果是循环小数，则将循环部分用括号括起来
	/* @note	*/
	string fractionToDecimal(int numerator, int denominator) {

	}
};

int main()
{
	double a, b;
	a = 4;
	b = 17;
	cout << a/b << endl;
	return 0;
}