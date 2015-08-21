///@file Palindrome Partitioning II
/*
Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

For example, given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut. 
*/
///@author	zhaowei
///@date	2015.07.27
///@version	1.0

///@date	2015.08.21
///@version	2.0

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution_v1 {
public:
	///@brief	计算将s划分为回文子串的最小的分割次数
	///@param	s	字符串
	///@return	返回最小分割次数
	/* @note	动态规划：设dp[i][j]表示字符串s[i..i+j-1]是否是回文字符串，mins[i]表示s[0..i]的最小分割次数。
				初始条件：dp[i][1] = true, dp[i][2] = (s[i] == s[i+1]), mins[0] = 0
				递推关系式： dp[i][j] = (s[i] == s[i+j-1] && dp[i+1][j-2])
				如果s[0...i]是回文，mins[i] = 0；
				如果s[0...i]不是回文，mins[i] = min{mins[k] + 1 (s[k+1...i]是回文)  或  mins[k] + i - k (s[k+1...i]不是回文)}，
				其中0<= k < i.
				时间复杂度为O(n^2)，空间复杂度为O(n^2).
				*/
	int minCut(string s) {
		int len = s.length();
		if(len <= 1)return 0;

		vector<vector<bool>> dp(len, vector<bool>(len+1, false));
		for (int i = 0; i != len; i++)	dp[i][1] = true;

		vector<int> mins(len, 0);//mins[i]表示s[0...i]的最小分割次数
		mins[0] = 0;
		for (int k = 2; k <= len; k++)
		{
			for (int i = 0; i <= len-k; i++)
			{
				if (k == 2)
					dp[i][2] = (s[i] == s[i+1]);
				else dp[i][k] = dp[i+1][k-2] && (s[i] == s[i+k-1]);
			}

			if (dp[0][k])
			{
				mins[k-1] = 0;
				continue;
			}

			mins[k-1] = len - 1;
			for(int i = 0; i < k-1; i++)
			{
				int tmp;
				if (dp[i+1][k-i-1])
					tmp = mins[i]+1;
				else
					tmp = mins[i]+k-i-1;
				if (mins[k-1] > tmp)
					mins[k-1] = tmp;
			}
		}
		return mins[len-1];
	}

};

class Solution {
public:
	/*//@note	动态规划。isPalin[i][j]表示s[i..j]是否是回文，min_cut[i]表示s[0..i-1]需要的最小切割数，初始化min_cut[i] = i-1, 
				0 <= i <= s.size(). 
				递推关系式为min_cut[j+1] = if (s[i] == s[j] && (j - i < 2 || isPalin[i+1][j-1])) then min(min_cut[j+1], min_cut[i]+1)
	*/
	int minCut(string s) {
		int size = s.size();
		vector<vector<bool>> isPalin(size, vector<bool>(size, false));
		vector<int> min_cut(size+1, 0);
		for (int i = 0; i != size+1; i++)
			min_cut[i] = i-1;

		for (int j = 1; j != size; j++)
		{
			for (int i = j; i >= 0; i--)
			{
				if ((s[i] == s[j]) && (j - i < 2 || isPalin[i+1][j-1]))
				{
					isPalin[i][j] = true;
					min_cut[j+1] = min(min_cut[j+1], min_cut[i] + 1);
				}
			}
		}
		return min_cut[size];
	}
};

int main()
{
	string s = "aab";
	Solution slt;
	int rslt = slt.minCut(s);
	return 0;
}