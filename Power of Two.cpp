///@file	Power of Two
/*
Given an integer, write a function to determine if it is a power of two.
*/
///@author	zhaowei
///@date	2015.07.25
///@version	1.0

///@date	2015.08.06
///@version	2.1

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution_v2 {
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

class Solution {
public:
	bool isPowerOfTwo(int n) {
		int power_n[31] = {1};
		for (int i = 0; i < 31; i++)
		{
			power_n[i] = 1 << i;
		}

		for (int i = 30; i >= 0; i--)
		{
			if (power_n[i] == n)	return true;
		}
		return false;
	}

	///@brief	 2的正整数次幂减1与本身相与得0
	bool isPowerOfTwo_v2_1(int n)
	{
		return (n > 0) && (!(n & (n-1)));
	}
};

int main()
{
	Solution slt;
	bool rslt = slt.isPowerOfTwo(1024);
	return 0;
}