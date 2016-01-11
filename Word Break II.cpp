///@file	Word Break II
/*
Given a string s and a dictionary of words dict, add spaces in s to construct a sentence where each word is a valid dictionary word.

Return all such possible sentences.

For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"]. 
*/
///@author	zhaowei
///@date	2015.07.30
///@version	1.0

///@date	2015.08.20
///@version	1.1

///@date	2016.01.11
///@version	1.2

#include <unordered_set>
#include <string>

using namespace std;

class Solution_v1 {
public:
	///@brief	给出字符串所有可能的满足词典的划分
	///@param	s	字符串
	///@param	wordDict	词典
	///@return	返回所有可能的划分
	/* @note	用一个一维数组记录下能够被划分的区间。dp[i]表示字符串s[i..end-1]是可以被划分的。
				这样在DFS递归查找所有可能时，如果不能够划分，就不用继续递归了，省去了很多重复计算。*/
	vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
		vector<bool> dp(s.size()+1, true);
		string sentence;
		wordBreak_DFS(s, wordDict, 0, dp, sentence);
		return rslt;
	}

private:
	///@brief	递归查找所有可能的划分
	///@param	s	原始字符串
	///@param	wordDict	词典
	///@param	start	开始划分的起点
	///@param	dp	某区间可否进行划分
	///@param	sentence	一个划分
	void wordBreak_DFS(string s, unordered_set<string>& wordDict, int start, vector<bool>& dp, string& sentence)
	{
		if (start == s.length())
		{
			rslt.push_back(sentence.substr(0, sentence.length()-1));		//	截取最后一个空格符
			return;
		}

		for (int i = start; i < s.length(); i++)
		{
			string word = s.substr(start, i-start+1);
			if (dp[i+1] && wordDict.find(word) != wordDict.end())
			{
				sentence = sentence + word + " ";

				int old_size = rslt.size();
				wordBreak_DFS(s, wordDict, i+1, dp, sentence);
				
				if (old_size == rslt.size())	//	如果没有划分成功，说明这个区间不能进行划分
					dp[i+1] = false;
				
				sentence = sentence.substr(0, sentence.length() - word.length() - 1);
			}			
		}
	}

	vector<string> rslt;
};

class Solution {
public:
	///@brief	给出字符串所有可能的满足词典的划分
	///@param	s	字符串
	///@param	wordDict	词典
	///@return	返回所有可能的划分
	///@note	1. 动态规划和深度优先遍历；2. 用一个一维数组记录下能够被划分的区间。dp[i]表示字符串s[i..end-1]是可以被划分的。
	//			这样在DFS递归查找所有可能时，如果不能够划分，就不用继续递归了，省去了很多重复计算。
	vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
		vector<string> rslt;
		vector<bool> dp(s.size() + 1, true);
		string sentence;
		helper(s, wordDict, 0, dp, sentence, rslt);
		return rslt;
	}

	///@brief	递归查找所有可能的划分
	///@param	s			原始字符串
	///@param	wordDict	词典
	///@param	start		开始划分的起点
	///@param	dp			某区间可否进行划分
	///@param	sentence	一个划分
	///@param	rslt		结果数组
	void helper(string s, unordered_set<string>& wordDict, int start, vector<bool>& dp, string& sentence, vector<string>& rslt) {
		if (start == s.size()) {
			rslt.push_back(sentence.substr(1));
			return;
		}
		for (int i = start; i != s.size(); i++) {
			string word = s.substr(start, i - start + 1);
			if (dp[i + 1] && wordDict.find(word) != wordDict.end()) {
				sentence += " " + word;
				int old_size = rslt.size();
				helper(s, wordDict, i + 1, dp, sentence, rslt);
				if (old_size == rslt.size())	dp[i+1] = false;	// 结果数组没有变化，说明s[i+1..end-1]不可划分
				sentence = sentence.substr(0, sentence.size() - word.size() - 1);
			}
		}
	}
};


int main()
{
	/*
	s = "catsanddog",
	dict = ["cat", "cats", "and", "sand", "dog"]
	*/
	unordered_set<string> wordDict;
	wordDict.insert("cat");
	wordDict.insert("cats");
	wordDict.insert("and");
	wordDict.insert("sand");
	wordDict.insert("dog");

	string s = "catsanddog";

	Solution slt;
	vector<string> rslt = slt.wordBreak(s, wordDict);
	return 0;
}