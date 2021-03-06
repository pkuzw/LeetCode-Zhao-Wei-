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

///@date    2015.09.04
///@version 2.0

///@date	2015.09.24
///@version	2.1

///@date	2016.04.11
///@version	2.2

///@date    October 20, 2018
///@version 2.3

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution_v1
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

class Solution_v2 {
public:
	///@brief	带有通配符字符串的匹配。'*'可以匹配任意字符串，包括空串；'?'可以匹配任意单个字符，但不可以是空字符。
	///@param	s	待匹配的字符串
	///@param	p	有通配符的字符串
	///@return	如果s和p匹配，则返回true；否则返回false
	///@note	1. 逐个字符向后匹配。
	//			2. 用两个变量m和n分别保存当遇到通配符'*'时，i和j在s和p中的下标，当s[i]和p[j]不匹配且p[j]不为'?'，在存在通配符'*'的条件下，就将i更新到++m
	//			（这里不能是m + 1，因为需要不断的向后尝试抵消不匹配的s中子串，这是最巧妙的一点），将j更新到n + 1.如果还是不匹配，则返回false。当遍历完s后，如果p还有剩余子串，
	//			除非都是'*'，否则也是false。
	//			3. 这里需要注意的是每次用i或j访问字符串中字符时，需要保证其不越界。	
    bool isMatch(string s, string p) {
		int i = 0;	//	s的下标
		int j = 0;	//	p的下标
		int m = -1;	//	通配符"*"在s中的下标
		int n = -1;	//	通配符"*"在p中的下标
		while (i < s.size()) {
			if (j < p.size() && (s[i] == p[j] || p[j] == '?')) {
				i++;
				j++;
			}
			else if (j < p.size() && p[j] == '*') {
				m = i;
				n = j++;				
			}
			else if (m >= 0) {	//	存在通配符"*"，则可以将s中之前不匹配的子串都与之相抵，非常巧妙
				i = ++m;
				j = n + 1;
			}
			else return false;
		}
		while (j < p.size() && p[j] == '*')	j++;	//	如果s已经匹配完毕，p还有剩余的话，除非全部都是'*'，否则二者不匹配
		return j == p.size();
    }
};

class Solution {
public:
    ///@brief   给定两个字符串s和p，其中s只含有小写字母，p除了含有小写字母之外，还可能含有通配符'?'和'*'，'?'可以表示任意字符，但不能表示空字符，'*'可以表示任意字符串，包括空字符。
    //          判断p能否表示s。
    ///@param   s   字符串s
    ///@param   p   字符串p
    ///@return  如果字符串p可以表示字符串s，那么返回true；否则返回false。
    ///@note    1. 枚举遍历
    ///         2. 设i，j分别为字符串s和p的循环变量，m和n分别是当p[j] == '*'时，i和j的值；
    //          3. 如果s[i] == p[j] || s[i] == '?'，那么i和j都分别自增，循环继续；
    //          4. 如果p[j] == '*'，那么就令m = i, n = j，然后继续遍历；
    //          5. 如果s[i] != p[j] && p[j] != '*' &&& p[j] != '?'，那么就看n是否已经指向了有效的'*'（即可以通过'*'来抵消掉s中不匹配的子串）。如果是，则继续增加m值，然后通过m来更新i
    //             如果不是，那么就返回false；
    //          6. 最后返回时要看j是否遍历完了所有的p中元素，除非p的末尾都是'*'，否则如果j没有遍历完p中元素，返回false；
    //          7. 时间复杂度为O(m)，空间复杂度为O(1)，其中m是s的长度。
	bool isMatch(string s, string p) {
        int i = 0, j = 0;
        int m = -1, n = 1;
        while (i < s.length()) {
            if (j < p.length() && (s[i] == p[j] || p[j] == '?')) {
                i++;
                j++;
            }
            else if (j < p.length() && p[j] == '*') {
                m = i;
                n = j++;
            }
            else if (m >= 0) {
                i = ++m;
                j = n + 1;
            }
            else return false;
        }
        while (j < p.length() && p[j] == '*')   j++;
        return j == p.length();
	}
};

int main()
{
	string a, b;
	Solution slt;
	while (cin >> a >> b)
	{
		string rslt = slt.isMatch(a, b) ? "Yes" : "No";
		cout << rslt;
		cout <<	endl;
	}
	return 0;
}
