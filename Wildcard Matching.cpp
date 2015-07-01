﻿///@file	Wildcard Matching
/*
			Implement wildcard pattern matching with support for '?' and '*'.

			'?' Matches any single character.
			'*' Matches any sequence of characters (including the empty sequence).

			The matching should cover the entire input string (not partial).

			The function prototype should be:
			bool isMatch(const char *s, const char *p)

			Some examples:
			isMatch("aa","a") → false
			isMatch("aa","aa") → true
			isMatch("aaa","aa") → false
			isMatch("aa", "*") → true
			isMatch("aa", "a*") → true
			isMatch("ab", "?*") → true
			isMatch("aab", "c*a*b") → false
*/
///@author	zhaowei
///@date	2015.06.23
///@version	1.0

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
	///@brief	对带有'*'和'?'两种通配符的字符串进行匹配
	///@param	s	原始字符串
	///@param	p	带有'*'和'?'通配符的字符串
	///@return	如果两个字符串匹配，返回true；否则返回false
	///@note	解题思路是先处理第一个'*'之前和最后一个'*'之后的两部分，然后把中间部分的两个'*'所夹的具体字符串提取出来进行匹配。
	//			如果三者全部都能匹配，就认为两个字符串匹配。这里需要注意将中间部分取出来时，要去掉原始字符串的一头一尾来进行匹配。
	//			另外，对于在候选匹配字符串中非*字符数已经超过原始字符串中的字符数目的情形，应该直接返回false。
	//			时间复杂度为O(n)，空间复杂度为O(1)
	bool isMatch(string s, string p)
	{		
		int normal_char_num = getCharNum(p);	//	计算p中的非*字符数目
		if (normal_char_num > s.size())
		{
			return false;
		}

		vector<int> asterisk = getAsterisk(p);	//	计算p中的*字符下标
		if (asterisk.size() == 0)	//	如果p中没有*号
		{
			if (s.size() != p.size())
			{
				return false;
			}
			return matchWithQuemark(s, p);
		}
		else	//	否则将p分成3部分来处理：头部、尾部和中间部分
		{
			if (!matchHead(s, p, asterisk.front()) || !matchTail(s, p, asterisk.back()))
			{
				return false;
			}
			int s_beg = asterisk.front();
			int s_end = s.size()-(p.size()-asterisk.back());
			for (int i = 0; i != asterisk.size()-1; i++)
			{
				s_beg = matchBody(s, p, s_beg, s_end, asterisk[i], asterisk[i+1]);
				if (s_beg == -1)
				{
					return false;
				}
			}
			return true;
		}
	}

	///@brief	计算字符串中的*位置
	///@param	s	字符串
	///@return	返回包含有字符串中*下标的数组
	vector<int> getAsterisk(string s)
	{
		vector<int> rslt;
		for (int i = 0; i != s.size(); i++)
		{
			if (s[i] == '*')
			{
				rslt.push_back(i);
			}
		}
		return rslt;
	}

	///@brief	计算候选匹配字符串中非*字符的数目
	///@param	s	候选匹配字符串
	///@return	返回候选匹配字符串中非*字符串的数目
	int getCharNum(string s)
	{
		int cnt = 0;
		for (int i = 0; i != s.size(); i++)
		{
			if (s[i] != '*')
			{
				cnt++;
			}
		}
		return cnt;
	}

	///@brief	匹配字符串中第一个*号之前的部分
	///@param	s	原始字符串
	///@param	p	候选匹配的字符串
	///@param	indx	候选匹配的字符串中第一个*出现的下标
	///@return	如果候选匹配的字符串在第一个*出现前的部分能够和原始字符串匹配，则返回true；否则返回false
	bool matchHead(string s, string p, int indx)
	{
		for (int i = 0; i != indx; i++)
		{
			if (p[i] != s[i] && p[i] != '?')
			{
				return false;
			}
		}
		return true;
	}

	///@brief	匹配字符串中最后一个*号之后的部分
	///@param	s	原始字符串
	///@param	p	候选匹配的字符串
	///@param	indx	候选匹配的字符串中最后一个*出现的下标
	///@return	如果候选匹配的字符串在最后一个*出现后的部分能够和原始字符串匹配，则返回true；否则返回false
	bool matchTail(string s, string p, int indx)
	{
		for (int i = s.size()-1, j = p.size()-1; j != indx; i--, j--)
		{
			if (s[i] != p[j] && p[j] != '?')
			{
				return false;
			}
		}
		return true;
	}

	///@brief	匹配字符串中带有*号的中间部分
	///@param	s	原始字符串
	///@param	p	候选匹配的字符串
	///@param	s_beg	原始字符串中开始匹配的字符下标
	///@param	s_end	原始字符串中的结束匹配的字符下标
	///@param	p_beg	候选匹配的字符串中*号出现的下标
	///@param	p_end	候选匹配的字符串中下一个*号出现的下标
	///@return	如果候选匹配的字符串在这两个*出现间的部分能够和原始字符串匹配，则返回原始字符串中的匹配处最后一位下标的后一位；否则返回-1
	int matchBody(string s, string p, int s_beg, int s_end, int p_beg, int p_end)
	{
		string p_body = p.substr(p_beg+1, p_end-p_beg-1);

		//	匹配的范围是除去头尾的中间部分。
		//	而且这里不能用!=来做跳出循环的判定，因为在该函数外部调用时s_beg是随着返回值变动的。
		for (int i = s_beg; i <= s_end-p_body.size()+1; i++)		
		{
			string s_body = s.substr(i, p_body.length());
			if (matchWithQuemark(s_body, p_body))
			{
				return i+s_body.length();
			}
		}
		return -1;
	}

	///@brief	判断带有'?'的两个等长的字符串是否匹配
	///@param	s	原始字符串
	///@param	p	带有'?'的字符串
	///@return	如果匹配，返回true，否则返回false
	bool matchWithQuemark(string s, string p)
	{
		for (int i = 0; i != s.size(); i++)
		{
			if (s[i] != p[i] && p[i] != '?')
			{
				return false;
			}
		}
		return true;
	}
};

int main()
{
	string a, b;
	Solution slt;
	while (cin >> a >> b)
	{
		cout << slt.isMatch(a, b);
		cout <<	endl;
	}
	return 0;
}