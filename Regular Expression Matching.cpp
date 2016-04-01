///@brief	正则表达式匹配，支持'.'和'*'
///@author	zhaowei
///@date	2015.06.01
///@version	1.0
/* @note	'.' Matches any single character.
			'*' Matches zero or more of the preceding element.

			The matching should cover the entire input string (not partial).

			The function prototype should be:
			bool isMatch(const char *s, const char *p)

			Some examples:
			isMatch("aa","a") → false
			isMatch("aa","aa") → true
			isMatch("aaa","aa") → false
			isMatch("aa", "a*") → true
			isMatch("aa", ".*") → true
			isMatch("ab", ".*") → true
			isMatch("aab", "c*a*b") → true

*/

///@date    2015.09.07
///@version 2.0

///@date	2015.09.14
///@version	2.1

///@date	2015.09.14
///@version	3.0

///@date	2016.04.01
///@version	3.1

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution_v1
{
public:
	///@brief	正则表达式匹配
	///@param	s	表达式1
	///@param	p	表达式2
	///@return	如果s和p能够匹配，则返回true；否则返回false
	///@author	zhaowei
	///@date	2015.06.01
	///@note	这个函数这么写，没法处理"aaa"与"ab*a*c*a"的匹配。如果有多个可重复出现的字符连续出现，则无法处理。
	bool isMatch_1(string s, string p) {
		int s_len = s.length();
		int p_len = p.length();

		int i = 0, j = 0;	//i:记录s中的字符下标; j:记录p中的字符下标
		int p_cnt = 0;		//记录p中被匹配的次数

		bool wildcard = false;	//记录p中是否存在'*'
		bool is_matched = false;

		bool *s_match = new bool[s_len];
		bool *p_match = new bool[p_len];
		for (int k = 0; k < s_len; k++)
		{
			s_match[k] = false;
		}
		for (int k = 0; k < p_len; k++)
		{
			p_match[k] = false;
		}

		for (i = 0, j = 0; i < s_len && j < p_len; i++)
		{
			if (s[i] == p[j])
			{				
				s_match[i] = true;
				p_match[j] = true;
				j++;
				p_cnt++;
			}
			else if (p[j] == '.')
			{
				s_match[i] = true;
				p_match[j] = true;
				j++;
				p_cnt++;
			}
			else if (p[j] == '*' && j < p_len-1 && s[i] == p[j+1])	//优先判断通配符.*之后的字符是否匹配
			{
				wildcard = true;
				s_match[i] = true;
				p_match[j+1] = true;
				j++;
				p_cnt++;
				
			}
			else if (p[j] == '*' && j >= 1 && (p[j-1] == '.' || p[j-1] == s[i]))		//如果通配符.*之后没有相应的字符对应，再来判断通配符是否满足匹配
			{
				s_match[i] = true;
				p_match[j-1] = true;
				p_cnt++;		
				wildcard = true;
			}
			else if (j < p_len-1 && p[j+1] == '*')	//某个重复出现的字符可以出现零次，跳到后面的字符进行匹配
			{
				j += 2;
				i--;
				wildcard = true;
			}			
			else
				break;
		}


		if (i == s_len	//1. 要将s中的字符都匹配过一遍
			//&& (j == p_len || (s_len == p_len && !wildcard) || (wildcard && j <= p_len-1)/* || (j == p_len-2 && p[j+1] == '*')*/)//如果p中没有*，则应该两字符串长度相等；否则j应该只比p_len少1，最后一位留给了'*'
			&& p_cnt == s_len)	//2. p的字符匹配次数应该等于s的长度
		{
			for (int k = 0; k < s_len; k++)
			{
				if (s_match[k] == false)
				{
					if (s[k] == '*')
					{
						continue;
					}
					else if (k < s_len-1 && s[k+1] == '*')
					{
						continue;
					}
					else
						return false;
				}
			}
			for (int k = 0; k < p_len; k++)
			{
				if (p_match[k] == false)
				{
					if (p[k] == '*')
					{
						continue;
					}
					else if (k < p_len-1 && p[k+1] == '*')
					{
						continue;
					}
					else
						return false;
				}
			}
			is_matched = true;
		}
		delete []s_match;
		delete []p_match;

		return is_matched;
	}

	///@brief	正则表达式匹配
	///@param	s	表达式1
	///@param	p	表达式2
	///@return	如果s和p能够匹配，则返回true；否则返回false
	///@author	zhaowei
	///@date	2015.06.01
	/* @note	解题思路：参考了leetcode的答案，给出了递归方法来解决这个问题

	*/
	bool isMatch(string s, string p) 
	{
		const char *s_char = s.c_str();	// 先将string转换成const char*表示的字符串
		const char *p_char = p.c_str();

		// 基本情况：如果p_char为空，那么s_char为空时返回true，否则返回false
		if (*p_char == '\0') 
			return *s_char == '\0';
				
		// 如果p下一个匹配的字符不是'*'，那么s和p的当前字符一定要匹配
		if (*(p_char+1) != '*') 
		{		
			return ((*p_char == *s_char) || (*p_char == '.' && *s_char != '\0')) && isMatch(s_char+1, p_char+1);
		}
		
		// 如果p下一个字符是'*'，那么一直将s匹配下去
		while ((*p_char == *s_char) || (*p_char == '.' && *s_char != '\0')) 
		{
			if (isMatch(s_char, p_char+2))	// 如果p+2即'*'后面的第一个字符及后面的所有字符可以和剩余的s匹配，则返回true，否则s自增1 
				return true;
			s_char++;
		}
		return isMatch(s_char, p_char+2);	// 匹配s和p+2
	}
};


