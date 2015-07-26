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
	/* @note	对十进制数n先自减1，然后不断的模26，所得+'A'就是某一位，然后用n自除26，直到其为0为止。时间复杂度为O(logn)，空间复杂度为O(1)*/
	string convertToTitle(int n) {
		string s;
		while (n > 0)
		{
			n--;
			int k = n % 26;
			s = char('A'+k) + s;
			n /= 26;
		}
		return s;
	}


};

int main()
{
	int n = 702;
	Solution slt;

	string s = slt.convertToTitle(n);
	return 0;
}
