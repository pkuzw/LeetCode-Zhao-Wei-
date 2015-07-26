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
	///@brief	将二十六进制整数:A, B, C, ..., Z, AA, AB转换成十进制整型变量
	///@param	s	二十六进制整数
	///@return	返回十进制整数
	/* @note	开辟一个数组存储26^k幂，然后用二十六进制的各个位上的字符乘以这个幂数组，然后将积相加即可。时间复杂度为O(n)，空间复杂度为O(n)。*/
	
	int titleToNumber(string s) {		
		int slen = s.length();
		int ts[7] = {0};
		ts[0] = 1;
		for (int i = 1; i < 7; i++)
		{
			int k = 1;
			for (int j = 0; j < i; j++)
				k *= 26;
			ts[i] = k;
		}

		int rslt = 0;
		for (int i = 0; i < slen; i++)
		{
			int k = 1;
			k = (s[i]-'A'+1) * ts[slen-i-1];
			rslt += k;
		}

		return rslt;
	}
};

int main()
{
	string s = "ZZZZZZ";
	Solution slt;

	int n = slt.titleToNumber(s);
	return 0;
}
