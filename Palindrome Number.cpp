///@brief	判断一个int型整数是否是回文数
///@author  zhaowei
///@date	2015.05.31
///@version	1.0

#include <iostream>
using namespace std;

class Solution
{
public:
	///@brief	判断一个int型整数是否是回文数
	///@param	x	整数
	///@return	如果是回文数，返回true；否则返回false
	///@author	zhaowei
	///@date	2015.05.31
	/* @note	1. 对于负数，判定为false；
				2. 整体思路是将x的每一位都取出来，然后依次比较判断。
				3. 需要两个数组，一个数组是用来判断x的长度和取每一位的整十倍数组，共10个；另一个数组用来保存每一位。
				4. 判定时从两头向中间走，判断每一对位是否相等。

	*/
	bool isPalindrome(int x) {
		int unit[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

		if (x == 0)	//如果x为0，返回true
		{
			return true;
		}

		if (x < 0)	//如果x小于0，返回false
		{
			return false;
		}

		int int_len = 0;	//x的位数
		for (int i = 0; i < 9; i++)
		{
			if (x < unit[i+1] && x >= unit[i])
			{
				int_len = i+1;
				break;
			}
		}

		if (int_len == 0)
		{
			int_len = 10;
		}

		int int_arr[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

		for (int i = 0; i < int_len; i++)	//计算x的每一位，将其保存到int_arr[]中
		{
			int_arr[i] = x/unit[int_len-i-1];
			int_arr[i] %= unit[1];	//上一步算出来的结果的最后一位就是int_arr[i]的值，故模10.
		}

		for (int i = 0; i < int_len; i++)	//判断int_arr[]是否是回文数
		{
			if (int_arr[i] != int_arr[int_len-i-1])
			{
				return false;
			}
		}

		return true;
	}
};
int main()
{
	int x = 1;
	Solution slt;
	cout << slt.isPalindrome(x) << endl;
	return 0;
}