///@note    递归求解
class Solution_v2 {
public:
	///@brief	通配符匹配
	///@param	s	字符串
	///@param	p	模板
	///@return	如果s与p匹配，则返回true；否则返回false
	///@note	p中的*可以表示0或多个前字符，.可以表示任意字符。
	bool isMatch(string s, string p) {
		if (p.empty())	return s.empty();
		if (p.size() == 1)	return (s.size() == 1 && (s[0] == p[0] || p[0] == '.'));
		if (p[1] != '*') {
			if (s.empty())	return false;
			return (s[0] == p[0] || p[0] == '.') && isMatch(s.substr(1), p.substr(1));
		}
		while (!s.empty() && (s[0] == p[0] || p[0] == '.')) {
			if (isMatch(s, p.substr(2)))	return true;
			s = s.substr(1);
		}
		return isMatch(s, p.substr(2));
	}
};

class Solution_v3 {
public:
	///@brief	通配符匹配
	///@param	s	字符串
	///@param	p	模板
	///@return	如果s与p匹配，则返回true；否则返回false
	///@note	动态规划。用dp[i][j]表示s[0..i-1]和p[0..j-1]是否匹配。则初始条件为dp[0][0] = true。递推关系式分两种情况讨论：
	//			如果p[j-1] == '*'，那么如果它表示前一个字符出现0次，则dp[i][j] = dp[i][j-2]；
	//			如果它表示前一个字符至少出现1次，则dp[i][j] = dp[i-1][j] && (s[i-1] == p[j-2] || p[j-2] == '.')；
	//			如果p[j-1] != '*'，则dp[i][j] = dp[i-1][j-1] && (s[i-1] == p[j-1] || p[j-1] == '.').
	//			时间复杂度为O(n^2)，空间复杂度为O(n^2)。
	bool isMatch(string s, string p) {
		int m = s.size(), n = p.size();
		vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));
		dp[0][0] = true;
		for (int i = 0; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				if (p[j-1] == '*')	
					dp[i][j] = dp[i][j-2] || (i > 0 && (s[i-1] == p[j-2] || p[j-2] == '.') && dp[i-1][j]);
				else
					dp[i][j] = i > 0 && dp[i-1][j-1] && (s[i-1] == p[j-1] || p[j-1] == '.');
			}
		}
		return dp[m][n];
	}
};

class Solution {
public:
	///@note	1. '*'表示0个或多个前一个字符；所以"aab"和"c*a*b"可以匹配，"c*a*b"的第一个'*'是0个c，第二个'*'是1个a。
	bool isMatch(string s, string p) {
		int m = s.size(), n = p.size();
		vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));
		dp[0][0] = true;
		for (int i = 0; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				if (p[j-1] == '*')	dp[i][j] = dp[i][j-2] || (i > 0 && dp[i-1][j] && (s[i-1] == p[j-2] || p[j-2] == '.'));
				else	dp[i][j] = i > 0 && dp[i-1][j-1] && (s[i-1] == p[j-1] || p[j-1] == '.');
			}
		}
		return dp[m][n];
	}
};

int main()
{
	string s = "aab";
	string p = "c*a*b";	
	Solution slt;	
	bool rslt = slt.isMatch(s, p);
	return 0;
}