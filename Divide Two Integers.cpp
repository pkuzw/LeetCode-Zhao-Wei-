///@file	Divide Two Integers
//			Divide two integers without using multiplication, division and mod operator.

//			If it is overflow, return MAX_INT.
///@author	zhaowei
///@date	2015.06.11
///@version	1.0

///@author  zhaowei
///@date    2015.09.06
///@version 2.0

///@date	2015.09.22
///@version	2.1

///@date    2016.04.07
///@version 2.2

///@date    September 11, 2018
///@version 2.3

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


class Solution_v2 {
public:
	///@brief	不用乘法、除法或求模运算来计算两个int型变量的除法
	///@param	dividend	被除数
	///@param	divisor		除数
	///@return	返回商
	///@note	1. 首先，需要做好溢出的情况处理，对于除数为0或者被除数为INT_MIN且除数为-1的情况，直接返回INT_MAX；
    //          2. 然后用一个标识符记录下商的符号。在对二者取绝对值后就可以进入运算环节了；
    //          3. 为了防止中间结果溢出，采用long型变量做中间值；
	//          4. 因为不能用乘法、除法和取模运算，除法的本质就是做减法，计算被除数是由多少个除数组成的。所以为了加快累计除数的速度，这里引入左移运算;
    //          5. 可以将时间复杂度提高到O(logn)。
    int divide(int dividend, int divisor) {
		if (!divisor || (dividend == INT_MIN && divisor == -1))	return INT_MAX;
        int sign = (divisor < 0) ^ (dividend < 0) ? -1 : 1;
		long m = labs(dividend), n = labs(divisor);
		int rslt = 0;
		while (m >= n) {
			long k = n;
			int i = 1;
			while (m >= k) {
				m -= k;
				k <<= 1;
				rslt += i;
				i <<= 1;
			}
		}
		return rslt * sign;
    }
};

class Solution {
public:
    ///@brief   在不使用乘法，除法和求模运算的情况下，计算两个32位整型变量的除法运算。
    ///@param   dividend    被除数
    ///@param   divisor     除数
    ///@return  如果商可以被32位整型变量表示，则返回int型的商；否则返回INT_MAX
    ///@note    1. 题目条件限制下，只能使用减法。
    //          2. 为了更快的进行减法，每次可以对除数进行左移运算来加快减法的速度。
    //          3. 在程序中为了避免int型变量的溢出，用long型来做临时变量。
    //          4. 时间复杂度为O(logn)，空间复杂度为O(1)。其中n为商的大小。
    int divide(int dividend, int divisor) {
        if (!divisor || (dividend == INT_MIN && divisor == -1)) return INT_MAX;
        int sign = 0;
        if ((divisor > 0 && dividend > 0) || (divisor < 0 && dividend < 0)) sign = 1;
        else sign = -1;
        
        long m = labs(dividend), n = labs(divisor);
        int rslt = 0;
        while (m >= n) {
            long k = n;
            int i = 1;
            while (m >= k) {
                m -= k;
                rslt += i;
                k <<= 1;
                i <<= 1;
            }
        }
        return sign * rslt;
    }
};


int main()
{
	int dividend = -2147483648;

	int divisor = 1;

	Solution slt;
	int d = slt.divide(dividend, divisor);
	return 0;
}
