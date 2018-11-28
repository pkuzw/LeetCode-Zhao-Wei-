///@file	Scramble String
/*
Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.

Below is one possible representation of s1 = "great":

great
/    \
gr    eat
/ \    /  \
g   r  e   at
/ \
a   t
To scramble the string, we may choose any non-leaf node and swap its two children.

For example, if we choose the node "gr" and swap its two children, it produces a scrambled string "rgeat".

rgeat
/    \
rg    eat
/ \    /  \
r   g  e   at
/ \
a   t
We say that "rgeat" is a scrambled string of "great".

Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled string "rgtae".

rgtae
/    \
rg    tae
/ \    /  \
r   g  ta  e
/ \
t   a
We say that "rgtae" is a scrambled string of "great".

Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1.
*/
///@author	zhaowei
///@date	2015.07.20
///@version	1.0

///@date	2015.08.26
///@version	2.0

///@date	2015.12.11
///@version 2.1

///@date	2016.05.02
///@version	2.2

///@date    November 28, 2018
///@version 2.3

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution_v1 {
public:
	///@brief	当一个字符串被用二叉树表示时，交换二叉树同一个父节点下的叶节点所得到的新字符串我们称之为Scramble String，现在给定两个字符串，
	//			写一个函数判定这两个字符串是否是scramble string
	///@param	s1	字符串1
	///@param	s2	字符串2
	///@return  如果这两个字符串是scramble string的话返回true；否则返回false	
	bool isScramble(string s1, string s2) {
	//	bool rslt = isScramble_Recur(s1, s2);
		bool rslt = isScramble_DP(s1, s2);
		return rslt;
	}

private:
	///@brief	递归的比较两个字符串是否为scramble string
	///@param	s1	字符串1
	///@param   s2	字符串2
	///@return  如果这两个字符串是scramble string的话返回true；否则返回false
	/* @note	递归法：如果字符串s1[0...i]和字符串s2[0...j](i == j)满足下列条件之一时就认为它们是scramble string:
				a. s1[0..k]与s2[0..k]是scramble string且s1[k+1..i]与s2[k+1..j]是scramble string；
				b. s1[0..k]与s2[j-k..j]是scramble string且s1[k+1..i]与s2[0..j-k-1]是scramble string；其中k = 0...i-1
				时间复杂度为O(2^n)
	*/
	bool isScramble_Recur(string& s1, string & s2)
	{
		string s1_tmp = s1;
		string s2_tmp = s2;
		sort(s1_tmp.begin(), s1_tmp.end());
		sort(s2_tmp.begin(), s2_tmp.end());
		if (s1_tmp != s2_tmp)	//	如果两个字符串所包含的字符不相同，则直接返回false
			return false;
		
		if (s1 == s2)	//	如果两字符串完全相同，直接返回true
			return true;
		
		for (int i = 1; i != s1.length(); i++)	//	i从1开始，保证不出现空字符串
		{
			string s1_left = s1.substr(0, i);
			string s1_right = s1.substr(i, s1.length()-i);

			string s2_left = s2.substr(0, i);
			string s2_right = s2.substr(i, s2.length()-i);

			if (isScramble_Recur(s1_left, s2_left) && isScramble_Recur(s1_right, s2_right))
			{
				return true;
			}

			s2_right = s2.substr(s2.length()-i, i);
			s2_left = s2.substr(0, s2.length()-i);

			if (isScramble_Recur(s1_left, s2_right) && isScramble_Recur(s1_right, s2_left))
			{
				return true;
			}
		}
		return false;
	}

	///@brief	动态规划法判断两字符串是否为scramble string
	///@param	s1	字符串1
	///@param   s2	字符串2
	///@return  如果这两个字符串是scramble string的话返回true；否则返回false
	/* @note	维护一个三维数组来dp[k][i][j]保存字符串s1[i..i+k]与字符串s2[j..j+k]是否为scramble string。
				初始条件为dp[1][i][j] = (s1[i] == s2[j]) ? true : false，
				dp[k][i][j] = ((dp[l][i][j] && dp[k-l][i+l][j+l]) || (dp[l][i][j+k-l] && dp[k-l][i+l][j]))。
				时间复杂度为O(n^4)，空间复杂度为O(n^3)。
	*/
	bool isScramble_DP(string &s1, string &s2)
	{
		if (s1.length() != s2.length())
		{
			return false;
		}
		const int len = s1.length();

		vector<vector<vector<bool>>> dp;
		vector<vector<bool>> matrix;
		vector<bool> line;

		for (int i = 0; i != len; i++)
			line.push_back(false);
		for (int i = 0; i != len; i++)
			matrix.push_back(line);		
		for (int i = 0; i != len+1; i++)
			dp.push_back(matrix);

		for (int i = 0; i != len; i++)
		{
			for (int j = 0; j != len; j++)
			{
				dp[1][i][j] = (s1[i] == s2[j]) ? true : false;
			}
		}

		for (int k = 2; k != len+1; k++)
		{
			for (int i = 0; i != len-k+1; i++)
			{
				for (int j = 0; j != len-k+1; j++)
				{					
					for (int l = 1; l != k && !dp[k][i][j]; l++)	//? 这里为什么要判断一下dp[k][i][j]? 这是因为如果已经判定出s1和s2在dp[k][i][j]处为true后，不需要也不能再进入后续的判定，一是浪费时间，二是有可能将原来的true抹成false
					{
						dp[k][i][j] = ((dp[l][i][j] && dp[k-l][i+l][j+l]) || (dp[l][i][j+k-l] && dp[k-l][i+l][j]));
					}
				}
			}
		}
		return dp[len][0][0];		
	}
};

