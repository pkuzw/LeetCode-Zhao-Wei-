///@file	Interleaving String
/*
Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

For example,
Given:
s1 = "aabcc",
s2 = "dbbca",

When s3 = "aadbbcbcac", return true.
When s3 = "aadbbbaccc", return false.
*/
///@author	zhaowei
///@date	2015.07.21
///@version	1.0

///@date	2015.08.25
///@version	2.0

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	递归判断某个字符串是否是两个字符串交叉生成的
	///@param	s1	字符串1
	///@param	end1	字符串1的最后一个字符下标
	///@param	s2	字符串2
	///@param	end2	字符串2的最后一个字符下标
	///@param	s3	字符串3
	///@param	end3	字符串3的最后一个字符下标
	///@return	如果两个字符串可以交叉生成该字符串，则返回true；否则返回false
	bool isInterleave_Time_O_pow_2_n(string s1, string s2, string s3) {
		return isInterleave_Recursive(s1, s1.size()-1, s2, s2.size()-1, s3, s3.size()-1);
	}

	///@brief	动态规划判断某个字符串是否是两个字符串交叉生成的
	///@param	s1	字符串1
	///@param	end1	字符串1的最后一个字符下标
	///@param	s2	字符串2
	///@param	end2	字符串2的最后一个字符下标
	///@param	s3	字符串3
	///@param	end3	字符串3的最后一个字符下标
	///@return	如果两个字符串可以交叉生成该字符串，则返回true；否则返回false
	/*/@note	用dp[i][j]表示s1[0..i-1]和s2[0..j-1]能够交叉组成s3[0..i+j-1]，
				初始条件是dp[0][i] = (s2[0..i-1] == s3[0..i-1]) ? true : false;
				dp[i][0] = (s1[0..i-1] == s3[0..i-1]) ?　true : false.
				递推关系式是dp[i][j] = ((dp[i][j-1] && s2[j-1] == s3[i+j-1]) || (dp[i-1][j] && s1[i-1] == s3[i+j-1])) ? true : false.
				时间复杂度为O(n^2)，空间复杂度为O(n^2)。
	*/
	bool isInterleave(string s1, string s2, string s3) {
		int len1 = s1.length(), len2 = s2.length(), len3 = s3.length();

		if (len1+len2 != len3)	//	两字符串长度之和与目标字符串不相等，直接返回false
		{
			return false;
		}
				 
		vector<vector<bool>> dp(len1+1, vector<bool>(len2+1, false));	//	利用vector的构造函数初始化
		if (len1 == 0)
		{
			return s2 == s3;
		}
		if (len2 == 0)
		{
			return s1 == s3;
		}

		for (int i = 1; i <= len1; i++)
		{
			dp[i][0] = (s1.substr(0, i) == s3.substr(0, i)) ? true : false;
		}
		for (int i = 1; i <= len2; i++)
		{
			dp[0][i] = (s2.substr(0, i) == s3.substr(0, i)) ? true : false;
		}	

		for (int i = 1; i <= len1; i++)
		{
			for (int j = 1; j <= len2; j++)
			{
				dp[i][j] = ((dp[i][j-1] && s2[j-1] == s3[i+j-1]) || (dp[i-1][j] && s1[i-1] == s3[i+j-1])) ? true : false;
			}
		}
		return dp[len1][len2];
	}

private:
	///@brief	递归判断某个字符串是否是两个字符串交叉生成的
	///@param	s1	字符串1
	///@param	end1	字符串1的最后一个字符下标
	///@param	s2	字符串2
	///@param	end2	字符串2的最后一个字符下标
	///@param	s3	字符串3
	///@param	end3	字符串3的最后一个字符下标
	///@return	如果两个字符串可以交叉生成该字符串，则返回true；否则返回false
	/* @note	递归：如果字符串3的最后一个字符可以和字符串1或2的最后一个字符匹配，则除去匹配的这两个字符，递归继续判断。递归的退出条件是
				当三个字符串的最后一个字符下标均为-1时。时间复杂度为O(2^n)？，空间复杂度为O(1). OJ报TLE
	*/
	bool isInterleave_Recursive(string s1, int end1, string s2, int end2, string s3, int end3)
	{
		if (end3 == -1)
		{
			if (end1 == -1 && end2 == -1)				
					return true;
			else
				return false;
		}
		if ((s1[end1] == s3[end3] && isInterleave_Recursive(s1.substr(0, end1), end1-1, s2, end2, s3.substr(0, end3), end3-1))
			|| (s2[end2] == s3[end3] && isInterleave_Recursive(s1, end1, s2.substr(0, end2), end2-1, s3.substr(0, end3), end3-1)))
			return true;
		
		return false;
	}
};

class Solution {
public:
	bool isInterleave(string s1, string s2, string s3) {
		int len1 = s1.size(), len2 = s2.size(), len3 = s3.size();
		if (len1 + len2 != len3)	return false;
		vector<vector<bool>> dp(len1 + 1, vector<bool>(len2 + 1, false));
		for (int i = 0; i != len1+1; i++)
			dp[i][0] = (s1.substr(0, i) == s3.substr(0, i)) ? true : false;
		for (int j = 0; j != len2+1; j++)
			dp[0][j] = (s2.substr(0, j) == s3.substr(0, j)) ? true : false;
		for (int i = 1; i != len1+1; i++)
			for (int j = 1; j != len2+1; j++)
				dp[i][j] = (dp[i][j-1] && s2[j-1] == s3[i+j-1]) || (dp[i-1][j] && s1[i-1] == s3[i+j-1]) ? true : false;
		return dp[len1][len2];
	}
};

int main()
{
	/*
	s1 = "aabcc",
	s2 = "dbbca",

	When s3 = "aadbbcbcac", return true.
	aadbbbaccc
	*/
	string s1 = "aabcc";
	string s2 = "dbbca";
	string s3 = "aadbbbaccc";
	Solution slt;
	cout << slt.isInterleave(s1, s2, s3) << endl;
	return 0;
}