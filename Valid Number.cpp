﻿///@file	Valid Number
/*
Validate if a given string is numeric.

Some examples:
"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true

Note: It is intended for the problem statement to be ambiguous. 

You should gather all requirements up front before implementing one.
*/
///@author	zhaowei
///@date	2015.07.11
///@version	1.0

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	///@brief	判断一个字符串是否是数字
	///@param	s	字符串
	///@return	如果该字符串是数字，返回true；否则返回false
	///@note	题目故意给的条件很模糊，需要自己去思考一下。
	//			1. 不能超过2个小数点，在指数形式下， 指数符号前可以有一个，指数符号后可以有一个；
	//			2. 可以有e，表示10的幂指数；
	//			3. 可以有'+', '-'，他们可以位于数字的开头或者'e'的后面
	//			4. 数字之间不能有空白符；
	//			5. 开头和结尾可以有连续的空白符；
	//			6. 数字应该允许被表示成十六进制，只要开头是0x或者0X，则后续就可以出现Aa, Bb, Cc, Dd, Ee, Ff。
	//			7. 如果不是十六进制，则不能出现除了'e'或者'E'之外的其他字母字符；
	//			8. 'e'或者'E'后面一定要有具体数字或者符号'-', '+'；
	//			9. 最多只能有一个'e'或者'E'；
	//			10.小数点可以在首位，即小数点前面可以没有数字；小数点后也可以没有数字
	bool isNumber(string s) {
		trimStr(s);	//	去除字符串首尾的连续空白符
		if (s.empty())	return false;	//	空字符为false
		else if (existSpace(s))	return false;
		else if (existSign(s) && !legalSign(s))	return false;
		else if (existExponent(s) && !legalExponent(s))	return false;
		else if (existPoint(s) && !legalPoint(s))	return false;
		else if (existIlegal(s))	return false;

		return true;
	}

