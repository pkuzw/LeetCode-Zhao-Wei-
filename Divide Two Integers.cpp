///@file	Divide Two Integers
//			Divide two integers without using multiplication, division and mod operator.

//			If it is overflow, return MAX_INT.
///@author	zhaowei
///@date	2015.06.11
///@version	1.0

///@author  zhaowei
///@date    2015.09.06
///@version 2.0

#include <iostream>
using namespace std;

class Solution_v1
{
public:
	///@brief	不用乘法、除法和求模，计算两个整型变量的商
	///@param	dividend	被除数
	///@param	divisor		除数
	///@return	如果商没有溢出，则返回整型计算规则的商，否则返回INT_MAX
	///@author	zhaowei
	///@date	2015.06.11
	///@note	用减法来模拟除法。为了提高算法效率，新建一个数组来保存除数的2^n幂，然后拿这个数组来做除数。
	///			最后统计商时利用左移运算来计算2^n幂.
	//			由于|INT_MIN| > |INT_MAX|，在处理边界的时候要非常小心。
	int divide(int dividend, int divisor) 
	{
		bool sign_flag = false;	//	标记是否需要将结果取反
		if (divisor == 0)
		{
			return INT_MAX;
		}
		if ((dividend < 0 && divisor > 0) || (dividend > 0 && divisor < 0))
		{
			sign_flag = true;			
		}

		//	用unsign来保存中间值，否则INT_MIN的绝对值大于INT_MAX的绝对值，都转换成int型的正数时计算会出错。0
		unsigned usgn_dividend, usgn_divisor;	
		
		int rslt = 0;

		usgn_dividend = (dividend < 0) ? 0 - dividend : dividend;

		usgn_divisor = (divisor < 0) ? 0 - divisor : divisor;		

		unsigned divisor_arr[32];	//	除数数组
		memset(divisor_arr, 1, 32*sizeof(unsigned));		

		unsigned mult = usgn_divisor;
		divisor_arr[0] = mult;
		int k = 1;
		while (mult < INT_MAX)	//	这里的上限不能超过INT_MAX的一半，否则在内部的mult变量就会溢出
		{	
			mult += mult;
			divisor_arr[k++] = mult;
		}

		int *cnt = new int[k];
		memset(cnt, 0, k*sizeof(int));

		for (int i = k-1; i >= 0; i--)
		{
			while (usgn_dividend >= divisor_arr[i])	//	用减法来模拟除法
			{
				usgn_dividend -= divisor_arr[i];
				cnt[i]++;
			}
		}
		
		unsigned tmp = 0;	//	中间结果一律用unsigned类型来保存
		for (int i = 0; i < k; i++)	//	计算各位之和
		{
			for (int j = 0; j < cnt[i]; j++)
			{
				tmp += (1 << i);
			}
		}

		//	INT_MIN的绝对值比INT_MAX大1，需要详细判断每一种分支情形
		if (tmp == INT_MAX + 1)
		{
			if (sign_flag)	rslt = INT_MIN;
			else	rslt = INT_MAX;			
		}
		else if (tmp > INT_MAX + 1)
		{
			rslt = INT_MAX;
		}
		else if (tmp == INT_MAX)
		{
			if (sign_flag)	rslt = 0 - INT_MAX;
			else	rslt = INT_MAX;		
		}else
		{
			if (sign_flag)	rslt = 0 - tmp;
			else	rslt = tmp;		
		}
		delete []cnt;
		return rslt;
	}
};


class Solution {
public:
    int divide(int dividend, int divisor) {
        if (divisor == 0 || (dividend == INT_MIN) && divisor == -1) return INT_MAX;
        long m = labs(dividend), n = labs(divisor);
        long rslt = 0;
        long sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;
        if (n == 1) return m * sign;
        while (m >= n){
            long k = n;
            int i = 0;
            while (k <= m) {
                m -= k;
                k <<= 1;
                rslt += 1 << i;
                i++;
            }
        }
        return rslt;
    }
};



int main()
{
	int dividend = 2147483647;

	int divisor = 1;

	Solution slt;
	int d = slt.divide(dividend, divisor);
	cout << dividend / (divisor) << "		" << d << endl;

	return 0;
}