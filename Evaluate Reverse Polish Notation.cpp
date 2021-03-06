﻿///@file	Evaluate Reverse Polish Notation
/*
Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are +, -, *, /. Each operand may be an integer or another expression.

Some examples:
["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6
*/
///@author	zhaowei
///@date	2015.08.04
///@version	1.0

///@date	2015.08.19
///@version	1.1

///@date	2016.01.13
///@version	1.2

#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	计算逆波兰表达式的值
	///@param	tokens	字符串数组：数字字符，或者+,-,*,/
	///@return	返回表达式的值
	/* @note	用一个栈来压入元素，遇到运算符，计算栈顶的两个元素，将结果压栈，然后继续向后遍历数组。时间复杂度为O(n)，空间复杂度为O(n)。*/
	int evalRPN(vector<string>& tokens) {
		stack<int> stk;
		for (int i = 0; i != tokens.size(); i++)
		{
			if (tokens[i] != "+" && tokens[i] != "-" && tokens[i] != "*" && tokens[i] != "/")
				stk.push(stoi(tokens[i]));
			else
			{
				if (tokens[i] == "+")
				{
					int a = stk.top();
					stk.pop();
					int b = stk.top();
					stk.pop();
					stk.push(b+a);
				}
				else if (tokens[i] == "-")
				{
					int a = stk.top();
					stk.pop();
					int b = stk.top();
					stk.pop();
					stk.push(b-a);
				}
				else if (tokens[i] == "*")
				{
					int a = stk.top();
					stk.pop();
					int b = stk.top();
					stk.pop();
					stk.push(b*a);
				}
				else if (tokens[i] == "/")
				{
					int a = stk.top();
					stk.pop();
					int b = stk.top();
					stk.pop();
					stk.push(b/a);
				}
			}
		}
		return stk.empty() ? 0 : stk.top();
	}
};

class Solution {
public:
	///@brief	计算逆波兰表达式的值
	///@param	tokens	字符串数组：数字字符，或者+,-,*,/
	///@return	返回表达式的值
	///@note	1. 栈；2. 注意'-'和'/'是需要区分顺序的，后弹出的者作为第一操作数，先弹出的是第二操作数。
	int evalRPN(vector<string>& tokens) {
		if (tokens.size() == 1)	return stoi(tokens[0]);
		stack<int> stk;
		for (int i = 0; i != tokens.size(); i++) {
			if (tokens[i] != "+" && tokens[i] != "-" && tokens[i] != "*" && tokens[i] != "/")	stk.push(stoi(tokens[i]));
			else if (tokens[i] == "+") {
				int a = stk.top();stk.pop();
				int b = stk.top();stk.pop();
				stk.push(a + b);
			}
			else if (tokens[i] == "-") {
				int a = stk.top();stk.pop();
				int b = stk.top();stk.pop();
				stk.push(b - a);
			}
			else if (tokens[i] == "*") {
				int a = stk.top();stk.pop();
				int b = stk.top();stk.pop();
				stk.push(a * b);
			}
			else if (tokens[i] == "/") {
				int a = stk.top();stk.pop();
				int b = stk.top();stk.pop();
				stk.push(b / a);
			}
		}
		return stk.top();

















// 		if (tokens.size() == 1)	return stoi(tokens.front());
// 		
// 		stack<int> stk;
// 		for (int i = 0; i != tokens.size(); i++)
// 		{
// 			if (tokens[i] != "+" && tokens[i] != "-" && tokens[i] != "*" && tokens[i] != "/")
// 				stk.push(stoi(tokens[i]));
// 			else if (tokens[i] == "+")
// 			{
// 				int a = stk.top();
// 				stk.pop();
// 				int b = stk.top();
// 				stk.pop();
// 				stk.push(a + b);			
// 			}
// 			else if (tokens[i] == "-")
// 			{
// 				int a = stk.top();
// 				stk.pop();
// 				int b = stk.top();
// 				stk.pop();
// 				stk.push(b - a);			
// 			}
// 			else if (tokens[i] == "*")
// 			{
// 				int a = stk.top();
// 				stk.pop();
// 				int b = stk.top();
// 				stk.pop();
// 				stk.push(a * b);			
// 			}
// 			else
// 			{
// 				int a = stk.top();
// 				stk.pop();
// 				int b = stk.top();
// 				stk.pop();
// 				stk.push(b / a);			
// 			}
// 		}
// 		return stk.top();
	}
};

int main()
{
	/*
	["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
	["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6
	*/
	vector<string> tokens;
	tokens.push_back("4");
	tokens.push_back("13");
	tokens.push_back("5");
	tokens.push_back("/");
	tokens.push_back("+");
	Solution slt;
	int rslt = slt.evalRPN(tokens);
	return 0;
}