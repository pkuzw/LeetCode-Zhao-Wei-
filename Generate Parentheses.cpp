/*/@file	Generate Parentheses.
			
			Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

			For example, given n = 3, a solution set is:

			"((()))", "(()())", "(())()", "()(())", "()()()"
///@author	zhaowei
///@date	2015.06.09
///@note	字符串的前i位中'('不少于')'就能保证其合法。
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution
{
public:
	///@brief	给定括号对数，生成所有可能合法括号字符串
	///@param	n	括号对数
	///@return	返回所有合法括号字符串
	///@author	zhaowei
	///@date	2015.06.09
	vector<string> generateParenthesis(int n) {
		vector<string> rslt;
		string str;
		helper(rslt, str, n, n);
		return rslt;
	}

private:
	///@brief	递归计算所有可能的合法字符串
	///@param	rslt	保存所有结果
	///@param	str		临时结果
	///@param	lnum	剩余的左括号数目
	///@param	rnum	剩余的右括号数目
	///@return	无
	///@note	只要保证剩余的左括号数目不多于右括号数即可
	void helper(vector<string>& rslt, string& str, int lnum, int rnum)
	{
		if (lnum > rnum)	//	当剩余的括号中'('数多于')'，就说明已经组合的字符串中'('数少于')'，字符串非法。
		{
			return;
		}
		if (lnum == 0 && rnum == 0)
		{
			rslt.push_back(str);
			return;
		}
		if (lnum > 0)
		{
			str.push_back('(');
			helper(rslt, str, lnum-1, rnum);
			str.pop_back();	//	将临时变量str中的左括号弹出，以准备下一种可能的组合
		}
		if (rnum > 0)
		{
			str.push_back(')');
			helper(rslt, str, lnum, rnum-1);
			str.pop_back();	//	将临时变量str中的右括号弹出，同上
		}
	}
};

int main()
{
	vector<string> parentheses;
	int n = 3;

	Solution slt;
	parentheses	= slt.generateParenthesis(n);

	for (auto i = 0; i != parentheses.size(); i++)
	{
		cout << parentheses[i] << endl;
	}

	return 0;
}
