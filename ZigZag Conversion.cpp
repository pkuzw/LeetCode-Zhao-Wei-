﻿///@brief	将多行带空格的字符串转换成不带空格的单行字符串
///@author  zhaowei
///@date	2015.05.27
///@version	1.0

///@date    2015.09.07
///@version 2.0

#include <iostream>
#include <string>
using namespace std;

class Solution_v1
{
public:
	///@brief	将原本纵向阅读的之字形字符串转换成横向阅读的字符串
	///@param	s	待处理的字符串
	///@param	numRows	之字形矩阵的行数
	///@return	转换后的字符串
	///@author	zhaowei
	///@date	2015.05.27
	///@status	在leetcode上报internal error，应该还有别的方法。
	///@note	模拟二维矩形来保存字符
	string convert1(string s, int numRows) {

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
	///@brief	将原本纵向阅读的之字形字符串转换成横向阅读的字符串
	///@param	s	待处理的字符串
	///@param	numRows	之字形矩阵的行数
	///@return	转换后的字符串
	///@author	zhaowei
	///@date	2015.05.27
	///@note	通过观察发现，这个之字形的字符串之间是有间隔来读取的，如果行号是i，那么第一行和最后一行的字符相隔的间距是2*(numRows-1)；
	//			中间各行的间距分别是2*(numRows-i-1)和2*i。这样按照两种情况进行读取即可。
	string convert(string s, int numRows) {
		string rstr;
		if (numRows == 1)	//如果行数是1直接返回
		{
			return s;
		}

		for (int i = 0; i < numRows; i++)
		{
			int j = 0;
			if (i == 0 || i == numRows-1)	//如果是首行和末行的情况，每个字符的间距相等，都是2*(numRows-1)
			{
				j = i;
				while (j < s.length())
				{
					rstr += s[j];
					j += 2*(numRows-1);
				}				
			}
			else							//中间各行的情况不一样，每numRows列中间又夹着一个字符，需要分两次处理
			{
				j = i;
				while (j < s.length())
				{
					rstr += s[j];
					j += 2*(numRows-i-1);
					if (j >= s.length())	//注意判定不要越界
					{
						break;
					}
					rstr += s[j];
					j += 2*i;
				}
			}
		}
		return rstr;
	}
};

class Solution {
public:
    string convert(string s, int nRows) {
        if (nRows <= 1) return s;
        string res = "";
        int size = 2 * nRows - 2;
        for (int i = 0; i < nRows; ++i) {
            for (int j = i; j < s.size(); j += size) {
                res += s[j];
                int tmp = j + size - 2 * i;
                if (i != 0 && i != nRows - 1 && tmp < s.size()) res += s[tmp];
            }
        }
        return res;
    }
};

int main()
{
	string t = "PAYPALISHIRING";
	int nrows = 3;
	
	Solution slt;
	string rslt = slt.convert(t, nrows);	


	cout << rslt << endl;

	return 0;
}