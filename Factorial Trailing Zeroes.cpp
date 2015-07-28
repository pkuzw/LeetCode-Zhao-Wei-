///@file	Factorial Trailing Zeroes
/*
Given an integer n, return the number of trailing zeroes in n!.

Note: Your solution should be in logarithmic time complexity.
*/
///@author	zhaowei
///@date	2015.07.28
///@version	1.0

#include <vector>

using namespace std;

class Solution {
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

int main()
{
	int n = 150;
	Solution slt;
	int rslt = slt.trailingZeroes(n);
	return 0;
}