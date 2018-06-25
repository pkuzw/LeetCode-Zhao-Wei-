///@brief	判断一个int型整数是否是回文数
///@author  zhaowei
///@date	2015.05.31
///@version	1.0

///@date    2015.09.07
///@version 2.0

///@date	2015.09.13
///@version	2.1

///@date	2015.09.13
///@version	3.0

///@date	2016.04.01
///@version	2.2

///@date    June 25, 2018
///@version 2.3

#include <iostream>
#include <string>
using namespace std;

class Solution_v1
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

class Solution_v3 {
public:
	///@brief	判断一个整型变量是否回文
	///@param	x	整型变量
	///@return  如果该整型变量回文，则返回true；否则返回false
	///@note	1. 利用string函数的to_string函数和模版中的reverse函数，将原来的整型变量转换成字符串，再划成两半进行比较。
	//			2. 时间复杂度O(n)，空间复杂度为O(n)。
	bool isPalindrome(int x) {
		if (x < 0)	return false;
		string str = to_string(static_cast<long long>(x));
		int len = str.size();
		if (len == 1)	return true;
		int half = len / 2;
		string left, right;
		if (len % 2) {
			left = str.substr(0, half);
			right = str.substr(half + 1, half);			
		}
		else {
			left = str.substr(0, half);
			right = str.substr(half, half);
		}
		reverse(right.begin(), right.end());
		return left == right;
	}
};

class Solution_v2 {
public:
	///@brief	判断一个整型变量是否回文
	///@param	x	整型变量
	///@return  如果该整型变量回文，则返回true；否则返回false
	///@note	利用求模和除法运算来逐位比较。时间复杂度为O(n)，空间复杂度为O(1)。
	bool isPalindrome(int x) {
		if (x < 0)	return false;
		int div = 1;
		while (x / div >= 10)	div *= 10;
		while (x) {
			int left = x / div;	//	左半部分
			int right = x % 10;	//	右半部分
			if (left != right)	return false;
			x = (x % div) / 10;	//	去掉首尾数字
			div /= 100;			//	将div也要相应减少2位
		}
		return true;
	}
};

class Solution_v2_1 {
public:
	///@note	1. 在缩小x的过程中应该是先去头，再去尾，相对简洁一些。
	//			2. 对于负数，直接返回false。
	bool isPalindrome(int x) {
		int div = 1;
		while (x / div >= 10)	div *= 10;
		while (x) {
			int head = x / div;
			int tail = x % 10;
			if (head != tail)	return false;
			//	便于和上面版本比较，此处为先去尾，再去头
			x /= 10;
			div /= 10;
			x = div == 0 ? x : x % div;
			div /= 10;
		}
		return true;
	}
};

class Solution {
public:
    ///@brief   计算给定数字是否为回文数，即从左到右读和从右向左读是一样的。
    ///@param   x   整形数字
    ///@return  如果给定数字x是回文数，则返回true；如果给定数字x不是回文数，则返回false。
    ///@note    1. 通过除数div的模运算和除数为10的除法运算来获取x的首尾两数字，如果二者相等，则将div乘以100，即扩充2位，循环直至x变为0.
    ///         2. 时间复杂度为O(1)，空间复杂度为O(1)，因为整型数字的长度固定，其不可能超过10位。
    bool isPalindrome(int x) {
        if (x < 0)  return false;
        int div = 1;
        while (x / div >= 10) div *= 10;
        while (x > 0) {
            int left = x / div;
            int right = x % 10;
            if (left == right) {
                x = (x % div) / 10;
                div /= 100;
            }
            else    return false;
        }
        return true;
    }
};

int main()
{
	int x = 154515451;
	Solution slt;
	bool rslt = slt.isPalindrome(x);
	return 0;
}