/*
dp[k][i][j]表示s1[i..i+k-1]是否与s2[j, j+k-1]为scramble string
*/
class Solution_v2 {
public:
	///@brief	判断两个字符串能够通过在二叉树节点上的交换来互相转换
	///@param	s1	字符串1
	///@param	s2	字符串2
	///@return	如果可以相互转换，则返回true；否则返回false
	///@note	1. 动态规划：1.维护一个三维数组来dp[k][i][j]保存字符串s1[i..i+k]与字符串s2[j..j+k]是否为scramble string。
	//			2. 初始条件为dp[1][i][j] = (s1[i] == s2[j]) ? true : false，
	//			3. 递推关系式为dp[k][i][j] = ((dp[l][i][j] && dp[k-l][i+l][j+l]) || (dp[l][i][j+k-l] && dp[k-l][i+l][j]))。
	//			4. 时间复杂度为O(n^4)，空间复杂度为O(n^3)。
	bool isScramble(string s1, string s2) {
		if (s1.size() != s2.size())	return false;
		const int len = s1.size();
		vector<vector<vector<bool>>> dp(len+1, vector<vector<bool>>(len, vector<bool>(len, false)));
		for (int i = 0; i != len; i++)
			for (int j = 0; j != len; j++)
				dp[1][i][j] = (s1[i] == s2[j]) ? true : false;
		for (int k = 2; k != len+1; k++)
			for (int i = 0; i != len-k+1; i++)
				for (int j = 0; j != len-k+1; j++)
					for (int l = 1; l != k && !dp[k][i][j]; l++)
						dp[k][i][j] = (dp[l][i][j] && dp[k-l][i+l][j+l]) || (dp[l][i][j+k-l] && dp[k-l][i+l][j]);
		return dp[len][0][0];
	}
};

class Solution {
public:
	bool isScramble(string s1, string s2) {
		if (s1.size() != s2.size())	return false;
		int len = s1.size();
		vector<vector<vector<bool>>> dp(len + 1, vector<vector<bool>>(len, vector<bool>(len, false)));
		for (int i = 0; i != len; i++) 
			for (int j = 0; j != len; j++)
				dp[1][i][j] = s1[i] == s2[j] ? true : false;
		for (int k = 2; k != len + 1; k++)
			for (int i = 0; i != len - k + 1; i++)
				for (int j = 0; j != len - k + 1; j++)
					for (int l = 1; l != k && !dp[k][i][j]; l++)
						dp[k][i][j] = (dp[l][i][j] && dp[k-l][i+l][j+l]) || (dp[l][i][j+k-l] && dp[k-l][i+l][j]);
		return dp[len][0][0];		
	}
};

int main()
{
	string s1 = "abc", s2 = "acb";
	Solution slt;
	cout << slt.isScramble(s1, s2) << endl;
	return 0;
}
