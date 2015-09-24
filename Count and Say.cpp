///@file	Count and Say
/*
			The count-and-say sequence is the sequence of integers beginning as follows:
			1, 11, 21, 1211, 111221, ...

			1 is read off as "one 1" or 11.
			11 is read off as "two 1s" or 21.
			21 is read off as "one 2, then one 1" or 1211.
			Given an integer n, generate the nth sequence.

			Note: The sequence of integers will be represented as a string.
*/
///@author	zhaowei
///@date	2015.06.18
///@version	1.0

///@date    2015.09.04
///@version 2.0

///@date	2015.09.24
///@version	2.1
#include <iostream>
#include <string>
using namespace std;

class Solution_v1
{
public:
	///@brief	计算第n个count&say序列元素
	///@param	n	下标
	///@return	返回第n个count&say序列元素
	///@author	zhaowei
	///@date	2015.06.18
	///@note	若元素相邻，则计算连续元素的个数，后续再接上该元素；如果元素不相邻，则直接输出'1'+'该元素'。
	//			时间复杂度为O(n^2)，空间复杂度为O(n).
	string countAndSay(int n)
	{
		string a = "1";
		if (n == 1)
		{
			return a;
		}
		int j = 1;
		while (j != n)
		{
			string b;		//	下一个元素
			int cnt = 1;	//	统计连续数字个数
			for (int i = 0; i != a.length(); i++)
			{
				if (i == a.length()-1)	//	如果是最后一位，则计算出它的连续出现次数和它本身
				{
					b += char(cnt+'0');
					b += a[i];
					cnt = 1;
				}
				else
				{
					if (a[i] == a[i+1])	//	统计连续数字个数
					{
						cnt++;
					}
					else
					{
						b += char(cnt+'0');
						b += a[i];
						cnt = 1;
					}
				}
			}
			a = b;
			j++;
		}
		return a;
	}
};

class Solution {
public:
	///@brief	给定初始字符串“1”，将它念出来并转换成数字字符串，求第n次迭代的结果
	///@param	n	迭代次数
	///@return	返回第n次迭代的结果
	///@note	迭代法。从初始字符串开始迭代，遇到相同的字符就进行计数，直到相邻两字符不同；对于最后一个字符要特殊对待，将累计计数器转化成的数字和它本身添加到结果的末尾。
    string countAndSay(int n) {
		string a = "1";
		int j = 1;
		while (j < n) {
			int cnt = 1;
			string b;
			for (int i = 0; i != a.size(); i++) {
				if (i == a.size() - 1) {
					b += cnt + '0';	//	注意：这种方法生成的字符串可以证明不会有超过4的字符出现
					b += a[i];
					cnt = 1;
				}
				else {
					if (a[i] == a[i + 1])	cnt++;
					else {
						b += cnt + '0';
						b += a[i];
						cnt = 1;
					}
				}
			}
			a = b;
			j++;
		}
		return a;
    }
};

int main()
{
	int n = 0;
	Solution slt;
	string rslt;
	while (cin >> n)
	{
		rslt = slt.countAndSay(n);
		cout << rslt << endl;
	}
	return 0;
}