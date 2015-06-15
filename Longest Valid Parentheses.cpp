///@file	Longest Valid Parentheses
/*
			Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed)
			
			parentheses substring.

			For "(()", the longest valid parentheses substring is "()", which has length = 2.

			Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.
*/
///@author	zhaowei
///@date	2015.06.13

#include <iostream>
#include <string>

using namespace std;

class Solution
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
	int longestValidParentheses(string s) 
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
};

int main()
{
	string s = ")(()(()(()())))())";
	Solution slt;
	cout << slt.longestValidParentheses(s) << endl;
	return 0;
}
