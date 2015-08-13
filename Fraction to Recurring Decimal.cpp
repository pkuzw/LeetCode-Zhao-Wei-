﻿///@file	Fraction to Recurring Decimal
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

///@date	2015.08.13
///@version	2.0

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

class Solution_v1 {
public:
	///@brief	将分数转换成小数
	///@param	numerator	分子
	///@param	denominator	分母
	///@return	返回字符串表示的小数，如果是循环小数，则将循环部分用括号括起来
	/* @note	1. 利用哈希表存储以前出现过的商，如果再次出现，则用括号包括起来返回；
				2. 时间复杂度为O(n)，空间复杂度为O(n)。*/
	string fractionToDecimal(int numerator, int denominator) {
		int s1 = numerator >= 0 ? 1 : -1;	//	分子的符号
		int s2 = denominator >= 0 ? 1 : -1;	//	分母的符号
		long long num = abs( (long long)numerator );	//	为了保证精度，将分子和分母转换成long long型
		long long den = abs( (long long)denominator );
		long long out = num / den;	//	计算其商
		long long rem = num % den;	//	计算其余数

		unordered_map<long long, int> m;
		string res = to_string(out);	//	将long long型变量转换成字符串
		if (s1 * s2 == -1 && (out > 0 || rem > 0)) res = "-" + res;	//	添加符号
		if (rem == 0) return res;	//	如果能被整除，则直接返回

		res += ".";	//	否则计算小数部分
		string s = "";
		int pos = 0;
		while (rem != 0) {
			if (m.find(rem) != m.end())
			{
				s.insert(m[rem], "(");
				s += ")";
				return res + s;
			}
			m[rem] = pos;
			s += to_string((rem * 10) / den);
			rem = (rem * 10) % den;
			++pos;
		}
		return res + s;
	}
};

class Solution {
public:
	string fractionToDecimal(int numerator, int denominator) {
		if (!denominator)	return "";
		if (!numerator)		return "0";

		int sign_n = (numerator < 0) ? -1 : 1;
		int sign_d = (denominator < 0) ? -1 : 1;
		long long num = abs((long long)numerator);	//	将除数和被除数都转换成正数，便于后续处理
		long long den = abs((long long)denominator);//	这里要将int型转换成long long型变量，否则遇到INT_MIN，就会溢出
		long long out = num / den;
		long long rem = num % den;

		string rslt = to_string(out);
		if (sign_d * sign_n == -1)	rslt = "-" + rslt;
		if (!rem)	return rslt;

		rslt += ".";
		unordered_map<long long, int> ht;	//	记录循环部分的起始下标
		string s;
		int pos = 0;
		while (rem)
		{
			if (ht.find(rem) != ht.end())
			{
				s.insert(ht[rem], "(");
				s += ")";
				return rslt + s;
			}
			else
			{
				s += to_string(rem * 10 / den);
				ht[rem] = pos;
				rem = rem * 10 % den;
				pos++;
			}
		}
		return rslt + s;
	}
};

int main()
{
	double a, b;
	a = -1;
	b = -2147483648;
	cout << a/b << endl;

	Solution_v1 slt_v1;
	string rslt = slt_v1.fractionToDecimal(-1, INT_MIN);

	Solution slt;
	rslt = slt.fractionToDecimal(-1, INT_MIN);

	return 0;
}