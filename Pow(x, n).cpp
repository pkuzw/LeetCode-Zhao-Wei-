///@file	Pow(x, n)
//			implement pow(x, n)
///@author	zhaowei
///@date	2015.07.02
///@version 1.0

#include <iostream>
using namespace std;

class Solution {
public:
	///@brief	实现计算浮点数的n次幂函数
	///@param	x	底数
	///@param	n	指数
	///@return	返回x^n的值
	///@note	先计算出n分解成二进制的表示形式，然后计算出底数x从2^0到2^30的幂值。通过先前计算出来的二进制表示位，将x的不同幂值相乘即可。
	//			注意INT_MAX = 2147483647，INT_MIN = -2147483648。
	//			时间复杂度为O(logn)，空间复杂度为O(1)。
	double myPow(double x, int n) 
	{
		bool flag = false;	//	标记n是否为负数
		bool f_min = false;	//	标记n是否为int_min
		if (n < 0)	// 注意INT_MAX = 2147483647，INT_MIN = -2147483648
		{
			if (n != INT_MIN)
			{
				n *= -1;
			}
			else
			{
				n = INT_MAX;
				f_min = true;
			}			
			flag = true;
		}
		else if (n == 0)	//	处理n为0的情形
		{
			return 1;
		}

		bool bit[33];	//	标记需要最终相乘哪几位x的2^k次幂
		memset(bit, false, 33*sizeof(bool));

		int bnry[33];	//	将n分解成二进制表示的数组
		memset(bnry, 0, 33*sizeof(int));
		for (int i = 0; i != 31; i++)
		{
			bnry[i] = 1 << i;
		}
		
		
		bnry[31] = INT_MAX;
		bnry[32] = INT_MAX;

		double candidate[33];	//	x的2^k幂数组
		memset(candidate, 0, 33*sizeof(double));

		candidate[0] = x;		
		for (int i = 1; i != 31; i++)
		{
			candidate[i] = candidate[i-1]*candidate[i-1];
		}
		candidate[31] = candidate[30]*(candidate[30]/candidate[0]);
		if (flag && f_min)
		{
			candidate[31] *= candidate[0];
		}
		candidate[32] = candidate[31];
		int tmp = n;
		while (tmp != 0)
		{
			for (int i = 31; i >= 0; i--)
			{
				if (tmp >= bnry[i] && tmp <= bnry[i+1])
				{
					bit[i] = true;
					tmp -= bnry[i];
				}
			}
		}

		double rslt = 1;	
		for (int i = 0; i != 32; i++)
		{
			if (bit[i])
			{
				rslt *= candidate[i];	//	将标记出的x的2^k幂相乘即可
			}
		}
		if (flag)	//	处理n为负数的情形
		{
			rslt = 1/rslt;
		}
		return rslt;
	}
};

int main()
{
	int n;
	double x;
	Solution slt;
	while (cin >> x >> n)
	{
		cout << slt.myPow(x, n) << endl;
	}
	return 0;
}