private:
	///@brief	截去字符串开头和末尾的连续空白符
	///@param	s	字符串
	///@return  空
	void trimStr(string &s)
	{
		if (s.empty())	return;	//	处理空字符串
		int head_indx = 0;
		while (s[head_indx] == ' ')
			head_indx++;
		s = s.substr(head_indx, s.length()-head_indx);

		int tail_indx = s.length()-1;
		while (s[tail_indx] == ' ')
			tail_indx--;
		s = s.substr(0, tail_indx+1);
		return;
	}

	///@brief	判断字符串中是否存在空白符
	///@param	s	字符串
	///@return	如果字符串中有空白符，则返回true；否则返回false
	bool existSpace(string s)
	{
		for (int i = 0; i != s.length(); i++)
			if (s[i] == ' ')
				return true;
		return false;
	}

	///@brief	判断字符串中是否存在正负号
	///@param	s	字符串
	///@return	如果字符串中有正负号，则返回true；否则返回false
	bool existSign(string s)
	{
		for (int i = 0; i != s.length(); i++)
			if (s[i] == '+' || s[i] == '-')
				return true;
		return false;
	}

	///@brief	计算字符串中的正负号个数
	///@param	s	字符串	
	///@return	包含有正负号数目的数组
	vector<int> getSignNum(string s)
	{
		int pos_cnt = 0, neg_cnt = 0;
		for (int i = 0; i != s.length(); i++)
		{
			if (s[i] == '+')	pos_cnt++;
			else if (s[i] == '-')	neg_cnt++;
		}
		vector<int> r;
		r.push_back(pos_cnt);
		r.push_back(neg_cnt);
		return r;
	}

	///@brief	计算正负号的下标
	///@param	s
	///@param	pos_indx	保存有正号下标的向量
	///@param	neg_indx	保存有负号下标的向量
	///@return	无
	void signIndx(string s, vector<int> &pos_indx, vector<int> &neg_indx)
	{		
		for (int i = 0; i != s.length(); i++)
		{
			if (s[i] == '+')	pos_indx.push_back(i);
			else if (s[i] == '-')	neg_indx.push_back(i);
		}
		return;
	}
	
	///@brief	判断字符串中是否有合法的'+', '-'号
	///@param	s	字符串
	///@return	如果'+'或者'-'出现在字符串的开头或者e的后面，则返回true；否则返回false。
	bool legalSign(string s)
	{
		vector<int> pos_indx, neg_indx;
		vector<int> sign_cnt = getSignNum(s);
		signIndx(s, pos_indx, neg_indx);

		if (sign_cnt[0] == 0 && sign_cnt[1] == 0)	return true;
		else if (sign_cnt[0] == 0 && sign_cnt[1] == 1)
		{
			if (neg_indx[0] == 0 || s[neg_indx[0]-1] == 'e')		return true;
		}
		else if (sign_cnt[0] == 1 && sign_cnt[1] == 0)
		{
			if (pos_indx[0] == 0 || s[pos_indx[0]-1] == 'e')		return true;
		}
		else if (sign_cnt[0] == 1 && sign_cnt[1] == 1)
		{
			if ((pos_indx[0] == 0 && s[neg_indx[0]-1] == 'e') || (neg_indx[0] == 0 && s[pos_indx[0]-1] == 'e'))	return true;
		}
		else if (sign_cnt[0] == 2 && sign_cnt[1] == 0) 
		{
			if (pos_indx[0] == 0 && s[pos_indx[1]-1] == 'e')		return true;
		}
		else if (sign_cnt[0] == 0 && sign_cnt[1] == 2) 
		{
			if (neg_indx[0] == 0 && s[neg_indx[1]-1] == 'e')		return true;
		}
		return false;
	}

	///@brief	判断字符串中是否有'e'或者'E'
	///@param	s	字符串
	///@return	如果字符串中有指数符号，则返回true；否则返回false。
	bool existExponent(string s)
	{
		for (int i = 0; i != s.length(); i++)
			if (s[i] == 'e' || s[i] == 'E')
				return true;
		return false;
	}

	///@brief	判断字符串中的指数符号是否合法
	///@param	s	字符串
	///@return	如果字符串中的指数符号合法，则返回true；否则返回false
	///@note	指数符号之前应该是数字字符，之后应该是正负号或者数字字符，其他情况都是不合法的；字符串中最多只能有一个指数符号
	bool legalExponent(string s)
	{
		int e_cnt = 0;
		for (int i = 0; i != s.length(); i++)
		{
			if (s[i] == 'e' || s[i] == 'E')
			{
				e_cnt++;
				if (e_cnt > 1)	//	如果字符串中指数符号多于1个，认为是非法字符串
				{
					return false;
				}
				if (i == 0 || i == s.length()-1)
				{
					return false;
				}
				if (!(((s[i-1] <= '9' && s[i-1] >= '0') || s[i-1] == '.') && ((s[i+1] <= '9' && s[i+1] >= '0') || s[i+1] == '-' || s[i+1] == '+' || s[i+1] == '.')))
				{
					return false;
				}
			}
		}
		return true;
	}

	///@brief	如果指数符号合法，则获取其所在下标
	///@param	s	字符串
	///@return	返回指数符号'e'或者'E'的下标
	int expIndx(string s)
	{
		for (int i = 0; i != s.length(); i++)
			if (s[i] == 'e' || s[i] == 'E')
				return i;
		return -1;
	}

	///@brief	判断字符串中是否含有小数点
	///@param	s	字符串
	///@return	如果存在小数点字符，则返回true；否则返回false
	bool existPoint(string s)
	{
		for (int i = 0; i != s.length(); i++)
			if (s[i] == '.')
				return true;
		return false;
	}

	///@brief	如果字符串中含有小数点，则计算小数点的数目
	///@param	s	字符串
	///@return	给出字符串中的小数点数目
	int getPointNum(string s)
	{
		int p_cnt = 0;
		for (int i = 0; i != s.length(); i++)
			if (s[i] == '.')
				p_cnt++;
		return p_cnt;
	}

	///@brief	判断字符串中的小数点是否合法
	///@param	s	字符串
	///@return	如果字符串中的小数点数目为1，且其前后均是数字字符，或者字符串中的小数点数目为2，且其位于指数字符两侧，且其
	//			前后均是数字字符，则返回true；小数点前可以没有数字；小数点后也可以没有数字；其他情况返回false
	bool legalPoint(string s)
	{
		int p_cnt = getPointNum(s);
		if (p_cnt == 0) return true;
		else if (p_cnt == 1)
		{
			if (s.length() == 1)	return false;	//	如果只有一个小数点，则非法
			for (int i = 0; i != s.length(); i++)
			{
				if (s[i] == '.')
				{					
					if (i == s.length()-1)
					{
						if (s[i-1] <= '9' && s[i-1] >= '0')	return true;							
						else	return false;
					}
					else if (i == 0)
					{
						if (s[i+1] <= '9' && s[i+1] >= '0')	return true;
						else return false;
					}
					else if (!(((s[i-1] <= '9' && s[i-1] >= '0') || s[i-1] == '+' || s[i-1] == '-' || s[i-1] == 'e') 
						&& ((s[i+1] <= '9' && s[i+1] >= '0') || s[i+1] == 'e')))
					{
						return false;
					}
					return true;
				}
			}
		}
		else if (p_cnt == 2)
		{
			if (s.length() == 2)	return false;	//	如果只有两个小数点，则非法

			if (!existExponent(s))	return false;			
			else if (legalExponent(s))
			{
				int e_indx = expIndx(s)	;
				int p_indx1 = 0, p_indx2 = 0;
				for (int i = 0; i != s.length(); i++)
				{
					if (s[i] == '.')
					{						
						if (i == 0)
						{
							if (s[i+1] <= '9' && s[i+1] >= '0')
								return true;
							else
								return false;
						}
						else if (i == s.length()-1)
						{
							if (s[i-1] <= '9' && s[i-1] >= '0')
								return true;
							else
								return false;
						}
						else if (!(((s[i-1] <= '9' && s[i-1] >= '0') || s[i-1] == '+' || s[i-1] == '-') 
							&& ((s[i+1] <= '9' && s[i+1] >= '0') || s[i+1] == 'e')))
						{
							return false;
						}

						if (p_indx1 == 0)
							p_indx1 = i;
						else
							p_indx2 = i;					
					}
				}
				if (p_indx1+1 < e_indx && e_indx+1 < p_indx2)
					return true;						
				else	
					return false;
			}			
		}		
		return false;
	}

	///@brief	判断字符串中是否存在其他字母字符
	///@param	s
	///@return  如果存在则返回false；否则返回true
	bool existIlegal(string s)
	{
		for (int i = 0; i != s.length(); i++)
		{
			if (!((s[i] <= '9' && s[i] >= '0') || s[i] == 'e' || s[i] == '.' || s[i] == '+' || s[i] == '-') )
			{
				return true;
			}
		}
		return false;
	}
};

int main()
{
	string s;
	Solution slt;
	while (getline(cin, s))
	{
		cout << slt.isNumber(s) << endl;
	}
	return 0;
}