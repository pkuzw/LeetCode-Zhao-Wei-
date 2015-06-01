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
#include <iostream>
#include <string>
using namespace std;

class Solution
{
public:
	bool isMatch(string s, string p) {
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
};

int main()
{
	string s = "aab";

	string p = ".*ab";
	while (cin >> s >> p)
	{
		Solution slt;
		cout << slt.isMatch(s, p) << endl;
	}
	
	return 0;
}