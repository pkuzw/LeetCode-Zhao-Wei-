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
///@version	1.1

///@date	2016.01.11
///@version	1.2

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
	///@brief	判断一个字符串能否被切分成字典中的单词
	///@param	s	字符串
	///@param	wordDict	词典
	///@return	如果可以则返回true；否则返回false
	///@note	1. 动态规划；2. 设dp[i]表示s[0..i-1]是否能被切分成词典中的单词，初始化dp[0] = true；
	//			3. 递推关系式dp[i] = dp[j] && s[j..i-1]是词典中的单词；
	//			4. 时间复杂度为O(n^2)，空间复杂度O(n)。
	bool wordBreak(string s, unordered_set<string>& wordDict) {
		if (s.empty() || wordDict.empty())	return false;
		const int len = s.size();
		vector<bool> dp(len + 1, false);
		dp[0] = true;
		for (int i = 0; i <= len; i++) {
			for (int j = 0; j < i; j++) {
				if (dp[j] && wordDict.find(s.substr(j, i - j)) != wordDict.end()) {
					dp[i] = true;
					break;
				}
			}
		}
		return dp[len];
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