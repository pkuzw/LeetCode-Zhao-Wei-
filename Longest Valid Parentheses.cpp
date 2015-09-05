///@file	Longest Valid Parentheses
/*
			Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed)
			
			parentheses substring.

			For "(()", the longest valid parentheses substring is "()", which has length = 2.

			Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.
*/
///@author	zhaowei
///@date	2015.06.13

///@author  zhaowei
///@date    2015.09.05

#include <iostream>
#include <string>
#include <stack>

using namespace std;

class Solution_v1
{
public:
	///@brief	计算括号字符串中最长有效括号的长度
	///@param	s	字符串
	///@return	返回字符串中有效括号的最长值
	///@author	zhaowei
	///@date	2015.06.15
	///@note	利用动态规划思想，声明一个bool型的动态二维数组isValid[0...len-1][0...len-1]来标记s中[i...j]为有效字符串。
	//			首先，最简单的情形是"()"，此时最长长度为2；
	//			其次，当子字符串的两端为"("和")"时，若中间的isValid[i+1][j-1]为true，则isValid[i][j]也为true。
	//			最后，当字符串的左半部分为有效子串，右半部分也是有效子串时，其和一定为有效字串。
	//			时间复杂度为O(n^3)，空间复杂度为O(n^2)
	int longestValidParentheses_dp(string s) 
	{
		const int len = s.length();
		
		bool **isValid = new bool*[len];	//	申请动态二维数组
		for (int i = 0; i < len; i++)
		{
			isValid[i] = new bool[len];
		}

		for (int i = 0; i < len; i++)		//	对二维数组初始化。这里需要注意不能使用memset来初始化动态申请的二维数组。
											//	因为其只能保证同一行的元素是连续内存，不能保证不同行的元素也是连续分配的。
		{
			for (int j = 0; j < len; j++)
			{
				isValid[i][j] = false;
			}
		}

		int rslt = 0;

		//	最基本情形
		for (int i = 0; i < len-1; i++)
		{
			if (s[i] == '(' && s[i+1] == ')')
			{
				isValid[i][i+1] = true;
				rslt = 2;
			}
		}

		
		for (int k = 4; k <= len; k += 2)	//	基本情形外的有效串不可能为奇数长度，最短为4
		{
			for (int i = 0; i < len-k+1; i++)
			{
				if (isValid[i+1][i+k-2] && s[i] == '(' && s[i+k-1] == ')')	//	复杂情形1
				{
					isValid[i][i+k-1] = true;
				}
				else
				{
					for (int j = i+1; j < i+k-2 ; j++)
					{
						if (isValid[i][j] && isValid[j+1][i+k-1])			//	复杂情形2
						{
							isValid[i][i+k-1] = true;
						}
					}
				}
				if (isValid[i][i+k-1] == true)
				{
					rslt = k;
				}
			}
		}
		
		for (int i = 0; i < len; i++)	//	释放申请的动态二维数组
		{
			delete[] isValid[i];		//	逐行释放
		}
		delete[] isValid;				//	最后释放数组头
		return rslt;
	}

	///@brief	计算括号字符串中最长有效括号的长度
	///@param	s	字符串
	///@return	返回字符串中有效括号的最长值
	///@author	zhaowei
	///@date	2015.06.15
	///@note	对于括号对考虑用栈这种数据结构来解决。当前字符如果是'('，则入栈；当前字符如果是')'，如果栈顶元素是'('，则弹栈；
	//			如果栈顶是')'，则入栈。最后有效的括号字符串长度应该是当前字符下标 - 栈顶元素下标。注意设置栈为空的哨兵元素-1。
	//			时间复杂度为O(n)，空间复杂度为O(n)
	int longestValidParentheses_stack(string s)
	{
		int len = s.length();
		stack<int> stk;
		int rslt = 0;		
		int top = -1;	
		stk.push(top);	//	哨兵元素入栈
		for (int i = 0; i < len; i++)
		{			
			if (stk.top() == -1)	//	若栈为空，则入栈
			{
				stk.push(i);
				continue;
			}

			if (s[i] == '(')	//	若当前元素为'('，入栈
			{
				stk.push(i);
			}
			else				//	若当前元素为')'
			{
				if (stk.top() == -1)	//	栈为空，入栈
				{
					stk.push(i);
				}
				else
				{
					if (s[stk.top()] == '(')	//	栈顶为'('，弹栈
					{
						stk.pop();
					}
					else			//	栈顶为')'，入栈
					{
						stk.push(i);
					}
				}
			}			
			
			top = stk.top();
			
			
			if (top > -1)
			{
				if (rslt < i - top)	//	计算出最长值
					rslt = i - top;
			}
			else if (top == -1)
			{
				rslt = i+1;
			}
			
		}

		return rslt;
	}
};

class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> stk;
        int start = 0;
        int rslt = 0;
        for (int i = 0; i != s.size(); i++){
            if (s[i] == '(')    stk.push(i);
            else if (s[i] == ')'){
                if (stk.empty())  start = i + 1;
                else{
                    stk.pop();
                    rslt = stk.empty() ? max(rslt, i - start + 1) : max(rslt, i - stk.top());
                }
            }
        }
        return rslt;
    }
};

int main()
{
	string s = "((()))())";
	Solution_v1 slt_v1;
	cout << slt_v1.longestValidParentheses_stack(s) << endl;
    Solution slt;
    cout << slt.longestValidParentheses(s) << endl;
	return 0;
}
