///@file	Basic Calculator II
/*
Implement a basic calculator to evaluate a simple expression string.

The expression string contains only non-negative integers, +, -, *, / operators and empty spaces . The integer division should truncate toward zero.

You may assume that the given expression is always valid.

Some examples:

"3+2*2" = 7
" 3/2 " = 1
" 3+5 / 2 " = 5
*/
///@author	zhaowei
///@date	2015.07.29
///@version	1.0

#include <stack>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
	///@brief	计算简单算术表达式
	///@param	s	字符串
	///@return	返回它计算结果。
	/* @note	先将算术表达式中多于的空格清除，然后转化成字符串的形式压入原始栈。然后从原始栈栈顶开始弹出字符串，如果遇到数字、加号、减号压入临时栈，
				如果遇到乘号和除号，则弹出两边的栈顶元素进行运算，并将结果压入临时栈，然后继续弹原始栈，直到其为空。这时候临时栈中就是只有加减号的
				算术表达式。然后再弹栈进行运算。在计算中间结果的时候用两个栈。第一个栈是原始的算术表达式，第二栈用来存放没有遇到*或/之前的算术表达式。
				时间复杂度为O(n)，空间复杂度为O(n)。没有处理分母有可能为0的情况，OJ报RE。*/
	int calculate(string s) {
		if (s.empty())	return 0;

		vector<string> str_nums;	//	原始栈
		bool flg = true;	//	是否是连除，这样写有问题。

		//	转换掉多于空格并压入原始栈
		vector<int> op_indx;
		for (int i = 0; i < s.length(); i++)
		{
			while (i < s.length() && s[i] == ' ')
			{
				s.erase(i, 1);	//	erase删除掉元素后i指向被删除元素的后一位
			}
		}
		for (int i = 0; i != s.length(); i++)
		{
			if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/')
			{
				if (s[i] != '/')	flg = false;
				op_indx.push_back(i);
			}
		}

		int start = 0;
		string str_num;
		for (int i = 0; i != op_indx.size(); i++)
		{
			str_num = s.substr(start, op_indx[i]-start);
			start = op_indx[i] + 1;
			str_nums.push_back(str_num);			
			str_nums.push_back(s.substr(op_indx[i], 1));
		}
		str_num = s.substr(start, s.length()-start);
		str_nums.push_back(str_num);
		if (flg)	reverse(str_nums.begin(), str_nums.end());	//	防止"100000000/1/2/3/4/5/6/7/8/9/10"这样的情况溢出

		int rslt = 0;
		vector<string> tmp;
		while (!str_nums.empty())	//	先算乘除
		{	
			string tp = str_nums.back();
			str_nums.pop_back();
			if (tp != "*" && tp != "/") 
			{
				tmp.push_back(tp);
			}
			else 
			{
				int n = 0;
				if (flg)
					n = tp == "*" ?  stringToInt(tmp.back()) * stringToInt(str_nums.back()) : stringToInt(tmp.back()) / stringToInt(str_nums.back());
				else
					n = tp == "*" ?  stringToInt(str_nums.back()) * stringToInt(tmp.back()) : stringToInt(str_nums.back()) / stringToInt(tmp.back());
				str_nums.pop_back();
				tmp.pop_back();
				tmp.push_back(intToString(n));
			}
		}

		while (!tmp.empty())	//	再算加减
		{
			string tp = tmp.back();
			tmp.pop_back();
			if (tp != "+" && tp != "-")
				str_nums.push_back(tp);
			else
			{
				rslt = tp == "+" ? stringToInt(str_nums.back()) + stringToInt(tmp.back()): stringToInt(str_nums.back()) - stringToInt(tmp.back());
				tmp.pop_back();
				str_nums.pop_back();
				str_nums.push_back(intToString(rslt));
			}
		}
		return stringToInt(str_nums.back());
	}

private:
	///@brief	将string转换成int型变量，支持负数
	int stringToInt(string s)
	{
		if (s == "-2147483648")	return INT_MIN;

		vector<int> dec;
		dec.push_back(1);
		for (int i = 1; i != 10; i++)
		{
			int k = dec[i-1] * 10;
			dec.push_back(k);
		}

		int num = 0;
		int sign = 1;	//	1:+，-1:-
		if (s[0] == '-')	
		{
			sign = -1;
			s = s.substr(1, s.length()-1);
		}
		else if (s[0] == '+')	
		{
			sign = 1;
			s = s.substr(1, s.length()-1);
		}
		for (int i = 0; i != s.length(); i++)
		{
			num += int(s[i]-'0')*dec[s.length()-i-1];
		}
		return num*sign;
	}

	///@brief	将整型转换成string，支持负数
	string intToString(int n)
	{
		if (n == 0)	return "0";
		int sign = n < 0 ? -1 : 1;	//1:+, -1:-

		n = sign * n;
		string s;
		while (n > 0)
		{
			char c = '0' + char(n % 10);
			s = c + s;
			n /= 10;
		}
		return sign == -1 ? "-" + s : s;
	}
};

int main()
{
	/*
	"3+2*2" = 7
	" 3/2 " = 1
	" 3+5 / 2 " = 5
	3+5 / 2 - 8 * 9
	1-1+1
	100000000/1/2/3/4/5/6/7/8/9/10
	*/
	string s = "1787+2136/3/2*2";
	Solution slt;
	int rslt = slt.calculate(s);
	return 0;
}