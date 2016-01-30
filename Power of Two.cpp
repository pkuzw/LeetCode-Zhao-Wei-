///@file	Power of Two
/*
Given an integer, write a function to determine if it is a power of two.
*/
///@author	zhaowei
///@date	2015.07.25
///@version	1.0

///@date	2015.08.06
///@version	1.1
///@version	2.0

///@date	2016.01.30
///@version	3.0

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution_v1 {
public:
	///@brief	判断一个数n是否是2的幂
	///@param	n	整数
	///@return	如果是则返回true，否则返回false
	/* @note	生成int能够表示的2^k的数组，然后在其中寻找是否存在n即可。时间复杂度为O(logn)，空间复杂度为O(logn)。*/
	bool isPowerOfTwo(int n) {
		int k = 1;
		vector<int> two_pow;
		for (int i = 0; i <= 30; i++)
			two_pow.push_back(1<<i);

		if (find(two_pow.begin(), two_pow.end(), n) == two_pow.end())
			return false;
		return true;
	}
};

class Solution_v2 {
public:
	///@note	 2的正整数次幂减1与本身相与得0
	bool isPowerOfTwo(int n)
	{
		return (n > 0) && (!(n & (n-1)));
	}
};

class Solution {
public:
	///@note	1. 正整数的2^k的2进制表示只有1个1，其余各位是0；对于负数直接判错。
	bool isPowerOfTwo(int n) {
		if (n < 0)	return false;
		int cnt = 0;
		while (n) {
			cnt += (n & 1);
			n >>= 1;
		}
		return cnt == 1;
	}
};

int main()
{
	Solution slt;
	bool rslt = slt.isPowerOfTwo(0);
	return 0;
}