///@file	Add Binary
/*
Given two binary strings, return their sum (also a binary string).

For example,
a = "11"
b = "1"
Return "100".
*/
///@author	zhaowei
///@date	2015.07.08
///@version	1.0

///@date	2015.08.27
///@version	2.0

///@date	2015.12.03
///@version	2.1

#include <iostream>
#include <string>

using namespace std;

class Solution_v1 {
public:
	///@brief	计算两个给定的二进制数的和
	///@param	a	二进制加数1
	///@param	b	二进制加数2
	///@return	返回a+b
	///@note	补齐两个不一样的子串，便于后续计算。时间复杂度为O(n)，空间复杂度为O(1)。
	string addBinary(string a, string b) 
	{
		bool flg = false;	//	进位标识
		if (a.length() > b.length())	//	默认a比b短，否则交换二者
			swap(a, b);

		int len_diff = b.length()-a.length();	
		string zero(len_diff, '0');
		a = zero + a;	//	补齐较短的字符串，便于后续计算
		
		for (int i = a.length()-1; i >= 0; i--)
		{
			if (a[i] == '1' && b[i] == '1')
			{
				if (!flg)				
				{
					b[i] = '0';
					flg = true;
				}
			}
			else if ((a[i] == '1' && b[i] == '0') || (a[i] == '0' && b[i] == '1'))
			{
				if (flg)	b[i] = '0';
				else		b[i] = '1';
			}
			else
			{
				if (flg)
				{
					b[i] = '1';
					flg = false;
				}				
			}
		}
		if (flg)	//	如果结果的最高位还需要进位，则补齐最高位
		{
			b = "1" + b;
		}
		return b;
	}
};

class Solution {
public:
	///@brief	计算两个二进制数的加法
	///@param	a	加数
	///@param	b	加数
	///@return	返回a+b的和
	///@note	1. 先计算出a和b的长度，将短的加数补齐前端0；2. 从末尾向前逐一相加即可；3. 时间复杂度为O(n)，n为加数的长度。
	string addBinary(string a, string b) {
		int lenA = a.size(), lenB = b.size();
		if (lenA < lenB)
		{
			swap(a, b);
			int t = lenA;
			lenA = lenB;
			lenB = t;
		}
		b = string(lenA - lenB, '0') + b;
		bool flg = false;
		for (int i = lenA - 1; i >= 0; i--)
		{
			if (a[i] == '0' && b[i] == '0')
			{
				if (flg)
				{
					a[i] = '1';				
					flg = false;
				}
			}
			else if ((a[i] == '1' && b[i] == '0') || (a[i] == '0' && b[i] == '1'))
			{
				if (flg)	a[i] = '0';
				else		a[i] = '1';
			}
			else
			{
				if (!flg)
				{
					a[i] = '0';
					flg = true;
				}
			}
		}
		if (flg)	a = "1" + a;
		return a;
	}
};

int main()
{
	string a, b;
	Solution slt;
	while (cin >> a >> b)
	{
		cout << slt.addBinary(a, b) << endl;
	}
	return 0;
}