﻿///@brief	Integer to Roman
///@author  zhaowei
///@date	2015.06.03
///@version 1.0

///@date    2015.09.07
///@version 2.0

///@date	2015.09.15
///@version	2.1

///@date	2016.04.02
///@version	2.2

#include <string>
#include <iostream>
using namespace std;

class Solution_v1
{
public:
	///@brief	阿拉伯数字转换成罗马数字
	///@param	num	待处理的整型变量
	///@return	返回转换后的罗马数字
	///@author	zhaowei
	///@date	2015.06.03
	///@note	逐位处理，每一位分成4种情况，<4, 4, 5-8, 9
	string intToRoman(int num) {

		string roman_elmnt[7] = {"I", "V", "X", "L", "C", "D", "M"};
		string roman_less[6] = {"IV", "IX", "XL", "XC", "CD", "CM"};


		int roman_bit[4] = {0};
		int num_bit[4] = {1000, 100, 10, 1};

		// 计算int型变量的各个位数
		for (int i = 0; i < 4; i++)
		{
			roman_bit[i] = num/num_bit[i];
			roman_bit[i] %= num_bit[2];
		}

		string rslt;	// 返回的字符串
		
		// 因为int型变量的千位不会有特殊字符，故先处理之。
		for (int j = 0; j < roman_bit[0]; j++)
		{
			rslt += roman_elmnt[6];
		}

		// 逐个处理百位、十位和个位
		// 分成4段，1-4，4，5-8，9 来对每一位进行转换
		for (int i = 1; i < 4; i++)
		{
			if (roman_bit[i] < 4)
			{
				for (int j = 0; j < roman_bit[i]; j++)
				{
					rslt += roman_elmnt[4-(i-1)*2];
				}
			}
			else if (roman_bit[i] == 4)
			{
				rslt += roman_less[4-(i-1)*2];
			}
			else if (roman_bit[i] >= 5 && roman_bit[i] < 9)
			{
				rslt += roman_elmnt[5-(i-1)*2];
				for (int j = 0; j < roman_bit[i]-5; j++)
				{
					rslt += roman_elmnt[4-(i-1)*2];
				}
			}
			else if (roman_bit[i] == 9)
			{
				rslt += roman_less[5-(i-1)*2];
			}
		}
	
		return rslt;		
    }
};

class Solution_v2 {
public:
	///@brief	将int型变量转换成罗马数字
	///@param	num	十进制的阿拉伯数字，范围是1 - 3999
	///@return	返回对应的罗马数字
	///@note	罗马数字是逢5和10有改变，所以与1 - 3999之间的整数有关的罗马整数是1，5，10，50，100，500和1000，一共7个。
	//			每个整数都可以划归成下列4中情况之一：1. 10的幂；2. 10的幂到5*10的幂-1之间；3. 5*10的幂到10的幂-1之间；4.10的幂-1.
	//			时间复杂度为O(logn)，空间复杂度为O(1)。
    string intToRoman(int num) {
		string rslt;
		char roman[7] = {'M', 'D', 'C', 'L', 'X', 'V', 'I'};
		int val[7] = {1000, 500, 100, 50, 10, 5, 1};

		for (int i = 0; i < 7; i += 2) {
			int x = num / val[i];
			if (x < 4) {
				for (int j = 1; j <= x; j++)	rslt += roman[i];
			}
			else if (x == 4)	rslt = rslt + roman[i] + roman[i-1];
			else if (x < 9 && x > 4) {
				rslt += roman[i-1];
				for (int j = 6; j <= x; j++)	rslt += roman[i];
			}
			else if (x == 9)	rslt = rslt + roman[i] + roman[i-2];
			num %= val[i];
		}
		return rslt;
    }
};

class Solution {
public:
	string intToRoman(int num) {
		string roman[] = {"M", "D", "C", "L", "X", "V", "I"};
		int units[] = {1000, 500, 100, 50, 10, 5, 1};
		string rslt;
		for (int i = 0; i < 7; i += 2) {
			int x = num / units[i];
			if (!x)	continue;
			else if (x < 4)
				for (int j = 0; j < x; j++)	rslt += roman[i];			
			else if (x == 4)
				rslt += roman[i] + roman[i-1];
			else if (x > 4 && x < 9) {
				rslt += roman[i-1];
				for (int j = 5; j < x; j++)	rslt += roman[i];
			}
			else if (x == 9)
				rslt += roman[i] + roman[i-2];
			num %= units[i];
		}
		return rslt;
	}
};

int main()
{
	Solution slt;
	Solution_v2 s2;
	int num = 3999;
	string t = slt.intToRoman(num);
	string t2 = s2.intToRoman(num);
	return 0;
}