///@brief	将多行带空格的字符串转换成不带空格的单行字符串
///@author  zhaowei
///@date	2015.05.27
///@version	1.0

///@date    2015.09.07
///@version 2.0

///@date	2015.09.11
///@version	2.1

///@date	2016.04.01
///@version	2.2

///@date    June 21, 2018
///@version 2.3

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

class Solution_v2 {
public:
	///@brief	将原本的之字形字符串转换成横行输出
	///@param	s	原来的之字形字符串
	///@param	nRows	行数
	///@return	返回成行输出的字符串
	///@note	通过观察可知，当按行输出时，相邻的两个字符是按照之字形输出相差2*(nRows - 1)的距离。如果是非首行和非末行，则还要减去2倍的行数。时间复杂度为O(n)，空间复杂度为O(n)。
    string convert(string s, int nRows) {
		if (nRows <= 1)	return s;
		int size = 2 * (nRows - 1);
		string rslt = "";
		for (int i = 0; i != nRows; i++) {
			for (int j = i; j < s.size(); j += size) {
				rslt += s[j];
				int tmp = j + size - 2 * i;
				if (tmp < s.size() && i != 0 && i != nRows - 1)	rslt += s[tmp];
			}
		}
		return rslt;
    }
};

class Solution_v2_1 {
public:
	///@note	1. 横向来看，相邻的两字符间距为2*(行数-1)，对于非首行和非末行的相邻字符，其间距再减少2*行号。
	string convert(string s, int nRows) {
		if (nRows <= 1)	return s;
		int interval = 2 * (nRows - 1);
		string rslt;
		for (int i = 0; i != nRows; i++) {
			for (int j = i; j < s.size(); j += interval) {
				rslt += s[j];
				int tmp = j + interval - 2*i;
				if (tmp < s.size() && i != 0 && i != nRows - 1)	rslt += s[tmp];
			}
		}
		return rslt;
	}
};

class Solution {
public:
    ///@brief   将字符串写为“之”字形，然后逐行输出，产生新的字符串。
    ///@param   s       字符串s
    ///@pram    numRows 之字形的字符串行数
    ///return   返回新的之字形字符串的逐行输出的结果
    ///@note    1. 通过观察发现，之字形字符串在首行和末行的相邻字符之间的下标差为2 * numRows - 2。
    //          2. 其余各行i在竖直两列之间还插有一个额外的字符，该字符和两个竖直列中靠后的同一行的字符的下标差为2 * i。
    //          3. 时间复杂度为O(n)，空间复杂度为O(1),n为字符串长度。
    string convert(string s, int numRows) {
        if (numRows <= 1 || s.length() == 1 || s.empty())   return s;
        string rslt =  "";
        int gap = 2 * (numRows - 1);
        for (int i = 0; i < numRows; i++) {
            for (int j = i; j < s.length(); j += gap) {
                rslt += s[j];   //  在这里向结果字符串添加竖列的字符
                int mid = j + gap - 2 * i;
                if (i > 0 && i < numRows - 1 && mid < s.length())
                    rslt += s[mid]; //  在这里向结果字符串添加两数列所夹的字符
            }
        }
        return rslt;
    }
};

int main()
{
	string t = "PAYPALISHIRING";	// rslt = PAHNAPLSIIGYIR
    t = "ABCDEFGH";
	int nrows = 3;
	
	Solution slt;
	string rslt = slt.convert(t, nrows);	

    cout << t.length() << endl;
	cout << rslt << endl;

	return 0;
}
