///@file	Distinct Subsequences
/*
Given a string S and a string T, count the number of distinct subsequences of T in S.

A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of 
the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" 
while "AEC" is not).

Here is an example:
S = "rabbbit", T = "rabbit"

Return 3.
*/
///@author	zhaowei
///@date	2015.07.23
///@version	1.0

///@date	2015.08.24
///@version	1.1

///@date	2016.01.06
///@version	1.2

#include <vector>
#include <string>

using namespace std;

class Solution_v1 {
public:
	///@brief	给定两个字符串s和t，计算有多少种删除字符的方法，能够将s转换成t
	///@param	s	字符串s
	///@param	t	字符串t
	///@return	返回删除方法数
	/* @note	动态规划：设dp[i][j]表示字符串s[0..i-1]转换成t[0..j-1]的方法数。则初始条件为dp[k][0] = 1, k = 1,2,..,i；
				递推关系式为dp[i][j] = s[i-1] == t[j-1] ? dp[i-1][j-1] + dp[i-1][j] : dp[i-1][j]。该递推关系的意思是如果
				s[i-1] == t[j-1]，那么表示最末尾的两个元素是一致的，转换的方法数就等于s[0..i-2]到t[0..j-2]的方法数与s[0..i-2]到
				t[0..j-1]的方法数之和；否则只有后者。时间复杂度为O(n^2)，空间复杂度为O(n^2)。*/
	int numDistinct(string s, string t) {
		vector<vector<int>> dp(s.length()+1, vector<int>(t.length()+1, 0));	//	初始化dp
		for (vector<int>::size_type i = 0; i != s.length()+1; i++)
			dp[i][0] = 1;

		for (vector<int>::size_type i = 1; i != s.length()+1; i++)
			for (vector<int>::size_type j = 1; j != t.length()+1; j++)
				dp[i][j] = s[i-1] == t[j-1] ? dp[i-1][j] + dp[i-1][j-1] : dp[i-1][j];

		return dp[s.length()][t.length()];
	}
};

class Solution {
public:
	///@brief	给定两个字符串s和t，计算有多少种删除字符的方法，能够将s转换成t
	///@param	s	字符串s
	///@param	t	字符串t
	///@return	返回删除方法数
	/* @note	1. 动态规划：设dp[i][j]表示字符串s[0..i-1]转换成t[0..j-1]的方法数。则初始条件为dp[k][0] = 1, k = 1,2,..,i；
				递推关系式为dp[i][j] = s[i-1] == t[j-1] ? dp[i-1][j-1] + dp[i-1][j] : dp[i-1][j]。
				2. 该递推关系的意思是如果	s[i-1] == t[j-1]，那么表示最末尾的两个元素是一致的，转换的方法数就等于s[0..i-2]到t[0..j-2]的方法数与s[0..i-2]到
				t[0..j-1]的方法数之和；否则只有后者。
				3. 时间复杂度为O(n^2)，空间复杂度为O(n^2)。*/
	int numDistinct(string s, string t) {
		int slen = s.size(), tlen = t.size();
		vector<vector<int>> dp(slen + 1, vector<int>(tlen + 1, 0));
		for (int i = 0; i <= slen; i++)	dp[i][0] = 1;
		for (int i = 1; i <= slen; i++)
			for (int j = 1; j <= tlen; j++)
				dp[i][j] = s[i - 1] == t[j - 1] ? dp[i - 1][j - 1] + dp[i - 1][j] : dp[i - 1][j];
		return dp[slen][tlen];
	}
};

int main()
{
	string s("rabbbit"), t("rabbit");
	Solution slt;
	int nums = slt.numDistinct(s, t);
	return 0;
}