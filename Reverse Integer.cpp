///@brief	将整数反转
///@author  zhaowei
///@date	2015.05.27
///@version	1.0
///@note	使用int或者int会有可能不够长，造成除数溢出。对于溢出的情况，直接输出零；另外，就是将末尾为零的情形翻转后要进行舍去。

///@date    2015.09.07
///@version 2.0

///@date	2015.09.12
///@version	2.1

///@date	2016.04.01
///@version	2.2

#include <iostream>
#include <string>
using namespace std;

class Solution_v1 {
public:
	///@brief	将整数x反转输出
	///@param	x	待反转的整数
	///@return	如果翻转后的整数开始有0，应该略去；如果整数超过了int表示的范围，则直接输出0
	///@author	zhaowei
	///@date	2015.05.28
	int reverse(int x) {

		int i = 1;
		int cnt = 1;	//记录整数x的位数
		bool flag = false;	//标记x的符号，true为负
		bool flag2 = false;	//标记x是否为10位数


		if (x == -2147483648)	//因为x的整型表示范围-2147483648 ~ 2147483647，所当x = -2147483648时，无法通过乘以-1来将其转换成整数，这样就溢出了。
		{
			return 0;
		}

		if (x / 1000000000 != 0)	//如果x是10位数，则将flag2标记为true
		{
			flag2 = true;
		}
	
		
		if (x < 0)		//如果x为负数，则将flag标为true，并取其绝对值
		{
			flag = true;
			x *= -1;
		}

		if (flag2)		//如果x为10位数，则直接将cnt值为10，否则在下面计算x的位数代码里会造成i溢出。因为不可能存在一个int型的变量i使得x对其取模等于它本身。
		{
			cnt = 10;
		}
		else
		{
			while (x % (i*10) != x)	//计算x的位数
			{		
				i *= 10;
				cnt++;
			}
		}


		int *rslt = new int[cnt];	//将x的各位反转后保存在数组rslt中
		for (int j = 0; j < cnt-1; j++)
		{	
			int k = 10;
			for (int t = 0; t < cnt-j-2; t++)
			{
				k *= 10;
			}
			int tmp = x / k;
			rslt[cnt-j-1] = tmp % 10;
		}
		rslt[0] = x % 10;


		if (flag2)	//对于x有10位长的情况，逐个判断其翻转后是否超过了x的表示范围。只有10位数存在这种溢出的可能。10位以下不可能。
		{
			if (rslt[0] > 2 || (rslt[0] == 2 && rslt[1] > 1) || (rslt[0] == 2 && rslt[1] == 1 && rslt[2] > 4)
				|| (rslt[0] == 2 && rslt[1] == 1 && rslt[2] == 4 && rslt[3] > 7) 
				|| (rslt[0] == 2 && rslt[1] == 1 && rslt[2] == 4 && rslt[3] == 7 && rslt[4] > 4)
				|| (rslt[0] == 2 && rslt[1] == 1 && rslt[2] == 4 && rslt[3] == 7 && rslt[4] == 4 && rslt[5] > 8)
				|| (rslt[0] == 2 && rslt[1] == 1 && rslt[2] == 4 && rslt[3] == 7 && rslt[4] == 4 && rslt[5] == 8 && rslt[6] > 3)
				|| (rslt[0] == 2 && rslt[1] == 1 && rslt[2] == 4 && rslt[3] == 7 && rslt[4] == 4 && rslt[5] == 8 && rslt[6] == 3 && rslt[7] > 6)
				|| (rslt[0] == 2 && rslt[1] == 1 && rslt[2] == 4 && rslt[3] == 7 && rslt[4] == 4 && rslt[5] == 8 && rslt[6] == 3 && rslt[7] == 6 && rslt[8] > 4)
				|| (rslt[0] == 2 && rslt[1] == 1 && rslt[2] == 4 && rslt[3] == 7 && rslt[4] == 4 && rslt[5] == 8 && rslt[6] == 3 && rslt[7] == 6 && rslt[8] == 4 && rslt[9] > 7)
				)
				return 0;			
		}

		int r = rslt[cnt-1];		//将rslt中的各元素依次整合到r中，并输出
		
		for (int j = cnt-2; j >= 0; j--)
		{
			int k = 1;
			for (int t = j; t < cnt-1; t++)
			{
				k *= 10;
			}
			r += rslt[j] * k;
		}

		if (flag)	//如果x为负，则将原有的结果转换为负。
		{
			r *= -1;
		}
		delete []rslt;
		return r;
	}
};

class Solution_v2 {
public:
	///@brief	将一个int型变量翻转
	///@param	x	int型变量
	///@return	返回翻转后的x
	///@note	这里需要注意：由于int型变量的范围是-2147483648 ~ 2147483647，所以对于如果是10位的整数，末位为大于2的情形，翻转后肯定会越界。
	//			所以在每次翻转累加前都要检查是否可能溢出，如果会溢出，则直接返回0.时间复杂度为O(logn)，空间复杂度为O(1)。
    int reverse(int x) {
 		int rslt = 0;
 		while (x) {
 			if (abs(rslt) > INT_MAX / 10)	
				return 0;
 			rslt = rslt * 10 + x % 10;
 			x /= 10;
 		}
 		return rslt;
    }

	///@brief	将一个int型变量翻转
	///@param	x	int型变量
	///@return	翻转后的int型变量
	///@note	利用string类中的reverse函数，先将int型变量转换成string型，然后调用reverse函数，最后再添加符号转换成int型变量
	int reverse_str(int x) {
		int sign = x < 0 ? -1 : 1;
		string s = to_string(static_cast<long long>(abs(x)));
		std::reverse(s.begin(), s.end());
		if (s.size() >= 10 && s > "2147483647")	return 0;	//	防止溢出
		int rslt = stoi(s);
		rslt *= sign;
		return rslt;
	}
};

class Solution {
public:
	///@note	1. 利用long long来防止中间过程整型变量越界
	int reverse(int x) {
		long long rslt = 0;
		while (x) {
			rslt = rslt * 10 + x % 10;
			x /= 10;
		}
		return rslt > INT_MAX || rslt < INT_MIN ? 0 : (int)rslt;
	}
};

int main()
{
	Solution slt; 
	int x = INT_MAX;
	
	int rslt = slt.reverse(x);
	return 0;
}