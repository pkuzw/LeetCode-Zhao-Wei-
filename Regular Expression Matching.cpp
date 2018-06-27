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

///@date    June 26, 2018
///@version 3.2

///@date    June 27, 2018
///@version 2.2

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
class Solution_v2_1 {
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

class Solution {
public:
    ///@brief   判定字符串p能否正则表达字符串s
    ///@param   s   字符串s
    ///@param   p   字符串p
    ///@return  如果字符串p能够正则表达字符串s，返回true；否则返回false
    ///@note    1. 递归法
    //          2.
    bool isMatch(string s, string p) {
        
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
    ///@brief   字符串p是否是s的正则表达式，即p能否满足正则表达式的扩充规则来表示s
    ///@param   s   原始字符串
    ///@param   p   正则表达式
    ///@return  如果p是s的正则表达式，返回true；否则返回false。
    ///@note    1. 动态规划；设dp[i][j]表示字符子串p[0..j-1]是字符子串s[0..i-1]的正则表达式。初始化dp[0][0] = true，因为
    //             空串必是空串的正则表达式；
    //          2. 递推关系式dp[i][j] = dp[i-1][j-1] && (s[i-1] == p[j-1] || p[j-1] == '.'), 如果p[j-1] != '*';
    //
    //                              = (dp[i][j-2]) || (dp[i-1][j] && (s[i-1] == p[j-2] || p[j-2] == '.')), 如果p[j-1] == '*'.
    //          3. 对于p[j-1] != '*'的情形，很好理解，dp[i][j]的值依赖于dp[i-1][j-1]和s[i-1]与p[j-1]是否匹配，后者又细分为
    //             p[j-1]是否为'.'的情况，因为'.'是通配符。
    //          4. 对于p[j-1] == '*'的情形，则稍微复杂一点。分两种情况：
    //              a. 如果p[j-2]一次也没有出现，那么dp[i][j]依赖于dp[i][j-2]的值，相当于p[j-2..j-1]一次也没有在s中出现，
    //                 那么直接去掉末尾这两个字符，来看剩余子串是否和s[0..i-1]相匹配。
    //              b. 如果p[j-2]至少在s中出现一次，那么应该将s[i-1]从s中去除，然后比较剩下的s[0..i-2]和p[0..j-1]是否匹配。
    //          5. 时间复杂度为O(mn)，空间复杂度为O(mn)，其中n为字符串s的长度，m为字符串p的长度。
	bool isMatch(string s, string p) {
        int n = s.length(), m = p.length();
        vector<vector<bool>> dp(n+1, vector<bool>(m+1, false));
        dp[0][0] = true;
        for (int i = 0; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                 //此处需注意i-1的越界问题，提前判定i > 0；之所不需要判定j > 1，是因为合法的正则表达式不可能在首元素出现‘*’.
                if (p[j-1] == '*')
                    dp[i][j] = (i > 0 && dp[i-1][j] && (s[i-1] == p[j-2] || p[j-2] == '.')) || (dp[i][j-2]);
                else
                    dp[i][j] = (i > 0 && dp[i-1][j-1] && (s[i-1] == p[j-1] || p[j-1] == '.'));
            }
        }
        return dp[n][m];
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
