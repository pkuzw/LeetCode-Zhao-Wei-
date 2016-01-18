///@file	Factorial Trailing Zeroes
/*
Given an integer n, return the number of trailing zeroes in n!.

Note: Your solution should be in logarithmic time complexity.
*/
///@author	zhaowei
///@date	2015.07.28
///@version	1.0

///@date	2015.08.13
///@version	1.1

///@date	2016.01.18
///@version	1.2

#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	计算n!的末尾的0的数目
	///@param	n	正整数
	///@return	返回n!的末尾0的个数
	/* @note	n!末尾的0的个数与n包含的10的倍数数目有关，10可以分解成2和5，那么就要找5的倍数即可。对于像25 = 5^2, 125 = 5^3，
				625 = 5^4，这样的数要多计算一次5的次数。时间复杂度为O(logn)，空间复杂度O(1)。*/
	int trailingZeroes(int n) {
		int zero_cnt = 0;
		while (n > 0)
		{
			zero_cnt += n / 5;
			n /= 5;
		}
		return zero_cnt;
	}
};

class Solution {
public:
	///@brief	计算n!的末尾的0的数目
	///@param	n	正整数
	///@return	返回n!的末尾0的个数
	///@note	1. n!中末尾0的数目实际上就是10的倍数，10可以分解为2 * 5，那么就要看n是5的多少倍，对于5^k来说，可以分解出k个5.
	int trailingZeroes(int n) {
		int rslt = 0;
		while (n) {
			rslt += n / 5;
			n /= 5;
		}
		return rslt;
	}
};

int main()
{
	int n = 150;
	Solution slt;
	int rslt = slt.trailingZeroes(n);

	Solution_v1 slt_v1;
	rslt = slt_v1.trailingZeroes(n);
	return 0;
}