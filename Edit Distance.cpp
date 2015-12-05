///@file	Edit Distance
/*
Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. 
(each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character
*/
///@author	zhaowei
///@date	2015.07.17
///@version	1.0

///@date	2015.08.27
///@version	2.0

///@date	2015.12.05
///@version	2.1

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	给定两个单词，将单词1转换成单词2，转换包括三种方法：1. 插入一个字符；2. 删除一个字符；3. 替换一个字符，计算需要的最少步数。
	///@param	word1	单词1
	///@param	word2	单词2
	///@return	返回转换需要的最小步数
	///@note	动态规划：设dp[i][j]表示word1[0..i-1]到word2[0..j-1]的操作步数，则初始值为dp[0][j] = j, dp[i][0] = i。
	//			dp[i][j] = (word1[i-1] == word2[j-1]) ？ dp[i-1][j-1] ： 1+min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])。这个公式表示如果当前
	//			两个字符相等，则等于除去这两个字符的步骤数；否则等于word1[0..i-2]到word2[0..j-1]的步骤数加上给word1添加一个字符的操作或者
	//			等于word1[0..i-1]到word2[0..j-2]的步骤数加上给word1删去一个字符的操作或者等于等于word1[0..i-2]到word2[0..j-2]的步骤数加上
	//			给word1更新最后一个字符的操作的最小值。时间复杂度为O(n^2)，空间复杂度为O(n^2)。
	int minDistance(string word1, string word2) {
		const int len1 = word1.length(), len2 = word2.length();
		vector<vector<int>> dp;
		vector<int> line;
		for (int i = 0; i != len2+1; i++)
		{
			line.push_back(0);
		}
		for (int i = 0; i != len1+1; i++)
		{
			dp.push_back(line);
		}
		
		//	初始化dp
		for (int i = 0; i != len2+1; i++)
		{
			dp[0][i] = i; 
		}
		for (int i = 0; i != len1+1; i++)
		{
			dp[i][0] = i;
		}

		for (int i = 1; i != len1+1; i++)
		{
			for (int j = 1; j != len2+1; j++)
			{
				dp[i][j] = (word1[i-1] == word2[j-1]) ? (dp[i-1][j-1]) : (1 + min(dp[i-1][j], min(dp[i][j-1], dp[i-1][j-1])));	//	递推公式
			}
		}
		return dp[len1][len2];
	}
};

class Solution {
public:
	///@brief	给定两个字符串word1和word2，可以进行三种操作，删除某个字符，增加某个字符或者更新某个字符。计算将word1变为word2的最少步数。
	///@param	word1	字符串1
	///@param	word2	字符串2
	///@return	返回将字符串1变为字符串2的最少步数
	///@note	1. 动态规划：设dp[i][j]表示将word1[0..i-1]变为word2[0..j-1]的最少步数。初始化dp[0][j] = j, dp[i][0] = i；递推关系式为
	//			dp[i][j] = word1[i-1] == word2[j-1] ? dp[i-1][j-1] : 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])；
	//			2. 时间复杂度为O(mn)，空间复杂度为O(mn)，其中m, n分别是word1和word2的长度。
	int minDistance(string word1, string word2) {
		int m = word1.length();
		int n = word2.length();
		vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
		for (int i = 0; i != m + 1; i++)	dp[i][0] = i;
		for (int i = 0; i != n + 1; i++)	dp[0][i] = i;
		for (int i = 1; i != m + 1; i++) {
			for (int j = 1; j != n + 1; j++) {
				dp[i][j] = word1[i-1] == word2[j-1] ? dp[i-1][j-1] : 1 + min(dp[i-1][j], min(dp[i][j-1], dp[i-1][j-1]));
			}
		}
		return dp[m][n];
	}
};

int main()
{
	Solution slt;
	string word1 = "jeep wrangler", word2 = "jeep compass";
	Solution_v1 slt_v1;
	int rslt = slt.minDistance(word1, word2);
	rslt = slt_v1.minDistance(word1, word2);
	return 0;
}