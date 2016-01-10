///@file	Palindrome Partitioning
/*
Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

For example, given s = "aab",
Return

[
["aa","b"],
["a","a","b"]
]
*/
///@author	zhaowei
///@date	2015.07.24
///@version	1.0

///@date	2015.08.21
///@version	2.0

///@date	2016.01.10
///@version	2.1

#include <vector>
#include <string>

using namespace std;

class Solution_v1 {
public:
	///@brief	给定一个字符串s，对它进行划分，使得划分后的子串是回文的。
	///@param	s	字符串
	///@return	返回所有可能的划分
	/* @note	动态规划生成字符串可能的所有子串是否回文。设dp[i][j]表示字符串s[i..i+j-1]是否回文。
				初始条件：dp[i][1] = true；dp[i][2] = s[i] == s[i+1]	? true : false。
				递推关系式为dp[i][j] = dp[i+1][j-2] && s[i] == s[i+j-1] ? true : false。
				然后再用DFS生成所有可能的子串划分，这样就能够生成所有的回文划分了。时间复杂度为O(n^2)?，空间复杂度为O(n^2)。*/
	vector<vector<string>> partition(string s) {
		if (s.empty())	return sub_strings;

		int slen = s.length();
		vector<vector<bool>> dp(slen, vector<bool>(slen+1, false));

		for (int i = 0; i != slen; i++)	//	子串长度为1
			dp[i][1] = true;

		for (int i = 0; i != slen-1; i++)	//	子串长度为2
			dp[i][2] = s[i] == s[i+1] ? true : false;

		for (int j = 3; j < slen+1; j++)	//	子串长度为3及以上
			for (int i = 0; i < slen-j+1; i++)
				dp[i][j] = dp[i+1][j-2] && s[i] == s[i+j-1] ? true : false;			
		

		vector<string> tmpstr;
		DFS_Recur(s, dp, 0, tmpstr);	//	递归的生成子串划分

		return sub_strings;
	}

private:
	vector<vector<string>> sub_strings;

	///@brief	生成都是回文的所有子串划分
	///@param	s	子串
	///@param	dp	判断子串是否为回文的二维矩阵
	///@param	start	子串开始划分的起点
	///@param	tmpstr	一个子串划分
	///@return	无
	/* @note	利用深度优先搜索的思想来划分子串。*/
	void DFS_Recur(string &s, vector<vector<bool>> dp, int start, vector<string> &tmpstr)
	{
		if (start >= s.length())
		{
			sub_strings.push_back(tmpstr);
			return;
		}

		for (int sub_len = 1; sub_len <= s.length()-start; sub_len++)	//	sub_len是子串的长度
		{
			if (dp[start][sub_len])	//	如果子串是回文的，就入队
			{
				tmpstr.push_back(s.substr(start, sub_len));
				DFS_Recur(s, dp, start+sub_len, tmpstr);
				tmpstr.pop_back();	//	递归返回上一层后，弹出上一次入队的元素
			}
		}
	}
};

class Solution_v2 {
public:
	///@brief	dfs. 判断一个子串是否回文，如果是就将其压入一个结果数组，然后递归调用dfs函数，否则继续向后遍历，直到字符串末尾。
	vector<vector<string>> partition(string s) {
		vector<string> part;
		dfs(s, 0, part);
		return rslt;
	}

private:
	//	结果数组
	vector<vector<string>> rslt;

	///@brief	判断字符串是否是回文的
	bool isPalindrome(const string& s)
	{
		int start = 0;
		int end = s.size()-1;
		while (s[start] == s[end])
		{
			start++;
			end--;
			if (start > end)	return true;
		}
		return false;
	}

	///@brief	深搜的递归版实现
	void dfs(string s, int start, vector<string>& part)
	{
		if (start == s.size())
		{
			rslt.push_back(part);
			return;
		}

		for (int i = start; i != s.size(); i++)
		{
			if (isPalindrome(s.substr(start, i - start + 1)))
			{
				part.push_back(s.substr(start, i - start + 1));
				dfs(s, i + 1, part);
				part.pop_back();
			}
		}
	}
};

class Solution {
public:
	///@brief	找到字符串中的所有回文子串
	///@param	s	字符串
	///@return	返回不同的回文子串划分
	///@note	1. 递归；2. 实现一个判断子串是否为回文子串的接口，然后从前向后遍历字符串，判断子串是否回文，如果是回文，就压入进一个划分；当到达末尾时将划分压入结果数组。
	vector<vector<string>> partition(string s) {
		vector<vector<string>> rslt;
		vector<string> partition;
		helper(s, 0, partition, rslt);
		return rslt;
	}

	///@brief	判断字符串是否回文
	///@param	s	字符串
	///@return	如果字符串回文，则返回true；否则返回false
	bool isPalindrome(const string& s) {
		if (s.empty())	return true;
		int i = 0, j = s.length() - 1;
		while (s[i++] == s[j--]) {
			if (i > j)	return true;
		}
		return false;
	}

	///@brief	递归辅助函数
	///@param	s	字符串
	///@param	start	子串的起始下标
	///@param	partition	对s的一个划分
	///@param	rslt	结果数组
	void helper(const string& s, int start, vector<string>& partition, vector<vector<string>>& rslt) {
		if (start == s.size()) {
			rslt.push_back(partition);
			return;
		}
		for (int i = start; i != s.size(); i++) {
			string sub_str = s.substr(start, i - start + 1);
			if (isPalindrome(sub_str)) {
				partition.push_back(sub_str);
				helper(s, i + 1, partition, rslt);
				partition.pop_back();
			}
		}
	}
};

int main()
{
	string s = "aab";
	Solution slt;
	vector<vector<string>> rslt = slt.partition(s);
	return 0;
}