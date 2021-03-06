﻿///@file	Reverse Bits
/*
Reverse bits of a given 32 bits unsigned integer.

For example, given input 43261596 (represented in binary as 00000010100101000001111010011100), return 964176192 (represented in binary as 00111001011110000010100101000000).

Follow up:
If this function is called many times, how would you optimize it?
*/
///@author	zhaowei
///@date	2015.07.24
///@version	1.0

///@date	2015.08.11
///@version	1.1
///@version	2.0

///@date	2016.01.19
///@version	2.1

#include <cstdint>
#include <vector>
using namespace std;

class Solution_v1 {
public:
	///@brief	将一个十进制uint32_t数转换成二进制，然后计算出它的二进制逆序的十进制数
	///@param	n	十进制整数
	///@return  返回它的二进制逆序的十进制数
	/* @note	先将其转换成二进制数，然后再将其转换成十进制数。时间复杂度为O(logn)，空间复杂度为O(1)。*/
	uint32_t reverseBits(uint32_t n) {
		uint32_t cnt[32];
		uint32_t k = 1;
		for (int i = 0; i != 32; i++)
			cnt[i] = k << i;

		vector<int> binary_cnt(32, 0);	//	转换成二进制数组	
		for (int i = 31; i >= 0; i--)
		{
			if (n >= cnt[i])
			{
				n -= cnt[i];
				binary_cnt[i] = 1;
			}
		}

		uint32_t reverse_uint32 = 0;	//	再反向转换成十进制
		for (int i = 0; i != 32; i++)
		{
			reverse_uint32 += binary_cnt[31-i]*cnt[i];
		}
		return reverse_uint32;
	}
};

class Solution_v1_1 {
public:
	uint32_t reverseBits(uint32_t n) {
		vector<uint32_t> pow_of_2;
		for (int i = 0; i <= 31; i++)
			pow_of_2.push_back(1 << i);

		vector<bool> rec(32, false);
		for (int i = 31; i >= 0; i--)
		{
			if (n >= pow_of_2[i])
			{
				n -= pow_of_2[i];
				rec[i] = true;
			}
		}

		uint32_t rslt = 0;
		for (int i = 0; i <= 31; i++)
		{
			rslt += rec[i] ? pow_of_2[31 - i] : 0;
		}
		return rslt;
	}
};

/*
位操作。只需要将当前数字的二进制表示从右至左析取出来，然后添加到新数字的末端即可
*/
class Solution_v2 {
public:
	uint32_t reverseBits(uint32_t n) {
		uint32_t rslt = 0;
		for (int i = 0; i <= 31; i++)
		{
			if (n & 1 == 1)	rslt = (rslt << 1) + 1;
			else			rslt <<= 1;
			n >>= 1;
		}
		return rslt;
	}
};

class Solution {
public:
	///@brief	将一个十进制uint32_t数转换成二进制，然后计算出它的二进制逆序的十进制数
	///@param	n	十进制整数
	///@return  返回它的二进制逆序的十进制数
	///@note	1. 利用位操作运算将uint32_t整型变量从左至右析出，然后添加到一个初始值为0的uint32_t的整型变量末尾。
	//			2. 注意在循环过程中，如果已经遍历完输入的整型变量，应该立即中止循环。
	uint32_t reverseBits(uint32_t n) {
		uint32_t rslt = 0;
		int k = 32;
		while (k--) {
			rslt |= (n & 1);
			if (!k)	break;
			rslt <<= 1;
			n >>= 1;
		}
		return rslt;
	}
};

int main()
{
	uint32_t n = 1/*2147483648*/;
	Solution slt;
	uint32_t rslt = slt.reverseBits(n);
	return 0;
}