///@file	Bitwise AND of Numbers Range
/*
Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND of all numbers in this range, inclusive.

For example, given the range [5, 7], you should return 4. 
*/
///@author	zhaowei
///@date	2015.08.04
///@version	1.0

///@date	2015.08.11
///@version	1.1

///@date    2016.01.24
///@version 1.2

#include <numeric>
using namespace std;

class Solution_v1 {
public:
	///@brief	计算将指定区间的连续整数求与的结果
	///@param	m	左边界
	///@param	n	右边界
	///@return	返回求与的值
	/* @note	通过观察发现，连续个整数求与世界上是求这些数的公共部分。所以建立一个全都是1的mask，然后分别对m和n求与，判断二者是否相同即可。
				如果不等，那么将mask左移1位继续求与。直到相等为止。
				时间复杂度为O(logn)，空间复杂度为O(1)。*/
	int rangeBitwiseAnd(int m, int n) {
		if (m == n)	return m;

		int mask = INT_MAX;
		while ((m & mask) != (n & mask))
		{
			mask <<= 1;
		}

		return m & mask;
	}

	///@brief	枚举法逐一求与，时间复杂度为O(n)，TLE。
	int verify(int m, int n)
	{
		int i = m+1;
		int r = m;
		while (i <= n)
		{
			r = r & i;
			i++;
		}
		return r;
	}
};

/*
通过观察发现，连续整数求与就是左右边界二进制表示的公共前缀。求两个数的公共前缀就是用0xffffffff不停的与之相与，如果不等，则左移一位直到相等为止。
*/
class Solution {
public:
    ///@brief   给定边界，求边界内的所有数的与
    ///@param   m   左边界
    ///@param   n   右边界
    ///@return  返回边界内的所有数的与
    ///@note    1. 位操作；2. 计算左边界与右边界的公共前缀，就是边界范围内的所有数的与。
	int rangeBitwiseAnd(int m, int n) {
		unsigned mask = 0xffffffff;
		while ((m & mask) != (n & mask)) mask <<= 1;
		return m & mask;		
	}
};

int main()
{
	int m = 578;
	int n = 698;
	Solution_v1 slt_v1;
	Solution slt;
	int r1 = slt_v1.rangeBitwiseAnd(m, n);
	int r2 = slt.rangeBitwiseAnd(m, n);
	return 0;
}