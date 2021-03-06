﻿///@file	Plus One
/*
Given a non-negative number represented as an array of digits, plus one to the number.

The digits are stored such that the most significant digit is at the head of the list.
*/
///@author	zhaowei
///@date	2015.07.08
///@version	1.0

///@date	2015.08.27
///@version	2.0

///@date	2015.12.01
///@version	2.1

///@date	2016.04.19
///@version	2.2

///@date    November 1, 2018
///@version 3.0

#include <iostream>
#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	将保存为整型vector的非负整数加1
	///@param	digits	非负整数
	///@return	返回该整数加1后的和
	///@note	注意进位
	vector<int> plusOne(vector<int>& digits) 
	{
		bool flg = false;	//	标记是否需要进位
		digits.back() += 1;
		if (digits.back() == 10)
		{
			flg = true;
			digits.back() = 0;
		}

		for (int i = digits.size()-2; i >= 0; i--)
		{
			if (flg)
			{
				digits[i]++;
				if (digits[i] == 10)
				{
					digits[i] = 0;					
				}
				else	
					flg = false;
			}			
		}

		vector<int> rslt;
		if (flg) rslt.push_back(1);	//	如果和比原来的整数多了一位，则需要把1提前加入结果
		for (int i = 0; i != digits.size(); i++)
		{
			rslt.push_back(digits[i]);
		}
		return rslt;
	}
};

class Solution_v2 {
public:
	///@brief	将整数存储在一维数组当中，将其末位加1后，计算所得结果
	///@param	digits	被加数
	///@return	返回加1后的和
	///@note	1. 从末位向前遍历；2. 设置一个标识符标记进位；3. 如果最高位也需要进位，则要在最前端插入1；4. 时间复杂度为O(n)，空间复杂度为O(1)，其中n为数字的长度。
	vector<int> plusOne(vector<int>& digits) {
		bool flg = false;
		digits.back()++;
		if (digits.back() == 10)
		{
			digits.back() = 0;
			flg = true;				 
		}
		for (int i = digits.size() - 2; i >= 0; i--)
		{			
			digits[i] = flg ? digits[i] + 1 : digits[i];
			if (digits[i] == 10)
			{
				digits[i] = 0;
				flg = true;
			}
			else	flg = false;			
		}
		if (flg)	digits.insert(digits.begin(), 1);
		return digits;
	}
};

class Solution_v2_2 {
public:
	///@brief	将整数存储在一维数组当中，将其末位加1后，计算所得结果
	///@param	digits	被加数
	///@return	返回加1后的和
	///@note	1. 从末位向前遍历；2. 设置一个标识符标记进位；3. 如果最高位也需要进位，则要在最前端插入1；4. 时间复杂度为O(n)，空间复杂度为O(1)，其中n为数字的长度。
	vector<int> plusOne(vector<int>& digits) {
		if (digits.empty()) {
			vector<int> rslt(1, 0);
			return rslt;
		}
		bool flg = false;
		digits.back()++;
		if (digits.back() == 10) {
			flg = true;
			digits.back() = 0;
		}
		for (int i = digits.size() - 2; i >= 0; i--) {
			if (flg) {
				digits[i]++;
				flg = false;
			}
			if (digits[i] == 10) {
				digits[i] = 0;
				flg = true;
			}
		}
		if (flg) {
			digits.insert(digits.begin(), 1);
			flg = false;
		}
		return digits;
	}
};

class Solution {
public:
    ///@brief   给定一个数组，用来表示一个非负整数，计算该整数自增1后的数组表示的值。
    ///@param   digits  数组
    ///@return  返回自增后的数组。
    ///@note    1. 枚举法；
    //          2. 注意进位即可；
    ///         3. 在数组中插入元素可以使用vector<int>::insert(iterator, val)方法，会在iterator前面插入val；
    //          4. 实际上，当carry已经为0时，就没必要继续向前遍历了，这样节约时间；
    //          5. 时间复杂度为O(n)，空间复杂度为O(1)，其中n为数组长度。
    vector<int> plusOne(vector<int>& digits) {
        int carry = 1;
        for (int i = digits.size() - 1; i >= 0 && carry == 1; i--) {
            digits[i] += carry;
            carry = digits[i] / 10;
            digits[i] %= 10;
        }
        if (carry)  digits.insert(digits.begin(), carry);
        return digits;
    }
};

int main()
{
	vector<int> sum;
	vector<int> digits;
	digits.push_back(9);
	digits.push_back(8);
	digits.push_back(9);

	
	Solution slt;
	sum = slt.plusOne(digits);

	return 0;
}
