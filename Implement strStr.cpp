///@file	Implement strStr()
/*
			Implement strStr().

			Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
*/
///@author	zhaowei
///@date	2015.06.11
///@version	1.0

///@date    2015.09.07
///@version 2.0

///@date	2015.09.22
///@version	2.1

///@date    2016.04.07
///@version 2.2

///@date    September 10, 2018
///@version 3.0

#include <iostream>
#include <string>
using namespace std;

class Solution_v1
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

class Solution_v2 {
public:
	///@brief	计算字符串中指定子串第一次出现的位置
	///@param	haystack	字符串
	///@param	needle		子串
	///@return	返回子串第一次出现的首字符下标
	///@note	用两重循环遍历字符串，外层循环用来作为字符串的起始位置遍历，内层循环用来匹配子串。时间复杂度为O(nk)，其中字符串长度为n，子串长度为k，空间复杂度为O(1)。
    int strStr(string haystack, string needle) {
		if (needle.size() > haystack.size())	return -1;
		if (needle.empty())	return 0;
		int i = 0, j = 0;
		for (i = 0; i <= haystack.size() - needle.size(); i++) {
			for (j = 0; j != needle.size(); j++) {
				if (needle[j] != haystack[i + j])	break;
			}
			if (j == needle.size())	return i;
		}
		return -1;
    }
};

class Solution_v2_2 {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty()) return 0;
        if (needle.size() > haystack.size())    return -1;
        int i = 0, j = 0;
        for (i = 0; i < haystack.size() - needle.size() + 1; i++) {
            for (j = 0; j < needle.size(); j++) {
                if (needle[j] != haystack[i+j])   break;
            }
            if (j == needle.size()) return i;
        }
        return -1;
    }
};

class Solution {
public:
    ///@brief   计算子串needle在主串haystack中第一次出现的下标
    ///@param   haystack    主串
    ///@param   needle      子串
    ///@return  返回子串needle在主串haystack中第一次出现的下标。如果不存在，则返回-1；如果子串为空，则返回0.
    ///@note    1. 双重循环。
    //          2. 时间复杂度为O(mn)，其中m为主串的长度，n为子串的长度。
    int strStr(string haystack, string needle) {
        if (needle.empty())   return 0;
        if (haystack.empty()) return -1;
        for (int i = 0; i < haystack.length(); i++) {
            int k = i;
            for (int j = 0; j < needle.length(); j++) {
                if (haystack[k++] != needle[j])   break;
                if (j == needle.length() - 1)   return k - needle.length();
            }
        }
        return -1;
    }
};

int main()
{
	string s = "hello";
	string n = "ll";
	Solution slt;
	int rslt = slt.strStr(s, n);
	return 0;
}
