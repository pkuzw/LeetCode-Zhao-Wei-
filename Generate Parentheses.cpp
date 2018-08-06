/*/@file	Generate Parentheses.
			
			Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

			For example, given n = 3, a solution set is:

			"((()))", "(()())", "(())()", "()(())", "()()()" */

///@author	zhaowei
///@date	2015.06.09
///@note	字符串的前i位中'('不少于')'就能保证其合法。
 
///@date    2015.09.07
///@version 2.0

///@date	2015.09.21
///@version	2.1

///@date	2016.04.06
///@version	2.2

///@date    August 6, 2018
///@version 2.3

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution_v1
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

class Solution_v2 {
public:
	///@brief	构造n对括号所有可能的合法组合
	///@param	n	括号的对数
	///@return	返回所有可能的合法组合
	///@note	递归法：所有的合法构造都要求剩余的右括号数目应该大于等于剩余的左括号数目。
	//			所以在递归时当剩余的右括号数目少于剩余的左括号数目时就不再继续递归。当剩余的左右括号数目
	//			都等于0时，则将构造成的字符串压入结果数组。
	vector<string> generateParenthesis(int n) {
		vector<string> rslt;
		helper(n, n, "", rslt);
		return rslt;
	}

	///@brief	递归构造所有可能的合法括号字符串
	///@param	left	剩余的左括号数目
	///@param	right	剩余的右括号数目
	///@param	out		一个合法的括号字符串
	///@param	rslt	所有合法字符串的集合
	///@return	无
	void helper(int left, int right, string out, vector<string>& rslt) {
		if (left > right)	return;
		if (!(left || right))	rslt.push_back(out);
		else {
			if (left)	helper(left - 1, right, out + '(', rslt);
			if (right)	helper(left, right - 1, out + ')', rslt);
		}
	}
};

class Solution_v2_2 {
public:
	vector<string> generateParenthesis(int n) {
		vector<string> rslt;
		string str;
		dfs(n, n, str, rslt);
		return rslt;
	}

	void dfs(int left, int right, string str, vector<string>& rslt) {
		if (left > right)	return;
		if (!left && !right)	rslt.push_back(str);					
		else {
			if (left)	dfs(left - 1, right, str + "(", rslt);
			if (right)	dfs(left, right - 1, str + ")", rslt);
		}

	}
};

class Solution {
public:
    ///@brief   给定参数n，计算所有合法的括号组合。
    ///@param   n   参数n，表示有n对左右括号。
    ///@return  返回所有合法的包含n对左右括号的字符串。
    ///@note    1. 递归法求解。注意到在拼凑合法的括号字符串时，只有当左括号的数目不少于右括号的数目时，目前的括号字符串才合法。利用这一点来进行递归。
    ///         2. 时间复杂度为O(n^2)?空间复杂度为O(m*n)，其中m是合法的字符串数目。
    vector<string> generateParenthesis(int n) {
        vector<string> rslt;
        string str = "";
        dfs(n, n, str, rslt);
        return rslt;
    }
    
    ///@brief   递归计算合法的括号字符串。
    ///@param   left    还没有使用的左括号的数目。
    ///@param   right   还没有使用的右括号数目。
    ///@param   valid_str   合法的字符串。
    ///@param   rslt    合法字符串集合。
    ///@note    1. 如果left > right，说明目前字符串中的左括号使用的比右括号少，那么必为非法字符串，直接返回。
    ///         2. 如果左括号和右括号的剩余数量都为0，那么说明是一个合法字符串，压入结果集合。
    ///         3. 否则分成两种情况，一种是将left自减1，然后给现有字符串添加一个左括号，递归调用dfs()函数本身；
    //             另一种是将right自减1，然后将现有字符串添加一个右括号，再递归地调用dfs()。
    void dfs(int left, int right, string valid_str, vector<string>& rslt) {
        if (left > right)   return;
        if (left == 0 && right == 0)    rslt.push_back(valid_str);
        else {
            if (left)   dfs(left - 1, right, valid_str + '(', rslt);
            if (right)  dfs(left, right - 1, valid_str + ')', rslt);
        }
    }
};

int main()
{
	vector<string> parentheses;
	int n = 3;

	Solution slt;
	parentheses	= slt.generateParenthesis(n);
	
	Solution_v2 s2;
	vector<string> p2 = s2.generateParenthesis(n);
	return 0;
}
