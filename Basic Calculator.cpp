///@file	Basic Calculator
/*
Implement a basic calculator to evaluate a simple expression string.

The expression string may contain open ( and closing parentheses ), the plus + or minus sign -, non-negative integers and empty spaces .

You may assume that the given expression is always valid.

Some examples:

"1 + 1" = 2
" 2-1 + 2 " = 3
"(1+(4+5+2)-3)+(6+8)" = 23
*/
///@author	zhaowei
///@date	2015.07.27
///@version	1.1

#include <stack>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
	///@brief	实现一个简单的计算器：给定的字符串中包含数字、加减号、括号()和空格符。假设输入都是有效的。
	///@param	s	算术字符串
	///@return	返回它的值
	/* @note	通过栈来保存括号。从左向右扫描字符串，如果遇到空白符，舍弃；如果遇到左括号、数字和加减号，入栈；如果遇到右括号，弹栈直到
				遇到第一个左括号。将这个封闭括号中的算术表达式计算出来再压回栈中。持续压栈直到最后。最后再清栈。
				期间如果遇到符号为加减号，那么计算它俩边的数字。
				支持负数。
				时间复杂度为O(n)，空间复杂度为O(n)。*/
	int calculate(string s) {
		if (s.empty())	return 0;

		int rslt = 0;
		stack<char> stk;

		for (int i = 0; i != s.length(); i++)
		{
			if (s[i] == ' ' && i < s.length()-1)	
				continue;

			if (s[i] != ')')
				stk.push(s[i]);

			if (s[i] == ')' || i == s.length()-1)
			{
				if (s[i] == ' ')	break;
				
				string stmp;				
				while (!stk.empty() && stk.top() != '(')
				{
					char c = stk.top();
					stk.pop();
					stmp += c;						
				}	
				if (!stk.empty())
					stk.pop();

				reverse(stmp.begin(), stmp.end());	//	将逆序的字符串反过来
				string rtmp = simpleCalculator(stmp);
				stmp.clear();

				for (int j = 0; j != rtmp.length(); j++)
				{
					if (j == 0 && rtmp[j] == '-')
					{
						if (!stk.empty() && stk.top() == '+')
						{	
							stk.top() = '-';
							continue;
						}
						if (!stk.empty() && stk.top() == '-')
						{	
							stk.top() = '+';
							continue;
						}								
					}
					stk.push(rtmp[j]);
				}
			}
		}
		if (!stk.empty())
		{
			string r;
			while (!stk.empty())
			{
				r += stk.top();
				stk.pop();
			}
			reverse(r.begin(), r.end());
			rslt = strToInt(simpleCalculator(r));
		}
		return rslt;
		
	}

private:
	///@brief	只包含加减号和有效数字的算术字符串运算
	///@param	s	只包括加减号和有效数字的字符串
	///@return	返回它的计算结果
	string simpleCalculator(string s)
	{
		vector<string> numbers;
		int n1 = 0;
		int n2 = 0;
		char sign = ' ';
		
		string num;
		for (int i = 0; i != s.length(); i++)
		{
			if (i > 0 && (s[i] == '+' || s[i] == '-'))
			{
				numbers.push_back(num);
				num.clear();
			}
			num += s[i];	
		}
		numbers.push_back(num);

		int rslt = 0;
		for (int i = 0; i != numbers.size(); i++)
		{
			int a = strToInt(numbers[i]);
			rslt += a;
		}
		return intToStr(rslt);			
	}

	///@brief	将字符串转换成整数
	///@param	s	字符串
	///@return	返回对应的整数。支持负数，和带'+'的正数
	int strToInt(string s)
	{	
		int indx = 0;	//	去除掉两边的空白字符
		while (s[indx] == ' ')
			indx++;
		s = s.substr(indx, s.length()-indx);

		indx = s.length()-1;
		while (s[indx] == ' ')
			indx--;
		s = s.substr(0, indx+1);

		bool flg = false;
		if (s[0] == '-')
		{
			s = s.substr(1, s.length()-1);
			flg = true;
		}
		else if (s[0] == '+')
		{
			s = s.substr(1, s.length()-1);
			flg = false;
		}
		
		int num = 0;
		vector<int> dec;
		for (int i = 0; i < s.length(); i++)
		{
			int k = 1;
			for (int j = 1; j <= i; j++)
			{
				k *= 10;
			}
			dec.push_back(k);
		}		

		for (int i = 0; i != s.length(); i++)
		{
			num += (s[i]-'0') * dec[s.length()-i-1];
		}

		return flg ? num*(-1) : num;
	}

	///@brief	将整数转换成字符串
	///@param	n	整数
	///@return	返回它对应的字符串
	string intToStr(int n)
	{
		if (n == 0)			return "0";
		if (n == INT_MIN)	return "-2147483648";
		string s;
		bool flg = false;
		if (n < 0)
		{
			flg = true;
			n *= -1;
		}
		vector<int> dec;
		for (int i = 0; i < 10; i++)
		{
			int k = 1;
			for (int j = 1; j <= i; j++)
			{
				k *= 10;
			}
			dec.push_back(k);
		}

		bool flg1 = false;
		for (int i = dec.size()-1; i >= 0; i--)
		{			
			int t = n;
			if (n >= dec[i])
			{
				s += char(n/dec[i]+'0');
				n %= dec[i];
				flg1 = true;
			}
			if (t < dec[i] && flg1)
				s += '0';
		}
		return flg ? "-" + s : s;
	}
};

int main()
{
	/*
	"1 + 1" = 2
	" 2-1 + 2 " = 3
	"(1+(4+5+2)-3)+(6+8)" = 23

	(103-(102+(6500-(7007+1-(1001-302)))))

	2-4-(8+2-6+(8+4-(1)+8- 10  ) )      
	*/
	
	string s = "1-(3+5-2+(3+19-(3-1-4+(9-4-(4-(1+(3)-2)-5)+8-(3-5)-1)-4)-5)-4+3-9)-4-(3+2-5)-10""1-(3+5-2+(3+19-(3-1-4+(9-4-(4-(1+(3)-2)-5)+8-(3-5)-1)-4)-5)-4+3-9)-4-(3+2-5)-10";
	//"1+2+3-10-11";
	Solution slt;
	int rslt = slt.calculate(s);
	cout << rslt << endl;
	return 0;
}