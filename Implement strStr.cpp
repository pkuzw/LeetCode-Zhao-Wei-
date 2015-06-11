///@file	Implement strStr()
/*
			Implement strStr().

			Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
*/
///@author	zhaowei
///@date	2015.06.11
///@version	1.0

#include <iostream>
#include <string>
using namespace std;

class Solution
{
public:
	///@brief	寻找字符串中子串第一次出现的下标
	///@param	haystack	字符串
	///@param	needle		子串
	///@return	如果子串存在，则返回第一次出现的下标；否则返回-1
	///@note	注意处理边界条件
	int strStr(string haystack, string needle) {
		int indx = -1;

		if (haystack.empty() && needle.empty())
			indx = 0;
		
		for (int i = 0; i != haystack.length(); i++)
		{
			if (isEqualStr(haystack, i, needle))
			{
				indx = i;
				break;
			}
		}
		return indx;
	}

private:
	///@brief	判断两个字符串是否相等
	///@param	haystack	字符串1
	///@param	b			字符串1中开始比较的下标
	///@param	needle		字符串2
	///@return	如果字符串1中存在字符串2，则返回true；否则返回false
	bool isEqualStr(string haystack, int b, string needle)
	{
		int len = needle.length();
		if (b+len > haystack.length())
		{
			return false;
		}

		bool rslt = true;
		for (int i = 0; i != len; i++)
		{
			if (haystack[b+i] != needle[i])
			{
				rslt = false;
				break;
			}
		}
		return rslt;
	}
};

int main()
{
	string s = "";
	string n = "";
	Solution slt;
	cout <<slt.strStr(s, n) << endl;
	return 0;
}