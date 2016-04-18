///@file	Valid Number
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

///@date	2015.12.01
///@version	2.0

///@date	2016.04.18
///@version	2.1

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	判断一个字符串是否是数字
	///@param	s	字符串
	///@return	如果该字符串是数字，返回true；否则返回false
	///@note	题目故意给的条件很模糊，需要自己去思考一下。
	//			1. 不能超过1个小数点；
	//			2. 可以有e，表示10的幂指数；
	//			3. 可以有'+', '-'，他们可以位于数字的开头或者'e'的后面
	//			4. 数字之间不能有空白符；
	//			5. 开头和结尾可以有连续的空白符；	
	//			6. 不能出现除了'e'之外的其他字母字符；
	//			7. 'e'或者'E'后面一定要有具体数字或者符号'-', '+'；
	//			8. 最多只能有一个'e'；
	//			9. 小数点可以在首位，即小数点前面可以没有数字；小数点后也可以没有数字；
	//			10.'e'之后不能有小数点。
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
			if (neg_indx[0] == 0 || (neg_indx[0] != s.length()-1 && s[neg_indx[0]-1] == 'e'))		return true;
		}
		else if (sign_cnt[0] == 1 && sign_cnt[1] == 0)
		{
			if (pos_indx[0] == 0 || (pos_indx[0] != s.length()-1 && s[pos_indx[0]-1] == 'e'))		return true;
		}
		else if (sign_cnt[0] == 1 && sign_cnt[1] == 1)
		{
			if ((pos_indx[0] == 0 && (neg_indx[0] != s.length()-1 && s[neg_indx[0]-1] == 'e')) 
				|| (neg_indx[0] == 0 && (pos_indx[0] != s.length()-1 && s[pos_indx[0]-1] == 'e')))	return true;
		}
		else if (sign_cnt[0] == 2 && sign_cnt[1] == 0) 
		{
			if (pos_indx[0] == 0 && (pos_indx[1] != s.length()-1 && s[pos_indx[1]-1] == 'e'))		return true;
		}
		else if (sign_cnt[0] == 0 && sign_cnt[1] == 2) 
		{
			if (neg_indx[0] == 0 && (neg_indx[1] != s.length()-1 && s[neg_indx[1]-1] == 'e'))		return true;
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
		int e_indx = 0;
		bool exist_exp = existExponent(s);
		if (exist_exp)	e_indx = expIndx(s);

		if (p_cnt == 0)	return true;	
		else if (p_cnt == 1)
		{
			if (s.length() == 1)	return false;	//	如果只有一个小数点，则非法
			for (int i = 0; i != s.length(); i++)
			{
				if (s[i] == '.')
				{	
					if (exist_exp)
					{						
						if (i > e_indx)	return false;
					}
					if (i == s.length()-1)
					{
						if (!(s[i-1] <= '9' && s[i-1] >= '0'))	return false;
					}
					else if (i == 0)
					{
						if (!(s[i+1] <= '9' && s[i+1] >= '0'))	return false;
					}					
					else if (!(((s[i-1] <= '9' && s[i-1] >= '0') || s[i-1] == '+' || s[i-1] == '-') 
						&& ((s[i+1] <= '9' && s[i+1] >= '0') || s[i+1] == 'e')))
					{
						return false;
					}
					return true;
				}
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

///@note	有限自动状态机
class Solution_v2 {
public:
	///@brief	判断给定的字符串是否是一个合法的数字
	///@param	s	字符串
	///@return	如果是合法字符串返回true；否则返回false
	///@note	1. 采用有限状态自动机来做状态判断。
	//			2. 对于字符串中的每一个字符输入，总共有6种情况，分别是INVALID, SPACE, SIGN, DIGIT, DOT, EXPONENT。
	//			3. 有限状态自动机是一个二维矩阵，矩阵的一共有6列，分别对应上面的6种输入字符状态； 矩阵有9行，分别对应着
	//			3.0 初始无输入或者只有space的状态；
	//			3.1 输入了数字之后的状态
	//			3.2 前面无数字，只输入了Dot的状态
	//			3.3 输入了符号状态
	//			3.4 前面有数字和有dot的状态
	//			3.5 'e' or 'E'输入后的状态
	//			3.6 输入e之后输入Sign的状态
	//			3.7 输入e后输入数字的状态
	//			3.8 前面有有效数输入之后，输入space的状态
	//			4. 时间复杂度为O(n)，空间复杂度为O(1)。其中n为字符串长度。
	bool isNumber(string s) {
		enum InputType {
			INVALID,		// 0 Include: Alphas, '(', '&' ans so on
			SPACE,			// 1 space
			SIGN,			// 2 '+','-'
			DIGIT,			// 3 numbers
			DOT,			// 4 '.'
			EXPONENT		// 5 'e' 'E'
		};
		int transTable[][6] = {
			//0INVA,1SPA,2SIG,3DI,4DO,5E
			-1,  0,  3,  1,  2, -1,//0初始无输入或者只有space的状态
			-1,  8, -1,  1,  4,  5,//1输入了数字之后的状态
			-1, -1, -1,  4, -1, -1,//2前面无数字，只输入了Dot的状态
			-1, -1, -1,  1,  2, -1,//3输入了符号状态
			-1,  8, -1,  4, -1,  5,//4前面有数字和有dot的状态
			-1, -1,  6,  7, -1, -1,//5'e' or 'E'输入后的状态
			-1, -1, -1,  7, -1, -1,//6输入e之后输入Sign的状态
			-1,  8, -1,  7, -1, -1,//7输入e后输入数字的状态
			-1,  8, -1, -1, -1, -1,//8前面有有效数输入之后，输入space的状态
		};
		int state = 0;
		for (int i = 0; i != s.size(); i++)
		{
			InputType input = INVALID;
			if (s[i] == ' ') input = SPACE;
			else if (s[i] == '+' || s[i] == '-') input = SIGN;
			else if (isdigit(s[i])) input = DIGIT;
			else if (s[i] == '.') input = DOT;
			else if (s[i] == 'e' || s[i] == 'E') input = EXPONENT;
			state = transTable[state][input];
			if (state == -1) return false;			
		}
		return state == 1 || state == 4 || state == 7 || state == 8;
	}
};

class Solution {
public:
	bool isNumber(string s) {
		enum InputType {INVALID, SPACE, SIGN, DIGIT, DOT, EXPONENT};
		int transTable[9][6] = {
//		0:INVALID  1:SPACE  2:SIGN  3.DIGIT  4.DOT  5.EXPONENT
			{-1,        0,       3,      1,       2,     -1}, //0初始无输入或者只有space的状态  
			{-1,        8,       -1,     1,       4,     5},  //1输入了数字之后的状态
			{-1,        -1,      -1,     4,       -1,    -1}, //2前面无数字，只输入了Dot的状态
			{-1,        -1,      -1,     1,       2,     -1}, //3输入了符号状态
			{-1,        8,       -1,     4,       -1,    5}, //4前面有数字和有dot的状态
			{-1,        -1,      6,      7,       -1,    -1}, //5'e' or 'E'输入后的状态
			{-1,        -1,      -1,     7,       -1,    -1}, //6输入e之后输入Sign的状态
			{-1,        8,       -1,     7,       -1,    -1},//7输入e后输入数字的状态
			{-1,        8,       -1,     -1,      -1,    -1}//8前面有有效数输入之后，输入space的状态
		};
		int state = 0;
		for (int i = 0; i != s.size(); i++) {
			InputType input = INVALID;
			if (s[i] == ' ')	input = SPACE;
			else if (s[i] == '+' || s[i] == '-')		input = SIGN;
			else if (isdigit(s[i]))	input = DIGIT;
			else if (s[i] == '.')	input = DOT;
			else if (s[i] == 'e' || s[i] == 'E')	input  = EXPONENT;
			state = transTable[state][input];
			if (state == -1)		return false;
		}
		return state == 1 || state == 4 || state == 7 || state == 8;
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