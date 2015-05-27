///@brief	将整数反转
///@author  zhaowei
///@date	2015.05.27
///@version	1.0
///@note	使用int或者int会有可能不够长，造成除数溢出。对于溢出的情况，直接输出零；另外，就是将末尾为零的情形翻转后要进行舍去。

#include <iostream>
using namespace std;

class Solution {
public:
	long long reverse(long long x) {

		long long i = 1;
		int cnt = 1;
		bool flag = false;
		if (x < 0)
		{
			flag = true;
			x *= -1;
		}
		while (x % (i*10) != x)
		{		
			i *= 10;
			cnt++;
		}


		int *rslt = new int[cnt];
		for (int j = 0; j < cnt-1; j++)
		{	
			long long k = 10;
			for (int t = 0; t < cnt-j-2; t++)
			{
				k *= 10;
			}
			long long tmp = x / k;
			rslt[cnt-j-1] = tmp % 10;
		}
		rslt[0] = x % 10;

		long long r = rslt[cnt-1];
		
		for (int j = cnt-2; j >= 0; j--)
		{
			long long k = 1;
			for (int t = j; t < cnt-1; t++)
			{
				k *= 10;
			}
			r += rslt[j] * k;
		}

		if (flag)
		{
			r *= -1;
		}
		delete []rslt;
		return r;
	}
};

int main()
{
	Solution slt;
	long x = -2147483648;
	
	cout << slt.reverse(x);
	cout << endl;
	return 0;
}