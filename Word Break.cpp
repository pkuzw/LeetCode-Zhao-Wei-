////@file	Word Break
/*
Given a string s and a dictionary of words dict, determine if s can be segmented into a space-separated sequence of one or more dictionary words.

For example, given
s = "leetcode",
dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code". 
*/
///@author	zhaowei
///@date	2015.07.30
///@version	1.0

///@date	2015.08.21
///@version	2.0

#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution_v1 {
public:
	///@brief	判断一个字符串能否被切分成字典中的单词
	///@param	s	字符串
	///@param	wordDict	词典
	///@return	如果可以则返回true；否则返回false
	/* @note	动态规划：设dp[i]表示字符串s[0..i-1]能否被切分成若干词典中的单词。初始条件dp[0] = true。
				递推关系式为dp[i] = dp[j] && s[j..i-1]是词典中的单词，其中0 <= j <= i-1。时间复杂度为O(n^2)，空间复杂度为O(n)。*/
	bool wordBreak(string s, unordered_set<string>& wordDict) {
		vector<bool> dp(s.length()+1, false);
		dp[0] = true;

		for (int i = 0; i <= s.length(); i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (dp[j] && wordDict.find(s.substr(j, i-j)) != wordDict.end())
				{
					dp[i] = true;
					break;	//	只需要找到一个匹配就可以
				}
			}
		}
		return dp[s.length()];
	}
};

class Solution {
public:
	bool wordBreak(string s, unordered_set<string>& wordDict) {
		if (s.empty())	return false;
		vector<bool> dp(s.size()+1, false);
		dp[0] = true;

		for (int i = 0; i != s.size()+1; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (dp[j] && wordDict.find(s.substr(j, i-j)) != wordDict.end())
				{
					dp[i] = true;
					break;
				}
			}
		}
		return dp[s.size()];
	}
};

int main()
{
	unordered_set<string> wordDict;
	wordDict.insert("leet");
	wordDict.insert("code");
	string s = "leetcode";
	Solution slt;
	bool rslt = slt.wordBreak(s, wordDict);
	return 0;
}