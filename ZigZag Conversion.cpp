///@brief	将多行带空格的字符串转换成不带空格的单行字符串
///@author  zhaowei
///@date	2015.05.27
///@version	1.0
#include <iostream>
#include <string>
using namespace std;

class Solution
{
public:
	///@brief	将原本纵向阅读的之字形字符串转换成横向阅读的字符串
	///@param	s	待处理的字符串
	///@param	numRows	之字形矩阵的行数
	///@return	转换后的字符串
	///@author	zhaowei
	///@date	2015.05.27
	///@status	在leetcode上报internal error，应该还有别的方法。
	string convert(string s, int numRows) {

		if (numRows > 1)	//如果大于一行，则转换为二维数组矩形
		{

			int len = s.length();

			char zigzag[50][50];
			for (int i = 0; i < 50; i++)
			{
				for (int j = 0; j < 50; j++)
				{
					zigzag[i][j] = ' ';
				}
			}

			string rstr;
			int k = 0;			//原字符串下标
			for (int j = 0; j < len/2+1; j++)		
			{
				for (int i = 0; i < numRows; i++)
				{
					if (j % (numRows-1) == 0)	//如果是第(numRows-1)的倍数列，则将该列填满
					{
						if (k != len-1)
							zigzag[i][j] = s[k++];
					}
					else						//否则通过关系式i + j%(numRows-1) == numRows-1来填对应的字符
					{
						if (k != len-1 && i + j%(numRows-1) == numRows-1)
							zigzag[i][j] = s[k++];
					}

				}
			}
			//消除空白字符
			for (int i = 0; i < numRows; i++)
			{
				for (int j = 0; j < len/2+1; j++)
				{
					if (zigzag[i][j] != ' ')
					{
						rstr += zigzag[i][j];
					}
				}
			}

			string rstr_2;
			for (int i = 0; i < rstr.length(); i++)
			{
				if (rstr[i] != ' ')
				{
					rstr_2 += rstr[i];
				}
			}
			return rstr_2;
		}
		else
		{
			return s;
		}
	}
};
int main()
{
	string t = "";
	int nrows = 1;
	
	Solution slt;
	string rslt = slt.convert(t, nrows);	


	cout << rslt << endl;

	return 0;
}