﻿///@brief	Roman to Integer
///@author  zhaowei
///@date	2015.06.03
///@version 1.0

#include <string>
#include <iostream>
using namespace std;

class Solution
{
public:
	///@brief	罗马数字转换成阿拉伯数字
	///@param	s	待转换的罗马数字
	///@return	返回转换后的阿拉伯数字
	///@author	zhaowei
	///@date	2015.06.03
	///@note	罗马数字的组成是从头到尾遍历一遍，根据不同的字符进行累加。注意在V, X, L, C, D, M前面的相应字符是减数，其后面的字符是加数。
	int romanToInt(string s) {

		char roman_elmnt[7] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
		int rslt = 0;

		for (int i = 0; i < s.length(); i++)	//遍历罗马数字，逐位累加，特殊字符前面的数字是减数，后面的才是加数
		{
			if (s[i] == 'M')
			{
				rslt += 1000;
			}
			else if (s[i] == 'D')
			{
				rslt += 500;
			}
			else if (s[i] == 'C')
			{
				if (i+1 < s.length() && (s[i+1] == 'D' || s[i+1] == 'M'))	// 注意要判断i+1是否越界
				{
					rslt -= 100;
				}
				else
					rslt += 100;
			}
			else if (s[i] == 'L')
			{
				rslt += 50;
			}
			else if (s[i] == 'X')
			{
				if (i+1 < s.length() && (s[i+1] == 'C' || s[i+1] == 'L'))	// 注意要判断i+1是否越界
				{
					rslt -= 10;
				}
				else
					rslt += 10;
			}
			else if (s[i] == 'V')
			{
				rslt += 5;
			}
			else if (s[i] == 'I')
			{
				if (i+1 < s.length() && (s[i+1] == 'X' || s[i+1] == 'V'))	// 注意要判断i+1是否越界
				{
					rslt -= 1;
				}
				else
					rslt += 1;
			}
		}
		return rslt;
	}
};

int main()
{
	Solution slt;

	string test;
	while (cin >> test)
	{
		int num = slt.romanToInt(test);
		cout << test << endl;
	}

	return 0;
}