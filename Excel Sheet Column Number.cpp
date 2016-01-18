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

///@date	2015.08.13
///@version	2.0

///@date	2016.01.18
///@version	3.0

#include <string>
#include <vector>
#include <cmath>

using namespace std;

class Solution_v1 {
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

class Solution_v2 {
public:
	int titleToNumber(string s) {
		vector<int> pow_of_26;
		double k = 0;
		while (1)
		{
			double l = pow(26, k);
			k = k + 1;
			if (l > INT_MAX)	break;
			pow_of_26.push_back(int(l));
		}
		int rslt = 0;
		if (s.empty())	return rslt;

		int j = 0;
		for (int i = s.size()-1; i >= 0; i--)
			rslt += (s[i] - 'A' + 1) * pow_of_26[j++];
		
		return rslt;
	}
};

class Solution {
public:
	///@brief	将Excel中的列号转换成数字
	///@param	s	字符串
	///@return	返回转换后的数字
	///@note	1. 迭代；2. 从前向后遍历一遍字符串，每次循环都将结果乘以26，相当于向后多一位数，然后再将当前位与'A'的实际差值加到结果数组中去即可。
	//			3. 时间复杂度为O(n)，空间复杂度为O(1)，n为字符串长度。
	int titleToNumber(string s) {
		int rslt = 0;
		for (int i = 0; i != s.size(); i++) {
			rslt *= 26;
			rslt += s[i] - 'A' + 1;
		}
		return rslt;
	}
};

int main()
{
	string s = "BA";
	Solution slt;
	int n = slt.titleToNumber(s);

	Solution_v1 slt_v1;
	n = slt_v1.titleToNumber(s);
	return 0;
}
