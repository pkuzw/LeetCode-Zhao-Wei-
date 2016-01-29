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

///@date	2015.08.09
///@version	1.1

///@date	2016.01.29
///@version	1.2

#include <stack>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution_v1 {
public:
	///@brief	能够处理分母为0的简洁版，AC
	int calculate_simple(string s) {
		int res = 0, d = 0;
		char sign = '+';
		stack<int> nums;
		for (int i = 0; i < s.size(); ++i) {
			if (s[i] >= '0') {
				d = d * 10 + s[i] - '0';
			}
			if ((s[i] < '0' && s[i] != ' ') || i == s.size() - 1) {
				if (sign == '+') nums.push(d);
				if (sign == '-') nums.push(-d);
				if (sign == '*' || sign == '/') {
					int tmp = sign == '*' ? nums.top() * d : nums.top() / d;
					nums.pop();
					nums.push(tmp);
				}
				sign = s[i];
				d = 0;
			} 
		}
		while (!nums.empty()) {
			res += nums.top();
			nums.pop();
		}
		return res;
	}

	///@brief	计算简单算术表达式
	///@param	s	字符串
	///@return	返回它计算结果。
	/* @note	先将算术表达式中多于的空格清除，然后转化成字符串的形式压入原始栈。然后从原始栈栈顶开始弹出字符串，如果遇到数字、加号、减号压入临时栈，
				如果遇到乘号和除号，则弹出两边的栈顶元素进行运算，并将结果压入临时栈，然后继续弹原始栈，直到其为空。这时候临时栈中就是只有加减号的
				算术表达式。然后再弹栈进行运算。在计算中间结果的时候用两个栈。第一个栈是原始的算术表达式，第二栈用来存放没有遇到*或/之前的算术表达式。
				时间复杂度为O(n)，空间复杂度为O(n)。*/
	int calculate(string s) {
		if (s.empty())	return 0;

		stack<string> str_nums;	//	原始栈

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
				op_indx.push_back(i);
			}
		}

		int end = s.length()-1;
		string str_num;
		for (int i = op_indx.size()-1; i >= 0; i--)
		{
			str_num = s.substr(op_indx[i]+1, end-op_indx[i]);
			end = op_indx[i] - 1;
			str_nums.push(str_num);			
			str_nums.push(s.substr(op_indx[i], 1));
		}
		str_num = s.substr(0, end+1);
		str_nums.push(str_num);

		int rslt = 0;
		stack<string> tmp;
		while (!str_nums.empty())	//	先算乘除
		{	
			string tp = str_nums.top();
			str_nums.pop();
			if (tp != "*" && tp != "/") 
			{
				tmp.push(tp);
			}
			else 
			{
				int n = tp == "*" ?  stringToInt(tmp.top()) * stringToInt(str_nums.top()) : stringToInt(tmp.top()) / stringToInt(str_nums.top());
				str_nums.pop();
				tmp.pop();
				str_nums.push(intToString(n));
			}
		}

		while (!tmp.empty())	//	tmp的算术表达式是逆序，要把它颠倒回去
		{
			str_nums.push(tmp.top());
			tmp.pop();
		}


		while (!str_nums.empty())	//	再算加减
		{
			string tp = str_nums.top();
			str_nums.pop();
			if (tp != "+" && tp != "-")
				tmp.push(tp);
			else
			{
				rslt = tp == "+" ? stringToInt(tmp.top()) + stringToInt(str_nums.top()): stringToInt(tmp.top()) - stringToInt(str_nums.top());
				tmp.pop();
				str_nums.pop();
				str_nums.push(intToString(rslt));
			}
		}
		return stringToInt(tmp.top());
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

class Solution_v1_1 {
public:
	int calculate(string s) {
		stack<int> stk;
		int rslt = 0;
		int d = 0;
		char sign = '+';

		if (s.empty())	return rslt;

		for (int i = 0; i != s.size(); i++)
		{		
			if (s[i] >= '0' && s[i] <= '9')
				d = d*10 + s[i]-'0';
			
			if ((s[i] < '0' && s[i] != ' ') || i == s.size()-1)	//	第一个判断加上不是' '是不要单独判空格符，以免最后一个字符是空格符时无法将最后一个数字计算入栈；第二个判断条件是为了将最后一个数字也压入栈
			{
				if (sign == '+')		
					stk.push(d);		
				else if (sign == '-')
					stk.push(-d);
				else if (sign == '*')
				{
					int tmp = stk.top() * d;
					stk.pop();
					stk.push(tmp);
				}
				else if (sign == '/')
				{
					int tmp = stk.top() / d;
					stk.pop();
					stk.push(tmp);
				}
				d = 0;
				sign = s[i];
			}
		}

		while (!stk.empty())
		{
			rslt += stk.top();
			stk.pop();
		}
		return rslt;
	}
};

class Solution {
public:
	///@note	1. 栈，用一个栈来保存所有能够做加法的数，这些数可以是正数、负数或者乘除组合起来的数；
	//			2. 用一个标记变量来保存当前数字的符号，初始为'+'。
	//			3. 注意处理表达式最后一个数字，它在第二个条件语句的第二个条件判断里面，是和第一个条件并列的关系，不是互斥的。
	int calculate(string s) {
		int rslt = 0, num = 0;
		char sign = '+';
		stack<int> stk;
		if (s.empty())	return 0;
		for (int i = 0; i != s.size(); i++) {
			if (s[i] >= '0') {	//	由于在ASCII中'0'~'9'的编码值大于'+', '-', '*', '/', ' '等符号，所以只需要判定下限即可
				num = num * 10 + s[i] - '0'	;
			}
			if ((s[i] < '0' && s[i] != ' ') || (i == s.size() - 1)) {
				if (sign == '+')		stk.push(num);
				else if (sign == '-')	stk.push(-num);
				else if (sign == '*') {
					num = stk.top() * num;
					stk.pop();
					stk.push(num);
				}
				else if (sign == '/') {
					num = stk.top() / num;
					stk.pop();
					stk.push(num);
				}
				sign = s[i];
				num = 0;
			}			
		}
		while (!stk.empty()) {
			rslt += stk.top();
			stk.pop();
		}
		return rslt;
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
	1787+2136/3/2*2
	1-1+1
	*/
	string s = "100000000/1/2/3/4/5/6/7/8/9/10";
	Solution slt;
	int rslt = slt.calculate(s);

	Solution_v1_1 slt11;
	int r11 = slt11.calculate(s);
	return 0;
}