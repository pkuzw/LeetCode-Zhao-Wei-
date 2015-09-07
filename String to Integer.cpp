///@brief	自己实现atoi函数
///@author	zhaowei
///@date	2015.05.28
///@version	1.0

///@date    2015.09.07
///@version 2.0

#include <iostream>
#include <string>
using namespace std;

class Solution_v1
{
public:
	///@brief	将string类型的字符串转换成int型
	///@author	zhaowei
	///@date	2015.05.31
	/* @note    通过leetcode上给的提示，结合自己在vc2010上运行系统给的atoi()函数实验，明确了如下边界条件：
				1. atoi()会将开始的所有空白字符舍弃；
				2. 如果接下来的非空白字符中是符号('+', '-')或者是数字，则对其进行转换。转换过程中会舍弃开始的连续若干个'0'；
				3. 如果在处理完数字后，字符串还有若干非数字字符，包括字母、空白符和其他符号，则忽略；
				4. 如果这些转换后的数字超过了int型表示的范围-2147483648 ~ 2147483647，则返回最邻近的边界范围值；
				5. 如果字符串中没有有效数字，即最开始的若干非空白字符就是字母或者其他字符，或者只有空白符，则返回0.
	*/	
	int myAtoi(string str)
	{
		int len = str.length();
		if (len == 0)	//空字符串返回0
		{
			return 0;
		}
		bool sign_ = false;	//符号标识符
		int valid_bit = 0;	//有效数字开始的下标位置

		while (valid_bit < len && (str[valid_bit] == ' ' || str[valid_bit] == '	') )	//寻找第一个有效数字的下标
		{
			valid_bit++;
		}

		if (valid_bit == len)	//如果字符串完全由空白符组成，返回0
		{
			return 0;
		}

		if (str[valid_bit] == '-')	//判断字符串数字的符号
		{
			sign_ = true;
		}
		else if (str[valid_bit] == '+' || (str[valid_bit] >= '0' && str[valid_bit] <= '9'))
		{
			sign_ = false;
		}
		else
			return 0;
		

		//统计字符串首部的连续0的个数
		int integer_arr[1000] = {0};	//保存有效数字的数组
		for (int i = 0; i < 1000; i++)	//对数组初始化
		{
			integer_arr[i] = -1;
		}
		if (str[valid_bit] == '+' || str[valid_bit] == '-')	//如果有符号位，则valid_bit自增1
		{
			if (valid_bit < len-1)	
			{
				valid_bit++;				
			}
			else
			{
				return 0;
			}				
		}
		else if (str[valid_bit] == '0')	//统计连续出现的首部0的个数
		{	
			while (str[valid_bit] == '0')
			{
				valid_bit++;
			}
		}

		int arr_index = 0;
		while(valid_bit < len && str[valid_bit] >= '0' && str[valid_bit] <= '9')	//将有效数字存入int数组
		{
			
			integer_arr[arr_index++] = str[valid_bit]-'0';
			valid_bit++;
		}

		if (arr_index > 10)	//判断有效数字越界的情况
		{
			if (sign_)
			{
				return INT_MIN;
			}
			return INT_MAX;
		}
		if (arr_index == 10)
		{
			if (integer_arr[0] > 2
				|| (integer_arr[0] == 2 && integer_arr[1] > 1)
				|| (integer_arr[0] == 2 && integer_arr[1] == 1 && integer_arr[2] > 4)
				|| (integer_arr[0] == 2 && integer_arr[1] == 1 && integer_arr[2] == 4 && integer_arr[3] > 7) 
				|| (integer_arr[0] == 2 && integer_arr[1] == 1 && integer_arr[2] == 4 && integer_arr[3] == 7 && integer_arr[4] > 4)
				|| (integer_arr[0] == 2 && integer_arr[1] == 1 && integer_arr[2] == 4 && integer_arr[3] == 7 && integer_arr[4] == 4 && integer_arr[5] > 8)
				|| (integer_arr[0] == 2 && integer_arr[1] == 1 && integer_arr[2] == 4 && integer_arr[3] == 7 && integer_arr[4] == 4 && integer_arr[5] == 8 && integer_arr[6] > 3)
				|| (integer_arr[0] == 2 && integer_arr[1] == 1 && integer_arr[2] == 4 && integer_arr[3] == 7 && integer_arr[4] == 4 && integer_arr[5] == 8 && integer_arr[6] == 3 && integer_arr[7] > 6)
				|| (integer_arr[0] == 2 && integer_arr[1] == 1 && integer_arr[2] == 4 && integer_arr[3] == 7 && integer_arr[4] == 4 && integer_arr[5] == 8 && integer_arr[6] == 3 && integer_arr[7] == 6 && integer_arr[8] > 4)
				|| (integer_arr[0] == 2 && integer_arr[1] == 1 && integer_arr[2] == 4 && integer_arr[3] == 7 && integer_arr[4] == 4 && integer_arr[5] == 8 && integer_arr[6] == 3 && integer_arr[7] == 6 && integer_arr[8] == 4 && integer_arr[9] > 7)
				)
			{
				if (sign_)
				{
					return INT_MIN;
				}
				return INT_MAX;
			}
		}
		if (arr_index <= 10)	//将不越界的int数组中的数字转换成int型变量
		{
			int rslt = 0;
			int multiple[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
			for (int i = 0; i < arr_index; i++)
			{
				rslt += integer_arr[i] * multiple[arr_index-i-1];
			}
			if (sign_)
			{
				rslt *= -1;
			}
			return rslt;
		}
		return 0;
	}

};

class Solution {
public:
    int atoi(const char *str) {
        if (!str) return 0;
        int res = 0;
        int left = 0;
        bool isPositive = true;
        while (str[left] == ' ') ++left;
        if (str[left] == '-' || str[left] == '+') {
            if (str[left] == '-') isPositive = false;
            ++left;
        }
        if (str[left] < '0' || str[left] >'9') return 0;
        while (str[left] >= '0' && str[left] <= '9') {
            if (res > INT_MAX / 10 || (res == INT_MAX / 10 && str[left] - '0' >= 8)) {
                return isPositive ? INT_MAX : INT_MIN;
            }
            res = res * 10 + str[left] - '0';
            ++left;
        }
        if(isPositive) return res;
        else return -res;
    }
};

int main()
{
	const char* s = "001 01";//"   2147483647stt";
	int n = atoi(s);
	cout << n << endl;

	string s1 = "2147483647";
//	string s2 = "1";
	//getline(cin, s1);
	Solution_v1 slt;

 	cout << slt.myAtoi(s1) << endl;
// 	cout << slt.myAtoi(s2) << endl;
	return 0;
}