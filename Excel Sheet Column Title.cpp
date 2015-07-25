///@file	Excel Sheet Column Title
/*
Given a positive integer, return its corresponding column title as appear in an Excel sheet.

For example:

1 -> A
2 -> B
3 -> C
...
26 -> Z
27 -> AA
28 -> AB 
*/
///@author	zhaowei
///@date	2015.07.26
///@version	1.0

#include <string>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
	///@brief	将int型正整数转换成二十六进制整数:A, B, C, ..., Z, AA, AB, ...
	///@param	n	十进制整数
	///@return	返回二十六进制数字符串
	/* @note	开辟一个数组存储26^k幂，然后用十进制数n从高到低除这个幂数组，得到的商就是二十六进制的各个位*/
	string convertToTitle(int n) {
		int ts[7] = {0};
		ts[0] = 1;
		for (int i = 1; i < 7; i++)
		{
			int k = 1;
			for (int j = 0; j < i; j++)
				k *= 26;
			ts[i] = k;
		}

		string s;
		for (int i = 6; i >= 0; i--)
		{
			int div = 0;
			if (n > ts[i])
			{
				div = n / ts[i];

				s += char('A' + div - 1);
				
				n %= ts[i];
			}
		}
		//s += char('A' + n - 1);

		return s;
	}
};

int main()
{
	int n = 1;
	Solution slt;

	string s = slt.convertToTitle(n);
	return 0;
}
